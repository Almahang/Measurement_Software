#ifndef WIDGETB_H
#define WIDGETB_H

#include <QWidget>
#include <QDebug>
#include "qcustomplot/qcustomplot.h"
#include "widgeta.h"

namespace Ui {
class WidgetB;
}

class WidgetB : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetB(QWidget *parent = 0);
    ~WidgetB();
    void addNewChart(QVector<double> x, QVector<double> y, QString name);
    int getRandomNo(int low, int high);

    int getSignaldata() const;
    void setSignaldata(int value);

public slots:
    void onMouseMoveGraph (QMouseEvent *event);
    void mousePress();
    void graphClicked(QCPAbstractPlottable*);


private:
    QVector<double> data;
    int size_x;
    Ui::WidgetB *ui;
    QCPAxisRect * wideAxisRect;

};

#endif // WIDGETB_H
