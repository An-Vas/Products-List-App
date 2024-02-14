#ifndef CLIENT_CLIENTQT5_H
#define CLIENT_CLIENTQT5_H

#include <QtCore/QCoreApplication>
#include <QtWebSockets/QWebSocket>
#include <QtNetwork/QHostAddress>
#include <iostream>
#include <nlohmann/json.hpp>

#include "JsonParser.h"
#include "UserActivityHandler.h"

class UserActivityHandler;
class ClientQt5: public QObject
{
    Q_OBJECT

public:
    ClientQt5(UserActivityHandler* handler, QObject* parent = nullptr);
    void send(const QString& msg);
    void restart();
    void setHandler(UserActivityHandler * handler);

private :
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);
    template<typename T>
    void onTextMessageReceived2(const QString& message);



private:
    QWebSocket* socket_;
    UserActivityHandler * uah;
};


#endif //CLIENT_CLIENTQT5_H
