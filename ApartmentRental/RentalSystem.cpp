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

void RentalSystem::rateApartment(int apartmentId, double rating) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId) {
            apartment.setRating(rating);
            std::cout << "������� ��� �������� � ID " << apartmentId << " ���������� �� " << rating << ".\n";
            return;
        }
    }
    std::cout << "�������� � ID " << apartmentId << " �� �������.\n";
}

double RentalSystem::getCurrencyRate(const std::string& currency) const {
    if (currency == "USD") return 1.0;
    if (currency == "EUR") return 0.85;
    if (currency == "GBP") return 3.20;
    return 1.0; // �� ��������� USD
}

bool RentalSystem::rentApartment(int apartmentId, const User& user, double rate, const std::string& currency) {
    for (auto& apartment : apartments) {
        if (apartment.getId() == apartmentId && apartment.isAvailable()) {
            apartment.setAvailable(false);
            users.push_back(user);

            double priceInCurrency = apartment.getPrice() * rate; // ������������� ����

            std::cout << user.getName() << " ��������� �������� � ID: " << apartmentId
                << " �� " << priceInCurrency << " " << currency << ".\n";
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
double RentalSystem::calculateRentalCost(int apartmentId, int rentalDays) const {
    for (const auto& apartment : apartments) {
        if (apartment.getId() == apartmentId) {
            double basePrice = apartment.getPrice();
            double totalCost = basePrice * rentalDays;

            // ������ ������ ��� ������������ ������ (>30 ����)
            if (rentalDays > 30) {
                totalCost *= 0.85; // ������ 15% �� ������ ����� 30 ����
            }

            std::cout << "�������� ��������� ������ �������� ID: " << apartmentId
                << " �� " << rentalDays << " ���� ��������: $" << totalCost << "\n";
            return totalCost;
        }
    }
    std::cout << "�������� � ID " << apartmentId << " �� �������.\n";
    return 0.0;
}
void RentalSystem::compareApartments(int apartmentId1, int apartmentId2) const {
    const Apartment* apt1 = nullptr;
    const Apartment* apt2 = nullptr;

    // ����� ������� � ��������� ID
    for (const auto& apartment : apartments) {
        if (apartment.getId() == apartmentId1) apt1 = &apartment;
        if (apartment.getId() == apartmentId2) apt2 = &apartment;
    }

    // ���������, ������� �� ��� ��������
    if (apt1 && apt2) {
        std::cout << "��������� �������:\n";

        // ��������� ��������������
        std::cout << "��������������:\n";
        std::cout << "�������� 1: " << apt1->getLocation() << "\n";
        std::cout << "�������� 2: " << apt2->getLocation() << "\n";

        // ��������� ���
        std::cout << "����:\n";
        std::cout << "�������� 1: $" << apt1->getPrice() << "\n";
        std::cout << "�������� 2: $" << apt2->getPrice() << "\n";

        // ��������� �����������
        std::cout << "�����������:\n";
        std::cout << "�������� 1: " << (apt1->isAvailable() ? "��������" : "����������") << "\n";
        std::cout << "�������� 2: " << (apt2->isAvailable() ? "��������" : "����������") << "\n";
    }
    else {
        std::cout << "���� ��� ��� �������� � ���������� ID �� �������.\n";
    }
}
