#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QString>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void dataToTable(QString sql);
    ~Login();

private slots:


    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
