#ifndef MDFFILEINFODIALOG_H
#define MDFFILEINFODIALOG_H

#include <QDialog>

namespace Ui {
class MDFFileInfoDialog;
}

class MDFFileInfoDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MDFFileInfoDialog(QString& fileName, QString* fileID, QString* formatID, QString* programID, unsigned short byteOrder,
                               unsigned short versionNumber, QString* date, QString* time, QString* author, QString* organization,
                               QString* projectName, QString* measurementObjectId, QString* comment, QWidget *parent = 0);
    ~MDFFileInfoDialog();

private:
    Ui::MDFFileInfoDialog *ui;
};

#endif // MDFFILEINFODIALOG_H
