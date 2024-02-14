#ifndef CLIENTTESTING_MAINWINDOWTESTING_H
#define CLIENTTESTING_MAINWINDOWTESTING_H

#include <QVBoxLayout>
#include <QtTest/QtTest>
#include "WindowSetup.h"
#include "UserActivityHandler.h"

class MainWindowTesting : public QObject {
    Q_OBJECT
private slots:
    void test_set_product_list() {

        WindowSetup windowSetup(0, nullptr);


        QTextEdit * productsTextEdit = windowSetup.productsTextEdit;

        QPushButton* addButton = windowSetup.addProductButton;
        QLineEdit* productNameEdit = windowSetup.productTextEdit;
        QSpinBox* productCountSpinbox = windowSetup.spinBox;

        QTest::mouseClick(addButton, Qt::LeftButton);
        QCOMPARE(productNameEdit->text(), QString(""));

        QTest::keyClicks(productNameEdit, "Product 1");

        QCOMPARE(productNameEdit->text(), QString("Product 1"));

        std::list<std::string> products = {"Product 1", "Product 2", "Product 3"};
        windowSetup.setProductList(products);
        QCOMPARE(productsTextEdit->toPlainText(), QString("Product 1\nProduct 2\nProduct 3"));


    }
};


#endif //CLIENTTESTING_MAINWINDOWTESTING_H
