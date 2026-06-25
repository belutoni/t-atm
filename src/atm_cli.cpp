//
// Created by Antonie Gabriel Belu on 02.06.2026.
//

#include "../include/atm_cli.h"
#include "../include/transaction_factory.h"
#include <iostream>

atm_cli_t::atm_cli_t() : bank_manager(bank_manager_t::get_instance()) {
}

void atm_cli_t::start() {
    std::cout << "=================================\n";
    std::cout << "        Welcome to t-atm         \n";
    std::cout << "=================================\n";

    bank_manager.load_banks_from_disk();

    if (bank_manager.get_banks().empty()) {
        std::cout << "No banks available. Creating default bank...\n";
        bank_manager.add_bank(bank_t("Default Romanian Bank"));
    }

    while (true) {
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Select Bank and Login\n";
        std::cout << "2. View Recent Clients\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";
        
        int option;
        std::cin >> option;

        if (option == 1) {
            select_bank();
        } else if (option == 2) {
            view_recent_clients();
        } else if (option == 3) {
            std::cout << "Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void atm_cli_t::select_bank() {
    std::cout << "\nAvailable Banks:\n";
    print_collection(bank_manager.get_banks());

    std::cout << "Select bank by index: ";
    size_t index;
    std::cin >> index;

    try {
        const bank_t& selected_bank = bank_manager.get_bank(index);
        std::cout << "Selected bank.\n";
        authenticate(selected_bank);
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void atm_cli_t::authenticate(const bank_t& bank) {
    std::string username, pin, first_name, last_name, street_name, city, state, postal_code, email, phone_number;
    std::cout << "Enter Username: ";
    std::cin >> username;

    std::cout << "Enter PIN: ";
    std::cin >> pin;
    std::cin.ignore(1000, '\n');

    std::cout << "Enter First Name: ";
    std::getline(std::cin, first_name);
    std::cout << "Enter Last Name: ";
    std::getline(std::cin, last_name);
    std::cout << "Enter Street Name: ";
    std::getline(std::cin, street_name);
    std::cout << "Enter City: ";
    std::getline(std::cin, city);
    std::cout << "Enter State: ";
    std::getline(std::cin, state);
    std::cout << "Enter Postal Code: ";
    std::getline(std::cin, postal_code);
    std::cout << "Enter Email: ";
    std::getline(std::cin, email);
    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, phone_number);

    client_t real_client(first_name, last_name, street_name, city, state, postal_code, email, phone_number);
    recent_clients.add(real_client);

    current_account.emplace(username, pin, real_client, bank, 1000, std::vector<std::shared_ptr<transaction_t>>{});
    std::cout << "\nLogin successful!\n";

    show_account_menu();
    current_account.reset();
}

void atm_cli_t::show_account_menu() {
    while (true) {
        std::cout << "\n--- Account Menu ---\n";
        std::cout << "1. View Balance & Details\n";
        std::cout << "2. Perform Transaction\n";
        std::cout << "3. Execute All Pending Transactions\n";
        std::cout << "4. Calculate Withdrawal Fees\n";
        std::cout << "5. Logout\n";
        std::cout << "Choose an option: ";

        int option;
        std::cin >> option;

        if (option == 1) {
            std::cout << current_account.value() << "\n";
        } else if (option == 2) {
            perform_transaction();
        } else if (option == 3) {
            current_account->execute_all_transactions();
            std::cout << "Transactions executed.\n";
        } else if (option == 4) {
            current_account->calculate_total_withdrawal_fees();
        } else if (option == 5) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void atm_cli_t::perform_transaction() {
    std::cout << "\n--- Select Transaction Type ---\n";
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdrawal\n";
    std::cout << "3. Transfer\n";
    std::cout << "4. Payment\n";
    std::cout << "5. Currency Exchange\n";
    std::cout << "Choose an option: ";

    int option;
    std::cin >> option;

    double amount;
    std::cout << "Enter amount: ";
    std::cin >> amount;

    std::string timestamp = "Now";

    std::shared_ptr<transaction_t> tx = nullptr;

    switch (option) {
        case 1: {
            std::string channel;
            std::cout << "Enter deposit channel (e.g. ATM, Branch): ";
            std::cin >> channel;
            tx = transaction_factory_t::create_deposit(amount, timestamp, channel);
            break;
        }
        case 2: {
            double fee;
            std::cout << "Enter withdrawal fee: ";
            std::cin >> fee;
            tx = transaction_factory_t::create_withdrawal(amount, timestamp, fee);
            break;
        }
        case 3: {
            std::string target;
            std::cout << "Enter target account: ";
            std::cin >> target;
            tx = transaction_factory_t::create_transfer(amount, timestamp, target);
            break;
        }
        case 4: {
            std::string merchant;
            std::cout << "Enter merchant name: ";
            std::cin >> merchant;
            tx = transaction_factory_t::create_payment(amount, timestamp, merchant);
            break;
        }
        case 5: {
            std::string from, to;
            double rate;
            std::cout << "From currency: ";
            std::cin >> from;
            std::cout << "To currency: ";
            std::cin >> to;
            std::cout << "Exchange rate: ";
            std::cin >> rate;
            tx = transaction_factory_t::create_currency_exchange(amount, timestamp, from, to, rate);
            break;
        }
        default:
            std::cout << "Invalid transaction type.\n";
            return;
    }

    if (tx) {
        current_account->add_transaction(tx);
        std::cout << "Transaction created and added to pending queue!\n";
    }
}

void atm_cli_t::view_recent_clients() const {
    std::cout << "\n--- Recent Clients ---\n";
    print_collection(recent_clients);
}
