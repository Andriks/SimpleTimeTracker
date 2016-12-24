
#include "database.h"

#include <QtXml>
#include <QXmlQuery>
#include <QXmlResultItems>
#include <QXmlNodeModelIndex>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>

#include <QDebug>


DataBase::DataBase() {}

IDataBase& DataBase::Get() {
    static DataBase OnlyOne;
    return OnlyOne;
}

void DataBase::write(const AppInfo &newApp, bool autosave) {
    writeToXML(newApp, autosave);
}

StrVector DataBase::getListOfAppByDay(const QString &day) {
    StrVector result;

    QString filename = makeFilename(day);
    if (!fileExists(filename)) {
        qDebug() << "[err] file " << filename << " do not exists";
        return result;
    }

    QFile file(filename);
    file.open(QFile::ReadOnly);

    QXmlQuery query;
    query.setFocus(&file);
    query.setQuery("distinct-values(//Root/Application[@idle='false']/Name[text()])");

    QString values;
    if (query.isValid()) {
        QXmlResultItems xmlResult;
        query.evaluateTo(&xmlResult);
        QXmlItem xmlItem(xmlResult.next());

        while (!xmlItem.isNull()) {
            if (xmlItem.isAtomicValue()) {
                QString name = xmlItem.toAtomicValue().toString();
                result.append(name);
            }

            values.append(xmlItem.toAtomicValue().toString());
            xmlItem = xmlResult.next();
        }
    }

    return result;
}

float DataBase::getAppTimeByDay(const QString &appName, const QString &day) {
    float result = -1;
    QString filename = makeFilename(day);
    if (!fileExists(filename)) {
        qDebug() << "[err] file " << filename << " do not exists";
        return result;
    }

    QFile file(filename);
    file.open(QFile::ReadOnly);

    QXmlQuery query;
    query.setFocus(&file);
    query.bindVariable("appName", QVariant(appName));
    query.setQuery("sum(//Root/Application[@idle='false' and Name=$appName]/Duration)");

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

float DataBase::getIdleTimeByDay(const QString &day)
{
    float result = -1;
    QString filename = makeFilename(day);
    if (!fileExists(filename)) {
        qDebug() << "[err] file " << filename << " do not exists";
        return result;
    }

    QFile file(filename);
    file.open(QFile::ReadOnly);

    QXmlQuery query;
    query.setFocus(&file);
    query.setQuery("sum(//Root/Application[@idle='true']/Duration)");

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
    QDateTime now = QDateTime::currentDateTime();
    QString day = now.toString("yyyyMMdd");
    QString filename = makeFilename(day);

    if (!fileExists(filename)) {
        QFile outFile(filename);
        if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for writing.";
            return;
        }
        mDBDocName = day;

        QDomProcessingInstruction decl =
            mDBDoc.createProcessingInstruction("xml", "version=\"1.0\"");
        mDBDoc.appendChild(decl);

        QDomElement root = mDBDoc.createElement("Root");
        root.setAttribute("day", QString(mDBDocName));
        mDBDoc.appendChild(root);

        QTextStream stream(&outFile);
        stream << mDBDoc.toString();
        outFile.close();
    } else if (day != mDBDocName) {
        QFile inFile(filename);
        if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file for reading. " << filename;
            return;
        }

        if (!mDBDoc.setContent(&inFile)) {
            qDebug() << "Failed to parse the file into a DOM tree.";
            inFile.close();
            return;
        }
        inFile.close();
        mDBDocName = day;
    }

}

void DataBase::writeToXML(const AppInfo &newApp, bool autosave) {
    updateDBDoc();

    QDomElement node = mDBDoc.createElement("Application");
    node.setAttribute("autosave", (autosave ? "true" : "false"));
    if (newApp.name != "idle") {
        node.setAttribute("idle", "false");
        appendSimpleNode(node, "Name", newApp.name);
        appendSimpleNode(node, "Title", newApp.title);
        appendSimpleNode(node, "Duration", QString::number(newApp.duration));
        appendSimpleNode(node, "TimeStarted", QString::number(newApp.timeStarted));
    } else {
        node.setAttribute("idle", "true");
        appendSimpleNode(node, "Duration", QString::number(newApp.duration));
        appendSimpleNode(node, "TimeStarted", QString::number(newApp.timeStarted));
    }


    QDomElement root = mDBDoc.documentElement();
    root.appendChild(node);

    QFile outFile( makeFilename(mDBDocName) );
    if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing.";
        return;
    }
    QTextStream stream( &outFile );
    stream << mDBDoc.toString();
    outFile.close();
}

void DataBase::appendSimpleNode(QDomElement &parent, const QString &name, const QString &text) const {
    QDomElement node = mDBDoc.createElement(name);
    QDomText nodeText = mDBDoc.createTextNode(text);
    node.appendChild(nodeText);
    parent.appendChild(node);

}

QString DataBase::makeFilename(const QString& day) {
    return "./data/" + day + ".xml";
}

bool DataBase::fileExists(const QString& path) {
    QFileInfo checkFile(path);
    return checkFile.exists() && checkFile.isFile();
}
