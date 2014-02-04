#include "allcompanyinvoices.h"
#include "ui_allcompanyinvoices.h"

#include "customer.h"

AllCompanyInvoices::AllCompanyInvoices(QWidget *parent, MainWindow *mW, Customer *customer) :
    QDialog(parent),
    ui(new Ui::AllCompanyInvoices)
{
    ui->setupUi(this);
    ui->label->setText(customer->getCompanyName());

    _mainWindow = mW;
    _customer = customer;
}

AllCompanyInvoices::~AllCompanyInvoices()
{
    delete ui;
}
