
#include "DataBase.h"

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

#include <QtXml>
#include <QXmlQuery>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QString>
#include <QFile>
#include <QFileInfo>


DataBase::DataBase() {}

IDataBase& DataBase::Get() {
    static DataBase OnlyOne;
    return OnlyOne;
}

void DataBase::write(AppInfo newApp) {
    writeToXML(newApp);
}

StrVector DataBase::getListOfAppByDay(const std::string& day) {
    StrVector result;

    std::string filename = makeFilename(day);
    if (!fileExists(filename)) {
        std::cout << "[err] file " << filename << " do not exists" << std::endl;
        return result;
    }

    QFile file(filename.c_str());
    file.open(QFile::ReadOnly);

    QXmlQuery query;
    query.setFocus(&file);
    query.setQuery("distinct-values(//Root/Application/Name[text()])");

    QString values;
    if (query.isValid()) {
        QXmlResultItems xmlResult;
        query.evaluateTo(&xmlResult);
        QXmlItem XmlItem(xmlResult.next());

        while (!XmlItem.isNull()) {
            if (XmlItem.isAtomicValue()) {
                QString name = XmlItem.toAtomicValue().toString();
                result.push_back(name.toStdString());
            }

            values.append(XmlItem.toAtomicValue().toString());
            XmlItem = xmlResult.next();
        }
    }

    return result;
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

    appendSimpleNode(node, "TimeStarted", std::to_string(newApp.timeStarted.toLong()));

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

std::string DataBase::makeFilename(const std::string& day) {
    return "./data/" + day + ".xml";
}

bool DataBase::fileExists(const std::string& path) {
    QFileInfo checkFile(path.c_str());
    return checkFile.exists() && checkFile.isFile();
}
