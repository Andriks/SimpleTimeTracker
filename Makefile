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
EVENT_DRIVER_DIR = src/event_driver

INC_PATH = \
	-I/usr/include/qt5 \
	-I/usr/include/qt5/QtCore \
	-I/usr/include/qt5/QtXml \
	-I/usr/include/qt5/QtXmlPatterns \
	-Isrc/headers \
	-I$(CONFIGMANAGER_DIR) \
	-I$(EVENT_DRIVER_DIR) \
	-I$(SRC_DIR) \
	$(NULL)

SRC_CPP = \
	main.cpp \
	deamoncreator.cpp \
	signalhandler.cpp \
	database.cpp \
	reporter.cpp \
	$(NULL)

SRC_CPP_CONFIGMANAGER = \
	jsonparser.cpp \
	configmanagerfactory.cpp \
	reporterconfigmanager.cpp \
	eventdriverconfigmanager.cpp \
	$(NULL)

SRC_CPP_EVENT_DRIVER = \
	eventdriverconfiguration.cpp \
	eventdriverserver.cpp \
	linuxstatemanager.cpp \
	eventtracker.cpp \
	statechangemanager.cpp \
	statemachine.cpp \
	statenotracking.cpp \
	stateactivetracking.cpp \
	stateidletracking.cpp \
	$(NULL)

OBJ += $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRC_CPP))
OBJ_CONFIGMANAGER += $(patsubst %.cpp, $(OBJ_DIR)/configmanager/%.o, $(SRC_CPP_CONFIGMANAGER))
OBJ_EVENT_DRIVER += $(patsubst %.cpp, $(OBJ_DIR)/event_driver/%.o, $(SRC_CPP_EVENT_DRIVER))

.PHONY: mkdir run

all: build

build: mkdir STT

run: build
	$(BIN_DIR)/STT

mkdir:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/configmanager
	@mkdir -p $(OBJ_DIR)/event_driver
	@mkdir -p $(BIN_DIR)

clean: 
	rm -rf $(OBJ_DIR) $(BIN_DIR)

STT: $(OBJ_CONFIGMANAGER) $(OBJ_EVENT_DRIVER) $(OBJ)
	$(CXX) $(CPP_FLAGS) -o $(BIN_DIR)/$@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@

$(OBJ_DIR)/configmanager/%.o: $(CONFIGMANAGER_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@

$(OBJ_DIR)/event_driver/%.o: $(EVENT_DRIVER_DIR)/%.cpp
	$(CXX) $(CPP_FLAGS) -c $(INC_PATH) $< -o $@
