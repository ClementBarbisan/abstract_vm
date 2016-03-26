#ifndef OPERAND_H
# define OPERAND_H

# include <stdio.h>
# include <string>
# include <IOperand.h>
# include <exception>
# include <sstream>
# include <OperandFactory.h>
# include <iostream>
# include <limits>

template <typename T>
class Operand : public IOperand
{
	private:
		Operand();
        OperandFactory  const *_factory;
		eOperandType	_type;
        std::string     _valueString;
		T				_value;
    
	public:
        Operand(OperandFactory const *factory, eOperandType type, std::string const & value)
		{
            _factory = factory;
			_type = type;
            _valueString = value;
			_value = stringToValue(value);
		}
    
		Operand(Operand const & cp)
		{
			*this = cp;
		}
		virtual ~Operand() {}
    
        OperandFactory *getFactory() const
        {
            return (_factory);
        }
    
		Operand & operator=(Operand const & cp)
		{
            _factory = cp.getFactory();
            _value = stringToValue(cp.toString());
			_type = cp.getType();
            _valueString = cp.toString();
		}
    
		int getPrecision() const
		{
			return (getType());
		}
    
		eOperandType getType() const
		{
			return (_type);
		}
    
        std::string const valueToString(T value) const
        {
            std::ostringstream os;
            
            os << value;
            return (os.str());
        }
    
        T   stringToValue(std::string const & operandString) const
        {
            T                   value;
            std::istringstream  ss(operandString);
            
            ss >> value;
            return (value);
        }
    
		IOperand const * operator+(IOperand const & rhs) const
        {
            T   rhsValue = stringToValue(rhs.toString());
            if (_value > std::numeric_limits<T>::max() - rhsValue)
                throw std::runtime_error(_valueString + " + " + rhs.toString() + " : Overflow");
            if (_value < std::numeric_limits<T>::min() - rhsValue)
                throw std::runtime_error(_valueString + " + " + rhs.toString() + " : Underflow");
            std::string string = valueToString(_value + rhsValue);
            if (rhs.getType() > getType())
                return (_factory->createOperand(rhs.getType(), string));
            else
                return (_factory->createOperand(getType(), string));
		}
    
		IOperand const * operator-(IOperand const & rhs) const
		{
            
            T   rhsValue = stringToValue(rhs.toString());
            if (_value > std::numeric_limits<T>::max() + rhsValue)
                throw std::runtime_error(_valueString + " - " + rhs.toString() + " : Overflow");
            if (_value < std::numeric_limits<T>::min() + rhsValue)
                throw std::runtime_error(_valueString + " - " + rhs.toString() + " : Underflow");
            std::string string = valueToString(_value - rhsValue);
            if (rhs.getType() > getType())
                return (_factory->createOperand(rhs.getType(), string));
            else
                return (_factory->createOperand(getType(), string));
		}
    
		IOperand const * operator*(IOperand const & rhs) const
		{
            T   rhsValue = stringToValue(rhs.toString());
            if (_value > std::numeric_limits<T>::max() / rhsValue)
                throw std::runtime_error(_valueString + " * " + rhs.toString() + " : Overflow");
            if (_value < std::numeric_limits<T>::min() / rhsValue)
                throw std::runtime_error(_valueString + " * " + rhs.toString() + " : Underflow");
            std::string string = valueToString(_value * rhsValue);
            if (rhs.getType() > getType())
                return (_factory->createOperand(rhs.getType(), string));
            else
                return (_factory->createOperand(getType(), string));
		}
    
		IOperand const * operator/(IOperand const & rhs) const
		{
            T   rhsValue = stringToValue(rhs.toString());
			if (rhsValue == 0)
				throw std::runtime_error("can't divide by 0");
            if (_value > std::numeric_limits<T>::max() * rhsValue)
                throw std::runtime_error(_valueString + " / " + rhs.toString() + " : Overflow");
            if (_value < std::numeric_limits<T>::min() * rhsValue)
                throw std::runtime_error(_valueString + " / " + rhs.toString() + " : Underflow");
            std::string string = valueToString(_value / rhsValue);
            if (rhs.getType() > getType())
                return (_factory->createOperand(rhs.getType(), string));
            else
                return (_factory->createOperand(getType(), string));
		}
    
        IOperand const * operator%(IOperand const & rhs) const
		{
            T rightValue = stringToValue(rhs.toString());
			if (rightValue == 0)
				throw std::runtime_error("can't divide by 0");
            std::string string = valueToString(_value + stringToValue(rhs.toString()));
            if (rhs.getType() > getType())
                return (_factory->createOperand(rhs.getType(), string));
            else
                return (_factory->createOperand(getType(), string));
		}
    
		std::string const & toString() const
		{
			return (_valueString);
		}
};

#endif /* Operand_h */
