/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:36:44 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/15 16:12:14 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_COMMANDS_H
#define ABSTRACT_VM_COMMANDS_H

#include <functional>
#include <stack>
#include <map>
#include <string>
#include <IOperand.h>

class Commands
{
	private:
		typedef std::function<void(void)> ptrFunc;
		std::map<std::string, ptrFunc> *_mapFunc;
		std::stack<double> *_stackValue;
	public:
		IOperand int8Nb(IOperand value);
		IOperand int16Nb(IOperand value);
		IOperand int32Nb(IOperand value);
		IOperand floatNb(IOperand value);
		IOperand doubleNb(IOperand value);
		bool push(IOperand value);
		bool assert(IOperand value);
		bool pop(void);
		bool dump(void);
		bool add(void);
		bool sub(void);
		bool mul(void);
		bool div(void);
		bool mod(void);
		bool print(void);
		bool exit(void);
		bool executeCommand(std::string name);
		std::stack<double> & getStackValue(void);
		std::map<std::string, ptrFunc> & getMap(void);
		Commands(void);
		Commands(Commands const &);
		Commands const & operator=(Commands const &);
		~Commands(void);
};

#endif
