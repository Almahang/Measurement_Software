#ifndef COLORCHANGEDIALOG_H
#define COLORCHANGEDIALOG_H

#include <QDialog>
#include <QString>
#include <QList>
#include <QColor>
#include <QLabel>

namespace Ui {
    class MyPixmap;
    class ColorChangeDialog;
}

class ColorChangeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ColorChangeDialog(int color, QWidget *parent = 0);
    ~ColorChangeDialog();
    
private:
    Ui::ColorChangeDialog *ui;
    QList<QString> colorList;
    int selectedColor;

private slots:
    void colorSelectedSlot(int colorIndex);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void colorChangedSignal(int index);
};



class MyLabel : public QLabel
{
  Q_OBJECT

public:
    void setindex(int index);

private:
    int index;
    void mousePressEvent(QMouseEvent *ev);

signals:
    void colorSelectedSignal(int index);
};

#endif // COLORCHANGEDIALOG_H
