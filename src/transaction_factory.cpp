//
// Created by Antonie Gabriel Belu on 02.06.2026.
//

#include "../include/transaction_factory.h"

std::shared_ptr<transaction_t> transaction_factory_t::create_deposit(double amount, const std::string& timestamp, const std::string& channel) {
    return std::make_shared<deposit_transaction_t>(amount, timestamp, channel);
}

std::shared_ptr<transaction_t> transaction_factory_t::create_withdrawal(double amount, const std::string& timestamp, double fee) {
    return std::make_shared<withdrawal_transaction_t>(amount, timestamp, fee);
}

std::shared_ptr<transaction_t> transaction_factory_t::create_transfer(double amount, const std::string& timestamp, const std::string& target_account) {
    return std::make_shared<transfer_transaction_t>(amount, timestamp, target_account);
}

std::shared_ptr<transaction_t> transaction_factory_t::create_payment(double amount, const std::string& timestamp, const std::string& merchant_name) {
    return std::make_shared<payment_transaction_t>(amount, timestamp, merchant_name);
}

std::shared_ptr<transaction_t> transaction_factory_t::create_currency_exchange(double amount, const std::string& timestamp, const std::string& from, const std::string& to, double rate) {
    return std::make_shared<currency_exchange_transaction_t>(amount, timestamp, from, to, rate);
}
