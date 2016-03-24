#ifndef IOPERAND_H
# define IOPERAND_H

# include <string>

class IOperand {
	public:
        typedef enum                eOperandType
        {
            INT8 = 1,
            INT16 = 2,
            INT32 = 3,
            DOUBLE = 4,
            FLOAT = 5
        }                           eOperandType;
		virtual int                 getPrecision() const = 0;
		virtual eOperandType        getType() const = 0;
		virtual IOperand const      *operator+(IOperand const & rhs) const = 0;
		virtual IOperand const      *operator-(IOperand const & rhs) const = 0;
		virtual IOperand const      *operator*(IOperand const & rhs) const = 0;
		virtual IOperand const      *operator/(IOperand const & rhs) const = 0;
		virtual IOperand const      *operator%(IOperand const & rhs) const = 0;
		virtual std::string const & toString() const = 0;
		virtual ~IOperand() {}
};

#endif /* IOperand_h */
