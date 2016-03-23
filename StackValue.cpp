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

#include <StackValue.h>
#include <IOperand.h>

Stack::Stack()
{
	this->_stack = new std::list<IOperand const *>;
}

Stack::Stack(Stack const & src)
{
	*this = src;
}

Stack const & Stack::operator=(Stack const & src)
{
	this->_stack = &src.getStack();
	return(*this);
}

Stack::~Stack()
{
	return;
}

std::list<IOperand const *> & Stack::getStack() const
{
	return(*this->_stack);
}

void Stack::addValueToStack(IOperand const * value)
{
	this->_stack->push_front(value);
}

void Stack::unstack()
{
    if (!_stack->empty())
        _stack->pop_front();
}
