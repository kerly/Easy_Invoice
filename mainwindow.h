#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databasemanager.h"
#include "customer.h"
#include "addcustomer.h"
#include "invoice.h"
#include "allcompanyinvoices.h"

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSplashScreen>
#include <QPixmap>
#include <QLabel>
#include <QVector>
#include <QList>

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

    DatabaseManager *_dbManager;
    QSqlQueryModel *_customerModel;
    QSqlQueryModel *_invoiceModel;
    QSqlTableModel *_invoiceTableModel;
    QSqlTableModel *_customerTableModel;

    bool addCustomerToList(Customer customer);
    bool editCustomer(Customer customer, QString origName);
    bool deleteCustomer(Customer customer);
    void showError(QString errMsg);
    void showStatus(QString statMsg);

private slots:
    void on_tableTabWidget_tabCloseRequested(int index);
    void on_pushButton_addCustomer_pressed();
    void on_pushButton_editCustomer_clicked();
    void on_pushButton_deleteCustomer_clicked();
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
