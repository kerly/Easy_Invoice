#include "addcustomer.h"
#include "ui_addcustomer.h"

AddCustomer::AddCustomer(QWidget *parent, MainWindow *mW, Customer *sentCustomer, QString purpose) :
    QDialog(parent),
    ui(new Ui::AddCustomer)
{
    ui->setupUi(this);
    ui->applyPushButton->setText(purpose);
    _mainWindow = mW;
    _sentCustomer = sentCustomer;
    _purpose = purpose;

    // Set the fields if a valid customer was sent in
    if(_sentCustomer != NULL) {
        setFormFields(_sentCustomer);
    }
}

AddCustomer::~AddCustomer()
{
    delete ui;
}

// PUBLIC FUNCTIONS
void AddCustomer::setFormFields(Customer *customer) {

    ui->companyNameLineEdit->setText(customer->getCompanyName());
    ui->firstNameLineEdit->setText(customer->getFirstName());
    ui->lastNameLineEdit->setText(customer->getLastName());
    ui->phoneNumberLineEdit->setText(customer->getPhoneNumber());

    if(_purpose == "DELETE COMPANY") {
        ui->companyNameLineEdit->setReadOnly(true);
        ui->firstNameLineEdit->setReadOnly(true);
        ui->lastNameLineEdit->setReadOnly(true);
        ui->phoneNumberLineEdit->setReadOnly(true);
    }
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

        if(_purpose == "Add") {
            _mainWindow->addCustomerToList(customer);
        }
        else if(_purpose == "Apply Edits") {
            _mainWindow->editCustomer(customer, _sentCustomer->getCompanyName());
        }
        else if (_purpose == "DELETE COMPANY") {
            QMessageBox::StandardButton answer;
            answer = QMessageBox::question(this, tr("ARE YOU SURE?"), "DELETE \"" + customer.getCompanyName() + "\" AND ALL ASSOCIATED INVOICES FROM THE DATABASE?\nTHIS CANNOT BE UNDONE", QMessageBox::Yes | QMessageBox::No );
            if(answer == QMessageBox::Yes) {
                _mainWindow->deleteCustomer(customer);
            }
        }

    }
    else {
        _mainWindow->showError("Cannot add customer to database: Company Name field is not long enough");
    }



}
