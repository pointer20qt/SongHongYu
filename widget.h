#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0,QString sname=NULL);
    void dataToTable(QString sql);
    void displayClass();
    void displaySno();
    void displayDate();
    QString sname;
    ~Widget();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
