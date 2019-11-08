#ifndef _READY_QUEUE_H_
#define _READY_QUEUE_H_
#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"

using namespace std;




class ReadyQueue {


    public:
        //keeps process as a vector 
        vector<Process> readyQ;

        /*
        enqueues the process to ready queue
        */
        void insert(Process p);
        
        /*
        returns process which has highest priority
        and dequeue it.
        */
        Process getProcess();
        

        /*
        returns highest priority value
        */
        int getPriority();
        

};

#endif