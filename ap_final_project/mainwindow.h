#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QListWidgetItem>
#include <QPixmap>
#include "book_list_item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void update_bookList();
    void update_bookList2();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_users_clicked();

    void on_commandLinkButton_clicked();

    void on_add_userButton_clicked();

    void on_delete_userButton_clicked();

    void on_update_userButton_clicked();

    void on_pushButton_books_clicked();

    void on_commandLinkButton_3_clicked();

    void on_commandLinkButton_4_clicked();

    void on_commandLinkButton_5_clicked();

    void on_pushButton_signup_clicked();

    void on_commandLinkButton_2_clicked();

    void on_signUPButton_clicked();

    void on_add_bookButton_clicked();

    void on_refresh_book_clicked();

private:
    Ui::MainWindow *ui;
    QListWidgetItem *m_ulitems;
    book_list_item *m_ulwidget;
    QSqlDatabase mydb;
};
#endif // MAINWINDOW_H
