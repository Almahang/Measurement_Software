#ifndef MEASURINGWINDOW_H
#define MEASURINGWINDOW_H

#include <QtCore>
#include <QMainWindow>
#include <QMdiSubWindow>
#include <QKeyEvent>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>

#include <widgeta.h>
#include <widgetb.h>

#include "signalselect.h"
#include "MDF/MDFLib.h"
#include "mysignal.h"
#include "mdffileinfodialog.h"
#include "modelmanager.h"

/* for debug */
#include <QDebug>

namespace Ui {
class MeasuringWindow;
}

class MeasuringWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MeasuringWindow(QWidget *parent = 0);
    ~MeasuringWindow();

private:
    Ui::MeasuringWindow *ui;
    MDFlib::MDF *mdf;
    char percent;
    SignalSelect *signalSelectDialog;
    QMdiSubWindow *signalWindow;
    WidgetA *signalWidget;
    QMdiSubWindow *graphicWindow;
    WidgetB *graphicWidget;

    void initSignals();
    QMap<QString, mySignal*>* allSignal;
    QList<QString> signalNameList;
    QStringList selectedSignals;
    QStringList notSelectedSignals;
    QString m_fileNameMDF;

    void openMDF(QString name);
    void openProfile(QString path);
    void saveProfile(QString path);
    void init();
    
private slots:

    void on_actionSelect_Signals_triggered();
    void on_actionSignal_window_triggered();
    void on_actionGraphic_Window_triggered();
    void on_actionMDF_file_info_triggered();
    void on_actionOpen_MDF_file_triggered();

    void on_actionClose_triggered();

    void on_actionAlign_windows_triggered();

    void on_actionSaveProfile_triggered();

    void on_actionLoadProfile_triggered();

    void on_actionExportProfile_triggered();

    void on_actionImportProfile_triggered();

    void on_actionCloseProfile_triggered();

public slots:
    void addSignal();

signals:
    void closeSignal();
};

#endif // MEASURINGWINDOW_H
