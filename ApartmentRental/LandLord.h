#pragma once
#include <string>
#include <vector>
#include "Apartment.h"

class Landlord {
private:
    std::string name;
    std::vector<Apartment*> ownedApartments;  // Список квартир, которые арендодатель сдаёт
    Apartment* rentedApartment = nullptr;     // Квартира, которую арендодатель арендует

public:
    Landlord(const std::string& name);

    std::string getName() const;

    // Методы для управления квартирами
    void addOwnedApartment(Apartment* apartment);  // Добавление квартиры в список собственных
    void showOwnedApartments() const;              // Показ всех квартир, которые сдаются

    // Функции аренды
    void rentApartment(Apartment& apartment);      // Аренда квартиры
    void freeRentedApartment();                    // Освобождение арендованной квартиры
    void showRentedApartment() const;              // Показ арендованной квартиры

    // Меню для арендодателя
    void landlordMenu();

    // Меню для арендатора
    void tenantMenu();
};
