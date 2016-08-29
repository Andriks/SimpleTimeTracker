
#include "IDataBase.h"

#include <memory>
#include <tinyxml.h>

class DataBase: public IDataBase
{
public:
    ~DataBase() override;
    void write(AppInfo newApp) override;

private:
    void updateDBDoc();
    void writeToXML(AppInfo newApp);


private:
    std::shared_ptr<TiXmlDocument> mDBDoc = nullptr;
    std::string mDBDocName = "";


/// singleton implementation
public:
    static IDataBase& Instance();
private:
    DataBase();
    // delete copy and move constructors and assign operators
    DataBase(DataBase const&) = delete;             // Copy construct
    DataBase(DataBase&&) = delete;                  // Move construct
    DataBase& operator=(DataBase const&) = delete;  // Copy assign
    DataBase& operator=(DataBase &&) = delete;      // Move assign

};
