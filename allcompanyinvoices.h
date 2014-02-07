#ifndef ALLCOMPANYINVOICES_H
#define ALLCOMPANYINVOICES_H

#include "mainwindow.h"
#include "invoice.h"
#include "customer.h"

#include <QDialog>
#include <QSqlQueryModel>

class MainWindow;
class Customer;
class Invoice;

namespace Ui {
class AllCompanyInvoices;
}

class AllCompanyInvoices : public QDialog
{
    Q_OBJECT

public:
    explicit AllCompanyInvoices(QWidget *parent = 0, MainWindow *mW = 0, Customer *customer = NULL);
    ~AllCompanyInvoices();

    void loadCustomerInvoices();

private slots:
    void on_pushButton_addInvoices_pressed();

private:
    Ui::AllCompanyInvoices *ui;
    MainWindow *_mainWindow;
    QSqlQueryModel *_invoiceModel;
    Customer *_customer;
};

#endif // ALLCOMPANYINVOICES_H
