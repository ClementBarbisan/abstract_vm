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
