#include "measuringwindow.h"
#include "ui_measuringwindow.h"

MeasuringWindow::MeasuringWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MeasuringWindow)
{
    ui->setupUi(this);

    init();

    connect(graphicWidget, SIGNAL(changedLoopSignal(int,int)), signalWidget, SLOT(changedLoopSlot(int,int))); //ezeket nem találtam, esetleg visszamaradt?

    this->showMaximized();
}

MeasuringWindow::~MeasuringWindow()
{
    emit closeSignal();//ez itt egy signalja a measuring windownak, nem tudom, hogy minek
    delete ui;
}

void MeasuringWindow::init()
{
    ui->mdiArea->closeAllSubWindows();
    allSignal = new QMap<QString, mySignal*>();
    this->setWindowTitle("Continental Measurement System");

    m_fileNameMDF = "";

    signalWidget = new WidgetA();        
    signalWindow = ui->mdiArea->addSubWindow(signalWidget, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    signalWindow->resize(275, 500);
    signalWindow->setWindowTitle("Signals");
    signalWindow->setAccessibleDescription("signals");
    signalWindow->show();
    ui->actionSignal_window->setChecked(true);

    graphicWidget = new WidgetB();
    graphicWindow = ui->mdiArea->addSubWindow(graphicWidget, Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    graphicWindow->resize(800, 500);
    graphicWindow->setWindowTitle("Charts");
    graphicWindow->setAccessibleDescription("charts");
    graphicWindow->show();
    ui->actionGraphic_Window->setChecked(true);
}

void MeasuringWindow::addSignal() // itt kéne átdobni az adatot a modelmanager-nek //ezt hívja meg a signal select ablak bezárásával
{
    qDebug() << "addSignal()";
    //signalWidget->clear();
    for(QStringList::iterator it = selectedSignals.begin(); it != selectedSignals.end(); it++)
    {
        mySignal* signal = allSignal->value(*it);//signal az allsignalból az it-edik
        if(!(signal->isLoaded())) // egész pontosan itt!! (ha már be van olvasva a jel, nem fogja újra)

        {
            signal->loadData();
            graphicWidget->addNewChart(signal->getTime(), signal->getData(), *signal->getName());
            qDebug() << "trying to add item to the model";
            signalWidget->m_modelManager->addItem(*signal->getName(), signal->getData(), *signal->getUnit(), true);
            //signal->setChart(chart);
        }
        //signal->setCheckBox(signalWidget->addItem(*it, *signal->getUnit(), signal->getData(), signal->getChart()), signal->isVisible());
    }
    QString mainClockName = notSelectedSignals.filter("MAIN_CLOCK", Qt::CaseSensitive).first(); //ezt a részt nem értem, hogy mit akar
    mySignal* mainClockSignal = allSignal->value(mainClockName);//itt nulladik elem, az első időpillanat, ez legyen egyenlő a nulladik (26) koordinátával
    if(!(mainClockSignal->isLoaded()))// 30 lesz a negyedik, az a main clock + 4 bármelyik signalnak 4edik elemének az x-e az érdekes
    {
        mainClockSignal->loadData();
        //graphicWidget->addMainClock(mainClockSignal);
    }
}

void MeasuringWindow::on_actionSelect_Signals_triggered()
{
    qDebug() << "on_actionSelect_Signals_triggered()";
    signalSelectDialog = new SignalSelect(selectedSignals, notSelectedSignals, this); //itt hozza létre a jelválasztó ablakot
    connect(signalSelectDialog, SIGNAL(updateSignalsSignal()), this, SLOT(addSignal())); //itt köti össze a cancel gomb megnyomására(amit azt hittünk nem csinál semmit) az add signal beindul
    signalSelectDialog->show(); //megjelenik
}

void MeasuringWindow::on_actionSignal_window_triggered()
{
    if(ui->actionSignal_window->isChecked()) signalWindow->show();
    else signalWindow->hide();
}

void MeasuringWindow::on_actionGraphic_Window_triggered()
{
    if(ui->actionGraphic_Window->isChecked()) graphicWindow->show();
    else graphicWindow->hide();
}

///
/// \brief MeasuringWindow::openMDF
/// \param name This is the file name
/// This function will load the MDF file into memory
///
void MeasuringWindow::openMDF(QString name)
{
    QList<MDFlib::MDFDG*> *dgList;
    QList<MDFlib::MDFCG*> *cgList;
    QList<MDFlib::MDFChannel*> *cnList;
    mdf = new MDFlib::MDF();
    signalNameList.clear();
    allSignal->clear();
    notSelectedSignals.clear();
    //signalNameList = new QList<QString>();


    int numberOfSignals = 0;
    bool error = mdf->Open(& name);
    if(error)
    {
        ui->statusbar->showMessage("ERROR: File not loaded!", 10000);
    }
    else
    {
        ui->statusbar->showMessage("Loading from file!");
        dgList = mdf->getDataGroups();
        for(QList<MDFlib::MDFDG*>::iterator dgIt = dgList->begin(); dgIt != dgList->end(); dgIt++)
        {
            cgList = (*dgIt)->getChannelGroups();
            for(QList<MDFlib::MDFCG*>::iterator cgIt = cgList->begin(); cgIt != cgList->end(); cgIt++)
            {
                cnList = (*cgIt)->getChannels();
                for(QList<MDFlib::MDFChannel*>::iterator cnIt = cnList->begin(); cnIt != cnList->end(); cnIt++)
                {
                    signalNameList.append(*((*cnIt)->getNameOfSignal()));
                    numberOfSignals++;

                    mySignal* signal = new mySignal(*cnIt);
                    allSignal->insert(*signal->getName(), signal);
                }
            }
        }
        notSelectedSignals.append(signalNameList);
        ui->statusbar->showMessage("Signals loaded!", 15000);
        ui->actionMDF_file_info->setEnabled(true);
        ui->actionSelect_Signals->setEnabled(true);
        m_fileNameMDF = name;
    }
    ui->statusbar->clearMessage();
}

void MeasuringWindow::openProfile(QString path)
{
    QFile file(path);
    if(!file.exists()) { ui->statusbar->showMessage("ERROR: Profile not opened!", 10000);return; }

    QSettings settings(path, QSettings::IniFormat, this);

    settings.beginGroup("signalWindow");
    signalWindow->resize(settings.value("size", QSize(275, 500)).toSize());
    signalWindow->move(settings.value("position", QPoint(0, 0)).toPoint());
    bool isHidden = settings.value("isHidden", false).toBool();
    if(isHidden && !signalWindow->isHidden()) signalWindow->hide();
    else signalWindow->show();
    settings.endGroup();

    settings.beginGroup("graphicWindow");
    graphicWindow->resize(settings.value("size", QSize(800, 500)).toSize());
    graphicWindow->move(settings.value("position", QPoint(275, 0)).toPoint());
    isHidden = settings.value("isHidden", false).toBool();
    if(isHidden && !graphicWindow->isHidden()) graphicWindow->hide();
    else graphicWindow->show();
    settings.endGroup();

    settings.beginGroup("signals");
    int signalsNumber = settings.value("size", 0).toInt();
    settings.endGroup();

    if(signalsNumber != 0 && ui->actionMDF_file_info->isEnabled())
    {
        selectedSignals.clear();
        notSelectedSignals.clear();
        notSelectedSignals.append(allSignal->keys());
        for(int i = 0; i < signalsNumber; ++i)
        {
            settings.beginGroup(QString("signal" + QString::number(i)));
            QString signalName = settings.value("name").toString();

            selectedSignals.append(signalName);
            notSelectedSignals.removeOne(signalName);
            addSignal();
            //mySignal *signal = allSignal->value(selectedSignals.last());
            //signal->getChart()->changeColor(settings.value("colorIndex").toInt());
            //signal->getChart()->setOffsetY(settings.value("offsetY").toInt());
            //signal->getChart()->setRateY(settings.value("rateY").toInt());

            settings.endGroup();
        }
    }
}

void MeasuringWindow::saveProfile(QString path)
{
    QFile file(path);
    if(file.exists()) if(!file.remove())    /* This will remove the settings file, if its exist.
                                            It is not a problem here because the valid settings
                                            always read from the current program running. */
    {
        ui->statusbar->showMessage("ERROR: Profile not saved!", 15000);
        return;
    }

    QSettings settings(path, QSettings::IniFormat, this);

    settings.beginGroup("signalWindow");
    settings.setValue("size", signalWindow->size());
    settings.setValue("position", signalWindow->pos());
    settings.setValue("isHidden", signalWindow->isHidden());
    settings.endGroup();

    settings.beginGroup("graphicWindow");
    settings.setValue("size", graphicWindow->size());
    settings.setValue("position", graphicWindow->pos());
    settings.setValue("isHidden", graphicWindow->isHidden());
    settings.endGroup();

    if(ui->actionMDF_file_info->isEnabled())
    {
        settings.beginGroup("MDF");
        settings.setValue("path", m_fileNameMDF);
        settings.endGroup();

        settings.beginGroup("signals");
        settings.setValue("size", selectedSignals.size());
        settings.endGroup();

        for(int i = 0; i < selectedSignals.size(); ++i)
        {
            mySignal *signal = allSignal->value(selectedSignals[i]);
            settings.beginGroup(QString("signal" + QString::number(i)));
            settings.setValue("name", *signal->getName());
            //settings.setValue("colorIndex", signal->getChart()->getColorIndex());
            //settings.setValue("offsetY", signal->getChart()->getOffsetY());
            //settings.setValue("rateY", signal->getChart()->getRateY());
            settings.endGroup();
        }
    }
    ui->statusbar->showMessage("Profile saved!", 15000);
}

void MeasuringWindow::on_actionMDF_file_info_triggered()
{
    MDFFileInfoDialog* dialog = new MDFFileInfoDialog(
                m_fileNameMDF,
                mdf->getFileID()->getFileID(),
                mdf->getFileID()->getFileVer(),
                mdf->getFileID()->getProgID(),
                mdf->getFileID()->getByteOrder(),
                mdf->getFileID()->getFileVerInt(),
                mdf->getFileHeader()->getDate(),
                mdf->getFileHeader()->getTime(),
                mdf->getFileHeader()->getAuthor(),
                mdf->getFileHeader()->getOrganization(),
                mdf->getFileHeader()->getProject(),
                mdf->getFileHeader()->getVehicleID(),
                mdf->getFileHeader()->getComment(),
                this);
    dialog->show();
}

///
/// \brief MeasuringWindow::on_actionOpen_MDF_file_triggered
/// Function for MDF file open
///
void MeasuringWindow::on_actionOpen_MDF_file_triggered()
{
    QString path = QDir::homePath();
    QString fn = QFileDialog::getOpenFileName(
                this,
                tr("Open MDF File"),
                path,
                tr("MDF files (*.mdf);;All files (*.*)"));

    if(!fn.isEmpty()) openMDF(fn);
    else
    {
        QMessageBox mb(QMessageBox::Critical, tr("Unable to Open"), tr("Unable to open the MDF file!"));
        mb.exec();
    }
}

void MeasuringWindow::on_actionSaveProfile_triggered()
{
    QString fn = QDir::toNativeSeparators(QString(QCoreApplication::applicationDirPath() + "/config.ini"));
    QFile file(fn);

    if(file.exists()) file.remove();
    saveProfile(fn);
}

void MeasuringWindow::on_actionLoadProfile_triggered()
{
    QString fn = QDir::toNativeSeparators(QString(QCoreApplication::applicationDirPath() + "/config.ini"));
    QFile file(fn);

    if(file.exists()) openProfile(fn);
    else
    {
        QMessageBox mb(QMessageBox::Critical, tr("Unable To Load"), tr("Unable to load the profile!"));
        mb.exec();
    }
}

void MeasuringWindow::on_actionExportProfile_triggered()
{
    QString path = QDir::homePath();
    QString fn = QFileDialog::getSaveFileName(
                this,
                tr("Export Profile"),
                path,
                tr("Configuration files (*.ini)"));

    if(!fn.isEmpty())
    {
        QFileInfo info(fn);
        QString ext = info.suffix();
        if(ext != "ini") fn += ".ini";
        saveProfile(fn);
    }
    else
    {
        QMessageBox mb(QMessageBox::Critical, tr("Unable to Export"), tr("Unable to export the profile!"));
        mb.exec();
    }
}

void MeasuringWindow::on_actionImportProfile_triggered()
{
    QString path = QDir::homePath();
    QString fn = QFileDialog::getOpenFileName(
                this,
                tr("Import Profile"),
                path,
                tr("Configuration files (*.ini)"));

    qDebug() << fn;

    if(!fn.isEmpty()) openProfile(fn);
    else
    {
        QMessageBox mb(QMessageBox::Critical, tr("Unable To Import"), tr("Unable to import the profile!"));
        mb.exec();
    }
}

void MeasuringWindow::on_actionClose_triggered()
{
    QApplication::quit();
}

void MeasuringWindow::on_actionAlign_windows_triggered()
{
    QSize size = ui->mdiArea->size();
    signalWindow->setGeometry(0, 0, size.width() * 0.30, size.height());
    graphicWindow->setGeometry(size.width() * 0.30, 0, size.width() * 0.70, size.height());
}

void MeasuringWindow::on_actionCloseProfile_triggered()
{
    init();
    on_actionAlign_windows_triggered();
}
