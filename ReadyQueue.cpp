#include <iostream>
#include <fstream>
#include <vector>
#include "Process.h"
#include "ReadyQueue.h"

using namespace std;




//adds given process to ready queue
void ReadyQueue::insert(Process p)
{
    readyQ.push_back(p);
    sort(readyQ.begin(), readyQ.end());
};

//returns highest priority process in the ready queue
Process ReadyQueue::getProcess()
{
    Process p = readyQ[readyQ.size()-1];
    readyQ.pop_back();
    return p;
};


//returns highest priority in the ready queue
int ReadyQueue::getPriority()
{
    Process p = readyQ[readyQ.size()-1];
    return p.priority;
}

