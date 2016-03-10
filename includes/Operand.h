//
//  Operand.h
//  abstract_vm
//
//  Created by ClémentBarbisan on 09/03/2016.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#ifndef Operand_h
#define Operand_h

#include <stdio.h>
#include <string>
#include <IOperand.h>
#include <exception>

template <typename T>
class Operand : public IOperand
{
	private:
		Operand();
		eOperandType	_type;
		T				_value;
	public:
		Operand(eOperandType type, T value)
		{
			_type = type;
			_value = value;
		}
		Operand(Operand const & cp)
		{
			*this = cp;
		}
		virtual ~Operand() {}
		Operand & operator=(Operand const & cp)
		{
			_type = cp.getType();
			_value = cp.getValue();
		}
		T	const	getValue() const
		{
			return (_value);
		}
		virtual int getPrecision() const
		{
			return (1);
		}
		virtual eOperandType getType() const
		{
			return (_type);
		}
		virtual Operand const * operator+(Operand const & rhs) const
		{
			_value = _value + rhs.getValue();
			return (this);
		}
		virtual Operand const * operator-(Operand const & rhs) const
		{
			_value = _value - rhs.getValue();
			return (this);
		}
		virtual Operand const * operator*(Operand const & rhs) const
		{
			_value = _value * rhs.getValue();
			return (this);
		}
		virtual Operand const * operator/(Operand const & rhs) const
		{
			if (rhs.getValue() == 0)
				throw std::runtime_error("can't divide by 0");
			_value = _value / rhs.getValue();
			return (this);
		}
		virtual Operand const * operator%(Operand const & rhs) const
		{
			if (rhs.getValue() == 0)
				throw std::runtime_error("can't divide by 0");
			_value = _value % rhs.getValue();
			return (this);
		}
		virtual std::string const & toString() const
		{
			return (std::to_string(_value));
		}
};

#endif /* Operand_h */
