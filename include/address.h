//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_ADDRESS_H
#define OOP_ADDRESS_H
#include <string>

#include "nlohmann/json.hpp"

class address_t {
protected:
    std::string street_name;
    std::string postal_code;
    std::string city;
    std::string state;
public:
    address_t() = default;
    address_t(
        std::string street_name,
        std::string postal_code,
        std::string city,
        std::string state) :   street_name(std::move(street_name)),
                                postal_code(std::move(postal_code)),
                                city(std::move(city)),
                                state(std::move(state)) {}

    [[nodiscard]] std::string get_address_line() const;

    friend std::ostream &operator<<(std::ostream &os, const address_t &email);

    // JSON
    friend void to_json(nlohmann::json &j, const address_t &a);
    friend void from_json(const nlohmann::json &j, address_t &a);
};


#endif //OOP_ADDRESS_H
