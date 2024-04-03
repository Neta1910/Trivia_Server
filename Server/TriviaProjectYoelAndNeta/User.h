#pragma once
#include "pch.h"

class User
{
public:
	User(const int& id, const std::string& name, const std::string& password, const std::string& email );

    // Getters
    const std::string& getName() const;
    const std::string& getPassword() const;
    const std::string& getEmail() const;
    int getId() const;

    // Setters
    void setName(const std::string& name);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);
    void setId(const int& id);

private:
	std::string _userName;
	std::string _password;
	std::string _email;
    int _id;
};