#include "WindowSetup.h"
#include <QResource>
#include <QtGui>

WindowSetup::WindowSetup(int argc, char *argv[]) : app(QApplication(argc, argv)){

    UserActivityHandler uah;
    uah.setWindowSetup(this);
    handler = &uah;
    window.setWindowTitle("Products List");
    window.setBaseSize(750, 400);
    int id = QFontDatabase::addApplicationFont(
            "C:\\Windows\\WinSxS\\amd64_microsoft-windows-font-truetype-sitka_31bf3856ad364e35_10.0.19041.1_none_9c1fe6045dbd922a\\Sitka.ttc");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    startSetup();

}

void WindowSetup::startSetup() {


    QFile file("C:\\ITMO\\5S_cpp\\Client\\stylesheet.qss");
    file.open(QFile::ReadOnly);
    app.setStyleSheet(file.readAll());

    QPalette pal = app.palette();
    pal.setColor(QPalette::Window, QColor(255, 160, 122));
    app.setPalette(pal);


    productsFormLayout->addRow("Product:", productTextEdit);
    productsFormLayout->addRow("Count:", spinBox);


    registrationFormLayout->addRow("Userid: ", userIdTextEdit);


    button->setFont(sitka);
    LogOutIdButton->setFont(sitka);
    confirmUserIdButton->setFont(sitka);

    QObject::connect(button, &QPushButton::clicked, [this]() {
        handler->handleClearList(curUserId);
        productTextEdit->clear();

    });
    QObject::connect(confirmUserIdButton, &QPushButton::clicked, [this]() {
        newUserConnect();
    });

    QObject::connect(LogOutIdButton, &QPushButton::clicked, [this]() {
        logoutInterfaceChange();
        productTextEdit->clear();
    });

    button->setAutoFillBackground(true);
    LogOutIdButton->setAutoFillBackground(true);
    button->setFlat(true);
    LogOutIdButton->setFlat(true);
    QPalette p1 = button->palette();
    p1.setColor(QPalette::Button, QColor(255, 228, 196));
    p1 = LogOutIdButton->palette();
    p1.setColor(QPalette::Button, QColor(255, 228, 196));



    addProductButton->setAutoFillBackground(true);
    addProductButton->setFlat(true);

    QPalette p = addProductButton->palette();
    p.setColor(QPalette::Button, QColor(255, 228, 196));
    addProductButton->setPalette(p);

    QObject::connect(addProductButton, &QPushButton::clicked, [=]() {
        addProductButtonOnClick();
    });

    addProductButton->setFont(sitka);
    productsFormLayout->itemAt(0, QFormLayout::LabelRole)->widget()->setFont(sitka);
    productsFormLayout->itemAt(1, QFormLayout::LabelRole)->widget()->setFont(sitka);

    spinBox->setFont(sitka);
    productTextEdit->setFont(sitka);
    userIdTextEdit->setFont(sitka);

    productsFormLayout->addWidget(addProductButton);
    registrationFormLayout->addWidget(confirmUserIdButton);



    leftLayout->addLayout(productsFormLayout);
    leftLayout->addWidget(button);
    leftLayout->addWidget(LogOutIdButton);


    label->setFont(sitka);

    productsTextEdit = new QTextEdit();

    rightLayout->addWidget(label);
    rightLayout->addWidget(productsTextEdit);
    rightLayout->addStretch();

    productsTextEdit->append(QString("Add some products"));



    mainLayout->addStretch();

    productsListLayout->addLayout(leftLayout, 2);
    productsListLayout->addLayout(rightLayout, 5);

    mainLayout->addLayout(registrationFormLayout, 1);
    mainLayout->addLayout(productsListLayout, 5);


    productsListLayout->addStretch();
    setProductListFont(productsTextEdit, label);



    makeProductListInvisiable();
    window.setFixedSize(600, 255);

    window.setLayout(mainLayout);
    window.show();
    app.exec();
}

void WindowSetup::setProductList(std::list<std::string> products) {

    productsTextEdit->clear();

    std::list<std::string>::iterator it;
    if (products.begin() == products.end()) {
        productsTextEdit->append(QString("Add some products"));
        int id = QFontDatabase::addApplicationFont(
                "C:\\Windows\\WinSxS\\amd64_microsoft-windows-font-truetype-sitka_31bf3856ad364e35_10.0.19041.1_none_9c1fe6045dbd922a\\Sitka.ttc");
        QString family = QFontDatabase::applicationFontFamilies(id).at(0);
        QFont sitka(family);
        productsTextEdit->setFont(sitka);
    }
    for (it = products.begin(); it != products.end(); ++it) {
        productsTextEdit->append(QString::fromStdString(*it));
    }


}

