#!/bin/sh

# Shell script settings
memleak=0
compile=0
tests=0
clean=0
debug=0
doc=0


# Make file settings
PROJNAME=browser
EXENAME=${PROJNAME}
EXEDIR=bin

LOGDIR=log
DEBUGLOG=debug.log
COMPNOHWLOG=compile_no_hard_wall.log
COMPHWLOG=compile_hard_wall.log
DOCLOG=doc.log
EXELOG=${EXENAME}.log
VALGRINDNOINPUTLOG=valgrind_noinput.log
EXEVALGRINDLOG=${EXENAME}_valgrind.log

VERBOSITY=1

CEXTRAFLAGS=-DENABLE_ASSERTIONS
BEHFLAGS=

DATE_FORMAT="%a %d %b %Y"
TIME_FORMAT=%H:%M:%S

usage () {
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]  - Usage:"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]  - >$0 <options>"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --clean|-c:	delete generated files"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --doc|-d:		generate documentation"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --debug|-g:	dump makefile flags to ${LOGDIR}/${DEBUGLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --compile|-co:	compile only"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --memleak|-m:	compile and check memory leaks using valgrind" 
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --test|-t:	compile and run tests"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`]       --help|-h:	print this help"
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
			compile=1
			tests=1
			shift 1
			;;
		--doc|-d)
			doc=1
			shift 1
			;;
		--memleak|-m)
			compile=1
			memleak=1
			shift 1
			;;
		--debug|-g)
			debug=1
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
			echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Illegal argument $1"
			usage
			exit 0
			;;
	esac
done

if [ ${compile} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Run script variables"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] EXECUTABLE"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Directory of the executable: ${EXEDIR}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Executable filename: ${EXENAME}"
	echo "\n"
fi

echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] LOGS"
echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Logfile directory: ${LOGDIRR}"

if [ ${debug} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Debug logfile name: ${DEBUGLOG}"
fi

if [ ${compile} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Compile logfile name hard wall: ${COMPHWLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Compile logfile name no hard wall: ${COMPNOHWLOG}"
fi

if [ ${tests} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Executable logfile name hard wall: ${EXELOG}"
fi

if [ ${doc} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Documentation logfile name: ${DOCLOG}"
fi

if [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind test set logfile name: ${VALGRINDTESLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind test label logfile name: ${VALGRINDNOINPUTLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind all input files logfile name: ${VALGRINDALLLOG}"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] --> Valgrind executable logfile name: ${EXEVALGRINDLOG}"
fi

echo "\n"

if [ ${clean} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Clean workspace"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make clean LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR})
fi

if [ ${compile} -eq 1 ] || [ ${tests} -eq 1 ] || [ ${debug} -eq 1 ] || [ ${doc} -eq 1 ] || [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Create log directory"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 mkdir -p ${LOGDIR})
fi

if [ ${debug} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Makefile variables"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make debug LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DEBUGLOG})
fi

if [ ${compile} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Compile sources"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make all LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} CEXTRAFLAGS=${CEXTRAFLAGS} 2> ${LOGDIR}/${COMPNOHWLOG})

	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Clean by-product"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make clean_byprod LOG_DIR=${LOGDIR} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR})
fi

if [ ${tests} -eq 1 ]; then
	if [ -f ./${EXEDIR}/${EXENAME} ]; then
		echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
		echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Run program"
		echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
		echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START: Testing with no input file"
		(set -x; \
		 ./${EXEDIR}/${EXENAME})
		echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED: Testing with no input file"
	else
		echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] FAILED: Compilation failed"
	fi
fi

if [ ${doc} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Compile documetation"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	(set -x; \
	 make doc LOG_DIR=${LOGDIR} LOGFILENAME=${EXELOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} CEXTRAFLAGS=${CEXTRAFLAGS} > ${LOGDIR}/${DOCLOG})
fi

if [ ${memleak} -eq 1 ]; then
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] Check memory leaks"
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] ========================================================================="
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] START: Valgrind with no input file"
	(set -x; \
	 make memleak LOG_DIR=${LOGDIR} LOGFILENAME=${EXEVALGRINDLOG} PROJ_NAME=${PROJNAME} EXE_NAME=${EXENAME} BIN_DIR=${EXEDIR} VERBOSITY=${VERBOSITY} VALGRINDLOGFILENAME=${VALGRINDNOINPUTLOG} VALGRINDEXEARGS="")
	echo "[`date "+${DATE_FORMAT} ${TIME_FORMAT}"`] COMPLETED: Valgrind with no input file"
fi
