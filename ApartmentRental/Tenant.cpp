#include "Tenant.h"
#include <iostream>
#include <format>

Tenant::Tenant(const std::string& name) : name(name) {}

std::string Tenant::getName() const {
    return name;
}

void Tenant::rentApartment(Apartment& apartment) {
    if (apartment.getAvailability()) {
        rentedApartment = &apartment;
        apartment.rentApartment();
        std::cout << std::format("{} арендовал квартиру на {}\n", name, apartment.getAddress());
    }
    else {
        std::cout << "Эта квартира уже арендована.\n";
    }
}

void Tenant::freeRentedApartment() {
    if (rentedApartment) {
        rentedApartment->freeApartment();
        rentedApartment = nullptr;
        std::cout << std::format("{} освободил арендованную квартиру.\n", name);
    }
    else {
        std::cout << "Вы не арендуете квартиру.\n";
    }
}

void Tenant::showRentedApartment() const {
    if (rentedApartment) {
        std::cout << std::format("{} арендует квартиру на:\n", name);
        rentedApartment->showInfo(1);
    }
    else {
        std::cout << "Вы не арендуете квартиру.\n";
    }
}
