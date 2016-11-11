#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <memory>
#include <string>

#include <QWidget>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QString>

#include <QDialog>

using namespace std;

namespace Ui {
class EmployeeManager;
}

class EmployeeManager : public QDialog
{
    Q_OBJECT

public:
    QSqlDatabase myemployees;
    QSqlQueryModel *modal;
    int count;

    void closeEmployeeDatabase()
    {
        myemployees.close();
        myemployees.removeDatabase(QSqlDatabase::defaultConnection);
    }

    bool openEmployeeDatabase()
    {
        QString databasepath = QDir::homePath();
        databasepath = databasepath + QString("/Syndicate/Databases/Decrypted/EmployeeDatabase.db");

        myemployees = QSqlDatabase::addDatabase("QSQLITE");
        myemployees.setDatabaseName(databasepath);

        if(!myemployees.open())
        {
            qDebug() << ("Not Connected to Database..");
            return false;
        }
        else
        {
            qDebug() << ("Connected to Database..");
            return true;
        }

    }

    void createEmployeeDatabase()
    {
        openEmployeeDatabase();
        QSqlQuery query;
        query.prepare("CREATE TABLE employeeinfo (`Employee ID` INTEGER PRIMARY KEY, Permissions varchar(255),"
                      "`First Name` varchar(255),`Last Name` varchar(255),Age integer, `Date Of Birth` varchar(255),"
                      "Address varchar(255),City varchar(255),State varchar(255), `Zip Code` integer,"
                      "`Home Phone` varchar(255),`Cell Phone` varchar(255),Email varchar(255),Username varchar(255),"
                      "Password varchar(255))");
        query.exec();
        query.prepare("INSERT INTO employeeinfo ([Employee ID], Permissions, Username, Password)"
                      "values ('1', 'Admin', 'Admin', 'Admin')");
        query.exec();
        closeEmployeeDatabase();
    }

    void login();
    void logout();
    void viewEmployees();

public:
    explicit EmployeeManager(QWidget *parent = 0);
    ~EmployeeManager();

private slots:
    void on_viewemployees_clicked();
    void on_editemployees_clicked();
    void on_loginlogin_clicked();
    void on_loginusername_returnPressed();
    void on_loginpassword_returnPressed();
    void on_logoutbutton_clicked();
    void on_viewemployeetable_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::EmployeeManager *ui;
};

#endif // EMPLOYEEMANAGER_H
