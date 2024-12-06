#include "ViewUI.h"
#include "ui_ViewUI.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QStringListModel>

ViewUI::ViewUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ViewUI)
{
    ui->setupUi(this);

    connect(ui->rodytiButton, &QPushButton::clicked, this, &::ViewUI::onRodytiButtonClicked);
    connect(ui->iseitiButton, &QPushButton::clicked, this, &::ViewUI::onIseitiButtonClicked);
    ui->comboBox->addItem("Adminai");
    ui->comboBox->addItem("Pazymiai");
    ui->comboBox->addItem("Grupes");
    ui->comboBox->addItem("Studentai");
    ui->comboBox->addItem("Dėstomi dalykai");
    ui->comboBox->addItem("Dėstytojai");
}

ViewUI::~ViewUI()
{
    delete ui;
}

void ViewUI::onRodytiButtonClicked()
{

    QString selectedFile = ui->comboBox->currentText();
    if(selectedFile == "Adminai"){
    QString filePath = "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/admins.txt";

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo: " + selectedFile);
        return;
    }

    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        lines.append(in.readLine());
    }

    file.close();

    QStringListModel *model = new QStringListModel(this);
    model->setStringList(lines);


    ui->listView->setModel(model);
    }
    else if(selectedFile == "Pazymiai"){
        QString filePath = "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/grades.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo: " + selectedFile);
            return;
        }

        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }

        file.close();

        QStringListModel *model = new QStringListModel(this);
        model->setStringList(lines);


        ui->listView->setModel(model);
    }
    else if(selectedFile == "Grupes"){
        QString filePath = "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/groups.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo: " + selectedFile);
            return;
        }

        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }

        file.close();

        QStringListModel *model = new QStringListModel(this);
        model->setStringList(lines);


        ui->listView->setModel(model);
    }
    else if(selectedFile == "Studentai"){
        QString filePath = "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/students.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo: " + selectedFile);
            return;
        }

        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }

        file.close();

        QStringListModel *model = new QStringListModel(this);
        model->setStringList(lines);


        ui->listView->setModel(model);
    }
    else if(selectedFile == "Dėstomi dalykai"){
        QString filePath = "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo: " + selectedFile);
            return;
        }

        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }

        file.close();

        QStringListModel *model = new QStringListModel(this);
        model->setStringList(lines);


        ui->listView->setModel(model);
    }
    else if(selectedFile == "Dėstytojai"){
        QString filePath = "C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/teachers.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti failo: " + selectedFile);
            return;
        }

        QStringList lines;
        QTextStream in(&file);
        while (!in.atEnd()) {
            lines.append(in.readLine());
        }

        file.close();

        QStringListModel *model = new QStringListModel(this);
        model->setStringList(lines);


        ui->listView->setModel(model);

    }
}


void ViewUI::onIseitiButtonClicked()
{
    this->close();
}
