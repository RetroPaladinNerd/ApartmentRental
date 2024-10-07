#include <iostream>
#include "RentalSystem.h"
#include "User.h"

void displayMenu() {
    std::cout << "Меню системы аренды квартир:\n";
    std::cout << "1. Показать доступные квартиры\n";
    std::cout << "2. Арендовать квартиру\n";
    std::cout << "3. Вернуть квартиру\n";
    std::cout << "4. Удалить квартиру\n";
    std::cout << "5. Загрузить квартиры из файла\n";
    std::cout << "6. Сохранить квартиры в файл\n";
    std::cout << "7. Загрузить пользователей из файла\n";
    std::cout << "8. Сохранить пользователей в файл\n";
    std::cout << "9. Выход\n";
}

int main() {
    RentalSystem rentalSystem;
    std::system("chcp 1251");
    std::system("cls");
    // Загружаем данные из файлов, если они существуют
    rentalSystem.loadApartmentsFromFile("C:/Users/Admin/source/repos/ApartmentRental/ApartmentRental/apartments.txt");
    rentalSystem.loadUsersFromFile("C:/Users/Admin/source/repos/ApartmentRental/ApartmentRental/users.txt");

    while (true) {
        displayMenu();
        int choice;
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice; // Получаем выбор пользователя

        switch (choice) {
        case 1:
            rentalSystem.displayAvailableApartments();
            break;
        case 2: {
            std::string name, email;
            std::cout << "Введите ваше имя: ";
            std::cin.ignore(); // Игнорируем предыдущий ввод
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
            std::cout << "Неверный выбор, попробуйте снова.\n";
        }
        std::cout << std::endl; // Пустая строка для лучшего восприятия
    }

    return 0;
}
