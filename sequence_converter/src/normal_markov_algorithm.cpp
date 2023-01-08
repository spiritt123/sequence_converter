#include "normal_markov_algorithm.h"
#include <algorithm>
#include <iostream>
#include <regex>

NMA::NMA()
{
    _rules.resize(100, " ");
}

NMA::~NMA() {}

void NMA::addRule(uint32_t number_of_rule, const std::string& rule)
{
    --number_of_rule; // correct index user->programm
    if (_rules[number_of_rule] == " ")
    {
        _rules[number_of_rule] = rule;
    }
    else
    {
        _rules.insert(_rules.begin() + number_of_rule, rule);
    }
}

void NMA::removeRule(uint32_t number_of_rule)
{
    _rules.erase(_rules.begin() + number_of_rule - 1);
}

const std::vector<std::string>& NMA::getRules() const
{
    return _rules;
}

nma::STATUS NMA::calculate(std::string& tape)
{
    std::string buffer;
    nma::STATUS status = nma::STATUS::Wait;
    for (const auto& rule : _rules)
    {
        buffer = rule.substr(0, rule.find("->"));
        if (buffer.back() == '|')
        {
            status = nma::STATUS::Success;
            buffer.pop_back();
        }
        
        if (tape.find(buffer) != std::string::npos)
        {
            std::string replace_str = rule.substr(rule.find(">") + 1, rule.length() - rule.find(">"));
            tape.replace(tape.find(buffer), buffer.size(), replace_str);
            return status;
        }
    }
    return (status = nma::STATUS::Error);
}

