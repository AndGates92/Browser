# Makefile for machine learning C implementation

DATE_FORMAT = %a %d %b %Y
TIME_FORMAT = %H:%M:%S

TIMESTAMP = ${shell date "+${DATE_FORMAT} ${TIME_FORMAT}"}

# Makefile variables
VERBOSE =
VERBOSE_ECHO = @

MKDIR = mkdir -p

# Project name
PROJ_NAME ?= browser

# Executable filename
EXE_NAME ?= $(PROJ_NAME)

# Dependency directory
DEP_DIR ?= dep

# Dependency filename
DEPFILENAME ?= Makefile.deps

# Log directory
LOG_DIR ?= log

# Log filename
LOGFILENAME ?= $(EXE_NAME).log

# Log file
LOGFILE=$(LOG_DIR)/$(LOGFILENAME)

VERBOSITY ?= 1

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

DEP_EXT = dep
OBJ_EXT = o
HEADER_EXT = h

# Meta-Object compiler handler Qt C++ language extension
MOC_SRC_EXT = moc.cpp
MOC_OBJ_EXT = moc.o

# Compile-time flags
# Upgrade all warnings to errors
# PIC (Position Independent Code) is required by Qt
# C++14 standard
# -rdyanmic: ELF linked adds all symbols to the dynamic symbol table
CFLAGS = -g -Wnon-virtual-dtor -Wall -Wconversion -fPIC -Werror -Wextra -Wpedantic -std=c++17 -rdynamic -Og
ASANFLAGS = -fsanitize-address-use-after-scope -fsanitize=leak -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer
CEXTRAFLAGS ?=
BEHFLAGS ?=
# -MP workaround for make errors when an header file is removed (Add phony target for each dependency other the main file)
# -MMD Dependency file listing only header files
# -MF specifies the dependency file
DEPENDFLAG = -MT $@ -MP -MMD -MF $(DEPFILE)
DEPFILE = $(patsubst %.$(OBJ_EXT),$(DEP_DIR)/%.$(DEP_EXT),$(notdir $@))

# Defines
LOG_DEFINES = LOGFILE="$(LOGFILE)" VERBOSITY=$(VERBOSITY)
DEFINE_LIST = $(LOG_DEFINES)
DFLAGS := $(foreach DEF, ${DEFINE_LIST}, -D${DEF})

# Libraries
MATHLIBS= m
GLUTLIBS = GLU GL glut
QTLIBS = Qt5Widgets Qt5Gui Qt5Core Qt5WebEngineCore Qt5WebEngineWidgets
X11LIBS = X11
LIB_LIST = $(MATHLIBS) \
           $(GLUTLIBS) \
           $(QTLIBS)   \
           $(X11LIBS)
LIBS := $(foreach LIB, ${LIB_LIST}, -l${LIB})

