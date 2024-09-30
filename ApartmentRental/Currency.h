#pragma once
#include <string>

enum class Currency {
    BYN, // Белорусский рубль
    USD, // Доллар США
    EUR  // Евро
};

std::string currencyToString(Currency currency);

