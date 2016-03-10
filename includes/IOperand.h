//
//  IOperand.h
//  abstract_vm
//
//  Created by Clement BARBISAN on 2/9/16.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#ifndef IOperand_h
#define IOperand_h

#include <string>

class IOperand {
	public:
	typedef enum    eOperandType
	{
		INT8,
		INT16,
		INT32,
		DOUBLE,
		FLOAT
	}				eOperandType;
		virtual int getPrecision() const = 0;
		virtual eOperandType getType() const = 0;
		virtual IOperand const * operator+(IOperand const & rhs) const = 0;
		virtual IOperand const * operator-(IOperand const & rhs) const = 0;
		virtual IOperand const * operator*(IOperand const & rhs) const = 0;
		virtual IOperand const * operator/(IOperand const & rhs) const = 0;
		virtual IOperand const * operator%(IOperand const & rhs) const = 0;
		virtual std::string const & toString() const = 0;
		virtual ~IOperand() {}
};

#endif /* IOperand_h */