# Directory containing source and header files
APP_DIR = app
TEST_DIR =
CLASSCOMPONENT_DIR = $(sort $(dir $(wildcard $(APP_DIR)/*/)))
COMPONENT_DIR = $(sort $(dir $(wildcard $(APP_DIR)/*/*/)))
SUBCOMPONENT_DIR = $(sort $(dir $(wildcard $(APP_DIR)/*/*/*/)))

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
           $(SUBCOMPONENT_DIR) \
           $(TEST_DIR)

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
SRCS := $(notdir $(wildcard $(foreach DIR, ${SRC_PATH}, $(DIR)/*.$(SRC_EXT))))
HEADERS := $(notdir $(wildcard $(foreach DIR, ${INCLUDE_PATH}, $(DIR)/*.$(HEADER_EXT))))
MOC_SRCS = $(patsubst %.$(HEADER_EXT),$(MOC_SRC_DIR)/%.$(MOC_SRC_EXT),$(notdir $(HEADERS)))
OBJS = $(patsubst %.$(SRC_EXT),$(OBJ_DIR)/%.$(OBJ_EXT),$(notdir $(SRCS)))
MOC_OBJS = $(patsubst %.$(HEADER_EXT),$(MOC_OBJ_DIR)/%.$(MOC_OBJ_EXT),$(notdir $(HEADERS)))
DEPS := $(patsubst %.$(OBJ_EXT),$(DEP_DIR)/%.$(DEP_EXT),$(notdir $(OBJS)))

VPATH = $(SRC_PATH) \
        $(INCLUDE_PATH)

MAIN = main.$(SRC_EXT)
EXE = $(BIN_DIR)/$(EXE_NAME)

-include $(wildcard $(DEPS))

$(EXE) : $(MOC_OBJS) $(OBJS)
	$(MKDIR) $(LOG_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(@F). Object files are: $^"
	$(CC) $(CFLAGS) $(ASANFLAGS) $(INCLUDES) -o $@ $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) $^ $(LIB_DIR) $(LIBS)

$(OBJ_DIR)/%.$(OBJ_EXT) : %.$(SRC_EXT)
	$(MKDIR) $(DEP_DIR)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(<F) and creating object $@ - dependency file is $(DEPFILE)"
	$(CC) $(DEPENDFLAG) $(CFLAGS) $(ASANFLAGS) $(INCLUDES) -c $< $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) -o $@ $(LIBS)

$(MOC_SRC_DIR)/%.$(MOC_SRC_EXT) : %.$(HEADER_EXT)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(<F) and creating moc source $@"
	$(MOC) $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) $(INCLUDE_HEADERS) $< -o $@

$(MOC_OBJ_DIR)/%.$(MOC_OBJ_EXT) : $(MOC_SRC_DIR)/%.$(MOC_SRC_EXT)
	$(MKDIR) $(@D)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiling $(<F) and creating moc object $@"
	$(CC) $(CFLAGS) $(ASANFLAGS) $(INCLUDES) -c $< $(DFLAGS) $(BEHFLAGS) $(CEXTRAFLAGS) -o $@ $(LIBS)

# Work around to force generating the file
$(DEPS) :

all : $(EXE)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compile $(PROJ_NAME)"

memleak : $(EXE)
	valgrind $(MEMCHECKOPTS) $(VALGRINDTOOLOPTS) $(VALGRINDLOGOPTS) $(EXE) $(VALGRINDEXEARGS)

debug :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Language: $(PROG_LANG)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiler: $(CC)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Compiler options:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> $(PROG_LANG) flags: $(CFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> $(PROG_LANG) extra flags: $(CEXTRAFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> ASAN flags: $(ASANFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Behaviour flags: $(BEHFLAGS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> logging defines: $(LOG_DEFINES)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Math libs: $(MATHLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> OpenGL GLUT libraries: $(GLUTLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> X11 libraries: $(X11LIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Qt libraries: $(QTLIBS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Files lists:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Source files: $(SRCS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Header files: $(HEADERS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Dependency files: $(DEPS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> moc source files: $(notdir $(MOC_SRCS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Object files: $(notdir $(OBJS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> moc object files: $(notdir $(MOC_OBJS))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Executable file: $(notdir $(EXE_NAME))"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Directories lists:"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Source directories: $(SRC_PATH)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> moc source directories: $(MOC_SRC_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Include directories: $(INCLUDE_PATH)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Include Qt library path: $(QT_HEADERS)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Extra libraries: $(LIB_DIR_PATH)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Exeutable directory: $(BIN_DIR)"
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] --> Log directory: $(LOG_DIR)"

clean_byprod :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove object files: $(OBJS)"
	rm -rf $(OBJ_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove moc object files: $(MOC_OBJS)"
	rm -rf $(MOC_OBJ_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove moc source files: $(MOC_SRCS)"
	rm -rf $(MOC_SRC_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove dependencies directory: $(DEP_DIR)"
	rm -rf $(DEP_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove doxygen documentation directory: $(DOX_DOC_DIR)"
	rm -rf $(DOX_DOC_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Clean by-product completed"

clean_prog :
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove binary directory: $(BIN_DIR)"
	rm -rf $(BIN_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Remove log directory: $(LOG_DIR)"
	rm -rf $(LOG_DIR)
	$(VERBOSE_ECHO)echo "[${TIMESTAMP}] Clean program completed"

clean :
	make clean_prog
	make clean_byprod

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

# phony target to avoid conflicts with a possible file with the same name
.PHONY: all,clean,depend,$(EXE),debug,doc,memleak

# Prevent intermediate files from being deleted
.SECONDARY: $(MOC_SRCS) $(MOC_OBJS) $(OBJS)
