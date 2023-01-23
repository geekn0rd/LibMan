#include <QString>
#include <QtSql>

int number_of_users(QString username, QString password)
{
    QSqlQuery qry;

    if (qry.exec("SELECT * FROM users WHERE username = '"+username+"' AND password='"+password+"';"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
        }
        return count;
    }
    else
    {
        return -1;
    }
}

int number_of_users(QString username)
{
    QSqlQuery qry;

    if (qry.exec("SELECT * FROM users WHERE username = '"+username+"';"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
        }
        return count;
    }
    else
    {
        return -1;
    }
}

int number_of_users_rowid(QString rowid)
{
    QSqlQuery qry;

    if (qry.exec("SELECT * FROM users WHERE rowid = '"+rowid+"';"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
        }
        return count;
    }
    else
    {
        return -1;
    }
}

bool add_user(QString username, QString password, QString student_number, QString is_admin = "0")
{
    if (number_of_users(username) == 0)
    {
        QString query = "INSERT INTO users (username, password, stu_no, is_admin) VALUES "
                            "('"+username+"','"+password+"', '"+student_number+"', '"+is_admin+"');";
        QSqlQuery qry;
        qry.exec(query);

        return true;
    }
    else
    {
        return false;
    }
}

bool delete_user(QString username)
{
    if (number_of_users(username) != 0 and username != "admin")
    {
        QString query = "DELETE FROM users WHERE username = '"+username+"';";
        QSqlQuery qry;
        qry.exec(query);

        return true;
    }
    else
    {
        return false;
    }
}

bool update_user(QString rowid, QString username, QString password, QString student_number, QString is_admin)
{
    if (number_of_users_rowid(rowid) == 1)
    {
        QString query = "UPDATE users SET username = '"+username+"', password = '"+password+"', stu_no = '"+
                student_number+"', is_admin = '"+is_admin+"' WHERE rowid = "+rowid+";";
        QSqlQuery qry;
        qry.exec(query);

        return true;
    }
    else
    {
        return false;
    }


}

bool delete_book(QString title)
{
    QString query = "DELETE FROM books WHERE title = '"+title+"';";
    QSqlQuery qry;
    qry.exec(query);
    return true;
}

int number_of_books(QString title)
{
    QSqlQuery qry;

    if (qry.exec("SELECT * FROM books WHERE title = '"+title+"';"))
    {
        int count = 0;
        while (qry.next())
        {
            count++;
        }
        return count;
    }
    else
    {
        return -1;
    }
}

bool add_book(QString title, QString author, QString about, QString pic_dir = "NULL")
{
    if (number_of_books(title) == 0)
    {
        QString query = "INSERT INTO books (title, author, about, pic_address) VALUES "
                            "('"+title+"','"+author+"', '"+about+"', '"+pic_dir+"');";
        QSqlQuery qry;
        qry.exec(query);

        return true;
    }
    else
    {
        return false;
    }
}


QString book_rowid(QString title)
{
    QString query = "SELECT rowid FROM books WHERE title = '"+title+"';";
    QSqlQuery qry;
    qry.exec(query);
    if(qry.next())
    {
        return qry.value(0).toString();
    }
    return "-1";
}

bool update_book(QString rowid, QString title, QString author, QString about, QString pic_dir)
{
    QString query = "UPDATE books SET title = '"+title+"', author = '"+author+"', about = '"+
            about+"', pic_address = '"+pic_dir+"' WHERE rowid = "+rowid+";";
    QSqlQuery qry;
    qry.exec(query);

    return true;

}
