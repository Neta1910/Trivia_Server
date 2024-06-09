#pragma once
#include <string>
#include <iostream>
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
		double rating = (correctAnswerCount) / (wrongAnswerCount + averageAnswerTime);

		return rating;
	}

	bool operator<(PlayerResults& other) {
		return this->calculateRating() < other.calculateRating();
	}
};