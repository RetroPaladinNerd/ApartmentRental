#include "RentalSystem.h"
#include <iostream>

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

void RentalSystem::addUser(const User& user) {
    users.push_back(user);
}

void RentalSystem::displayUsers() const {
    std::cout << "Пользователи:\n";
    for (const auto& user : users) {
        std::cout << "Имя: " << user.getName() << ", Email: " << user.getEmail() << "\n";
    }
}
