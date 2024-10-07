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

bool RentalSystem::rentApartment(int apartmentId, const User& user) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId && apartment.isAvailable()) {
            apartment.setAvailable(false);
            users.push_back(user);
            std::cout << user.getName() << " арендовал квартиру с ID: "
                << apartmentId << "\n";
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

void RentalSystem::loadApartmentsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int id;
        std::string location;
        double price;
        bool available;

        if (iss >> id >> std::ws) {
            std::getline(iss, location, ',');
            iss >> price >> available;
            addApartment(Apartment(id, location, price, available));
        }
    }
    file.close();
}

void RentalSystem::saveApartmentsToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& apartment : apartments) {
        file << apartment.getId() << " "
            << apartment.getLocation() << ","
            << apartment.getPrice() << " "
            << apartment.isAvailable() << "\n";
    }
    file.close();
}

void RentalSystem::loadUsersFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, email;
        std::getline(iss, name, ',');
        std::getline(iss, email);
        users.push_back(User(name, email));
    }
    file.close();
}

void RentalSystem::saveUsersToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& user : users) {
        file << user.toString() << "\n";
    }
    file.close();
}
