#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("sammy");  // Husk at ændre til dit brugernavn
    db.setPassword("#Superdeadcasp2004");  // Husk at ændre til din adgangskode
    if (!db.open()) {
        qDebug() << "Database connection failed";
        return -1;
    }



    QSqlQuery query;

    if (query.exec("SELECT * FROM task")) {
        while (query.next()) {
            // Antag at første kolonne indeholder opgavens ID og anden kolonne opgavens navn
            int id = query.value(0).toInt(); // Få ID fra første kolonne (index 0)
            QString taskName = query.value(1).toString(); // Få opgavens navn fra anden kolonne (index 1)
            QString time = query.value(2).toString(); 

            // Udskriv opgavens ID og navn
            qDebug() << "Opgave ID:" << id << "Navn:" << taskName << "Tid: " << time;
        }
    } else {
        qDebug() << "Fejl under udførsel af forespørgsel:" << query.lastError().text();
    }

    qDebug() << "Finished";
    return 0;
}


