#include "AdminUI.h"
#include "LoginUI.h"
#include "ViewUI.h"
#include "ui_AdminUI.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QTextEdit>

AdminUI::AdminUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminUI)
{
    ui->setupUi(this);


    connect(ui->addUserButton, &QPushButton::clicked, this, &AdminUI::onAddUserButtonClicked);
    connect(ui->deleteUserButton, &QPushButton::clicked, this, &AdminUI::onRemoveUserButtonClicked);
    connect(ui->createGroupButton, &QPushButton::clicked, this, &AdminUI::onCreateGroupButtonClicked);
    connect(ui->assignGroupButton, &QPushButton::clicked, this, &AdminUI::onAssignGroupButtonClicked);
    connect(ui->deleteGroupButton, &QPushButton::clicked, this, &AdminUI::onDeleteGroupButtonClicked);
    connect(ui->addSubjectButton, &QPushButton::clicked, this, &::AdminUI::onCreateSubjectButtonClicked);
    connect(ui->assignSubjectButton, &QPushButton::clicked, this, &::AdminUI::onAssignSubjectButtonClicked);
    connect(ui->deleteSubjectButton, &QPushButton::clicked, this, &::AdminUI::onDeleteSubjectButtonClicked);
    connect(ui->logOffButton, &QPushButton::clicked, this, &::AdminUI::onLogOffButtonClicked);
    connect(ui->viewFileButton, &QPushButton::clicked, this, &::AdminUI::onViewButtonClicked);
}

AdminUI::~AdminUI()
{
    delete ui;
}

int AdminUI::getNextID(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Nepavyko atidaryti failo: " << filename;
        return 1;
    }

    int maxID = 0;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("|");
        if (fields.size() > 0) {
            int id = fields[0].toInt();
            if (id > maxID) {
                maxID = id;
            }
        }
    }
    file.close();
    return maxID + 1;
}

void AdminUI::appendToFile(const QString &filename, const QString &data)
{
    QFile file(filename);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo įrašymui: " + filename);
        return;
    }

    QTextStream out(&file);
    out << data << "\n";
    file.close();
}

void AdminUI::removeFromFile(const QString &filename, int userID)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo pašalinimui: " + filename);
        return;
    }


    QTextStream in(&file);
    QStringList lines;
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }


    file.resize(0);
    QTextStream out(&file);

    bool found = false;
    for (const QString &line : lines) {
        QStringList fields = line.split("|");
        if (fields[0].toInt() == userID) {
            found = true;
            continue;
        }
        out << line << "\n";
    }

    if (found) {
        QMessageBox::information(this, "Pašalinta", "Vartotojas pašalintas sėkmingai!");
    } else {
        QMessageBox::warning(this, "Klaida", "Vartotojas su tokiu ID nerastas!");
    }

    file.close();
}

void AdminUI::onAddUserButtonClicked()
{

    bool ok;
    QString name = QInputDialog::getText(this, "Pridėti vartotoją", "Įveskite vardą:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Vardas negali būti tuščias!");
        return;
    }


    QString surname = QInputDialog::getText(this, "Pridėti vartotoją", "Įveskite pavardę:", QLineEdit::Normal, "", &ok);
    if (!ok || surname.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Pavardė negali būti tuščia!");
        return;
    }


    QStringList roles = {"Studentas", "Dėstytojas"};
    QString role = QInputDialog::getItem(this, "Pasirinkite rolę", "Rolė:", roles, 0, false, &ok);
    if (!ok || role.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Rolė turi būti pasirinkta!");
        return;
    }


    QString filename = (role == "Studentas") ? "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt" : "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt";




    int newID = getNextID(filename);


    QString newUserEntry;
    if (role == "Studentas") {
        newUserEntry = QString("%1|%2|%3").arg(newID).arg(name).arg(surname);
    } else {
        newUserEntry = QString("%1|%2|%3").arg(newID).arg(name).arg(surname);
    }

    appendToFile(filename, newUserEntry);

    QMessageBox::information(this, "Atlikta", "Vartotojas pridėtas sėkmingai!");
}

