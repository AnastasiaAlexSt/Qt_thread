/********************************************************************************
** Form generated from reading UI file 'datasendwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATASENDWIDGET_H
#define UI_DATASENDWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataSendWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_2;
    QSpinBox *harmonic_f_sb;
    QComboBox *harmonic_cb;
    QLabel *label_4;
    QSpinBox *harmonic_a_sb;
    QSpinBox *harmonic_p_sb;
    QRadioButton *harmonic_rb;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QRadioButton *random_data_rb;

    void setupUi(QWidget *DataSendWidget)
    {
        if (DataSendWidget->objectName().isEmpty())
            DataSendWidget->setObjectName(QString::fromUtf8("DataSendWidget"));
        DataSendWidget->resize(288, 214);
        verticalLayout_3 = new QVBoxLayout(DataSendWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(DataSendWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 2, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 2, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        harmonic_f_sb = new QSpinBox(groupBox);
        harmonic_f_sb->setObjectName(QString::fromUtf8("harmonic_f_sb"));
        harmonic_f_sb->setMinimum(-100);
        harmonic_f_sb->setMaximum(100);
        harmonic_f_sb->setValue(1);

        gridLayout->addWidget(harmonic_f_sb, 3, 1, 1, 1);

        harmonic_cb = new QComboBox(groupBox);
        harmonic_cb->setObjectName(QString::fromUtf8("harmonic_cb"));

        gridLayout->addWidget(harmonic_cb, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        harmonic_a_sb = new QSpinBox(groupBox);
        harmonic_a_sb->setObjectName(QString::fromUtf8("harmonic_a_sb"));
        harmonic_a_sb->setMinimum(-100);
        harmonic_a_sb->setMaximum(100);
        harmonic_a_sb->setValue(1);

        gridLayout->addWidget(harmonic_a_sb, 1, 1, 1, 1);

        harmonic_p_sb = new QSpinBox(groupBox);
        harmonic_p_sb->setObjectName(QString::fromUtf8("harmonic_p_sb"));
        harmonic_p_sb->setMinimum(-360);
        harmonic_p_sb->setMaximum(360);
        harmonic_p_sb->setValue(0);

        gridLayout->addWidget(harmonic_p_sb, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);


        horizontalLayout->addWidget(groupBox);

        harmonic_rb = new QRadioButton(DataSendWidget);
        harmonic_rb->setObjectName(QString::fromUtf8("harmonic_rb"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(harmonic_rb->sizePolicy().hasHeightForWidth());
        harmonic_rb->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(harmonic_rb);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(DataSendWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        random_data_rb = new QRadioButton(DataSendWidget);
        random_data_rb->setObjectName(QString::fromUtf8("random_data_rb"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(random_data_rb->sizePolicy().hasHeightForWidth());
        random_data_rb->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(random_data_rb);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);


        retranslateUi(DataSendWidget);

        QMetaObject::connectSlotsByName(DataSendWidget);
    } // setupUi

    void retranslateUi(QWidget *DataSendWidget)
    {
        DataSendWidget->setWindowTitle(QApplication::translate("DataSendWidget", "DataSendWidget", nullptr));
        groupBox->setTitle(QApplication::translate("DataSendWidget", "sin/cos", nullptr));
        label_3->setText(QApplication::translate("DataSendWidget", "\320\244\320\260\320\267\320\260:", nullptr));
        label_6->setText(QApplication::translate("DataSendWidget", "\320\223\321\206", nullptr));
        label_5->setText(QApplication::translate("DataSendWidget", "\320\263\321\200\320\260\320\264", nullptr));
        label_7->setText(QApplication::translate("DataSendWidget", "sin/cos:", nullptr));
        label_2->setText(QApplication::translate("DataSendWidget", "\320\220\320\274\320\277\320\273\320\270\321\202\321\203\320\264\320\260:", nullptr));
        label_4->setText(QApplication::translate("DataSendWidget", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260:", nullptr));
        harmonic_rb->setText(QString());
        label->setText(QApplication::translate("DataSendWidget", "\320\241\320\273\321\203\321\207\320\260\320\271\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", nullptr));
        random_data_rb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DataSendWidget: public Ui_DataSendWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATASENDWIDGET_H
