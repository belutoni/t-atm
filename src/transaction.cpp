//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#include "../include/transaction.h"

int transaction_t::total_transactions = 0;
constexpr static int transaction_id_start = 100000;

transaction_t::transaction_t(const double amount, std::string timestamp)
    : amount(amount), timestamp(std::move(timestamp)), transaction_id(total_transactions + transaction_id_start) {
    ++total_transactions;
}

int transaction_t::get_total_transactions() {
    return total_transactions;
}

deposit_transaction_t::deposit_transaction_t(const double amount, std::string timestamp, std::string channel)
    : transaction_t(amount, std::move(timestamp)), deposit_channel(std::move(channel)) {}

std::shared_ptr<transaction_t> deposit_transaction_t::clone() const {
    return std::make_shared<deposit_transaction_t>(*this);
}

void deposit_transaction_t::execute() {
    std::cout << "Executing deposit of " << amount << " via " << deposit_channel << "\n";
}

void deposit_transaction_t::print(std::ostream& os) const {
    os << "Type: Deposit, Channel: " << deposit_channel;
}

withdrawal_transaction_t::withdrawal_transaction_t(const double amount, std::string timestamp, const double fee)
    : transaction_t(amount, std::move(timestamp)), fee(fee) {}

std::shared_ptr<transaction_t> withdrawal_transaction_t::clone() const {
    return std::make_shared<withdrawal_transaction_t>(*this);
}

void withdrawal_transaction_t::execute() {
    std::cout << "Executing withdrawal of " << amount << " with fee " << fee << "\n";
}

void withdrawal_transaction_t::print(std::ostream& os) const {
    os << "Type: Withdrawal, Fee: " << fee;
}

transfer_transaction_t::transfer_transaction_t(const double amount, std::string timestamp, std::string target_account)
    : transaction_t(amount, std::move(timestamp)), target_account(std::move(target_account)) {}

std::shared_ptr<transaction_t> transfer_transaction_t::clone() const {
    return std::make_shared<transfer_transaction_t>(*this);
}

void transfer_transaction_t::execute() {
    std::cout << "Executing transfer of " << amount << " to " << target_account << "\n";
}

void transfer_transaction_t::print(std::ostream& os) const {
    os << "Type: Transfer, Target Account: " << target_account;
}

payment_transaction_t::payment_transaction_t(const double amount, std::string timestamp, std::string merchant_name)
    : transaction_t(amount, std::move(timestamp)), merchant_name(std::move(merchant_name)) {}

std::shared_ptr<transaction_t> payment_transaction_t::clone() const {
    return std::make_shared<payment_transaction_t>(*this);
}

void payment_transaction_t::execute() {
    std::cout << "Executing payment of " << amount << " to " << merchant_name << "\n";
}

void payment_transaction_t::print(std::ostream& os) const {
    os << "Type: Payment, Merchant: " << merchant_name;
}
