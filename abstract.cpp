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
#include <checker.h>

int main(int argc, char* argv[])
{
    Checker parser;
    //parser.addCommand("push", "push int32\\([0-9]+\\)");
    //parser.addCommand("pop", "pop");
    if (argc == 1)
    {
        std::string line;
        while (true)
        {
            std::getline(std::cin, line);
            if (parser.checkLine(line))
                std::cout << line << std::endl;
            else
                std::cout << "blop" << std::endl;
        }
    }
    else if (argc == 2)
    {
        std::cout << argv[1] << std::endl;
    }
    else
        std::cout << "Too much arguments : Usage - ./avm <filename>" << std::endl;
}

