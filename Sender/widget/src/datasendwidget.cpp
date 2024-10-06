#include "datasendwidget.h"
#include "./ui_datasendwidget.h"

DataSendWidget::DataSendWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataSendWidget)
{
    ui->setupUi(this);
    InitUi();
}

DataSendWidget::~DataSendWidget()
{
    delete ui;
}

void DataSendWidget::SetInitHarmonicParameters(int a, int f, int p)
{
    ui->harmonic_a_sb->setValue(a);
    ui->harmonic_f_sb->setValue(f);
    ui->harmonic_p_sb->setValue(p);
}

DataSendWidgetInfo::TypeFunction DataSendWidget::GetTypeFunction()
{
    DataSendWidgetInfo::TypeFunction type;
    if(ui->harmonic_rb->isChecked())
    {
        std::string type_harmonic = ui->harmonic_cb->currentText().toStdString();
        type = DataSendWidgetInfo::TypeFunctionEnum[type_harmonic];
    }
    else if(ui->random_data_rb->isChecked())
    {
        type = DataSendWidgetInfo::TypeFunction::random;
    }

    return type;
}

int DataSendWidget::GetAmplitude()
{
    return ui->harmonic_a_sb->value();
}

int DataSendWidget::GetPhase()
{
    return ui->harmonic_p_sb->value();
}

int DataSendWidget::GetFrequency()
{
    return ui->harmonic_f_sb->value();
}

void DataSendWidget::InitUi()
{
    ui->harmonic_rb->setChecked(true);
    ui->harmonic_cb->addItem("sin");
    ui->harmonic_cb->addItem("cos");
    ui->harmonic_cb->setCurrentText("sin");
}