void AdminUI::onRemoveUserButtonClicked()
{

    bool ok;
    int userID = QInputDialog::getInt(this, "Pašalinti vartotoją", "Įveskite vartotojo ID:", 0, 1, 10000, 1, &ok);
    if (!ok) {
        return;
    }


    QStringList roles = {"Studentas", "Dėstytojas"};
    QString role = QInputDialog::getItem(this, "Pasirinkite rolę", "Rolė:", roles, 0, false, &ok);
    if (!ok || role.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Rolė turi būti pasirinkta!");
        return;
    }


    QString filename = (role == "Studentas") ? "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt" : "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt";


    removeFromFile(filename, userID);
}
void AdminUI::onCreateGroupButtonClicked()
{
    bool ok;
    QString groupName = QInputDialog::getText(this, "Sukurti grupę", "Įveskite grupės pavadinimą:", QLineEdit::Normal, "", &ok);

    if (ok && !groupName.isEmpty()) {
        QFile file("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/groups.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo grupėms.");
            return;
        }

        QTextStream out(&file);
        out << groupName << "\n";

        file.close();
        QMessageBox::information(this, "Atlikta", "Grupė buvo sukurta!");
    } else if (!ok) {
        QMessageBox::information(this, "Atšaukta", "Grupės kūrimas atšauktas.");
    } else {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti grupės pavadinimą.");
    }
}
void AdminUI::onAssignGroupButtonClicked()
{
    bool ok;
    QString studentId = QInputDialog::getText(this, "Priskirti grupę studentui", "Įveskite studento ID:", QLineEdit::Normal, "", &ok);
    if (!ok || studentId.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti studento ID.");
        return;
    }

    QString groupName = QInputDialog::getText(this, "Priskirti grupę", "Įveskite grupės pavadinimą:", QLineEdit::Normal, "", &ok);
    if (!ok || groupName.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti grupės pavadinimą.");
        return;
    }


    QFile groupFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/groups.txt");
    if (!groupFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo su grupėmis.");
        return;
    }

    bool groupExists = false;
    QTextStream groupStream(&groupFile);
    while (!groupStream.atEnd()) {
        if (groupStream.readLine().trimmed() == groupName) {
            groupExists = true;
            break;
        }
    }
    groupFile.close();

    if (!groupExists) {
        QMessageBox::warning(this, "Klaida", "Tokios grupės nėra.");
        return;
    }


    QFile studentFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt");
    if (!studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo su studentais.");
        return;
    }

    QStringList updatedStudents;
    bool studentFound = false;
    QTextStream studentStream(&studentFile);
    while (!studentStream.atEnd()) {
        QString line = studentStream.readLine().trimmed();
        QStringList parts = line.split("|");

        if (parts.size() > 0 && parts[0].trimmed() == studentId) {
            studentFound = true;


            if (parts.size() >= 4 && parts[3].trimmed() == groupName) {
                QMessageBox::information(this, "Informacija", "Studentas jau yra šioje grupėje.");
                return;
            }


            if (parts.size() == 3) {
                line += "|" + groupName;
            } else if (parts.size() == 4) {
                parts[3] = groupName;
                line = parts.join("|");
            }
        }

        updatedStudents.append(line);
    }
    studentFile.close();

    if (!studentFound) {
        QMessageBox::warning(this, "Klaida", "Studentas su nurodytu ID nerastas.");
        return;
    }


    if (!studentFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko perrašyti failo su studentais.");
        return;
    }

    QTextStream out(&studentFile);
    for (const QString &line : updatedStudents) {
        out << line << "\n";
    }
    studentFile.close();

    QMessageBox::information(this, "Atlikta", "Grupė sėkmingai priskirta studentui!");


}

