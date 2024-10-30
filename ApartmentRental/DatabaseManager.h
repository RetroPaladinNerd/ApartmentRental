#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>

class DatabaseManager {
public:
    virtual ~DatabaseManager() = default;

    virtual void openDB() = 0;                   // ����������� ����� �������� ��
    virtual void closeDB() = 0;                  // ����������� ����� �������� ��
    virtual void executeSQL(const std::string& sql) const = 0;  // ����������� ����� ���������� SQL
};

#endif // DATABASEMANAGER_H
