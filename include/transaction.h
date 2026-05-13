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
    virtual ~transaction_t() = default;

    [[nodiscard]] virtual std::shared_ptr<transaction_t> clone() const = 0;
    virtual void execute() = 0;

    void print_transaction(std::ostream& os) const {
        os << "#" << transaction_id << " [Amount: " << amount << ", Timestamp: " << timestamp << "] - ";
        print(os);
    }

    friend std::ostream& operator<<(std::ostream& os, const transaction_t& t) {
        t.print_transaction(os);
        return os;
    }

    static int get_total_transactions();
};

class deposit_transaction_t : public transaction_t {
private:
    std::string deposit_channel;
protected:
    void print(std::ostream& os) const override;
public:
    deposit_transaction_t(double amount, std::string timestamp, std::string channel);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

class withdrawal_transaction_t : public transaction_t {
private:
    double fee;
protected:
    void print(std::ostream& os) const override;
public:
    withdrawal_transaction_t(double amount, std::string timestamp, double fee);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;

    [[nodiscard]] double get_fee() const { return fee; }
};

class transfer_transaction_t : public transaction_t {
private:
    std::string target_account;
protected:
    void print(std::ostream& os) const override;
public:
    transfer_transaction_t(double amount, std::string timestamp, std::string target_account);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

class payment_transaction_t : public transaction_t {
private:
    std::string merchant_name;
protected:
    void print(std::ostream& os) const override;
public:
    payment_transaction_t(double amount, std::string timestamp, std::string merchant_name);
    [[nodiscard]] std::shared_ptr<transaction_t> clone() const override;
    void execute() override;
};

#endif //OOP_TRANSACTION_H