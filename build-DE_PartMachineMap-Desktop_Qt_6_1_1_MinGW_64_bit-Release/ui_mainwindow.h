/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QToolButton *toolButton;
    QLabel *labelEditor;
    QPlainTextEdit *plainTextEditEditor;
    QPlainTextEdit *plainTextEditMessages;
    QLabel *label;
    QPushButton *pushButtonAltiumPart2Machines;
    QPushButton *pushButtonPanasonicCoordsToOriginal;
    QLabel *labelWorkDirectory;
    QPlainTextEdit *plainTextEditWorkDirectory;
    QMenuBar *menubar;
    QMenu *menuDE_part_to_machines;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(664, 509);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        toolButton = new QToolButton(centralwidget);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(150, 10, 501, 51));
        labelEditor = new QLabel(centralwidget);
        labelEditor->setObjectName(QString::fromUtf8("labelEditor"));
        labelEditor->setGeometry(QRect(40, 220, 47, 13));
        plainTextEditEditor = new QPlainTextEdit(centralwidget);
        plainTextEditEditor->setObjectName(QString::fromUtf8("plainTextEditEditor"));
        plainTextEditEditor->setGeometry(QRect(150, 210, 501, 31));
        plainTextEditMessages = new QPlainTextEdit(centralwidget);
        plainTextEditMessages->setObjectName(QString::fromUtf8("plainTextEditMessages"));
        plainTextEditMessages->setGeometry(QRect(30, 280, 611, 181));
        plainTextEditMessages->setReadOnly(true);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 260, 47, 13));
        pushButtonAltiumPart2Machines = new QPushButton(centralwidget);
        pushButtonAltiumPart2Machines->setObjectName(QString::fromUtf8("pushButtonAltiumPart2Machines"));
        pushButtonAltiumPart2Machines->setGeometry(QRect(150, 70, 501, 41));
        pushButtonPanasonicCoordsToOriginal = new QPushButton(centralwidget);
        pushButtonPanasonicCoordsToOriginal->setObjectName(QString::fromUtf8("pushButtonPanasonicCoordsToOriginal"));
        pushButtonPanasonicCoordsToOriginal->setGeometry(QRect(150, 120, 501, 41));
        labelWorkDirectory = new QLabel(centralwidget);
        labelWorkDirectory->setObjectName(QString::fromUtf8("labelWorkDirectory"));
        labelWorkDirectory->setGeometry(QRect(40, 180, 91, 16));
        plainTextEditWorkDirectory = new QPlainTextEdit(centralwidget);
        plainTextEditWorkDirectory->setObjectName(QString::fromUtf8("plainTextEditWorkDirectory"));
        plainTextEditWorkDirectory->setGeometry(QRect(150, 170, 501, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 664, 20));
        menuDE_part_to_machines = new QMenu(menubar);
        menuDE_part_to_machines->setObjectName(QString::fromUtf8("menuDE_part_to_machines"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDE_part_to_machines->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        toolButton->setText(QCoreApplication::translate("MainWindow", "Part 2 machines", nullptr));
        labelEditor->setText(QCoreApplication::translate("MainWindow", "Editor", nullptr));
        plainTextEditEditor->setPlainText(QCoreApplication::translate("MainWindow", "C:\\WindowsNotepad.exe", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Messages", nullptr));
        pushButtonAltiumPart2Machines->setText(QCoreApplication::translate("MainWindow", "Altium part 2 machines\n"
"", nullptr));
        pushButtonPanasonicCoordsToOriginal->setText(QCoreApplication::translate("MainWindow", "Panasonic coordinates to original", nullptr));
        labelWorkDirectory->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Work directory</p></body></html>", nullptr));
        menuDE_part_to_machines->setTitle(QCoreApplication::translate("MainWindow", "DE part to machines", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
