#include <Abstract.h>
#include <Parser.h>
#include <Commands.h>
#include <OperandFactory.h>
#include <QueueFunctions.h>
#include <StackValue.h>
#include <Lexer.h>
#include <fstream>

void        readFile(Lexer & lexer, char* filename)
{
    int             lineNb;
    std::string     line;
    std::ifstream   file(filename);
    
    lineNb = 0;
    while (std::getline(file, line))
    {
        if (line.length() > 0)
        {
            try
            {
                std::cout << line << std::endl;
                lexer.checkLine(line, lineNb);
            }
            catch (Lexer::lexicalException& e)
            {
            }
        }
        lineNb++;
    }
}

std::string trim(std::string line)
{
    size_t first = line.find_first_not_of(' ');
    size_t last = line.find_last_not_of(' ');
    return line.substr(first, (last-first+1));
}

void        standardEntryReading(Lexer & lexer)
{
    int			lineNb;
    std::string line;
    
    lineNb = 0;
    try
    {
        while (line.length() == 0 || trim(line) != "exit")
        {
            std::getline(std::cin, line);
            if (line.length() > 0)
                lexer.checkLine(line, lineNb);
            lineNb++;
        }
    }
    catch (Lexer::lexicalException& e)
    {
    }
}

void        executeInstructions(Queue & queue, Commands & commands)
{
    try
    {
        while (!queue.getQueue().empty() && !commands.getExit())
            queue.executeNextCommand();
    }
	catch (Commands::executeException &e)
    {
		
    }
	catch (std::runtime_error &e)
	{
		std::cout << "Operand factory : " << e.what();
	}
   
}

void        parseFile(Lexer & lexer)
{
    OperandFactory  factory;
    Stack           stack;
    Commands        commands(stack, factory);
    Queue           queue(commands);
    Parser          parser(queue, commands, lexer, factory);
	
	while (!parser.getList().empty())
	{
		try
		{
            std::list<std::string const> instructions = parser.getList().front();
            if (instructions.size() > 1)
            {
                std::string const line = instructions.front();
                instructions.pop_front();
                parser.checkLine(line, instructions, lexer.getLineNb().front());
            }
            else
                parser.checkLine(instructions.front(), lexer.getLineNb().front());
		}
        catch (Parser::parsingException &e)
		{
			
		}
		lexer.getLineNb().pop_front();
		parser.getList().pop_front();
	}
	if (parser.getErrorList().empty())
		executeInstructions(queue, commands);
}

int         main(int argc, char* argv[])
{
    Lexer	lexer;

    if (argc == 1)
        standardEntryReading(lexer);
    else if (argc == 2)
        readFile(lexer, argv[1]);
    else
        std::cout << "Too much arguments : Usage - ./avm [filename]" << std::endl;
    if (lexer.getErrorList().size() > 0)
        return (-1);
    parseFile(lexer);
    return (0);
}

