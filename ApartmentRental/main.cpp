#include <iostream>
#include "RentalSystem.h"
#include "User.h"

// Меню для работы с квартирами
void apartmentMenu(RentalSystem& rentalSystem) {
    int choice;
    while (true) {
        std::cout << "\nМеню работы с квартирами:\n";
        std::cout << "1. Добавить квартиру\n";
        std::cout << "2. Показать доступные квартиры\n";
        std::cout << "3. Арендовать квартиру\n";
        std::cout << "4. Вернуть квартиру\n";
        std::cout << "5. Удалить квартиру\n";
        std::cout << "6. Установить рейтинг квартире\n";
        std::cout << "7. Расчёт стоимости аренды\n"; //
        std::cout << "8. Сравнение двух квартир\n";
        std::cout << "9. Загрузить данные о квартирах из файла\n";
        std::cout << "10. Сохранить данные о квартирах в файл\n";
        std::cout << "11. Назад в главное меню\n";
        std::cout << "Введите ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
        case 1: { // Новый блок для добавления квартиры
            int id;
            std::string location;
            double price;
            bool available;
            char availabilityInput;

            std::cout << "Введите ID новой квартиры: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Введите местоположение: ";
            std::getline(std::cin, location);
            std::cout << "Введите цену: ";
            std::cin >> price;
            std::cout << "Квартира доступна? (y/n): ";
            std::cin >> availabilityInput;
            available = (availabilityInput == 'y' || availabilityInput == 'Y');

            Apartment newApartment(id, location, price, available);
            rentalSystem.addApartment(newApartment); // Добавляем квартиру в систему
            std::cout << "Квартира добавлена успешно.\n";
            break;
        }
        case 2:
            rentalSystem.displayAvailableApartments();
            break;
        case 3: {
            // Выбор валюты для аренды
            std::string currency;
            std::cout << "Выберите валюту (USD, EUR, BYN): ";
            std::cin >> currency;

            double rate = rentalSystem.getCurrencyRate(currency); // Получаем курс валюты

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

            rentalSystem.rentApartment(apartmentId, user, rate, currency); // Передаем валюту и курс
            break;
        }
        case 4: {
            int apartmentId;
            std::cout << "Введите ID квартиры для возврата: ";
            std::cin >> apartmentId;
            rentalSystem.returnApartment(apartmentId);
            break;
        }
        case 5: {
            int apartmentId;
            std::cout << "Введите ID квартиры для удаления: ";
            std::cin >> apartmentId;
            rentalSystem.removeApartment(apartmentId);
            break;
        }
        case 6: {
            int apartmentId;
            double rating;
            std::cout << "Введите ID квартиры для оценки: ";
            std::cin >> apartmentId;
            std::cout << "Введите рейтинг (0-5): ";
            std::cin >> rating;
            rentalSystem.rateApartment(apartmentId, rating);
            break;
        }
        case 7:
            // Расчёт стоимости аренды
            int apartmentId;
            int rentalDays;
            std::cout << "Введите ID квартиры для расчёта стоимости аренды: ";
            std::cin >> apartmentId;
            std::cout << "Введите количество дней аренды: ";
            std::cin >> rentalDays;
            rentalSystem.calculateRentalCost(apartmentId, rentalDays);
            break;
        case 8:
            // Сравнение квартир
            int apartmentId1, apartmentId2;
            std::cout << "Введите ID первой квартиры для сравнения: ";
            std::cin >> apartmentId1;
            std::cout << "Введите ID второй квартиры для сравнения: ";
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
        std::cout << "3. Сохранить данные о пользователях в файл\n";
        std::cout << "4. Загрузить данные о пользователях из файла\n";
        std::cout << "5. Назад в главное меню\n";
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
            rentalSystem.saveUsersToFile("users.txt");
            break;
        case 4:
            rentalSystem.loadUsersFromFile("users.txt");
            break;
        case 5:
            return; // Возвращаемся в главное меню
        default:
            std::cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
}

// Главное меню
void mainMenu() 
{
    RentalSystem rentalSystem;
    std::system("chcp 1251");
    std::system("cls");
    int choice;
    while (true) 
    {
        std::cout << "\nГлавное меню:\n";
        std::cout << "1. Меню работы с квартирами\n";
        std::cout << "2. Меню работы с пользователями\n";
        std::cout << "3. Выход\n";
        std::cout << "Введите ваш выбор: ";
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
