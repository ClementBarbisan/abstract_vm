//
//  Lexer.cpp
//  abstract_vm
//
//  Created by Clement BARBISAN on 2/9/16.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#include <stdio.h>
#include <Lexer.h>
#include <regex>

Lexer::Lexer()
{
    this->errorList = new std::list<std::string>();
    this->parserList = new std::list< std::list<std::string> >();
}

Lexer::Lexer(Lexer const & cp)
{
    *this = cp;
}

Lexer & Lexer::operator=(Lexer const & cp)
{
    this->parserList = cp.parserList;
    this->errorList = cp.errorList;
    return (*this);
}

Lexer::~Lexer()
{
    for (std::list<std::string>::iterator it = errorList->begin(); it != errorList->end(); it++)
    {
        std::cout << *it << std::endl;
    }
    parserList->erase(parserList->begin(), parserList->end());
    errorList->erase(errorList->begin(), errorList->end());
    delete parserList;
    delete errorList;
}

std::list< std::list<std::string> > *Lexer::getParserList() const
{
    return (parserList);
}

std::list<std::string>  *Lexer::getErrorList() const
{
    return (errorList);
}

void    Lexer::addLineToParser(std::string line, int lineNb) const
{
    std::smatch matches;
    std::list<std::string> tokens;
    
    line = line.substr(0, line.find(";"));
    std::regex_match(line, matches, std::regex("[a-zA-Z0-9]+"));
	if (matches.length() > 3)
		throw Lexer::lexicalException("too much tokens", line, lineNb, *errorList);
    for (std::smatch::iterator it = matches.begin(); it < matches.end(); it++)
        tokens.push_back(*it);
    parserList->push_back(tokens);
}

void    Lexer::checkLine(std::string line, int lineNb) const
{
    if (std::regex_match(line, std::regex("[a-z]+( [a-z]{3,6}[0-9]{0,2}\\([-]?[0-9]+(.[0-9]+)?\\))?(;.*)?")))
        addLineToParser(line, lineNb);
    else
        throw Lexer::lexicalException("lexical error", line, lineNb, *errorList);
}

Lexer::lexicalException::lexicalException(std::string msg, std::string line, int lineNb, std::list<std::string> & errorList): std::logic_error(msg), _errorList(errorList)
{
    _msg = msg;
    searchError(line, lineNb);
}

std::list<std::string> & Lexer::lexicalException::getErrorList() const
{
    return (_errorList);
}

Lexer::lexicalException::lexicalException(Lexer::lexicalException const & cp) : std::logic_error(cp.getMsg()), _errorList(cp.getErrorList())
{
    *this = cp;
}



void    Lexer::lexicalException::searchError(std::string line, int nbLine) const
{
    std::string error;
    
    error = "Line " + std::to_string(nbLine) + " : " + line + " : " + what();
    _errorList.push_back(error);
}

Lexer::lexicalException::~lexicalException() throw()
{
}

Lexer::lexicalException & Lexer::lexicalException::operator=(lexicalException const & cp)
{
    this->_msg = cp._msg;
    return (*this);
}

std::string Lexer::lexicalException::getMsg() const
{
    return (_msg);
}

const char *Lexer::lexicalException::what() const throw()
{
    return (_msg.c_str());
}