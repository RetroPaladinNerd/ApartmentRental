#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include <string>
#include "Apartment.h"
#include "User.h"
#include <sqlite3.h>

class RentalSystem {
public:
    RentalSystem();
    ~RentalSystem();

    sqlite3* db; // указатель на базу данных

    void addApartmentToDB(const Apartment& apartment);
    void displayAvailableApartmentsFromDB() const;
    bool rentApartmentFromDB(int apartmentId, const User& user);
    bool returnApartmentToDB(int apartmentId);
    bool removeApartmentFromDB(int apartmentId);

    void rateApartmentInDB(int apartmentId, double rating); //  метод для установки рейтинга

    void addUserToDB(const User& user);
    void displayUsersFromDB() const;

    double getCurrencyRate(std::string_view currency) const;
    double calculateRentalCostFromDB(int apartmentId, int rentalDays) const;
    void compareApartmentsFromDB(int apartmentId1, int apartmentId2) const;
    

private:
    std::vector<Apartment> apartments;
    std::vector<User> users;

    void openDB();
    void closeDB();
    void executeSQL(const std::string& sql) const;
};

#endif // RENTALSYSTEM_H
