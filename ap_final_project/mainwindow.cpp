#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sql.h"
#include <QMessageBox>
#include <QChar>
#include "log.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    log_to_file("Application Started.");

    // Fix the window size
    this->setFixedSize(800, 600);

    m_ulitems = NULL;
    m_ulitems = NULL;
    ui->setupUi(this);
    ui->Pages->setCurrentIndex(0);
    QPixmap users("../ap_final_project/pics/users5.png");
    ui->users_icon->setPixmap(users);
    QPixmap books("../ap_final_project/pics/icon-book.jpg");
    ui->books_icon->setPixmap(books);
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../ap_final_project/database.db");
    if (!mydb.open())
    {
        ui->db_status->setText("Failed to open database!");
    }
    else
    {
        ui->db_status->setText("Connected...");
    }
    //update_userList();
}

MainWindow::~MainWindow()
{
    delete [] m_ulwidget;
    delete [] m_ulitems;
    delete ui;
    log_to_file("Application Ended.");
}

void MainWindow::update_bookList()
{
   /* if(m_ulitems != NULL)
        {delete [] m_ulitems;m_ulitems=NULL;}
    if(m_ulwidget !=NULL)
        {delete [] m_ulwidget;m_ulwidget=NULL;}*/

    QSqlQuery q("select * from books");
    m_ulitems=new QListWidgetItem[100];
    m_ulwidget=new book_list_item[100];

    int i = 0;
    while (q.next())
    {
        m_ulwidget[i].set_data(q.value(0).toString(),q.value(1).toString(),q.value(2).toString(), q.value(3).toString());
        m_ulitems[i].setSizeHint(QSize(559, 213));
        ui->list_books->addItem(&m_ulitems[i]);
        ui->list_books->setItemWidget(&m_ulitems[i],&m_ulwidget[i]);
        i++;
    }
 }
void MainWindow::update_bookList2()
{
    QSqlQuery q("select * from books");
    m_ulitems=new QListWidgetItem[100];
    m_ulwidget=new book_list_item[100];

    int i = 0;
    while (q.next())
    {
        m_ulwidget[i].set_data2(q.value(0).toString(),q.value(1).toString(),q.value(2).toString(), q.value(3).toString());
        m_ulitems[i].setSizeHint(QSize(559, 213));
        ui->admin_List->addItem(&m_ulitems[i]);
        ui->admin_List->setItemWidget(&m_ulitems[i],&m_ulwidget[i]);
        i++;
    }
 }
void MainWindow::on_pushButton_clicked()
{
    QString username, password;
    username =  ui->lineEdit_user->text();
    password = ui->lineEdit_pass_2->text();
    log_to_file("Someone with username=" + username + " and password=" + password +" is trying to sign in.");
    if (!mydb.isOpen())
    {
        log_to_file("Failed to open the database.");
    }

    int does_exist = number_of_users(username, password);
    if (does_exist == 1)
    {
        QSqlQuery qry;
        qry.exec("SELECT * FROM users WHERE username = '"+username+"' AND password='"+password+"'");
        qry.next();
        if (qry.value(3).toBool())
        {
            if (m_ulitems != NULL and m_ulwidget != NULL)
            {
                delete [] m_ulitems;
                m_ulitems=NULL;
                delete [] m_ulwidget;
                m_ulwidget=NULL;
            }
            update_bookList2();
            log_to_file("An admin with username=" + username + " successfully signed in.");
            ui->Pages->setCurrentIndex(3);
        }
        else
        {
            if (m_ulitems != NULL and m_ulwidget != NULL)
            {
                delete [] m_ulitems;
                m_ulitems=NULL;
                delete [] m_ulwidget;
                m_ulwidget=NULL;
            }
            log_to_file("A user with username=" + username + " successfully signed in.");
            update_bookList();
            ui->Pages->setCurrentIndex(1);
        }
     }
     else
     {
        QMessageBox::warning(this, "Log in", "Username or Password is not correct.\n"
                                                 "If you don't have an account you can sign up.");
        log_to_file("signning in failed.");
     }
    ui->lineEdit_user->setText("");
    ui->lineEdit_pass_2->setText("");

}


