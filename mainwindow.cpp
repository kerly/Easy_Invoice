#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Setup UI components
    ui->setupUi(this);
    ui->tableTabWidget->tabBar()->tabButton(0, QTabBar::RightSide)->resize(0, 0);
    QList<int> sizes;
    sizes << 100 << 1000;
    ui->splitter->setSizes(sizes);

    // Start splash screen
    QPixmap pixmap(":/images/resources/aperture_blue.png");
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();

    // Open Database
    _dbManager = new DatabaseManager(this);
    QString messageResult = _dbManager->openDB();
    if(messageResult != NULL) {
        QMessageBox::critical(this, tr("Database Error"), "The database could not be opened: \n" + messageResult);
        ui->statusBar->showMessage("Open Database unsuccessful");

    } else {

        ui->statusBar->showMessage("Database Connected");

        messageResult = _dbManager->createCustomerAndInvoiceTables();
        if(messageResult != NULL){
            QMessageBox::critical(this, tr("Database Error"), "The tables could not be created: \n" + messageResult);
        }

        // Load the customer List
        _customerTableModel = new QSqlTableModel(this);
        _customerTableModel->setTable("customer");
        _customerTableModel->select();
        ui->listView->setModel(_customerTableModel);
        ui->listView->setModelColumn(1);
//        _customerModel = _dbManager->loadCustomerList();
//        if(_customerModel != NULL) {
//            ui->listView->setModel(_customerModel);
//            ui->statusBar->showMessage("Successfully loaded customer list");
//        } else {
//            QMessageBox::critical(this, tr("Database Error"), "The database could not load the customer list");
//            ui->statusBar->showMessage("Database: Load customer list unsuccessful");
//        }

        // Load all Invoice table
        _invoiceTableModel = new QSqlTableModel(this);
        _invoiceTableModel->setTable("invoice");
        _invoiceTableModel->select();
        ui->tableView->setModel(_invoiceTableModel);
//        _invoiceModel = _dbManager.loadInvoiceTable();

//        if(_invoiceModel != NULL) {
//            ui->tableView->setModel(_invoiceModel);
//            ui->statusBar->showMessage("Successfully loaded invoice table");
//        } else {
//            QMessageBox::critical(this, tr("Database Error"), "The database could not load the invoice table");
//            ui->statusBar->showMessage("Database: Load invoice table unsuccessful");
//        }

    }

    //QThread::sleep(3);
    splash->hide();
}

/*
 *TUTORIAL:
 *model = new QSqlTableModel(this);
 *model->setTable("customer");
 *model->select();
 *ui->tableView->setModel(model);
 *
 *
 */

MainWindow::~MainWindow()
{
    _dbManager->closeDB();
    delete ui;
}


// PUBLIC FUNCTIONS
bool MainWindow::addCustomerToList(Customer customer) {

    QString messageResult = _dbManager->addCustomer(customer);
    if( messageResult != NULL)
    {

        QMessageBox::critical(this, tr("Save attempt failed"), "Could not save \"" + customer.getCompanyName() + "\" into the database: \n" + messageResult);
        ui->statusBar->showMessage("Add to database unsuccessful: " + customer.getCompanyName());
        return false;
    } else {

        ui->statusBar->showMessage("Successfully added \"" + customer.getCompanyName() + "\" to the databse");

        // Close the current tab
        ui->tableTabWidget->removeTab(ui->tableTabWidget->currentIndex());

        // Open the company invoice tab
        QWidget *customerInvoiceTab = new AllCompanyInvoices(0, this, &customer);
        ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(customerInvoiceTab, customer.getCompanyName() + " Invoices"));
    }

    return true;

}

