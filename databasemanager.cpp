#include "databasemanager.h"

DatabaseManager::DatabaseManager()
{
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
    path.append(QDir::separator()).append("DocuPrint.db.sqlite");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
#else
    // NOTE: File exists in the application private folder, in Symbian Qt implementation
    db.setDatabaseName("DocuPrint.db.sqlite");
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
    path.append(QDir::separator()).append("my.db.sqlite");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
#else

    // Remove created database binary file
    return QFile::remove("my.db.sqlite");
#endif
}

QString DatabaseManager::createCustomerAndInvoiceTables()
{

    if(db.isOpen() == false)
        return "The database is not open";


    QSqlQuery query;
    bool ret = query.exec("create table if not exists customer( "
                     "companyId INTEGER PRIMARY KEY NOT NULL, "
                     "companyName VARCHAR(25) NOT NULL UNIQUE, "
                     "firstName VARCHAR(20), "
                     "lastName VARCHAR(20), "
                     "phoneNumber VARCHAR(20) )");

    if(ret == false)
        return query.lastError().text();

    QSqlQuery query2;
    bool ret2 = query2.exec("create table if not exists invoice( "
                       "invoiceId INTEGER PRIMARY KEY NOT NULL, "
                       "companyName VARCHAR(25), "
                       "date TEXT, "
                       "cost FLOAT, "
                       "comments VARCHAR(225), "
                       "inheritId INTEGER NOT NULL REFERENCES customer(companyId) )");

    if(ret2 == false)
        return query2.lastError().text();


    return NULL;
}

QSqlQueryModel* DatabaseManager::loadCustomerList() {

    QSqlQueryModel *modal = new QSqlQueryModel();
    QSqlQuery *query = new QSqlQuery();

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

    query->prepare("select date, cost, comments from invoice");

    if( !query->exec() ) {
        return NULL;
    }

    modal->setQuery(*query);
    return modal;

}

QString DatabaseManager::addCustomer(Customer customer) {

    QSqlQuery qry;

    if(db.isOpen() == false)
        return "The databse is not open";

    if( !qry.exec("insert into customer (companyName, firstName, lastName, phoneNumber) values ('"+customer.getCompanyName()+"', '"+customer.getFirstName()+"', '"+customer.getLastName()+"', '"+customer.getPhoneNumber()+"')") )
    {
        return qry.lastError().text();
    }


    return NULL;
}

QString DatabaseManager::updateCustomer(Customer customer) {

    QSqlQuery qry;

    if(db.isOpen() == false)
        return "The databse is not open";

    if(! qry.exec("update customer set companyName='"+customer.getCompanyName()+"', firstName='"+customer.getFirstName()+"', lastName='"+customer.getLastName()+"', phoneNumber='"+customer.getPhoneNumber()+"' where companyId='"+customer.getId()+"' "))
    {
        return qry.lastError().text();
    }

    return NULL;
}
