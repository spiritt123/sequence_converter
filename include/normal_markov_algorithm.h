#pragma once

#include <vector>
#include <string>

namespace nma
{
    enum STATUS
    {
        Wait = 0, 
        Success,
        Error
    };
}

class NMA
{
public:
    NMA();
    ~NMA();

    void addRule(uint32_t number_of_rule, const std::string& rule);
    void removeRule(uint32_t number_of_rule);
    const std::vector<std::string>& getRules() const;

    nma::STATUS calculate(std::string& tape);

private:
    std::vector<std::string> _rules;
};

