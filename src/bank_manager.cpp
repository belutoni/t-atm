//
// Created by Antonie Gabriel Belu on 02.06.2026.
//

#include "../include/bank_manager.h"
#include <filesystem>
#include <iostream>

bank_manager_t& bank_manager_t::get_instance() {
    static bank_manager_t instance;
    return instance;
}

void bank_manager_t::add_bank(const bank_t& bank) {
    banks.add(bank);
}

bank_t& bank_manager_t::get_bank(size_t index) {
    return banks.get(index);
}

repository_t<bank_t>& bank_manager_t::get_banks() {
    return banks;
}

void bank_manager_t::load_banks_from_disk() {
    const std::string directory = "assets";
    if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory)) {
        return;
    }

    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            try {
                bank_t loaded_bank = bank_t::load(entry.path().string());
                banks.add(loaded_bank);
            } catch (const std::exception& e) {
                std::cerr << "Error loading bank from " << entry.path().string() << ": " << e.what() << "\n";
            }
        }
    }
}

void bank_manager_t::save_all_banks() {
    for (size_t i = 0; i < banks.size(); ++i) {
        banks.get(i).save();
    }
}
