#!/bin/sh

# set -x shows commands as they are executed
# In this script, echo commands will not be printed - hence set +x will be set (see echotimestamp function)

# Shell script settings
memleak=0
compile=0
sanitize=0
coverage=0
profiler=0
tests=0
clean=no
cleanbyproduct=0
debug=0
doc=0
qtbasedir=
clean_target=

# Make file settings
PROJNAME=browser
EXENAME=${PROJNAME}
TESTEREXENAME=${PROJNAME}_tester
EXEDIR=bin

LOGDIR=log
DEBUGLOG=debug.log
DEBUGERR=debug.err
COMPLOG=compile_browser.log
COMPERR=compile_browser.err
DOCLOG=doc.log
DOCERR=doc.err
COVERAGELOG=coverage.log
COVERAGEERR=coverage.err
PROFILERLOG=profiler.log
PROFILERERR=profiler.err
EXELOG=${EXENAME}.log
VALGRINDNOINPUTLOG=valgrind_noinput.log
EXEVALGRINDLOG=${EXENAME}_valgrind.log

VERBOSITY=1

COMPILETYPE=Debug
COVERAGE=0
SANITIZER=0
CEXTRAFLAGS=-DENABLE_ASSERTIONS
BEHFLAGS=
COVEXTRAOPTS=--json-format
PROFEXTRAOPTS=

QTBASEDIR=/opt/qt/5.15.0/gcc_64

DATE_FORMAT="%a %d %b %Y"
TIME_FORMAT=%H:%M:%S

ITEMSYMBOL="-->"

valid_compile_types="
	(Debug to compile in debug mode without enabling compile optimizations)
	(Release to compile in release mode enabling compile optimizations)"

valid_clean_levels="
	(no to not perform any cleaning)
	(all to clean all generate files)
	(logs to clean log files)
	(byproducts to clean dependency files, object files and MOC generated files)
	(outputs to clean doxygen documentation and converage and profiling files)
	(binaries to clean all binaries)"

#########################################################
# Logging
#########################################################
echotimestamp() {
	# set +x do not print commands as they are executed
	(set +x; \
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]  - $1")
}

#########################################################
# Help
#########################################################
usage() {
	echotimestamp "  - Usage:"
	echotimestamp "  - >$0 <options>"
	echotimestamp ""
	echotimestamp "       --clean|-c:		delete generated files before start compilation.
	Its default behaviour is to delete all generated files. However the user can choose what to delete by adding an optional argument.
	List of valid arguments is:${valid_clean_levels}"
	echotimestamp "       --cleanbyproduct|-cbp:	delete generated files during compilation. This step is run after compilation is completed and succesfull."
	echotimestamp "       --doc|-d:			generate documentation"
	echotimestamp "       --debug|-g:		dump makefile flags to ${LOGDIR}/${DEBUGLOG}"
	echotimestamp "       --compile|-co:		compile the programme.
	Its default behaviour is to compile it in debug mode. Nonetheless the user can specify the mode by adding an optional argument to this option.
	List of valid arguments is:${valid_compile_types}"
	echotimestamp "       --sanitize|-s:		enable sanitize while compiling - note that this option is only valid if compiling the source code"
	echotimestamp "       --coverage|-cov:		add coverage flags while compiling and generate coverage report"
	echotimestamp "       --profiler|-p:		add profiling flags while compiling and generate profiling report"
	echotimestamp "       --memleak|-m:		compile and check memory leaks using valgrind" 
	echotimestamp "       --test|-t:			run tests"
	echotimestamp "       --qtbasedir:		base directory of QT or system"
	echotimestamp "       				- system: use system QT libraries"
	echotimestamp "       				- <directory>: base directory of QT. It is assumed that it contains the following directories: lib, include and bin. QT specific environment variables are set as follows: QTLIBDIR = QTBASEDIR/lib and QTTOLLDIR = QTBASEDIR/bin"
	echotimestamp "       --help|-h:		print this help"
}

