#include <iostream>
#include "RentalSystem.h"
#include "User.h"

// ���� ��� ������ � ����������
void apartmentMenu(RentalSystem& rentalSystem) {
    int choice;
    while (true) {
        std::cout << "\n���� ������ � ����������:\n";
        std::cout << "1. �������� ��������\n";
        std::cout << "2. �������� ��������� ��������\n";
        std::cout << "3. ���������� ��������\n";
        std::cout << "4. ������� ��������\n";
        std::cout << "5. ������� ��������\n";
        std::cout << "6. ���������� ������� ��������\n";
        std::cout << "7. ������ ��������� ������\n"; //
        std::cout << "8. ��������� ���� �������\n";
        std::cout << "9. ��������� ������ � ��������� �� �����\n";
        std::cout << "10. ��������� ������ � ��������� � ����\n";
        std::cout << "11. ����� � ������� ����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: { // ����� ���� ��� ���������� ��������
            int id;
            std::string location;
            double price;
            bool available;
            char availabilityInput;

            std::cout << "������� ID ����� ��������: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "������� ��������������: ";
            std::getline(std::cin, location);
            std::cout << "������� ����: ";
            std::cin >> price;
            std::cout << "�������� ��������? (y/n): ";
            std::cin >> availabilityInput;
            available = (availabilityInput == 'y' || availabilityInput == 'Y');

            Apartment newApartment(id, location, price, available);
            rentalSystem.addApartment(newApartment); // ��������� �������� � �������
            std::cout << "�������� ��������� �������.\n";
            break;
        }
        case 2:
            rentalSystem.displayAvailableApartments();
            break;
        case 3: {
            // ����� ������ ��� ������
            std::string currency;
            std::cout << "�������� ������ (USD, EUR, BYN): ";
            std::cin >> currency;

            double rate = rentalSystem.getCurrencyRate(currency); // �������� ���� ������

            std::string name, email;
            std::cout << "������� ���� ���: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "������� ��� email: ";
            std::getline(std::cin, email);

            User user(name, email);
            int apartmentId;
            std::cout << "������� ID �������� ��� ������: ";
            std::cin >> apartmentId;

            rentalSystem.rentApartment(apartmentId, user, rate, currency); // �������� ������ � ����
            break;
        }
        case 4: {
            int apartmentId;
            std::cout << "������� ID �������� ��� ��������: ";
            std::cin >> apartmentId;
            rentalSystem.returnApartment(apartmentId);
            break;
        }
        case 5: {
            int apartmentId;
            std::cout << "������� ID �������� ��� ��������: ";
            std::cin >> apartmentId;
            rentalSystem.removeApartment(apartmentId);
            break;
        }
        case 6: {
            int apartmentId;
            double rating;
            std::cout << "������� ID �������� ��� ������: ";
            std::cin >> apartmentId;
            std::cout << "������� ������� (0-5): ";
            std::cin >> rating;
            rentalSystem.rateApartment(apartmentId, rating);
            break;
        }
        case 7:
            // ������ ��������� ������
            int apartmentId;
            int rentalDays;
            std::cout << "������� ID �������� ��� ������� ��������� ������: ";
            std::cin >> apartmentId;
            std::cout << "������� ���������� ���� ������: ";
            std::cin >> rentalDays;
            rentalSystem.calculateRentalCost(apartmentId, rentalDays);
            break;
        case 8:
            // ��������� �������
            int apartmentId1, apartmentId2;
            std::cout << "������� ID ������ �������� ��� ���������: ";
            std::cin >> apartmentId1;
            std::cout << "������� ID ������ �������� ��� ���������: ";
            std::cin >> apartmentId2;
            rentalSystem.compareApartments(apartmentId1, apartmentId2);
            break;
        case 9:
            rentalSystem.loadApartmentsFromFile("apartments.txt");
            break;
        case 10:
            rentalSystem.saveApartmentsToFile("apartments.txt");
            break;
        case 11:
            return; // ������������ � ������� ����
        default:
            std::cout << "�������� �����, ���������� �����.\n";
        }
    }
}

// ���� ��� ������ � ��������������
void userMenu(RentalSystem& rentalSystem) {
    int choice;
    while (true) {
        std::cout << "\n���� ������ � ��������������:\n";
        std::cout << "1. �������� ������������\n";
        std::cout << "2. �������� ���� �������������\n";
        std::cout << "3. ��������� ������ � ������������� � ����\n";
        std::cout << "4. ��������� ������ � ������������� �� �����\n";
        std::cout << "5. ����� � ������� ����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, email;
            std::cout << "������� ��� ������������: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "������� email ������������: ";
            std::getline(std::cin, email);

            User user(name, email);
            rentalSystem.addUser(user);
            std::cout << "������������ ��������.\n";
            break;
        }
        case 2:
            rentalSystem.displayUsers();
            break;
        case 3:
            rentalSystem.saveUsersToFile("users.txt");
            break;
        case 4:
            rentalSystem.loadUsersFromFile("users.txt");
            break;
        case 5:
            return; // ������������ � ������� ����
        default:
            std::cout << "�������� �����, ���������� �����.\n";
        }
    }
}

// ������� ����
void mainMenu() 
{
    RentalSystem rentalSystem;
    std::system("chcp 1251");
    std::system("cls");
    int choice;
    while (true) 
    {
        std::cout << "\n������� ����:\n";
        std::cout << "1. ���� ������ � ����������\n";
        std::cout << "2. ���� ������ � ��������������\n";
        std::cout << "3. �����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) 
        {
        case 1:
            apartmentMenu(rentalSystem);
            break;
        case 2:
            userMenu(rentalSystem);
            break;
        case 3:
            std::cout << "����� �� ���������...\n";
            return;
        default:
            std::cout << "�������� �����, ���������� �����.\n";

        }
    }
}

int main() {
    mainMenu();
    return 0;
}
