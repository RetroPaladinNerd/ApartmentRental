#include <iostream>
#include "RentalSystem.h"
#include "User.h"

// ���� ��� ������ � ����������
void apartmentMenu(RentalSystem& rentalSystem) {
    int choice;
    while (true) {
        std::cout << "\n���� ������ � ����������:\n";
        std::cout << "1. �������� ��������� ��������\n";
        std::cout << "2. ���������� ��������\n";
        std::cout << "3. ������� ��������\n";
        std::cout << "4. ������� ��������\n";
        std::cout << "5. ����� � ������� ����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            rentalSystem.displayAvailableApartments();
            break;
        case 2: {
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
        std::cout << "3. ����� � ������� ����\n";
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
            return; // ������������ � ������� ����
        default:
            std::cout << "�������� �����, ���������� �����.\n";
        }
    }
}

// ������� ����
void mainMenu() {
    RentalSystem rentalSystem;
    std::system("chcp 1251");
    std::system("cls");
    int choice;
    while (true) {
        std::cout << "\n������� ����:\n";
        std::cout << "1. ���� ������ � ����������\n";
        std::cout << "2. ���� ������ � ��������������\n";
        std::cout << "3. �����\n";
        std::cout << "������� ��� �����: ";
        std::cin >> choice;

        switch (choice) {
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
