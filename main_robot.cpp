#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("robot_worker");
    db.setUserName("sammy");  
    db.setPassword("#Superdeadcasp2004");  
    if (!db.open()) {
        qDebug() << "Database connection failed";
        return -1;
    }

    QSqlQuery query;
    QString robotName = "MyRobot";
    if (!query.exec(QString("INSERT INTO robots (name, current_task) VALUES ('%1', 'Starting')").arg(robotName))) {
        qDebug() << "Could not create robot in the database:" << query.lastError().text();
        return -1;
    }
    qDebug() << "Robot named" << robotName << "has been created in the database.";

   
    if (query.exec("SELECT * FROM task")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString taskName = query.value(1).toString();
            QString time = query.value(2).toString();
            qDebug() << "Task ID:" << id << "Name:" << taskName << "Time:" << time;
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    
    int taskId;
    std::cout << "Enter the ID of the task you wish to remove: ";
    std::cin >> taskId;

    query.prepare("DELETE FROM task WHERE task_id = :task_id");
    query.bindValue(":task_id", taskId);
    if (query.exec()) {
        if(query.numRowsAffected() > 0) {
            qDebug() << "The task with ID" << taskId << "has now been completed and removed from the database.";
        } else {
            qDebug() << "No tasks found with the given ID.";
        }
    } else {
        qDebug() << "Error removing task:" << query.lastError().text();
    }

    
    std::cout << "Remaining tasks" << std::endl;
    if (query.exec("SELECT * FROM task")) {
        while (query.next()) {
            int id = query.value(0).toInt();
            QString taskName = query.value(1).toString();
            QString time = query.value(2).toString();
            qDebug() << "Task ID:" << id << "Name:" << taskName << "Time:" << time;
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
    }

    
    if (!query.exec(QString("DELETE FROM robots WHERE name = '%1'").arg(robotName))) {
        qDebug() << "Could not remove robot from the database:" << query.lastError().text();
    } else {
        qDebug() << "Robot named" << robotName << "has been removed from the database.";
    }

    return 0;
}
