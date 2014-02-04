#include "addcustomer.h"
#include "ui_addcustomer.h"

AddCustomer::AddCustomer(QWidget *parent, MainWindow *mW, QString purpose) :
    QDialog(parent),
    ui(new Ui::AddCustomer)
{
    ui->setupUi(this);
    ui->applyPushButton->setText(purpose);
    _mainWindow = mW;
    _purpose = purpose;
}

AddCustomer::~AddCustomer()
{
    delete ui;
}

// SLOTS
void AddCustomer::on_applyPushButton_clicked()
{
    // Set the customer from the fields
    Customer customer;
    QString cNameHolder = ui->companyNameLineEdit->text();

    customer.setFirstName(ui->firstNameLineEdit->text());
    customer.setLastName(ui->lastNameLineEdit->text());
    customer.setPhoneNumber(ui->phoneNumberLineEdit->text());

    // Add if name is long enough
    if(cNameHolder.size() > 2) {
        customer.setCompanyName(cNameHolder);

        if(_purpose == "Add")
            _mainWindow->addCustomerToList(customer);
        else if(_purpose == "Apply Edits")
            _mainWindow->editCustomer(customer);

    }
    else {
        _mainWindow->showError("Cannot add customer to database: Company Name field is not long enough");
    }



}
