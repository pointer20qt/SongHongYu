#include "widget.h"
#include "login.h"
#include<QApplication>
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QTableWidgetItem>
#include<QCheckBox>
#include<QDateTime>
#include<QString>
#include<QMessageBox>
#include<QPushButton>
#include<QTableWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login l;
    l.show();
    return a.exec();
}
