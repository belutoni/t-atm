//
// Created by Antonie Gabriel Belu on 02.06.2026.
//

#ifndef OOP_BANK_MANAGER_H
#define OOP_BANK_MANAGER_H

#include "bank.h"
#include "repository.h"

class bank_manager_t {
    repository_t<bank_t> banks;

    bank_manager_t() = default;

public:
    bank_manager_t(const bank_manager_t&) = delete;
    bank_manager_t& operator=(const bank_manager_t&) = delete;
    bank_manager_t(bank_manager_t&&) = delete;
    bank_manager_t& operator=(bank_manager_t&&) = delete;

    static bank_manager_t& get_instance();

    void add_bank(const bank_t& bank);
    bank_t& get_bank(size_t index);
    repository_t<bank_t>& get_banks();
    
    void load_banks_from_disk();
    void save_all_banks();
};

#endif // OOP_BANK_MANAGER_H
