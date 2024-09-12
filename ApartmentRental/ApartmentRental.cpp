#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Класс Квартира
class Apartment {
private:
    string address;
    int rooms;
    double rent;
    bool isAvailable;

public:
    // Конструктор
    Apartment(string address, int rooms, double rent)
        : address(address), rooms(rooms), rent(rent), isAvailable(true) {}

    // Функция получения информации о квартире
    void showInfo() const {
        cout << "Адрес: " << address << endl;
        cout << "Комнат: " << rooms << endl;
        cout << "Аренда: " << rent << endl;
        cout << "Доступность: " << (isAvailable ? "Доступна" : "Занята") << endl;
    }

    // Получение статуса доступности
    bool getAvailability() const {
        return isAvailable;
    }

    // Изменение статуса квартиры на занятую
    void rentApartment() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Квартира по адресу " << address << " арендована." << endl;
        }
        else {
            cout << "Квартира по адресу " << address << " уже занята." << endl;
        }
    }

    // Освобождение квартиры
    void freeApartment() {
        isAvailable = true;
        cout << "Квартира по адресу " << address << " снова доступна для аренды." << endl;
    }
};

// Класс Арендатор
class Tenant {
private:
    string name;
    string phoneNumber;

public:
    // Конструктор
    Tenant(string name, string phoneNumber) : name(name), phoneNumber(phoneNumber) {}

    // Функция получения информации об арендаторе
    void showInfo() const {
        cout << "Имя арендатора: " << name << endl;
        cout << "Телефон: " << phoneNumber << endl;
    }
};

// Класс Система аренды
class RentalSystem {
private:
    vector<Apartment> apartments;
    vector<Tenant> tenants;

public:
    // Добавление квартиры в систему
    void addApartment(const Apartment& apartment) {
        apartments.push_back(apartment);
        cout << "Квартира добавлена в систему." << endl;
    }

    // Добавление арендатора в систему
    void addTenant(const Tenant& tenant) {
        tenants.push_back(tenant);
        cout << "Арендатор добавлен в систему." << endl;
    }

    // Показать все квартиры
    void showAllApartments() const {
        for (const auto& apartment : apartments) {
            apartment.showInfo();
            cout << "------------------------" << endl;
        }
    }

    // Аренда квартиры
    void rentApartment(int index) {
        if (index >= 0 && index < apartments.size()) {
            apartments[index].rentApartment();
        }
        else {
            cout << "Неправильный индекс квартиры." << endl;
        }
    }

    // Освобождение квартиры
    void freeApartment(int index) {
        if (index >= 0 && index < apartments.size()) {
            apartments[index].freeApartment();
        }
        else {
            cout << "Неправильный индекс квартиры." << endl;
        }
    }
};

int main() {
    RentalSystem system;

    // Добавление нескольких квартир
    system.addApartment(Apartment("ул. Пушкина, 10", 3, 30000));
    system.addApartment(Apartment("ул. Лермонтова, 25", 2, 20000));
    system.addApartment(Apartment("ул. Гоголя, 5", 1, 15000));

    // Добавление арендатора
    system.addTenant(Tenant("Иван Иванов", "+7-900-123-45-67"));

    // Показ всех квартир
    cout << "Все квартиры в системе:\n";
    system.showAllApartments();

    // Аренда квартиры
    system.rentApartment(1);

    // Попытка арендовать ту же квартиру снова
    system.rentApartment(1);

    // Освобождение квартиры
    system.freeApartment(1);

    // Повторная аренда квартиры
    system.rentApartment(1);

    return 0;
}
