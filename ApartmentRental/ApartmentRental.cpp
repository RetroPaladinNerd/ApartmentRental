#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm> // для std::ranges::sort
#include <iomanip>   // для std::setprecision
#include <format>    // для std::format
#include <ranges>    // для std::ranges

using namespace std;

// Перечисление для валют
enum class Currency {
    BYN, // Белорусский рубль
    USD, // Доллар США
    EUR  // Евро
};

// Использование enum для упрощения доступа к валютам
using enum Currency;

// Функция для получения строки названия валюты
string currencyToString(Currency currency) {
    switch (currency) {
    case BYN: return "BYN";
    case USD: return "USD";
    case EUR: return "EUR";
    default: return "";
    }
}

// Класс Apartment
class Apartment {
private:
    string address;
    int rooms;
    double rent;
    Currency currency;      // Поле для валюты
    bool isAvailable = true;  // Инициализация isAvailable внутри класса
    vector<double> ratings;   // Массив для хранения оценок

public:
    // Конструктор
    Apartment(string_view address, int rooms, double rent, Currency currency)
        : address(address), rooms(rooms), rent(rent), currency(currency) {}

    // Функция отображения информации о квартире
    void showInfo(int index) const {
        cout << std::format("Квартира #{}\n", index); // Индекс квартиры начинается с 1
        cout << std::format("Адрес: {}\n", address);
        cout << std::format("Комнат: {}\n", rooms);
        cout << std::format("Аренда: {} {}\n", rent, currencyToString(currency));
        cout << std::format("Доступность: {}\n", (isAvailable ? "Доступна" : "Занята"));
        cout << std::format("Рейтинг: {}\n", (ratings.empty() ? "Нет рейтинга" : to_string(getAverageRating())));
    }

    // Получение средней оценки
    double getAverageRating() const {
        if (ratings.empty()) return 0.0;
        double sum = 0;
        for (double rating : ratings) {
            sum += rating;
        }
        return round((sum / ratings.size()) * 100) / 100; // Округление до сотых
    }

    // Добавление оценки
    void addRating(double rating) {
        ratings.push_back(rating);
        cout << std::format("Квартира оценена на {:.2f} звёзд.\n", rating); // Форматирование до двух знаков после запятой
    }

    // Получатели и установщики для работы с данными
    string getAddress() const { return address; }
    void setAddress(string_view newAddress) { address = newAddress; }

    int getRooms() const { return rooms; }
    void setRooms(int newRooms) { rooms = newRooms; }

    double getRent() const { return rent; }
    void setRent(double newRent) { rent = newRent; }

    Currency getCurrency() const { return currency; }
    void setCurrency(Currency newCurrency) { currency = newCurrency; }

    bool getAvailability() const { return isAvailable; }

    // Функция аренды квартиры
    void rentApartment() {
        if (isAvailable) {
            isAvailable = false;
            cout << std::format("Квартира на {} арендована.\n", address);
        }
        else {
            cout << std::format("Квартира на {} уже арендована.\n", address);
        }
    }

    // Функция освобождения квартиры
    void freeApartment() {
        isAvailable = true;
        cout << std::format("Квартира на {} снова доступна для аренды.\n", address);
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

        // Подменю для выбора валюты
        int currencyChoice;
        cout << "Выберите валюту:\n";
        cout << "1. BYN\n";
        cout << "2. USD\n";
        cout << "3. EUR\n";
        cout << "Введите ваш выбор: ";
        cin >> currencyChoice;

        Currency currency;
        switch (currencyChoice) {
        case 1:
            currency = BYN;
            break;
        case 2:
            currency = USD;
            break;
        case 3:
            currency = EUR;
            break;
        default:
            cout << "Неверный выбор валюты. Установлена валюта по умолчанию BYN.\n";
            currency = BYN;
            break;
        }

        apartments.emplace_back(address, rooms, rent, currency);
        cout << "Квартира добавлена успешно.\n";
    }

    // Показ всех квартир
    void showAllApartments() const {
        if (apartments.empty()) {
            cout << "Нет доступных квартир.\n";
            return;
        }
        for (size_t i = 0; i < apartments.size(); ++i) {
            apartments[i].showInfo(i + 1); // Индекс квартиры начинается с 1
            cout << "------------------------" << endl;
        }
    }

    // Поиск квартиры по диапазону цен
    void searchApartmentByPrice(double minPrice, double maxPrice) const {
        bool found = false;
        for (size_t i = 0; i < apartments.size(); ++i) {
            if (apartments[i].getRent() >= minPrice && apartments[i].getRent() <= maxPrice) {
                apartments[i].showInfo(i + 1); // Индекс квартиры начинается с 1
                cout << "------------------------" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "Квартиры в данном диапазоне цен не найдены.\n";
        }
    }

    // Сортировка квартир по стоимости с использованием std::ranges::sort
    void sortApartmentsByPrice() {
        auto begin = apartments.begin(); // Определение начала диапазона
        auto end = apartments.end();     // Определение конца диапазона

        std::ranges::sort(begin, end, [](const Apartment& a, const Apartment& b) {
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

        if (index >= 1 && index <= apartments.size()) { // Индексы теперь от 1 до size
            cout << "Введите оценку (от 1 до 5): ";  // Рейтинг от 1 до 5
            cin >> rating;
            if (rating >= 1.0 && rating <= 5.0) {     // Устанавливаем диапазон 1-5
                apartments[index - 1].addRating(rating); // Индекс для массива
            }
            else {
                cout << "Оценка должна быть от 1 до 5.\n";
            }
        }
        else {
            cout << "Неверный индекс квартиры.\n";
        }
    }

    // Аренда квартиры
    void rentApartment() {
        int index;
        cout << "Введите индекс квартиры для аренды: ";
        cin >> index;

        if (index >= 1 && index <= apartments.size()) { // Индексы теперь от 1 до size
            apartments[index - 1].rentApartment(); // Индекс для массива
        }
        else {
            cout << "Неверный индекс квартиры.\n";
        }
    }

    // Освобождение квартиры
    void freeApartment() {
        int index;
        cout << "Введите индекс квартиры для освобождения: ";
        cin >> index;

        if (index >= 1 && index <= apartments.size()) { // Индексы теперь от 1 до size
            apartments[index - 1].freeApartment(); // Индекс для массива
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
    cout << "6. Арендовать квартиру\n";
    cout << "7. Освободить квартиру\n"; // Новый пункт в меню
    cout << "0. Выйти\n\n";
    cout << "Введите ваш выбор: ";
}

int main() {
    system("chcp 1251");
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
            cout << "Введите минимальную цену: ";
            cin >> minPrice;
            cout << "Введите максимальную цену: ";
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
        case 6:
            system.rentApartment();
            break;
        case 7:
            system.freeApartment();
            break;
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
