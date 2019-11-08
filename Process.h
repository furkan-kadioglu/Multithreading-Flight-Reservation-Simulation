#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


class Process{

    public:

        //given data 
        string name;
        int arrivalTime;
        vector<int> code;
        int priority;


        //calculated data 
        int terminationTime;
        int executionTime;

        //which process will be executed by cpu
        int currentInstruction;

        //shows process arrived to ready queue or not 
        bool outOfSystem;

        //shows index of process in processes vector
        int id;

        //name of this function is very descriptive :)
        void turnaroundWaitingCalculationNPrint(ofstream &outFile);

        //shows how 2 process are compared
        bool  operator< (const Process& _process) const;

        //constructor
        Process(
            string _name,
            int _arrivalTime, 
            vector<int> _code, 
            int _priority);
        
};

#endif