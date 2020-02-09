#include "person.h"
#include "ui_person.h"
#include<QSqlQuery>
#include<QString>
#include<QDebug>
#include<QTextCharFormat>
#include<QColor>

Person::Person(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
}

Person::~Person()
{
    delete ui;
}

void Person::init(QString sno,QString sname)
{
    ui->label->setText("学号:"+sno);
    ui->label_2->setText("姓名:"+sname);
    QSqlQuery q;
    qDebug()<<q.exec(QString("select signTime from signinfo "
           "where sno='%1' and  date_format(signTime,'%Y-%m')="
           "date_format(curdate(),'%Y-%m')").arg(sno));
    q.next();
    ui->label_3->setText("签到次数:"+QString::number(q.size()));
    QTextCharFormat f;
    f.setForeground(Qt::red);
    f.setBackground(Qt::green);

    while(q.next())
    {
        ui->calendarWidget->setDateTextFormat(q.value(0).toDate(),f);
    }
}
