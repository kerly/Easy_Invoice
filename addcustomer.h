#ifndef ADDCUSTOMER_H
#define ADDCUSTOMER_H

#include "mainwindow.h"
#include "customer.h"

#include <QDialog>
#include <QMessageBox>

class MainWindow;
class Customer;

namespace Ui {
class AddCustomer;
}

class AddCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomer(QWidget *parent = 0, MainWindow *mW = 0, Customer *sentCustomer = NULL, QString purpose = NULL);
    ~AddCustomer();

    void setFormFields(Customer *customer);

private slots:
    void on_applyPushButton_clicked();

private:
    Ui::AddCustomer *ui;
    MainWindow *_mainWindow;
    QString _purpose;
    Customer *_sentCustomer;

};

#endif // ADDCUSTOMER_H
