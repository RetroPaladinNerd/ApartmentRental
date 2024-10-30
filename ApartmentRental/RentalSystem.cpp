#include "RentalSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

// �����������: �������� ���� ������
RentalSystem::RentalSystem() {
    openDB();
}

// ����������: �������� ���� ������
RentalSystem::~RentalSystem() {
    closeDB();
}

// ���������� SQL-�������
void RentalSystem::executeSQL(const std::string& sql) const {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� SQL: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

// �������� ���� ������ SQLite
void RentalSystem::openDB() {
    if (int rc = sqlite3_open("rental_system.db", &db); rc) {
        std::cerr << "������ �������� ���� ������: " << sqlite3_errmsg(db) << "\n";
    }
    else {
        std::cout << "���� ������ ������� �������.\n";
    }

    // �������� ������, ���� �� ���
    std::string createApartmentsTable = R"(
        CREATE TABLE IF NOT EXISTS apartments (
            id INTEGER PRIMARY KEY,
            location TEXT NOT NULL,
            price REAL NOT NULL,
            available INTEGER NOT NULL,
            rating REAL DEFAULT 0
        );
    )";

    std::string createUsersTable = R"(
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            email TEXT NOT NULL
        );
    )";

    executeSQL(createApartmentsTable);
    executeSQL(createUsersTable);
}

// �������� ���� ������ SQLite
void RentalSystem::closeDB() {
    sqlite3_close(db);
}

// ���������� �������� � ���� ������
void RentalSystem::addApartmentToDB(const Apartment& apartment) {
    std::stringstream ss;
    ss << "INSERT INTO apartments (id, location, price, available, rating) VALUES ("
        << apartment.getId() << ", '"
        << apartment.getLocation() << "', "
        << apartment.getPrice() << ", "
        << (apartment.isAvailable() ? 1 : 0) << ", "
        << apartment.getRating() << ");";

    executeSQL(ss.str());
    std::cout << "�������� ��������� � ���� ������. \n";
}


// ����������� ��������� ������� �� ���� ������
void RentalSystem::displayAvailableApartmentsFromDB() const {
    std::string sql = "SELECT id, location, price FROM apartments WHERE available = 1;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr); rc != SQLITE_OK) {
        std::cerr << "������ ���������� �������: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    std::cout << "��������� ��������:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double price = sqlite3_column_double(stmt, 2);

        std::cout << "ID: " << id << ", ��������������: " << location << ", ����: $" << price << "\n";
    }

    sqlite3_finalize(stmt);
}

bool RentalSystem::rentApartmentFromDB(int apartmentId, const User& user) {
    // �������� ����������� ��������
    std::string checkAvailabilitySQL = "SELECT price, available FROM apartments WHERE id = " + std::to_string(apartmentId) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, checkAvailabilitySQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� �������: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double price = sqlite3_column_double(stmt, 0);
        int available = sqlite3_column_int(stmt, 1);
        if (available == 0) {
            std::cout << "�������� � ID " << apartmentId << " ����������.\n";
            sqlite3_finalize(stmt);
            return false;
        }

        // ���������� ������� ����������� ��������
        std::string updateSQL = "UPDATE apartments SET available = 0 WHERE id = " + std::to_string(apartmentId) + ";";
        executeSQL(updateSQL);

        // ���������� ������������ � ���� ������
        addUserToDB(user);

        // �������� �� �������� ������
        std::cout << user.getName() << " ��������� �������� � ID: " << apartmentId
            << " �� " << price << " ��������.\n";  // ������������, ��� ���� � ������

        sqlite3_finalize(stmt);
        return true;
    }

    sqlite3_finalize(stmt);
    return false;
}

// ������� ��������
bool RentalSystem::returnApartmentToDB(int apartmentId) {
    std::string updateSQL = "UPDATE apartments SET available = 1 WHERE id = " + std::to_string(apartmentId) + ";";
    executeSQL(updateSQL);
    std::cout << "�������� � ID " << apartmentId << " ���� ����������.\n";
    return true;
}

