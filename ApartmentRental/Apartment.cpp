#include "Apartment.h"
#include <iostream>
#include <format>

Apartment::Apartment(std::string_view address, int rooms, double rent, Currency currency)
    : address(address), rooms(rooms), rent(rent), currency(currency) {}

void Apartment::showInfo(int index) const {
    std::cout << std::format("�������� #{}\n", index);
    std::cout << std::format("�����: {}\n", address);
    std::cout << std::format("������: {}\n", rooms);
    std::cout << std::format("������: {} {}\n", rent, currencyToString(currency));
    std::cout << std::format("�����������: {}\n", (isAvailable ? "��������" : "������"));
    std::cout << std::format("�������: {}\n", (ratings.empty() ? "��� ��������" : std::to_string(getAverageRating())));
}

double Apartment::getAverageRating() const {
    if (ratings.empty()) return 0.0;
    double sum = 0;
    for (double rating : ratings) {
        sum += rating;
    }
    return round((sum / ratings.size()) * 100) / 100;
}

void Apartment::addRating(double rating) {
    ratings.push_back(rating);
    std::cout << std::format("�������� ������� �� {:.2f} ����.\n", rating);
}

std::string Apartment::getAddress() const { return address; }
void Apartment::setAddress(std::string_view newAddress) { address = newAddress; }

int Apartment::getRooms() const { return rooms; }
void Apartment::setRooms(int newRooms) { rooms = newRooms; }

double Apartment::getRent() const { return rent; }
void Apartment::setRent(double newRent) { rent = newRent; }

Currency Apartment::getCurrency() const { return currency; }
void Apartment::setCurrency(Currency newCurrency) { currency = newCurrency; }

bool Apartment::getAvailability() const { return isAvailable; }

void Apartment::rentApartment() {
    if (isAvailable) {
        isAvailable = false;
        std::cout << std::format("�������� �� {} ����������.\n", address);
    }
    else {
        std::cout << std::format("�������� �� {} ��� ����������.\n", address);
    }
}

void Apartment::freeApartment() {
    isAvailable = true;
    std::cout << std::format("�������� �� {} ����� �������� ��� ������.\n", address);
}
