
#ifndef lexer_h
# define lexer_h

# include <string>
# include <list>
# include <exception>

class lexer
{
    class lexicalException : public std::logic_error
    {
        public:
            lexicalException();
            lexicalException(lexicalException const & cp);
            lexicalException & operator=(lexicalException const & cp);
            std::string getMsg() const;
            virtual ~lexicalException() throw();
            virtual const char *what() const throw();
        private:
            std::string _msg;
    };
    public:
        lexer();
        lexer(lexer const & cp);
        lexer & operator=(lexer const & cp);
        void checkLine(std::string line, int nbLine);
        ~lexer();
    private:
        std::list< std::list<std::string> > *parseList;
    
    
};

#endif
