#include <Parser.h>
#include <QueueFunctions.h>
#include <Commands.h>
#include <Lexer.h>
#include <iostream>
#include <instruction.h>
#include <OperandFactory.h>

Parser::Parser(Queue & queue, Commands & commands, Lexer & lexer, OperandFactory & factory) : _queue(queue), _commands(commands), _parserList(lexer.getParserList()), _factory(factory)
{
	this->_countLine = 0;
}

Parser::~Parser()
{
    
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

IOperand const * Parser::_createOperand(std::list<std::string const> operand) const
{
    IOperand::eOperandType type = _factory.getEnumType(operand.front());
    operand.pop_front();
    return (_factory.createOperand(type, operand.front()));
}

void    Parser::checkLine(std::string const line, std::list<std::string const> operand, int lineNb) const
{
    for (int i = 0; i < 2; i++)
    {
        if (line == _commands.getCommands()[i])
        {
            s_instruct *instruction = new s_instruct();
            instruction->func = line;
            instruction->value = _createOperand(operand);
            _queue.addFunctionToQueue(instruction, lineNb);
            return;
        }
    }
    throw std::exception();
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
    throw std::exception();
}