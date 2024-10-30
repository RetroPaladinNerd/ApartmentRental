#include <iostream>
#include <string>
#include "RentalSystem.h"
#include "User.h"

//���������� ����
void displayMainMenu();
void displayApartmentMenu();
void displayUserMenu();
void handleAddApartment(RentalSystem& system);
void handleDisplayApartments(const RentalSystem& system);
void handleRentApartment(RentalSystem& system);
void handleReturnApartment(RentalSystem& system);
void handleRemoveApartment(RentalSystem& system);
void handleRateApartment(RentalSystem& system);
void handleAddUser(RentalSystem& system);
void handleDisplayUsers(const RentalSystem& system);
void handleCompareApartments(const RentalSystem& system);
void handleApartmentSection(RentalSystem& rentalSystem);
void handleUserSection(RentalSystem& rentalSystem);


int main() {
    std::system("chcp 1251");
    std::system("cls");
    RentalSystem rentalSystem;
    int choice;

    do {
        displayMainMenu();
        std::cout << "�������� ������: ";
        std::cin >> choice;
        std::cin.ignore(); // ������� ������

        switch (choice) {
        case 1: handleApartmentSection(rentalSystem); break;
        case 2: handleUserSection(rentalSystem); break;
        case 0: std::cout << "����� �� ���������...\n"; break;
        default: std::cout << "�������� ����. ����������, �������� �������������� �������.\n"; break;
        }
    } while (choice != 0);

    return 0;
}

void handleApartmentSection(RentalSystem& rentalSystem) {
    int apartmentChoice;
    do {
        displayApartmentMenu();
        std::cout << "�������� ��������: ";
        std::cin >> apartmentChoice;
        std::cin.ignore(); // ������� ������

        switch (apartmentChoice) {
        case 1: handleAddApartment(rentalSystem); break;
        case 2: handleDisplayApartments(rentalSystem); break;
        case 3: handleRentApartment(rentalSystem); break;
        case 4: handleReturnApartment(rentalSystem); break;
        case 5: handleRemoveApartment(rentalSystem); break;
        case 6: handleRateApartment(rentalSystem); break;
        case 7: handleCompareApartments(rentalSystem); break;
        case 0: std::cout << "������� � ������� ����...\n"; break;
        default: std::cout << "�������� ����. ����������, �������� �������������� �������.\n"; break;
        }
    } while (apartmentChoice != 0);
}

void handleUserSection(RentalSystem& rentalSystem) {
    int userChoice;
    do {
        displayUserMenu();
        std::cout << "�������� ��������: ";
        std::cin >> userChoice;
        std::cin.ignore(); // ������� ������

        switch (userChoice) {
        case 1: handleAddUser(rentalSystem); break;
        case 2: handleDisplayUsers(rentalSystem); break;
        case 0: std::cout << "������� � ������� ����...\n"; break;
        default: std::cout << "�������� ����. ����������, �������� �������������� �������.\n"; break;
        }
    } while (userChoice != 0);
}

void displayMainMenu() {
    std::cout << "\n������� ����:\n";
    std::cout << "1. ������ � ���������� � �������\n";
    std::cout << "2. ������ � ��������������\n";
    std::cout << "0. �����\n";
}

void displayApartmentMenu() {
    std::cout << "\n���� ������ � ���������� � �������:\n";
    std::cout << "1. �������� ��������\n";
    std::cout << "2. ���������� ��������� ��������\n";
    std::cout << "3. ���������� ��������\n";
    std::cout << "4. ������� ��������\n";
    std::cout << "5. ������� ��������\n";
    std::cout << "6. ������� ��������\n";
    std::cout << "7. �������� ��� �������� �� ���������\n"; // ����� �����
    std::cout << "0. ��������� � ������� ����\n";
}

void displayUserMenu() {
    std::cout << "\n���� ������ � ��������������:\n";
    std::cout << "1. �������� ������������\n";
    std::cout << "2. ���������� ���� �������������\n";
    std::cout << "0. ��������� � ������� ����\n";
}

void handleAddApartment(RentalSystem& system) {
    int id;
    std::string location;
    double price;
    bool available;

    std::cout << "������� ID ��������: ";
    std::cin >> id;
    std::cin.ignore(); // ������� ������
    std::cout << "������� �������������� ��������: ";
    std::getline(std::cin, location);
    std::cout << "������� ���� �� ������: ";
    std::cin >> price;
    std::cout << "�������� �������� (1 = ��, 0 = ���)? ";
    std::cin >> available;

    Apartment apartment(id, location, price, available);
    system.addApartmentToDB(apartment);
}

void handleDisplayApartments(const RentalSystem& system) {
    system.displayAvailableApartmentsFromDB();
}

void handleRentApartment(RentalSystem& system) {
    int apartmentId;
    std::string userName;
    std:: string userEmail;

    std::cout << "������� ID �������� ��� ������: ";
    std::cin >> apartmentId;
    std::cin.ignore(); // ������� ������

    std::cout << "������� ��� ������������: ";
    std::getline(std::cin, userName);
    std::cout << "������� email ������������: ";
    std::getline(std::cin, userEmail);

    // ������� ������������ � �������� � �������
    User user(userName, userEmail);
    system.rentApartmentFromDB(apartmentId, user); // ������ ��������� ������ � �����
}

void handleReturnApartment(RentalSystem& system) {
    int apartmentId;
    std::cout << "������� ID �������� ��� ��������: ";
    std::cin >> apartmentId;
    system.returnApartmentToDB(apartmentId);
}

void handleRemoveApartment(RentalSystem& system) {
    int apartmentId;
    std::cout << "������� ID �������� ��� ��������: ";
    std::cin >> apartmentId;
    system.removeApartmentFromDB(apartmentId);
}

void handleRateApartment(RentalSystem& system) {
    int apartmentId;
    double rating;
    std::cout << "������� ID �������� ��� ������: ";
    std::cin >> apartmentId;
    std::cout << "������� ������ (�� 1 �� 5): ";
    std::cin >> rating;

    system.rateApartmentInDB(apartmentId, rating);
}

void handleAddUser(RentalSystem& system) {
    std::string userName;
    std:: string userEmail;
    std::cout << "������� ��� ������������: ";
    std::cin.ignore(); // ������� ������
    std::getline(std::cin, userName);
    std::cout << "������� email ������������: ";
    std::getline(std::cin, userEmail);

    User user(userName, userEmail);
    system.addUserToDB(user);
}

void handleDisplayUsers(const RentalSystem& system) {
    system.displayUsersFromDB();
}

// ����� ������� ��� ��������� �������
void handleCompareApartments(const RentalSystem& system) {
    int apartmentId1;
    int apartmentId2;
    std::cout << "������� ID ������ �������� ��� ���������: ";
    std::cin >> apartmentId1;
    std::cout << "������� ID ������ �������� ��� ���������: ";
    std::cin >> apartmentId2;

    system.compareApartmentsFromDB(apartmentId1, apartmentId2);
}
