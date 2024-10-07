#include "RentalSystem.h"
#include <iostream>

void RentalSystem::addApartment(const Apartment& apartment) {
    apartments.push_back(apartment);
}

void RentalSystem::displayAvailableApartments() const {
    std::cout << "��������� ��������:\n";
    for (const auto& apartment : apartments) {
        if (apartment.isAvailable()) {
            std::cout << "ID: " << apartment.getId() << ", ��������������: "
                << apartment.getLocation() << ", ����: $"
                << apartment.getPrice() << "\n";
        }
    }
}

bool RentalSystem::rentApartment(int apartmentId, const User& user) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId && apartment.isAvailable()) {
            apartment.setAvailable(false);
            users.push_back(user);
            std::cout << user.getName() << " ��������� �������� � ID: "
                << apartmentId << "\n";
            return true;
        }
    }
    std::cout << "�������� � ID " << apartmentId << " ����������.\n";
    return false;
}

bool RentalSystem::returnApartment(int apartmentId) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId && !apartment.isAvailable()) {
            apartment.setAvailable(true);
            std::cout << "�������� � ID " << apartmentId << " ���� ����������.\n";
            return true;
        }
    }
    std::cout << "�������� � ID " << apartmentId << " � ������ ������ �� ����������.\n";
    return false;
}

bool RentalSystem::removeApartment(int apartmentId) {
    for (auto it = apartments.begin(); it != apartments.end(); ++it) {
        if (it->getId() == apartmentId) {
            apartments.erase(it);
            std::cout << "�������� � ID " << apartmentId << " ���� �������.\n";
            return true;
        }
    }
    std::cout << "�������� � ID " << apartmentId << " �� �������.\n";
    return false;
}

void RentalSystem::addUser(const User& user) {
    users.push_back(user);
}

void RentalSystem::displayUsers() const {
    std::cout << "������������:\n";
    for (const auto& user : users) {
        std::cout << "���: " << user.getName() << ", Email: " << user.getEmail() << "\n";
    }
}
