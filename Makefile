# Makefile for browser C implementation

DATE_FORMAT = %a %d %b %Y
TIME_FORMAT = %H:%M:%S

TIMESTAMP = ${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}

# Makefile variables
VERBOSE =
VERBOSE_ECHO = @
COMPILE_TYPE ?= Debug
COMPILE_TYPE_VALID_VALUES = Release Debug Compare

ifneq ($(COMPILE_TYPE), $(filter $(COMPILE_TYPE), $(COMPILE_TYPE_VALID_VALUES)))
  $(error Compile type $(COMPILE_TYPE) is not valid. Valid values are $(COMPILE_TYPE_VALID_VALUES))
endif

# Shell commands
RM = rm -rf
MKDIR = mkdir -p
MV = mv

# tester suffix
TESTER_SUFFIX = _tester

# Project name
PROJ_NAME ?= browser

# Executable filename
EXE_NAME ?= $(PROJ_NAME)
TESTER_EXE_NAME ?= $(PROJ_NAME)$(TESTER_SUFFIX)

# Dependency directory
DEP_DIR ?= dep

# Dependency filename
DEPFILENAME ?= Makefile.deps

# file name without extension that contain the main method
APP_MAIN = main
TESTER_MAIN = tester

# Log directory
LOG_DIR ?= log

# Log filename
LOGFILENAME ?= $(EXE_NAME).log

PROFILERLOGFILENAME ?= analyze.gmon.log

# Log file
LOGFILE=$(LOG_DIR)/$(LOGFILENAME)

# Coverage directory
COVERAGE_DIR ?= coverage

# Profile directory
PROFILE_DIR ?= profile

VERBOSITY ?= 1

SANITIZER ?= 0
COVERAGE ?= 0
PROFILER ?= 0

# Program Language
PROG_LANG ?= C++

# File extensions
ifeq ($(PROG_LANG), C++)
  SRC_EXT = cpp
  # - g++ for C++ files
  CC = g++
else ifeq ($(PROG_LANG), C)
  SRC_EXT = c
  # - gcc for C files
  CC = gcc
endif

MOC = moc

COV = gcov

PROFILER = gprof

DEP_EXT = dep
OBJ_EXT = o
HEADER_EXT = h

# Meta-Object compiler handler Qt C++ language extension
MOC_SRC_EXT = moc.cpp
MOC_OBJ_EXT = moc.o

ANNSRC_EXT = -ann

COV_FILES = gcov

# Compile-time flags
# Upgrade all warnings to errors
# PIC (Position Independent Code) is required by Qt
# C++14 standard
# -rdyanmic: ELF linked adds all symbols to the dynamic symbol table
CFLAGS = -Wnon-virtual-dtor -Wall -Wconversion -fPIC -Werror -Wextra -Wpedantic -std=c++17 -rdynamic
CDEBUGFLAGS += -Og -g3
ifeq ($(COMPILE_TYPE), Debug)
  CFLAGS += $(CDEBUGFLAGS)
else
  ifeq ($(COMPILE_TYPE), Release)
    CFLAGS += -O3
  else
    ifeq ($(COMPILE_TYPE), Compare)
      export GCC_COMPARE_DEBUG = "$(CDEBUGFLAGS) -fcompare-debug-not-overriden"
    endif
  endif
endif

ifeq ($(SANITIZER), 1)
  ASANFLAGS = -fsanitize-address-use-after-scope -fsanitize=leak -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer
else
  ASANFLAGS =
endif

ifeq ($(COVERAGE), 1)
  COVFLAGS = -ftest-coverage -fprofile-arcs -fprofile-abs-path
  COVLIBS = gcov
else
  COVFLAGS =
  COVLIBS =
endif

ifeq ($(PROFILER), 1)
  PROFILERFLAGS = -pg
else
  PROFILERFLAGS =
endif

ifeq ($(APP_MAIN), $(TESTER_MAIN))
  $(warning application top level filename $(APP_MAIN) is the same as tester top level filename $(TESTER_MAIN))
endif