void MainWindow::on_pushButton_users_clicked()
{
    QString query = "SELECT * FROM users;";
    QSqlQueryModel *my_model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.exec(query);
    my_model->setQuery(qry);
    ui->dbtableView->setModel(my_model);
    log_to_file("An admin went to users page.");
    ui->Pages->setCurrentIndex(4);
}


void MainWindow::on_commandLinkButton_clicked()
{
    ui->Pages->setCurrentIndex(3);
}


void MainWindow::on_add_userButton_clicked()
{
    QString username, password, stu_no, is_admin;
    username =  ui->man_usernameEdit->text();
    password = ui->man_passwordEdit->text();
    stu_no =  ui->man_stu_noEdit->text();
    is_admin =  ui->man_is_adminEdit->text();
    if ((username == "" or stu_no == "" or password == "" or username == "admin") and (is_admin == "" or is_admin == '1' or is_admin == '0'))
    {
        QMessageBox::warning(this, "User Managment", "You can't leave fields empty.");
    }
    else if(add_user(username, password, stu_no, is_admin))
    {
        QMessageBox::information(this, "User Managment", "User has been successfully added.");
        log_to_file("An admin successfully added a user with username=" + username + ".");
    }
    else
    {
        QMessageBox::warning(this, "User Managment", "An error occurred.\n"
                                                     "Maybe this username already exists.");
    }
    ui->rowidlineEdit->setText("");
    ui->man_is_adminEdit->setText("");
    ui->man_usernameEdit->setText("");
    ui->man_stu_noEdit->setText("");
    ui->man_passwordEdit->setText("");
    QString query = "SELECT * FROM users;";
    QSqlQueryModel *my_model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.exec(query);
    my_model->setQuery(qry);
    ui->dbtableView->setModel(my_model);

}


void MainWindow::on_delete_userButton_clicked()
{
    QString username;
    username =  ui->man_usernameEdit->text();
    if (username == "")
    {
        QMessageBox::warning(this, "User Managment", "You can't leave username field empty.");
    }
    else if(delete_user(username))
    {
        QMessageBox::information(this, "User Managment", "User has been successfully removed.");
         log_to_file("An admin successfully removed a user with username=" + username + ".");
    }
    else
    {
        QMessageBox::warning(this, "User Managment", "An error occurred.\n"
                                                     "Maybe this username doesn't exist.");
    }
    ui->rowidlineEdit->setText("");
    ui->man_is_adminEdit->setText("");
    ui->man_usernameEdit->setText("");
    ui->man_stu_noEdit->setText("");
    ui->man_passwordEdit->setText("");
    QString query = "SELECT * FROM users;";
    QSqlQueryModel *my_model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.exec(query);
    my_model->setQuery(qry);
    ui->dbtableView->setModel(my_model);

}

void MainWindow::on_update_userButton_clicked()
{
    QString rowid, username, password, stu_no, is_admin;
    rowid = ui->rowidlineEdit->text();
    username =  ui->man_usernameEdit->text();
    password = ui->man_passwordEdit->text();
    stu_no =  ui->man_stu_noEdit->text();
    is_admin =  ui->man_is_adminEdit->text();
    if ((username == "" or stu_no == "" or password == "" or username == "admin" or rowid == "1")
            and (is_admin == '1' or is_admin == '0'))
    {
        QMessageBox::warning(this, "User Managment", "Update can't be done.\n"
                                                     "Check your inputs.");
    }
    else if(update_user(rowid, username, password, stu_no, is_admin))
    {
        QMessageBox::information(this, "User Managment", "User has been successfully edited.");
         log_to_file("An admin successfully edited a user rowid=" + rowid + ".");
    }
    else
    {
        QMessageBox::warning(this, "User Managment", "An error occurred.\n"
                                                     "Maybe you can't make this change.");
    }
    ui->rowidlineEdit->setText("");
    ui->man_is_adminEdit->setText("");
    ui->man_usernameEdit->setText("");
    ui->man_stu_noEdit->setText("");
    ui->man_passwordEdit->setText("");
    QString query = "SELECT * FROM users;";
    QSqlQueryModel *my_model = new QSqlQueryModel();
    QSqlQuery qry;
    qry.exec(query);
    my_model->setQuery(qry);
    ui->dbtableView->setModel(my_model);
}


