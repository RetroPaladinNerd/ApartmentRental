// UserManager.h
#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>
#include "User.h"

class UserManager {
public:
    virtual void addUser(const User& user) = 0;
    virtual void displayUsers() const = 0;
    virtual ~UserManager() = default;
};

#endif // USER_MANAGER_H
