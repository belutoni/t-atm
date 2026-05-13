//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#include "../include/personl_information.h"

std::ostream &operator<<(std::ostream &os, const personl_information_t &pi) {
    os << "first_name: " << pi.first_name << '\n'
            << "last_name: " << pi.last_name << '\n'
            << "phone_number: " << pi.phone << '\n'
            << "email: " << pi.email << '\n'
            << "address: " << pi.address << '\n';

    return os;
}

void to_json(nlohmann::json &j, const personl_information_t &pi) {
    j = nlohmann::json{
        {"first_name", pi.first_name},
        {"last_name", pi.last_name},
        {"phone", pi.phone},
        {"email", pi.email},
        {"address", pi.address}
    };
}

void from_json(const nlohmann::json &j, personl_information_t &pi) {
    j.at("first_name").get_to(pi.first_name);
    j.at("last_name").get_to(pi.last_name);
    j.at("phone").get_to(pi.phone);
    j.at("email").get_to(pi.email);
    j.at("address").get_to(pi.address);
}
