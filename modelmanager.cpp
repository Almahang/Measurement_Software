#include "modelmanager.h"

ModelManager::ModelManager(QObject *parent) :
    QObject(parent)
{
    m_signalListModel = new QStandardItemModel(0, 4, this);     /* will be 0 row, 4 collumns in the list (name, value, unit, is enabled?) */
    m_signalItemSelectionModel = new QItemSelectionModel(m_signalListModel, this);
    emptyModel();
}

void ModelManager::emptyModel()
{
    m_signalListModel->clear();
    m_signalListModel->setHorizontalHeaderLabels(QStringList()
                                                 << tr("Signal Name")
                                                 << tr("Value")
                                                 << tr("Unit"));
    /*
    QList<QStandardItem *> newRow;
    m_signalListModel->appendRow(newRow);

    // Example for checkbox
    QStandardItem * item0 = new QStandardItem(true);
    item0->setCheckable(true);
    item0->setCheckState(Qt::Checked);
    m_signalListModel->setItem(0, 3, item0);*/
}

void ModelManager::addItem(QString name, QVector<double> data, QString unit, bool enabled)
{

    QList<QStandardItem *> newRow;
    m_signalListModel->appendRow(newRow);
    int row = m_signalListModel->rowCount() - 1;
    qDebug() << "model add item, row: " << row << " name: " << name << " data[0]: " << data.at(0) << " unit: " << unit << " enabled: " << enabled;

    QStandardItem *item0 = new QStandardItem(name);
    m_signalListModel->setItem(row, 0, item0);
    QString dataStr = QString::number(data.at(0));
    QStandardItem *item1 = new QStandardItem(dataStr);
    m_signalListModel->setItem(row, 1, item1);
    if(unit.isNull() || unit.isEmpty()) unit = "n/a";
    QStandardItem *item2 = new QStandardItem(unit);
    m_signalListModel->setItem(row, 2, item2);
        item0->setCheckable(true);
    if(enabled) item0->setCheckState(Qt::Checked);
    else item0->setCheckState(Qt::Unchecked);
}


/*
 * ide kell majd átdobálni az adatokat, amire szükség lesz..
 * és szintén itt kel majd törölni...
 * a view magától feldolgozza  változást
 *
 * itt nem kell foglalkozni a kijelöléssekkel, azt a WidgetA-tól elkérni.
 * Ő pontosan tudni fogja mi a kijelölt elem idexe, amit aztán oda lehet
 * adni a chart-nak.
 */
