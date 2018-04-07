#ifndef CCUSTOMMESSAGEBOX_H
#define CCUSTOMMESSAGEBOX_H
#define LAYOUT_SPACING 20
#define DEFAULT_HEIGHT  (160)
#define DEFAULT_WIDTH   (350)
#define MIN_WEIGHT      (100)
#define MIN_WIDTH       (150)
#define FONT_SIZE       (14)
#include <QObject>
#include <QDialog>
#include<QLabel>
#include<QToolButton>
#include<QWidget>
#include<QString>
class CCustomMessageBox : public QDialog
{
    Q_OBJECT
public:
    enum CUSTOM_MESSAGE_TYPE{
         CUSTOM_MESSAGE_NOICON = 0,  /**< �� */
         CUSTOM_MESSAGE_QUESTION,    /**< ѯ�� */
         CUSTOM_MESSAGE_INFORMATION, /**< ��Ϣ */
         CUSTOM_MESSAGE_WARNING,     /**< ���� */
         CUSTOM_MESSAGE_CRITICAL,   /**< ���� */
     };
    CCustomMessageBox(CUSTOM_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo,QWidget *parent = 0,
                         Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowTitleHint);



    ~CCustomMessageBox();

    void setTextInfo(const QString &strInfo);
    void setTextInfo(const QString &strTitle, const QString &strInfo);

       /**
        * @brief ����һ�����غ���
        * @see CCustomMessageBox::setTextInfo
        * @param type[in] ��Ϣ������
        * @param strTitle [in] ����
        * @param strInfo [in] ��Ϣ����
        */
       void setTextInfo(CUSTOM_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo);

   private:
       /**
        * @brief ��ʼ��
        * @param strInfo [in] ��Ϣ����
        */
       void initialize(const QString &strInfo);

       /**
        * @brief ����
        */
       void alignment();
       void paintEvent(QPaintEvent *event);


   private:
       QLabel *m_pLabelIcon;  /**< ��ʾ��Ϣ����ͼ�� */
       QLabel *m_pLabelInfo;  /**< ��ʾ��Ϣ */
       QToolButton *m_pBtnYes; /**< �ǣ�ȷ������Ť */
       QToolButton *m_pBtnNo;  /**< ��ȡ������Ť */
       CUSTOM_MESSAGE_TYPE m_eCustomType; /**< �Զ�������  */
    };

#endif // CCUSTOMMESSAGEBOX_H
