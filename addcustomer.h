#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include "mainwindow.h"
#include "customer.h"

#include <QDialog>

class MainWindow;
class Customer;

namespace Ui {
class AddCustomer;
}

class AddCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomer(QWidget *parent = 0, MainWindow *mW = 0, QString purpose = NULL);
    ~AddCustomer();

private slots:
    void on_applyPushButton_clicked();

private:
    Ui::AddCustomer *ui;
    MainWindow *_mainWindow;
    QString _purpose;

};

#endif // ADDCUSTOMER_H
