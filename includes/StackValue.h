#ifndef ABSTRACT_VM_STACK_H
#define ABSTRACT_VM_STACK_H

#include <list>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>

class IOperand;

class Stack
{
	private:
		std::list<IOperand const *> *_stack;
	public:
		Stack(void);
		Stack(Stack const &);
		Stack const & operator=(Stack const &);
		~Stack(void);
		std::list<IOperand const *> & getStack(void) const;
		void addValueToStack(IOperand const * value);
		void unstack(void);
};

#endif
