//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_EMAIL_ADDRESS_H
#define OOP_EMAIL_ADDRESS_H
#include <string>
#include "base_exception.h"
#include "nlohmann/json.hpp"

class invalid_email_at : public base_exception {
public:
    explicit invalid_email_at(std::string const &email)
        : base_exception("invalid_email_at", email + " has an illegal format for '@'!") {
    }
};

class invalid_email_dot : public base_exception {
public:
    explicit invalid_email_dot(std::string const &email)
        : base_exception("invalid_email_dot", email + " has an illegal format for '.'!") {
    }
};

class invalid_email_spaces : public base_exception {
public:
    explicit invalid_email_spaces(std::string const &email)
        : base_exception("invalid_email_spaces", email + " has an illegal format for ' '!") {
    }
};


class email_address_t {
protected:
    std::string value;

public:
    email_address_t() = default;

    explicit email_address_t(const std::string &value) {
        this->value = value;
        const size_t at_pos = this->value.find('@');
        // Email must have only one '@'
        // Not start with '@'
        if (
            at_pos == std::string::npos ||
            at_pos == 0 ||
            value.find('@', at_pos + 1) != std::string::npos) {
            throw invalid_email_at(value);
        }

        // Dot must not be exactly after '@' or end of email
        if (const size_t dot_pos = this->value.find('.', at_pos + 1);
            dot_pos == std::string::npos || dot_pos == at_pos + 1 || dot_pos == this->value.length() - 1) {
            throw invalid_email_dot(value);
        }

        // No spaces allowed
        if (this->value.find(' ') != std::string::npos) {
            throw invalid_email_spaces(this->value);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const email_address_t &email);

    friend void to_json(nlohmann::json &j, const email_address_t &e);
    friend void from_json(const nlohmann::json &j, email_address_t &e);
};


#endif //OOP_EMAIL_ADDRESS_H
