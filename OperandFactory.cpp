#include <OperandFactory.h>
#include <Operand.h>
#include <limits>
#include <regex>
#include <iostream>

IOperand const *OperandFactory::createInt8(std::string const & value) const
{
    if (std::regex_search(value, std::regex("\\.+")))
        throw std::runtime_error("is not a 8 bit integer.");
    if (stringToValue(value) >= std::numeric_limits<int8_t>::max())
        throw std::runtime_error("is too high for 8 bit integer.");
    if (stringToValue(value) <= std::numeric_limits<int8_t>::min())
        throw std::runtime_error("is too low for 8 bit integer.");
    return (new Operand<int8_t>(this, IOperand::INT8, value));
}

IOperand const *OperandFactory::createInt16(std::string const & value) const
{
    if (std::regex_search(value, std::regex("\\.+")))
        throw std::runtime_error("is not a 16 bit integer.");
    if (stringToValue(value) >= std::numeric_limits<int16_t>::max())
        throw std::runtime_error("is too high for 16 bit integer.");
    if (stringToValue(value) <= std::numeric_limits<int16_t>::min())
        throw std::runtime_error("is too low for 16 bit integer.");
    return (new Operand<int16_t>(this, IOperand::INT16, value));
}

IOperand const *OperandFactory::createInt32(std::string const & value) const
{
    if (std::regex_search(value, std::regex("\\.+")))
        throw std::runtime_error("is not a 32 bit integer.");
    if (stringToValue(value) >= std::numeric_limits<int32_t>::max())
        throw std::runtime_error("is too high for 32 bit integer.");
    if (stringToValue(value) <= std::numeric_limits<int32_t>::min())
        throw std::runtime_error("is too low for 32 bit integer.");
    return (new Operand<int32_t>(this, IOperand::INT32, value));
}

IOperand const *OperandFactory::createFloat(std::string const & value) const
{
    if (stringToValue(value) >= std::numeric_limits<float>::max())
        throw std::runtime_error("is too high for float.");
    if (stringToValue(value) <= std::numeric_limits<float>::min())
        throw std::runtime_error("is too low for float.");
    return (new Operand<float>(this, IOperand::FLOAT, value));
}

IOperand const *OperandFactory::createDouble(std::string const & value) const
{
    if (stringToValue(value) >= std::numeric_limits<double>::max())
        throw std::runtime_error("is too high for double.");
    if (stringToValue(value) <= std::numeric_limits<double>::min())
        throw std::runtime_error("is too low for double.");
    return (new Operand<double>(this, IOperand::DOUBLE, value));
}

double OperandFactory::stringToValue(std::string const & operandString) const
{
    double                   value;
    std::istringstream  ss(operandString);
    
    ss >> value;
    return (value);
}

IOperand::eOperandType OperandFactory::getEnumType(std::string name)
{
    if ((*_mapEnum)[name])
        return ((*_mapEnum)[name]);
    throw std::runtime_error("Unknown operand type : " + name);
}

OperandFactory::~OperandFactory()
{
    _mapOperand->erase(_mapOperand->begin(), _mapOperand->end());
    _mapEnum->erase(_mapEnum->begin(), _mapEnum->end());
    delete _mapOperand;
    delete _mapEnum;
}

OperandFactory::OperandFactory()
{
    _mapOperand = new std::map<IOperand::eOperandType, funcOperand>();
    (*_mapOperand)[IOperand::INT8] = &OperandFactory::createInt8;
    (*_mapOperand)[IOperand::INT16] = &OperandFactory::createInt16;
    (*_mapOperand)[IOperand::INT32] = &OperandFactory::createInt32;
    (*_mapOperand)[IOperand::FLOAT] = &OperandFactory::createFloat;
    (*_mapOperand)[IOperand::DOUBLE] = &OperandFactory::createDouble;
    _mapEnum = new std::map<std::string, IOperand::eOperandType>();
    (*_mapEnum)["int8"] = IOperand::INT8;
    (*_mapEnum)["int16"] = IOperand::INT16;
    (*_mapEnum)["int32"] = IOperand::INT32;
    (*_mapEnum)["float"] = IOperand::FLOAT;
    (*_mapEnum)["double"] = IOperand::DOUBLE;
}

IOperand const * OperandFactory::createOperand(IOperand::eOperandType type, std::string const & value) const
{
    if ((*_mapOperand)[type])
    {
        funcOperand func = (*_mapOperand)[type];
        return ((this->*func)(value));
    }
    for (std::map<std::string, IOperand::eOperandType>::iterator it = _mapEnum->begin(); it != _mapEnum->end(); it++)
    {
        if (it->second == type)
            throw std::runtime_error("Couldn't create operand of type : " + it->first);
    }
    throw std::runtime_error("Unknown operand type.");
}