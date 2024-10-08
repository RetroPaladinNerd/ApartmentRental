#include "Apartment.h"
#include <iostream>

Apartment::Apartment(int id, const std::string& location, double price, bool available)
    : id(id), location(location), price(price), available(available) {}

double Apartment::getRating() const {
    return rating;
}

void Apartment::setRating(double newRating) {
    rating = newRating;
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

void Apartment::setAvailable(bool isAvailable) {
    available = isAvailable;
}

// Реализация оператора == как скрытого друга
bool operator==(const Apartment& lhs, const Apartment& rhs) {
    return lhs.id == rhs.id && lhs.location == rhs.location &&
        lhs.price == rhs.price && lhs.available == rhs.available;
}

// Реализация оператора <=> как скрытого друга с использованием partial_ordering
std::partial_ordering operator<=>(const Apartment& lhs, const Apartment& rhs) {
    return lhs.price <=> rhs.price;  // Сравнение по цене
}

// Оператор вывода информации о квартире
std::ostream& operator<<(std::ostream& os, const Apartment& apartment) {
    os << "Квартира ID: " << apartment.id
        << "\nМестоположение: " << apartment.location
        << "\nЦена: $" << apartment.price
        << "\nДоступность: " << (apartment.available ? "Доступна" : "Недоступна") << "\n";
    return os;
}
