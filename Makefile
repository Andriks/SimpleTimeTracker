# created by ashcherba

CXX = g++
CPP_FLAGS += -g -O0 -pthread -std=c++11 -fPIC
CPP_FLAGS += -fpermissive
# CPP_FLAGS += -Wall
LIBS = -lX11 -lQt5Core -lQt5Xml -lQt5XmlPatterns

OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src/sources
CONFIGMANAGER_DIR = src/configmanager

INC_PATH = \
	-I/usr/include/qt5 \
	-I/usr/include/qt5/QtCore \
	-I/usr/include/qt5/QtXml \
	-I/usr/include/qt5/QtXmlPatterns \
	-Isrc/configmanager \
	-Isrc/headers \
	-I$(SRC_DIR) \
	$(NULL)

SRC_CPP = \
	main.cpp \
	deamoncreator.cpp \
	appchangeeventdriver.cpp \
	signalhandler.cpp \
	database.cpp \
	reporter.cpp \
	$(NULL)

SRC_CPP_CONFIGMANAGER = \
	configmanager.cpp \
	$(NULL)

OBJ += $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_CPP))
OBJ_CONFIGMANAGER += $(patsubst %.cpp, $(OBJ_DIR)/configmanager/%.o, $(SRC_CPP_CONFIGMANAGER))

.PHONY: mkdir run

all: build

build: mkdir STT

run: build
	$(BIN_DIR)/STT

mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/configmanager
	@mkdir -p $(BIN_DIR)

clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)

STT: $(OBJ) $(OBJ_CONFIGMANAGER)
	$(CXX) $(CPP_FLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@

$(OBJ_DIR)/configmanager/%.o: $(CONFIGMANAGER_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@
