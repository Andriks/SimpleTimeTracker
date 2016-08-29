
#include "IDataBase.h"

class DataBase: public IDataBase
{
public:
    // singleton implementation
    static IDataBase& Instance();

    virtual ~DataBase();
    virtual void write();

private:
    DataBase();

    // delete copy and move constructors and assign operators
    DataBase(DataBase const&) = delete;             // Copy construct
    DataBase(DataBase&&) = delete;                  // Move construct
    DataBase& operator=(DataBase const&) = delete;  // Copy assign
    DataBase& operator=(DataBase &&) = delete;      // Move assign

};