TESTFLAGS ?=
CEXTRAFLAGS ?=
BEHFLAGS ?=
# -MP workaround for make errors when an header file is removed (Add phony target for each dependency other the main file)
# -MMD Dependency file listing only header files
# -MF specifies the dependency file
DEPENDFLAG = -MT $@ -MP -MMD -MF $(DEPFILE)
DEPFILE = $(patsubst %.$(OBJ_EXT),$(DEP_DIR)/%.$(DEP_EXT),$(notdir $@))

# Defines
QTTESTER_DEFINES = QT_TESTLIB_LIB QT_WIDGETS_LIB QT_GUI_LIB
LOG_DEFINES = LOGFILE="$(LOGFILE)" VERBOSITY=$(VERBOSITY)
DEFINE_LIST = $(LOG_DEFINES) \
              $(QTTESTER_DEFINES)
DFLAGS := $(foreach DEF, ${DEFINE_LIST}, -D${DEF})

# Libraries
THREADLIBS= pthread
MATHLIBS= m
GLUTLIBS = GLU GL glut
QTLIBS = Qt5Widgets Qt5Gui Qt5Core Qt5WebEngineCore Qt5WebEngineWidgets
QTTESTLIBS = Qt5Test
X11LIBS = X11
LIB_LIST = $(MATHLIBS)   \
           $(THREADLIBS) \
           $(GLUTLIBS)   \
           $(QTLIBS)     \
           $(QTTESTLIBS) \
           $(X11LIBS)    \
           $(COVLIBS)
LIBS := $(foreach LIB, ${LIB_LIST}, -l${LIB})

# Directory containing source and header files
APP_DIR = app
TESTER_DIR = tester

ROOT_DIR = ${APP_DIR} \
           ${TESTER_DIR}

CLASSCOMPONENT_DIR = $(foreach DIR, ${ROOT_DIR}, $(sort $(dir $(wildcard $(DIR)/*/))))
COMPONENT_DIR = $(foreach DIR, ${CLASSCOMPONENT_DIR}, $(sort $(dir $(wildcard $(DIR)*/))))
SUBCOMPONENT_DIR = $(foreach DIR, ${COMPONENT_DIR}, $(sort $(dir $(wildcard $(DIR)*/))))

# Directory containing top level
MAIN_DIR = top

# Directory containing source files
SRC_DIR = src

# Directory containing moc source files
MOC_SRC_DIR = moc_src

# Directory containing include files
INCLUDE_DIR = include

# Directory containing object files
OBJ_DIR = obj

# Directory containing moc object files
MOC_OBJ_DIR = moc_obj

# Directory containing binary files
BIN_DIR ?= bin

# Doxygen variables
DOXYGEN = doxygen
DOX_DIR = doxygen
DOX_CFG_FILENAME = ${PROJ_NAME}.config

DOX_CFG_FILE = $(DOX_DIR)/$(DOX_CFG_FILENAME)

DOX_DOC_DIR = doc

DOX_COMMENT_SECTION = \#\#\#\#\#\#\#\#\#\#\#\#\#\#\#
DOX_INPUT_FILE_HEADER = \#\# Input files

# Valgrind variables
VALGRIND=valgrind

MEMCHECKOPTS = --tool=memcheck --leak-check=full --error-limit=no --show-leak-kinds=all --track-origins=yes
VALGRINDTOOLOPTS =
VALGRINDLOGFILENAME ?= valgrind.log
VALGRINDLOGFILE = $(LOG_DIR)/$(VALGRINDLOGFILENAME)
VALGRINDLOGOPTS = -v --log-file=$(VALGRINDLOGFILE) --time-stamp=yes
VALGRINDEXEARGS ?=

DIR_LIST = $(CLASSCOMPONENT_DIR) \
           $(COMPONENT_DIR) \
           $(SUBCOMPONENT_DIR)

INCLUDE_PATH := $(foreach DIR, ${DIR_LIST}, $(DIR)$(INCLUDE_DIR))
INCLUDE_HEADERS := $(foreach INCHEADER, ${INCLUDE_PATH}, -I${INCHEADER})

ifneq ($(QTLIBDIR),)
  QT_LIB_DIR = $(QTLIBDIR)
endif

LIB_DIR_PATH = $(QT_LIB_DIR)