void MainWindow::on_pushButton_books_clicked()
{
    update_bookList2();
     log_to_file("An admin went to books page.");
    ui->Pages->setCurrentIndex(2);
}


void MainWindow::on_commandLinkButton_3_clicked()
{
    ui->Pages->setCurrentIndex(0);
}


void MainWindow::on_commandLinkButton_4_clicked()
{
    ui->Pages->setCurrentIndex(3);
}


void MainWindow::on_commandLinkButton_5_clicked()
{
    ui->Pages->setCurrentIndex(0);
}



void MainWindow::on_pushButton_signup_clicked()
{
    ui->Pages->setCurrentIndex(5);
}


void MainWindow::on_commandLinkButton_2_clicked()
{
    ui->Pages->setCurrentIndex(0);
}

void MainWindow::on_signUPButton_clicked()
{
    QString stu_no, username, password, confirm;
    stu_no =  ui->sign_up_stuno->text();
    username =  ui->sign_up_username->text();
    password = ui->sign_up_pass->text();
    confirm = ui->sign_u_confirm->text();
    if (confirm == "" or password == "" or username == "" or stu_no == "")
    {
        QMessageBox::warning(this, "Opening an account", "Fields Can't be empty!");
        return;
    }
    else if (number_of_users(username) > 0)
    {
        QMessageBox::warning(this, "Opening an account", "This username already exists!");
    }
    else if (password != confirm)
    {
        QMessageBox::warning(this, "Opening an account", "Passwords Don't Match!");
        ui->sign_up_pass->setText("");
        ui->sign_u_confirm->setText("");
        return;
    }
    else
    {
        if (add_user(username, password, stu_no))
        {
            QMessageBox::information(this, "User Managment", "You have successfully registered.\n"
                                                             "You can now login from login page.");
             log_to_file("Someone with stu_no="  + stu_no + " and username =" + username +" opend an account.");
        }
    }
    ui->sign_up_stuno->setText("");
    ui->sign_up_username->setText("");
    ui->sign_up_pass->setText("");
    ui->sign_u_confirm->setText("");
}


void MainWindow::on_add_bookButton_clicked()
{
    QString title, author, about, pic_dir;
    title = ui->title_Edit->text();
    author = ui->authorEdit->text();
    about = ui->aboutEdit->text();
    pic_dir = ui->picdirEdit->text();

    if (title == "" or about == "" or author == "" or pic_dir == "")
    {
        QMessageBox::warning(this, "Book Management", "Fields Can't be empty!");
        return;
    }
    else
    {
        if (add_book(title, author,about, pic_dir))
        {
            QMessageBox::information(this, "User Managment", "Book successfully added.");
            log_to_file("An admin successfully added a book with title=" + title + ".");
            update_bookList2();
        }
        else
        {
             QMessageBox::warning(this, "Book Management", "This Title already exists!");
        }
    }

    ui->title_Edit->setText("");
    ui->authorEdit->setText("");
    ui->aboutEdit->setText("");
    ui->picdirEdit->setText("");
}

void MainWindow::on_refresh_book_clicked()
{
    log_to_file("Trying to refresh the list of books.");
    QSqlQuery q("SELECT COUNT(*) FROM books");
    q.next();

    // Getting the number of books
    int j =  q.value(0).toInt();
    for (int i = 0; i < j; i++)
    {
        delete ui->list_books->takeItem(i);
    }
    delete [] m_ulitems;
    m_ulitems=NULL;
    delete [] m_ulwidget;
    m_ulwidget=NULL;
    update_bookList2();
}

