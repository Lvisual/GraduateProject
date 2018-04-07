#include "employeemodel.h"

int Employee::id() const
{
    return m_id;
}

void Employee::setId(int id)
{
    m_id = id;
}

QString Employee::name() const
{
    return m_name;
}

void Employee::setName(const QString &name)
{
    m_name = name;
}

int Employee::age() const
{
    return m_age;
}

void Employee::setAge(int age)
{
    m_age = age;
}

QString Employee::sex() const
{
    return m_sex;
}

void Employee::setSex(const QString &sex)
{
    m_sex = sex;
}

QString Employee::phone() const
{
    return m_phone;
}

void Employee::setPhone(const QString &phone)
{
    m_phone = phone;
}

QString Employee::address() const
{
    return m_address;
}

void Employee::setAddress(const QString &address)
{
    m_address = address;
}

QString Employee::remark() const
{
    return m_remark;
}

void Employee::setRemark(const QString &remark)
{
    m_remark = remark;
}



employeeModel::employeeModel(const int totalColumn, const int aColumnNumWithChechBox, QObject *parent)
:totalColumn(totalColumn),colNumberWithCheckBox(aColumnNumWithChechBox),
QAbstractTableModel(parent)
{
    //dao = new BaseStationDao();
    //rowCheckStateMap.clear();

}

int employeeModel::rowCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }

    return m_employeeVec.size();
}


//返回数据的列数
int employeeModel::columnCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }
    return totalColumn;
}

QVariant employeeModel::data( const QModelIndex &index, int role ) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return QString::number(index.row()+1);
        if (index.column() == 1)
            return m_employeeVec[index.row()].id();
        if (index.column() == 2)
            return m_employeeVec[index.row()].name();
        if (index.column() == 3)
            return m_employeeVec[index.row()].age();
        if (index.column() == 4)
            return m_employeeVec[index.row()].sex();
        if(index.column() == 5)
            return m_employeeVec[index.row()].phone();
         if(index.column()== 6)
            return m_employeeVec[index.row()].address();
        if(index.column() ==7)
            return m_employeeVec[index.row()].remark();
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


QVariant employeeModel::headerData( int section, Qt::Orientation orientation, int role ) const
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
            return QStringLiteral("员工年龄");
        if (section == 4)
            return QStringLiteral("员工性别");
        if (section == 5)
            return QStringLiteral("员工联系方式");
        if (section == 6)
            return QStringLiteral("员工住址");
        if (section == 7)
            return QStringLiteral("员工备注");
        if (section == 8)
            return QStringLiteral("多选");
    }
    return QVariant();
}


Qt::ItemFlags employeeModel::flags( const QModelIndex &index ) const
{
    if(!index.isValid())
        return 0;
    if (index.column() == colNumberWithCheckBox)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


bool employeeModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if(!index.isValid())
        return false;
    if (role == Qt::CheckStateRole && index.column() == colNumberWithCheckBox)
    {
        if (value == Qt::Checked) //
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            if(m_employeeVec.size() > index.row())
            emit EmployeeIsChecked(m_employeeVec[index.row()]);
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
        }
    }
    return true;
}


void employeeModel:: removeRow(int row){
    m_employeeVec.erase(m_employeeVec.begin()+row); //从vector删除第row行
}

void employeeModel::appendEmployeeInfos(const QVector<Employee> &infos){
    m_employeeVec.clear();
    m_employeeVec.append(infos);
}

void employeeModel::addEmployeeInfo( const Employee &info )
{
    //dao->insert(baseInfo);
    m_employeeVec.push_back(info);  //把基站信息加入到要baseInfos容器中。
    freshModel();
}


  void employeeModel::freshModel(){
      beginResetModel();//开始初始化BaseModel，接着QTableView将重新显示
      endResetModel();//显示baseInfo容器中的学生信息
  }

