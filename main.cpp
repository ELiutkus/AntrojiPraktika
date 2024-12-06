#include <QApplication>
#include "LoginUI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginUI loginWindow;
    loginWindow.show();

    return app.exec();
}