#########################################################
# Compilation
#########################################################
compile_binary() {
	filename=""
	directoryname=""
	if [ $# -eq 0 ] || [ $# -gt 1 ]; then
		echotimestamp " Function $0 accepts only 1 arguments - provided $#."
		echotimestamp " Usage:"
		echotimestamp " >$0 <target>"
		exit 1
	else
		target=$1
	fi

	if [ ${compile} -eq 1 ]; then
		echo "\n"
		echotimestamp " ========================================================================="
		echotimestamp " Execute target ${target}"
		echotimestamp " ========================================================================="
		(set -x; \
		 make ${target} LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} CEXTRAFLAGS=${CEXTRAFLAGS} SANITIZER=${SANITIZER} COVERAGE=${COVERAGE} PROFILER=${PROFILER} 1> ${LOGDIR}/${COMPLOG} 2> ${LOGDIR}/${COMPERR} COMPILE_TYPE=${COMPILETYPE})
		# If make returns code 2, it means it encountered errors
		retCode=$?
		if [ ${retCode} -eq 2 ]; then
			echotimestamp " FAILED: Execution of target ${target} failed as Makefile return code is ${retCode}"
			exit 1
		else
			echotimestamp " SUCCEED: Execution of target ${target} succeeded as Makefile return code is ${retCode}"
		fi
	fi
}

#########################################################
# Qt base directory
#########################################################
choose_qtbasedir() {
	valid_answer=0
	valid_replies="
	(y or Y for yes)
	(n or N for no and exit)
	(<path> to set the Qt base directory)"
	echotimestamp " Do you want to use the system libraries?${valid_replies}"
	while [ ${valid_answer} -eq 0 ]; do
		read reply
		case "${reply}" in
			y|Y)
				valid_answer=1
				;;
			n|N)
				echotimestamp " Exiting..."
				exit 1
				;;
			?*)
				if [ -d ${reply} ]; then
					QTBASEDIR=${reply}
					valid_answer=1
				else
					echotimestamp " Reply ${reply} is not valid. Valid replies are:${valid_replies}"
					valid_answer=0
				fi
				;;
		esac
	done
}

fill_qt_paths() {
	paths_found=1
	if ! [ -z "${QTBASEDIR}" ]; then
		if [ -d ${QTBASEDIR} ]; then
			if [ -d ${QTBASEDIR}/lib ]; then
				export QTLIBDIR=${QTBASEDIR}/lib
				export LD_LIBRARY_PATH=${QTLIBDIR}:${LD_LIBRARY_PATH}
			else
				paths_found=0
			fi
			if [ -d ${QTBASEDIR}/include ]; then
				export QTINCLUDEDIR=${QTBASEDIR}/include
			else
				paths_found=0
			fi
			if [ -d ${QTBASEDIR}/bin ]; then
				export QTTOOLDIR=${QTBASEDIR}/bin
				export PATH=${QTTOOLDIR}:${PATH}
			else
				paths_found=0
			fi
		else
			paths_found=0
		fi
	fi

	return ${paths_found}
}

configure_qt_paths() {
	# Settings QT libraries path
	if ! [ -z "${qtbasedir}" ]; then
		if [ "${qtbasedir}" = "system" ]; then
			QTBASEDIR=
		elif [ -d ${qtbasedir} ]; then
			QTBASEDIR=${qtbasedir}
		else
			echotimestamp " Unable to find Qt base directory ${qtbasedir} passed to command line"
			choose_qtbasedir
		fi
	fi

	fill_qt_paths
	success=$?

	while [ ${success} -eq 0 ]; do
		echotimestamp " Unable to find all Qt paths (${QTBASEDIR}/lib, ${QTBASEDIR}/include and ${QTBASEDIR}/bin)"
		choose_qtbasedir
		fill_qt_paths
		success=$?
	done
}

#########################################################
# Compile configuration
#########################################################
choose_compile_type() {
	valid_answer=0
	echotimestamp " What type of compilation do you want to set?${valid_compile_types}"
	while [ ${valid_answer} -eq 0 ]; do
		read reply
		case "${reply}" in
			Debug|Release)
				COMPILETYPE=${reply}
				valid_answer=1
				;;
			?*)
				echotimestamp " Reply ${reply} is not valid. Valid replies are:${valid_compile_types}"
				valid_answer=0
				;;
		esac
	done
}

check_compile_type() {
	valid_compile_type=0;
	case "${COMPILETYPE}" in
		Debug|Release)
			valid_compile_type=1
			;;
		?*)
			echotimestamp " Reply ${COMPILETYPE} is not valid. Valid replies are:${valid_compile_types}"
			valid_compile_type=0
			;;
	esac
	return ${valid_compile_type}
}

configure_compilation() {
	check_compile_type
	success=$?

	if [ ${success} -eq 0 ]; then
		echotimestamp " Compilation type ${COMPILETYPE} is not supported"
		choose_compile_type
	fi
}

