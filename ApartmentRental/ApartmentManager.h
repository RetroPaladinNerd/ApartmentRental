// ApartmentManager.h
#ifndef APARTMENT_MANAGER_H
#define APARTMENT_MANAGER_H

#include <string>
#include "Apartment.h"

class ApartmentManager {
public:
    virtual void addApartment(const Apartment& apartment) = 0;
    virtual void displayAvailableApartments() const = 0;
    virtual void rentApartment(int apartmentId, const User& user) = 0;
    virtual void returnApartment(int apartmentId) = 0;
    virtual ~ApartmentManager() = default;
};

#endif // APARTMENT_MANAGER_H
