#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdarg.h>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

typedef std::tuple<int, int, int, int> ipTuple;


template <typename TupleT, std::size_t... Is>
void print_tuple_imp(const TupleT& tp, std::index_sequence<Is...>) {
    size_t index = 0;
    auto printElem = [&index](const auto& x) {
        if (index++ > 0) 
            std::cout << ".";
        std::cout << x;
    };
    (printElem(std::get<Is>(tp)), ...);
    std::cout << std::endl;
}

template <typename TupleT, std::size_t TupSize = std::tuple_size_v<TupleT>>
void print_tuple(const TupleT& tp) {
    print_tuple_imp(tp, std::make_index_sequence<TupSize>{});
}

bool get_ip_from_line(const std::string &line, ipTuple &ip)
{
    std::vector<std::string> v = split(line, '\t');
    std::vector<std::string> ipVec = split(v.at(0), '.');

    if(ipVec.size() < 4)
        return false;

    ip = std::make_tuple(std::stoi(ipVec[0]), std::stoi(ipVec[1]), std::stoi(ipVec[2]), std::stoi(ipVec[3]));
    return true;
}

//Проверяет айпишник на строгое соответствие
template <typename TupleT, std::size_t... Is, typename... Args>
bool check_ip(const TupleT& tp, std::index_sequence<Is...>,  Args... values) {
    std::vector<int> vec = {values...};
    int index = 0;

    bool checked = true;
    auto checkElement = [&checked, &index](const auto& x, int  x1) {
        index ++;

        if(x == x1)
            return checked &= true;

        return checked &= false;
    };

    (checkElement(std::get<Is>(tp), vec.at(index)), ...);
    return checked;
}

//Проверяет айпишник на строгое соответствие
template <typename TupleT>
bool check_ip_any(const TupleT& tp, int value) {
    return std::get<0>(tp) == value || 
        std::get<1>(tp) == value ||
        std::get<2>(tp) == value ||
        std::get<3>(tp) == value;
}

//отфильтровать список айпишников на строгое соответствие переданному списку значений
template <typename... Args>
void filter(const std::vector<ipTuple>& vec, Args... values)
{
    auto filterCount = sizeof...(values);
    if(filterCount > 4)
        throw;

    std::vector<ipTuple> filteredPool;
    for(auto tuple : vec)
    {
         if(check_ip(tuple, std::make_index_sequence<sizeof...(values)>{}, values...))
            filteredPool.emplace_back(tuple);

    }
    for(auto ip : filteredPool)
        print_tuple(ip);
}

void filter_any(const std::vector<ipTuple>& vec, int value)
{
    std::vector<ipTuple> filteredPool;
    for(auto tuple : vec)
    {
         if(check_ip_any(tuple, value))
            filteredPool.emplace_back(tuple);

    }
    for(auto ip : filteredPool)
        print_tuple(ip);
}


int main(int argc, char const *argv[])
{
    try
    {
        std::vector<ipTuple> ip_pool;
        /** get ip list from file */
        //std::ifstream dataFile;
        //dataFile.open("ip_filter.tsv");
        //for(std::string line; std::getline(dataFile, line);)

        for(std::string line; std::getline(std::cin, line);)
        {
            ipTuple ip;
            //если не удалось вытащить айпи из строки, то прерываем чтение
            if(!get_ip_from_line(line, ip))
                break;
            ip_pool.push_back(std::move(ip));
        }

        sort(ip_pool.begin(), ip_pool.end(),[](auto &left, auto &right){
            return std::tie(left) > std::tie(right);
        });

        for(auto ip : ip_pool)
            print_tuple(ip);
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        filter(ip_pool, 1);
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8
        filter(ip_pool, 46, 70);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        filter_any(ip_pool, 46);
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
