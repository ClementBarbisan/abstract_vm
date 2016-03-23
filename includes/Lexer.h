
#ifndef Lexer_h
# define Lexer_h

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
                lexicalException(std::string msg, std::string line, int lineNb, std::list<std::string> & errorList);
                lexicalException(lexicalException const & cp);
                void    searchError(std::string line, int nbLine) const;
                lexicalException & operator=(lexicalException const & cp);
                std::string getMsg() const;
                std::list<std::string> & getErrorList() const;
                virtual ~lexicalException() throw();
                virtual const char *what() const throw();
            private:
                lexicalException();
                std::list<std::string> &    _errorList;
                std::string                 _msg;
        };
        Lexer();
        Lexer(Lexer const & cp);
        Lexer & operator=(Lexer const & cp);
        void checkLine(std::string line, int lineNb) const;
        std::list<std::string>  *getErrorList() const;
        std::list< std::list<std::string> > *getParserList() const;
    
        ~Lexer();
    private:
        void    addLineToParser(std::string line, int lineNb) const;
        std::list<std::string>  *errorList;
        std::list< std::list<std::string> > *parserList;
};

#endif
