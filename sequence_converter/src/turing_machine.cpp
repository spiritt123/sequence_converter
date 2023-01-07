#include "turing_machine.h"
#include <algorithm>
#include <iostream>

TuringMachine::TuringMachine()
{
    _pointer = 0;
    _state = 0;
    _tape = "0";
}

TuringMachine::~TuringMachine() {}

void TuringMachine::addRule(const std::string& rule)
{
    //rule is correct!!!!
    std::string left = rule.substr(0, rule.find("->"));
    auto exist_rule = std::find_if (_rules.begin(), _rules.end(), 
                [left](const std::string& str) -> bool { 
                    return str.find(left) != std::string::npos; 
                });
    if (exist_rule != _rules.end())
    {
        *exist_rule = rule;
    }
    else
    {
        _rules.push_back(rule);
    }
}

void TuringMachine::removeRule(const std::string& rule)
{
    _rules.erase(std::remove(_rules.begin(), _rules.end(), rule), _rules.end());
    ///!!!!!
}

const std::vector<std::string>& TuringMachine::getRules() const
{
    return _rules;
}

bool TuringMachine::calculate()
{
    if (_tape.length() == _pointer)
    {
        _tape += "0";
    }  
    std::string left = std::to_string(_tape[_pointer] - '0') 
                     + "q" 
                     + std::to_string(_state)
                     + "->";    
    auto rule = std::find_if (_rules.begin(), _rules.end(), 
                [left](const std::string& str) -> bool { 
                    return str.find(left) != std::string::npos; 
                });
    if (rule == _rules.end())
    {
        return false; //error
    }
    std::string right = *rule;
    char move = right[right.length() - 1];
    right = right.substr(right.find(">") + 1, right.length() - right.find(">") - 1);
    _tape[_pointer] = right[0];
    _state = stoi(right.substr(2, right.length() - 2));

    if (move == 'L')
        --_pointer;
    else if (move == 'R')
        ++_pointer;

    return true; //success
}

void TuringMachine::setPointer(int pointer)
{
    _pointer = pointer;
}

int TuringMachine::getPointer() const
{
    return _pointer;
}

void TuringMachine::setState(uint32_t state)
{
    _state = state;
}

uint32_t TuringMachine::getState() const
{
    return _state;
}

void TuringMachine::setTape(const std::string& tape)
{
    _tape = tape;
}

const std::string& TuringMachine::getTape() const
{
    return _tape;
}



