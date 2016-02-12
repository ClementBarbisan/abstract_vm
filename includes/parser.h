//
// Created by Clement BARBISAN on 30/11/15.
//

#ifndef ABSTRACT_VM_parser_H
#define ABSTRACT_VM_parser_H

#include <map>
#include <string>
#include <regex>
#include "stack.h"

std::string    commands[11] =
{
    "push",
    "pop",
    "dump",
    "assert",
    "add",
    "sub",
    "mul",
    "div",
    "mod",
    "print",
    "exit"
};

class parser 
{
    private:
        int _countLine;
		Stack  *_stack;
        std::map<std::string, std::regex> _commands;
        void _incrementCountLine();
		bool _addFunctionToStack(std::string const name);
    public:
        parser(void);
        parser(Stack *stack);
        ~parser(void);
        parser(parser const &);
        parser const & operator=(parser const &);
        void addCommand(std::string const name, std::string const regex);
        bool checkLine(std::string const line);
        std::map<std::string, std::regex> const & getCommands() const;
		Stack *getFunctions() const;
		int getCountLine() const;
};

#endif
