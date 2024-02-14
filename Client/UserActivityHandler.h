#ifndef CLIENT_USERACTIVITYHANDLER_H
#define CLIENT_USERACTIVITYHANDLER_H

#include "ClientQt5.h"
#include "WindowSetup.h"
#include <memory>

class ClientQt5;
class WindowSetup;
class UserActivityHandler {
private:
    WindowSetup * windowSetup;
    std::shared_ptr<ClientQt5> client;
public:
    UserActivityHandler();

    void handleAddProduct (std::string name, int amount, std::string userId);
    void handleClearList (std::string userId);
    void acceptMessage(const QString& message);
    void userConnect(std::string userId);
    void setWindowSetup(WindowSetup * windowSetup);
};


#endif //CLIENT_USERACTIVITYHANDLER_H