//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_TRANSACTION_H
#define OOP_TRANSACTION_H

#include <string>
#include <iostream>
#include <memory>

class transaction_t {
protected:
    double amount;
    std::string timestamp;
    static int total_transactions;
    int transaction_id;

    virtual void print(std::ostream& os) const = 0;
public:
    transaction_t(double amount, std::string timestamp);

    void print_transaction(std::ostream& os) const {
        os << "#" << transaction_id << " [Amount: " << amount << ", Timestamp: " << timestamp << "] - ";
        print(os);
    }

    friend std::ostream& operator<<(std::ostream& os, const transaction_t& t) {
        t.print_transaction(os);
        return os;
    }

    static int get_total_transactions();

    [[nodiscard]] virtual std::shared_ptr<transaction_t> clone() const = 0;
    virtual void execute() = 0;

    virtual ~transaction_t() = default;
};

class deposit_transaction_t : public transaction_t {
protected:
    std::string deposit_channel;

    void print(std::ostream& os) const override;
public:
    deposit_transaction_t(double amount, std::string timestamp, std::string channel);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

class withdrawal_transaction_t : public transaction_t {
protected:
    double fee;

    void print(std::ostream& os) const override;
public:
    withdrawal_transaction_t(double amount, std::string timestamp, double fee);

    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;

    [[nodiscard]] double get_fee() const { return fee; }
};

class transfer_transaction_t : public transaction_t {
protected:
    std::string target_account;

    void print(std::ostream& os) const override;
public:
    transfer_transaction_t(double amount, std::string timestamp, std::string target_account);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

class payment_transaction_t : public transaction_t {
protected:
    std::string merchant_name;

    void print(std::ostream& os) const override;
public:
    payment_transaction_t(double amount, std::string timestamp, std::string merchant_name);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

class currency_exchange_transaction_t : public transaction_t {
protected:
    std::string from_currency;
    std::string to_currency;
    double exchange_rate;

    void print(std::ostream& os) const override;
public:
    currency_exchange_transaction_t(double amount, const std::string &timestamp, std::string from, std::string to, double rate);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

#endif //OOP_TRANSACTION_H