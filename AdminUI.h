#ifndef ADMINUI_H
#define ADMINUI_H

#include <QMainWindow>

namespace Ui {
class AdminUI;
}

class AdminUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminUI(QWidget *parent = nullptr);
    ~AdminUI();

private slots:
    void onAddUserButtonClicked();
    void onRemoveUserButtonClicked();
    void onCreateGroupButtonClicked();
    void onAssignGroupButtonClicked();
    void onDeleteGroupButtonClicked();
    void onCreateSubjectButtonClicked();
    void onAssignSubjectButtonClicked();
    void onDeleteSubjectButtonClicked();
    void onLogOffButtonClicked();
    void onViewButtonClicked();


private:
    Ui::AdminUI *ui;
    int getNextID(const QString &filename);
    void appendToFile(const QString &filename, const QString &data);
    void removeFromFile(const QString &filename, int userID);
};

#endif // ADMINUI_H
