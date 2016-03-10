/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbarbisa <cbarbisa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 15:21:07 by cbarbisa          #+#    #+#             */
/*   Updated: 2015/12/15 15:23:13 by cbarbisa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <abstract.h>
#include <parser.h>
#include <lexer.h>
#include <fstream>

void    readFile(lexer *lexer, char* filename)
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
            lexer->checkLine(line);
        }
        catch (lexer::lexicalException& e)
        {
            lexer->searchError(line, lineNb, e);
        }
        lineNb++;
    }
}

void    standardEntryReading(lexer *lexer)
{
    int			lineNb;
    std::string line;
    
    lineNb = 0;
    try
    {
        while (true)
        {
            std::getline(std::cin, line);
            lexer->checkLine(line);
            lineNb++;
        }
    }
    catch (lexer::lexicalException& e)
    {
        lexer->searchError(line, lineNb, e);
    }
}

void    parseFile(parser *currentParser)
{
	
}

int main(int argc, char* argv[])
{
    parser	parser;
    lexer	lexer;

    if (argc == 1)
        standardEntryReading(&lexer);
    else if (argc == 2)
        readFile(&lexer, argv[1]);
    else
        std::cout << "Too much arguments : Usage - ./avm [filename]" << std::endl;
    if (lexer.getErrorList()->size() > 0)
        return (-1);
    parseFile(&parser);
}

