

CXX = g++
CPP_FLAGS += -g -O0 -pthread -std=c++11 -fPIC
CPP_FLAGS += -fpermissive
# CPP_FLAGS += -Wall
LIBS = -lX11 -ltinyxml -lQtCore -lQtXml -lQtXmlPatterns

OBJ_DIR = obj
BIN_DIR = bin
HEADER_DIR = include
SRC_DIR = src

INC_PATH = \
	-I/usr/include/qt4 \
	-I/usr/include/qt4/QtCore \
	-I/usr/include/qt4/QtXml \
	-I/usr/include/qt4/QtXmlPatterns \
	-I$(HEADER_DIR) \
	-I$(SRC_DIR) \
	$(NULL)

SRC_CPP = \
	main.cpp \
	DeamonCreator.cpp \
	AppChangeEventDriver.cpp \
	SignalHandler.cpp \
	DataBase.cpp \
	TimeInfo.cpp \
	Reporter.cpp \
	stt_algorithm.cpp \
	$(NULL)

OBJ += $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_CPP))

.PHONY: mkdir run

all: build

build: mkdir simpleTimeTrackerEXE

run: build
	$(BIN_DIR)/simpleTimeTrackerEXE

mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)

simpleTimeTrackerEXE: $(OBJ)
	$(CXX) $(CPP_FLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@
