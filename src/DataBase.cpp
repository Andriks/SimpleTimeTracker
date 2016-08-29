
#include <iostream>

#include "DataBase.h"

DataBase::DataBase() {}
DataBase::~DataBase() {}

IDataBase& DataBase::Instance() {
    static DataBase OnlyOne;
    return OnlyOne;
}

void DataBase::write() {
    std::cout << "DataBase::write()" << std::endl;
}