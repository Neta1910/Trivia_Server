#pragma once
#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <sstream> // Include for std::ostringstream
#include <string>  // Include for std::string

typedef struct PlayerResults
{
public:
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
	unsigned int gamesPlayed;
	unsigned int user_id;

    double calculateRating() const {
        // Calculate rating
        double rating = (1.00 * correctAnswerCount) / (wrongAnswerCount + averageAnswerTime);

        // Use a string stream to format the rating to 2 decimal places
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << rating;
        std::string formattedRatingStr = stream.str();

        // Convert the formatted string back to a double
        double formattedRating = std::stod(formattedRatingStr);

        return formattedRating;
    }

	bool operator<(PlayerResults& other) {
		return this->calculateRating() < other.calculateRating();
	}
};