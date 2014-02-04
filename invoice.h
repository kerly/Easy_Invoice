#ifndef INVOICE_H
#define INVOICE_H

#include <QDateTime>

class Invoice
{
public:
    Invoice();
    Invoice(QString companyName);
    ~Invoice();

    int getId();
    void setId(int id);
    QString getDateString();
    QDateTime getDateTime();
    void setDateTime(QDateTime dTime);
    QString getCompanyName();
    void setCompanyName(QString cName);
    QString getCost();
    void setCost(QString cost);
    QString getComments();
    void setComments(QString comments);

private:
    int _id;
    QDateTime _date;
    QString _companyName;
    QString _cost;
    QString _comments;

};

#endif // INVOICE_H
