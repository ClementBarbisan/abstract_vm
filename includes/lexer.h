
#ifndef lexer_h
# define lexer_h

# include <string>
# include <list>
# include <exception>
# include <iostream>

class lexer
{
    public:
        class lexicalException : public std::logic_error
        {
        public:
            lexicalException(std::string msg);
            lexicalException(lexicalException const & cp);
            lexicalException & operator=(lexicalException const & cp);
            std::string getMsg() const;
            virtual ~lexicalException() throw();
            virtual const char *what() const throw();
        private:
			lexicalException();
            std::string _msg;
        };
        lexer();
        lexer(lexer const & cp);
        lexer & operator=(lexer const & cp);
        void checkLine(std::string line) const;
        std::list<std::string>  *getErrorList() const;
        std::list< std::list<std::string> > *getParserList() const;
        void    searchError(std::string line, int nbLine, lexicalException & e) const;
        ~lexer();
    private:
        void    addLineToParser(std::string line) const;
        std::list<std::string>  *errorList;
        std::list< std::list<std::string> > *parserList;
};

#endif
