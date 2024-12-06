#ifndef TEACHERUI_H
#define TEACHERUI_H

#include <QMainWindow>

namespace Ui {
class TeacherUI;
}

class TeacherUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherUI(QWidget *parent = nullptr);
    ~TeacherUI();
    QString getStudentID(const QString &name, const QString &surname);

private slots:
    void saveGrade();
    void deleteGrade();
    void exitButton();
    void viewSubjectsButton();
    void viewGradesButton();
    void findStudentIDButton();

private:
    Ui::TeacherUI *ui;

    bool checkTeacherExistence(const QString& teacherID);
    bool checkSubjectExistence(const QString& subjectID);

};

#endif // TEACHERUI_H
