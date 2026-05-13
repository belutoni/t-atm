//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#include "../include/bank.h"

std::string bank_t::get_filepath() const {
    return "assets/" + get_identifier() + ".json";
}

bank_t& bank_t::operator=(const bank_t& other) {
    if (this != &other) {
        name = other.name;
        clients = other.clients;
    }

    return *this;
}

void bank_t::add_client(const client_t& client) {
    clients.push_back(client);
}

void bank_t::remove_client(const size_t index) {
    if (index >= clients.size())
        return;

    clients.erase(clients.begin() + static_cast<long>(index));
}

size_t bank_t::client_count() const {
    return clients.size();
}

void bank_t::save() const {
    nlohmann::json j;
    j["bank_name"] = name;
    j["clients"] = clients;

    std::ofstream file(get_filepath());
    file << j.dump(4);
}

bank_t bank_t::load(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("could not open " + filepath);

    nlohmann::json j = nlohmann::json::parse(file);
    bank_t bank;
    bank.name = j.at("bank_name").get<std::string>();
    bank.clients = j.at("clients").get<std::vector<client_t>>();

    return bank;
}

std::string bank_t::get_identifier() const {
    std::string identifier = this->name;
    std::erase_if(identifier, isspace);
    // smart pants
    std::ranges::transform(identifier.begin(), identifier.end(), identifier.begin(), [](const char c) { return std::tolower(c); });

    return identifier.substr(0, 3);
}

std::ostream& operator<<(std::ostream& os, const bank_t& bank) {
    os << "bank: " << bank.name << " (" << bank.clients.size() << " clients)\n";
    for (size_t i = 0; i < bank.clients.size(); i++)
        os << "[" << i << "] " << bank.clients[i] << "\n";

    return os;
}