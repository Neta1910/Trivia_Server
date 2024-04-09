#include "Quistion.h"

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
