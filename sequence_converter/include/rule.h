#pragma once

#include <string>
#include <cstdlib>

class Rule
{
public:
    Rule() = delete;
    Rule(std::string line);
    Rule(const Rule &rule);
    Rule& operator=(const Rule& right);

    friend bool operator==(const Rule &left, const Rule &right);

    char getCurrentSymbol() const;
    unsigned int getCurrentState() const;
    char getNextSymbol() const;
    unsigned int getNextState() const;
    char getMove() const;
    std::string getLine() const;

private:
    char _current_symbol;
    unsigned int _current_state;
    char _next_symbol;
    unsigned int _next_state;
    char _move;
    std::string _line;
};


