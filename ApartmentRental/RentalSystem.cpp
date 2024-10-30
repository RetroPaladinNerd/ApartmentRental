#include "RentalSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Конструктор: открытие базы данных
RentalSystem::RentalSystem() {
    openDB();
}

// Деструктор: закрытие базы данных
RentalSystem::~RentalSystem() {
    closeDB();
}

// Выполнение SQL-запроса
void RentalSystem::executeSQL(const std::string& sql) const {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения SQL: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}

// Открытие базы данных SQLite
void RentalSystem::openDB() {
    if (int rc = sqlite3_open("rental_system.db", &db); rc) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << "\n";
    }
    else {
        std::cout << "База данных успешна открыта.\n";
    }

    // Создание таблиц, если их нет
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

// Закрытие базы данных SQLite
void RentalSystem::closeDB() {
    sqlite3_close(db);
}

// Добавление квартиры в базу данных
void RentalSystem::addApartmentToDB(const Apartment& apartment) {
    std::stringstream ss;
    ss << "INSERT INTO apartments (id, location, price, available, rating) VALUES ("
        << apartment.getId() << ", '"
        << apartment.getLocation() << "', "
        << apartment.getPrice() << ", "
        << (apartment.isAvailable() ? 1 : 0) << ", "
        << apartment.getRating() << ");";

    executeSQL(ss.str());
    std::cout << "Квартира добавлена в базу данных. \n";
}


// Отображение доступных квартир из базы данных
void RentalSystem::displayAvailableApartmentsFromDB() const {
    std::string sql = "SELECT id, location, price FROM apartments WHERE available = 1;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr); rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    std::cout << "Доступные квартиры:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* location = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double price = sqlite3_column_double(stmt, 2);

        std::cout << "ID: " << id << ", Местоположение: " << location << ", Цена: $" << price << "\n";
    }

    sqlite3_finalize(stmt);
}

bool RentalSystem::rentApartmentFromDB(int apartmentId, const User& user) {
    // Проверка доступности квартиры
    std::string checkAvailabilitySQL = "SELECT price, available FROM apartments WHERE id = " + std::to_string(apartmentId) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, checkAvailabilitySQL.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << "\n";
        return false;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        double price = sqlite3_column_double(stmt, 0);
        int available = sqlite3_column_int(stmt, 1);
        if (available == 0) {
            std::cout << "Квартира с ID " << apartmentId << " недоступна.\n";
            sqlite3_finalize(stmt);
            return false;
        }

        // Обновление статуса доступности квартиры
        std::string updateSQL = "UPDATE apartments SET available = 0 WHERE id = " + std::to_string(apartmentId) + ";";
        executeSQL(updateSQL);

        // Добавление пользователя в базу данных
        addUserToDB(user);

        // Сообщаем об успешной аренде
        std::cout << user.getName() << " арендовал квартиру с ID: " << apartmentId
            << " за " << price << " долларов.\n";  // Предполагаем, что цена в рублях

        sqlite3_finalize(stmt);
        return true;
    }

    sqlite3_finalize(stmt);
    return false;
}

// Возврат квартиры
bool RentalSystem::returnApartmentToDB(int apartmentId) {
    std::string updateSQL = "UPDATE apartments SET available = 1 WHERE id = " + std::to_string(apartmentId) + ";";
    executeSQL(updateSQL);
    std::cout << "Квартира с ID " << apartmentId << " была возвращена.\n";
    return true;
}

// Удаление квартиры из базы данных
bool RentalSystem::removeApartmentFromDB(int apartmentId) {
    std::string deleteSQL = "DELETE FROM apartments WHERE id = " + std::to_string(apartmentId) + ";";
    executeSQL(deleteSQL);
    std::cout << "Квартира с ID " << apartmentId << " была удалена.\n";
    return true;
}

// Добавление пользователя в базу данных
void RentalSystem::addUserToDB(const User& user) {
    std::stringstream ss;
    ss << "INSERT INTO users (name, email) VALUES ('"
        << user.getName() << "', '"
        << user.getEmail() << "');";
    executeSQL(ss.str());
}

// Отображение всех пользователей из базы данных
void RentalSystem::displayUsersFromDB() const {
    std::string sql = "SELECT name, email FROM users;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << "\n";
        return;
    }

    std::cout << "Пользователи:\n";
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        const char* email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::cout << "Имя: " << name << ", Email: " << email << "\n";
    }

    sqlite3_finalize(stmt);
}

void RentalSystem::rateApartmentInDB(int apartmentId, double rating) {
    // Проверим, что рейтинг находится в допустимом диапазоне
    if (rating < 1.0 || rating > 5.0) {
        std::cout << "Ошибка: Оценка должна быть в диапазоне от 1 до 5." << std::endl;
        return;
    }

    sqlite3* db;
    char* errorMessage = nullptr;

    // Открываем соединение с базой данных
    int rc = sqlite3_open("rental_system.db", &db);
    if (rc) {
        std::cerr << "Не удалось открыть базу данных: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // SQL-запрос для проверки наличия квартиры с данным ID
    std::string checkQuery = "SELECT COUNT(*) FROM apartments WHERE id = ?;";
    sqlite3_stmt* stmt;

    // Подготавливаем запрос
    rc = sqlite3_prepare_v2(db, checkQuery.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Привязываем параметр (ID квартиры) к запросу
    sqlite3_bind_int(stmt, 1, apartmentId);

    // Выполняем запрос
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0); // Получаем количество квартир с данным ID
        if (count == 0) {
            std::cout << "Квартира с ID " << apartmentId << " не найдена." << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
    }
    else {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(stmt); // Завершаем проверку существования квартиры

    // SQL-запрос для обновления рейтинга квартиры
    std::string updateQuery = "UPDATE apartments SET rating = ? WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка подготовки запроса обновления: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    // Привязываем параметры (рейтинг и ID квартиры) к запросу
    sqlite3_bind_double(stmt, 1, rating);
    sqlite3_bind_int(stmt, 2, apartmentId);

    // Выполняем запрос
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Ошибка обновления записи: " << sqlite3_errmsg(db) << std::endl;
    }
    else {
        std::cout << "Рейтинг квартиры с ID " << apartmentId << " успешно обновлен до " << rating << "." << std::endl;
    }

    // Завершаем работу с запросом и базой данных
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}


void RentalSystem::compareApartmentsFromDB(int apartmentId1, int apartmentId2) const {
    // SQL query to retrieve prices of the two apartments
    std::string sql = "SELECT id, price FROM apartments WHERE id IN (" + std::to_string(apartmentId1) + ", " + std::to_string(apartmentId2) + ");";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка выполнения запроса: " << sqlite3_errmsg(db) << "\n";
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
        std::cout << "Квартира с ID " << apartmentId1 << " не найдена.\n";
    }
    if (!found2) {
        std::cout << "Квартира с ID " << apartmentId2 << " не найдена.\n";
    }

    
    if (found1 && found2) {
        std::cout << "Сравнение квартир:\n";
        std::cout << "Квартира ID " << apartmentId1 << " стоит " << price1 << " долларов.\n";
        std::cout << "Квартира ID " << apartmentId2 << " стоит " << price2 << " долларов.\n";

        if (price1 < price2) {
            std::cout << "Квартира с ID " << apartmentId1 << " дешевле.\n";
        }
        else if (price1 > price2) {
            std::cout << "Квартира с ID " << apartmentId2 << " дешевле.\n";
        }
        else {
            std::cout << "Обе квартиры стоят одинаково.\n";
        }
    }
}
