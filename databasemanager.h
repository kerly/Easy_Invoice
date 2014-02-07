#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "mainwindow.h"
#include "customer.h"
#include "invoice.h"

#include <QObject>
#include <QVector>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

class MainWindow;
class Customer;

class DatabaseManager
{
public:
    DatabaseManager(MainWindow *mW);
    ~DatabaseManager();

public:
    QString openDB();
    void closeDB();
    bool deleteDB();
    QString createCustomerAndInvoiceTables();
    QSqlQueryModel *loadCustomerList();
    QSqlQueryModel *loadInvoiceTable();
    QSqlQueryModel *loadCustomerInvoices(Customer *customer);
    QString addCustomer(Customer customer);
    QString deleteCustomer(Customer customer);
    QString updateCustomer(Customer customer, QString origName);
    Customer *getCustomerByName(QString cName);
    QSqlError lastError();

private:
    MainWindow *_mainWindow;
    QSqlDatabase db;
    Customer *_customer;
    Invoice *_invoice;
    QVector<QString> _customerColumns;
    QVector<QString> _invoiceColumns;
};

#endif // DATABASEMANAGER_H
