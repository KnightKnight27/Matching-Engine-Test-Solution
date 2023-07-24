//
// Created by kartik on 7/24/23.
//
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include "matching_engine.h"

std::ostream &operator<<(std::ostream &os, const Order &obj) {
    os << obj.getOrderID() << " " << (obj.isBuy() ? "BUY" : "SELL") << " "
       << obj.getInstrument() << " " << obj.getUnfilledQuantity()
       << " " << obj.getLimitPrice() << "\n";
    return os;
}

MatchingEngineFIFO::MatchingEngineFIFO() {
    // Constructor implementation...
}

bool MatchingEngineFIFO::create_order(const std::string &order_id, const std::string &order_type,
                                      const std::string &instrument, uint32_t quantity, const double &price) {
    constexpr double eps = 1e-9;
    if (!quantity || price < 0.0 + eps) {
        return false;
    }
    auto order = std::make_shared<Order>();
    order->setOrderID(order_id);
    order->setBuy(order_type == "BUY");
    order->setLimitPrice(price);
    order->setUnfilledQuantity(quantity);
    order->setFilledQuantity(0);
    order->setInstrument(instrument);
    all_order_t.emplace_back(order);
    if (match_price_points(order))
        return true;
    order_book_t &order_book = order->isBuy() ? buy_orders : sell_orders;
    auto order_i = order_book[instrument].find(price);
    if (order_i == order_book[instrument].end()) {
        order_book[instrument].emplace(price, std::make_shared<price_point_t>());
        order_i = order_book[instrument].find(price);
    }
    order_i->second->emplace(order);
    return false;
}

void MatchingEngineFIFO::print_order_books() {
    std::cout << "\n";
    auto order_book_order = get_order_book_order();
    std::vector <std::reference_wrapper<Order>> all_orders;
    all_orders.reserve(all_order_t.size());
    for (auto &order: all_order_t) {
        all_orders.emplace_back(std::ref(*order));
    }

    auto print_side_order_book = [](std::queue <Order> &orders) {
        std::queue <Order> temp_orders;
        while (!orders.empty()) {
            const auto &order = orders.front();
            if (!order.isFilled()) {
                std::cout << order.getOrderID() << " " << (order.isBuy() ? "BUY" : "SELL") << " "
                          << order.getInstrument() << " " << order.getUnfilledQuantity()
                          << " " << order.getLimitPrice() << "\n";

            }
            temp_orders.push(order);
            orders.pop();
        }
        orders.swap(temp_orders);
    };

    for (const std::string &instrument: *order_book_order) {
        std::queue <Order> sell_order_u;
        std::queue <Order> buy_order_u;

        for (const auto &order: all_orders) {
            if (order.get().getInstrument() == instrument) {
                if (order.get().isBuy()) {
                    buy_order_u.push(order.get());
                } else {
                    sell_order_u.push(order.get());
                }
            }
        }

        print_side_order_book(sell_order_u);
        print_side_order_book(buy_order_u);
    }
}

bool MatchingEngineFIFO::fill_order(const std::shared_ptr <Order> &order, const std::shared_ptr <Order> &matching_order,
                                    uint32_t fill_quantity) {
    order->setFilledQuantity(order->getFilledQuantity() + fill_quantity);
    order->setUnfilledQuantity(order->getUnfilledQuantity() - fill_quantity);

    if (order->isBuy()) {
        const auto &instrument = order->getInstrument();
        const auto &matching_order_id = matching_order->getOrderID();
        const auto &order_id = order->getOrderID();
        const auto &limit_price = order->getLimitPrice();
        std::cout << "TRADE " << instrument << " " << matching_order_id << " " << order_id
                  << " " << fill_quantity << " " << limit_price << "\n";
    }

    if (!order->getUnfilledQuantity()) {
        order->setFilled(true);
        return true;
    }

    return false;
}

bool
MatchingEngineFIFO::match_orders_in_price_point(std::shared_ptr <Order> order, std::shared_ptr <price_point_t> pp) {
    while (!pp->empty()) {
        std::shared_ptr <Order> matching_order = pp->front();
        const uint32_t fill_quantity = std::min(matching_order->getUnfilledQuantity(), order->getUnfilledQuantity());

        if (fill_order(matching_order, order, fill_quantity))
            pp->pop();
        if (fill_order(order, matching_order, fill_quantity))
            return true;
    }
    return false;
}

bool MatchingEngineFIFO::match_price_points(std::shared_ptr <Order> order) {
    order_book_t &complete_order_book = order->isBuy() ? sell_orders : buy_orders;
    security_order_book_t &opposing_order_book = complete_order_book[order->getInstrument()];
    security_order_book_t::iterator it = order->isBuy() ? opposing_order_book.begin() : opposing_order_book.end();
    security_order_book_t::iterator end_it = order->isBuy() ? opposing_order_book.end() : opposing_order_book.begin();

    while (it != end_it) {
        if (!order->isBuy())
            it--;
        if ((order->isBuy() && (it->first > order->getLimitPrice())) ||
            (!order->isBuy() && (it->first < order->getLimitPrice())))
            break;
        std::shared_ptr <price_point_t> pp = it->second;
        if (match_orders_in_price_point(order, pp))
            return true;
        if (order->isBuy())
            it++;
    }
    return false;
}

std::unique_ptr <std::vector<std::string>> MatchingEngineFIFO::get_order_book_order() {
    auto order_book_display_order = std::make_unique < std::vector < std::string >> ();
    for (std::shared_ptr <Order> order_t: all_order_t) {
        if (order_t->getUnfilledQuantity()) {
            order_book_display_order->push_back(order_t->getInstrument());
            unfilled_orders[order_t->getInstrument()].emplace_back(*order_t);
        }
    }
    std::unordered_set <std::string> encounteredElements;
    order_book_display_order->erase(
            std::remove_if(
                    order_book_display_order->begin(), order_book_display_order->end(),
                    [&encounteredElements](const std::string &element) {
                        return !encounteredElements.insert(element).second;
                    }
            ),
            order_book_display_order->end()
    );
    return order_book_display_order;
}
