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

   
    if (query.exec("SELECT * FROM task WHERE is_assigned = FALSE")) {
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
    std::cout << "Enter the ID of the task you wish to assign: ";
    std::cin >> taskId;

    
    query.prepare("SELECT is_assigned FROM task WHERE task_id = :task_id");
    query.bindValue(":task_id", taskId);
    if (query.exec() && query.next()) {
        bool isAssigned = query.value(0).toBool();
        if (!isAssigned) {
            
            query.prepare("UPDATE task SET is_assigned = TRUE WHERE task_id = :task_id");
            query.bindValue(":task_id", taskId);
            if (query.exec()) {
                qDebug() << "The task with ID" << taskId << "is now assigned to the robot.";
            } else {
                qDebug() << "Error updating task assignment status:" << query.lastError().text();
            }
        } else {
            qDebug() << "This task is already assigned to another robot.";
        }
    } else {
        qDebug() << "Error checking task assignment status:" << query.lastError().text();
    }

    
    if (!query.exec(QString("DELETE FROM robots WHERE name = '%1'").arg(robotName))) {
        qDebug() << "Could not remove robot from the database:" << query.lastError().text();
    } else {
        qDebug() << "Robot named" << robotName << "has been removed from the database.";
    }

    return 0;
}

