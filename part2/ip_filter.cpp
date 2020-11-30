#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <exception>
#include <algorithm>
#include <cstdlib> 
#include <cstdint>
#include "trim.h"

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
    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));
    return r;
}


struct my_ip {
    std::string strval; 
    std::array<uint8_t,4> intval;
    
    my_ip(std::string v): strval(v) {
        auto items = split(strval, '.');
        if (items.size()!=4){ 
            throw std::invalid_argument("");
        }
        for(int i=0; i<4; i++){
            auto num=std::stoi(items[i]);
            if (num>=0 && num<=255){
                intval[i]=num;
            } else {
                throw std::invalid_argument("");
            }
        }
    }
};


int main(int , char const **)
{
    try
    {
        // fill pull and check
        long line_number=1; 
        std::vector<my_ip> ip_pool;
        for(std::string line; std::getline(std::cin, line); line_number++) {
            try{
                trim(line);
                if (line.size() == 0){
                    continue; // ignore empty adress or strings
                }
                std::vector<std::string> v = split(line, '\t');
                ip_pool.push_back(my_ip(v.at(0)));
            } catch (const std::invalid_argument &ex){
                std::cerr << "Skipped invalid IP-address on line " << line_number << std::endl;
            }    
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), 
            [](const my_ip &lv, const my_ip &rv){
                return lv.intval>rv.intval;
            }
        );

        // Print all list
        for (my_ip& ip : ip_pool){
            std::cout<<ip.strval<<std::endl;
        }

        //  filter by first byte and output
        // ip = filter(1)
        for_each(ip_pool.begin(), ip_pool.end(),
            [z0=1](const my_ip& ip){
                if (ip.intval[0]==z0){
                    std::cout<<ip.strval<<std::endl;
                }
            }
        );

        // filter by first and second bytes and output
        // ip = filter(46, 70)
        for_each(ip_pool.begin(), ip_pool.end(),
            [z0=46, z1=70](const my_ip& ip){
                if (ip.intval[0]==z0 && ip.intval[1]==z1 ){
                    std::cout<<ip.strval<<std::endl;
                }
            }
        );

        // filter by any byte and output
        // ip = filter_any(46)
        for_each(ip_pool.begin(), ip_pool.end(),
            [z=46](const my_ip& ip){
                if (std::find(ip.intval.cbegin(), ip.intval.cend(), z) != ip.intval.cend()){
                    std::cout<<ip.strval<<std::endl;
                }
            }
        );
        
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
