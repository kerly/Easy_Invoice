#include "databasemanager.h"

const QString DB_NAME = "DocuPrint.db.sqlite";

DatabaseManager::DatabaseManager(MainWindow *mW)
{
    _mainWindow = mW;
}
DatabaseManager::~DatabaseManager()
{
}

QString DatabaseManager::openDB()
{
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");

#ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
#else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName(DB_NAME);
#endif

    // Open databasee
    if(db.open() == false)
        return db.lastError().text();

    return NULL;
}

void DatabaseManager::closeDB()
{
    // Close the database
    if(db.isOpen() == true)
    {
        db.close();
        db.removeDatabase(QSqlDatabase::defaultConnection);
    }
}

QSqlError DatabaseManager::lastError()
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

bool DatabaseManager::deleteDB()
{
    // Close database
    db.close();

#ifdef Q_OS_LINUX
    // NOTE: We have to store database file into user home folder in Linux
    QString path(QDir::home().path());
    path.append(QDir::separator()).append(DB_NAME);
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
#else

    // Remove created database binary file
    return QFile::remove(DB_NAME);
#endif
}

QString DatabaseManager::createCustomerAndInvoiceTables()
{

    if(db.isOpen() == false)
        if(db.open() == false)
            return db.lastError().text();

    QString compId = "companyId INTEGER PRIMARY KEY NOT NULL, ";



    QSqlQuery query;
    bool ret = query.exec("create table if not exists customer( "
                     + compId +
                     "companyName VARCHAR(25) NOT NULL UNIQUE, "
                     "firstName VARCHAR(20), "
                     "lastName VARCHAR(20), "
                     "phoneNumber VARCHAR(20) )");

    if(ret == false) {
        return query.lastError().text();
    }

    QSqlQuery query2;
    bool ret2 = query2.exec("create table if not exists invoice( "
                       "invoiceId INTEGER PRIMARY KEY NOT NULL, "
                       "companyName VARCHAR(25), "
                       "date TEXT, "
                       "cost FLOAT, "
                       "comments VARCHAR(225), "
                       "inheritId INTEGER NOT NULL REFERENCES customer(companyId) )");

    if(ret2 == false) {
        return query2.lastError().text();
    }

    return NULL;
}

QSqlQueryModel* DatabaseManager::loadCustomerList() {

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();

    if(db.isOpen() == false)
        if(db.open() == false)
            return NULL;

    query->prepare("select companyName from customer");

    if( !query->exec() ) {
        return NULL;
    }

    modal->setQuery(*query);
    return modal;

}

QSqlQueryModel* DatabaseManager::loadInvoiceTable() {

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();

    if(db.isOpen() == false)
        if(db.open() == false)
            return NULL;

    query->prepare("select date, companyName, cost, comments from invoice");

    if( !query->exec() ) {
        return NULL;
    }

    modal->setQuery(*query);
    return modal;

}

QSqlQueryModel* DatabaseManager::loadCustomerInvoices(Customer *customer) {

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();

    if(db.isOpen() == false)
        if(db.open() == false)
            return NULL;

    query->prepare("select date, cost, comments from invoice where companyName ='"+customer->getCompanyName()+"' ");

    if( !query->exec() ) {
        return NULL;
    }

    modal->setQuery(*query);
    return modal;

}

QString DatabaseManager::addCustomer(Customer customer) {

    QSqlQuery qry;

    if(db.isOpen() == false)
        if(db.open() == false)
            return db.lastError().text();

    if( !qry.exec("insert into customer (companyName, firstName, lastName, phoneNumber) values ('"+customer.getCompanyName()+"', '"+customer.getFirstName()+"', '"+customer.getLastName()+"', '"+customer.getPhoneNumber()+"')") )
    {
        return qry.lastError().text();
    }

    return NULL;
}

QString DatabaseManager::deleteCustomer(Customer customer) {

    QSqlQuery qry;

    if(db.isOpen() == false)
        if(db.open() == false)
            return db.lastError().text();

    if( !qry.exec("DELETE from customer where companyName='"+customer.getCompanyName()+"' ") )
    {
        return qry.lastError().text();
    }

    if( !qry.exec("DELETE from invoice where companyName='"+customer.getCompanyName()+"' ") )
    {
        return qry.lastError().text();
    }

    return NULL;
}

Customer *DatabaseManager::getCustomerByName(QString cName) {

    Customer *retrievedCustomer = new Customer();
    QSqlQuery qry;

    if(db.isOpen() == false)
        if(db.open() == false)
            return NULL;

    if( qry.exec("select * from customer where companyName='"+cName+"' ")) {

        while(qry.next())
        {
            retrievedCustomer->setId(qry.value(0).toInt());
            retrievedCustomer->setCompanyName(qry.value(1).toString());
            retrievedCustomer->setFirstName(qry.value(2).toString());
            retrievedCustomer->setLastName(qry.value(3).toString());
            retrievedCustomer->setPhoneNumber(qry.value(4).toString());
        }

    } else {
        return NULL;
    }


    return retrievedCustomer;
}

QString DatabaseManager::updateCustomer(Customer customer, QString origName) {

    QSqlQuery qry;

    if(db.isOpen() == false)
        if(db.open() == false)
            return db.lastError().text();

    if(! qry.exec("update customer set companyName='"+customer.getCompanyName()+"', firstName='"+customer.getFirstName()+"', lastName='"+customer.getLastName()+"', phoneNumber='"+customer.getPhoneNumber()+"' where companyName='"+origName+"' "))
    {
        return qry.lastError().text();
    }

    // Update invoice companyName if the name changed
    if(customer.getCompanyName() != origName) {
        if(! qry.exec("update invoice set companyName='"+customer.getCompanyName()+"' where companyName='"+origName+"' "))
        {
            return qry.lastError().text();
        }
    }

    return NULL;
}
