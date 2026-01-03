include $(ROOT)log.mk

DIR 		:= $(notdir $(CURDIR))
FULL_DIR	:= $(PRE_DIR)/$(DIR)

OBJ_FOLDER 	:= $(ROOT)$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(OBJ_FOLDER_NAME)$(FULL_DIR)
LIB_FOLDER 	:= $(ROOT)$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(LIB_FOLDER_NAME)$(FULL_DIR)
BIN_FOLDER 	:= $(ROOT)$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME)$(FULL_DIR)

TARGET  	:= $(LIB_FOLDER)/lib$(DIR).a

DIRS 		:= $(filter-out . qml/,$(wildcard */))
INCLUDES 	:= $(notdir $(wildcard ./*.hpp))
SOURCES 	:= $(notdir $(wildcard ./*.cpp) $(wildcard ./*.c))
OBJECTS 	:= $(SOURCES:.cpp=.o)
OBJECTS 	:= $(addprefix $(OBJ_FOLDER)/, $(OBJECTS:.c=.o))

MOC = moc
MOC_HEADERS := $(shell grep -l '\<Q_OBJECT\>' *.hpp)
MOC_SOURCES := $(addprefix $(OBJ_FOLDER)/, $(MOC_HEADERS:.hpp=.moc.cpp))
MOC_OBJS := $(MOC_SOURCES:.moc.cpp=.moc.o)

PWD := $(shell pwd)
PACKAGE		:= $(QT_CFLAGS)

WARNINGS := -Wall -Wextra -Werror
WARNINGS_CPP := 
FLAGS += -pipe -D_REENTRANT -fPIC

.PHONY: all clean $(DIRS)

all: $(DIRS) $(OBJ_FOLDER) $(LIB_FOLDER) $(TARGET)

$(TARGET): $(OBJECTS) $(MOC_OBJS)
	@$(LOG_AR)
	$(AR) rcs $@ $^
	
$(DIRS):
	$(MAKE) -C $@ ROOT=../$(ROOT) PRE_DIR=$(FULL_DIR)  $(MAKECMDGOALS)

$(OBJ_FOLDER)/%.o: %.cpp
	@echo $(MOC_OBJS)
	@$(LOG_CXX)
	$(CXX) $(FLAGS) $(CXXFLAGS) $(WARNINGS) $(WARNINGS_CPP) $(PACKAGE) -MMD -c $< -o $@

$(OBJ_FOLDER)/%.o: %.c
	@$(LOG_CC)
	$(CC) $(FLAGS) $(CFLAGS) $(WARNINGS) $(PACKAGE) -MMD -c $< -o $@

$(OBJ_FOLDER):
	$(shell mkdir -p $(OBJ_FOLDER))

$(LIB_FOLDER):
	$(shell mkdir -p $(LIB_FOLDER))

$(OBJ_FOLDER)/%.moc.cpp: %.hpp
	@$(LOG_MOC)
	$(MOC) $< -o $@

$(OBJ_FOLDER)/%.moc.o: $(OBJ_FOLDER)/%.moc.cpp
	@$(LOG_CXX)
	$(CXX) $(FLAGS) $(CXXFLAGS) $(WARNINGS) $(WARNINGS_CPP) $(PACKAGE) -MMD -c $< -o $@

include $(wildcard $(OBJECTS:.o=.d))

clean: $(DIRS)
	$(shell rm -rf $(OBJ_FOLDER))
	$(shell rm -rf $(LIB_FOLDER))