#ifndef SIGNALSELECT_H
#define SIGNALSELECT_H

#include <QtCore>
#include <QDialog>
#include <QCheckBox>
#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QDebug>

namespace Ui {
class SignalSelect;
}

class SignalSelect : public QDialog
{
    Q_OBJECT
    
public:
    explicit SignalSelect(QStringList & selectedSignals, QStringList & notSelectedSignals, QWidget *parent = 0);
    ~SignalSelect();

private:
    Ui::SignalSelect *ui;
    QStringList m_notSelectedSignals;
    QStringList m_selectedSignals;
    QStringList m_filteredSignals;
    QStringList *m_oldNotSelectedSignals;
    QStringList *m_oldSelectedSignals;
    QModelIndex refreshWidgets(QModelIndex index);
    QModelIndex updateWidgets(QModelIndex index, bool select);
    void keyPressEvent(QKeyEvent* event);

private slots:

    void on_checkBox_clicked();                             //case sensitive filtering

    //here
    void on_addToListButton_clicked();

    void on_removeFromListButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_okButton_clicked();

    void on_findEdit_textChanged(const QString &arg1);

    void on_clearSelectedButton_clicked();

signals:
    void updateSignalsSignal();
};

#endif // SIGNALSELECT_H