void AdminUI::onDeleteGroupButtonClicked()
{
    bool ok;
    QString groupName = QInputDialog::getText(this, "Ištrinti grupę", "Įveskite grupės pavadinimą:", QLineEdit::Normal, "", &ok);
    if (!ok || groupName.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti grupės pavadinimą.");
        return;
    }


    QFile groupFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/groups.txt");
    if (!groupFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo su grupėmis.");
        return;
    }

    QStringList updatedGroups;
    QTextStream groupStream(&groupFile);
    bool groupFound = false;
    while (!groupStream.atEnd()) {
        QString line = groupStream.readLine().trimmed();
        if (line == groupName) {
            groupFound = true;
        } else {
            updatedGroups.append(line);
        }
    }
    groupFile.close();

    if (!groupFound) {
        QMessageBox::warning(this, "Klaida", "Tokios grupės nėra.");
        return;
    }

    if (!groupFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko perrašyti failo su grupėmis.");
        return;
    }

    QTextStream outGroup(&groupFile);
    for (const QString &line : updatedGroups) {
        outGroup << line << "\n";
    }
    groupFile.close();


    QFile studentFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt");
    if (!studentFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo su studentais.");
        return;
    }

    QStringList updatedStudents;
    QTextStream studentStream(&studentFile);
    while (!studentStream.atEnd()) {
        QString line = studentStream.readLine().trimmed();
        QStringList parts = line.split("|");

        if (parts.size() == 4 && parts[3].trimmed() == groupName) {

            parts.removeLast();
            line = parts.join("|");
        }
        updatedStudents.append(line);
    }
    studentFile.close();

    if (!studentFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko perrašyti failo su studentais.");
        return;
    }

    QTextStream outStudent(&studentFile);
    for (const QString &line : updatedStudents) {
        outStudent << line << "\n";
    }
    studentFile.close();

    QMessageBox::information(this, "Atlikta", "Grupė ir jos ryšiai su studentais buvo sėkmingai pašalinti.");
}

