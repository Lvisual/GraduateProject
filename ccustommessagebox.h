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
         CUSTOM_MESSAGE_NOICON = 0,  /**< 无 */
         CUSTOM_MESSAGE_QUESTION,    /**< 询问 */
         CUSTOM_MESSAGE_INFORMATION, /**< 信息 */
         CUSTOM_MESSAGE_WARNING,     /**< 警告 */
         CUSTOM_MESSAGE_CRITICAL,   /**< 错误 */
     };
    CCustomMessageBox(CUSTOM_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo,QWidget *parent = 0,
                         Qt::WindowFlags flags = Qt::CustomizeWindowHint | Qt::WindowTitleHint);



    ~CCustomMessageBox();

    void setTextInfo(const QString &strInfo);
    void setTextInfo(const QString &strTitle, const QString &strInfo);

       /**
        * @brief 这是一个重载函数
        * @see CCustomMessageBox::setTextInfo
        * @param type[in] 消息的类型
        * @param strTitle [in] 标题
        * @param strInfo [in] 信息内容
        */
       void setTextInfo(CUSTOM_MESSAGE_TYPE type, const QString &strTitle, const QString &strInfo);

   private:
       /**
        * @brief 初始化
        * @param strInfo [in] 信息内容
        */
       void initialize(const QString &strInfo);

       /**
        * @brief 布局
        */
       void alignment();
       void paintEvent(QPaintEvent *event);


   private:
       QLabel *m_pLabelIcon;  /**< 提示信息类型图标 */
       QLabel *m_pLabelInfo;  /**< 提示信息 */
       QToolButton *m_pBtnYes; /**< 是（确定）按扭 */
       QToolButton *m_pBtnNo;  /**< 否（取消）按扭 */
       CUSTOM_MESSAGE_TYPE m_eCustomType; /**< 自定义类型  */
    };

#endif // CCUSTOMMESSAGEBOX_H
