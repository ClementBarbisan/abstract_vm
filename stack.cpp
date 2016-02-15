/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:20:54 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/15 15:34:36 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

Stack::Stack()
{
	this->_stack = new std::vector< std::vector<std::string> >;
}

Stack::Stack(Commands * commands)
{
	this->_stack = new std::vector< std::vector<std::string> >;
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

std::vector< std::vector<std::string> > *Stack::getStack() const
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
	std::vector<std::string> functions;
	functions.push_back(name);
	functions.push_back(name);
	functions.push_back(name);
	this->_stack->push_back(functions);
	return(true);
}

bool Stack::unstack()
{
	return(true);
}
