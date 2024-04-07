#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("sammy");  // Change to username
    db.setPassword("#Superdeadcasp2004");  // Change to password
    db.open();
    
    QSqlQuery query;
    
    qDebug() << query.exec("SELECT * FROM task"); // employee er her navnet på en tabel, ikke et schema
    
    qDebug() << "Number of rows:" << query.size(); 
    
    qDebug() << "Finished";
    return 1;
}


