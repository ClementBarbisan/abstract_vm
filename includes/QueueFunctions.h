//
//  queue.hpp
//  abstract_vm
//
//  Created by Clement BARBISAN on 3/23/16.
//  Copyright © 2016 Clement BARBISAN. All rights reserved.
//

#ifndef queue_hpp
#define queue_hpp

#include <stdio.h>
#include <string>
#include <queue>
#include <vector>

class Queue
{
    private:
        std::queue< std::vector<std::string> > _queue;
    public:
        bool    addFunctionToQueue(std::string name);
    
};

#endif /* queue_hpp */
