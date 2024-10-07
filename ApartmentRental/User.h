#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User(const std::string& name, const std::string& email);

    std::string getName() const;
    std::string getEmail() const;

    std::string toString() const; // Для сохранения в файл

private:
    std::string name;
    std::string email;
};

#endif // USER_H
