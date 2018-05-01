#ifndef LABELMODEL_H
#define LABELMODEL_H
#include<QObject>
#include<QAbstractTableModel>
#include<QPushButton>
class Label{

public:
    int employeeId() const;
    void setEmployeeId(int employeeId);

    int lableId() const;
    void setLableId(int lableId);

    QString charge() const;
    void setCharge(const QString &charge);

    QString state() const;
    void setState(const QString &state);

    QString remark() const;
    void setRemark(const QString &remark);

    QString labelName() const;
    void setLabelName(const QString &labelName);

private:
    int m_employeeId;
    int m_lableId;
    QString m_labelName;
    QString m_charge;
    QString m_state;
    QString m_remark;
};


class LabelModel : public QAbstractTableModel
{
    Q_OBJECT
public:
   LabelModel(const int totalColumn, const int aColumnNumWithChechBox = 0, QObject *parent = 0);

public:
    typedef QVector<Label>labelVec;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    labelVec getLabelVec(){
        return this->m_labelVec;
    }

public:
    void addLabelInfo(const Label &labelInfo);
    void appendLabelInfos(const QVector<Label> &infos);
    void removeRow(int row);
    void freshModel();
    signals:
    void LabelIsChecked(const Label &labelInfo);
private:
    labelVec m_labelVec;
    int totalColumn;
    int colNumberWithCheckBox;
    QPushButton m_btn;
    //BaseStationDao *dao;

public:
    QMap<int, Qt::CheckState> rowCheckStateMap;
};

#endif // LABELMODEL_H
