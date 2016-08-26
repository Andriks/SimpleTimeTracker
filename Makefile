

CXX = g++
CPP_FLAGS += -g -O0 -Wall -pthread -std=c++11
LD_FLAGS = 

AR = ar
ARFLAGS = -rv

CUR_DIR = .
OBJ_DIR = $(CUR_DIR)/obj
HEADER_DIR = $(CUR_DIR)/include
SRC_DIR = $(CUR_DIR)/src

INC_PATH = \
	-I. \
	-I$(HEADER_DIR) \
	-I$(SRC_DIR) \
	$(NULL)

SRC_CPP = \
	AppChangeEventDriver.cpp \
	main.cpp \
	$(NULL)

OBJ += $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_CPP))

.PHONY: mkdir clean build

all: mkdir appCEDRunner

build: mkdir $(OBJ)

mkdir:
	@mkdir -p $(OBJ_DIR)

clean: 
	rm -rf $(OBJ_DIR) appCEDRunner

# appCEDRunner: $(OBJ) $(OBJ_DIR)/main.o
# 	$(CXX) $< -o $@

# $(OBJ_DIR)/main.o: $(CUR_DIR)/main.cpp
# 	$(CXX) -c $(INC_PATH) $(CUR_DIR)/main.cpp -o $@

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
# 	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@

appCEDRunner: $(OBJ)
	$(CXX) $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@
