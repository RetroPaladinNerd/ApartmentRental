#pragma once
#include <string>
#include "Apartment.h"

class Tenant {
private:
    std::string name;        // ��� ����������
    Apartment* rentedApartment = nullptr;  // ������������ ��������

public:
    Tenant(const std::string& name);

    std::string getName() const;

    // ������ ��������
    void rentApartment(Apartment& apartment);

    // ������������ ������������ ��������
    void freeRentedApartment();

    // ����� ������������ ��������
    void showRentedApartment() const;
};
