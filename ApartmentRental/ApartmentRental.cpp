#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm> // для std::sort

using namespace std;

// Класс Apartment
class Apartment {
private:
    string address;
    int rooms;
    double rent;
    bool isAvailable = true;  // Инициализация isAvailable внутри класса
    vector<double> ratings;   // Массив для хранения оценок

public:
    // Конструктор
    Apartment(string_view address, int rooms, double rent)
        : address(address), rooms(rooms), rent(rent) {}

    // Функция отображения информации о квартире
    void showInfo() const {
        cout << "Адрес: " << address << endl;
        cout << "Комнат: " << rooms << endl;
        cout << "Аренда: " << rent << endl;
        cout << "Доступность: " << (isAvailable ? "Доступна" : "Занята") << endl;
        cout << "Рейтинг: " << (ratings.empty() ? "Нет рейтинга" : to_string(getAverageRating())) << endl;
    }

    // Получение средней оценки
    double getAverageRating() const {
        if (ratings.empty()) return 0.0;
        double sum = 0;
        for (double rating : ratings) {
            sum += rating;
        }
        return sum / ratings.size();
    }

    // Добавление оценки
    void addRating(double rating) {
        ratings.push_back(rating);
        cout << "Квартира оценена на " << rating << " звёзд.\n";
    }

    // Получатели и установщики для работы с данными
    string getAddress() const { return address; }
    void setAddress(string_view newAddress) { address = newAddress; }

    int getRooms() const { return rooms; }
    void setRooms(int newRooms) { rooms = newRooms; }

    double getRent() const { return rent; }
    void setRent(double newRent) { rent = newRent; }

    bool getAvailability() const { return isAvailable; }

    // Функция аренды квартиры
    void rentApartment() {
        if (isAvailable) {
            isAvailable = false;
            cout << "Квартира на " << address << " арендована.\n";
        }
        else {
            cout << "Квартира на " << address << " уже арендована.\n";
        }
    }

    // Функция освобождения квартиры
    void freeApartment() {
        isAvailable = true;
        cout << "Квартира на " << address << " снова доступна для аренды.\n";
    }
};

// Класс RentalSystem
class RentalSystem {
private:
    vector<Apartment> apartments;

public:
    // Добавление квартиры
    void addApartment() {
        string address;
        cout << "Введите адрес квартиры: ";
        cin.ignore();
        getline(cin, address);

        int rooms;
        cout << "Введите количество комнат: ";
        cin >> rooms;

        double rent;
        cout << "Введите стоимость аренды: ";
        cin >> rent;

        apartments.emplace_back(address, rooms, rent);
        cout << "Квартира добавлена успешно.\n";
    }

    // Показ всех квартир
    void showAllApartments() const {
        if (apartments.empty()) {
            cout << "Нет доступных квартир.\n";
            return;
        }
        for (const auto& apartment : apartments) {
            apartment.showInfo();
            cout << "------------------------" << endl;
        }
    }

    // Поиск квартиры по диапазону цен
    void searchApartmentByPrice(double minPrice, double maxPrice) const {
        bool found = false;
        for (const auto& apartment : apartments) {
            if (apartment.getRent() >= minPrice && apartment.getRent() <= maxPrice) {
                apartment.showInfo();
                cout << "------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Квартиры в данном диапазоне цен не найдены.\n";
        }
    }

    // Сортировка квартир по стоимости
    void sortApartmentsByPrice() {
        sort(apartments.begin(), apartments.end(), [](const Apartment& a, const Apartment& b) {
            return a.getRent() < b.getRent();
            });
        cout << "Квартиры успешно отсортированы по стоимости аренды.\n";
    }

    // Добавление рейтинга квартире
    void rateApartment() {
        int index;
        double rating;
        cout << "Введите индекс квартиры для оценки: ";
        cin >> index;

        if (index >= 0 && index < apartments.size()) {
            cout << "Введите оценку (от 1 до 5): ";
            cin >> rating;
            if (rating >= 1.0 && rating <= 5.0) {
                apartments[index].addRating(rating);
            }
            else {
                cout << "Оценка должна быть от 1 до 5.\n";
            }
        }
        else {
            cout << "Неверный индекс квартиры.\n";
        }
    }
};

// Функция для отображения меню
void displayMenu() {
    cout << "\nМеню системы аренды квартир:\n";
    cout << "1. Добавить квартиру\n";
    cout << "2. Показать все квартиры\n";
    cout << "3. Поиск квартиры по цене\n";
    cout << "4. Сортировка квартир по стоимости\n";
    cout << "5. Оценить квартиру\n";
    cout << "0. Выйти\n";
    cout << "Введите ваш выбор: ";
}

int main() {
    std::system("chcp 1251");
    system("cls");
    RentalSystem system;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            system.addApartment();
            break;
        case 2:
            system.showAllApartments();
            break;
        case 3: {
            double minPrice, maxPrice;
            cout << "Введите минимальную стоимость: ";
            cin >> minPrice;
            cout << "Введите максимальную стоимость: ";
            cin >> maxPrice;
            system.searchApartmentByPrice(minPrice, maxPrice);
            break;
        }
        case 4:
            system.sortApartmentsByPrice();
            break;
        case 5:
            system.rateApartment();
            break;
        case 0:
            cout << "Выход из программы...\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    } while (choice != 0);

    return 0;
}
