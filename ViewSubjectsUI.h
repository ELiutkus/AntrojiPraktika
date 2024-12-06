#ifndef VIEWSUBJECTSUI_H
#define VIEWSUBJECTSUI_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ViewSubjectsUI; }
QT_END_NAMESPACE

class ViewSubjectsUI : public QMainWindow {
    Q_OBJECT

public:
    explicit ViewSubjectsUI(QWidget *parent = nullptr);
    ~ViewSubjectsUI();

private:
    Ui::ViewSubjectsUI *ui;
    QStringListModel *model;

    void loadSubjects();
    void exitButton();
};

#endif // VIEWSUBJECTSUI_H
