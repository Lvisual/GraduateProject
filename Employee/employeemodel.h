#ifndef EMPLOYEEMODEL_H
#define EMPLOYEEMODEL_H

#include <QObject>
#include<QString>
#include<QAbstractTableModel>
class Employee{

public:

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    int age() const;
    void setAge(int age);

    QString sex() const;
    void setSex(const QString &sex);

    QString phone() const;
    void setPhone(const QString &phone);

    QString address() const;
    void setAddress(const QString &address);

    QString remark() const;
    void setRemark(const QString &remark);

private:
    int m_id;
    QString m_name;
    int m_age;
    QString m_sex;
    QString m_phone;
    QString m_address;
    QString m_remark;
};

class employeeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
   employeeModel(const int totalColumn, const int aColumnNumWithChechBox = 0, QObject *parent = 0);

public:
    typedef QVector<Employee>employeeVec;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    employeeVec getEmployeeVec(){
        return this->m_employeeVec;
    }

public:
    void addEmployeeInfo(const Employee &employeeInfo);
    void appendEmployeeInfos(const QVector<Employee> &infos);
    void removeRow(int row);
    void freshModel();
    signals:
    void EmployeeIsChecked(const Employee &employeeInfo);
private:
    employeeVec m_employeeVec;
    int totalColumn;
    int colNumberWithCheckBox;
    //BaseStationDao *dao;

public:
    QMap<int, Qt::CheckState> rowCheckStateMap;
};

#endif // EMPLOYEEMODEL_H
