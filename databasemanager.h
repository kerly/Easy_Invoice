#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "customer.h"

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>

class Customer;

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

public:
    QString openDB();
    void closeDB();
    bool deleteDB();
    QString createCustomerAndInvoiceTables();
    QSqlQueryModel *loadCustomerList();
    QSqlQueryModel *loadInvoiceTable();
    QString addCustomer(Customer customer);
    QString updateCustomer(Customer customer, QString origName);
    Customer *getCustomerByName(QString cName);
    QSqlError lastError();

private:
    QSqlDatabase db;
    Customer *_customer;
};

#endif // DATABASEMANAGER_H
