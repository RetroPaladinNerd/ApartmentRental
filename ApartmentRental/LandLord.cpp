#include "Landlord.h"
#include <iostream>
#include <format>

Landlord::Landlord(const std::string& name) : name(name) {}

std::string Landlord::getName() const {
    return name;
}

void Landlord::addOwnedApartment(Apartment* apartment) {
    ownedApartments.push_back(apartment);
    std::cout << std::format(" вартира на {} добавлена в список сдаваемых квартир.\n", apartment->getAddress());
}

void Landlord::showOwnedApartments() const {
    if (ownedApartments.empty()) {
        std::cout << "” вас нет квартир дл€ сдачи.\n";
        return;
    }
    std::cout << std::format(" вартиры, сдаваемые {}:\n", name);
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
        std::cout << "Ёта квартира уже арендована.\n";
    }
}

void Landlord::freeRentedApartment() {
    if (rentedApartment) {
        rentedApartment->freeApartment();
        rentedApartment = nullptr;
        std::cout << std::format("{} освободил арендованную квартиру.\n", name);
    }
    else {
        std::cout << "¬ы не арендуете квартиру.\n";
    }
}

void Landlord::showRentedApartment() const {
    if (rentedApartment) {
        std::cout << std::format("{} арендует квартиру на:\n", name);
        rentedApartment->showInfo(1);
    }
    else {
        std::cout << "¬ы не арендуете квартиру.\n";
    }
}
