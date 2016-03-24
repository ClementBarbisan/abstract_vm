#ifndef COMMANDS_H
# define COMMANDS_H

# include <functional>
# include <map>
# include <string>
# include <list>

class IOperand;
class Stack;
class OperandFactory;

class Commands
{
    typedef void (Commands::*ptrVoidFunc)(int lineNb);
    typedef void (Commands::*ptrFunc)(IOperand const &, int lineNb);
	private:
        std::string     _commandsVoid[9];
        std::string     _commands[2];
        Commands(Commands const &);
        Commands(void);
        Commands const & operator=(Commands const &);
		std::map<std::string, ptrFunc> *_mapFunc;
		std::map<std::string, ptrVoidFunc> *_mapVoidFunc;
        std::list<std::string> *_errorList;
        bool _exitApp;
		Stack & _stack;
        OperandFactory & _factory;
	public:
        class executeException : public std::logic_error
        {
            public:
                executeException(std::string msg, std::string line, std::list<std::string> *errorList, int nbLine);
                executeException(std::string msg, std::list<std::string> *errorList, int nbLine);
                executeException(executeException const & cp);
                void    searchError(std::string line, int nbLine) const;
                void    searchError(int nbLine) const;
                executeException & operator=(executeException const & cp);
                std::list<std::string> *getErrorList() const;
                std::string getMsg() const;
                virtual ~executeException() throw();
                virtual const char *what() const throw();
            private:
                executeException();
                std::list<std::string> *_errorList;
                std::string _msg;
        };
        void push(IOperand const & value, int lineNb);
        void assert(IOperand const & value, int lineNb);
        void pop(int lineNb);
        void dump(int lineNb);
        void add(int lineNb);
        void sub(int lineNb);
        void mul(int lineNb);
        void div(int lineNb);
        void mod(int lineNb);
        void print(int lineNb);
        void exit(int lineNb);
		void executeCommand(std::string const name, IOperand const & value, int line);
        void executeCommand(std::string const name, int line);
		Stack & getStackValue(void) const;
        std::string const *getCommands() const;
        std::string const *getCommandsVoid() const;
        bool    getExit() const;
        Commands(Stack & stack, OperandFactory & factory);
		~Commands(void);
};

#endif
