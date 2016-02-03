#include <QApplication>
#include <measuringwindow.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MeasuringWindow* measuringWindow = new MeasuringWindow();
    measuringWindow->show();
    return a.exec();
}
