//
//  queue.cpp
//  abstract_vm
//
//  Created by Clement BARBISAN on 3/23/16.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#include "QueueFunctions.h"

bool Queue::addFunctionToQueue(std::string name)
{
    std::vector<std::string> vec;
    vec.push_back(name);
    _queue.push(vec);
    return (true);
}