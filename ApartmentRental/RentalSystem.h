//#ifndef RENTALSYSTEM_H
//#define RENTALSYSTEM_H
//
//#include <vector>
//#include <string>
//#include "Apartment.h"
//#include "User.h"
//#include <sqlite3.h>
//
//class RentalSystem {
//public:
//    RentalSystem();
//    ~RentalSystem();
//
//    sqlite3* db; // указатель на базу данных
//
//    void addApartmentToDB(const Apartment& apartment);
//    void displayAvailableApartmentsFromDB() const;
//    bool rentApartmentFromDB(int apartmentId, const User& user);
//    bool returnApartmentToDB(int apartmentId);
//    bool removeApartmentFromDB(int apartmentId);
//
//    void rateApartmentInDB(int apartmentId, double rating); //  метод для установки рейтинга
//
//    void addUserToDB(const User& user);
//    void displayUsersFromDB() const;
//
//    double getCurrencyRate(std::string_view currency) const;
//    double calculateRentalCostFromDB(int apartmentId, int rentalDays) const;
//    void compareApartmentsFromDB(int apartmentId1, int apartmentId2) const;
//    void compareApartments(int apartmentId1, int apartmentId2);
//
//private:
//    std::vector<Apartment> apartments;
//    std::vector<User> users;
//
//    void openDB();
//    void closeDB();
//    void executeSQL(const std::string& sql) const;
//};
//
//#endif // RENTALSYSTEM_H
//
//// сделать все функции что тут есть виртуальными

//#ifndef RENTALSYSTEM_H
//#define RENTALSYSTEM_H
//
//#include <vector>
//#include <string>
//#include "Apartment.h"
//#include "User.h"
//#include "DatabaseManager.h"
//#include <sqlite3.h>
//#include "Comparable.h"
//
//class RentalSystem : public DatabaseManager {
//public:
//    RentalSystem();
//    virtual ~RentalSystem();
//
//    // Реализация методов DatabaseManager
//    virtual void openDB() override;
//    virtual void closeDB() override;
//    virtual void executeSQL(const std::string& sql) const override;
//
//    // Реализация методов Comparable
//    virtual void compareApartmentsFromDB(int apartmentId1, int apartmentId2) const override;
//
//    // Методы, связанные с функциональностью аренды
//    virtual void addApartmentToDB(const Apartment& apartment);
//    virtual void displayAvailableApartmentsFromDB() const;
//    virtual bool rentApartmentFromDB(int apartmentId, const User& user);
//    virtual bool returnApartmentToDB(int apartmentId);
//    virtual bool removeApartmentFromDB(int apartmentId);
//    virtual void rateApartmentInDB(int apartmentId, double rating); // метод для установки рейтинга
//
//    // Методы, связанные с работой с пользователем
//    virtual void addUserToDB(const User& user);
//    virtual void displayUsersFromDB() const;
//
//protected:
//    sqlite3* db;  // указатель на базу данных
//    std::vector<Apartment> apartments;
//    std::vector<User> users;
//};
//
//#endif // RENTALSYSTEM_H

#ifndef RENTALSYSTEM_H
#define RENTALSYSTEM_H

#include <vector>
#include <string>
#include "Apartment.h"
#include "User.h"
#include "DatabaseManager.h"
#include "Comparable.h"
#include <sqlite3.h>

class RentalSystem : public DatabaseManager, public Comparable {
public:
    RentalSystem();
    virtual ~RentalSystem();

    // Реализация методов DatabaseManager
    virtual void openDB() override;
    virtual void closeDB() override;
    virtual void executeSQL(const std::string& sql) const override;

    // Реализация методов Comparable
    virtual void compareApartmentsFromDB(int apartmentId1, int apartmentId2) const override;

    // Методы, связанные с функциональностью аренды
    virtual void addApartmentToDB(const Apartment& apartment);
    virtual void displayAvailableApartmentsFromDB() const;
    virtual bool rentApartmentFromDB(int apartmentId, const User& user);
    virtual bool returnApartmentToDB(int apartmentId);
    virtual bool removeApartmentFromDB(int apartmentId);
    virtual void rateApartmentInDB(int apartmentId, double rating);

    virtual void addUserToDB(const User& user);
    virtual void displayUsersFromDB() const;

protected:
    sqlite3* db;  // указатель на базу данных
    std::vector<Apartment> apartments;
    std::vector<User> users;
};

#endif // RENTALSYSTEM_H
