//
// Created by kartik on 7/24/23.
//
#ifndef MATCHING_ENGINE_LEARNING_ORDER_H
#define MATCHING_ENGINE_LEARNING_ORDER_H

#include <stdint-gcc.h>
#include <string>

class Order {
public:
    Order();

    const std::string &getOrderID() const;

    const std::string &getInstrument() const;

    bool isBuy() const;

    bool isFilled() const;

    double getLimitPrice() const;

    uint32_t getUnfilledQuantity() const;

    uint32_t getFilledQuantity() const;

    void setOrderID(const std::string &order_id);

    void setInstrument(const std::string &instrument);

    void setBuy(bool buy);

    void setFilled(bool filled);

    void setLimitPrice(double price);

    void setUnfilledQuantity(uint32_t quantity);

    void setFilledQuantity(uint32_t quantity);

    friend std::ostream &operator<<(std::ostream &os, const Order &obj);

private:
    std::string order_id;
    std::string instrument;
    bool is_buy: 1;
    bool is_filled: 1;
    double limit_price;
    double total_fill_price;
    uint32_t unfilled_quantity;
    uint32_t filled_quantity;
};

#endif //MATCHING_ENGINE_LEARNING_ORDER_H
