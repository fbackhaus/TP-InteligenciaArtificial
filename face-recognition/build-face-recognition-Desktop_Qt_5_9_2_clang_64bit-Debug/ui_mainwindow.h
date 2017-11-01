/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "cursorcontrollerwidget.hpp"
#include "grapher.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *calibrateAction;
    QAction *showProcessingAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *controlPanelGroupBox;
    QGridLayout *gridLayout_4;
    QCheckBox *controlMouseCheckbox;
    QPushButton *calibrateButton;
    QCheckBox *showProcessingCheckbox;
    QSpacerItem *horizontalSpacer;
    QGroupBox *cameraGroupBox;
    QGridLayout *gridLayout_3;
    CursorControllerWidget *cursorControllerWidget;
    QSpacerItem *verticalSpacer;
    QGroupBox *graphicsGroupBox;
    QGridLayout *gridLayout_2;
    Grapher *velocityGrapher;
    Grapher *positionGrapher;
    QLabel *positionLabel;
    QLabel *velocityLabel;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1155, 735);
        calibrateAction = new QAction(MainWindow);
        calibrateAction->setObjectName(QStringLiteral("calibrateAction"));
        showProcessingAction = new QAction(MainWindow);
        showProcessingAction->setObjectName(QStringLiteral("showProcessingAction"));
        showProcessingAction->setCheckable(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        controlPanelGroupBox = new QGroupBox(centralwidget);
        controlPanelGroupBox->setObjectName(QStringLiteral("controlPanelGroupBox"));
        gridLayout_4 = new QGridLayout(controlPanelGroupBox);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        controlMouseCheckbox = new QCheckBox(controlPanelGroupBox);
        controlMouseCheckbox->setObjectName(QStringLiteral("controlMouseCheckbox"));

        gridLayout_4->addWidget(controlMouseCheckbox, 0, 2, 1, 1);

        calibrateButton = new QPushButton(controlPanelGroupBox);
        calibrateButton->setObjectName(QStringLiteral("calibrateButton"));
        calibrateButton->setCheckable(false);
        calibrateButton->setChecked(false);

        gridLayout_4->addWidget(calibrateButton, 0, 0, 1, 1);

        showProcessingCheckbox = new QCheckBox(controlPanelGroupBox);
        showProcessingCheckbox->setObjectName(QStringLiteral("showProcessingCheckbox"));
        showProcessingCheckbox->setChecked(true);

        gridLayout_4->addWidget(showProcessingCheckbox, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 3, 1, 1);


        gridLayout->addWidget(controlPanelGroupBox, 0, 0, 1, 2);

        cameraGroupBox = new QGroupBox(centralwidget);
        cameraGroupBox->setObjectName(QStringLiteral("cameraGroupBox"));
        gridLayout_3 = new QGridLayout(cameraGroupBox);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        cursorControllerWidget = new CursorControllerWidget(cameraGroupBox);
        cursorControllerWidget->setObjectName(QStringLiteral("cursorControllerWidget"));

        gridLayout_3->addWidget(cursorControllerWidget, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 0, 1, 1, 1);


        gridLayout->addWidget(cameraGroupBox, 1, 0, 1, 1);

        graphicsGroupBox = new QGroupBox(centralwidget);
        graphicsGroupBox->setObjectName(QStringLiteral("graphicsGroupBox"));
        gridLayout_2 = new QGridLayout(graphicsGroupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        velocityGrapher = new Grapher(graphicsGroupBox);
        velocityGrapher->setObjectName(QStringLiteral("velocityGrapher"));

        gridLayout_2->addWidget(velocityGrapher, 3, 1, 1, 1);

        positionGrapher = new Grapher(graphicsGroupBox);
        positionGrapher->setObjectName(QStringLiteral("positionGrapher"));

        gridLayout_2->addWidget(positionGrapher, 1, 1, 1, 1);

        positionLabel = new QLabel(graphicsGroupBox);
        positionLabel->setObjectName(QStringLiteral("positionLabel"));

        gridLayout_2->addWidget(positionLabel, 0, 1, 1, 1);

        velocityLabel = new QLabel(graphicsGroupBox);
        velocityLabel->setObjectName(QStringLiteral("velocityLabel"));

        gridLayout_2->addWidget(velocityLabel, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 1, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 3, 0, 1, 1);


        gridLayout->addWidget(graphicsGroupBox, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1155, 22));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Face Features Based Cursor Controller", Q_NULLPTR));
        calibrateAction->setText(QApplication::translate("MainWindow", "Calibrar", Q_NULLPTR));
        showProcessingAction->setText(QApplication::translate("MainWindow", "Mostrar procesamiento", Q_NULLPTR));
        controlPanelGroupBox->setTitle(QApplication::translate("MainWindow", "Panel de control", Q_NULLPTR));
        controlMouseCheckbox->setText(QApplication::translate("MainWindow", "Controlar el mouse", Q_NULLPTR));
        calibrateButton->setText(QApplication::translate("MainWindow", "Reestablecer puntos", Q_NULLPTR));
        showProcessingCheckbox->setText(QApplication::translate("MainWindow", "Mostrar procesamiento", Q_NULLPTR));
        cameraGroupBox->setTitle(QApplication::translate("MainWindow", "C\303\241mara", Q_NULLPTR));
        graphicsGroupBox->setTitle(QApplication::translate("MainWindow", "Gr\303\241ficos", Q_NULLPTR));
        positionLabel->setText(QApplication::translate("MainWindow", "Posici\303\263n de target", Q_NULLPTR));
        velocityLabel->setText(QApplication::translate("MainWindow", "Velocidad de target", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
