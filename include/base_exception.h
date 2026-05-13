//
// Created by Antonie Gabriel Belu on 16.03.2026.
//

#ifndef OOP_BASE_EXCEPTION_H
#define OOP_BASE_EXCEPTION_H
#include <string>


class base_exception : public std::exception {
protected:
    std::string message;
public:
    explicit base_exception(
        std::string from,
        std::string message) {
        this->message = "[" + std::move(from) + "] " + std::move(message);
    }

    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
};


#endif //OOP_BASE_EXCEPTION_H