#ifndef WIDGETA_H
#define WIDGETA_H

#include <QWidget>
#include "modelmanager.h"
#include "qcustomplot/qcustomplot.h"

namespace Ui {
class WidgetA;
}

class WidgetA : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetA(QWidget *parent = 0);
    ~WidgetA();

    ModelManager* m_modelManager;

private:
    Ui::WidgetA *ui;
};

#endif // WIDGETA_H
