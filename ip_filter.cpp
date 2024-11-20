#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <tuple>

std::tuple<int, int, int, int> parse_ip_adress(std::string str)
{
    // Разделение ip адреса на отдельные числа
    std::istringstream ip_stream(str);

    int n1, n2, n3, n4;
    std::getline(ip_stream, str, '.');
    n1 = std::stoi(str);
    std::getline(ip_stream, str, '.');
    n2 = std::stoi(str);
    std::getline(ip_stream, str, '.');
    n3 = std::stoi(str);
    std::getline(ip_stream, str, '.');
    n4 = std::stoi(str);

    return std::make_tuple(n1, n2, n3, n4);

}


std::vector<std::tuple<int, int, int, int>> readfile(std::string filename)
{
    // открытие файла
    std::ifstream file (filename);
    if (!file.is_open())
    {
        std::cerr << L"error open file" << std::endl;
        return {};
    }

    std::vector<std::tuple<int, int, int, int>> ip_adreses;

    // чтение строк из файла
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream str(line);
        std::string text1, text2, text3;
        std::getline(str, text1, '\t');
        std::getline(str, text2, '\t');
        std::getline(str, text3, '\t');

        // вытаскиваем каждое число адреса
        auto ip_adress = parse_ip_adress(text1);
        ip_adreses.push_back(ip_adress);
    }
    // закрываем файл
    file.close();

    return ip_adreses;


}


void sort_ip(std::vector<std::tuple<int, int, int, int>> & ip_adress)
{
    // сортируем в обратном лексикографическом порядке
    std::sort(ip_adress.begin(), ip_adress.end(), [&](const auto ip1, const auto ip2)
    {
        if (std::get<0>(ip1) != std::get<0>(ip2)) {
            return std::get<0>(ip1) > std::get<0>(ip2);
        } else if (std::get<1>(ip1) != std::get<1>(ip2)) {
            return std::get<1>(ip1) > std::get<1>(ip2);
        } else if (std::get<2>(ip1) != std::get<2>(ip2)) {
            return std::get<2>(ip1) > std::get<2>(ip2);
        } else {
            return std::get<3>(ip1) > std::get<3>(ip2);
        }
    });
}