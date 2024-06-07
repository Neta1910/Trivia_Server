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

	double calculateRating() const {
		const double W_CAC = 1.0; // Weight for Correct Answer Count
		const double W_WAC = 1.0; // Weight for Wrong Answer Count
		const double W_AAT = 0.5; // Weight for Average Answer Time

		// Calculate rating
		double rating = W_CAC * correctAnswerCount - W_WAC * wrongAnswerCount + W_AAT * (1.0 / averageAnswerTime);

		return rating;
	}

	bool operator<(PlayerResults& other) {
		return this->calculateRating() < other.calculateRating();
	}
};