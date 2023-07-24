#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "matching_engine.h"

int main() {
    MatchingEngineFIFO engine;
    std::string line, order_type, instrument, order_id;
    uint32_t quantity;
    double price;

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        if (iss >> order_id >> order_type >> instrument >> quantity >> price) {
            engine.create_order(order_id, order_type, instrument, quantity, price);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    engine.print_order_books();

    return 0;
}
