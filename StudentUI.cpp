#include "StudentUI.h"
#include "LoginUI.h"
#include "ViewSubjectsUI.h"
#include "ui_StudentUI.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QTextEdit>

StudentUI::StudentUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StudentUI)
{
    ui->setupUi(this);
    connect(ui->viewGradesButton, &QPushButton::clicked, this, &StudentUI::viewGradesButton);
    connect(ui->exitButton, &QPushButton::clicked, this, &StudentUI::exitButton);
    connect(ui->viewSubjectsButton, &QPushButton::clicked, this, &StudentUI::viewSubjectsButton);
}

StudentUI::~StudentUI()
{
    delete ui;
}
void StudentUI::viewGradesButton(){


    bool ok;
    QString studentName = QInputDialog::getText(this, "Studento vardas", "Įveskite savo vardą:", QLineEdit::Normal, "", &ok);
    if (!ok || studentName.isEmpty()) return;

    QString studentSurname = QInputDialog::getText(this, "Studento pavardė", "Įveskite savo pavardę:", QLineEdit::Normal, "", &ok);
    if (!ok || studentSurname.isEmpty()) return;


    QString studentID = getStudentID(studentName, studentSurname);
    if (studentID.isEmpty()) {
        QMessageBox::information(this, "Problema", "Studentas nerastas.");
        return;
    }


    QFile gradesFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades.txt");
    if (!gradesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti 'grades.txt' failo.");
        return;
    }

    QTextStream gradesIn(&gradesFile);
    QStringList studentGrades;


    while (!gradesIn.atEnd()) {
        QString line = gradesIn.readLine();
        QStringList fields = line.split('|');

        if (fields.size() == 5 && fields[3] == studentID) {
            QString groupID = fields[0];
            QString teacherID = fields[1];
            QString subjectID = fields[2];
            QString grade = fields[4];
            studentGrades.append("Grupė: " + groupID + ", Paskaita: " + subjectID + ", Pažymys: " + grade);
        }
    }

    gradesFile.close();


    if (studentGrades.isEmpty()) {
        QMessageBox::information(this, "Informacija", "Nėra pažymių šiam studentui.");
        return;
    }


    QString result = studentGrades.join("\n");
    QMessageBox::information(this, "Jūsų pažymiai", result);
}

QString StudentUI::getStudentID(const QString &name, const QString &surname) {
    QFile studentsFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt");
    if (!studentsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti 'students.txt' failo.");
        return "";
    }

    QTextStream studentIn(&studentsFile);


    while (!studentIn.atEnd()) {
        QString line = studentIn.readLine();
        QStringList fields = line.split('|');
        if (fields.size() == 4 && fields[1] == name && fields[2] == surname) {
            studentsFile.close();
            return fields[0];
        }
    }

    studentsFile.close();
    return "";
}
void StudentUI::exitButton(){
    this->close();
    QMessageBox::information(this, "Atsijungta", "Sėkmingai atsijungta!");
    LoginUI *loginWindow = new LoginUI(this);
    loginWindow->show();
}
void StudentUI::viewSubjectsButton(){
    ViewSubjectsUI *viewSubjectWindow = new ViewSubjectsUI(this);
    viewSubjectWindow->show();
}
