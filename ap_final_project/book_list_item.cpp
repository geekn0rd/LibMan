#include "book_list_item.h"
#include "ui_book_list_item.h"
#include <QPixmap>
#include <QMessageBox>
#include "sql.h"
#include "mainwindow.h"
#include "dialog_book_update.h"
#include "log.h"

book_list_item::book_list_item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::book_list_item)
{
    ui->setupUi(this);
}

book_list_item::~book_list_item()
{
    delete ui;
}

void book_list_item::set_data(QString name, QString author, QString about, QString pic_dir)
{
    ui->bookPages->setCurrentIndex(0);
    ui->label_title->setText(name);
    ui->label_author->setText(author);
    ui->label_->setText(about);
    if (pic_dir == "NULL")
    {
        QPixmap pix("../ap_final_project/pics/default_book_cover_2015.jpg");
        ui->book_cover->setPixmap(pix);
    }
    else
    {
        QPixmap pic(pic_dir);
        ui->book_cover->setPixmap(pic);
    }
}

void book_list_item::set_data2(QString name, QString author, QString about, QString pic_dir)
{
    ui->bookPages->setCurrentIndex(1);
    ui->label_title_5->setText(name);
    ui->label_author_5->setText(author);
    ui->about2->setText(about);
    ui->pic_dir->setText(pic_dir);
    if (pic_dir == "NULL")
    {
        QPixmap pix("../ap_final_project/pics/default_book_cover_2015.jpg");
        ui->book_cover_2->setPixmap(pix);
    }
    else
    {
        QPixmap pic(pic_dir);
        ui->book_cover_2->setPixmap(pic);
    }
}

void book_list_item::on_pushButton_clicked()
{
    QString title = ui->label_title_5->text();
    QMessageBox::StandardButton sure;
    sure = QMessageBox::question(this, "Delete", "Are You Sure?",QMessageBox::Yes|QMessageBox::No);
    if (sure == QMessageBox::Yes)
    {
        delete_book(title);
        log_to_file("An admin successfully removed a book  with title=" + title + ".");
    }
    else
    {
      log_to_file("An admin clicked cancel when trying to delete a book  with title=" + title + ".");
    }
}


void book_list_item::on_updateButton_clicked()
{
    QString title, author, about, pic_dir;
    title = ui->label_title_5->text();
    author = ui->label_author_5->text();
    about = ui->about2->text();
    pic_dir = ui->pic_dir->text();
    log_to_file("An admin clicked delete on a book  with title=" + title + ".");
    Dialog_book_update dialog;
    dialog.setModal(true);
    dialog.set_data(title, author, about, pic_dir);
    dialog.exec();

}

