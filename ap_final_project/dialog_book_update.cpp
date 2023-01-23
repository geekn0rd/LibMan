#include "dialog_book_update.h"
#include "ui_dialog_book_update.h"
#include "sql.h"
#include "log.h"

Dialog_book_update::Dialog_book_update(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_book_update)
{
    ui->setupUi(this);
}

Dialog_book_update::~Dialog_book_update()
{
    delete ui;
}


void Dialog_book_update::set_data(QString title, QString author, QString about, QString pic_dir)
{
    ui->title_Edit_2->setText(title);
    ui->authorEdit_2->setText(author);
    ui->aboutEdit_2->setText(about);
    ui->picdirEdit_2->setText(pic_dir);
    this->rowid = book_rowid(title);
}

void Dialog_book_update::on_buttonBox_accepted()
{
    QString title, author, about, pic_dir;
    title = ui->title_Edit_2->text();
    author = ui->authorEdit_2->text();
    about = ui->aboutEdit_2->text();
    pic_dir = ui->picdirEdit_2->text();
    update_book(rowid, title, author, about, pic_dir);
    log_to_file("An admin successfully edited a book  with rowid=" + rowid + ".");
}

