#ifndef DIALOG_BOOK_UPDATE_H
#define DIALOG_BOOK_UPDATE_H

#include <QDialog>

namespace Ui {
class Dialog_book_update;
}

class Dialog_book_update : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_book_update(QWidget *parent = nullptr);
    ~Dialog_book_update();
    void set_data(QString title, QString author, QString about, QString pic_dir);
private slots:
    void on_buttonBox_accepted();

private:
    QString rowid = "";
    Ui::Dialog_book_update *ui;
};

#endif // DIALOG_BOOK_UPDATE_H
