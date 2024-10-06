#pragma once
#include <string>
#include "Apartment.h"

class Tenant {
private:
    std::string name;        // Имя арендатора
    Apartment* rentedApartment = nullptr;  // Арендованная квартира

public:
    Tenant(const std::string& name);

    std::string getName() const;

    // Аренда квартиры
    void rentApartment(Apartment& apartment);

    // Освобождение арендованной квартиры
    void freeRentedApartment();

    // Показ арендованной квартиры
    void showRentedApartment() const;
};
