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
