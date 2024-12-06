#include "ViewSubjectsUI.h"
#include "ui_ViewSubjectsUI.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

ViewSubjectsUI::ViewSubjectsUI(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ViewSubjectsUI), model(new QStringListModel(this)) {
    ui->setupUi(this);


    ui->viewList->setModel(model);


    loadSubjects();

    connect(ui->exitButton, &QPushButton::clicked, this, &ViewSubjectsUI::exitButton);

}

ViewSubjectsUI::~ViewSubjectsUI() {
    delete ui;
}

void ViewSubjectsUI::loadSubjects() {
    QFile file("C:/Users/eckal/Documents/Programos/Akademine sistema/AcademicSystem/subject.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Klaida", "Nepavyko atidaryti 'subject.txt' failo.");
        return;
    }

    QStringList subjects;
    QTextStream in(&file);


    while (!in.atEnd()) {
        QString line = in.readLine();
        subjects.append(line);
    }

    file.close();


    model->setStringList(subjects);
}
void ViewSubjectsUI::exitButton(){
    this->close();
}
