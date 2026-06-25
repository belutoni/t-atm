#include "atm_cli.h"
#include <iostream>

int main() {
    try {
        atm_cli_t cli;
        cli.start();
    } catch (const std::exception& e) {
        std::cerr << "it crapped somewhere: " << e.what() << "\n";
        return 1;
    }

    return 0;
}