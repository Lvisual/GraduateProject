#include "labelmodel.h"
#include<QString>

int Label::employeeId() const
{
return m_employeeId;
}

void Label::setEmployeeId(int employeeId)
{
m_employeeId = employeeId;
}

int Label::lableId() const
{
return m_lableId;
}

void Label::setLableId(int lableId)
{
m_lableId = lableId;
}

QString Label::charge() const
{
return m_charge;
}

void Label::setCharge(const QString &charge)
{
m_charge = charge;
}

QString Label::state() const
{
return m_state;
}

void Label::setState(const QString &state)
{
m_state = state;
}

QString Label::remark() const
{
return m_remark;
}

void Label::setRemark(const QString &remark)
{
m_remark = remark;
}



LabelModel::LabelModel(const int totalColumn, const int aColumnNumWithChechBox, QObject *parent)
:totalColumn(totalColumn),colNumberWithCheckBox(aColumnNumWithChechBox),
QAbstractTableModel(parent)
{
    m_btn.setText(QString::fromLocal8Bit("�鿴����"));
    //dao = new BaseStationDao();
    //rowCheckStateMap.clear();

}

int LabelModel::rowCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }

    return m_labelVec.size();
}


//�������ݵ�����
int LabelModel::columnCount( const QModelIndex &parent ) const
{
    if (parent.isValid()){
        return 0;
    }
    return totalColumn;
}

QVariant LabelModel::data( const QModelIndex &index, int role ) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 1)
            return QString::number(index.row()+1);
        if (index.column() == 2)
            return m_labelVec[index.row()].lableId();
        if (index.column() == 3)
            return m_labelVec[index.row()].employeeId();
        if (index.column() == 4)
            return m_labelVec[index.row()].charge();
        if (index.column() == 5)
            return m_labelVec[index.row()].state();
        if(index.column() == 6)
            return m_labelVec[index.row()].remark();
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


QVariant LabelModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == 0)
            return QString::fromLocal8Bit("��ѡ");
        if (section == 1)
            return QString::fromLocal8Bit("���");
        if (section == 2)
            return QString::fromLocal8Bit("��ǩID");
        if (section == 3)
            return QString::fromLocal8Bit("Ա��ID");
        if (section == 4)
            return QString::fromLocal8Bit("����");
        if (section == 5)
            return QString::fromLocal8Bit("����״̬");
        if (section == 6)
            return QString::fromLocal8Bit("��ע");
        if(section == 7)
            return QString::fromLocal8Bit("����");

    }
    return QVariant();
}


Qt::ItemFlags LabelModel::flags( const QModelIndex &index ) const
{
    if(!index.isValid())
        return 0;
    if (index.column() == colNumberWithCheckBox)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;

    return  Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


bool LabelModel::setData( const QModelIndex &index, const QVariant &value, int role )
{
    if(!index.isValid())
        return false;
    if (role == Qt::CheckStateRole && index.column() == colNumberWithCheckBox)
    {
        if (value == Qt::Checked) //
        {
            rowCheckStateMap[index.row()] = Qt::Checked;
            if(m_labelVec.size() > index.row())
            emit LabelIsChecked(m_labelVec[index.row()]);
        }
        else
        {
            rowCheckStateMap[index.row()] = Qt::Unchecked;
        }
    }
    return true;
}


void LabelModel:: removeRow(int row){
    m_labelVec.erase(m_labelVec.begin()+row); //��vectorɾ����row��
}

void LabelModel::appendLabelInfos(const QVector<Label> &infos){
    m_labelVec.clear();
    m_labelVec.append(infos);
}

void LabelModel::addLabelInfo( const Label &info )
{
    //dao->insert(baseInfo);
    m_labelVec.push_back(info);  //�ѻ�վ��Ϣ���뵽ҪbaseInfos�����С�
    freshModel();
}

  void LabelModel::freshModel(){
      beginResetModel();//��ʼ��ʼ��BaseModel������QTableView��������ʾ
      endResetModel();//��ʾbaseInfo�����е�ѧ����Ϣ
  }





















