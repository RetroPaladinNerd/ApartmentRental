#include "Landlord.h"
#include <iostream>
#include <format>

Landlord::Landlord(const std::string& name) : name(name) {}

std::string Landlord::getName() const {
    return name;
}

void Landlord::addOwnedApartment(Apartment* apartment) {
    ownedApartments.push_back(apartment);
    std::cout << std::format("Квартира на {} добавлена в список сдаваемых квартир.\n", apartment->getAddress());
}

void Landlord::showOwnedApartments() const {
    if (ownedApartments.empty()) {
        std::cout << "У вас нет квартир для сдачи.\n";
        return;
    }
    std::cout << std::format("Квартиры, сдаваемые {}:\n", name);
    for (size_t i = 0; i < ownedApartments.size(); ++i) {
        ownedApartments[i]->showInfo(i + 1);
        std::cout << "------------------------" << std::endl;
    }
}

void Landlord::rentApartment(Apartment& apartment) {
    if (apartment.getAvailability()) {
        rentedApartment = &apartment;
        apartment.rentApartment();
        std::cout << std::format("{} арендовал квартиру на {}\n", name, apartment.getAddress());
    }
    else {
        std::cout << "Эта квартира уже арендована.\n";
    }
}

void Landlord::freeRentedApartment() {
    if (rentedApartment) {
        rentedApartment->freeApartment();
        rentedApartment = nullptr;
        std::cout << std::format("{} освободил арендованную квартиру.\n", name);
    }
    else {
        std::cout << "Вы не арендуете квартиру.\n";
    }
}

void Landlord::showRentedApartment() const {
    if (rentedApartment) {
        std::cout << std::format("{} арендует квартиру на:\n", name);
        rentedApartment->showInfo(1);
    }
    else {
        std::cout << "Вы не арендуете квартиру.\n";
    }
}

// Меню для арендодателя
void Landlord::landlordMenu() {
    int choice;
    do {
        std::cout << "\nМеню арендодателя:\n";
        std::cout << "1. Добавить квартиру для сдачи\n";
        std::cout << "2. Показать все сдаваемые квартиры\n";
        std::cout << "3. Арендовать квартиру\n";
        std::cout << "4. Освободить арендованную квартиру\n";
        std::cout << "5. Показать арендованную квартиру\n";
        std::cout << "0. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            // Логика добавления квартиры
            std::cout << "Введите адрес квартиры: ";
            std::string address;
            std::cin.ignore();
            std::getline(std::cin, address);

            int rooms;
            std::cout << "Введите количество комнат: ";
            std::cin >> rooms;

            double rent;
            std::cout << "Введите стоимость аренды: ";
            std::cin >> rent;

            int currencyChoice;
            std::cout << "Выберите валюту:\n1. BYN\n2. USD\n3. EUR\nВведите ваш выбор: ";
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
            // Арендовать квартиру
            // Можно добавить список доступных квартир для аренды здесь
            break;
        }
        case 4:
            freeRentedApartment();
            break;
        case 5:
            showRentedApartment();
            break;
        case 0:
            std::cout << "Выход из меню арендодателя.\n";
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 0);
}

// Меню для арендатора
void Landlord::tenantMenu() {
    int choice;
    do {
        std::cout << "\nМеню арендатора:\n";
        std::cout << "1. Показать все доступные квартиры\n";
        std::cout << "2. Поиск квартиры по цене\n";
        std::cout << "3. Арендовать квартиру\n";
        std::cout << "4. Освободить арендованную квартиру\n";
        std::cout << "5. Показать арендованную квартиру\n";
        std::cout << "0. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            // Логика показа всех доступных квартир
            break;
        case 2:
            // Логика поиска квартиры по цене
            break;
        case 3:
            // Логика аренды квартиры
            break;
        case 4:
            freeRentedApartment();
            break;
        case 5:
            showRentedApartment();
            break;
        case 0:
            std::cout << "Выход из меню арендатора.\n";
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 0);
}
