#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm> // для std::sort
#include <iomanip>   // для std::setprecision
#include <format>    // для std::format (C++20)

using namespace std;

// Перечисление для валют
enum class Currency {
    BYN, // Белорусский рубль
    USD, // Доллар США
    EUR  // Евро
};

// Функция для получения строки названия валюты
string currencyToString(Currency currency) {
    switch (currency) {
    case Currency::BYN:
        return "BYN";
    case Currency::USD:
        return "USD";
    case Currency::EUR:
        return "EUR";
    default:
        return "";
    }
}

// Класс Apartment
class Apartment {
private:
    string address;
    int rooms;
    double rent;
    Currency currency;      // Поле для валюты
    bool isAvailable;       // Инициализация isAvailable будет в конструкторе
    vector<double> ratings; // Массив для хранения оценок

public:
    // Конструктор
    Apartment(string_view address, int rooms, double rent, Currency currency)
        : address(address), rooms(rooms), rent(rent), currency(currency), isAvailable(true) {}

    // Функция отображения информации о квартире
    void showInfo(int index) const {
        std::cout << std::format("Квартира #{}\n", index); // Индекс квартиры начинается с 1
        std::cout << std::format("Адрес: {}\n", address);
        std::cout << std::format("Комнат: {}\n", rooms);
        std::cout << std::format("Аренда: {} {}\n", rent, currencyToString(currency));
        std::cout << std::format("Доступность: {}\n", (isAvailable ? "Доступна" : "Занята"));
        std::cout << std::format("Рейтинг: {}\n", (ratings.empty() ? "Нет рейтинга" : to_string(getAverageRating())));
    }

    // Получение средней оценки
    double getAverageRating() const {
        if (ratings.empty()) {
            return 0.0;
        }

        double sum = 0;

        for (double rating : ratings) {
            sum += rating;
        }

        return round((sum / ratings.size()) * 100) / 100; // Округление до сотых
    }

    // Добавление оценки
    void addRating(double rating) {
        ratings.push_back(rating);
        std::cout << std::format("Квартира оценена на {:.2f} звёзд.\n", rating); // Форматирование до двух знаков после запятой
    }

    // Получатели и установщики для работы с данными
    string getAddress() const {
        return address;
    }

    void setAddress(string_view newAddress) {
        address = newAddress;
    }

    int getRooms() const {
        return rooms;
    }

    void setRooms(int newRooms) {
        rooms = newRooms;
    }

    double getRent() const {
        return rent;
    }

    void setRent(double newRent) {
        rent = newRent;
    }

    Currency getCurrency() const {
        return currency;
    }

    void setCurrency(Currency newCurrency) {
        currency = newCurrency;
    }

    bool getAvailability() const {
        return isAvailable;
    }

    // Функция аренды квартиры
    void rentApartment() {
        if (isAvailable) {
            isAvailable = false;
            std::cout << std::format("Квартира на {} арендована.\n", address);
        }
        else {
            std::cout << std::format("Квартира на {} уже арендована.\n", address);
        }
    }

    // Функция освобождения квартиры
    void freeApartment() {
        isAvailable = true;
        std::cout << std::format("Квартира на {} снова доступна для аренды.\n", address);
    }
};

// Класс RentalSystem
class RentalSystem {
private:
    vector<Apartment> apartments; // Вектор для хранения квартир

public:
    // Добавление квартиры
    void addApartment() {
        string address;
        std::cout << "Введите адрес квартиры: ";
        cin.ignore();
        getline(cin, address);

        int rooms;
        std::cout << "Введите количество комнат: ";
        cin >> rooms;

        double rent;
        std::cout << "Введите стоимость аренды: ";
        cin >> rent;

        int currencyChoice; // Переменная для выбора валюты
        std::cout << "Выберите валюту:\n";
        std::cout << "1. BYN\n";
        std::cout << "2. USD\n";
        std::cout << "3. EUR\n";
        std::cout << "Введите ваш выбор: ";
        cin >> currencyChoice;

        Currency currency; // Объявляем переменную для валюты
        switch (currencyChoice) {
        case 1:
            currency = Currency::BYN;
            break;
        case 2:
            currency = Currency::USD;
            break;
        case 3:
            currency = Currency::EUR;
            break;
        default:
            std::cout << "Неверный выбор валюты. Установлена валюта по умолчанию BYN.\n";
            currency = Currency::BYN;
            break;
        }

        apartments.emplace_back(address, rooms, rent, currency);
        std::cout << "Квартира добавлена успешно.\n";
    }

