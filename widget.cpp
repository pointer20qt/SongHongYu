#include "widget.h"
#include "ui_widget.h"
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
#include"person.h"

Widget::Widget(QWidget *parent,QString sname) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->sname=sname;
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
    dataToTable("select *from student");
    displayClass();
    displaySno();
    displayDate();
}

void Widget::dataToTable(QString sql)
{
    qDebug()<<this->sname;
    QSqlQuery q;//通过这个函数可以执行sql语句
    q.exec(QString("select sno from student where sname='%1'").arg(sname));
    q.next();
    QString curSno=q.value(0).toString();
    //exec 专门
    if(q.exec(sql))
    {
        ui->tableWidget->setRowCount(q.size());//根据数据库size（）出需要多少行
        int i=0;//i应该控制的是行
        while(q.next())
        {
            //将mysql中student表每一列提取出来到qt图形界面上
            //setItem就是设置格
            QCheckBox *c=new QCheckBox("未签到哦");
            QString sno=q.value(0).toString();

            QSqlQuery q3;
            q3.exec(QString("select signTime from signinfo "
                            "where sno=%1 and date(signTime)=curdate()"
                            "order by signTime desc").arg(sno));


            q3.next();

            if(sno!=curSno)
            {
                c->setDisabled(true);
            }

            //判断当天是否已经有签到的了，如果有每次运行的时候都要显示出来
            if(q3.size())
            {
                c->setText("已签到");
                c->setDisabled(true);
                c->setChecked(true);
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(q3.value(0).toString()));
            }
            //向tableWidget中一列一列添加数据
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(q.value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(q.value(1).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(q.value(2).toString()));
            ui->tableWidget->setCellWidget(i,3,c);
            //拉姆达表达式,[=]值传递
            connect(c,QCheckBox::clicked,[=](){
                //1.修改控件本身的状态
                c->setText("已签到");
                c->setDisabled(true);
                //2.向表格中添加本人签到时间
                ui->tableWidget->setItem(i,4,new QTableWidgetItem(QDateTime::currentDateTime().toString()));

                //3.向数据库中插入一条数据
                QSqlQuery q1;
                q1.exec(QString("insert into signInfo values(%1,now())").arg(sno));
            });
            i++;
       }
   }
}

void Widget::displayDate()
{
    connect(ui->tableWidget,QTableWidget::cellDoubleClicked,[=](int r,int c){
        Person* p=new Person();
        p->init(ui->tableWidget->item(r,0)->text(),ui->tableWidget->item(r,1)->text());
        p->show();
    });
}

void Widget::displayClass()
{
    //根据班级查找
    QSqlQuery q4;
    q4.exec("select distinct class from student");
    ui->comboBox->addItem("全部班级");
    while(q4.next())
    {
        ui->comboBox->addItem(q4.value(0).toString());
    }
    connect(ui->comboBox,QComboBox::currentTextChanged,[=](QString text){
       if(text=="全部班级")
       {
           dataToTable("select *from student");
       }
       else
       {
           dataToTable(QString("select *from student where class='%1'").arg(text));
       }
    });
}

void Widget::displaySno()
{
    //判断一下你是否已经填写学号，只有填写学号才能正常查找
    connect(ui->pushButton,QPushButton::clicked,[=](){
        if(ui->lineEdit->text().isEmpty())
        {
            QMessageBox::warning(this,"warn","您输入为空");
        }
        else
        {
            dataToTable(QString("select *from student where sno like '%1'").arg(ui->lineEdit->text()));
        }
    });
}

Widget::~Widget()
{
    delete ui;
}
