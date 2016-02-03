#include "colorchangedialog.h"
#include "ui_colorchangedialog.h"

ColorChangeDialog::ColorChangeDialog(int color, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ColorChangeDialog)
{
    ui->setupUi(this);

    QList<QHBoxLayout*> layoutList;
    layoutList << ui->horizontalLayout << ui->horizontalLayout_2 << ui->horizontalLayout_3 << ui->horizontalLayout_4 << ui->horizontalLayout_5;
    colorList << "red" << "green" << "blue" << "cyan" << "magenta" << "yellow" << "gray" << "teal" << "tomato" << "white" << "brown" << "greenyellow" << "deeppink" << "steelblue" << "darkRed" << "darkGreen" << "darkBlue" << "darkCyan" << "darkMagenta" << "khaki" << "darkGray" << "darkOrange" << "darkOrchid" << "slateblue" << "springgreen";
    for(int i = 0; i < 25; i++)
    {
        QPixmap* pixmap = new QPixmap(25, 25);
        QColor* newColor = new QColor(colorList[i]);
        pixmap->fill(*newColor);
        MyLabel* label = new MyLabel();
        label->setPixmap(*pixmap);
        label->setindex(i);
        layoutList.at(i / 5)->addWidget(label);
        connect(label, SIGNAL(colorSelectedSignal(int)), this, SLOT(colorSelectedSlot(int)));
    }
    QPixmap* pixmap = new QPixmap(30, 30);
    QColor* actualColor = new QColor(colorList[color]);
    pixmap->fill(*actualColor);
    ui->label_26->setPixmap(*pixmap);
    selectedColor = color;
}

ColorChangeDialog::~ColorChangeDialog()
{
    delete ui;
}

void ColorChangeDialog::colorSelectedSlot(int colorIndex)
{
    QPixmap* pixmap = new QPixmap(30, 30);
    QColor* color = new QColor(colorList[colorIndex]);
    pixmap->fill(*color);
    ui->label_26->setPixmap(*pixmap);
    selectedColor = colorIndex;

    this->setWindowTitle(QString("Color"));
}

void ColorChangeDialog::on_pushButton_clicked()
{
    emit colorChangedSignal(selectedColor);
    this->close();
}

void ColorChangeDialog::on_pushButton_2_clicked()
{
    this->close();
}






void MyLabel::mousePressEvent(QMouseEvent*)
{
    emit colorSelectedSignal(index);
}

void MyLabel::setindex(int index)
{
    this->index = index;
}


