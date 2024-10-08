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

// �������� == ��� ������� ����
bool operator==(const Apartment& lhs, const Apartment& rhs) {
    return lhs.id == rhs.id && lhs.location == rhs.location &&
        lhs.price == rhs.price && lhs.available == rhs.available;
}

// �������� <=> ��� ������� ����
std::partial_ordering operator<=>(const Apartment& lhs, const Apartment& rhs) {
    return lhs.price <=> rhs.price;
}

// �������� ������ ���������� � �������� ��� ������� ����, ������������� � Apartment.cpp
std::ostream& operator<<(std::ostream& os, const Apartment& apartment) {
    os << "�������� ID: " << apartment.id
        << "\n��������������: " << apartment.location
        << "\n����: $" << apartment.price
        << "\n�����������: " << (apartment.available ? "��������" : "����������") << "\n";
    return os;
}