    // Показ всех квартир
    void showAllApartments() const {
        if (apartments.empty()) {
            std::cout << "Нет доступных квартир.\n";
            return;
        }

        for (size_t i = 0; i < apartments.size(); ++i) {
            apartments[i].showInfo(i + 1); // Индекс квартиры начинается с 1
            std::cout << "------------------------" << endl;
        }
    }

    // Поиск квартиры по диапазону цен
    void searchApartmentByPrice(double minPrice, double maxPrice) const {
        bool found = false;

        for (size_t i = 0; i < apartments.size(); ++i) {
            if (apartments[i].getRent() >= minPrice && apartments[i].getRent() <= maxPrice) {
                apartments[i].showInfo(i + 1); // Индекс квартиры начинается с 1
                std::cout << "------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            std::cout << "Квартиры в данном диапазоне цен не найдены.\n";
        }
    }

    // Сортировка квартир по стоимости
    void sortApartmentsByPrice() {
        sort(apartments.begin(), apartments.end(), [](const Apartment& a, const Apartment& b) {
            return a.getRent() < b.getRent();
            });
        std::cout << "Квартиры успешно отсортированы по стоимости аренды.\n";
    }

    // Добавление рейтинга квартире
    void rateApartment() {
        int index;
        double rating;

        std::cout << "Введите индекс квартиры для оценки: ";
        cin >> index;

        if (index >= 1 && index <= apartments.size()) { // Индексы теперь от 1 до size
            std::cout << "Введите оценку (от 1 до 5): ";  // Рейтинг от 1 до 5
            cin >> rating;
            if (rating >= 1.0 && rating <= 5.0) { // Устанавливаем диапазон 1-5
                apartments[index - 1].addRating(rating); // Индекс для массива
            }
            else {
                std::cout << "Оценка должна быть от 1 до 5.\n";
            }
        }
        else {
            std::cout << "Неверный индекс квартиры.\n";
        }
    }

    // Аренда квартиры
    void rentApartment() {
        int index;

        std::cout << "Введите индекс квартиры для аренды: ";
        cin >> index;

        if (index >= 1 && index <= apartments.size()) { // Индексы теперь от 1 до size
            apartments[index - 1].rentApartment(); // Индекс для массива
        }
        else {
            std::cout << "Неверный индекс квартиры.\n";
        }
    }

    // Освобождение квартиры
    void freeApartment() {
        int index;

        std::cout << "Введите индекс квартиры для освобождения: ";
        cin >> index;

        if (index >= 1 && index <= apartments.size()) { // Индексы теперь от 1 до size
            apartments[index - 1].freeApartment(); // Индекс для массива
        }
        else {
            std::cout << "Неверный индекс квартиры.\n";
        }
    }
};

// Функция для отображения меню
void displayMenu() {
    std::cout << "\nМеню системы аренды квартир:\n";
    std::cout << "1. Добавить квартиру\n";
    std::cout << "2. Показать все квартиры\n";
    std::cout << "3. Поиск квартиры по цене\n";
    std::cout << "4. Сортировка квартир по стоимости\n";
    std::cout << "5. Оценить квартиру\n";
    std::cout << "6. Арендовать квартиру\n";
    std::cout << "7. Освободить квартиру\n"; // Новый пункт в меню
    std::cout << "0. Выйти\n\n";
    std::cout << "Введите ваш выбор: ";
}

int main() {
    system("chcp 1251");
    system("cls");

    RentalSystem system; // Создание экземпляра системы аренды квартир
    int choice; // Переменная для выбора меню

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
            double minPrice; // Минимальная цена
            double maxPrice; // Максимальная цена

            std::cout << "Введите минимальную цену: ";
            cin >> minPrice;
            std::cout << "Введите максимальную цену: ";
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
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
