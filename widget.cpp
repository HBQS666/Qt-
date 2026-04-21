#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    for(int i = 20;i<=40;i++){
        ui->sizeBox->addItem(QString::number(i));
    }
    QString example = "AaBbYyZz";
    ui->labelExample->setText(example);
    ui->labelExample->setAlignment(Qt::AlignCenter);

    this->group = new QButtonGroup(this);
    group->addButton(ui->overLineRadio,1);
    group->addButton(ui->underLineRadio,2);
    group->addButton(ui->strickOutRadio,3);
    group->addButton(ui->cancelRadio,4);

    this->font = ui->labelExample->font();
    font.setFamily("华文隶书");
    font.setPointSize(20);
    ui->labelExample->setFont(font);

    connect(group,&QButtonGroup::idToggled,[=](int id,bool flag){
        if(!flag) return ;
        font.setOverline(false);
        font.setUnderline(false);
        font.setStrikeOut(false);

        QString line = group->button(id)->text();

        if(line == "上划线"){
            font.setOverline(true);
        }else if(line == "下划线"){
            font.setUnderline(true);
        }else if(line == "删除线"){
            font.setStrikeOut(true);
        }
        ui->labelExample->setFont(font);
    });

    connect(ui->sizeBox,&QComboBox::currentIndexChanged,[this](){
        int wordSize = ui->sizeBox->currentText().toInt();
        font.setPointSize(wordSize);
        ui->labelExample->setFont(font);
    });

    connect(ui->fontBox,&QComboBox::currentIndexChanged,[this](){
        QString wordFont = ui->fontBox->currentText();
        font.setFamily(wordFont);
        ui->labelExample->setFont(font);
    });

    connect(ui->boldBtn,&QCheckBox::checkStateChanged,[this](){
        setStyle();
        ui->labelExample->setFont(font);
    });

    connect(ui->italicBtn,&QCheckBox::checkStateChanged,[this](){
        setStyle();
        ui->labelExample->setFont(font);
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setStyle()
{
    if(ui->boldBtn->isChecked()){
        font.setBold(true);
    }else{
        font.setBold(false);
    }

    if(ui->italicBtn->isChecked()){
        font.setItalic(true);
    }else{
        font.setItalic(false);
    }
}








