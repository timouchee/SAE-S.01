#include "database.h"
#include <QDebug>

database::database()
{

}

bool database::openDatabase()
{
    qDebug() << "zteh" << Qt::endl;
    mydb = QSqlDatabase::addDatabase(CONNECT_TYPE);
    mydb.setDatabaseName(DATABASE_NAME);

    return (mydb.open());
}

void database::closeDatabase()
{

}
