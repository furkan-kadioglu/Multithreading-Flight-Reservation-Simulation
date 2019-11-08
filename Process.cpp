#include <iostream>
#include <string>
#include <fstream>
#include "Process.h"

using namespace std;




Process::Process(
            string _name,
            int _arrivalTime, 
            vector<int> _code, 
            int _priority)
            {
                name = _name;
                arrivalTime = _arrivalTime;
                code = _code;
                priority = _priority;
                outOfSystem = true;
                currentInstruction = 0;
                executionTime = 0;
            };


/*
shows how two processes are compared 
*/
bool Process::operator< (const Process& _process)const
{
    if(priority != _process.priority)
    {
        return priority > _process.priority;
    }else 
    {
        return arrivalTime > _process.arrivalTime;
    }
    
};



