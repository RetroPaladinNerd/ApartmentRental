#ifndef APARTMENT_H
#define APARTMENT_H

#include <string>
#include <compare>  
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

    // Дружественные операторы как скрытые друзья
    friend bool operator==(const Apartment& lhs, const Apartment& rhs) {
        return lhs.id == rhs.id && lhs.location == rhs.location &&
            lhs.price == rhs.price && lhs.available == rhs.available;
    }

    friend std::partial_ordering operator<=>(const Apartment& lhs, const Apartment& rhs) {
        return lhs.price <=> rhs.price;  // Сравнение только по цене
    }

    friend std::ostream& operator<<(std::ostream& os, const Apartment& apartment) {
        os << "Квартира ID: " << apartment.id
            << "\nМестоположение: " << apartment.location
            << "\nЦена: $" << apartment.price
            << "\nДоступность: " << (apartment.available ? "Доступна" : "Недоступна") << "\n";
        return os;
    }

private:
    int id;
    std::string location;
    double price;
    bool available;
    double rating = 0.0;  // Инициализация рейтинга по умолчанию
};

#endif // APARTMENT_H
