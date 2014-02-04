#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableTabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);

    // Open Database
    QString messageResult = _dbManager.openDB();
    if(messageResult != NULL) {
        QMessageBox::critical(this, tr("Database Error"), "The database could not be opened: \n" + messageResult);
        ui->statusBar->showMessage("Open Database unsuccessful");

    } else {

        ui->statusBar->showMessage("Database Connected");

        messageResult = _dbManager.createCustomerAndInvoiceTables();
        if(messageResult != NULL){
            QMessageBox::critical(this, tr("Database Error"), "The tables could not be created: \n" + messageResult);
        }

        // Load the customer List
        _customerModel = _dbManager.loadCustomerList();

        if(_customerModel != NULL) {
            ui->listView->setModel(_customerModel);
            ui->statusBar->showMessage("Successfully loaded customer list");
        } else {
            QMessageBox::critical(this, tr("Database Error"), "The database could not load the customer list: \n" + messageResult);
            ui->statusBar->showMessage("Database: Load customer list unsuccessful");
        }

        // Load all Invoice table
        _invoiceModel = _dbManager.loadInvoiceTable();

        if(_invoiceModel != NULL) {
            ui->listView->setModel(_invoiceModel);
            ui->statusBar->showMessage("Successfully loaded customer list");
        } else {
            QMessageBox::critical(this, tr("Database Error"), "The database could not load the customer list: \n" + messageResult);
            ui->statusBar->showMessage("Database: Load customer list unsuccessful");
        }

    }
}

MainWindow::~MainWindow()
{
    _dbManager.closeDB();
    delete ui;
}


// PUBLIC FUNCTIONS
bool MainWindow::addCustomerToList(Customer customer) {

    QString messageResult = _dbManager.addCustomer(customer);
    if( messageResult != NULL)
    {

        QMessageBox::critical(this, tr("Save attempt failed"), "Could not save \"" + customer.getCompanyName() + "\" into the database: \n" + messageResult);
        ui->statusBar->showMessage("Add to database unsuccessful: " + customer.getCompanyName());
        return false;
    } else {

        ui->statusBar->showMessage("Successfully added \"" + customer.getCompanyName() + "\" to the databse");
        _allCustomers.append(customer);
        //ui->listWidget->addItem(customer.getCompanyName());

        // Close the current tab
        ui->tableTabWidget->removeTab(ui->tableTabWidget->currentIndex());

        // Open the company invoice tab
        QWidget *customerInvoiceTab = new AllCompanyInvoices(0, this, &customer);
        ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(customerInvoiceTab, customer.getCompanyName() + " Invoices"));
    }

    return true;

}

bool MainWindow::editCustomer(Customer customer) {

    QString messageResult = _dbManager.updateCustomer(customer);
    if( messageResult != NULL)
    {

        QMessageBox::critical(this, tr("Update attempt failed"), "Could not update \"" + customer.getCompanyName() + "\" in the database: \n" + messageResult);
        ui->statusBar->showMessage("Database update unsuccessful: " + customer.getCompanyName());
        return false;

    } else {

        ui->statusBar->showMessage("Successfully updated \"" + customer.getCompanyName() + "\" info in the databse");
    }

    return true;
}

void MainWindow::showError(QString errMsg) {
    QMessageBox::critical(this, tr("Error"), errMsg);
    ui->statusBar->showMessage(errMsg);
}

// SLOTS
void MainWindow::on_tableTabWidget_tabCloseRequested(int index)
{
    ui->tableTabWidget->removeTab(index);
}

void MainWindow::on_pushButton_addCustomer_pressed()
{
    // Add a new tab where the user can input a new customer
    QWidget *addCustomer = new AddCustomer(0, this, "Add");
    ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(addCustomer, tr("Add New Company")));
}


void MainWindow::on_pushButton_editCustomer_clicked()
{
    // Add a new tab where the user can input a new customer
    QWidget *addCustomer = new AddCustomer(0, this, "Apply Edits");
    ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(addCustomer, tr("Edit Company Fields")));
}
