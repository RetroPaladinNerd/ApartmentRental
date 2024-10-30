#include <iostream>
#include <string>
#include "RentalSystem.h"
#include "User.h"

//управление меню
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
        std::cout << "Выберите раздел: ";
        std::cin >> choice;
        std::cin.ignore(); // очистка буфера

        switch (choice) {
        case 1: handleApartmentSection(rentalSystem); break;
        case 2: handleUserSection(rentalSystem); break;
        case 0: std::cout << "Выход из программы...\n"; break;
        default: std::cout << "Неверный ввод. Пожалуйста, выберите действительный вариант.\n"; break;
        }
    } while (choice != 0);

    return 0;
}

void handleApartmentSection(RentalSystem& rentalSystem) {
    int apartmentChoice;
    do {
        displayApartmentMenu();
        std::cout << "Выберите действие: ";
        std::cin >> apartmentChoice;
        std::cin.ignore(); // очистка буфера

        switch (apartmentChoice) {
        case 1: handleAddApartment(rentalSystem); break;
        case 2: handleDisplayApartments(rentalSystem); break;
        case 3: handleRentApartment(rentalSystem); break;
        case 4: handleReturnApartment(rentalSystem); break;
        case 5: handleRemoveApartment(rentalSystem); break;
        case 6: handleRateApartment(rentalSystem); break;
        case 7: handleCompareApartments(rentalSystem); break;
        case 0: std::cout << "Возврат в главное меню...\n"; break;
        default: std::cout << "Неверный ввод. Пожалуйста, выберите действительный вариант.\n"; break;
        }
    } while (apartmentChoice != 0);
}

void handleUserSection(RentalSystem& rentalSystem) {
    int userChoice;
    do {
        displayUserMenu();
        std::cout << "Выберите действие: ";
        std::cin >> userChoice;
        std::cin.ignore(); // очистка буфера

        switch (userChoice) {
        case 1: handleAddUser(rentalSystem); break;
        case 2: handleDisplayUsers(rentalSystem); break;
        case 0: std::cout << "Возврат в главное меню...\n"; break;
        default: std::cout << "Неверный ввод. Пожалуйста, выберите действительный вариант.\n"; break;
        }
    } while (userChoice != 0);
}

void displayMainMenu() {
    std::cout << "\nГлавное меню:\n";
    std::cout << "1. Работа с квартирами и арендой\n";
    std::cout << "2. Работа с пользователями\n";
    std::cout << "0. Выход\n";
}

void displayApartmentMenu() {
    std::cout << "\nМеню работы с квартирами и арендой:\n";
    std::cout << "1. Добавить квартиру\n";
    std::cout << "2. Отобразить доступные квартиры\n";
    std::cout << "3. Арендовать квартиру\n";
    std::cout << "4. Вернуть квартиру\n";
    std::cout << "5. Удалить квартиру\n";
    std::cout << "6. Оценить квартиру\n";
    std::cout << "7. Сравнить две квартиры по стоимости\n"; // Новый пункт
    std::cout << "0. Вернуться в главное меню\n";
}

void displayUserMenu() {
    std::cout << "\nМеню работы с пользователями:\n";
    std::cout << "1. Добавить пользователя\n";
    std::cout << "2. Отобразить всех пользователей\n";
    std::cout << "0. Вернуться в главное меню\n";
}

void handleAddApartment(RentalSystem& system) {
    int id;
    std::string location;
    double price;
    bool available;

    std::cout << "Введите ID квартиры: ";
    std::cin >> id;
    std::cin.ignore(); // очистка буфера
    std::cout << "Введите местоположение квартиры: ";
    std::getline(std::cin, location);
    std::cout << "Введите цену за аренду: ";
    std::cin >> price;
    std::cout << "Квартира доступна (1 = Да, 0 = Нет)? ";
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

    std::cout << "Введите ID квартиры для аренды: ";
    std::cin >> apartmentId;
    std::cin.ignore(); // очистка буфера

    std::cout << "Введите имя пользователя: ";
    std::getline(std::cin, userName);
    std::cout << "Введите email пользователя: ";
    std::getline(std::cin, userEmail);

    // Создаем пользователя и передаем в систему
    User user(userName, userEmail);
    system.rentApartmentFromDB(apartmentId, user); // Убрали параметры валюты и курса
}

void handleReturnApartment(RentalSystem& system) {
    int apartmentId;
    std::cout << "Введите ID квартиры для возврата: ";
    std::cin >> apartmentId;
    system.returnApartmentToDB(apartmentId);
}

void handleRemoveApartment(RentalSystem& system) {
    int apartmentId;
    std::cout << "Введите ID квартиры для удаления: ";
    std::cin >> apartmentId;
    system.removeApartmentFromDB(apartmentId);
}

void handleRateApartment(RentalSystem& system) {
    int apartmentId;
    double rating;
    std::cout << "Введите ID квартиры для оценки: ";
    std::cin >> apartmentId;
    std::cout << "Введите оценку (от 1 до 5): ";
    std::cin >> rating;

    system.rateApartmentInDB(apartmentId, rating);
}

void handleAddUser(RentalSystem& system) {
    std::string userName;
    std:: string userEmail;
    std::cout << "Введите имя пользователя: ";
    std::cin.ignore(); // очистка буфера
    std::getline(std::cin, userName);
    std::cout << "Введите email пользователя: ";
    std::getline(std::cin, userEmail);

    User user(userName, userEmail);
    system.addUserToDB(user);
}

void handleDisplayUsers(const RentalSystem& system) {
    system.displayUsersFromDB();
}

// Новая функция для сравнения квартир
void handleCompareApartments(const RentalSystem& system) {
    int apartmentId1;
    int apartmentId2;
    std::cout << "Введите ID первой квартиры для сравнения: ";
    std::cin >> apartmentId1;
    std::cout << "Введите ID второй квартиры для сравнения: ";
    std::cin >> apartmentId2;

    system.compareApartmentsFromDB(apartmentId1, apartmentId2);
}
