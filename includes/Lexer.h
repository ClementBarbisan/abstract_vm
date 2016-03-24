#ifndef LEXER_H
# define LEXER_H

# include <string>
# include <list>
# include <exception>
# include <iostream>

class Lexer
{
    public:
        class lexicalException : public std::logic_error
        {
            public:
                lexicalException(std::string msg, std::string line, int lineNb, std::list<std::string const> & errorList);
                lexicalException(lexicalException const & cp);
                void                                    searchError(std::string line, int nbLine) const;
                lexicalException &                      operator=(lexicalException const & cp);
                std::string                             getMsg() const;
                std::list<std::string const> &          getErrorList() const;
                virtual ~lexicalException() throw();
                virtual const char                      *what() const throw();
            private:
                lexicalException();
                std::list<std::string const> &          _errorList;
                std::string                             _msg;
        };
        Lexer();
        Lexer(Lexer const & cp);
        Lexer &                                         operator=(Lexer const & cp);
        void                                            checkLine(std::string line, int lineNb) const;
        std::list<std::string const>              &     getErrorList() const;
        std::list< std::list<std::string const> > &     getParserList() const;
        std::list<int>                            &     getLineNb() const;
        ~Lexer();
    private:
        void                                            _addLineToParser(std::string line, int lineNb) const;
        std::list<std::string const>                    *_errorList;
        std::list< std::list<std::string const> >       *_parserList;
        std::list<int>                                  *_lineNb;
};

#endif
