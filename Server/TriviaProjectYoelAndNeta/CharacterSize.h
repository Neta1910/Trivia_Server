#pragma once
#include <iostream>
#include <unordered_map>

enum class Character_size
{
    kSmall,
    kMedium,
    kLarge
};

std::unordered_map<Character_size, std::string> character_size_to_string({
    {Character_size::kSmall, "small"},
    {Character_size::kMedium, "medium"},
    {Character_size::kLarge, "large"}  
});