//
// Created by Antonie Gabriel Belu on 02.06.2026.
//

#ifndef OOP_TRANSACTION_FACTORY_H
#define OOP_TRANSACTION_FACTORY_H

#include "transaction.h"
#include <memory>
#include <string>

class transaction_factory_t {
public:
    static std::shared_ptr<transaction_t> create_deposit(double amount, const std::string& timestamp, const std::string& channel);
    static std::shared_ptr<transaction_t> create_withdrawal(double amount, const std::string& timestamp, double fee);
    static std::shared_ptr<transaction_t> create_transfer(double amount, const std::string& timestamp, const std::string& target_account);
    static std::shared_ptr<transaction_t> create_payment(double amount, const std::string& timestamp, const std::string& merchant_name);
    static std::shared_ptr<transaction_t> create_currency_exchange(double amount, const std::string& timestamp, const std::string& from, const std::string& to, double rate);
};

#endif // OOP_TRANSACTION_FACTORY_H
