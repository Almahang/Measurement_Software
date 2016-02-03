#include "mdffileinfodialog.h"
#include "ui_mdffileinfodialog.h"

MDFFileInfoDialog::MDFFileInfoDialog(QString &fileName, QString *fileID, QString *formatID, QString *programID, unsigned short byteOrder, unsigned short versionNumber, QString *date, QString *time, QString *author, QString *organization, QString *projectName, QString *measurementObjectId, QString *comment, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MDFFileInfoDialog)
{
    ui->setupUi(this);
    ui->label_14->setText(fileName);
    ui->label_15->setText(*fileID);
    ui->label_16->setText(*formatID);
    ui->label_17->setText(*programID);
    ui->label_18->setText(QString::number(byteOrder));
    ui->label_19->setText(QString::number(versionNumber));
    ui->label_20->setText(*date);
    ui->label_21->setText(*time);
    ui->label_22->setText(*author);
    ui->label_23->setText(*organization);
    ui->label_24->setText(*projectName);
    ui->label_25->setText(*measurementObjectId);
    ui->plainTextEdit->appendPlainText(*comment); //comment

    this->setWindowTitle(QString("MDF file info"));
    ui->pushButton->setFocus();
}

MDFFileInfoDialog::~MDFFileInfoDialog()
{
    delete ui;
}


