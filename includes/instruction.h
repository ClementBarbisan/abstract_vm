#ifndef INSTRUCTION_H
# define INSTRUCTION_H

#include <string>
#include <IOperand.h>

struct  s_instruct
{
    std::string     func;
    IOperand const  *value;
};

#endif /* lineFunc_h */
