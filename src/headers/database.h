
#include "Idatabase.h"

#include <memory>
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

    void write(const AppInfo &newApp) override;
    StrVector getListOfAppByDay(const QString &day) override;
    float getAppTimeByDay(const QString &appName, const QString &day) override;

private:
    void updateDBDoc();
    void writeToXML(const AppInfo &newApp);
    void appendSimpleNode(QDomElement& parent, const QString &name, const QString &text) const;

    // makes filename as './some/path/2000_01_01.xml' from day as '2000_01_01'
    QString makeFilename(const QString &day);
    bool fileExists(const QString &path);

private:
    QDomDocument mDBDoc;
    QString mDBDocName = "";

};
