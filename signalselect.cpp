#include "signalselect.h"
#include "ui_signalselect.h"

SignalSelect::SignalSelect(QStringList & selectedSignals, QStringList & notSelectedSignals, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignalSelect)
{
    ui->setupUi(this);

    m_oldSelectedSignals = &selectedSignals;
    notSelectedSignals.sort(Qt::CaseInsensitive);
    m_oldNotSelectedSignals = &notSelectedSignals;

    m_selectedSignals = selectedSignals;
    m_notSelectedSignals = notSelectedSignals;
    m_filteredSignals = notSelectedSignals;

    refreshWidgets(ui->allSignalsWidget->currentIndex());

    ui->allSignalsWidget->setAlternatingRowColors(true);
    ui->allSignalsWidget->setToolTip("Choose the signals, which you want to see.");

    ui->selectedSignalsWidget->setAlternatingRowColors(true);
    ui->selectedSignalsWidget->setToolTip("Selected signals.");

    ui->allSignalsWidget->setUniformItemSizes(true);
    ui->selectedSignalsWidget->setUniformItemSizes(true);

    ui->findEdit->setFocus();

    this->setWindowTitle("Select signals");

    connect(ui->allSignalsWidget, SIGNAL(doubleClicked(QModelIndex)), ui->addToListButton, SLOT(click()));
    connect(ui->selectedSignalsWidget, SIGNAL(doubleClicked(QModelIndex)), ui->removeFromListButton, SLOT(click()));
}

SignalSelect::~SignalSelect()
{
    delete ui;
}

QModelIndex SignalSelect::refreshWidgets(QModelIndex index)
{
    ui->allSignalsWidget->clear();
    ui->selectedSignalsWidget->clear();
    ui->allSignalsWidget->addItems(m_filteredSignals);
    ui->selectedSignalsWidget->addItems(m_selectedSignals);
    return index;
}

QModelIndex SignalSelect::updateWidgets(QModelIndex index, bool select)
{
    if(select) // add signal to selected list
    {
        QString str = m_filteredSignals.at(index.row());

        m_notSelectedSignals.removeOne(str);
        m_filteredSignals.removeOne(str);
        m_selectedSignals.append(str);
    }
    else // remove signal from selected list
    {
        QString str = m_selectedSignals.at(index.row());
        m_selectedSignals.removeOne(str);
        m_notSelectedSignals.append(str);
        emit on_findEdit_textChanged(ui->findEdit->text());
    }
    refreshWidgets(index);
    if(!index.isValid()) index = index.sibling(index.row() - 1, index.column());
    return index;
}

void SignalSelect::keyPressEvent(QKeyEvent* event)
{
    if((event->modifiers().testFlag(Qt::ControlModifier)) && (event->key() == Qt::Key_F))
    {
        ui->findEdit->setFocus();
        ui->findEdit->selectAll();
    }
}

void SignalSelect::on_checkBox_clicked()                        //case sensitive filtering
{
    QPalette p = ui->checkBox->palette();
    QColor blue(0, 0, 255);
    p.setColor(QPalette::Active, QPalette::Highlight, blue);
    ui->checkBox->setPalette(p);
    emit on_findEdit_textChanged(ui->findEdit->text());
}


void SignalSelect::on_addToListButton_clicked()
{
    QModelIndex current = ui->allSignalsWidget->currentIndex();
    if(current.isValid())
    {
        QModelIndex index = updateWidgets(current, true);

        if(index.row() < ui->allSignalsWidget->count() - 1)
        {
            ui->allSignalsWidget->setCurrentIndex(index);
        }
    }
}

void SignalSelect::on_removeFromListButton_clicked()
{
    QModelIndex current = ui->selectedSignalsWidget->currentIndex();
    if(current.isValid())
    {
        QModelIndex index = updateWidgets(current, false);

        if(index.row() < ui->selectedSignalsWidget->count() - 1)
        {
            ui->selectedSignalsWidget->setCurrentIndex(index);
        }
    }
}

void SignalSelect::on_upButton_clicked()
{
    QModelIndex current = ui->selectedSignalsWidget->currentIndex();
    if(current.isValid())
    {
        m_selectedSignals.move(current.row(), current.row() - 1);
        QModelIndex newIndex = refreshWidgets(ui->selectedSignalsWidget->currentIndex());
        newIndex = newIndex.sibling(newIndex.row() - 1, newIndex.column());
        ui->selectedSignalsWidget->setCurrentIndex(newIndex);
    }
}

void SignalSelect::on_downButton_clicked()
{
    QModelIndex current = ui->selectedSignalsWidget->currentIndex();
    if(current.isValid())
    {
        m_selectedSignals.move(current.row(), current.row() + 1);
        ui->selectedSignalsWidget->setCurrentIndex(refreshWidgets(ui->selectedSignalsWidget->currentIndex()));
    }
}

void SignalSelect::on_okButton_clicked()
{
    m_oldSelectedSignals->clear();
    m_oldNotSelectedSignals->clear();
    m_oldSelectedSignals->append(m_selectedSignals);
    m_oldNotSelectedSignals->append(m_notSelectedSignals);
    emit updateSignalsSignal();
    this->close();
}

void SignalSelect::on_findEdit_textChanged(const QString &arg1)
{
    if(arg1.size() <= 2){                 //if the writed text size as same as or shorter than this integer, the filter don't start
        m_filteredSignals = m_notSelectedSignals;
        refreshWidgets(ui->allSignalsWidget->currentIndex());
        ui->filteredEdit->setText("n.a.");
    }
    else
    {
        if(ui->checkBox->isChecked())
        {
            m_filteredSignals = m_notSelectedSignals.filter(ui->findEdit->text(), Qt::CaseSensitive);
        }
        else
        {
            m_filteredSignals = m_notSelectedSignals.filter(ui->findEdit->text(), Qt::CaseInsensitive);
        }
        refreshWidgets(ui->allSignalsWidget->currentIndex());
        ui->filteredEdit->setText(QString::number(m_filteredSignals.size()));
    }
}

void SignalSelect::on_clearSelectedButton_clicked()
{
    m_selectedSignals = *m_oldSelectedSignals;
    m_notSelectedSignals = *m_oldNotSelectedSignals;
    m_filteredSignals = *m_oldNotSelectedSignals;
    refreshWidgets(ui->allSignalsWidget->currentIndex());
    ui->selectedSignalsWidget->clear();
}
