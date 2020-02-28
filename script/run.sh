#!/bin/sh

# set -x shows commands as they are executed
# In this script, echo commands will not be printed

# Shell script settings
memleak=0
compile=0
tests=0
clean=0
cleanbyproduct=0
debug=0
doc=0


# Make file settings
PROJNAME=browser
EXENAME=${PROJNAME}
EXEDIR=bin

LOGDIR=log
DEBUGLOG=debug.log
COMPLOG=compile_browser.log
DOCLOG=doc.log
EXELOG=${EXENAME}.log
VALGRINDNOINPUTLOG=valgrind_noinput.log
EXEVALGRINDLOG=${EXENAME}_valgrind.log

VERBOSITY=1

CEXTRAFLAGS=-DENABLE_ASSERTIONS
BEHFLAGS=

DATE_FORMAT="%a %d %b %Y"
TIME_FORMAT=%H:%M:%S

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
	echotimestamp "       --memleak|-m:		compile and check memory leaks using valgrind" 
	echotimestamp "       --test|-t:		compile and run tests"
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

if [ ${compile} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echotimestamp " Run script variables"
	echotimestamp " ========================================================================="
	echotimestamp " EXECUTABLE"
	echotimestamp " ========================================================================="
	echotimestamp " --> Directory of the executable: ${EXEDIR}"
	echotimestamp " --> Executable filename: ${EXENAME}"
	echo "\n"
fi

echotimestamp " ========================================================================="
echotimestamp " LOGS"
echotimestamp " ========================================================================="
echotimestamp " --> Logfile directory: ${LOGDIRR}"

if [ ${debug} -eq 1 ]; then
	echotimestamp " --> Debug logfile name: ${DEBUGLOG}"
fi

if [ ${compile} -eq 1 ]; then
	echotimestamp " --> Compile logfile name: ${COMPLOG}"
fi

if [ ${tests} -eq 1 ]; then
	echotimestamp " --> Executable logfile: ${EXELOG}"
fi

if [ ${doc} -eq 1 ]; then
	echotimestamp " --> Documentation logfile name: ${DOCLOG}"
fi

if [ ${memleak} -eq 1 ]; then
	echotimestamp " --> Valgrind test set logfile name: ${VALGRINDTESLOG}"
	echotimestamp " --> Valgrind test label logfile name: ${VALGRINDNOINPUTLOG}"
	echotimestamp " --> Valgrind all input files logfile name: ${VALGRINDALLLOG}"
	echotimestamp " --> Valgrind executable logfile name: ${EXEVALGRINDLOG}"
fi

echo "\n"

if [ ${clean} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Clean workspace"
	echotimestamp " ========================================================================="
	(set -x; \
	 make clean LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR})
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
	 make debug LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DEBUGLOG})
fi

if [ ${compile} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Compile sources"
	echotimestamp " ========================================================================="
	(set -x; \
	 make all LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} CEXTRAFLAGS=${CEXTRAFLAGS} 2> ${LOGDIR}/${COMPLOG})
fi

if [ ${cleanbyproduct} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Clean by-product"
	echotimestamp " ========================================================================="
	(set -x; \
	 make clean_byprod LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR})
fi

if [ ${tests} -eq 1 ]; then
	if [ -f ./${EXEDIR}/${EXENAME} ]; then
		echotimestamp " ========================================================================="
		echotimestamp " Run program"
		echotimestamp " ========================================================================="
		echotimestamp " START: Testing with no input file"
		(set -x; \
		 ./${EXEDIR}/${EXENAME})
		echotimestamp " COMPLETED: Testing with no input file"
	else
		echotimestamp " FAILED: Compilation failed"
	fi
fi

if [ ${doc} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Compile documetation"
	echotimestamp " ========================================================================="
	(set -x; \
	 make doc LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DOCLOG})
fi

if [ ${memleak} -eq 1 ]; then
	echotimestamp " ========================================================================="
	echotimestamp " Check memory leaks"
	echotimestamp " ========================================================================="
	echotimestamp " START: Valgrind with no input file"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} VALGRINDLOGFILENAME=${VALGRINDNOINPUTLOG} VALGRINDEXEARGS="")
	echotimestamp " COMPLETED: Valgrind with no input file"
fi
