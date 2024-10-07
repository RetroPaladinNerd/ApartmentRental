#include <iostream>
#include "RentalSystem.h"
#include "User.h"

// Меню для работы с квартирами
void apartmentMenu(RentalSystem& rentalSystem) {
    int choice;
    while (true) {
        std::cout << "\nМеню работы с квартирами:\n";
        std::cout << "1. Показать доступные квартиры\n";
        std::cout << "2. Арендовать квартиру\n";
        std::cout << "3. Вернуть квартиру\n";
        std::cout << "4. Удалить квартиру\n";
        std::cout << "5. Назад в главное меню\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            rentalSystem.displayAvailableApartments();
            break;
        case 2: {
            std::string name, email;
            std::cout << "Введите ваше имя: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите ваш email: ";
            std::getline(std::cin, email);

            User user(name, email);
            int apartmentId;
            std::cout << "Введите ID квартиры для аренды: ";
            std::cin >> apartmentId;
            rentalSystem.rentApartment(apartmentId, user);
            break;
        }
        case 3: {
            int apartmentId;
            std::cout << "Введите ID квартиры для возврата: ";
            std::cin >> apartmentId;
            rentalSystem.returnApartment(apartmentId);
            break;
        }
        case 4: {
            int apartmentId;
            std::cout << "Введите ID квартиры для удаления: ";
            std::cin >> apartmentId;
            rentalSystem.removeApartment(apartmentId);
            break;
        }
        case 5:
            return; // Возвращаемся в главное меню
        default:
            std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
}

// Меню для работы с пользователями
void userMenu(RentalSystem& rentalSystem) {
    int choice;
    while (true) {
        std::cout << "\nМеню работы с пользователями:\n";
        std::cout << "1. Добавить пользователя\n";
        std::cout << "2. Показать всех пользователей\n";
        std::cout << "3. Назад в главное меню\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, email;
            std::cout << "Введите имя пользователя: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            std::cout << "Введите email пользователя: ";
            std::getline(std::cin, email);

            User user(name, email);
            rentalSystem.addUser(user);
            std::cout << "Пользователь добавлен.\n";
            break;
        }
        case 2:
            rentalSystem.displayUsers();
            break;
        case 3:
            return; // Возвращаемся в главное меню
        default:
            std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
}

// Главное меню
void mainMenu() {
    RentalSystem rentalSystem;
    std::system("chcp 1251");
    std::system("cls");
    int choice;
    while (true) {
        std::cout << "\nГлавное меню:\n";
        std::cout << "1. Меню работы с квартирами\n";
        std::cout << "2. Меню работы с пользователями\n";
        std::cout << "3. Выход\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            apartmentMenu(rentalSystem);
            break;
        case 2:
            userMenu(rentalSystem);
            break;
        case 3:
            std::cout << "Выход из программы...\n";
            return;
        default:
            std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
