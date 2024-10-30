#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>

class DatabaseManager {
public:
    virtual ~DatabaseManager() = default;

    virtual void openDB() = 0;                   // Абстрактный метод открытия БД
    virtual void closeDB() = 0;                  // Абстрактный метод закрытия БД
    virtual void executeSQL(const std::string& sql) const = 0;  // Абстрактный метод выполнения SQL
};

#endif // DATABASEMANAGER_H
