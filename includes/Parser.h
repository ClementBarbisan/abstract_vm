#ifndef PARSER_H
# define PARSER_H

# include <map>
# include <string>
# include <regex>
# include <list>
# include <instruction.h>

class Queue;
class Commands;
class Lexer;
class OperandFactory;
class IOperand;

class Parser
{
    private:
		
        int _countLine;
		Queue  &                                    _queue;
        Commands &                                  _commands;
        std::list< std::list<std::string const> > & _parserList;
        OperandFactory &                            _factory;
        void                                        _incrementCountLine();
		void                                        _addFunctionToQueue(s_instruct *instruction, int lineNb);
        IOperand const *                            _createOperand(std::list<std::string const> operand) const;
        Parser(void);
        Parser(Parser const &);
        Parser const &                              operator=(Parser const &);
    public:
        Parser(Queue & queue, Commands & commands, Lexer & lexer, OperandFactory & factory);
        ~Parser(void);
        void                                        checkLine(std::string const line, std::list<std::string const> const nb, int lineNb) const;
        void                                        checkLine(std::string const line, int lineNb) const;
		Queue &                                     getFunctions() const;
        std::list< std::list<std::string const> > & getList();
		int                                         getCountLine() const;
};

#endif
