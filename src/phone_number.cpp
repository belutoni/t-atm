//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#include "../include/phone_number.h"

std::ostream &operator<<(std::ostream &os, const phone_number_t &pn) {
    os << pn.value;
    
    return os;
}

void to_json(nlohmann::json &j, const phone_number_t &p) {
    j = p.value;
}

void from_json(const nlohmann::json &j, phone_number_t &p) {
    p.value = j.get<std::string>();
}
