
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
        QXmlItem xmlItem(xmlResult.next());

        while (!xmlItem.isNull()) {
            if (xmlItem.isAtomicValue()) {
                QString name = xmlItem.toAtomicValue().toString();
                result.push_back(name.toStdString());
            }

            values.append(xmlItem.toAtomicValue().toString());
            xmlItem = xmlResult.next();
        }
    }

    return result;
}

float DataBase::getAppTimeByDay(const std::string& appName, const std::string& day) {
    float result = -1;
    std::string filename = makeFilename(day);
    if (!fileExists(filename)) {
        std::cout << "[err] file " << filename << " do not exists" << std::endl;
        return result;
    }

    QFile file(filename.c_str());
    file.open(QFile::ReadOnly);

    QXmlQuery query;
    query.setFocus(&file);
    query.bindVariable( "appName", QVariant(appName.c_str()) );
    query.setQuery("sum(//Root/Application[Name=$appName]/Duration)");

    if (query.isValid()) {
        QXmlResultItems xmlResult;
        query.evaluateTo(&xmlResult);
        QXmlItem xmlItem(xmlResult.next());

        if (!xmlItem.isNull()) {
            result = xmlItem.toAtomicValue().toFloat();
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
    QString qfilename = filename.c_str();

    if (!fileExists(filename)) {

        QFile outFile(qfilename);
        if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug( "Failed to open file for writing." );
            return;
        }
        mDBDocName = day;

        QDomProcessingInstruction decl =
            mDBDoc.createProcessingInstruction("xml", "version=\"1.0\"");
        mDBDoc.appendChild(decl);

        QDomElement root = mDBDoc.createElement("Root");
        root.setAttribute("day", QString(mDBDocName.c_str()));
        mDBDoc.appendChild(root);

        QTextStream stream(&outFile);
        stream << mDBDoc.toString();
        outFile.close();
    } else if (day != mDBDocName) {
        QFile inFile(qfilename);
        if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading. " << qfilename;
            return;
        }

        if (!mDBDoc.setContent(&inFile)) {
            qDebug( "Failed to parse the file into a DOM tree." );
            inFile.close();
            return;
        }
        inFile.close();

        mDBDocName = day;
    }

}

void DataBase::writeToXML(AppInfo newApp)
{
    updateDBDoc();

    QDomElement node = mDBDoc.createElement("Application");
    node.setAttribute("pid", newApp.pid.c_str());

    appendSimpleNode(node, "Name", newApp.name);
    appendSimpleNode(node, "Title", newApp.title);
    appendSimpleNode(node, "Duration", std::to_string(newApp.duration));

    appendSimpleNode(node, "TimeStarted", std::to_string(newApp.timeStarted.toLong()));

    QDomElement root = mDBDoc.documentElement();
    root.appendChild(node);

    QFile outFile( makeFilename(mDBDocName).c_str() );
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }
    QTextStream stream( &outFile );
    stream << mDBDoc.toString();
    outFile.close();
}

void DataBase::appendSimpleNode(QDomElement& parent, std::string name, std::string text) const {
    QDomElement node = mDBDoc.createElement( QString(name.c_str()) );
    QDomText nodeText = mDBDoc.createTextNode( QString(text.c_str()) );
    node.appendChild(nodeText);
    parent.appendChild(node);

}

std::string DataBase::makeFilename(const std::string& day) {
    return "./data/" + day + ".xml";
}

bool DataBase::fileExists(const std::string& path) {
    QFileInfo checkFile(path.c_str());
    return checkFile.exists() && checkFile.isFile();
}
