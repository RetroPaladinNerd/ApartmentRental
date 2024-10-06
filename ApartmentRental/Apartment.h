#pragma once
#pragma once
#include <string>
#include <vector>
#include "Currency.h"

class Apartment {
private:
    std::string address;
    int rooms;
    double rent;
    Currency currency;
    bool isAvailable = true;
    std::vector<double> ratings;

public:
    Apartment(std::string_view address, int rooms, double rent, Currency currency);

    void showInfo(int index) const;
    double getAverageRating() const;
    void addRating(double rating);

    std::string getAddress() const;
    void setAddress(std::string_view newAddress);

    int getRooms() const;
    void setRooms(int newRooms);

    double getRent() const;
    void setRent(double newRent);

    Currency getCurrency() const;
    void setCurrency(Currency newCurrency);

    bool getAvailability() const;
    void rentApartment();
    void freeApartment();
};
