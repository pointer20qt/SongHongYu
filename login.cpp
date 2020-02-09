#include "login.h"
#include "widget.h"
#include "ui_login.h"
#include "widget.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QSqlQuery>
#include<QPushButton>
#include<QString>
#include<QMessageBox>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");//QT连接数据库需要的驱动
    db.setDatabaseName("20_sign");
    db.setUserName("root");
    db.setPassword("123456");
    if(db.open())
    {
        qDebug()<<"数据库连接成功";
    }
    else
    {
        qDebug()<<"数据库连接失败";
    }
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString sname=ui->lineEdit->text();
    QString pwd=ui->lineEdit_2->text();
    QSqlQuery q;
    //sql语句查询sname是否在数据库中存在
    qDebug()<<q.exec(QString("select *from student where sname='%1'").arg(sname));
    if(q.size())
    {
        q.exec(QString("select *from student where pwd='%1'").arg(pwd));
        if(q.size()>0)
        {
            Widget *w=new Widget(0,sname);
            w->show();
            this->close();
        }
        else
        {
            QMessageBox::warning(this,"错误窗口","密码错误");
        }
    }
    else
    {
        QMessageBox::warning(this,"错误窗口","用户名错误");
    }
}