// �������� �������� �� ���� ������
bool RentalSystem::removeApartmentFromDB(int apartmentId) {
    std::string deleteSQL = "DELETE FROM apartments WHERE id = " + std::to_string(apartmentId) + ";";
    executeSQL(deleteSQL);
    std::cout << "�������� � ID " << apartmentId << " ���� �������.\n";
    return true;
}

// ���������� ������������ � ���� ������
void RentalSystem::addUserToDB(const User& user) {
    std::stringstream ss;
    ss << "INSERT INTO users (name, email) VALUES ('"
        << user.getName() << "', '"
        << user.getEmail() << "');";
    executeSQL(ss.str());
}

// ����������� ���� ������������� �� ���� ������
void RentalSystem::displayUsersFromDB() const {
    std::string sql = "SELECT name, email FROM users;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� �������: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    std::cout << "������������:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::cout << "���: " << name << ", Email: " << email << "\n";
    }

    sqlite3_finalize(stmt);
}

void RentalSystem::rateApartmentInDB(int apartmentId, double rating) {
    // ��������, ��� ������� ��������� � ���������� ���������
    if (rating < 1.0 || rating > 5.0) {
        std::cout << "������: ������ ������ ���� � ��������� �� 1 �� 5." << std::endl;
        return;
    }

    sqlite3* db;
    char* errorMessage = nullptr;

    // ��������� ���������� � ����� ������
    int rc = sqlite3_open("rental_system.db", &db);
    if (rc) {
        std::cerr << "�� ������� ������� ���� ������: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // SQL-������ ��� �������� ������� �������� � ������ ID
    std::string checkQuery = "SELECT COUNT(*) FROM apartments WHERE id = ?;";
    sqlite3_stmt* stmt;

    // �������������� ������
    rc = sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� �������: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // ����������� �������� (ID ��������) � �������
    sqlite3_bind_int(stmt, 1, apartmentId);

    // ��������� ������
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0); // �������� ���������� ������� � ������ ID
        if (count == 0) {
            std::cout << "�������� � ID " << apartmentId << " �� �������." << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
    }
    else {
        std::cerr << "������ ���������� �������: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(stmt); // ��������� �������� ������������� ��������

    // SQL-������ ��� ���������� �������� ��������
    std::string updateQuery = "UPDATE apartments SET rating = ? WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� ������� ����������: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // ����������� ��������� (������� � ID ��������) � �������
    sqlite3_bind_double(stmt, 1, rating);
    sqlite3_bind_int(stmt, 2, apartmentId);

    // ��������� ������
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "������ ���������� ������: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "������� �������� � ID " << apartmentId << " ������� �������� �� " << rating << "." << std::endl;
    }

    // ��������� ������ � �������� � ����� ������
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void RentalSystem::compareApartmentsFromDB(int apartmentId1, int apartmentId2) const {
    // SQL query to retrieve prices of the two apartments
    std::string sql = "SELECT id, price FROM apartments WHERE id IN (" + std::to_string(apartmentId1) + ", " + std::to_string(apartmentId2) + ");";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "������ ���������� �������: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    double price1 = 0.0, price2 = 0.0;
    bool found1 = false, found2 = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        double price = sqlite3_column_double(stmt, 1);

        if (id == apartmentId1) {
            price1 = price;
            found1 = true;
        }
        else if (id == apartmentId2) {
            price2 = price;
            found2 = true;
        }
    }

    sqlite3_finalize(stmt);

    
    if (!found1) {
        std::cout << "�������� � ID " << apartmentId1 << " �� �������.\n";
    }
    if (!found2) {
        std::cout << "�������� � ID " << apartmentId2 << " �� �������.\n";
    }

    
    if (found1 && found2) {
        std::cout << "��������� �������:\n";
        std::cout << "�������� ID " << apartmentId1 << " ����� " << price1 << " ��������.\n";
        std::cout << "�������� ID " << apartmentId2 << " ����� " << price2 << " ��������.\n";

        if (price1 < price2) {
            std::cout << "�������� � ID " << apartmentId1 << " �������.\n";
        }
        else if (price1 > price2) {
            std::cout << "�������� � ID " << apartmentId2 << " �������.\n";
        }
        else {
            std::cout << "��� �������� ����� ���������.\n";
        }
    }
}
