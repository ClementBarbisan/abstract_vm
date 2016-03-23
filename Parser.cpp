/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:21:38 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/01 16:15:18 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Parser.h>
#include <queueFunctions.h>
#include <iostream>

Parser::Parser()
{
	this->_countLine = 0;
	this->_queue = new Queue();
}

Parser::Parser(Queue *queue)
{
    this->_countLine = 0;
	this->_queue = queue;
}

Parser::Parser(Parser const & src)
{
    *this = src;
}

Parser::~Parser()
{
    return;
}

Parser const & Parser::operator=(Parser const & src)
{
    this->_countLine = src.getCountLine();
    this->_commands = src.getCommands();
	this->_queue = src.getFunctions();
    return(*this);
}

Queue *Parser::getFunctions() const
{
	return (this->_queue);
}

void    Parser::addCommand(const std::string name, const std::string regex)
{
    std::regex reg(regex);
    std::cout << regex << std::endl;
    this->_commands[name] = reg;
}

void    Parser::_incrementCountLine()
{
    this->_countLine++;
}

bool Parser::_addFunctionToQueue(std::string const name)
{
	return(this->_queue->addFunctionToQueue(name));
}

int Parser::getCountLine() const
{
    return(this->_countLine);
}

std::map<std::string, std::regex> const & Parser::getCommands() const
{
    return (this->_commands);
};

bool  Parser::checkLine(std::string line)
{
    std::map<std::string, std::regex>::iterator it;
    for (it = this->_commands.begin(); it != this->_commands.end(); it++)
    {
        if (line.find(it->first) != std::string::npos)
        {
            std::string replace = std::regex_replace(line, it->second, "");
            if (replace == "" || replace[0] == ';')
			{
                this->_addFunctionToQueue(line);
				return(true);
			}
			else
                return(false);
        }
    }
    return(false);
}