void AdminUI::onCreateSubjectButtonClicked()
{

    bool ok;
    QString subjectName = QInputDialog::getText(this, "Sukurti dalyką", "Įveskite dėstomo dalyko pavadinimą:", QLineEdit::Normal, "", &ok);

    if (!ok || subjectName.isEmpty()) {
        QMessageBox::warning(this, "Klaida", "Prašome įvesti dėstomo dalyko pavadinimą.");
        return;
    }


    QFile subjectFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt");
    if (!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo su dalykais.");
        return;
    }


    int lastId = 0;
    QTextStream in(&subjectFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.size() >= 2) {
            bool ok;
            int id = parts[0].toInt(&ok);
            if (ok && id > lastId) {
                lastId = id;
            }
        }
    }
    subjectFile.close();

    int newId = lastId + 1;


    if (!subjectFile.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo įrašymui.");
        return;
    }

    QTextStream out(&subjectFile);
    out << newId << "|" << subjectName << "\n";
    subjectFile.close();

    QMessageBox::information(this, "Atlikta", "Dėstomas dalykas sėkmingai pridėtas.");
}
void AdminUI::onAssignSubjectButtonClicked()
{

    QFile teacherFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt");
    if (!teacherFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti teachers.txt failo.");
        return;
    }

    QStringList teachers;
    QTextStream teacherIn(&teacherFile);
    while (!teacherIn.atEnd()) {
        QString line = teacherIn.readLine();
        QStringList parts = line.split("|");
        if (parts.size() >= 2) {
            teachers.append(parts[0] + " | " + parts[1] + " " + parts[2]);
        }
    }
    teacherFile.close();


    bool ok;
    QString selectedTeacher = QInputDialog::getItem(this, "Pasirinkti dėstytoją", "Pasirinkite dėstytoją:", teachers, 0, false, &ok);
    if (!ok || selectedTeacher.isEmpty()) {
        return;
    }

    QString selectedTeacherId = selectedTeacher.split(" | ").first();


    QFile subjectFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt");
    if (!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti subject.txt failo.");
        return;
    }

    QStringList subjects;
    QTextStream subjectIn(&subjectFile);
    while (!subjectIn.atEnd()) {
        QString line = subjectIn.readLine();
        QStringList parts = line.split("|");
        if (parts.size() >= 2) {
            subjects.append(parts[0] + " | " + parts[1]);
        }
    }
    subjectFile.close();


    QString selectedSubject = QInputDialog::getItem(this, "Pasirinkti dėstomą dalyką", "Pasirinkite dėstomą dalyką:", subjects, 0, false, &ok);
    if (!ok || selectedSubject.isEmpty()) {
        return;
    }

    QString selectedSubjectId = selectedSubject.split(" | ").first();


    QFile tempFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers_temp.txt");
    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko sukurti laikino failo.");
        return;
    }

    if (!teacherFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko perskaityti teachers.txt failo.");
        tempFile.close();
        return;
    }

    QTextStream in(&teacherFile);
    QTextStream out(&tempFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split("|");
        if (parts.size() >= 3 && parts[0] == selectedTeacherId) {

            if (parts.size() == 3) {
                parts.append(selectedSubjectId);
                parts[3] = selectedSubjectId;
            }
            out << parts.join("|") << "\n";
        } else {
            out << line << "\n";
        }
    }

    teacherFile.close();
    tempFile.close();


    if (!QFile::remove("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt") || !QFile::rename("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers_temp.txt", "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt")) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atnaujinti teachers.txt failo.");
        return;
    }

    QMessageBox::information(this, "Atlikta", "Dėstomas dalykas sėkmingai priskirtas dėstytojui.");

}
void AdminUI::onDeleteSubjectButtonClicked()
{

        QFile subjectFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt");
        if (!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti subject.txt failo.");
            return;
        }

        QStringList subjects;
        QTextStream subjectIn(&subjectFile);
        while (!subjectIn.atEnd()) {
            QString line = subjectIn.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 2) {
                subjects.append(parts[0] + " | " + parts[1]);
            }
        }
        subjectFile.close();


        bool ok;
        QString selectedSubject = QInputDialog::getItem(this, "Pašalinti dėstomą dalyką", "Pasirinkite dėstomą dalyką:", subjects, 0, false, &ok);
        if (!ok || selectedSubject.isEmpty()) {
            return;
        }

        QString selectedSubjectId = selectedSubject.split(" | ").first();


        QFile tempSubjectFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject_temp.txt");
        if (!tempSubjectFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko sukurti laikino subject.txt failo.");
            return;
        }

        if (!subjectFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko perskaityti subject.txt failo.");
            tempSubjectFile.close();
            return;
        }

        QTextStream in(&subjectFile);
        QTextStream out(&tempSubjectFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.startsWith(selectedSubjectId + "|")) {
                out << line << "\n";
            }
        }

        subjectFile.close();
        tempSubjectFile.close();


        if (!QFile::remove("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt") || !QFile::rename("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject_temp.txt", "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt")) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atnaujinti subject.txt failo.");
            return;
        }


        QFile teacherFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt");
        QFile tempTeacherFile("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers_temp.txt");
        if (!teacherFile.open(QIODevice::ReadOnly | QIODevice::Text) || !tempTeacherFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti teachers.txt arba sukurti laikino failo.");
            return;
        }

        QTextStream teacherIn(&teacherFile);
        QTextStream teacherOut(&tempTeacherFile);
        while (!teacherIn.atEnd()) {
            QString line = teacherIn.readLine();
            QStringList parts = line.split("|");
            if (parts.size() >= 4 && parts[3] == selectedSubjectId) {
                parts.removeAt(3);
            }
            teacherOut << parts.join("|") << "\n";
        }

        teacherFile.close();
        tempTeacherFile.close();


        if (!QFile::remove("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt") || !QFile::rename("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers_temp.txt", "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt")) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atnaujinti teachers.txt failo.");
            return;
        }

        QMessageBox::information(this, "Sėkmė", "Dėstomas dalykas ir jo priskyrimai sėkmingai pašalinti.");
}
void AdminUI::onLogOffButtonClicked()
{
    this->close();
    QMessageBox::information(this, "Atsijungta", "Sėkmingai atsijungta!");
    LoginUI *loginWindow = new LoginUI(this);
    loginWindow->show();
}

void AdminUI::onViewButtonClicked(){
    ViewUI *viewWindow = new ViewUI(this);
    viewWindow->show();
}
