#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>

#define DATABASE_NAME "nodenot_bd9"
#define CONNECT_TYPE "QODBC"

class database
{
public:
    database();
    bool openDatabase();
    void closeDatabase();

private:
    QSqlDatabase mydb;
};

#endif // DATABASE_H
