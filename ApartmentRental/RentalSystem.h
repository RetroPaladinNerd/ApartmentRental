#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include <string>
#include "Apartment.h"
#include "User.h"

class RentalSystem {
public:
    void addApartment(const Apartment& apartment);
    void displayAvailableApartments() const;
    bool rentApartment(int apartmentId, const User& user);
    bool returnApartment(int apartmentId);
    bool removeApartment(int apartmentId);
    void loadApartmentsFromFile(const std::string& filename);
    void saveApartmentsToFile(const std::string& filename) const;
    void loadUsersFromFile(const std::string& filename);
    void saveUsersToFile(const std::string& filename) const;

private:
    std::vector<Apartment> apartments;
    std::vector<User> users;
};

#endif // RENTALSYSTEM_H
