//
//  lexer.cpp
//  abstract_vm
//
//  Created by Clement BARBISAN on 2/9/16.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#include <stdio.h>
#include <lexer.h>
#include <regex>

lexer::lexer()
{
    this->errorList = new std::list<std::string>();
    this->parserList = new std::list< std::list<std::string> >();
}

lexer::lexer(lexer const & cp)
{
    *this = cp;
}

lexer & lexer::operator=(lexer const & cp)
{
    this->parserList = cp.parserList;
    this->errorList = cp.errorList;
    return (*this);
}

lexer::~lexer()
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

std::list< std::list<std::string> > *lexer::getParserList() const
{
    return (parserList);
}

std::list<std::string>  *lexer::getErrorList() const
{
    return (errorList);
}

void    lexer::searchError(std::string line, int nbLine, lexicalException& e) const
{
    std::string error;
    
    error = "Line " + std::to_string(nbLine) + " : " + line + " : " + e.what();
    errorList->push_back(error);
}

void    lexer::addLineToParser(std::string line) const
{
    std::smatch matches;
    std::list<std::string> tokens;
    
    line = line.substr(0, line.find(";"));
    std::regex_match(line, matches, std::regex("[a-zA-Z0-9]+"));
	if (matches.length() > 3)
		throw lexer::lexicalException("too much tokens");
    for (std::smatch::iterator it = matches.begin(); it < matches.end(); it++)
        tokens.push_back(*it);
    parserList->push_back(tokens);
}

void    lexer::checkLine(std::string line) const
{
    if (std::regex_match(line, std::regex("[a-z]+( [a-z]{3,6}[0-9]{0,2}\\([-]?[0-9]+(.[0-9]+)?\\))?(;.*)?")))
        addLineToParser(line);
    else
        throw lexer::lexicalException("lexical error");
}

lexer::lexicalException::lexicalException(std::string msg): std::logic_error(msg)
{
    _msg = msg;
}

lexer::lexicalException::~lexicalException() throw()
{
}

lexer::lexicalException & lexer::lexicalException::operator=(lexicalException const & cp)
{
    this->_msg = cp._msg;
    return (*this);
}

std::string lexer::lexicalException::getMsg() const
{
    return (_msg);
}

const char *lexer::lexicalException::what() const throw()
{
    return (_msg.c_str());
}