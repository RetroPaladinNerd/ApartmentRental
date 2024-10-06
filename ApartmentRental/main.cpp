#include <iostream>
#include "RentalSystem.h"
#include "Landlord.h"

void displayMainMenu() {
    std::cout << "\nВыберите режим работы:\n";
    std::cout << "1. Режим арендодателя\n";
    std::cout << "2. Режим арендатора\n";
    std::cout << "0. Выйти\n";
    std::cout << "Введите ваш выбор: ";
}

int main() {
    system("chcp 1251");
    system("cls");

    std::string name;
    std::cout << "Введите ваше имя: ";
    std::cin >> name;

    Landlord landlord(name);  // Один пользователь может быть и арендодателем, и арендатором
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
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
