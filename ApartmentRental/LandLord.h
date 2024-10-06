#pragma once
#include <string>
#include <vector>
#include "Apartment.h"

class Landlord {
private:
    std::string name;
    std::vector<Apartment*> ownedApartments;  // ������ �������, ������� ������������ ����
    Apartment* rentedApartment = nullptr;     // ��������, ������� ������������ ��������

public:
    Landlord(const std::string& name);

    std::string getName() const;

    // ������ ��� ���������� ����������
    void addOwnedApartment(Apartment* apartment);  // ���������� �������� � ������ �����������
    void showOwnedApartments() const;              // ����� ���� �������, ������� �������

    // ������� ������
    void rentApartment(Apartment& apartment);      // ������ ��������
    void freeRentedApartment();                    // ������������ ������������ ��������
    void showRentedApartment() const;              // ����� ������������ ��������

    // ���� ��� ������������
    void landlordMenu();

    // ���� ��� ����������
    void tenantMenu();
};
