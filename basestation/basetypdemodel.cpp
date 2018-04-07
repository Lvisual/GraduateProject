#include "basetypdemodel.h"

baseTypeModel::baseTypeModel(const int totalColumn, const int aColumnNumWithChechBox, QObject *parent)
:totalColumn(totalColumn),colNumberWithCheckBox(aColumnNumWithChechBox),
QAbstractTableModel(parent)
{
    //dao = new BaseStationDao();
    //rowCheckStateMap.clear();

}


int baseTypeModel::rowCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }

    return baseTypeInfoVec.size();
}


//返回数据的列数
int baseTypeModel::columnCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }
    return totalColumn;
}

QVariant baseTypeModel::data( const QModelIndex &index, int role ) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return QString::number(index.row()+1);
        if (index.column() == 1)
            return baseTypeInfoVec[index.row()].getTypeId();
        if (index.column() == 2)
            return baseTypeInfoVec[index.row()].getTypeName();
        if (index.column() == 3)
            return baseTypeInfoVec[index.row()].getTypeRemark();
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


QVariant baseTypeModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
            return QStringLiteral("序号");
        if (section == 1)
            return QStringLiteral("基站类型ID");
        if (section == 2)
            return QStringLiteral("基站名称");
        if (section == 3)
            return QStringLiteral("基站类型备注");
        if (section == 4)
            return QStringLiteral("多选");
    }
    return QVariant();
}


Qt::ItemFlags baseTypeModel::flags( const QModelIndex &index ) const
{
    if(!index.isValid())
        return 0;
    if (index.column() == colNumberWithCheckBox)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


bool baseTypeModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if(!index.isValid())
        return false;
    if (role == Qt::CheckStateRole && index.column() == colNumberWithCheckBox)
    {
        if (value == Qt::Checked) //
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            if(baseTypeInfoVec.size() > index.row())
            emit BaseTypeInfoIsChecked(baseTypeInfoVec[index.row()]);
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
        }
    }
    return true;
}


void baseTypeModel:: removeRow(int row){
    baseTypeInfoVec.erase(baseTypeInfoVec.begin()+row); //从vector删除第row行
}

void baseTypeModel::appendBaseTypeInfos(const QVector<baseTypeInfo> &infos){
    baseTypeInfoVec.clear();
    baseTypeInfoVec.append(infos);
}

void baseTypeModel::AddBaseTypeInfo( const baseTypeInfo &baseInfo )
{
    //dao->insert(baseInfo);
    baseTypeInfoVec.push_back(baseInfo);  //把基站信息加入到要baseInfos容器中。
    freshModel();
}


  void baseTypeModel::freshModel(){

      beginResetModel();//开始初始化BaseModel，接着QTableView将重新显示
      endResetModel();//显示baseInfo容器中的学生信息
  }
