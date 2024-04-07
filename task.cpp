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
    
    
    int taskName , taskTime; 
    std::string askDescription; 

    std::cout << "Indtast opgaven navn: "; 
    std::cin >> taskName;
    std::cout << std::endl; 

    std::cout << "Indtast opgaven beskrivelse: "; 
    std::getline(std::cin >> std::ws, askDescription); 
    std::cout << std::endl; 

    std::cout << "Indtast opgavens tid: ";
    std::cin >> taskTime; 
    std::cout << std::endl;  






    QSqlQuery query;
    
    
    query.prepare("INSERT INTO task(task_id, description, time) VALUES (:task_id, :taskDescription , :taskTime)");
    query.bindValue(":task_id", taskName);
    query.bindValue(":taskDescription", QString::fromStdString(askDescription)); 
    query.bindValue(":taskTime", taskTime);


    if(!query.exec()){
    	qDebug() << "Fejl under tilføjelsen af opgave: " << query.lastError().text();
    	return -1; 
    }

    qDebug() << "Opgaven er tilføjet til databasen med succes.";

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


