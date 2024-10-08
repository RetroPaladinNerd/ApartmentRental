#ifndef APARTMENT_H
#define APARTMENT_H

#include <string>
#include <compare>  // Для оператора <=> в C++20
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

    // Объявление и определение оператора вывода как скрытого друга
    friend std::ostream& operator<<(std::ostream& os, const Apartment& apartment) {
        os << "Квартира ID: " << apartment.id
            << "\nМестоположение: " << apartment.location
            << "\nЦена: $" << apartment.price
            << "\nДоступность: " << (apartment.available ? "Доступна" : "Недоступна") << "\n";
        return os;
    }

    // Другие дружественные операторы
    friend bool operator==(const Apartment& lhs, const Apartment& rhs);
    friend std::partial_ordering operator<=>(const Apartment& lhs, const Apartment& rhs);

private:
    int id;
    std::string location;
    double price;
    bool available;
    double rating = 0.0;  // Инициализация рейтинга по умолчанию
};

#endif // APARTMENT_H
