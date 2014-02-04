#include "customer.h"
#include "invoice.h"

Customer::Customer()
{
}
Customer::~Customer()
{
}

int Customer::getId(){
    return _id;
}
void Customer::setId(int id) {
    _id = id;
}

QString Customer::getCompanyName() {
    return _companyName;
}
void Customer::setCompanyName(QString cName) {
    _companyName = cName;
}

QString Customer::getFirstName() {
    return _firstName;
}
void Customer::setFirstName(QString fName) {
    _firstName = fName;
}

QString Customer::getLastName() {
    return _lastName;
}
void Customer::setLastName(QString lName) {
    _lastName = lName;
}

QString Customer::getPhoneNumber() {
    return _phoneNumber;
}
void Customer::setPhoneNumber(QString pNumber) {
    _phoneNumber = pNumber;
}

