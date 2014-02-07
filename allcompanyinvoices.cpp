#include "allcompanyinvoices.h"
#include "ui_allcompanyinvoices.h"

#include "customer.h"

AllCompanyInvoices::AllCompanyInvoices(QWidget *parent, MainWindow *mW, Customer *customer) :
    QDialog(parent),
    ui(new Ui::AllCompanyInvoices)
{
    // Setup UI
    ui->setupUi(this);
    ui->label_cName->setText(customer->getCompanyName());
    ui->label_fName->setText("Frist name: " + customer->getFirstName());
    ui->label_lName->setText("Last name: " + customer->getLastName());
    ui->label_pNumber->setText("Phone number: " + customer->getPhoneNumber());

    // Set variables
    _mainWindow = mW;
    _customer = customer;

    // Load customer invoices
    loadCustomerInvoices();
}

AllCompanyInvoices::~AllCompanyInvoices()
{
    delete ui;
}

void AllCompanyInvoices::on_pushButton_addInvoices_pressed()
{
    // Add invoices to the database
    QVector<Invoice> invoices;
}

void AllCompanyInvoices::loadCustomerInvoices() {

    // Load all Invoice table
    _invoiceModel = _mainWindow->_dbManager->loadCustomerInvoices(_customer);

    if(_invoiceModel != NULL) {
        ui->tableView->setModel(_invoiceModel);
        _mainWindow->showStatus("Successfully loaded invoice table: " + _customer->getCompanyName());
    } else {
        QMessageBox::critical(this, tr("Database Error"), "The database could not load the invoice table: " + _customer->getCompanyName());
        _mainWindow->showStatus("Database: Load invoice table for " + _customer->getCompanyName() + " unsuccessful");
    }
}
