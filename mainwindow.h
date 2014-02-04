#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasemanager.h"
#include "customer.h"
#include "addcustomer.h"
#include "invoice.h"
#include "allcompanyinvoices.h"

#include <QMainWindow>
#include <QLabel>
#include <QVector>

class Customer;
class Invoice;
class DatabaseManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<Customer> _allCustomers;
    QVector<Invoice> _allInvcoies;

    bool addCustomerToList(Customer customer);
    bool editCustomer(Customer customer, QString origName);
    void showError(QString errMsg);

private slots:
    void on_tableTabWidget_tabCloseRequested(int index);
    void on_pushButton_addCustomer_pressed();
    void on_pushButton_editCustomer_clicked();

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    DatabaseManager _dbManager;
    QSqlQueryModel *_customerModel;
    QSqlQueryModel *_invoiceModel;
};

#endif // MAINWINDOW_H