#########################################################
# Clean operation configuration
#########################################################
choose_clean_level() {
	valid_answer=0

	echotimestamp " Do you want to perfom any cleaning?${valid_clean_levels}"
	while [ ${valid_answer} -eq 0 ]; do
		read reply
		case "${reply}" in
			no|all|logs|binaries|outputs|byproducts)
				clean=${reply}
				valid_answer=1
				;;
			?*)
				echotimestamp " Reply ${reply} is not valid. Valid replies are:${valid_clean_levels}"
				valid_answer=0
				;;
		esac
	done
}

set_clean_target() {
	target_set=0;
	case "${clean}" in
		no)
			clean_target=""
			target_set=1;
			;;
		all)
			clean_target="clean"
			target_set=1;
			;;
		logs|binaries|outputs|byproducts)
			clean_target="clean_${clean}"
			target_set=1;
			;;
		?*)
			target_set=0;
			;;
	esac

	return ${target_set}
}

configure_clean_operations() {
	set_clean_target
	success=$?

	while [ ${success} -eq 0 ]; do
		echotimestamp " Clean level ${clean} is not supported"
		choose_clean_level
		set_clean_target
		success=$?
	done

	if [ "${clean}" != "no" ] && [ "${clean_target}" = "" ]; then
		echotimestamp " Value of clean ${clean} expects target to have a value difference from an empty string"
		exit 1
	fi
}

if [ $# -lt 1 ]; then
	usage
	exit 1
fi

for args
do
	case "$1" in
		--compile|-co)
			compile=1
			next_arg=$2
			case "${next_arg}" in
				"" | -*)
					COMPILETYPE=Debug
					;;
				?*)
					COMPILETYPE=${next_arg}
					shift 1
					;;
			esac
			configure_compilation
			shift 1
			;;
		--coverage|-cov)
			coverage=1
			shift 1
			;;
		--profiler|-p)
			profiler=1
			shift 1
			;;
		--sanitize|-s)
			sanitize=1
			shift 1
			;;
		--test|-t)
			tests=1
			shift 1
			;;
		--doc|-d)
			doc=1
			shift 1
			;;
		--memleak|-m)
			memleak=1
			shift 1
			;;
		--debug|-g)
			debug=1
			shift 1
			;;
		--cleanbyproduct|-cbp)
			cleanbyproduct=1
			shift 1
			;;
		--clean|-c)
			next_arg=$2
			case "${next_arg}" in
				"" | -*)
					clean=all
					;;
				?*)
					clean=${next_arg}
					shift 1
					;;
			esac
			configure_clean_operations
			shift 1
			;;
		--qtbasedir)
			qtbasedir=$2
			shift 2
			;;
		--help|-h)
			usage
			exit 0
			;;
		?*)
			echotimestamp " Illegal argument $1"
			usage
			exit 1
			;;
	esac
done

configure_qt_paths

if [ ${compile} -eq 0 ] && [ ${sanitize} -eq 1 ]; then
	echotimestamp " Unable to enable sanitizer or coverage as compilation is disabled."
	echotimestamp " ${ITEMSYMBOL} sanitizer: ${sanitize} (expected 0)"
	exit 1
else
	SANITIZER=${sanitize}
fi

COVERAGE=${coverage}
PROFILER=${profiler}

