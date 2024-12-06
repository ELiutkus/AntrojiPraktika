#ifndef STUDENTUI_H
#define STUDENTUI_H

#include <QMainWindow>

namespace Ui {
class StudentUI;
}

class StudentUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentUI(QWidget *parent = nullptr);
    ~StudentUI();

private slots:
    void viewGradesButton();
    void exitButton();
    void viewSubjectsButton();

private:
    Ui::StudentUI *ui;
    QString getStudentID(const QString &name, const QString &surname);
};

#endif // STUDENTUI_H
