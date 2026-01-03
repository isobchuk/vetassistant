# Project name
TARGET	= vetassistant

# Compiler system
SYSTEM	=
CXX		?=$(SYSTEM)g++
CC		?=$(SYSTEM)gcc
AS		?=$(SYSTEM)as
OBJCOPY	?=$(SYSTEM)objcopy
SIZE	?=$(SYSTEM)size
LD		?=$(SYSTEM)ld
OBJDUMP	?=$(SYSTEM)objdump
AR		?=$(SYSTEM)ar

# Defines for the different configurations (others can be added)
DEFINES =
DEFINES_DEBUG =
DEFINES_RELEASE = -DNDEBUG

# Flags for different configurations (others can be added)
CONFIGURATION ?= debug
ifeq ($(CONFIGURATION), release)
DEFINES 		+= $(DEFINES_RELEASE)
OPTIMIZE		=-Os
else
DEFINES 		+= $(DEFINES_DEBUG)
OPTIMIZE		=-Og -g
endif

# Folders with results
RESULT_FOLDER_NAME 		= output
BIN_FOLDER_NAME		   	= bin
LIB_FOLDER_NAME			= lib
OBJ_FOLDER_NAME			= obj


# Warnings configuration
WARNINGS		= -Wall -Werror -Wextra -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wshadow=compatible-local -Wcast-qual -Wconversion -Wsign-conversion -Wlogical-op
WARNINGS_CPP 	= -Wctor-dtor-privacy -Woverloaded-virtual -Wsign-promo -Wzero-as-null-pointer-constant -Wextra-semi -Wnon-virtual-dtor

DIRS := src
GLOBAL_INCLUDE := $(CURDIR)/src
ISO			   := $(CURDIR)

# QT stuff
QT_CFLAGS := $(shell pkg-config --cflags Qt5Core Qt5Gui Qt5Qml Qt5Quick Qt5QmlModels Qt5Network)
QT_LIBS   := $(shell pkg-config --libs Qt5Core Qt5Gui Qt5Qml Qt5Quick Qt5QmlModels Qt5Network)

# Sqlite3 libs
SQLITE3_LIBS := $(shell pkg-config --libs sqlite3)

# Compilation flags and linker script
FLAGS		= $(OPTIMIZE) $(DEFINES) -I$(GLOBAL_INCLUDE) -I$(ISO)
CFLAGS		=
CXXFLAGS 	= -std=c++20 -fconcepts-diagnostics-depth=5
LDFLAGS		?=
LIBS		= $(QT_LIBS) $(SQLITE3_LIBS)

export RESULT_FOLDER_NAME CONFIGURATION BIN_FOLDER_NAME LIB_FOLDER_NAME OBJ_FOLDER_NAME WARNINGS WARNINGS_CPP FLAGS CFLAGS CXXFLAGS LDFLAGS LIBS INCLUDES QT_CFLAGS

LIB_ROOT = $(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(LIB_FOLDER_NAME)
SUBLIBS  = $(shell find $(LIB_ROOT) -name '*.a' -type f)

include $(ROOT)log.mk


.PHONY: all clean $(DIRS)

all:  $(DIRS) $(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME) $(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME)/$(TARGET)
	@$(LOG_SIZE)
	$(SIZE) $(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME)/$(TARGET)

$(DIRS):
	$(MAKE) -C $@ ROOT=../ PRE_DIR= $(MAKECMDGOALS)

$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME)/$(TARGET): $(DIRS) $(SUBLIBS)
	@$(LOG_LD)
	$(CXX) -Wl,$(OPTIMIZE) -Wl,--start-group $(SUBLIBS) -Wl,--end-group $(LDFLAGS) $(LIBS) -o $(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME)/$(TARGET)


$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME) :
	$(shell mkdir -p $(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME) )

clean: $(DIRS)
	$(shell rm -rf $(RESULT_FOLDER_NAME))