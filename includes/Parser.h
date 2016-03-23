//
// Created by Clement BARBISAN on 30/11/15.
//

#ifndef ABSTRACT_VM_Parser_H
# define ABSTRACT_VM_Parser_H

# include <map>
# include <string>
# include <regex>

class Queue;

class Parser
{
    private:
		
        int _countLine;
		Queue  *_queue;
        std::map<std::string, std::regex> _commands;
        void _incrementCountLine();
		bool _addFunctionToQueue(std::string const name);
    public:
        Parser(void);
        Parser(Queue *queue);
        ~Parser(void);
        Parser(Parser const &);
        Parser const & operator=(Parser const &);
        void addCommand(std::string const name, std::string const regex);
        bool checkLine(std::string const line);
        std::map<std::string, std::regex> const & getCommands() const;
		Queue *getFunctions() const;
		int getCountLine() const;
};

#endif
