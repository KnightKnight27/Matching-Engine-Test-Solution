//
// Created by kartik on 7/24/23.
//
#include "order.h"

Order::Order()
        : is_buy(false),
          is_filled(false),
          limit_price(0.0),
          total_fill_price(0.0),
          unfilled_quantity(0),
          filled_quantity(0) {
}

const std::string &Order::getOrderID() const {
    return order_id;
}

const std::string &Order::getInstrument() const {
    return instrument;
}

bool Order::isBuy() const {
    return is_buy;
}

bool Order::isFilled() const {
    return is_filled;
}

double Order::getLimitPrice() const {
    return limit_price;
}

uint32_t Order::getUnfilledQuantity() const {
    return unfilled_quantity;
}

uint32_t Order::getFilledQuantity() const {
    return filled_quantity;
}

void Order::setOrderID(const std::string &order_id) {
    this->order_id = order_id;
}

void Order::setInstrument(const std::string &instrument) {
    this->instrument = instrument;
}

void Order::setBuy(bool buy) {
    is_buy = buy;
}

void Order::setFilled(bool filled) {
    is_filled = filled;
}

void Order::setLimitPrice(double price) {
    limit_price = price;
}

void Order::setUnfilledQuantity(uint32_t quantity) {
    unfilled_quantity = quantity;
}

void Order::setFilledQuantity(uint32_t quantity) {
    filled_quantity = quantity;
}
