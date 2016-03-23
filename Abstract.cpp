/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:21:07 by cbarbisa          #+#    #+#             */
/*   Updated: 2016/03/23 15:05:02 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Abstract.h>
#include <Parser.h>
#include <Lexer.h>
#include <fstream>

void    readFile(Lexer *Lexer, char* filename)
{
    int lineNb;
    std::string line;
    std::ifstream file(filename);
    
    lineNb = 0;
    while (std::getline(file, line) && line.length() > 0)
    {
        try
        {
            std::cout << line << std::endl;
            Lexer->checkLine(line, lineNb);
        }
        catch (Lexer::lexicalException& e)
        {
            
        }
        lineNb++;
    }
}

void    standardEntryReading(Lexer *Lexer)
{
    int			lineNb;
    std::string line;
    
    lineNb = 0;
    try
    {
        while (true)
        {
            std::getline(std::cin, line);
            Lexer->checkLine(line, lineNb);
            lineNb++;
        }
    }
    catch (Lexer::lexicalException& e)
    {
        
    }
}

//void    parseFile(Parser *currentParser)
//{
	
//}

int main(int argc, char* argv[])
{
//    Parser	parser;
    Lexer	Lexer;

    if (argc == 1)
        standardEntryReading(&Lexer);
    else if (argc == 2)
        readFile(&Lexer, argv[1]);
    else
        std::cout << "Too much arguments : Usage - ./avm [filename]" << std::endl;
    if (Lexer.getErrorList()->size() > 0)
        return (-1);
//    parseFile(&parser);
}

