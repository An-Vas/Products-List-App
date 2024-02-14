#ifndef CLIENT_WINDOWSETUP_H
#define CLIENT_WINDOWSETUP_H



#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QLabel>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QFormLayout>
#include <QSpinBox>
#include "UserActivityHandler.h"
#include "ResponseHandler.h"

class UserActivityHandler;


class WindowSetup {
private:
    std::string curUserId = "";

    QApplication app;
    QWidget window;
    UserActivityHandler* handler = nullptr;
    QFont sitka;


public:
    QTextEdit *productsTextEdit;

    QFormLayout *productsFormLayout  = new QFormLayout;
    QHBoxLayout *productsListLayout  = new QHBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QVBoxLayout *leftLayout  = new QVBoxLayout;
    QFormLayout *registrationFormLayout = new QFormLayout;
    QPushButton *button  = new QPushButton("Clear the list");
    QLabel *label = new QLabel("Current Product List");
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QLineEdit *productTextEdit = new QLineEdit;
    QLineEdit *userIdTextEdit  = new QLineEdit;
    QPushButton *addProductButton  = new QPushButton("Add");
    QPushButton *confirmUserIdButton  = new QPushButton("Apply");
    QPushButton *LogOutIdButton  = new QPushButton("Log out");
    QSpinBox *spinBox = new QSpinBox;

    void startSetup();
    WindowSetup (int argc, char *argv[] );
    void setProductList(std::list<std::string> products);
    void setProductListFont(QTextEdit* productsTextEdit, QLabel *label);

    void acceptServerReaponce(Request j);

private:

    void addProductButtonOnClick();
    void newUserConnect();
    void makeProductListVisiable();
    void makeProductListInvisiable();
    void makeRegistrationVisiable();
    void makeRegistrationInvisiable();
    void logoutInterfaceChange();

};


#endif //CLIENT_WINDOWSETUP_H