void WindowSetup::setProductListFont(QTextEdit *productsTextEdit, QLabel *label) {

    int id = QFontDatabase::addApplicationFont(
            "C:\\Windows\\WinSxS\\amd64_microsoft-windows-font-truetype-sitka_31bf3856ad364e35_10.0.19041.1_none_9c1fe6045dbd922a\\Sitka.ttc");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont sitka(family);
    productsTextEdit->setFont(sitka);
    label->setFont(sitka);
}

void WindowSetup::acceptServerReaponce(Request r){

    if (r.type == "user"){
        makeProductListVisiable();
        makeRegistrationInvisiable();

        std::list<std::string> strList;
        std::list<ProductListItem>::iterator it;
        for (it = r.list.begin(); it != r.list.end(); ++it){
            strList.push_back(it->name + " " + std::to_string(it->amount));
        }

        setProductList(strList);

    }

    if (r.type == "product"){
        std::list<std::string> strList;
        std::list<ProductListItem>::iterator it;
        for (it = r.list.begin(); it != r.list.end(); ++it){
            strList.push_back(it->name + " " + std::to_string(it->amount));
        }

        setProductList(strList);
    }
    if (r.type == "clear"){
        std::list<std::string> strList;
        setProductList(strList);
    }



}

void WindowSetup::addProductButtonOnClick(){
    handler->handleAddProduct(productTextEdit->text().toStdString(), spinBox->value(), curUserId);
}

void WindowSetup::newUserConnect(){

    handler->userConnect(userIdTextEdit->text().toStdString());
    curUserId = userIdTextEdit->text().toStdString();
}

void WindowSetup::makeProductListVisiable(){

    window.setFixedSize(600, 255);
    for(int i = 0; i < productsFormLayout->count(); i++) {
        QWidget *widget = productsFormLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->show();
        }
    }

    for(int i = 0; i < productsListLayout->count(); i++) {
        QWidget *widget = productsListLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->show();
        }
    }

    for(int i = 0; i < rightLayout->count(); i++) {
        QWidget *widget = rightLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->show();
        }
    }

    for(int i = 0; i < leftLayout->count(); i++) {
        QWidget *widget = leftLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->show();
        }
    }
}

void WindowSetup::makeProductListInvisiable(){


    for(int i = 0; i < productsFormLayout->count(); i++) {
        QWidget *widget = productsFormLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->hide();
        }
    }

    for(int i = 0; i < productsListLayout->count(); i++) {
        QWidget *widget = productsListLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->hide();
        }
    }

    for(int i = 0; i < rightLayout->count(); i++) {
        QWidget *widget = rightLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->hide();
        }
    }

    for(int i = 0; i < leftLayout->count(); i++) {
        QWidget *widget = leftLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            widget->hide();
        }
    }
}

void WindowSetup::makeRegistrationInvisiable(){
    for(int i = 0; i < registrationFormLayout->count(); i++) {
        QWidget *widget = registrationFormLayout->itemAt(i)->widget();
        if(widget != nullptr) {
            delete widget;
        }
    }
    delete userIdTextEdit;
    delete registrationFormLayout;
}

void WindowSetup::logoutInterfaceChange(){
    curUserId = "";
    confirmUserIdButton  = new QPushButton("Apply");
    confirmUserIdButton->setFont(sitka);
    QObject::connect(confirmUserIdButton, &QPushButton::clicked, [this]() {
        newUserConnect();
    });
    userIdTextEdit = new QLineEdit;

    registrationFormLayout = new QFormLayout;
    registrationFormLayout->addRow("Userid: ", userIdTextEdit);
    registrationFormLayout->addWidget(confirmUserIdButton);
    mainLayout->addLayout(registrationFormLayout, 1);

    auto index1 = mainLayout->indexOf(productsListLayout) ;
    auto index2 = mainLayout->indexOf(registrationFormLayout);
    mainLayout->takeAt(index1) ;
    mainLayout->insertLayout(index2, registrationFormLayout) ;

    makeProductListInvisiable();

}
