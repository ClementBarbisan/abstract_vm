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
		std::list<std::string const>				*_errorList;
        OperandFactory &                            _factory;
        void                                        _incrementCountLine();
		void                                        _addFunctionToQueue(s_instruct *instruction, int lineNb);
        IOperand const *                            _createOperand(std::list<std::string const> operand, int lineNb) const;
        Parser(void);
        Parser(Parser const &);
        Parser const &                              operator=(Parser const &);
    public:
    class parsingException : public std::logic_error
    {
        public:
            parsingException(std::string msg, std::string line, std::list<std::string const> *errorList, int nbLine);
            parsingException(parsingException const & cp);
            void                            searchError(std::string line, int nbLine) const;
            parsingException &              operator=(parsingException const & cp);
            std::list<std::string const>    *getErrorList() const;
            std::string                     getMsg() const;
            virtual ~parsingException() throw();
            virtual const char              *what() const throw();
        private:
            parsingException();
            std::list<std::string const>      *_errorList;
            std::string                 _msg;
        };
        Parser(Queue & queue, Commands & commands, Lexer & lexer, OperandFactory & factory);
        ~Parser(void);
		std::list<std::string const> &				getErrorList() const;
		void                                        checkLine(std::string const line, std::list<std::string const> const nb, int lineNb) const;
        void                                        checkLine(std::string const line, int lineNb) const;
		Queue &                                     getFunctions() const;
        std::list< std::list<std::string const> > & getList();
		int                                         getCountLine() const;
};

#endif
