#include "User.h"
User::User(const int& id, const std::string& name, const std::string& password, const std::string& email) :
	_id(id), _userName(name), _password(password), _email(email)
{
}

// Getter implementations
const std::string& User::getName() const {
    return _userName;
}

const std::string& User::getPassword() const {
    return _password;
}

const std::string& User::getEmail() const {
    return _email;
}

int User::getId() const
{
    return this->_id;
}

// Setter implementations
void User::setName(const std::string& name) {
    _userName = name;
}

void User::setPassword(const std::string& password) {
    _password = password;
}

void User::setEmail(const std::string& email) {
    _email = email;
}

void User::setId(const int& id)
{
    this->_id = id;
}
