/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:21:38 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/01 16:15:18 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <stack.h>
#include <iostream>

parser::parser()
{
	this->_countLine = 0;
	this->_stack = new Stack();
}

parser::parser(Stack *stack)
{
    this->_countLine = 0;
	this->_stack = stack;
}

parser::parser(parser const & src)
{
    *this = src;
}

parser::~parser()
{
    return;
}

parser const & parser::operator=(parser const & src)
{
    this->_countLine = src.getCountLine();
    this->_commands = src.getCommands();
	this->_stack = src.getFunctions();
    return(*this);
}

Stack *parser::getFunctions() const
{
	return (this->_stack);
}

void    parser::addCommand(const std::string name, const std::string regex)
{
    std::regex reg(regex);
    std::cout << regex << std::endl;
    this->_commands[name] = reg;
}

void    parser::_incrementCountLine()
{
    this->_countLine++;
}

bool parser::_addFunctionToStack(std::string const name)
{
	return(this->_stack->addFunctionToStack(name));
}

int parser::getCountLine() const
{
    return(this->_countLine);
}

std::map<std::string, std::regex> const & parser::getCommands() const
{
    return (this->_commands);
};

bool  parser::checkLine(std::string line)
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
