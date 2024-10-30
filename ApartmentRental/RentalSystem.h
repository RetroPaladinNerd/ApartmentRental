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
    ~RentalSystem() final;

    // ���������� ������� DatabaseManager
     void openDB() override;
     void closeDB() override;
     void executeSQL(const std::string& sql) const override;

    // ���������� ������� Comparable
     void compareApartmentsFromDB(int apartmentId1, int apartmentId2) const override;

    // ������, ��������� � ����������������� ������
    virtual void addApartmentToDB(const Apartment& apartment);
    virtual void displayAvailableApartmentsFromDB() const;
    virtual bool rentApartmentFromDB(int apartmentId, const User& user);
    virtual bool returnApartmentToDB(int apartmentId);
    virtual bool removeApartmentFromDB(int apartmentId);
    virtual void rateApartmentInDB(int apartmentId, double rating);

    virtual void addUserToDB(const User& user);
    virtual void displayUsersFromDB() const;

private:
    sqlite3* db;  // ��������� �� ���� ������
    std::vector<Apartment> apartments;
    std::vector<User> users;
};

#endif // RENTALSYSTEM_H
