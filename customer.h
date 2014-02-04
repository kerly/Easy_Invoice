#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

class Customer
{
public:
    Customer();
    ~Customer();

    // Getters and setters
    int getId();
    void setId(int id);
    QString getCompanyName();
    void setCompanyName(QString cName);
    QString getFirstName();
    void setFirstName(QString fName);
    QString getLastName();
    void setLastName(QString lName);
    QString getPhoneNumber();
    void setPhoneNumber(QString pNumber);


private:
    int _id;
    QString _companyName = NULL;
    QString _firstName;
    QString _lastName;
    QString _phoneNumber;
};

#endif // CUSTOMER_H
