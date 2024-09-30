#include "RentalSystem.h"
#include <iostream>
#include <format>
#include <ranges>

void RentalSystem::addApartment() {
    std::string address;
    std::cout << "������� ����� ��������: ";
    std::cin.ignore();
    std::getline(std::cin, address);

    int rooms;
    std::cout << "������� ���������� ������: ";
    std::cin >> rooms;

    double rent;
    std::cout << "������� ��������� ������: ";
    std::cin >> rent;

    int currencyChoice;
    std::cout << "�������� ������:\n1. BYN\n2. USD\n3. EUR\n������� ��� �����: ";
    std::cin >> currencyChoice;

    Currency currency = (currencyChoice == 2) ? Currency::USD :
        (currencyChoice == 3) ? Currency::EUR : Currency::BYN;

    apartments.emplace_back(address, rooms, rent, currency);
    std::cout << "�������� ��������� �������.\n";
}

void RentalSystem::showAllApartments() const {
    if (apartments.empty()) {
        std::cout << "��� ��������� �������.\n";
        return;
    }
    for (size_t i = 0; i < apartments.size(); ++i) {
        apartments[i].showInfo(i + 1);
        std::cout << "------------------------" << std::endl;
    }
}

// ������ ������ ��� ���������...

// ���������� ������������
void RentalSystem::addLandlord(const std::string& name) {
    landlords.emplace_back(name);
    std::cout << std::format("������������ {} �������� � �������.\n", name);
}

// ����� ���� �������������
void RentalSystem::showLandlords() const {
    if (landlords.empty()) {
        std::cout << "��� ������������������ �������������.\n";
        return;
    }
    for (size_t i = 0; i < landlords.size(); ++i) {
        std::cout << std::format("������������ #{}: {}\n", i + 1, landlords[i].getName());
    }
}

// ���������� �������� ������������ ��� �����
void RentalSystem::landlordAddApartmentToRent(int landlordIndex, int apartmentIndex) {
    if (landlordIndex >= 1 && landlordIndex <= landlords.size() &&
        apartmentIndex >= 1 && apartmentIndex <= apartments.size()) {
        landlords[landlordIndex - 1].addOwnedApartment(&apartments[apartmentIndex - 1]);
    }
    else {
        std::cout << "�������� ������ ������������ ��� ��������.\n";
    }
}

// ������ �������� �������������
void RentalSystem::landlordRentApartment(int landlordIndex, int apartmentIndex) {
    if (landlordIndex >= 1 && landlordIndex <= landlords.size() &&
        apartmentIndex >= 1 && apartmentIndex <= apartments.size()) {
        landlords[landlordIndex - 1].rentApartment(apartments[apartmentIndex - 1]);
    }
    else {
        std::cout << "�������� ������ ������������ ��� ��������.\n";
    }
}

// ������������ ������������ �������� �������������
void RentalSystem::landlordFreeRentedApartment(int landlordIndex) {
    if (landlordIndex >= 1 && landlordIndex <= landlords.size()) {
        landlords[landlordIndex - 1].freeRentedApartment();
    }
    else {
        std::cout << "�������� ������ ������������.\n";
    }
}
 
