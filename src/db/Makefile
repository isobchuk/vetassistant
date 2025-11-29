include $(ROOT)build/log.mk

DIR 		:= $(notdir $(CURDIR))
FULL_DIR	:= $(PRE_DIR)/$(DIR)

OBJ_FOLDER 	:= $(ROOT)$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(OBJ_FOLDER_NAME)$(FULL_DIR)
LIB_FOLDER 	:= $(ROOT)$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(LIB_FOLDER_NAME)$(FULL_DIR)
BIN_FOLDER 	:= $(ROOT)$(RESULT_FOLDER_NAME)/$(CONFIGURATION)/$(BIN_FOLDER_NAME)$(FULL_DIR)

TARGET  	:= $(LIB_FOLDER)/lib$(DIR).a

DIRS 		:= $(filter-out .,$(wildcard */))
INCLUDES 	:= $(notdir $(wildcard ./*.hpp))
SOURCES 	:= $(notdir $(wildcard ./*.cpp) $(wildcard ./*.c))
OBJECTS 	:= $(SOURCES:.cpp=.o)
OBJECTS 	:= $(addprefix $(OBJ_FOLDER)/, $(OBJECTS:.c=.o))


.PHONY: all clean $(DIRS)

all: $(DIRS) $(OBJ_FOLDER) $(LIB_FOLDER) $(TARGET)

$(TARGET): $(OBJECTS)
	@$(LOG_AR)
	$(AR) rcs $@ $^
	@echo $(wildcard $(OBJECTS:.o=.d))
	
$(DIRS):
	$(MAKE) -C $@ ROOT=../$(ROOT) PRE_DIR=$(FULL_DIR)  $(MAKECMDGOALS)

$(OBJ_FOLDER)/%.o: %.cpp
	@$(LOG_CXX)
	$(CXX) $(FLAGS) $(CXXFLAGS) $(WARNINGS) $(WARNINGS_CPP) -MMD -c $< -o $@

$(OBJ_FOLDER)/%.o: %.c
	@$(LOG_CC)
	$(CC) $(FLAGS) $(CFLAGS) $(WARNINGS) -MMD -c $< -o $@

$(OBJ_FOLDER):
	$(shell mkdir -p $(OBJ_FOLDER))

$(LIB_FOLDER):
	$(shell mkdir -p $(LIB_FOLDER))

include $(wildcard $(OBJECTS:.o=.d))

clean: $(DIRS)
	$(shell rm -rf $(OBJ_FOLDER))
	$(shell rm -rf $(LIB_FOLDER))