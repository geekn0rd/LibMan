#ifndef BOOK_LIST_ITEM_H
#define BOOK_LIST_ITEM_H

#include <QWidget>
#include <QDebug>
namespace Ui {
class book_list_item;
}

class book_list_item : public QWidget
{
    Q_OBJECT

public:
    explicit book_list_item(QWidget *parent = nullptr);
    ~book_list_item();
    void set_data(QString, QString, QString, QString);
    void set_data2(QString, QString, QString, QString);
private slots:
    void on_pushButton_clicked();

    void on_updateButton_clicked();

private:
    Ui::book_list_item *ui;
};



#endif // BOOK_LIST_ITEM_H
