#include "ClientQt5.h"
#include "UserActivityHandler.h"

ClientQt5::ClientQt5(UserActivityHandler* handler, QObject* parent)
: QObject(parent)
, socket_(new QWebSocket())
{
    uah = handler;
    socket_->open(QUrl("ws://localhost:8080"));
    connect(socket_, &QWebSocket::connected, this, &ClientQt5::onConnected);
    connect(socket_, &QWebSocket::disconnected, this, &ClientQt5::onDisconnected);
    connect(socket_, &QWebSocket::textMessageReceived, this, &ClientQt5::onTextMessageReceived);
    restart();
}

void ClientQt5::send(const QString& msg)
{
    socket_->sendTextMessage(msg);
}



void ClientQt5::restart()
{
    socket_->close();
    socket_->open(QUrl("ws://localhost:8080"));
}


void ClientQt5::setHandler(UserActivityHandler * handler){
    uah = handler;
}


void ClientQt5::onConnected()
{

}

void ClientQt5::onDisconnected()
{
    restart();
}

void ClientQt5::onTextMessageReceived(const QString& message)
{
    onTextMessageReceived2<UserActivityHandler>(message);
}

template<typename T>
void ClientQt5::onTextMessageReceived2(const QString& message) {
    (static_cast<T*>(uah))->acceptMessage(message);
}
