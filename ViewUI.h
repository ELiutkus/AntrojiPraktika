#ifndef VIEWUI_H
#define VIEWUI_H

#include <QDialog>
#include <QListView>
#include <QFileSystemModel>
#include <QWidget>
#include <QStringListModel>
#include <QComboBox>
#include <QListView>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

namespace Ui {
class ViewUI;
}

class ViewUI : public QDialog
{
    Q_OBJECT

public:
    explicit ViewUI(QWidget *parent = nullptr);
    ~ViewUI();

private:
    Ui::ViewUI *ui;

    void onIseitiButtonClicked();
    void onRodytiButtonClicked();
    void onComboBoxSelect();
};

#endif // VIEWUI_H
