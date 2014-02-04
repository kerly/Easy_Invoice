#include "invoice.h"

// CONSTRUCTORS / DESTRUCTOR
Invoice::Invoice()
{
}
Invoice::Invoice(QString companyName)
{
    _companyName = companyName;
}
Invoice::~Invoice()
{
}

int Invoice::getId(){
    return _id;
}
void Invoice::setId(int id){
    _id = id;
}

QString Invoice::getDateString() {
    return _date.toString();
}

QDateTime Invoice::getDateTime(){
    return _date;
}

void Invoice::setDateTime(QDateTime dTime){
    _date = dTime;
}

QString Invoice::getCompanyName(){
    return _companyName;
}

void Invoice::setCompanyName(QString cName){
    _companyName = cName;
}

QString Invoice::getCost(){
    return _cost;
}

void Invoice::setCost(QString cost){
    _cost = cost;
}

QString Invoice::getComments(){
    return _comments;
}

void Invoice::setComments(QString comments){
    _comments = comments;
}
