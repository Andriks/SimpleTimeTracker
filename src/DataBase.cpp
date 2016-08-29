
#include "DataBase.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>



DataBase::DataBase() {
    mDBDoc = std::shared_ptr<TiXmlDocument>(new TiXmlDocument());
}
DataBase::~DataBase() {}

IDataBase& DataBase::Instance() {
    static DataBase OnlyOne;
    return OnlyOne;
}

void DataBase::write(AppInfo newApp) {
    std::cout << "DataBase::write()" << std::endl;
    writeToXML(newApp);
}

void DataBase::updateDBDoc() {
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%Y_%m_%d",timeinfo);
    std::string filename(buffer);
    filename = "./bin/" + filename + ".xml";

    std::ifstream infile(filename);
    if (!infile.good()) {
        mDBDocName = buffer;
        mDBDoc = std::shared_ptr<TiXmlDocument>(new TiXmlDocument(filename));

        TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
        TiXmlElement* root = new TiXmlElement( "Root" );

        mDBDoc->LinkEndChild(decl);
        mDBDoc->LinkEndChild(root);

        mDBDoc->SaveFile(filename);
    } else if (buffer != mDBDocName) {
        if (!mDBDoc->LoadFile(filename)) {
            std::cout << "can't load " << filename << std::endl;
        }
        mDBDocName = buffer;
    }
}

void DataBase::writeToXML(AppInfo newApp)
{
    updateDBDoc();

    TiXmlElement* root = nullptr;
    root = mDBDoc->FirstChildElement(); 

    TiXmlElement node("Application");
    node.SetAttribute("name", newApp.name);

    TiXmlElement pid("Pid");
    TiXmlText pidText(newApp.pid);
    pid.LinkEndChild(&pidText);
    node.LinkEndChild(&pid);

    TiXmlElement title("Title");
    TiXmlText titleText(newApp.title);
    title.LinkEndChild(&titleText);
    node.LinkEndChild(&title);

    // auto time std::chrono::time_point_cast<std::chrono::milliseconds>(newApp.timeStarted)
    // int time = newApp.timeStarted.time_since_epoch().count();
    // TiXmlElement timeStarted("Title");
    // TiXmlText timeStartedText(time);
    // timeStarted.LinkEndChild(&timeStartedText);
    // node.LinkEndChild(&timeStarted);

    root->LinkEndChild(&node);
    mDBDoc->SaveFile("./bin/" + mDBDocName + ".xml" );
}