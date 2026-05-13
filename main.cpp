#include "bank.h"
#include "bank_account.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "Enter bank name: ";
    std::string my_bank_name;
    std::ifstream tastatura("tastatura.txt");
    std::getline(tastatura, my_bank_name);

    if (my_bank_name.empty()) {
        my_bank_name = "Default Romanian Bank";
    }

    std::cout << "\n[t-atm stadiu 1] Creating Bank\n";
    bank_t bank(my_bank_name);
    std::cout << bank << '\n';

    std::cout << "[t-atm stadiu doi] Creating Clients\n";
    client_t client1("Mihai", "Eminescu", "Str. Teilor", "Iasi", "Iasi", "700000",
                     "mihai@poezie.ro", "0711223344");
    client_t client2("Ion", "Creanga", "Str. Bojdeucii", "Iasi", "Iasi", "700111",
                     "ion@povesti.ro", "0722334455");
    std::cout << client1 << '\n' << client2 << '\n';

    std::cout << "[t-atm stadiu three] Adding Clients to Bank\n";
    bank.add_client(client1);
    bank.add_client(client2);
    std::cout << bank << '\n';

    std::cout << "[t-atm stage 4 c de la client] Removing a Client\n";
    bank.remove_client(1);
    std::cout << bank << '\n';

    std::cout << "[t-atm stage quattro] Testing Copy and Assignment\n";
    bank_t copied_bank(bank);
    std::cout << "COPIED_BANK: " << copied_bank << '\n';
    bank_t assigned_bank("Temporary Bank");
    std::cout << "ASSIGNED_BANK: " << assigned_bank << '\n';
    assigned_bank = bank;
    std::cout << "ASSIGNED_BANK AFTER = BANK: " << assigned_bank << '\n';

    std::cout << "[t-atm stadiu sase] Testing Bank Account Creation\n";
    client_t moved_client(std::move(client1));
    std::cout << moved_client << '\n';
    bank_account_t acc1("mihai_emi", "1234", moved_client, bank, 5000, {});
    std::cout << acc1 << '\n';

    std::cout << "[t-atm polymorphism (poly doar in c++, nu relatii)] Adding transactions\n";
    acc1.add_transaction(std::make_shared<deposit_transaction_t>(1000, "2026-04-27 10:00", "ATM"));
    acc1.add_transaction(std::make_shared<withdrawal_transaction_t>(200, "2026-04-27 11:00", 2.5));
    acc1.add_transaction(std::make_shared<transfer_transaction_t>(500, "2026-04-27 12:00", "RO123456789"));
    acc1.add_transaction(std::make_shared<payment_transaction_t>(50, "2026-04-27 13:00", "Supermarket"));

    std::cout << "Executing all transactions:\n";
    acc1.execute_all_transactions();

    std::cout << "\nCalculating total fees using dynamic_cast:\n";
    acc1.calculate_total_withdrawal_fees();

    std::cout << "\nTotal transactions created: " << transaction_t::get_total_transactions() << "\n";

    std::cout << "Account with transactions:\n" << acc1 << '\n';
    bank_account_t acc_copy(acc1);
    std::cout << "ACCOUNT COPY: " << acc_copy << '\n';

    std::cout << "[t-atm m am plictisit] Saving Bank Data to JSON\n";
    bank.save();

    std::cout << "[t-atm noua] Loading Bank Data from JSON\n";
    std::string file_path = "assets/" + bank.get_identifier() + ".json";
    bank_t loaded_bank = bank_t::load(file_path);
    std::cout << loaded_bank << '\n';
    return 0;
}
