#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question(const std::string& question, const std::vector<std::string>& possibeleAnsowers, const std::string& correctAnsower);
	Question();
	std::string getQuestion() const;
	std::vector <std::string> getPossibleAnswers() const;
	std::string getCorrectAnswer() const;

	std::string setQuestion(const std::string& val);
	std::vector <std::string> setPossibleAnswers(const std::string& val);
	std::string setCorrectAnswer(const std::string& val);

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	std::string m_correctAnswer;
};