/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:20:54 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/01 18:22:31 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>

Stack::Stack()
{
}

Stack::Stack(Commands * commands)
{
	this->_commands = commands;
}

Stack::Stack(Stack const & src)
{
	*this = src;
}

Stack const & Stack::operator=(Stack const & src)
{
	this->_stack = src.getStack();
	this->_commands = src.getCommands();
	return(*this);
}

Stack::~Stack()
{
	return;
}

std::multimap<std::string, std::string, std::string> Stack::getStack() const
{
	return(this->_stack);
}

Commands *Stack::getCommands() const
{
	return(this->_commands);
}

void Stack::setCommands(Commands *commands)
{
	this->_commands = commands;
}

bool Stack::addFunctionToStack(std::string const name)
{
	std::string *functions = new std::string[3];
	functions[0] = name;
	functions[1] = name;
	functions[2] = name;
	return(true);
}

bool Stack::unstack()
{
	return(true);
}