if [ ${compile} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echotimestamp " Run script variables"
	echotimestamp " ========================================================================="
	echotimestamp " EXECUTABLE"
	echotimestamp " ========================================================================="
	echotimestamp " ${ITEMSYMBOL} Directory of the executable: ${EXEDIR}"
	echotimestamp " ${ITEMSYMBOL} Executable filename: ${EXENAME}"
	echo "\n"
fi

echotimestamp " ========================================================================="
echotimestamp " LOGS"
echotimestamp " ========================================================================="
echotimestamp " ${ITEMSYMBOL} Logfile directory: ${LOGDIRR}"

if [ ${debug} -eq 1 ]; then
	echotimestamp " ${ITEMSYMBOL} Debug logfile name: ${DEBUGLOG}"
	echotimestamp " ${ITEMSYMBOL} Debug error file name: ${DEBUGERR}"
fi

if [ ${compile} -eq 1 ]; then
	echotimestamp " ${ITEMSYMBOL} Compile logfile name: ${COMPLOG}"
	echotimestamp " ${ITEMSYMBOL} Compile error file name: ${COMPERR}"
fi

if [ ${tests} -eq 1 ]; then
	echotimestamp " ${ITEMSYMBOL} Executable logfile: ${EXELOG}"
fi

if [ ${doc} -eq 1 ]; then
	echotimestamp " ${ITEMSYMBOL} Documentation logfile name: ${DOCLOG}"
	echotimestamp " ${ITEMSYMBOL} Documentation error file name: ${DOCERR}"
fi

if [ ${memleak} -eq 1 ]; then
	echotimestamp " ${ITEMSYMBOL} Valgrind test set logfile name: ${VALGRINDTESLOG}"
	echotimestamp " ${ITEMSYMBOL} Valgrind test label logfile name: ${VALGRINDNOINPUTLOG}"
	echotimestamp " ${ITEMSYMBOL} Valgrind all input files logfile name: ${VALGRINDALLLOG}"
	echotimestamp " ${ITEMSYMBOL} Valgrind executable logfile name: ${EXEVALGRINDLOG}"
fi

echo "\n"

if [ "${clean}" != "no" ] && [ "${clean_target}" != "" ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Clean workspace"
	echotimestamp " ========================================================================="
	(set -x; \
	 make ${clean_target} LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR})
elif [ ${compile} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Delete executable directory ${EXEDIR}"
	echotimestamp " ========================================================================="
	# Delete executable directory in order to avoid using the previous executables if compile fails and running tests
	(set -x; \
	 /bin/rm -rf ${EXEDIR}/*)
fi

if [ ${compile} -eq 1 ] || [ ${tests} -eq 1 ] || [ ${debug} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echo "\n"
	echotimestamp " ========================================================================="
	echotimestamp " Create log directory"
	echotimestamp " ========================================================================="
	(set -x; \
	 mkdir -p ${LOGDIR})
fi

if [ ${debug} -eq 1 ]; then
	echo "\n"
	echotimestamp " ========================================================================="
	echotimestamp " Makefile variables"
	echotimestamp " ========================================================================="
	(set -x; \
	 make debug LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} SANITIZER=${SANITIZER} COVERAGE=${COVERAGE} PROFILER=${PROFILER} PROFEXTRAOPTS=${PROFEXTRAOPTS} COVEXTRAOPTS=${COVEXTRAOPTS} 1> ${LOGDIR}/${DEBUGLOG} 2> ${LOGDIR}/${DEBUGERR})
fi

compile_binary app

if [ ${cleanbyproduct} -eq 1 ]; then
	echo "\n"
	echotimestamp " ========================================================================="
	echotimestamp " Clean by-product"
	echotimestamp " ========================================================================="
	(set -x; \
	 make clean_byproducts LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR})
fi

if [ ${tests} -eq 1 ]; then

	compile_binary tester

	if [ -f ./${EXEDIR}/${TESTEREXENAME} ]; then
		echotimestamp " ========================================================================="
		echotimestamp " Run program"
		echotimestamp " ========================================================================="
		echotimestamp " START: Testing with no input file"
		(set -x; \
		 ./${EXEDIR}/${TESTEREXENAME})
		echotimestamp " COMPLETED: Testing with no input file"
	else
		echotimestamp " FAILED: Compilation failed - Cannot find  ./${EXEDIR}/${TESTEREXENAME}"
	fi
fi

if [ ${coverage} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Coverage"
	echotimestamp " ========================================================================="
	echotimestamp " ${ITEMSYMBOL} Coverage logfile name: ${COVERAGELOG}"
	echotimestamp " ${ITEMSYMBOL} Coverage error file name: ${COVERAGEERR}"
	(set -x; \
	 make coverage COVEXTRAOPTS=${COVEXTRAOPTS} 1> ${LOGDIR}/${COVERAGELOG} 2> ${LOGDIR}/${COVERAGEERR})
fi

if [ ${profiler} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Profiling"
	echotimestamp " ========================================================================="
	echotimestamp " ${ITEMSYMBOL} Profiling logfile name: ${PROFILERLOG}"
	echotimestamp " ${ITEMSYMBOL} Profiling error file name: ${PROFILERERR}"
	(set -x; \
	 make profiling EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} PROFEXTRAOPTS=${PROFEXTRAOPTS} 1> ${LOGDIR}/${PROFILERLOG} 2> ${LOGDIR}/${PROFILERERR})
	exit 0
fi

if [ ${doc} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Compile documetation"
	echotimestamp " ========================================================================="
	(set -x; \
	 make doc LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} 1> ${LOGDIR}/${DOCLOG} 2> ${LOGDIR}/${DOCERR})
fi

if [ ${memleak} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Check memory leaks"
	echotimestamp " ========================================================================="
	echotimestamp " START: Valgrind with no input file"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} VALGRINDLOGFILENAME=${VALGRINDNOINPUTLOG} VALGRINDEXEARGS="")
	echotimestamp " COMPLETED: Valgrind with no input file"
fi
