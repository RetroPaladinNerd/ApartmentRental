#ifndef APARTMENT_H
#define APARTMENT_H

#include <string>
#include <compare>  // Для оператора <=> в C++20
#include <iostream>

class Apartment {
public:
    Apartment(int id, const std::string& location, double price, bool available);

    double getRating() const;
    void setRating(double newRating);
    int getId() const;
    std::string getLocation() const;
    double getPrice() const;
    bool isAvailable() const;
    void setAvailable(bool isAvailable);

    // Дружественные функции для перегруженных операторов
    friend bool operator==(const Apartment& lhs, const Apartment& rhs);
    friend std::partial_ordering operator<=>(const Apartment& lhs, const Apartment& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Apartment& apartment);

private:
    int id;
    std::string location;
    double price;
    bool available;
    double rating = 0.0;  // Инициализация рейтинга по умолчанию
};

#endif // APARTMENT_H
