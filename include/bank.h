//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_BANK_H
#define OOP_BANK_H
#include <string>
#include "client.h"
#include <vector>
#include "nlohmann/json.hpp"
#include <fstream>

class invalid_bank_name : public base_exception {
public:
    explicit invalid_bank_name(std::string const & name)
        : base_exception("invalid_bank_name", name + " has too short of a length.") {}
};


class bank_t {
protected:
    std::string name;
    std::vector<client_t> clients;

    [[nodiscard]] std::string get_filepath() const;
public:
    // plange json daca nu exista
    bank_t(const bank_t& other) = default;

    bank_t() : name("<change_bank_name>") {}
    explicit bank_t(std::string name) : name(std::move(name)) {
        if (this->name.length() < 3)
            throw invalid_bank_name(this->name);
    }

    bank_t(
        std::string name,
        const std::vector<client_t>& clients) : name(std::move(name)),
                                                clients(clients) {
        if (this->name.length() < 3)
            throw invalid_bank_name(this->name);
    }

    [[nodiscard]] std::string get_identifier() const;
    [[nodiscard]] size_t client_count() const;

    void add_client(const client_t& client);
    void remove_client(size_t index);

    bank_t& operator=(const bank_t& other);
    friend std::ostream& operator<<(std::ostream& os, const bank_t& bank);

    // JSON Related Save + Load
    void save() const;
    static bank_t load(const std::string& filepath);

    ~bank_t() = default;
};


#endif //OOP_BANK_H