//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_PERSONL_INFORMATION_H
#define OOP_PERSONL_INFORMATION_H

#include <string>
#include <ostream>

#include "address.h"
#include "email_address.h"
#include "phone_number.h"
#include "nlohmann/json.hpp"

class personl_information_t {
protected:
    std::string first_name;
    std::string last_name;
    phone_number_t phone;
    email_address_t email;
    address_t address;

public:
    personl_information_t() = default;

    personl_information_t(
        std::string first_name,
        std::string last_name,
        address_t address,
        phone_number_t phone,
        email_address_t email)
        : first_name(std::move(first_name)),
          last_name(std::move(last_name)),
          phone(std::move(phone)),
          email(std::move(email)),
          address(std::move(address)) {}

    friend std::ostream &operator<<(std::ostream &os, const personl_information_t &pi);

    friend void to_json(nlohmann::json &j, const personl_information_t &pi);
    friend void from_json(const nlohmann::json &j, personl_information_t &pi);
};


#endif //OOP_PERSONL_INFORMATION_H
