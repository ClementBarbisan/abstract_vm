/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 10:27:41 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/01 18:11:04 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_STACK_H
#define ABSTRACT_VM_STACK_H

#include <stack>
#include <string>
#include <commands.h>
#include <iterator>
#include <sstream>
#include <iostream>

class Stack
{
	private:
		std::multimap<std::string, std::string, std::string> _stack;
		Commands *_commands;
	public:
		Stack(void);
		Stack(Commands * commands);
		Stack(Stack const &);
		Stack const & operator=(Stack const &);
		~Stack(void);
		std::multimap<std::string, std::string, std::string> getStack(void) const;
		Commands *getCommands(void) const;
		void setCommands(Commands *commands);
		bool addFunctionToStack(std::string const name);
		bool unstack(void);
};

#endif
