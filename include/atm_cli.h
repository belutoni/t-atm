#ifndef OOP_ATM_CLI_H
#define OOP_ATM_CLI_H

#include "bank_manager.h"
#include "bank_account.h"
#include <memory>
#include <optional>

class atm_cli_t {
    bank_manager_t& bank_manager;
    std::optional<bank_account_t> current_account;
    repository_t<client_t> recent_clients;

    void select_bank();
    void authenticate(const bank_t& bank);
    void show_account_menu();
    void perform_transaction();
    void view_recent_clients() const;

public:
    atm_cli_t();
    void start();
};

#endif // OOP_ATM_CLI_H
