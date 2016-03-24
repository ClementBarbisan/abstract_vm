#include <stdio.h>
#include <Lexer.h>
#include <regex>

Lexer::Lexer()
{
    _errorList = new std::list<std::string const>();
    _parserList = new std::list< std::list<std::string const> >();
    _lineNb = new std::list<int>();
}

Lexer::Lexer(Lexer const & cp)
{
    *this = cp;
}

Lexer & Lexer::operator=(Lexer const & cp)
{
    _parserList = &cp.getParserList();
    _errorList = &cp.getErrorList();
    _lineNb = &cp.getLineNb();
    return (*this);
}

Lexer::~Lexer()
{
    for (std::list<std::string const>::iterator it = _errorList->begin(); it != _errorList->end(); it++)
        std::cout << *it << std::endl;
    _parserList->erase(_parserList->begin(), _parserList->end());
    _errorList->erase(_errorList->begin(), _errorList->end());
    _lineNb->erase(_lineNb->begin(), _lineNb->end());
    delete _lineNb;
    delete _parserList;
    delete _errorList;
}

std::list<int>  & Lexer::getLineNb() const
{
    return (*_lineNb);
}

std::list< std::list<std::string const> > & Lexer::getParserList() const
{
    return (*_parserList);
}

std::list<std::string const>  & Lexer::getErrorList() const
{
    return (*_errorList);
}

void    Lexer::_addLineToParser(std::string line, int lineNb) const
{
    std::smatch matches;
    std::list<std::string const> tokens;
    
    line = line.substr(0, line.find(";"));
    std::regex_match(line, matches, std::regex("[a-zA-Z0-9.]+"));
	if (matches.length() > 3)
		throw Lexer::lexicalException("too much tokens", line, lineNb, *_errorList);
    for (std::smatch::iterator it = matches.begin(); it < matches.end(); it++)
        tokens.push_back(*it);
    _parserList->push_back(tokens);
    _lineNb->push_back(lineNb);
}

void    Lexer::checkLine(std::string line, int lineNb) const
{
    if (std::regex_match(line, std::regex("[a-z]+( [a-z]{3,6}[0-9]{0,2}\\([-]?[0-9]+(.[0-9]+)?\\))?(;.*)?")))
        _addLineToParser(line, lineNb);
    else
        throw Lexer::lexicalException("lexical error", line, lineNb, *_errorList);
}

Lexer::lexicalException::lexicalException(std::string msg, std::string line, int lineNb, std::list<std::string const> & errorList): std::logic_error(msg), _errorList(errorList)
{
    _msg = msg;
    searchError(line, lineNb);
}

std::list<std::string const> & Lexer::lexicalException::getErrorList() const
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