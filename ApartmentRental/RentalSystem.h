#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include "Apartment.h"
#include "User.h"

class RentalSystem {
public:
    void addApartment(const Apartment& apartment);
    void displayAvailableApartments() const;
    bool rentApartment(int apartmentId, const User& user);
    bool returnApartment(int apartmentId);
    bool removeApartment(int apartmentId);

    void addUser(const User& user);
    void displayUsers() const;

private:
    std::vector<Apartment> apartments;
    std::vector<User> users;
};

#endif // RENTALSYSTEM_H
