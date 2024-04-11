#include "Quistion.h"

Question::Question(const std::string& question, const std::vector<std::string>& possibleAnsowers, const std::string& correctAnsower) :
    m_correctAnswer(correctAnsower), m_possibleAnswers(possibleAnsowers), m_question(question)
{
}

Question::Question()
{
}

std::string Question::getQuestion() const
{
    return this->m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
    return this->m_possibleAnswers;
}

std::string Question::getCorrectAnswer() const
{
    return this->m_correctAnswer;
}
