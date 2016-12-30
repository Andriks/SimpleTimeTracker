#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QString>
#include <QJsonObject>


class JsonParser
{
public:
    static QJsonObject read(const QString filename);

};

#endif // JSONPARSER_H
