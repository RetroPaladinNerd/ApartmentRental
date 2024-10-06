#include "Landlord.h"
#include <iostream>
#include <format>

Landlord::Landlord(const std::string& name) : name(name) {}

std::string Landlord::getName() const {
    return name;
}

void Landlord::addOwnedApartment(Apartment* apartment) {
    ownedApartments.push_back(apartment);
    std::cout << std::format("�������� �� {} ��������� � ������ ��������� �������.\n", apartment->getAddress());
}

void Landlord::showOwnedApartments() const {
    if (ownedApartments.empty()) {
        std::cout << "� ��� ��� ������� ��� �����.\n";
        return;
    }
    std::cout << std::format("��������, ��������� {}:\n", name);
    for (size_t i = 0; i < ownedApartments.size(); ++i) {
        ownedApartments[i]->showInfo(i + 1);
        std::cout << "------------------------" << std::endl;
    }
}

void Landlord::rentApartment(Apartment& apartment) {
    if (apartment.getAvailability()) {
        rentedApartment = &apartment;
        apartment.rentApartment();
        std::cout << std::format("{} ��������� �������� �� {}\n", name, apartment.getAddress());
    }
    else {
        std::cout << "��� �������� ��� ����������.\n";
    }
}

void Landlord::freeRentedApartment() {
    if (rentedApartment) {
        rentedApartment->freeApartment();
        rentedApartment = nullptr;
        std::cout << std::format("{} ��������� ������������ ��������.\n", name);
    }
    else {
        std::cout << "�� �� ��������� ��������.\n";
    }
}

void Landlord::showRentedApartment() const {
    if (rentedApartment) {
        std::cout << std::format("{} �������� �������� ��:\n", name);
        rentedApartment->showInfo(1);
    }
    else {
        std::cout << "�� �� ��������� ��������.\n";
    }
}

// ���� ��� ������������
void Landlord::landlordMenu() {
    int choice;
    do {
        std::cout << "\n���� ������������:\n";
        std::cout << "1. �������� �������� ��� �����\n";
        std::cout << "2. �������� ��� ��������� ��������\n";
        std::cout << "3. ���������� ��������\n";
        std::cout << "4. ���������� ������������ ��������\n";
        std::cout << "5. �������� ������������ ��������\n";
        std::cout << "0. �����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // ������ ���������� ��������
            std::cout << "������� ����� ��������: ";
            std::string address;
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

            Apartment* newApartment = new Apartment(address, rooms, rent, currency);
            addOwnedApartment(newApartment);
            break;
        }
        case 2:
            showOwnedApartments();
            break;
        case 3: {
            // ���������� ��������
            // ����� �������� ������ ��������� ������� ��� ������ �����
            break;
        }
        case 4:
            freeRentedApartment();
            break;
        case 5:
            showRentedApartment();
            break;
        case 0:
            std::cout << "����� �� ���� ������������.\n";
            break;
        default:
            std::cout << "�������� �����. ����������, ���������� �����.\n";
            break;
        }
    } while (choice != 0);
}

// ���� ��� ����������
void Landlord::tenantMenu() {
    int choice;
    do {
        std::cout << "\n���� ����������:\n";
        std::cout << "1. �������� ��� ��������� ��������\n";
        std::cout << "2. ����� �������� �� ����\n";
        std::cout << "3. ���������� ��������\n";
        std::cout << "4. ���������� ������������ ��������\n";
        std::cout << "5. �������� ������������ ��������\n";
        std::cout << "0. �����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            // ������ ������ ���� ��������� �������
            break;
        case 2:
            // ������ ������ �������� �� ����
            break;
        case 3:
            // ������ ������ ��������
            break;
        case 4:
            freeRentedApartment();
            break;
        case 5:
            showRentedApartment();
            break;
        case 0:
            std::cout << "����� �� ���� ����������.\n";
            break;
        default:
            std::cout << "�������� �����. ����������, ���������� �����.\n";
            break;
        }
    } while (choice != 0);
}
