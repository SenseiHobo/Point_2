#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Opretter databaseforbindelse
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("sammy");  // Husk at ændre dette til dit brugernavn
    db.setPassword("#Superdeadcasp2004");  // Husk at ændre dette til din adgangskode
    if (!db.open()) {
        qDebug() << "Databaseforbindelse mislykkedes";
        return -1;
    }


    // Viser tilgængelige opgaver 

    QSqlQuery query;
     if (query.exec("SELECT * FROM task")) {
        while (query.next()) {

            int id = query.value(0).toInt(); 
            QString taskName = query.value(1).toString(); 
            QString time = query.value(2).toString(); 

            // Udskriv opgavens ID og navn
            qDebug() << "Opgave ID:" << id << "Navn:" << taskName << "Tid: " << time;
        }
    } else {
        qDebug() << "Fejl under udførsel af forespørgsel:" << query.lastError().text();
    }


    int taskId;
    std::cout << "Indtast ID for den opgave, du ønsker at fjerne: ";
    std::cin >> taskId;


    query.prepare("DELETE FROM task WHERE task_id = :task_id");
    query.bindValue(":task_id", taskId);

    if (query.exec()) {
        if(query.numRowsAffected() > 0) {
            qDebug() << "Opgaven med ID " << taskId << " er nu blevet klaret og er fjernet fra databasen.";
        } else {
            qDebug() << "Ingen opgaver fundet med det angivne ID.";
        }
    } else {
        qDebug() << "Fejl under fjernelsen af opgave: " << query.lastError().text();
    }

    std::cout << "Efterladende opgaver" << std::endl;

    if (query.exec("SELECT * FROM task")) {
        while (query.next()) {

            int id = query.value(0).toInt(); 
            QString taskName = query.value(1).toString(); 
            QString time = query.value(2).toString(); 

            // Udskriv opgavens ID og navn
            qDebug() << "Opgave ID:" << id << "Navn:" << taskName << "Tid: " << time;
        }
    } else {
        qDebug() << "Fejl under udførsel af forespørgsel:" << query.lastError().text();
    }



    return 0;
}
