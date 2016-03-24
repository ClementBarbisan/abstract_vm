#ifndef OPERANDFACTORY_H
# define OPERANDFACTORY_H

# include <stdio.h>
# include <IOperand.h>
# include <map>

class OperandFactory
{
    typedef IOperand const *(OperandFactory::*funcOperand)(std::string const &) const;
	public:
		OperandFactory();
		~OperandFactory();
        IOperand::eOperandType getEnumType(std::string name);
        IOperand const *createOperand(IOperand::eOperandType type, std::string const & value) const;
	private:
        OperandFactory(OperandFactory const & cp);
        OperandFactory & operator=(OperandFactory const & cp);
		std::map<IOperand::eOperandType, funcOperand> *_mapOperand;
        std::map<std::string, IOperand::eOperandType> *_mapEnum;
		IOperand const *createInt8(std::string const & value) const;
		IOperand const *createInt16(std::string const & value) const;
		IOperand const *createInt32(std::string const & value) const;
		IOperand const *createFloat(std::string const & value) const;
		IOperand const *createDouble(std::string const & value) const;
};

#endif
