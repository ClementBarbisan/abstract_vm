//
//  lexer.cpp
//  abstract_vm
//
//  Created by Clement BARBISAN on 2/9/16.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#include <stdio.h>
#include "lexer.h"
#include <regex>

lexer::lexer()
{
    this->parserList = new std::list< std::list<std::string> >();
}

lexer::lexer(lexer const & cp)
{
    *this = cp;
}

lexer & lexer::operator=(lexer const & cp)
{
    this->parserList = cp.parserList;
    return (*this);
}

lexer::~lexer()
{
    delete parserList;
}

std::list< std::list<std::string> > *lexer::getParserList() const
{
    return (parserList);
}

std::list<std::string>  *lexer::getErrorList() const
{
    return (errorList);
}

void    lexer::searchError(std::string line, int nbLine) const
{
    errorList->push_back(line);
}

void    lexer::addLineToParser(std::string line) const
{
    std::smatch matches;
    
    std::regex_match(line, matches, std::regex("[a-zA-Z0-9]+"));
}

void    lexer::checkLine(std::string line, int nbLine) const
{
    try
    {
        if (std::regex_match(line, std::regex("[a-z]+( [a-z]{3,6}[0-9]{0,2}\\([-]?[0-9]+(.[0-9]+)?\\))?(;.*)?")))
            addLineToParser(line);
        else
            throw lexer::lexicalException();
    }
    catch (lexer::lexicalException& e)
    {
        searchError(line, nbLine);
    }
}