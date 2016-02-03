#include "mysignal.h"

mySignal::mySignal()
{
    visible = false;
    loaded = false;
    checkBox = NULL;
    //chart = NULL;
    channel = NULL;
}

mySignal::mySignal(MDFlib::MDFChannel *ch)
{
    channel = ch;
    name = ch->getNameOfSignal();
    description = ch->getDescriptionOfSignal();
    visible = false;
    loaded = false;
    checkBox = NULL;
    //chart = NULL;
}

void mySignal::loadData()
{
    loaded = true;
    channel->LoadData();
    channel->getTimeChannel()->LoadData();
    unit = channel->getUnits();
    timeUnit = channel->getTimeChannel()->getUnits();

    data = channel->getData()->toVector();
    time = channel->getTimeChannel()->getData()->toVector();
}

MDFlib::MDFChannel *mySignal::getChannel() const
{
    return channel;
}

void mySignal::setChannel(MDFlib::MDFChannel *value)
{
    channel = value;
    name = value->getNameOfSignal();
    description = value->getDescriptionOfSignal();
}

QString *mySignal::getName() const
{
    return name;
}

QString *mySignal::getDescription() const
{
    return description;
}

QCheckBox *mySignal::getCheckBox() const
{
    return checkBox;
}

/*void mySignal::setCheckBox(QCheckBox *value, bool checked)
{
    if(checkBox && chart)
    {
        disconnect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkboxChangedSlot(int)));
    }
    checkBox = value;
    checkBox->setChecked(checked);
    if(chart)
    {
        connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(checkboxChangedSlot(int)));
    }
}*/

QVector<double> mySignal::getData() const
{
    return data;
}

QVector<double> mySignal::getTime() const
{
    return time;
}

/*
SignalChart *mySignal::getChart() const
{
    return chart;
}

void mySignal::setChart(SignalChart *value)
{
    chart = value;
    connect(this, SIGNAL(checkBoxCheckedSignal()), chart, SLOT(addToSceneSlot()));
    connect(this, SIGNAL(checkBoxUncheckedSignal()), chart, SLOT(removeFromSceneSlot()));
}
*/

void mySignal::checkboxChangedSlot(int state)
{
    if(state == Qt::Checked)
    {
        visible = true;
        emit checkBoxCheckedSignal();
    }
    if(state == Qt::Unchecked)
    {
        visible = false;
        emit checkBoxUncheckedSignal();
    }
}

bool mySignal::isVisible() const
{
    return visible;
}

bool mySignal::isLoaded() const
{
    return loaded;
}

QString *mySignal::getUnit() const
{
    return unit;
}

void mySignal::setUnit(QString *value)
{
    unit = value;
}