bool MainWindow::editCustomer(Customer customer, QString origName) {

    QString messageResult = _dbManager->updateCustomer(customer, origName);
    if( messageResult != NULL)
    {

        QMessageBox::critical(this, tr("Update attempt failed"), "Could not update \"" + customer.getCompanyName() + "\" in the database: \n" + messageResult);
        ui->statusBar->showMessage("Database update unsuccessful: " + customer.getCompanyName());
        return false;

    } else {

        ui->statusBar->showMessage("Successfully updated \"" + customer.getCompanyName() + "\" info in the databse");
        ui->tableTabWidget->removeTab(ui->tableTabWidget->currentIndex());
    }

    return true;
}

bool MainWindow::deleteCustomer(Customer customer) {

    QString messageResult = _dbManager->deleteCustomer(customer);
    if( messageResult != NULL)
    {

        QMessageBox::critical(this, tr("Delete attempt failed"), "Could not delete \"" + customer.getCompanyName() + "\" from the database: \n" + messageResult);
        ui->statusBar->showMessage("Database remove unsuccessful: " + customer.getCompanyName());
        return false;

    } else {

        ui->statusBar->showMessage("Successfully deleted \"" + customer.getCompanyName() + "\" from the databse");
        ui->tableTabWidget->removeTab(ui->tableTabWidget->currentIndex());
    }

    return true;
}

void MainWindow::showError(QString errMsg) {
    QMessageBox::critical(this, tr("Error"), errMsg);
    ui->statusBar->showMessage(errMsg);
}

void MainWindow::showStatus(QString statMsg) {
    ui->statusBar->showMessage(statMsg);
}

// SLOTS
void MainWindow::on_tableTabWidget_tabCloseRequested(int index)
{
    ui->tableTabWidget->removeTab(index);
}

void MainWindow::on_pushButton_addCustomer_pressed()
{
    // Add a new tab where the user can input a new customer
    QWidget *addCustomer = new AddCustomer(0, this, NULL, "Add");
    ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(addCustomer, tr("Add New Company")));
}


void MainWindow::on_pushButton_editCustomer_clicked()
{
    // Add a new tab where the user can edit a current customer
    QAbstractItemModel *model = ui->listView->model();
    QString cNameFromList = model->data(ui->listView->currentIndex(), Qt::DisplayRole).toString();
    Customer *customer = _dbManager->getCustomerByName(cNameFromList);

    if(customer != NULL) {
        QWidget *editCustomer = new AddCustomer(0, this, customer ,"Apply Edits");
        ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(editCustomer, tr("Edit Company Fields")));

    } else {
        QMessageBox::critical(this, tr("Error"), "Cannot edit customer: \"" + cNameFromList + "\" ");
        ui->statusBar->showMessage("Could not edit customer: \"" + cNameFromList + "\" ");
    }
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    // Open the company invoice tab
    QAbstractItemModel *model = ui->listView->model();
    QString cNameFromList = model->data(index, Qt::DisplayRole).toString();
    Customer *customer = _dbManager->getCustomerByName(cNameFromList);

    QWidget *customerInvoiceTab = new AllCompanyInvoices(0, this, customer);
    ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(customerInvoiceTab, customer->getCompanyName() + " Invoices"));
}

void MainWindow::on_pushButton_deleteCustomer_clicked()
{
    // Add a new tab where the user can delete a customer
    QAbstractItemModel *model = ui->listView->model();
    QString cNameFromList = model->data(ui->listView->currentIndex(), Qt::DisplayRole).toString();
    Customer *customer = _dbManager->getCustomerByName(cNameFromList);

    if(customer != NULL) {
        QWidget *deleteCustomer = new AddCustomer(0, this, customer ,"DELETE COMPANY");
        ui->tableTabWidget->setCurrentIndex(ui->tableTabWidget->addTab(deleteCustomer, "DELETE " + cNameFromList + " FROM DATABASE"));

    } else {
        QMessageBox::critical(this, tr("Error"), "Could not find customer: \"" + cNameFromList + "\" ");
        ui->statusBar->showMessage("Could not find customer: \"" + cNameFromList + "\" ");
    }
}
