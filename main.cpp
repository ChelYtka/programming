#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>
#include "ip_filter.h"

int main () {

    std::vector<std::tuple<int, int, int, int>> ip_adress;

    // считывает файл
    ip_adress = readfile("../ip_filter.tsv");

    sort_ip(ip_adress);
    // задание 1
    std::cout << "task 1" << std::endl;
    // выводит все ip
    for (const auto& ip : ip_adress)
    {
        std::cout << std::get<0>(ip) << ".";
        std::cout << std::get<1>(ip) << ".";
        std::cout << std::get<2>(ip) << ".";
        std::cout << std::get<3>(ip) << ".";
        std::cout << std::endl;
    }

    std::cout << std::endl;
    // задание 2
    std::cout << "task 2" << std::endl;
    // проверяет, если ip подходит - выводит
    for (const auto& ip : ip_adress) {
        if (std::get<0>(ip) == 1)
        {
            std::cout << std::get<0>(ip) << ".";
            std::cout << std::get<1>(ip) << ".";
            std::cout << std::get<2>(ip) << ".";
            std::cout << std::get<3>(ip) << ".";
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
    // задание 3
    std::cout << "task 3" << std::endl;
    // проверяет, если ip подходит - выводит
    for (decltype(ip_adress[0]) ip : ip_adress) {
        if (std::get<0>(ip) == 46)
        {
            if (std::get<1>(ip) == 70)
            {
                std::cout << std::get<0>(ip) << ".";
                std::cout << std::get<1>(ip) << ".";
                std::cout << std::get<2>(ip) << ".";
                std::cout << std::get<3>(ip) << ".";
                std::cout << std::endl;
            }
        }
    }

    std::cout << std::endl;
    // задание 4
    std::cout << "task 4" << std::endl;
    // проверяет, если ip подходит - выводит
    for (const auto& ip : ip_adress) {
        if (std::get<0>(ip) == 46 ||
            std::get<1>(ip) == 46 ||
            std::get<2>(ip) == 46 ||
            std::get<3  >(ip) == 46 )
        {
            std::cout << std::get<0>(ip) << ".";
            std::cout << std::get<1>(ip) << ".";
            std::cout << std::get<2>(ip) << ".";
            std::cout << std::get<3>(ip) << ".";
            std::cout << std::endl;
        }
    }
}