#ifndef QUEUEFUNCTIONS_H
# define QUEUEFUNCTIONS_H

# include <stdio.h>
# include <string>
# include <queue>
# include <list>
# include <instruction.h>

class Commands;

class Queue
{
    private:
        std::queue<s_instruct *>            *_queue;
        std::list<int>                      *_countLine;
        Commands               &            _commands;
        Queue();
        Queue(Queue const & cp);
        Queue & operator=(Queue const & cp);
    public:
        Queue(Commands & commands);
        ~Queue();
        void                                executeNextCommand();
        void                                addFunctionToQueue(s_instruct *instruction, int lineNb);
        std::queue<s_instruct *> const &    getQueue() const;
};

#endif /* queue_hpp */
