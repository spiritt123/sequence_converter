#pragma once

#include <vector>
#include <string>

class TuringMachine
{
public:
    TuringMachine();
    ~TuringMachine();

    void addRule(const std::string& rule);
    void removeRule(const std::string& rule);
    const std::vector<std::string>& getRules() const;

    bool calculate();
    void setPointer(int pointer);
    int getPointer() const;
    void setState(uint32_t state);
    uint32_t getState() const;
    void setTape(const std::string& tape);
    const std::string& getTape() const;

private:
    std::vector<std::string> _rules;
    int _pointer;
    uint32_t _state;
    std::string _tape;

};

