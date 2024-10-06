#include <iostream>
#include "RentalSystem.h"

void displayMenu() {
    std::cout << "\nМеню системы аренды квартир:\n";
    std::cout << "1. Добавить квартиру\n";
    std::cout << "2. Показать все квартиры\n";
    std::cout << "3. Поиск квартиры по цене\n";
    std::cout << "4. Сортировка квартир по стоимости\n";
    std::cout << "5. Оценить квартиру\n";
    std::cout << "6. Арендовать квартиру\n";
    std::cout << "7. Освободить квартиру\n";
    std::cout << "8. Добавить арендодателя\n";
    std::cout << "9. Показать арендодателей\n";
    std::cout << "10. Добавить квартиру арендодателю для сдачи\n";
    std::cout << "11. Арендодатель арендует квартиру\n";
    std::cout << "12. Арендодатель освобождает квартиру\n";
    std::cout << "0. Выйти\n\n";
    std::cout << "Введите ваш выбор: ";
}

int main() {
    system("chcp 1251");
    system("cls");

    RentalSystem system;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
        case 1:
            system.addApartment();
            break;
        case 2:
            system.showAllApartments();
            break;
        case 8: {
            std::string name;
            std::cout << "Введите имя арендодателя: ";
            std::cin >> name;
            system.addLandlord(name);
            break;
        }
        case 9:
            system.showLandlords();
            break;
        case 10: {
            int landlordIndex, apartmentIndex;
            system.showLandlords();
            std::cout << "Введите индекс арендодателя: ";
            std::cin >> landlordIndex;
            system.showAllApartments();
            std::cout << "Введите индекс квартиры: ";
            std::cin >> apartmentIndex;
            system.landlordAddApartmentToRent(landlordIndex, apartmentIndex);
            break;
        }
        case 11: {
            int landlordIndex, apartmentIndex;
            system.showLandlords();
            std::cout << "Введите индекс арендодателя: ";
            std::cin >> landlordIndex;
            system.showAllApartments();
            std::cout << "Введите индекс квартиры: ";
            std::cin >> apartmentIndex;
            system.landlordRentApartment(landlordIndex, apartmentIndex);
            break;
        }
        case 12: {
            int landlordIndex;
            system.showLandlords();
            std::cout << "Введите индекс арендодателя: ";
            std::cin >> landlordIndex;
            system.landlordFreeRentedApartment(landlordIndex);
            break;
        }
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
