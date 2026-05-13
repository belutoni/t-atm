//
// Created by Antonie Gabriel Belu on 18.03.2026.
//

#include "../include/bank_account.h"

std::ostream &operator<<(std::ostream& os, const bank_account_t& bank_account) {
    os << "account_id: " << bank_account.identifier << "\n"
       << "username: " << bank_account.username << "\n\n"
       << bank_account.client << "\n"
       << bank_account.bank
       << "balance: " << bank_account.balance << "\n"
       << "transactions:\n";

    if (bank_account.transactions.empty()) {
        os << "  No transactions found.\n";
        return os;
    }

    for (const auto& transaction : bank_account.transactions) {
        if (transaction) {
            os << "> " << *transaction << "\n";
        }
    }

    return os;
}

bank_account_t::bank_account_t(const bank_account_t &other) 
    : identifier(other.identifier), username(other.username), pin(other.pin),
      client(other.client), bank(other.bank), balance(other.balance) {
    for (const auto& t : other.transactions) {
        if (t) {
            transactions.push_back(t->clone());
        } else {
            transactions.push_back(nullptr);
        }
    }
}

void swap(bank_account_t& first, bank_account_t& second) noexcept {
    using std::swap;
    swap(first.identifier, second.identifier);
    swap(first.username, second.username);
    swap(first.pin, second.pin);
    swap(first.client, second.client);
    swap(first.bank, second.bank);
    swap(first.balance, second.balance);
    swap(first.transactions, second.transactions);
}

bank_account_t &bank_account_t::operator=(bank_account_t other) noexcept {
    swap(*this, other);
    return *this;
}

void bank_account_t::add_transaction(const std::shared_ptr<transaction_t>& transaction) {
    transactions.push_back(transaction);
}

void bank_account_t::execute_all_transactions() const {
    for (auto& transaction : transactions) {
        if (transaction) {
            transaction->execute();
        }
    }
}

void bank_account_t::calculate_total_withdrawal_fees() const {
    double total_fees = 0.0;
    for (const auto& transaction : transactions) {
        if (const auto wt = std::dynamic_pointer_cast<withdrawal_transaction_t>(transaction)) {
            total_fees += wt->get_fee();
        }
    }
    std::cout << "Total withdrawal fees for account " << identifier << " is: " << total_fees << "\n";
}
