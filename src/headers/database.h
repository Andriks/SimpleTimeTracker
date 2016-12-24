
#include "Idatabase.h"

#include <QDomDocument>
#include <QDomElement>

class DataBase: public IDataBase
{
private:
    /// Singleton implementation
    DataBase();
    DataBase(DataBase const&) = delete;             // Copy construct
    DataBase(DataBase&&) = delete;                  // Move construct
    DataBase& operator=(DataBase const&) = delete;  // Copy assign
    DataBase& operator=(DataBase &&) = delete;      // Move assign
public:
    static IDataBase& Get();

    void write(const AppInfo &newApp, bool autosave) override;
    StrVector getListOfAppByDay(const QString &day) override;
    float getAppTimeByDay(const QString &appName, const QString &day) override;
    float getIdleTimeByDay(const QString &day) override;

private:
    void updateDBDoc();
    void writeToXML(const AppInfo &newApp, bool autosave);
    void appendSimpleNode(QDomElement& parent, const QString &name, const QString &text) const;

    // makes filename as './some/path/20160101.xml' from day as '20160101'
    QString makeFilename(const QString &day);
    bool fileExists(const QString &path);

private:
    QDomDocument mDBDoc;
    QString mDBDocName = "";

};
