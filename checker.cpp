/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:21:38 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/01 16:15:18 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <checker.h>
#include <iostream>

Checker::Checker()
{
	this->_countLine = 0;
	this->_stack = new Stack();
}

Checker::Checker(Stack *stack)
{
    this->_countLine = 0;
	this->_stack = stack;
}

Checker::Checker(Checker const & src)
{
    *this = src;
}

Checker::~Checker()
{
    return;
}

Checker const & Checker::operator=(Checker const & src)
{
    this->_countLine = src.getCountLine();
    this->_commands = src.getCommands();
	this->_stack = src.getFunctions();
    return(*this);
}

Stack *Checker::getFunctions() const
{
	return (this->_stack);
}

void    Checker::addCommand(const std::string name, const std::string regex)
{
    std::regex reg(regex);
    std::cout << regex << std::endl;
    this->_commands[name] = reg;
}

void    Checker::_incrementCountLine()
{
    this->_countLine++;
}

bool Checker::_addFunctionToStack(std::string const name)
{
	return(this->_stack->addFunctionToStack(name));
}

int Checker::getCountLine() const
{
    return(this->_countLine);
}

std::map<std::string, std::regex> const & Checker::getCommands() const
{
    return (this->_commands);
};

bool  Checker::checkLine(std::string line)
{
    std::map<std::string, std::regex>::iterator it;
    for (it = this->_commands.begin(); it != this->_commands.end(); it++)
    {
        if (line.find(it->first) != std::string::npos)
        {
            std::string replace = std::regex_replace(line, it->second, "");
            if (replace == "" || replace[0] == ';')
			{
                this->_addFunctionToStack(line);
				return(true);
			}
			else
                return(false);
        }
    }
    return(false);
}
