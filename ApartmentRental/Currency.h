#pragma once
#include <string>

enum class Currency {
    BYN, // ����������� �����
    USD, // ������ ���
    EUR  // ����
};

std::string currencyToString(Currency currency);

