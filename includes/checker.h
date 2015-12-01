//
// Created by Clement BARBISAN on 30/11/15.
//

#ifndef ABSTRACT_VM_CHECKER_H
#define ABSTRACT_VM_CHECKER_H

#include <map>
#include <string>
#include <regex>
#include <stack.h>

class Checker 
{
    private:
        int _countLine;
		Stack  *_stack;
        std::map<std::string, std::regex> _commands;
        void _incrementCountLine();
		bool _addFunctionToStack(std::string const name);
    public:
        Checker(void);
        Checker(Stack *stack);
        ~Checker(void);
        Checker(Checker const &);
        Checker const & operator=(Checker const &);
        void addCommand(std::string const name, std::string const regex);
        bool checkLine(std::string const line);
        std::map<std::string, std::regex> const & getCommands() const;
		Stack *getFunctions() const;
		int getCountLine() const;
};

#endif
