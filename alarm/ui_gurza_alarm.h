/********************************************************************************
** Form generated from reading UI file 'gurza_alarm.ui'
**
** Created: Tue 11. Jun 12:13:35 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GURZA_ALARM_H
#define UI_GURZA_ALARM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTimeEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *vl_events;
    QLabel *lbl_ev_title;
    QVBoxLayout *vl_signal;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *freq_label;
    QLineEdit *edit_frq;
    QLabel *lcd_lbl;
    QLCDNumber *lcd;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QLabel *label;
    QRadioButton *rb_auto;
    QRadioButton *rb_manual;
    QLabel *time_label;
    QTimeEdit *t_e;
    QPushButton *bt_start;
    QPushButton *bt_stop;
    QPushButton *bt_quit;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setWindowModality(Qt::ApplicationModal);
        MainWindow->resize(403, 450);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Calibri"));
        font.setPointSize(12);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vl_events = new QVBoxLayout();
        vl_events->setSpacing(0);
        vl_events->setObjectName(QString::fromUtf8("vl_events"));
        vl_events->setSizeConstraint(QLayout::SetMinimumSize);
        lbl_ev_title = new QLabel(centralwidget);
        lbl_ev_title->setObjectName(QString::fromUtf8("lbl_ev_title"));
        lbl_ev_title->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Linux Libertine G"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        lbl_ev_title->setFont(font1);
        lbl_ev_title->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        vl_events->addWidget(lbl_ev_title);


        gridLayout->addLayout(vl_events, 0, 0, 1, 2);

        vl_signal = new QVBoxLayout();
        vl_signal->setSpacing(10);
        vl_signal->setObjectName(QString::fromUtf8("vl_signal"));
        vl_signal->setSizeConstraint(QLayout::SetMinimumSize);

        gridLayout->addLayout(vl_signal, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(20, -1, 20, -1);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 10, -1, -1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Linux Libertine G"));
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_2->setFont(font2);
        label_2->setFrameShape(QFrame::Box);
        label_2->setFrameShadow(QFrame::Raised);
        label_2->setAlignment(Qt::AlignCenter);
        label_2->setWordWrap(true);

        verticalLayout_2->addWidget(label_2);

        freq_label = new QLabel(centralwidget);
        freq_label->setObjectName(QString::fromUtf8("freq_label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(freq_label->sizePolicy().hasHeightForWidth());
        freq_label->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Linux Libertine G"));
        freq_label->setFont(font3);
        freq_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        freq_label->setWordWrap(true);

        verticalLayout_2->addWidget(freq_label);

        edit_frq = new QLineEdit(centralwidget);
        edit_frq->setObjectName(QString::fromUtf8("edit_frq"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(edit_frq->sizePolicy().hasHeightForWidth());
        edit_frq->setSizePolicy(sizePolicy2);
        edit_frq->setMinimumSize(QSize(100, 0));
        edit_frq->setReadOnly(true);

        verticalLayout_2->addWidget(edit_frq);

        lcd_lbl = new QLabel(centralwidget);
        lcd_lbl->setObjectName(QString::fromUtf8("lcd_lbl"));
        sizePolicy1.setHeightForWidth(lcd_lbl->sizePolicy().hasHeightForWidth());
        lcd_lbl->setSizePolicy(sizePolicy1);
        lcd_lbl->setFont(font3);
        lcd_lbl->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lcd_lbl->setWordWrap(true);

        verticalLayout_2->addWidget(lcd_lbl);

        lcd = new QLCDNumber(centralwidget);
        lcd->setObjectName(QString::fromUtf8("lcd"));
        lcd->setMinimumSize(QSize(100, 155));
        lcd->setNumDigits(1);

        verticalLayout_2->addWidget(lcd);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 10, -1, -1);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font2);
        label_3->setFrameShape(QFrame::Box);
        label_3->setFrameShadow(QFrame::Raised);
        label_3->setAlignment(Qt::AlignCenter);
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Linux Libertine G"));
        font4.setPointSize(12);
        label->setFont(font4);

        verticalLayout->addWidget(label);

        rb_auto = new QRadioButton(centralwidget);
        rb_auto->setObjectName(QString::fromUtf8("rb_auto"));
        sizePolicy2.setHeightForWidth(rb_auto->sizePolicy().hasHeightForWidth());
        rb_auto->setSizePolicy(sizePolicy2);
        rb_auto->setFont(font4);

        verticalLayout->addWidget(rb_auto);

        rb_manual = new QRadioButton(centralwidget);
        rb_manual->setObjectName(QString::fromUtf8("rb_manual"));
        sizePolicy2.setHeightForWidth(rb_manual->sizePolicy().hasHeightForWidth());
        rb_manual->setSizePolicy(sizePolicy2);
        rb_manual->setFont(font4);

        verticalLayout->addWidget(rb_manual);

        time_label = new QLabel(centralwidget);
        time_label->setObjectName(QString::fromUtf8("time_label"));
        sizePolicy1.setHeightForWidth(time_label->sizePolicy().hasHeightForWidth());
        time_label->setSizePolicy(sizePolicy1);
        time_label->setFont(font3);
        time_label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        time_label->setWordWrap(true);

        verticalLayout->addWidget(time_label);

        t_e = new QTimeEdit(centralwidget);
        t_e->setObjectName(QString::fromUtf8("t_e"));
        sizePolicy2.setHeightForWidth(t_e->sizePolicy().hasHeightForWidth());
        t_e->setSizePolicy(sizePolicy2);
        t_e->setFont(font3);

        verticalLayout->addWidget(t_e);

        bt_start = new QPushButton(centralwidget);
        bt_start->setObjectName(QString::fromUtf8("bt_start"));
        sizePolicy2.setHeightForWidth(bt_start->sizePolicy().hasHeightForWidth());
        bt_start->setSizePolicy(sizePolicy2);
        bt_start->setMinimumSize(QSize(150, 0));
        bt_start->setFont(font3);

        verticalLayout->addWidget(bt_start);

        bt_stop = new QPushButton(centralwidget);
        bt_stop->setObjectName(QString::fromUtf8("bt_stop"));
        sizePolicy2.setHeightForWidth(bt_stop->sizePolicy().hasHeightForWidth());
        bt_stop->setSizePolicy(sizePolicy2);
        bt_stop->setMinimumSize(QSize(150, 0));
        bt_stop->setFont(font3);

        verticalLayout->addWidget(bt_stop);

        bt_quit = new QPushButton(centralwidget);
        bt_quit->setObjectName(QString::fromUtf8("bt_quit"));
        sizePolicy2.setHeightForWidth(bt_quit->sizePolicy().hasHeightForWidth());
        bt_quit->setSizePolicy(sizePolicy2);
        bt_quit->setMinimumSize(QSize(150, 0));
        bt_quit->setFont(font3);

        verticalLayout->addWidget(bt_quit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 403, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        lbl_ev_title->setText(QApplication::translate("MainWindow", "\320\236\320\272\320\275\320\276 \321\201\320\276\320\261\321\213\321\202\320\270\320\271", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\277\320\276\320\274\320\276\320\263\320\260\321\202\320\265\320\273\321\214\320\275\321\213\320\265 \320\264\320\260\320\275\320\275\321\213\320\265", 0, QApplication::UnicodeUTF8));
        freq_label->setText(QApplication::translate("MainWindow", "\320\237\320\270\320\272\320\276\320\262\321\213\320\271 \321\203\321\200\320\276\320\262\320\265\320\275\321\214 \321\210\321\203\320\274\320\260 (\320\274\320\222)", 0, QApplication::UnicodeUTF8));
        lcd_lbl->setText(QApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\202\321\200\320\265\320\262\320\276\320\263", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\320\237\320\260\320\275\320\265\320\273\321\214 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274", 0, QApplication::UnicodeUTF8));
        rb_auto->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270\320\271", 0, QApplication::UnicodeUTF8));
        rb_manual->setText(QApplication::translate("MainWindow", "\320\240\321\203\321\207\320\275\320\276\320\271", 0, QApplication::UnicodeUTF8));
        time_label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\262\321\200\320\265\320\274\321\217", 0, QApplication::UnicodeUTF8));
        bt_start->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", 0, QApplication::UnicodeUTF8));
        bt_stop->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", 0, QApplication::UnicodeUTF8));
        bt_quit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GURZA_ALARM_H
