#include "userCheckers.h"
#define MIN_PASSWORD_SIZE 8

bool UserCheckers::checkPassword(const std::string& password)
{
    // checking password is at least 8
    if (password.length() < MIN_PASSWORD_SIZE)
    {
        return false;
    }
    // checking if password has a capitel letter
    if (!std::regex_search(password, std::regex("[A-Z]")))
    {
        return false;
    }
    // checking if password has a small letter
    if (!std::regex_search(password, std::regex("[a-z]")))
    {
        return false;
    }
    // checking if password has a number
    if (!std::regex_search(password, std::regex("[0-9]")))
    {
        return false;
    }
}

bool UserCheckers::checkEmail(const std::string& email)
{
    std::regex pattern("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");

    return std::regex_match(email, pattern);
}

bool UserCheckers::checkAddress(const std::string& address)
{
    // Regular expression pattern for the address template
    std::regex pattern("[a-zA-Z]+,\\s[0-9]+,\\s[a-zA-Z]+");

    return std::regex_match(address, pattern);
}
