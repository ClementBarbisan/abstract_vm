//
//  OperandFactory.cpp
//  abstract_vm
//
//  Created by ClémentBarbisan on 09/03/2016.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#include <OperandFactory.h>
#include <Operand.h>

IOperand const * OperandFactory::createInt8(std::string const & value) const
{
    return (new Operand<int8_t>(this, IOperand::INT8, value));
}

IOperand const * OperandFactory::createInt16(std::string const & value) const
{
    return (new Operand<int16_t>(this, IOperand::INT16, value));
}

IOperand const * OperandFactory::createInt32(std::string const & value) const
{
    return (new Operand<int32_t>(this, IOperand::INT32, value));
}

IOperand const * OperandFactory::createFloat(std::string const & value) const
{
    return (new Operand<float>(this, IOperand::FLOAT, value));
}

IOperand const * OperandFactory::createDouble(std::string const & value) const
{
    return (new Operand<double>(this, IOperand::DOUBLE, value));
}

OperandFactory::OperandFactory()
{
    mapOperand = std::map<IOperand::eOperandType, funcOperand>();
    mapOperand[IOperand::INT8] = &OperandFactory::createInt8;
    mapOperand[IOperand::INT16] = &OperandFactory::createInt16;
    mapOperand[IOperand::INT32] = &OperandFactory::createInt32;
    mapOperand[IOperand::FLOAT] = &OperandFactory::createFloat;
    mapOperand[IOperand::DOUBLE] = &OperandFactory::createDouble;
}

std::map<IOperand::eOperandType, OperandFactory::funcOperand> const & OperandFactory::getMapOperand() const
{
    return (mapOperand);
}

IOperand const * OperandFactory::createOperand(IOperand::eOperandType type, std::string const & value) const
{
    funcOperand func = mapOperand[type];
    func(value);
}