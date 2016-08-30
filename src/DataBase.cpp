
#include "DataBase.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>


DataBase::DataBase() {}
DataBase::~DataBase() {}

IDataBase& DataBase::Instance() {
    static DataBase OnlyOne;
    return OnlyOne;
}

void DataBase::write(AppInfo newApp) {
    writeToXML(newApp);
}

void DataBase::updateDBDoc() {
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);

    std::strftime(buffer,80,"%Y_%m_%d",timeinfo);
    std::string day = buffer;
    std::string filename = makeFilename(day);

    std::ifstream infile(filename);
    if (!infile.good()) {
        mDBDocName = day;

        TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
        TiXmlElement* root = new TiXmlElement( "Root" );
        root->SetAttribute("day", mDBDocName);

        mDBDoc.LinkEndChild(decl);
        mDBDoc.LinkEndChild(root);

        mDBDoc.SaveFile(filename);
    } else if (day != mDBDocName) {
        if (!mDBDoc.LoadFile(filename)) {
            std::cerr << "can't load " << filename << std::endl;
        }
        mDBDocName = day;
    }
}

void DataBase::writeToXML(AppInfo newApp)
{
    updateDBDoc();

    TiXmlElement* node = new TiXmlElement("Application");
    node->SetAttribute("pid", newApp.pid);

    appendSimpleNode(node, "Name", newApp.name);
    appendSimpleNode(node, "Title", newApp.title);
    appendSimpleNode(node, "Duration", std::to_string(newApp.duration));

    long time = newApp.timeStarted.time_since_epoch().count();
    appendSimpleNode(node, "TimeStarted", std::to_string(time));

    TiXmlElement* root = mDBDoc.FirstChildElement();
    root->LinkEndChild(node);
    mDBDoc.SaveFile(makeFilename(mDBDocName));
}

void DataBase::appendSimpleNode(TiXmlElement* parent, std::string name, std::string text) const {
    TiXmlElement* node = new TiXmlElement(name);
    TiXmlText* nodeText = new TiXmlText(text);
    node->LinkEndChild(nodeText);
    parent->LinkEndChild(node);
}

std::string DataBase::makeFilename(std::string day) {
    return "./data/" + day + ".xml";
}
