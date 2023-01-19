#pragma once

#include <string>

namespace bf
{
    enum STATUS
    {
        Wait = 0, 
        Success,
        InputChar,
        OutputChar
    };
    enum STATUS_CODE
    {
        Correctly = 0,
        OpenBracketNestingError,
        CloseBracketNestingError
    };
}
class Brainfuck
{
public:
    Brainfuck();
    ~Brainfuck();

    bf::STATUS_CODE setCode(std::string code);
    bf::STATUS calculate();
    void setChar(char ch);
    char getChar();
    void setPointer(int pointer);
    int getPointer() const;
    void clearMemory();
    
    uint32_t getMemorySize();
    const char* getMemory();

private:
    int _pointer;
    int _index;
    char *_memory;
    uint32_t _memory_size;
    std::string _code;
};

