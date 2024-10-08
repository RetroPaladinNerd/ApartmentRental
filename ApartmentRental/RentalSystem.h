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
    bool rentApartment(int apartmentId, const User& user, double rate, const std::string& currency); // �������� ��������� ������
    bool returnApartment(int apartmentId);
    bool removeApartment(int apartmentId);

    void rateApartment(int apartmentId, double rating); //  ����� ��� ��������� ��������

    void addUser(const User& user);
    void displayUsers() const;

    double getCurrencyRate(std::string_view currency) const; // ����� ��� ��������� ����� ������
    double calculateRentalCost(int apartmentId, int rentalDays) const;
    void compareApartments(int apartmentId1, int apartmentId2) const;
    
    void saveApartmentsToFile(const std::string& filename) const; // ������ � ���� �������
    void saveUsersToFile(const std::string& filename) const; // ������ � ���� �������������
    void loadApartmentsFromFile(const std::string& filename); // ������ � ���� �������
    void loadUsersFromFile(const std::string& filename); // ������ � ���� �������������


private:
    std::vector<Apartment> apartments;
    std::vector<User> users;
};

#endif // RENTALSYSTEM_H
