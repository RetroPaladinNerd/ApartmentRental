#include <iostream>
#include "RentalSystem.h"
#include "Landlord.h"

void displayMainMenu() {
    std::cout << "\n�������� ����� ������:\n";
    std::cout << "1. ����� ������������\n";
    std::cout << "2. ����� ����������\n";
    std::cout << "0. �����\n";
    std::cout << "������� ��� �����: ";
}

int main() {
    system("chcp 1251");
    system("cls");

    std::string name;
    std::cout << "������� ���� ���: ";
    std::cin >> name;

    Landlord landlord(name);  // ���� ������������ ����� ���� � �������������, � �����������
    int choice;

    do {
        displayMainMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            landlord.landlordMenu();
            break;
        case 2:
            landlord.tenantMenu();
            break;
        case 0:
            std::cout << "����� �� ���������.\n";
            break;
        default:
            std::cout << "�������� �����. ����������, ���������� �����.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
