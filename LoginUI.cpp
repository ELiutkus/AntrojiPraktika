#include "LoginUI.h"
#include "AdminUI.h"
#include "TeacherUI.h"
#include "StudentUI.h"
#include "ui_LoginUI.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

LoginUI::LoginUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginUI)
{
    ui->setupUi(this);
    connect(ui->loginButtonAdmin, &QPushButton::clicked, this, &LoginUI::LoginButtonAdminClicked);
    connect(ui->loginButtonTeacher, &QPushButton::clicked, this, &LoginUI::LoginButtonTeacherClicked);
    connect(ui->loginButtonStudent, &QPushButton::clicked, this, &LoginUI::LoginButtonStudentClicked);
}

LoginUI::~LoginUI()
{
    delete ui;
}

void LoginUI::LoginButtonAdminClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti tiek vartotojo vardą, tiek slaptažodį.");
        return;
    }
        if (checkCredentials("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/admins.txt", username, password)) {
            QMessageBox::information(this, "Prisijungta!", "Sėkmingai prisijungėte kaip administratorius!");
            this->close();
            AdminUI *adminWindow = new AdminUI(this);
            adminWindow->show();
        } else {
            QMessageBox::warning(this, "Klaida", "Netinkami prisijungimo duomenys!");
        }
}

void LoginUI::LoginButtonTeacherClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti tiek vartotojo vardą, tiek slaptažodį.");
        return;
    }
        if (checkCredentials("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt", username, password)) {
            QMessageBox::information(this, "Prisijungta!", "Sėkmingai prisijungėte kaip dėstytojas!");
            this->close();
            TeacherUI *teacherWindow = new TeacherUI(this);
            teacherWindow->show();
        } else {
            QMessageBox::warning(this, "Klaida", "Netinkami prisijungimo duomenys!");
        }
}
void LoginUI::LoginButtonStudentClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti tiek vartotojo vardą, tiek slaptažodį.");
        return;
    }
    if (checkCredentials("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt", username, password)) {
        QMessageBox::information(this, "Prisijungta!", "Sėkmingai prisijungėte kaip studentas!");
        this->close();
        StudentUI *studentWindow = new StudentUI(this);
        studentWindow->show();
    } else {
        QMessageBox::warning(this, "Klaida", "Netinkami prisijungimo duomenys!");
    }
}
bool LoginUI::checkCredentials(const QString &filename, const QString &username, const QString &password)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Nepavyko atidaryti failo: " << filename;
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("|");


        if (fields.size() > 2) {
            if (fields[1] == username && fields[2] == password) {
                file.close();
                return true;
        }
        }else{
            qDebug() << "Netinkamas duomenų formatas eilutėje: " << line;
        }
    }
    file.close();
    return false;
}
