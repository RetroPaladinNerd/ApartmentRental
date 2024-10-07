#include "Apartment.h"
#include <iostream>

Apartment::Apartment(int id, const std::string& location, double price, bool available)
    : id(id), location(location), price(price), available(available), rating(0.0) {} // Инициализация рейтинга

double Apartment::getRating() const {
    return rating;
}

void Apartment::setRating(double rating) {
    this->rating = rating;
}

int Apartment::getId() const {
    return id;
}

std::string Apartment::getLocation() const {
    return location;
}

double Apartment::getPrice() const {
    return price;
}

bool Apartment::isAvailable() const {
    return available;
}

void Apartment::setAvailable(bool available) {
    this->available = available;
}

void displayApartmentInfo(const Apartment& apartment) {
    std::cout << "Квартира ID: " << apartment.id
        << "\nМестоположение: " << apartment.location
        << "\nЦена: $" << apartment.price
        << "\nДоступность: " << (apartment.available ? "Доступна" : "Недоступна") << "\n";
}

bool Apartment::operator==(const Apartment & other) const {
        return this->id == other.id;
}

bool Apartment::operator>(const Apartment& other) const {
        return this->price > other.price;
}

std::ostream& operator<<(std::ostream& os, const Apartment& apartment) {
    os << "Квартира ID: " << apartment.id
        << "\nМестоположение: " << apartment.location
        << "\nЦена: $" << apartment.price
        << "\nДоступность: " << (apartment.available ? "Доступна" : "Недоступна") << "\n";
    return os;
}
