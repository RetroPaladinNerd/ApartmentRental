#ifndef APARTMENT_H
#define APARTMENT_H

#include <string>

class Apartment {
public:
    Apartment(int id, const std::string& location, double price, bool available);

    int getId() const;
    std::string getLocation() const;
    double getPrice() const;
    bool isAvailable() const;

    void setAvailable(bool available);

private:
    int id;
    std::string location;
    double price;
    bool available;
};

#endif // APARTMENT_H
