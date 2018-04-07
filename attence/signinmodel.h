#ifndef SIGNINMODEL_H
#define SIGNINMODEL_H

#include <QObject>
#include<QString>
#include<QAbstractTableModel>
class SignIn{

public:

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString agent() const;
    void setAgent(const QString &agent);

    QString signdate() const;
    void setSigndate(const QString &signdate);

    QString signtime() const;
    void setSigntime(const QString &signtime);

    QString status() const;
    void setStatus(const QString &status);

    QString remark() const;
    void setRemark(const QString &remark);

private:
    int m_id;
    QString m_name;
    QString m_agent;
    QString m_signdate;
    QString m_signtime;
    QString m_status;
    QString m_remark;
};

class SignInModel : public QAbstractTableModel
{
    Q_OBJECT
public:
   SignInModel(const int totalColumn, const int aColumnNumWithChechBox = 0, QObject *parent = 0);

public:
    typedef QVector<SignIn>signinVec;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    signinVec getsigninVec(){
        return this->m_signinVec;
    }

public:
    void addsigninInfo(const SignIn &signinInfo);
    void appendsigninInfos(const QVector<SignIn> &infos);
    void removeRow(int row);
    void freshModel();
    signals:
    void SigninIsChecked(const SignIn &signinInfo);
private:
    signinVec m_signinVec;
    int totalColumn;
    int colNumberWithCheckBox;
    //BaseStationDao *dao;

public:
    QMap<int, Qt::CheckState> rowCheckStateMap;
};


#endif // SIGNINMODEL_H
