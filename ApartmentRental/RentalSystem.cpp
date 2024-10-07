#include "RentalSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>

void RentalSystem::addApartment(const Apartment& apartment) {
    apartments.push_back(apartment);
}

void RentalSystem::displayAvailableApartments() const {
    std::cout << "Доступные квартиры:\n";
    for (const auto& apartment : apartments) {
        if (apartment.isAvailable()) {
            std::cout << "ID: " << apartment.getId() << ", Местоположение: "
                << apartment.getLocation() << ", Цена: $"
                << apartment.getPrice() << "\n";
        }
    }
}

void RentalSystem::rateApartment(int apartmentId, double rating) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId) {
            apartment.setRating(rating);
            std::cout << "Рейтинг для квартиры с ID " << apartmentId << " установлен на " << rating << ".\n";
            return;
        }
    }
    std::cout << "Квартира с ID " << apartmentId << " не найдена.\n";
}

double RentalSystem::getCurrencyRate(const std::string& currency) const {
    if (currency == "USD") return 1.0;
    if (currency == "EUR") return 0.85;
    if (currency == "GBP") return 3.20;
    return 1.0; // По умолчанию USD
}

bool RentalSystem::rentApartment(int apartmentId, const User& user, double rate, const std::string& currency) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId && apartment.isAvailable()) {
            apartment.setAvailable(false);
            users.push_back(user);

            double priceInCurrency = apartment.getPrice() * rate; // Пересчитываем цену

            std::cout << user.getName() << " арендовал квартиру с ID: " << apartmentId
                << " за " << priceInCurrency << " " << currency << ".\n";
            return true;
        }
    }
    std::cout << "Квартира с ID " << apartmentId << " недоступна.\n";
    return false;
}

bool RentalSystem::returnApartment(int apartmentId) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId && !apartment.isAvailable()) {
            apartment.setAvailable(true);
            std::cout << "Квартира с ID " << apartmentId << " была возвращена.\n";
            return true;
        }
    }
    std::cout << "Квартира с ID " << apartmentId << " в данный момент не арендована.\n";
    return false;
}

bool RentalSystem::removeApartment(int apartmentId) {
    for (auto it = apartments.begin(); it != apartments.end(); ++it) {
        if (it->getId() == apartmentId) {
            apartments.erase(it);
            std::cout << "Квартира с ID " << apartmentId << " была удалена.\n";
            return true;
        }
    }
    std::cout << "Квартира с ID " << apartmentId << " не найдена.\n";
    return false;
}

void RentalSystem::addUser(const User& user) {
    users.push_back(user);
}

void RentalSystem::displayUsers() const {
    std::cout << "Пользователи:\n";
    for (const auto& user : users) {
        std::cout << "Имя: " << user.getName() << ", Email: " << user.getEmail() << "\n";
    }
}
double RentalSystem::calculateRentalCost(int apartmentId, int rentalDays) const {
    for (const auto& apartment : apartments) {
        if (apartment.getId() == apartmentId) {
            double basePrice = apartment.getPrice();
            double totalCost = (basePrice * rentalDays)/30;

            // Пример скидки для долгосрочной аренды (>30 дней)
            if (rentalDays > 30) {
                totalCost *= 0.85; // Скидка 15% на аренду более 30 дней
            }

            std::cout << "Итоговая стоимость аренды квартиры ID: " << apartmentId
                << " на " << rentalDays << " дней составит: $" << totalCost << "\n";
            return totalCost;
        }
    }
    std::cout << "Квартира с ID " << apartmentId << " не найдена.\n";
    return 0.0;
}
void RentalSystem::compareApartments(int apartmentId1, int apartmentId2) const {
    const Apartment* apt1 = nullptr;
    const Apartment* apt2 = nullptr;

    // Поиск квартир с заданными ID
    for (const auto& apartment : apartments) {
        if (apartment.getId() == apartmentId1) apt1 = &apartment;
        if (apartment.getId() == apartmentId2) apt2 = &apartment;
    }

    // Проверяем, найдены ли обе квартиры
    if (apt1 && apt2) {
        std::cout << "Сравнение квартир:\n";

        // Сравнение местоположения
        std::cout << "Местоположение:\n";
        std::cout << "Квартира 1: " << apt1->getLocation() << "\n";
        std::cout << "Квартира 2: " << apt2->getLocation() << "\n";

        // Сравнение цен
        std::cout << "Цена:\n";
        std::cout << "Квартира 1: $" << apt1->getPrice() << "\n";
        std::cout << "Квартира 2: $" << apt2->getPrice() << "\n";

        // Сравнение доступности
        std::cout << "Доступность:\n";
        std::cout << "Квартира 1: " << (apt1->isAvailable() ? "Доступна" : "Недоступна") << "\n";
        std::cout << "Квартира 2: " << (apt2->isAvailable() ? "Доступна" : "Недоступна") << "\n";
    }
    else {
        std::cout << "Одна или обе квартиры с указанными ID не найдены.\n";
    }
}
void RentalSystem::saveApartmentsToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи.\n";
        return;
    }
    for (const auto& apartment : apartments) {
        outFile << apartment.getId() << ","
            << apartment.getLocation() << ","
            << apartment.getPrice() << ","
            << (apartment.isAvailable() ? "1" : "0") << "\n";
    }
    outFile.close();
    std::cout << "Данные о квартирах сохранены в файл " << filename << ".\n";
}
void RentalSystem::saveUsersToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Ошибка открытия файла для записи.\n";
        return;
    }
    for (const auto& user : users) {
        outFile << user.getName() << "," << user.getEmail() << "\n";
    }
    outFile.close();
    std::cout << "Данные о пользователях сохранены в файл " << filename << ".\n";
}
void RentalSystem::loadApartmentsFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла для чтения.\n";
        return;
    }

    apartments.clear(); // Очищаем текущий список квартир
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        int id;
        std::string location;
        double price;
        bool available;
        char delimiter;

        if (ss >> id >> delimiter) { // Читаем ID и пропускаем запятую
            std::getline(ss, location, ','); // Читаем местоположение до запятой
            ss >> price >> delimiter; // Читаем цену и пропускаем запятую
            ss >> available; // Читаем доступность

            Apartment apartment(id, location, price, available);
            apartments.push_back(apartment); // Добавляем квартиру в список
        }
    }
    inFile.close();
    std::cout << "Данные о квартирах загружены из файла " << filename << ".\n";
}
void RentalSystem::loadUsersFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла для чтения.\n";
        return;
    }

    users.clear(); // Очищаем текущий список пользователей
    std::string line;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string name, email;

        std::getline(ss, name, ','); // Читаем имя до запятой
        std::getline(ss, email);     // Читаем email до конца строки

        User user(name, email);
        users.push_back(user); // Добавляем пользователя в список
    }
    inFile.close();
    std::cout << "Данные о пользователях загружены из файла " << filename << ".\n";
}
