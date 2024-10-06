#ifndef DATASENDWIDGET_H
#define DATASENDWIDGET_H

#include <QWidget>
#include <unordered_map>
#include <string>
namespace DataSendWidgetInfo{
enum class TypeFunction
{
    sin = 0,
    cos,
    random,
};

static std::unordered_map<TypeFunction, std::string> TypeFunctionNameStr
{
    {TypeFunction::sin, "sin"},
    {TypeFunction::cos, "cos"},
    {TypeFunction::random, "random"},
};

static std::unordered_map<std::string, TypeFunction> TypeFunctionEnum
{
    {"sin", TypeFunction::sin},
    {"cos", TypeFunction::cos},
    {"random", TypeFunction::random},
};
}

QT_BEGIN_NAMESPACE
namespace Ui { class DataSendWidget; }
QT_END_NAMESPACE

class DataSendWidget : public QWidget
{
    Q_OBJECT

public:
    DataSendWidget(QWidget *parent = nullptr);
    ~DataSendWidget();

    void SetInitHarmonicParameters(int a, int f, int p);
    DataSendWidgetInfo::TypeFunction GetTypeFunction();

    int GetAmplitude();
    int GetPhase();
    int GetFrequency();
private:
    Ui::DataSendWidget *ui;
private:
    void InitUi();
};
#endif // DATASENDWIDGET_H
