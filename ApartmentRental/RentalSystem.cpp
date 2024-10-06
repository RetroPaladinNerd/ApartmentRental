#include "RentalSystem.h"
#include <iostream>
#include <format>
#include <ranges>

void RentalSystem::addApartment() {
    std::string address;
    std::cout << "Введите адрес квартиры: ";
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

    apartments.emplace_back(address, rooms, rent, currency);
    std::cout << "Квартира добавлена успешно.\n";
}

void RentalSystem::showAllApartments() const {
    if (apartments.empty()) {
        std::cout << "Нет доступных квартир.\n";
        return;
    }
    for (size_t i = 0; i < apartments.size(); ++i) {
        apartments[i].showInfo(i + 1);
        std::cout << "------------------------" << std::endl;
    }
}

// Другие методы без изменений...

// Добавление арендодателя
void RentalSystem::addLandlord(const std::string& name) {
    landlords.emplace_back(name);
    std::cout << std::format("Арендодатель {} добавлен в систему.\n", name);
}

// Показ всех арендодателей
void RentalSystem::showLandlords() const {
    if (landlords.empty()) {
        std::cout << "Нет зарегистрированных арендодателей.\n";
        return;
    }
    for (size_t i = 0; i < landlords.size(); ++i) {
        std::cout << std::format("Арендодатель #{}: {}\n", i + 1, landlords[i].getName());
    }
}

// Добавление квартиры арендодателю для сдачи
void RentalSystem::landlordAddApartmentToRent(int landlordIndex, int apartmentIndex) {
    if (landlordIndex >= 1 && landlordIndex <= landlords.size() &&
        apartmentIndex >= 1 && apartmentIndex <= apartments.size()) {
        landlords[landlordIndex - 1].addOwnedApartment(&apartments[apartmentIndex - 1]);
    }
    else {
        std::cout << "Неверный индекс арендодателя или квартиры.\n";
    }
}

// Аренда квартиры арендодателем
void RentalSystem::landlordRentApartment(int landlordIndex, int apartmentIndex) {
    if (landlordIndex >= 1 && landlordIndex <= landlords.size() &&
        apartmentIndex >= 1 && apartmentIndex <= apartments.size()) {
        landlords[landlordIndex - 1].rentApartment(apartments[apartmentIndex - 1]);
    }
    else {
        std::cout << "Неверный индекс арендодателя или квартиры.\n";
    }
}

// Освобождение арендованной квартиры арендодателем
void RentalSystem::landlordFreeRentedApartment(int landlordIndex) {
    if (landlordIndex >= 1 && landlordIndex <= landlords.size()) {
        landlords[landlordIndex - 1].freeRentedApartment();
    }
    else {
        std::cout << "Неверный индекс арендодателя.\n";
    }
}
 
