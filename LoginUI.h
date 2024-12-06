#ifndef LOGINUI_H
#define LOGINUI_H

#include <QDialog>

namespace Ui {
class LoginUI;
}

class LoginUI : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUI(QWidget *parent = nullptr);
    ~LoginUI();

private slots:
    // Pakeiskite pavadinimą čia
    void LoginButtonAdminClicked();
    void LoginButtonTeacherClicked();
    void LoginButtonStudentClicked();


private:
    Ui::LoginUI *ui;
    bool checkCredentials(const QString &filename, const QString &username, const QString &password);
};

#endif // LOGINUI_H
