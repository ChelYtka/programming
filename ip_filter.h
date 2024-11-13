#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>

std::tuple<int, int, int, int> parse_ip_adress(std::string ip_address_str); // Функция преобразования строки IP адреса в кортеж

std::vector<std::tuple<int, int, int, int>> readfile(std::string fileName); // Функция считывания файла

void sort_ip(std::vector<std::tuple<int, int, int, int>>& ipAddresses); // Функция сортировки ip адресов
#endif // IP_FILTER_H