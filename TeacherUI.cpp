#include "TeacherUI.h"
#include "ViewSubjectsUI.h"
#include "ui_TeacherUI.h"
#include "LoginUI.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QFileDialog>
#include <QTextEdit>

TeacherUI::TeacherUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherUI)
{
    ui->setupUi(this);

    connect(ui->saveGradeButton, &QPushButton::clicked, this, &TeacherUI::saveGrade);
    connect(ui->deleteGradeButton, &QPushButton::clicked, this, &TeacherUI::deleteGrade);
    connect(ui->exitButton, &QPushButton::clicked, this, &TeacherUI::exitButton);
    connect(ui->viewSubjectsButton, &QPushButton::clicked, this, &TeacherUI::viewSubjectsButton);
    connect(ui->viewGradesButton, &QPushButton::clicked, this, &TeacherUI::viewGradesButton);
    connect(ui->findStudentIDButton, &QPushButton::clicked, this, &TeacherUI::findStudentIDButton);
}

TeacherUI::~TeacherUI()
{
    delete ui;
}

void TeacherUI::saveGrade()
{
    QString teacherID = ui->teacherIDLineEdit->text();
    QString groupID = ui->groupIDLineEdit->text();
    QString studentID = ui->studentIDLineEdit->text();
    QString subjectID = ui->subjectIDLineEdit->text();
    QString grade = ui->gradeLineEdit->text();


    if (!checkTeacherExistence(teacherID)) {
        QMessageBox::warning(this, "Klaida", "Dėstytojas su tokiu ID neegzistuoja.");
        return;
    }


    if (!checkTeacherExistence(subjectID)) {
        QMessageBox::warning(this, "Klaida", "Paskaita su tokiu ID neegzistuoja.");
        return;
    }

    QFile file("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti grades.txt failo.");
        return;
    }

    QTextStream out(&file);
    out << groupID << "|" << teacherID << "|" << subjectID << "|" << studentID << "|" << grade << "\n";
    file.close();

    QMessageBox::information(this, "Atlikta", "Pažymys išsaugotas!");
}

void TeacherUI::deleteGrade()
{
    QString teacherID = ui->teacherIDLineEdit->text();
    QString studentID = ui->studentIDLineEdit->text();
    QString subjectID = ui->subjectIDLineEdit->text();

    if (!checkTeacherExistence(teacherID)) {
        QMessageBox::warning(this, "Klaida", "Dėstytojas su tokiu ID neegzistuoja.");
        return;
    }

    if (!checkTeacherExistence(subjectID)) {
        QMessageBox::warning(this, "Klaida", "Paskaita su tokiu ID neegzistuoja.");
        return;
    }

    QFile file("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades.txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti grades.txt failo.");
        return;
    }

    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }
    file.close();

    bool gradeFound = false;
    QFile fileOut("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades_temp.txt");
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko sukurti laikino failo.");
        return;
    }

    QTextStream out(&fileOut);
    for (const QString& line : lines) {
        QStringList parts = line.split('|');
        if (parts.at(1) == teacherID && parts.at(3) == studentID && parts.at(2) == subjectID) {
            gradeFound = true;
        } else {
            out << line << "\n";
        }
    }
    fileOut.close();

    if (gradeFound) {
        QFile::remove("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades.txt");
        QFile::rename("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades_temp.txt", "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades.txt");
        QMessageBox::information(this, "Sėkmė", "Pažymys pašalintas!");
    } else {
        QMessageBox::warning(this, "Klaida", "Pažymys nerastas.");
    }
}

bool TeacherUI::checkTeacherExistence(const QString& teacherID)
{
    QFile file("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');
        if (parts.at(0) == teacherID) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool TeacherUI::checkSubjectExistence(const QString& subjectID)
{
    QFile file("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');
        if (parts.at(0) == subjectID) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}
void TeacherUI::exitButton(){
    this->close();
    QMessageBox::information(this, "Atsijungta", "Sėkmingai atsijungta!");
    LoginUI *loginWindow = new LoginUI(this);
    loginWindow->show();
}
void TeacherUI::viewSubjectsButton(){
    ViewSubjectsUI *viewSubjectWindow = new ViewSubjectsUI(this);
    viewSubjectWindow->show();
}
QString TeacherUI::getStudentID(const QString &name, const QString &surname) {
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
void TeacherUI::viewGradesButton(){


    bool ok;
    QString studentName = QInputDialog::getText(this, "Studento vardas", "Įveskite studento vardą:", QLineEdit::Normal, "", &ok);
    if (!ok || studentName.isEmpty()) return;

    QString studentSurname = QInputDialog::getText(this, "Studento pavardė", "Įveskite studento pavardę:", QLineEdit::Normal, "", &ok);
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
void TeacherUI::findStudentIDButton(){

    bool ok;
    QString studentName = QInputDialog::getText(this, "Studento vardas", "Įveskite studento vardą:", QLineEdit::Normal, "", &ok);
    if (!ok || studentName.isEmpty()) return;

    QString studentSurname = QInputDialog::getText(this, "Studento pavardė", "Įveskite studento pavardę:", QLineEdit::Normal, "", &ok);
    if (!ok || studentSurname.isEmpty()) return;


    QString studentID = getStudentID(studentName, studentSurname);
    if (studentID.isEmpty()) {
        QMessageBox::information(this, "Problema", "Studentas nerastas.");
    } else {
        QMessageBox::information(this, "Studento ID", "Studento ID: " + studentID);
    }

}
