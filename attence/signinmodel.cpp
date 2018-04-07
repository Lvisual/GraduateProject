#include "signinmodel.h"

int SignIn::id() const
{
    return m_id;
}

void SignIn::setId(int id)
{
    m_id = id;
}

QString SignIn::name() const
{
    return m_name;
}

void SignIn::setName(const QString &name)
{
    m_name = name;
}

QString SignIn::agent() const
{
    return m_agent;
}

void SignIn::setAgent(const QString &agent)
{
    m_agent = agent;
}

QString SignIn::signdate() const
{
    return m_signdate;
}

void SignIn::setSigndate(const QString &signdate)
{
    m_signdate = signdate;
}

QString SignIn::signtime() const
{
    return m_signtime;
}

void SignIn::setSigntime(const QString &signtime)
{
    m_signtime = signtime;
}

QString SignIn::status() const
{
    return m_status;
}

void SignIn::setStatus(const QString &status)
{
    m_status = status;
}

QString SignIn::remark() const
{
    return m_remark;
}

void SignIn::setRemark(const QString &remark)
{
    m_remark = remark;
}


SignInModel::SignInModel(const int totalColumn, const int aColumnNumWithChechBox, QObject *parent)
:totalColumn(totalColumn),colNumberWithCheckBox(aColumnNumWithChechBox),
QAbstractTableModel(parent)
{
    //dao = new BaseStationDao();
    //rowCheckStateMap.clear();

}

int SignInModel::rowCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }

    return m_signinVec.size();
}


//返回数据的列数
int SignInModel::columnCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }
    return totalColumn;
}

QVariant SignInModel::data( const QModelIndex &index, int role ) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return QString::number(index.row()+1);
        if (index.column() == 1)
            return m_signinVec[index.row()].id();
        if (index.column() == 2)
            return m_signinVec[index.row()].name();
        if (index.column() == 3)
            return m_signinVec[index.row()].agent();
        if (index.column() == 4)
            return m_signinVec[index.row()].signdate();
        if(index.column() == 5)
            return m_signinVec[index.row()].signtime();
         if(index.column()== 6)
            return m_signinVec[index.row()].status();
        if(index.column() ==7)
            return m_signinVec[index.row()].remark();
    }

    if (role == Qt::CheckStateRole) {
        if(index.column() == colNumberWithCheckBox) {
        if(rowCheckStateMap.contains(index.row()))
            return rowCheckStateMap[index.row()] == Qt::Checked ? Qt::Checked : Qt::Unchecked;
        return Qt::Unchecked;
        }
    }
    return QVariant();
}


QVariant SignInModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
            return QStringLiteral("序号");
        if (section == 1)
            return QStringLiteral("员工ID");
        if (section == 2)
            return QStringLiteral("员工姓名");
        if (section == 3)
            return QStringLiteral("员工部门");
        if (section == 4)
            return QStringLiteral("签到日期");
        if (section == 5)
            return QStringLiteral("签到时间");
        if (section == 6)
            return QStringLiteral("状态");
        if (section == 7)
            return QStringLiteral("备注");
        if (section == 8)
            return QStringLiteral("选择");
    }
    return QVariant();
}


Qt::ItemFlags SignInModel::flags( const QModelIndex &index ) const
{
    if(!index.isValid())
        return 0;
    if (index.column() == colNumberWithCheckBox)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


bool SignInModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if(!index.isValid())
        return false;
    if (role == Qt::CheckStateRole && index.column() == colNumberWithCheckBox)
    {
        if (value == Qt::Checked) //
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            if(m_signinVec.size() > index.row())
            emit SigninIsChecked(m_signinVec[index.row()]);
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
        }
    }
    return true;
}


void SignInModel:: removeRow(int row){
    m_signinVec.erase(m_signinVec.begin()+row); //从vector删除第row行
}

void SignInModel::appendsigninInfos(const QVector<SignIn> &infos){
    m_signinVec.clear();
    m_signinVec.append(infos);
}

void SignInModel::addsigninInfo( const SignIn &info )
{
    //dao->insert(baseInfo);
    m_signinVec.push_back(info);  //把基站信息加入到要baseInfos容器中。
    freshModel();
}


  void SignInModel::freshModel(){
      beginResetModel();//开始初始化BaseModel，接着QTableView将重新显示
      endResetModel();//显示baseInfo容器中的学生信息
  }
