#include "rule.h"




Rule::Rule(std::string line)
{
    if (sscanf(line.c_str(), 
               "%cq%d->%cq%d%c", 
               &_current_symbol, 
               &_current_state, 
               &_next_symbol, 
               &_next_state, 
               &_move) < 5)
    {
        throw "Uncorrect state or symbol";
    }

    if (_move != 'L' && _move != 'R' && _move != 'S')
    {
        throw "Uncorrect move(expected L or R or S)";
    }
    _line = line;
}


Rule::Rule(const Rule &rule)
{
    _current_state = rule.getCurrentState();
    _current_symbol = rule.getCurrentSymbol();
    _next_state = rule.getNextState();
    _next_symbol = rule.getNextSymbol();
    _move = rule.getMove();
    _line = rule.getLine();
}

Rule& Rule::operator=(const Rule& right)
{
    if (this == &right)
    {
        return *this;
    }
    Rule(right.getLine());
    return *this;
}

bool operator==(const Rule &left, const Rule &right)
{
    return (left.getCurrentSymbol() == right.getCurrentSymbol() &&
            left.getCurrentState() == right.getCurrentState());
}

char Rule::getCurrentSymbol() const
{
    return _current_symbol;
}

unsigned int Rule::getCurrentState() const
{
    return _current_state;
}

char Rule::getNextSymbol() const
{
    return _next_symbol;
}

unsigned int Rule::getNextState() const
{
    return _next_state;
}

std::string Rule::getLine() const
{
    return _line;
}

char Rule::getMove() const
{
    return _move;
}

