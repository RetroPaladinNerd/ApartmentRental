#pragma once
#pragma once
#include <vector>
#include "Apartment.h"
#include "Landlord.h"

class RentalSystem {
private:
    std::vector<Apartment> apartments;
    std::vector<Landlord> landlords;  // ������ �������������

public:
    // ������ ��� ���������� ����������
    void addApartment();
    void showAllApartments() const;
    void searchApartmentByPrice(double minPrice, double maxPrice) const;
    void sortApartmentsByPrice();
    void rateApartment();
    void rentApartment();
    void freeApartment();

    // ������ ��� ������ � ��������������
    void addLandlord(const std::string& name);
    void showLandlords() const;
    void landlordAddApartmentToRent(int landlordIndex, int apartmentIndex);
    void landlordRentApartment(int landlordIndex, int apartmentIndex);
    void landlordFreeRentedApartment(int landlordIndex);
};
