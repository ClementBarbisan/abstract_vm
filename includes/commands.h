/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:36:44 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/15 15:39:58 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_COMMANDS_H
#define ABSTRACT_VM_COMMANDS_H

#include <functional>
#include <stack>
#include <map>
#include <string>

class Commands
{
	private:
		typedef std::function<void(void)> ptrFunc;
		std::map<std::string, ptrFunc> *_mapFunc;
		std::stack<double> *_stackValue;
	public:
		int8_t int8Nb(int8_t nb);
		int16_t int16Nb(int16_t nb);
		int32_t int32Nb(int32_t nb);
		float floatNb(float nb);
		double doubleNb(double nb);
		bool push(double nb);
		bool assert(double nb);
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
		Commands(std::stack<std::string> & stack);
		Commands(Commands const &);
		Commands const & operator=(Commands const &);
		~Commands(void);
};

#endif
