#include <QueueFunctions.h>
#include <Commands.h>

Queue::Queue(Commands & commands) : _commands(commands)
{
    _countLine = new std::list<int>();
    _queue = new std::queue<s_instruct *>();
}

Queue::~Queue()
{
    _countLine->erase(_countLine->begin(), _countLine->end());
    while (!_queue->empty())
    {
        delete _queue->front();
        _queue->pop();
    }
    delete _queue;
    delete _countLine;
}

std::queue<s_instruct *> const & Queue::getQueue() const
{
    return (*_queue);
}

void    Queue::executeNextCommand()
{
    if (_queue->front()->value != NULL)
        _commands.executeCommand(_queue->front()->func, *(_queue->front()->value), _countLine->front());
    else
        _commands.executeCommand(_queue->front()->func, _countLine->front());
    _countLine->pop_front();
    _queue->pop();
}

void    Queue::addFunctionToQueue(s_instruct *instruction, int lineNb)
{
    _queue->push(instruction);
    _countLine->push_back(lineNb);
}