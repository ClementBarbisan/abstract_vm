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
        typedef IOperand const *(OperandFactory::*funcOperand)(std::string const &) const;
		OperandFactory();
		~OperandFactory();
        std::map<IOperand::eOperandType, funcOperand> const & getMapOperand() const;
		IOperand const * createOperand(IOperand::eOperandType type, std::string const & value) const;
	private:
        OperandFactory(OperandFactory const & cp);
        OperandFactory & operator=(OperandFactory const & cp);
		std::map<IOperand::eOperandType, funcOperand> mapOperand;
		IOperand const * createInt8(std::string const & value) const;
		IOperand const * createInt16(std::string const & value) const;
		IOperand const * createInt32(std::string const & value) const;
		IOperand const * createFloat(std::string const & value) const;
		IOperand const * createDouble(std::string const & value) const;
	
};

#endif
