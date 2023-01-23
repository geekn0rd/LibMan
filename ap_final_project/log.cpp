#include "log.h"
using namespace std;

void log_to_file(QString log)
{
    QString file_dir("../ap_final_project/log.txt");
    QFile file(file_dir);

    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&file);
        QDate cd = QDate::currentDate();
        QTime ct = QTime::currentTime();

        out << cd.toString() << ", " << ct.toString() << " : " << log << endl;
    }


    file.close();
    return;
}
