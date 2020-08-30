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
clean=0
cleanbyproduct=0
debug=0
doc=0
qtbasedir=

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

echotimestamp () {
	# set +x do not print commands as they are executed
	(set +x; \
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]  - $1")
}

usage () {
	echotimestamp "  - Usage:"
	echotimestamp "  - >$0 <options>"
	echotimestamp ""
	echotimestamp "       --clean|-c:		delete generated files before start compilation"
	echotimestamp "       --cleanbyproduct|-cbp:	delete generated files during compilation"
	echotimestamp "       --doc|-d:			generate documentation"
	echotimestamp "       --debug|-g:		dump makefile flags to ${LOGDIR}/${DEBUGLOG}"
	echotimestamp "       --compile|-co:		compile only"
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

if [ $# -lt 1 ]; then
	usage
	exit 0
fi

for args
do
	case "$1" in
		--compile|-co)
			compile=1
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
			clean=1
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
			exit 0
			;;
	esac
done

# Settings QT libraries path
if ! [ -z "${qtbasedir}" ]; then
	if [ "${qtbasedir}" = "system" ]; then
		QTBASEDIR=
	elif [ -d ${qtbasedir} ]; then
		QTBASEDIR=${qtbasedir}
	fi
fi

if ! [ -z "${QTBASEDIR}" ] && [ -d ${QTBASEDIR} ]; then
	if [ -d ${QTBASEDIR}/lib ]; then
		export QTLIBDIR=${QTBASEDIR}/lib
	fi
	if [ -d ${QTBASEDIR}/include ]; then
		export QTINCLUDEDIR=${QTBASEDIR}/include
	fi
	if [ -d ${QTBASEDIR}/bin ]; then
		export QTTOOLDIR=${QTBASEDIR}/bin
	fi
fi
export PATH=${QTTOOLDIR}:${PATH}
export LD_LIBRARY_PATH=${QTLIBDIR}:${LD_LIBRARY_PATH}

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

if [ ${clean} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Clean workspace"
	echotimestamp " ========================================================================="
	(set -x; \
	 make clean LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR})
elif [ ${compile} -eq 1 ]; then
	# Delete executable in order to avoid using the previous one if compile fails and running tests
	(set -x; \
	 /bin/rm -rf ${EXEDIR}/${EXENAME})
fi

if [ ${compile} -eq 1 ] || [ ${tests} -eq 1 ] || [ ${debug} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Create log directory"
	echotimestamp " ========================================================================="
	(set -x; \
	 mkdir -p ${LOGDIR})
fi

if [ ${debug} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Makefile variables"
	echotimestamp " ========================================================================="
	(set -x; \
	 make debug LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} SANITIZER=${SANITIZER} COVERAGE=${COVERAGE} PROFILER=${PROFILER} PROFEXTRAOPTS=${PROFEXTRAOPTS} COVEXTRAOPTS=${COVEXTRAOPTS} 1> ${LOGDIR}/${DEBUGLOG} 2> ${LOGDIR}/${DEBUGERR})
fi

if [ ${compile} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Compile sources"
	echotimestamp " ========================================================================="
	(set -x; \
	 make all LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} CEXTRAFLAGS=${CEXTRAFLAGS} SANITIZER=${SANITIZER} COVERAGE=${COVERAGE} PROFILER=${PROFILER} 1> ${LOGDIR}/${COMPLOG} 2> ${LOGDIR}/${COMPERR})
	# If make returns code 2, it means it encountered errors
	retCode=$?
	if [ ${retCode} -eq 2 ]; then
		echotimestamp " FAILED: Compilation failed as Makefile return code is ${retCode}"
		exit 1
	else
		echotimestamp " SUCCEED: Compilation succeeded as Makefile return code is ${retCode}"
	fi
fi

if [ ${cleanbyproduct} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Clean by-product"
	echotimestamp " ========================================================================="
	(set -x; \
	 make clean_byprod LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} TESTER_EXE_NAME=${TESTEREXENAME} BIN_DIR=${EXEDIR})
fi

if [ ${tests} -eq 1 ]; then
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
	exit 1
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
