//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_CLIENT_H
#define OOP_CLIENT_H

#include <nlohmann/json.hpp>
#include <string>

#include "email_address.h"
#include "personl_information.h"
#include "phone_number.h"

class client_t {
protected:
    personl_information_t personal_information;

public:
    client_t() = default;
    client_t(const client_t &other) = default;

    client_t(std::string first_name,
                std::string last_name,
                std::string street_name,
                std::string city,
                std::string state,
                std::string postal_code,
                const std::string &email,
                const std::string &phone_number) : personal_information(
                                            std::move(first_name), std::move(last_name),
                                                        address_t(
                                                            std::move(street_name),
                                                            std::move(postal_code),
                                                            std::move(city),
                                                            std::move(state)),
                                                        phone_number_t(phone_number),
                                                        email_address_t(email)) {}

    client_t(client_t &&other) noexcept : personal_information(std::move(other.personal_information)) {}

    client_t &operator=(const client_t &other) = default;
    client_t &operator=(client_t &&other) noexcept {
        if (this != &other)
            personal_information = std::move(other.personal_information);

        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const client_t &client);

    friend void to_json(nlohmann::json &j, const client_t &c);
    friend void from_json(const nlohmann::json &j, client_t &c);
    ~client_t() = default;
};

#endif // OOP_CLIENT_H
