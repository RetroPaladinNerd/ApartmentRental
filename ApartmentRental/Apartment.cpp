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
