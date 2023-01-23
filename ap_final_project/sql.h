#ifndef SQL_H
#define SQL_H

#include <QString>
#include <QtSql>

int number_of_users(QString username, QString password);
int number_of_users(QString username);
int number_of_users_rowid(QString rowid);
bool add_user(QString username, QString password, QString student_number, QString is_admin = "0");
bool delete_user(QString username);
bool update_user(QString rowid, QString username, QString password, QString student_number, QString is_admin);

bool delete_book(QString title);
int number_of_books(QString title);
QString book_rowid(QString title);
bool add_book(QString title, QString author, QString about, QString pic_dir = "NULL");
bool update_book(QString rowid, QString title, QString author, QString about, QString pic_dir);

#endif // SQL_H
