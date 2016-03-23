/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:22:52 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/01 15:23:07 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Commands.h>
#include <StackValue.h>
#include <OperandFactory.h>
#include <IOperand.h>

void Commands::executeException::searchError(std::string line, int nbLine) const
{
    std::string error;
    
    error = "Line " + std::to_string(nbLine) + " : " + line + " : " + what();
    _errorList->push_back(error);
}

void Commands::executeException::searchError(int nbLine) const
{
    std::string error;
    
    error = "Line " + std::to_string(nbLine) + " : " + what();
    _errorList->push_back(error);
}

Commands::executeException::executeException(std::string msg, std::list<std::string> *errorList, int nbLine) : std::logic_error(msg),
    _errorList(errorList)
{
    _msg = msg;
    searchError(nbLine);
}

Commands::executeException::executeException(std::string msg, std::string line, std::list<std::string> *errorList, int nbLine) : std::logic_error(msg),
_errorList(errorList)
{
    _msg = msg;
    searchError(line, nbLine);
}

Commands::executeException::~executeException() throw()
{
    
}

Commands::executeException::executeException(Commands::executeException const & cp) : std::logic_error(cp.getMsg()),
    _errorList(cp.getErrorList())
{
    *this = cp;
}

std::list<std::string> *Commands::executeException::getErrorList() const
{
    return (_errorList);
}

std::string Commands::executeException::getMsg() const
{
    return (_msg);
}

const char *Commands::executeException::what() const throw()
{
    return (_msg.c_str());
}

Commands::executeException & Commands::executeException::operator=(Commands::executeException const & cp)
{
    _msg = cp.getMsg();
    return (*this);
}

Commands::Commands(Stack & stack, OperandFactory & factory) : _stack(stack), _factory(factory)
{
    _exitApp = false;
    _errorList = new std::list<std::string>();
    (*_mapFunc)["push"] = &Commands::push;
    (*_mapFunc)["assert"] = &Commands::assert;
    (*_mapVoidFunc)["pop"] = &Commands::pop;
    (*_mapVoidFunc)["dump"] = &Commands::dump;
    (*_mapVoidFunc)["add"] = &Commands::add;
    (*_mapVoidFunc)["sub"] = &Commands::sub;
    (*_mapVoidFunc)["mul"] = &Commands::mul;
    (*_mapVoidFunc)["div"] = &Commands::div;
    (*_mapVoidFunc)["mod"] = &Commands::mod;
    (*_mapVoidFunc)["print"] = &Commands::print;
    (*_mapVoidFunc)["exit"] = &Commands::exit;
    commandsVoid[0] = "pop";
    commandsVoid[1] = "dump";
    commandsVoid[2] = "add";
    commandsVoid[3] = "sub";
    commandsVoid[4] = "mul";
    commandsVoid[5] = "div";
    commandsVoid[6] = "mod";
    commandsVoid[7] = "print";
    commandsVoid[8] = "exit";
    commands[0] = "push";
    commands[1] = "assert";
}

Commands::~Commands()
{
    for (std::list<std::string>::iterator it = _errorList->begin(); it != _errorList->end(); it++)
    {
        std::cout << *it << std::endl;
    }
    _errorList->erase(_errorList->begin(), _errorList->end());
    delete _errorList;
}

void    Commands::executeCommand(std::string name, int line)
{
    if ((*_mapVoidFunc)[name])
    {
        ptrVoidFunc func = (*_mapVoidFunc)[name];
        (this->*func)(line);
        return;
    }
    throw Commands::executeException("Command not found", name, _errorList, line);
}

void    Commands::executeCommand(std::string name, IOperand & value, int line)
{
    if ((*_mapFunc)[name])
    {
        ptrFunc func = (*_mapFunc)[name];
        (this->*func)(value, line);
        return;
    }
    throw Commands::executeException("Command not found", name, _errorList, line);
}

bool    Commands::getExit() const
{
    return (_exitApp);
}

Stack & Commands::getStackValue() const
{
    return (_stack);
}

void Commands::push(IOperand & value, int lineNb)
{
    lineNb = 0;
    _stack.addValueToStack(&value);
}

void Commands::assert(IOperand & value, int lineNb)
{
    if (!_stack.getStack().empty())
    {
        if (value.toString() != _stack.getStack().front()->toString())
        {
            std::cout << "Assert failed : " << value.toString() << " not equal to " << _stack.getStack().front()->toString() << " : exit program." << std::endl;
            exit(lineNb);
        }
    }
    else
        Commands::executeException("Empty stack, abort assert", _errorList, lineNb);
}

void Commands::pop(int lineNb)
{
    if (!_stack.getStack().empty())
    {
        _stack.unstack();
    }
    else
        Commands::executeException("Empty stack, abort pop", _errorList, lineNb);
}

void Commands::dump(int lineNb)
{
    lineNb = 0;
    for (std::list<IOperand const *>::iterator it = _stack.getStack().begin(); it != _stack.getStack().end(); ++it)
        std::cout << (*it)->toString() << std::endl;
}

void Commands::add(int lineNb)
{
    if (_stack.getStack().size() < 2)
    {
        IOperand const & value1 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const & value2 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const * result = value2 + value1;
        _stack.addValueToStack(result);
    }
    else
        Commands::executeException("Not enough elements on stack, abort add", _errorList, lineNb);
}

void Commands::sub(int lineNb)
{
    if (_stack.getStack().size() < 2)
    {
        IOperand const & value1 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const & value2 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const * result = value2 - value1;
        _stack.addValueToStack(result);
    }
    else
        Commands::executeException("Not enough elements on stack, abort sub", _errorList, lineNb);
}

void Commands::mul(int lineNb)
{
    if (_stack.getStack().size() < 2)
    {
        IOperand const & value1 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const & value2 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const * result = value2 * value1;
        _stack.addValueToStack(result);
    }
    else
        Commands::executeException("Not enough elements on stack, abort mul", _errorList, lineNb);
}

void Commands::div(int lineNb)
{
    if (_stack.getStack().size() < 2)
    {
        IOperand const & value1 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const & value2 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const * result = value2 / value1;
        _stack.addValueToStack(result);
    }
    else
        Commands::executeException("Not enough elements on stack, abort div", _errorList, lineNb);
}

void Commands::mod(int lineNb)
{
    if (_stack.getStack().size() < 2)
    {
        IOperand const & value1 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const & value2 = *_stack.getStack().front();
        _stack.unstack();
        IOperand const * result = value2 % value1;
        _stack.addValueToStack(result);
    }
    else
        Commands::executeException("Not enough elements on stack, abort mod", _errorList, lineNb);
}

void Commands::print(int lineNb)
{
    if (!_stack.getStack().empty())
    {
        if (_stack.getStack().front()->getType() == IOperand::INT8)
            std::cout << static_cast<char>(atoi(_stack.getStack().front()->toString().c_str())) << std::endl;
        else
            Commands::executeException("Value on top is not an integer, abort print", _errorList, lineNb);
    }
    else
         Commands::executeException("Stack is empty, abort print", _errorList, lineNb);
}

void Commands::exit(int lineNb)
{
    lineNb = 0;
    _exitApp = true;
}
