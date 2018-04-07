#ifndef BASETYPDEMODEL_H
#define BASETYPDEMODEL_H

#include <QObject>
#include<QAbstractTableModel>

class baseTypeInfo{
public:
    void setBaseTypeId(QString id){typeId = id;}
    QString getTypeId()const {return typeId;}
    void setBaseTypeName(QString name){typeName=name;}
    QString getTypeName() const{return typeName;}
    void setBaseTypeRemark(QString remark){typeRemark=remark;}
    QString getTypeRemark() const{return typeRemark;}
private:
    QString typeId;
    QString typeName;
    QString typeRemark;
};


class baseTypeModel : public QAbstractTableModel
{
    Q_OBJECT
public:
   baseTypeModel(const int totalColumn, const int aColumnNumWithChechBox = 0, QObject *parent = 0);

public:
    typedef QVector<baseTypeInfo> baseTypeInfos;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    baseTypeInfos getTypeBaseInfo(){
        return this->baseTypeInfoVec;
    }

public:
    void AddBaseTypeInfo(const baseTypeInfo &baseInfo);
    void appendBaseTypeInfos(const QVector<baseTypeInfo> &infos);
    void removeRow(int row);
    void freshModel();
    signals:
    void BaseTypeInfoIsChecked(const baseTypeInfo &baseInfo);
private:
    baseTypeInfos baseTypeInfoVec;
    int totalColumn;
    int colNumberWithCheckBox;
    //BaseStationDao *dao;

public:
    QMap<int, Qt::CheckState> rowCheckStateMap;
};

#endif // BASETYPDEMODEL_H
