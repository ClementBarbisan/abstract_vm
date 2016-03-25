#include <Parser.h>
#include <QueueFunctions.h>
#include <Commands.h>
#include <Lexer.h>
#include <iostream>
#include <instruction.h>
#include <OperandFactory.h>

void Parser::parsingException::searchError(std::string line, int nbLine) const
{
    std::string error;
    
    error = "Line " + std::to_string(nbLine) + " : " + line + " : " + what();
    _errorList->push_back(error);
}

Parser::parsingException::parsingException(std::string msg, std::string line, std::list<std::string const> *errorList, int nbLine) : std::logic_error(msg),
_errorList(errorList)
{
    _msg = msg;
    searchError(line, nbLine);
}

Parser::parsingException::~parsingException() throw()
{
    
}

Parser::parsingException::parsingException(Parser::parsingException const & cp) : std::logic_error(cp.getMsg()),
_errorList(cp.getErrorList())
{
    *this = cp;
}

std::list<std::string const> *Parser::parsingException::getErrorList() const
{
    return (_errorList);
}

std::string Parser::parsingException::getMsg() const
{
    return (_msg);
}

const char *Parser::parsingException::what() const throw()
{
    return (_msg.c_str());
}

Parser::parsingException & Parser::parsingException::operator=(Parser::parsingException const & cp)
{
    _msg = cp.getMsg();
    return (*this);
}

Parser::Parser(Queue & queue, Commands & commands, Lexer & lexer, OperandFactory & factory) : _queue(queue), _commands(commands), _parserList(lexer.getParserList()), _factory(factory)
{
	this->_countLine = 0;
	_errorList = new std::list<std::string const>();
}

Parser::~Parser()
{
	for (std::list<std::string const>::iterator it = _errorList->begin(); it != _errorList->end(); it++)
        std::cout << *it << std::endl;
	_errorList->erase(_errorList->begin(), _errorList->end());
	delete _errorList;
}

std::list<std::string const> &	Parser::getErrorList() const
{
	return (*_errorList);
}


Queue & Parser::getFunctions() const
{
	return (this->_queue);
}

void    Parser::_incrementCountLine()
{
    this->_countLine++;
}

void    Parser::_addFunctionToQueue(s_instruct *instruction, int lineNb)
{
	this->_queue.addFunctionToQueue(instruction, lineNb);
}

int     Parser::getCountLine() const
{
    return(this->_countLine);
}

std::list< std::list<std::string const> > & Parser::getList()
{
    return (_parserList);
}

IOperand const * Parser::_createOperand(std::list<std::string const> operand, int lineNb) const
{
    IOperand::eOperandType type = _factory.getEnumType(operand.front());
    operand.pop_front();
    try
    {
       return (_factory.createOperand(type, operand.front()));
    }
    catch (std::runtime_error &e)
    {
        throw parsingException(static_cast<std::string>(e.what()) , operand.front(), _errorList, lineNb);
    }
    
}

void    Parser::checkLine(std::string const line, std::list<std::string const> operand, int lineNb) const
{
    for (int i = 0; i < 2; i++)
    {
        if (line == _commands.getCommands()[i])
        {
            s_instruct *instruction = new s_instruct();
            instruction->func = line;
            instruction->value = _createOperand(operand, lineNb);
            _queue.addFunctionToQueue(instruction, lineNb);
            return;
        }
    }
    throw parsingException("Command not found", line, _errorList, lineNb);
}

void    Parser::checkLine(std::string const line, int lineNb) const
{
    for (int i = 0; i < 9; i++)
    {
        if (_commands.getCommandsVoid()[i] == line)
        {
            s_instruct *instruction = new s_instruct();
            instruction->func = line;
            instruction->value = NULL;
            _queue.addFunctionToQueue(instruction, lineNb);
            return;
        }
    }
     throw parsingException("Command not found", line, _errorList, lineNb);
}