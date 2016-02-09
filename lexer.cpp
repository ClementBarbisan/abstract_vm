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
    this->parseList = new std::list< std::list<std::string> >();
}

lexer::lexer(lexer const & cp)
{
    *this = cp;
}

lexer & lexer::operator=(lexer const & cp)
{
    this->parseList = cp.parseList;
    return (*this);
}

lexer::~lexer()
{
    delete parseList;
}

void    lexer::checkLine(<#std::string line#>, int nbLine)
{
    try
    {
        if (std::regex_match(line, "[a-z]{3,6}( [a-z]{3,6}[0-9]{0,2}\([-]?[0-9]+(.[0-9]+)?\))?"))
        {
            
        }
        else
        {
            throw lexer::lexicalException();
        }
    }
    catch (lexer::lexicalException& e)
    {
        
    }
}