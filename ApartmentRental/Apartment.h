#ifndef APARTMENT_H
#define APARTMENT_H

#include <string>
#include <compare>  // ƒл€ оператора <=> в C++20
#include <iostream>

class Apartment {
public:
    Apartment(int id, const std::string& location, double price, bool available);

    double getRating() const;
    void setRating(double rating);
    int getId() const;
    std::string getLocation() const;
    double getPrice() const;
    bool isAvailable() const;
    void setAvailable(bool availableStatus);

    // ƒружественные функции
    friend bool operator==(const Apartment& lhs, const Apartment& rhs);
    friend std::partial_ordering operator<=>(const Apartment& lhs, const Apartment& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Apartment& apartment); // ќбъ€вление как друга

private:
    int id;
    std::string location;
    double price;
    bool available;
    double rating = 0.0;  // »нициализаци€ рейтинга по умолчанию
};

#endif // APARTMENT_H
