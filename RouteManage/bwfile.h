#ifndef BWFILE_H
#define BWFILE_H
#define max1 100
#include <QString>
class BwFile
{
public:
    BwFile();
    void readFile(QString filename);
    void writeFile(QString filename);
    QString* getBuffer();
    int getRow();
private:
    QString  m_buffer[max1];
    int m_row;
};

#endif // BWFILE_H
