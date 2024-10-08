#ifndef APARTMENT_H
#define APARTMENT_H

#include <string>

class Apartment {
public:
    Apartment(int id, const std::string& location, double price, bool available);

    int getId() const;
    std::string getLocation() const;
    double getPrice() const;
    bool isAvailable() const;

    // �������
    void setRating(double rating);
    double getRating() const;

    void setAvailable(bool available);

private:
    int id;
    std::string location;
    double price;
    bool available;
    double rating = 0.0; 

    friend void displayApartmentInfo(const Apartment& apartment); // ������������� �������

    bool operator==(const Apartment& other) const; // ����������
    bool operator>(const Apartment& other) const; // ��������� ���
    friend std::ostream& operator<<(std::ostream& os, const Apartment& apartment); // ������� �����

};

#endif // APARTMENT_H
