
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

    void write(AppInfo newApp) override;
    StrVector getListOfAppByDay(const std::string& day) override;
    float getAppTimeByDay(const std::string& appName, const std::string& day) override;

private:
    void updateDBDoc();
    void writeToXML(AppInfo newApp);
    void appendSimpleNode(QDomElement& parent, std::string name, std::string text) const;

    // makes filename as './some/path/2000_01_01.xml' from day as '2000_01_01'
    std::string makeFilename(const std::string& day);
    bool fileExists(const std::string& path);

private:
    QDomDocument mDBDoc;
    std::string mDBDocName = "";

};
