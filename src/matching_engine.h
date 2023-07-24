//
// Created by kartik on 7/24/23.
//

#ifndef MATCHING_ENGINE_LEARNING_MATCHING_ENGINE_H
#define MATCHING_ENGINE_LEARNING_MATCHING_ENGINE_H

#include <memory>
#include <map>
#include <unordered_map>
#include <vector>
#include <queue>
#include "order.h"

typedef std::queue <std::shared_ptr<Order>> price_point_t;
typedef std::map<double, std::shared_ptr<price_point_t>> security_order_book_t;
typedef std::unordered_map <std::string, security_order_book_t> order_book_t;
typedef std::unordered_map <std::string, std::vector<Order>> unfilled_order;
typedef std::vector <std::shared_ptr<Order>> all_order;

class MatchingEngineFIFO {
public:
    MatchingEngineFIFO();

    bool create_order(const std::string &order_id, const std::string &order_type,
                      const std::string &instrument, uint32_t quantity, const double &price);

    void print_order_books();

private:
    bool fill_order(const std::shared_ptr <Order> &order, const std::shared_ptr <Order> &matching_order,
                    uint32_t fill_quantity);

    bool match_orders_in_price_point(std::shared_ptr <Order> order, std::shared_ptr <price_point_t> pp);

    bool match_price_points(std::shared_ptr <Order> order);

    std::unique_ptr <std::vector<std::string>> get_order_book_order();

    all_order all_order_t;
    unfilled_order unfilled_orders;
    order_book_t buy_orders;
    order_book_t sell_orders;
};

#endif //MATCHING_ENGINE_LEARNING_MATCHING_ENGINE_H
