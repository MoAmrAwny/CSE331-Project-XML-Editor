/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *MAIN_PAGE;
    QLabel *label;
    QPushButton *BROWSE_BUTTON;
    QPushButton *COPY_BUTTON;
    QLabel *label_2;
    QWidget *COPY_PAGE;
    QLabel *COPY_LABEL;
    QTextEdit *XML_TEXT;
    QPushButton *OK_COPY_BUTTON;
    QPushButton *CLOSE_COPY_LABEL;
    QWidget *XML_PAGE;
    QLabel *features;
    QLabel *please_choose;
    QComboBox *dropdown;
    QPushButton *back_button;
    QTextEdit *DisplayFiles;
    QWidget *NETWORK_PAGE;
    QLabel *Network_Page;
    QPushButton *most_follower;
    QPushButton *most_active;
    QPushButton *mutual_followers;
    QPushButton *suggestions;
    QPushButton *back_button_2;
    QWidget *Search;
    QLabel *Search_2;
    QTextEdit *textEdit_2;
    QPushButton *SearchByTopic;
    QPushButton *SearchByWord;
    QPushButton *SearchBack;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 800, 600));
        MAIN_PAGE = new QWidget();
        MAIN_PAGE->setObjectName("MAIN_PAGE");
        label = new QLabel(MAIN_PAGE);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 40, 701, 141));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        font.setHintingPreference(QFont::PreferDefaultHinting);
        label->setFont(font);
        label->setTextFormat(Qt::TextFormat::AutoText);
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BROWSE_BUTTON = new QPushButton(MAIN_PAGE);
        BROWSE_BUTTON->setObjectName("BROWSE_BUTTON");
        BROWSE_BUTTON->setGeometry(QRect(482, 370, 151, 75));
        QFont font1;
        font1.setPointSize(15);
        BROWSE_BUTTON->setFont(font1);
        COPY_BUTTON = new QPushButton(MAIN_PAGE);
        COPY_BUTTON->setObjectName("COPY_BUTTON");
        COPY_BUTTON->setGeometry(QRect(166, 370, 150, 75));
        COPY_BUTTON->setFont(font1);
        label_2 = new QLabel(MAIN_PAGE);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(260, 500, 291, 31));
        QFont font2;
        font2.setPointSize(9);
        label_2->setFont(font2);
        stackedWidget->addWidget(MAIN_PAGE);
        COPY_PAGE = new QWidget();
        COPY_PAGE->setObjectName("COPY_PAGE");
        COPY_LABEL = new QLabel(COPY_PAGE);
        COPY_LABEL->setObjectName("COPY_LABEL");
        COPY_LABEL->setGeometry(QRect(100, 50, 600, 100));
        QFont font3;
        font3.setPointSize(30);
        COPY_LABEL->setFont(font3);
        COPY_LABEL->setAlignment(Qt::AlignmentFlag::AlignCenter);
        XML_TEXT = new QTextEdit(COPY_PAGE);
        XML_TEXT->setObjectName("XML_TEXT");
        XML_TEXT->setGeometry(QRect(100, 250, 450, 200));
        OK_COPY_BUTTON = new QPushButton(COPY_PAGE);
        OK_COPY_BUTTON->setObjectName("OK_COPY_BUTTON");
        OK_COPY_BUTTON->setGeometry(QRect(650, 290, 100, 30));
        OK_COPY_BUTTON->setFont(font1);
        CLOSE_COPY_LABEL = new QPushButton(COPY_PAGE);
        CLOSE_COPY_LABEL->setObjectName("CLOSE_COPY_LABEL");
        CLOSE_COPY_LABEL->setGeometry(QRect(650, 380, 100, 30));
        CLOSE_COPY_LABEL->setFont(font1);
        stackedWidget->addWidget(COPY_PAGE);
        XML_PAGE = new QWidget();
        XML_PAGE->setObjectName("XML_PAGE");
        features = new QLabel(XML_PAGE);
        features->setObjectName("features");
        features->setGeometry(QRect(280, 10, 250, 131));
        features->setFont(font3);
        features->setAlignment(Qt::AlignmentFlag::AlignCenter);
        please_choose = new QLabel(XML_PAGE);
        please_choose->setObjectName("please_choose");
        please_choose->setGeometry(QRect(290, 140, 241, 20));
        dropdown = new QComboBox(XML_PAGE);
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->addItem(QString());
        dropdown->setObjectName("dropdown");
        dropdown->setGeometry(QRect(290, 190, 231, 28));
        back_button = new QPushButton(XML_PAGE);
        back_button->setObjectName("back_button");
        back_button->setGeometry(QRect(360, 510, 83, 29));
        DisplayFiles = new QTextEdit(XML_PAGE);
        DisplayFiles->setObjectName("DisplayFiles");
        DisplayFiles->setGeometry(QRect(180, 270, 461, 161));
        stackedWidget->addWidget(XML_PAGE);
        NETWORK_PAGE = new QWidget();
        NETWORK_PAGE->setObjectName("NETWORK_PAGE");
        Network_Page = new QLabel(NETWORK_PAGE);
        Network_Page->setObjectName("Network_Page");
        Network_Page->setGeometry(QRect(260, 50, 321, 131));
        Network_Page->setFont(font3);
        most_follower = new QPushButton(NETWORK_PAGE);
        most_follower->setObjectName("most_follower");
        most_follower->setGeometry(QRect(60, 340, 211, 31));
        most_follower->setFont(font1);
        most_active = new QPushButton(NETWORK_PAGE);
        most_active->setObjectName("most_active");
        most_active->setGeometry(QRect(300, 340, 211, 31));
        most_active->setFont(font1);
        mutual_followers = new QPushButton(NETWORK_PAGE);
        mutual_followers->setObjectName("mutual_followers");
        mutual_followers->setGeometry(QRect(540, 340, 211, 31));
        mutual_followers->setFont(font1);
        suggestions = new QPushButton(NETWORK_PAGE);
        suggestions->setObjectName("suggestions");
        suggestions->setGeometry(QRect(300, 430, 211, 41));
        suggestions->setFont(font1);
        back_button_2 = new QPushButton(NETWORK_PAGE);
        back_button_2->setObjectName("back_button_2");
        back_button_2->setGeometry(QRect(360, 530, 83, 29));
        stackedWidget->addWidget(NETWORK_PAGE);
        Search = new QWidget();
        Search->setObjectName("Search");
        Search_2 = new QLabel(Search);
        Search_2->setObjectName("Search_2");
        Search_2->setGeometry(QRect(350, 110, 151, 71));
        Search_2->setFont(font3);
        textEdit_2 = new QTextEdit(Search);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(300, 380, 231, 85));
        SearchByTopic = new QPushButton(Search);
        SearchByTopic->setObjectName("SearchByTopic");
        SearchByTopic->setGeometry(QRect(230, 280, 111, 29));
        SearchByWord = new QPushButton(Search);
        SearchByWord->setObjectName("SearchByWord");
        SearchByWord->setGeometry(QRect(490, 280, 131, 29));
        SearchBack = new QPushButton(Search);
        SearchBack->setObjectName("SearchBack");
        SearchBack->setGeometry(QRect(370, 520, 83, 29));
        stackedWidget->addWidget(Search);
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "XML EDITOR AND NETWORK ANALYSIS", nullptr));
        BROWSE_BUTTON->setText(QCoreApplication::translate("MainWindow", "BROWSE FILE", nullptr));
        COPY_BUTTON->setText(QCoreApplication::translate("MainWindow", "COPY FILE", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "incase of decompressing kindly click Browse", nullptr));
        COPY_LABEL->setText(QCoreApplication::translate("MainWindow", "PLEASE PASTE TEXT FILE", nullptr));
        OK_COPY_BUTTON->setText(QCoreApplication::translate("MainWindow", "OK", nullptr));
        CLOSE_COPY_LABEL->setText(QCoreApplication::translate("MainWindow", "BACK", nullptr));
        features->setText(QCoreApplication::translate("MainWindow", "Features ", nullptr));
        please_choose->setText(QCoreApplication::translate("MainWindow", "please choose your desired feature", nullptr));
        dropdown->setItemText(0, QCoreApplication::translate("MainWindow", "Choose the feature", nullptr));
        dropdown->setItemText(1, QCoreApplication::translate("MainWindow", "Check Consistency", nullptr));
        dropdown->setItemText(2, QCoreApplication::translate("MainWindow", "Prettifying", nullptr));
        dropdown->setItemText(3, QCoreApplication::translate("MainWindow", "to JSON", nullptr));
        dropdown->setItemText(4, QCoreApplication::translate("MainWindow", "Minifying", nullptr));
        dropdown->setItemText(5, QCoreApplication::translate("MainWindow", "Compress", nullptr));
        dropdown->setItemText(6, QCoreApplication::translate("MainWindow", "Decompress", nullptr));
        dropdown->setItemText(7, QCoreApplication::translate("MainWindow", "Network Analysis", nullptr));
        dropdown->setItemText(8, QCoreApplication::translate("MainWindow", "Graph Visualization", nullptr));
        dropdown->setItemText(9, QCoreApplication::translate("MainWindow", "Search", nullptr));

        back_button->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        Network_Page->setText(QCoreApplication::translate("MainWindow", "Network_page", nullptr));
        most_follower->setText(QCoreApplication::translate("MainWindow", "Most Follower", nullptr));
        most_active->setText(QCoreApplication::translate("MainWindow", "Most Active", nullptr));
        mutual_followers->setText(QCoreApplication::translate("MainWindow", "Mutual Followers", nullptr));
        suggestions->setText(QCoreApplication::translate("MainWindow", "Suggest followers", nullptr));
        back_button_2->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        Search_2->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        SearchByTopic->setText(QCoreApplication::translate("MainWindow", "Search by topic", nullptr));
        SearchByWord->setText(QCoreApplication::translate("MainWindow", "Search by word", nullptr));
        SearchBack->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
