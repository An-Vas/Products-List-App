#include <QApplication>
#include <QPushButton>
#include <QTestAccessibility>
#include "MainWindowTesting.cpp"


int main(int argc, char *argv[]) {
    MainWindowTesting mainWindowTesting;

   QTest::qExec(&mainWindowTesting, argc, argv);
    return 0;
}