ifneq ($(LIB_DIR_PATH),)
  LIB_DIR := $(foreach LIBDIR, ${LIB_DIR_PATH}, -L${LIBDIR})
endif

ifneq ($(QTINCLUDEDIR),)
  QT_HEADERS = $(QTINCLUDEDIR)
else
  ifneq ($(wildcard /usr/include/x86_64-linux-gnu/qt5),)
    QT_HEADERS = /usr/include/x86_64-linux-gnu/qt5
  else
    $(error Qt libraries not found - QTINCLUDEDIR is not defined)
  endif
endif
INCLUDE_PATH_LIBS = $(QT_HEADERS)

ifneq ($(INCLUDE_PATH_LIBS),)
  INCLUDE_LIBS := $(foreach INCLIB, ${INCLUDE_PATH_LIBS}, -isystem${INCLIB})
endif

INCLUDES = $(INCLUDE_HEADERS) \
           $(INCLUDE_LIBS)

SRC_PATH := $(foreach DIR, ${DIR_LIST}, $(DIR)$(SRC_DIR))
SRCS := $(wildcard $(foreach DIR, ${SRC_PATH}, $(DIR)/*.$(SRC_EXT)))
HEADERS := $(wildcard $(foreach DIR, ${INCLUDE_PATH}, $(DIR)/*.$(HEADER_EXT)))
MOC_SRCS = $(patsubst %.$(HEADER_EXT),$(MOC_SRC_DIR)/%.$(MOC_SRC_EXT),$(notdir $(HEADERS)))
OBJS = $(patsubst %.$(SRC_EXT),$(OBJ_DIR)/%.$(OBJ_EXT),$(notdir $(SRCS)))
MOC_OBJS = $(patsubst %.$(HEADER_EXT),$(MOC_OBJ_DIR)/%.$(MOC_OBJ_EXT),$(notdir $(HEADERS)))
DEPS := $(patsubst %.$(OBJ_EXT),$(DEP_DIR)/%.$(DEP_EXT),$(notdir $(OBJS)))

VPATH = $(SRC_PATH) \
        $(INCLUDE_PATH)

# Object directoy and files
OBJS_DIR = $(MOC_OBJ_DIR) \
           $(OBJ_DIR)

OBJS_LIST = $(MOC_OBJS) \
            $(OBJS)

APP_MAIN_OBJ = $(OBJ_DIR)/$(APP_MAIN).$(OBJ_EXT) \
               $(MOC_OBJ_DIR)/$(APP_MAIN).$(MOC_OBJ_EXT)

TESTER_MAIN_OBJ = $(OBJ_DIR)/$(TESTER_MAIN).$(OBJ_EXT) \
                  $(MOC_OBJ_DIR)/$(TESTER_MAIN).$(MOC_OBJ_EXT)

MAIN_OBJS = $(APP_MAIN_OBJ) \
            $(TESTER_MAIN_OBJ)

# Leave only one top level
# Filter out top level files from the main objects and then filter out the outcome from the full list of objects
APP_UNNEEDED_OBJ = $(filter-out $(APP_MAIN_OBJ), $(MAIN_OBJS)) $(filter $(TESTER_DIR), $(OBJS_LIST))
APP_OBJS = $(filter-out $(APP_UNNEEDED_OBJ), $(OBJS_LIST))
TESTER_OBJS = $(filter-out $(filter-out $(TESTER_MAIN_OBJ), $(MAIN_OBJS)), $(OBJS_LIST))

COVSEARCHDIR := $(foreach DIR, ${OBJS_DIR}, --object-directory ${DIR})
COVOPTS = --all-blocks --branch-probabilities --function-summaries --demangled-names --unconditional-branches
COVEXTRAOPTS ?=

# Profiler
OUTPROFOPTS = --annotated-source --exec-count --graph --separate-files
#ANALYSISPROFOPTS = --line --static-call-graph --display-unused-functions
# --line causes failure of gprof with the following error: somebody miscounted: ltab.len=X instead of Y
ANALYSISPROFOPTS = --static-call-graph --display-unused-functions
MISCPROFOPTS =
PROFEXTRAOPTS ?=

APP_EXE = $(BIN_DIR)/$(EXE_NAME)
TESTER_EXE = $(BIN_DIR)/$(TESTER_EXE_NAME)
PROFILE_DATA = gmon.out

-include $(wildcard $(DEPS))

$(TESTER_EXE) : $(TESTER_OBJS)
	$(MKDIR) $(LOG_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Linking $(@F). Object files are: $^"
	$(CC) $(ASANFLAGS) $(PROFILERFLAGS) -o $@ $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) $^ $(LIB_DIR) $(LIBS)

$(APP_EXE) : $(APP_OBJS)
	$(MKDIR) $(LOG_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Linking $(@F). Object files are: $^"
	$(CC) $(ASANFLAGS) $(PROFILERFLAGS) -o $@ $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) $^ $(LIB_DIR) $(LIBS)

$(OBJ_DIR)/%.$(OBJ_EXT) : %.$(SRC_EXT)
	$(MKDIR) $(DEP_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(<F) and creating object $@ - dependency file is $(DEPFILE)"
	$(CC) $(DEPENDFLAG) $(CFLAGS) $(ASANFLAGS) $(COVFLAGS) $(PROFILERFLAGS) $(INCLUDES) -c $< $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) -o $@ $(LIBS)

$(MOC_SRC_DIR)/%.$(MOC_SRC_EXT) : %.$(HEADER_EXT)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(<F) and creating moc source $@"
	$(MOC) $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) $(INCLUDE_HEADERS) $< -o $@

$(MOC_OBJ_DIR)/%.$(MOC_OBJ_EXT) : $(MOC_SRC_DIR)/%.$(MOC_SRC_EXT)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(<F) and creating moc object $@"
	$(CC) $(CFLAGS) $(ASANFLAGS) $(COVFLAGS) $(PROFILERFLAGS) $(INCLUDES) -c $< $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) -o $@ $(LIBS)

# Work around to force generating the file
$(DEPS) :

app : $(APP_EXE)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compile $(APP_EXE)"

tester : $(TESTER_EXE)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compile $(TESTER_EXE)"

all : $(APP_EXE) $(TESTER_EXE)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compile application and tester for $(PROJ_NAME)"

memleak : $(APP_EXE)
	valgrind $(MEMCHECKOPTS) $(VALGRINDTOOLOPTS) $(VALGRINDLOGOPTS) $(APP_EXE) $(VALGRINDEXEARGS)

debug :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Language: $(PROG_LANG)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiler: $(CC)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Coverage tool: $(COV)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Profiler tool: $(PROFILER)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Executables:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> application: $(APP_EXE)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> tester: $(TESTER_EXE)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiler options:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> $(PROG_LANG) flags: $(CFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> $(PROG_LANG) extra flags: $(CEXTRAFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> ASAN flags: $(ASANFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Coverage compile flags: $(COVFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Profiler flags: $(PROFILERFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Behaviour flags: $(BEHFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> logging defines: $(LOG_DEFINES)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> tester defines: $(QTTESTER_DEFINES)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Math libs: $(MATHLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> OpenGL GLUT libraries: $(GLUTLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> X11 libraries: $(X11LIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Qt libraries: $(QTLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Coverage libraries: $(COVLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> tester libraries: $(QTTESTLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiler options:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Coverage options: $(GCOVOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Coverage extra options: $(COVEXTRAOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Profiler options: $(PROFOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Profiler extra options: $(PROFEXTRAOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Files lists:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Source files: $(notdir $(SRCS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Header files: $(notdir $(HEADERS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Dependency files: $(DEPS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> moc source files: $(notdir $(MOC_SRCS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Object files: $(notdir $(OBJS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> moc object files: $(notdir $(MOC_OBJS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Executable file: $(notdir $(EXE_NAME))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Directories lists:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Application directory: $(APP_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Tester directory: $(TESTER_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Source directories: $(SRC_PATH)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> moc source directories: $(MOC_SRC_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Include directories: $(INCLUDE_PATH)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Include Qt library path: $(QT_HEADERS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Extra libraries: $(LIB_DIR_PATH)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Exeutable directory: $(BIN_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Log directory: $(LOG_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Coverage directory: $(COVERAGE_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Profiling directory: $(PROFILE_DIR)"

clean_byproducts :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove object files: $(OBJS)"
	rm -rf $(OBJ_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove moc object files: $(MOC_OBJS)"
	rm -rf $(MOC_OBJ_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove moc source files: $(MOC_SRCS)"
	rm -rf $(MOC_SRC_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove dependencies directory: $(DEP_DIR)"
	rm -rf $(DEP_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Clean by-product completed"

clean_logs :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove log directory: $(LOG_DIR)"
	$(RM) $(LOG_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Clean log completed"

clean_outputs :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove coverage directory: $(COVERAGE_DIR)"
	$(RM) $(COVERAGE_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove profile directory: $(PROFILE_DIR)"
	$(RM) $(PROFILE_DIR)
	$(RM) $(PROFILE_DATA)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove doxygen documentation directory: $(DOX_DOC_DIR)"
	rm -rf $(DOX_DOC_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Clean outputs completed"

clean_binaries :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove binary directory: $(BIN_DIR)"
	$(RM) $(BIN_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Clean binaries completed"

clean :
	make clean_logs
	make clean_outputs
	make clean_binaries
	make clean_byproducts

doc :
	$(MKDIR) $(DOX_DOC_DIR)
	# delete all inputs directories as well as header in doxygen configuration file
	sed -i '/INPUT/d' $(DOX_CFG_FILE)
	sed -i '/$(DOX_COMMENT_SECTION)/d' $(DOX_CFG_FILE)
	sed -i '/$(DOX_INPUT_FILE_HEADER)/d' $(DOX_CFG_FILE)
	sed -i '$d' $(DOX_CFG_FILE)
	sed -i '$d' $(DOX_CFG_FILE)
	# add inputs directories as well as header in doxygen configuration file
	echo "\n$(DOX_COMMENT_SECTION)" >> $(DOX_CFG_FILE)
	echo "$(DOX_INPUT_FILE_HEADER)" >> $(DOX_CFG_FILE)
	echo "$(DOX_COMMENT_SECTION)\n" >> $(DOX_CFG_FILE)
	echo "INPUT = " >> $(DOX_CFG_FILE);
	for dir in $(SRC_PATH) $(INCLUDE_PATH); do \
	  echo "INPUT += $$dir" >> $(DOX_CFG_FILE); \
	done
	$(DOXYGEN) $(DOX_CFG_FILE)

coverage:
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Generating coverage report with $(COV)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Coverage options $(COVOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Coverage extra options $(COVEXTRAOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Coverage search directory options $(COVSEARCHDIR)"
	$(MKDIR) $(COVERAGE_DIR)
	$(COV) $(COVOPTS) $(COVEXTRAOPTS) $(COVSEARCHDIR) $(SRCS)
	$(MV) *$(COV_FILES)* $(COVERAGE_DIR)

profiling:
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Generating profiling report with $(PROFILER)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Output profiler options $(OUTPROFOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Analysis profiler options $(ANALYSISPROFOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Miscellaneous profiler options $(MISCPROFOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Profiler extra options $(PROFEXTRAOPTS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Profiler search directory options $(PROFSEARCHDIR)"
	$(MKDIR) $(PROFILE_DIR)
	$(PROFILER) $(OUTPROFOPTS) $(INCLUDE_HEADERS) $(ANALYSISPROFOPTS) $(MISCPROFOPTS) $(PROFEXTRAOPTS) $(APP_EXE) $(PROFILE_DATA) > $(PROFILE_DIR)/$(PROFILERLOGFILENAME)
	$(MV) *$(ANNSRC_EXT) $(PROFILE_DIR)

# phony target to avoid conflicts with a possible file with the same name
.PHONY: all,clean,clean_logs,clean_outputs,clean_byproducts,clean_binaries,,depend,$(TESTER_EXE),$(APP_EXE),debug,doc,memleak,coverage,profiling

# Prevent intermediate files from being deleted
.SECONDARY: $(MOC_SRCS) $(MOC_OBJS) $(OBJS)
