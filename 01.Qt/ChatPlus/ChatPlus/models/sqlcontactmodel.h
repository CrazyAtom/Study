#pragma once

#ifndef __SQLCONTACTMODEL_H__
#define __SQLCONTACTMODEL_H__

#include <QSqlQueryModel>

class SqlContactModel : public QSqlQueryModel
{
public:
    explicit SqlContactModel(QObject *parent = Q_NULLPTR);
};

#endif // __SQLCONTACTMODEL_H__
