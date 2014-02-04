#ifndef ALLCOMPANYINVOICES_H
#define ALLCOMPANYINVOICES_H

#include "mainwindow.h"
#include "invoice.h"
#include "customer.h"

#include <QDialog>

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

private:
    Ui::AllCompanyInvoices *ui;
    MainWindow *_mainWindow;
    Customer *_customer;
};

#endif // ALLCOMPANYINVOICES_H
