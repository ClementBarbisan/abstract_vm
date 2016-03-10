//
//  OperandFactory.h
//  abstract_vm
//
//  Created by ClémentBarbisan on 09/03/2016.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#ifndef OperandFactory_h
#define OperandFactory_h

#include <stdio.h>
#include <IOperand.h>
#include <map>

class OperandFactory
{
	public:
		OperandFactory();
		~OperandFactory();
		IOperand const * createOperand(IOperand::eOperandType type, std::string const & value) const;
	private:
		OperandFactory(OperandFactory const & cp);
		OperandFactory & operator=(OperandFactory const & cp);
		std::map<IOperand::eOperandType, IOperand const *(*)(std::string const &)> mapOperand;
		IOperand const * createInt8(std::string const & value) const;
		IOperand const * createInt16(std::string const & value) const;
		IOperand const * createInt32(std::string const & value) const;
		IOperand const * createIntFloat(std::string const & value) const;
		IOperand const * createIntDouble(std::string const & value) const;
	
};

#endif
