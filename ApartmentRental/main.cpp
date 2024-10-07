#include <iostream>
#include "RentalSystem.h"
#include "User.h"

void displayMenu() {
    std::cout << "���� ������� ������ �������:\n";
    std::cout << "1. �������� ��������� ��������\n";
    std::cout << "2. ���������� ��������\n";
    std::cout << "3. ������� ��������\n";
    std::cout << "4. ������� ��������\n";
    std::cout << "5. ��������� �������� �� �����\n";
    std::cout << "6. ��������� �������� � ����\n";
    std::cout << "7. ��������� ������������� �� �����\n";
    std::cout << "8. ��������� ������������� � ����\n";
    std::cout << "9. �����\n";
}

int main() {
    RentalSystem rentalSystem;
    std::system("chcp 1251");
    std::system("cls");
    // ��������� ������ �� ������, ���� ��� ����������
    rentalSystem.loadApartmentsFromFile("C:/Users/Admin/source/repos/ApartmentRental/ApartmentRental/apartments.txt");
    rentalSystem.loadUsersFromFile("C:/Users/Admin/source/repos/ApartmentRental/ApartmentRental/users.txt");

    while (true) {
        displayMenu();
        int choice;
        std::cout << "������� ��� �����: ";
        std::cin >> choice; // �������� ����� ������������

        switch (choice) {
        case 1:
            rentalSystem.displayAvailableApartments();
            break;
        case 2: {
            std::string name, email;
            std::cout << "������� ���� ���: ";
            std::cin.ignore(); // ���������� ���������� ����
            std::getline(std::cin, name);
            std::cout << "������� ��� email: ";
            std::getline(std::cin, email);

            User user(name, email);
            int apartmentId;
            std::cout << "������� ID �������� ��� ������: ";
            std::cin >> apartmentId;
            rentalSystem.rentApartment(apartmentId, user);
            break;
        }
        case 3: {
            int apartmentId;
            std::cout << "������� ID �������� ��� ��������: ";
            std::cin >> apartmentId;
            rentalSystem.returnApartment(apartmentId);
            break;
        }
        case 4: {
            int apartmentId;
            std::cout << "������� ID �������� ��� ��������: ";
            std::cin >> apartmentId;
            rentalSystem.removeApartment(apartmentId);
            break;
        }
        case 5:
            rentalSystem.loadApartmentsFromFile("data/apartments.txt");
            break;
        case 6:
            rentalSystem.saveApartmentsToFile("data/apartments.txt");
            break;
        case 7:
            rentalSystem.loadUsersFromFile("data/users.txt");
            break;
        case 8:
            rentalSystem.saveUsersToFile("data/users.txt");
            break;
        case 9:
            return 0;
        default:
            std::cout << "�������� �����, ���������� �����.\n";
        }
        std::cout << std::endl; // ������ ������ ��� ������� ����������
    }

    return 0;
}
