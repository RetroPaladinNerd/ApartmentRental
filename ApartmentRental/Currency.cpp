#include "Currency.h"

std::string currencyToString(Currency currency) {
    switch (currency) {
    case Currency::BYN: return "BYN";
    case Currency::USD: return "USD";
    case Currency::EUR: return "EUR";
    default: return "";
    }
}
