#include "brainfuck.h"
#include <algorithm>
#include <iostream>

Brainfuck::Brainfuck()
{
    _pointer = 0;
    _memory_size = 3000;
    _memory = (char*)calloc(_memory_size, sizeof(char));
}

Brainfuck::~Brainfuck() 
{
    free(_memory);
}

bf::STATUS_CODE Brainfuck::setCode(std::string code)
{
    int count = 0;
    for (int i = 0; i < code.length(); ++i)
    {
        if (code[i] == '[') ++count;
        if (code[i] == ']') --count;
        if (count < 0) return bf::STATUS_CODE::CloseBracketNestingError;
    }
    if (count != 0) return bf::STATUS_CODE::OpenBracketNestingError;

    _code = code;    
    _index = 0;
    return bf::STATUS_CODE::Correctly;
}

bf::STATUS Brainfuck::calculate()
{
    if (_index >= _code.length())
    {
        return bf::STATUS::Success;
    }

    int count = 0; //count of brackets
    switch (_code[_index])
    {
    case '>':
        ++_pointer;
        _pointer %= _memory_size;
        break;
    case '<':
        --_pointer;
        _pointer %= _memory_size;
        break;
    case '+':
        ++_memory[_pointer];
        break;
    case '-':
        --_memory[_pointer];
        break;
    case '[':
        break;
    case ']':
        if (_memory[_pointer] == 0) break;
        while (1)
        //while ( !(_code[_index] == '[' && count == 0) )
        {
            --_index;
            if (_code[_index] == '[' && count == 0) break;
            if (_code[_index] == ']') ++count;
            if (_code[_index] == '[') --count;
        }
        break;
    case '.':
        ++_index;
        return bf::STATUS::OutputChar;
    case ',':
        ++_index;
        return bf::STATUS::InputChar;
    }
    ++_index;
    return bf::STATUS::Wait;
}

void Brainfuck::setChar(char ch)
{
    _memory[_pointer] = ch;
}

char Brainfuck::getChar()
{
    return _memory[_pointer];
}

void Brainfuck::setPointer(int pointer)
{
    _pointer = pointer;
}

int Brainfuck::getPointer() const
{
    return _pointer;
}

void Brainfuck::clearMemory()
{
    for (int i = 0; i < _memory_size; ++i)
    {
        _memory[i] = 0;
    } 
}

uint32_t Brainfuck::getMemorySize()
{
    return _memory_size;
}

const char* Brainfuck::getMemory()
{
    return _memory;
}



