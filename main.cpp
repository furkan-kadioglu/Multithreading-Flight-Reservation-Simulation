#include <iostream>
#include "Process.h"
#include "ReadyQueue.h"
#include <fstream>
#include <vector>



using namespace std;

// prints ready queue at given time 
void print(ofstream &out,vector<Process> readyQ,int _time)
{   
    out <<_time<<":";
    out<<"HEAD-";
    
    
    
    if(readyQ.size()!=0)
    {   
        for(int i=readyQ.size()-1; i>=0; i--)
        {
            out<<readyQ[i].name<<"["<<(readyQ[i].currentInstruction+1)<<"]-";
        }
        out<<"TAIL"<<endl;
    }else{
        out<<"-TAIL"<<endl;
    }

};




// prints turnaround and waiting time to output.txt for each process at the end of process
void turnaroundWaitingCalculationNPrint(ofstream &outFile, Process p)
{
    outFile<<"Turnaround time for "<<p.name<<" = "<<p.terminationTime-p.arrivalTime<<" ms"<<endl;
    outFile<<"Waiting time for "<<p.name<<" = "<<p.terminationTime-p.arrivalTime-p.executionTime<<endl;
};

//returns first process after given time 
int getFirst(int _time, vector<Process> processes)
{
    int firstId;
    for (int i = 0; i < processes.size(); i++)
    {
        if(_time<processes[i].arrivalTime && processes[firstId].arrivalTime>processes[i].arrivalTime)
        {
            firstId=i;
        }
    }
    return firstId;
};

int main(){
   

   /*
   PART I
    LOADING INSTRUCTIONS INTO PROGRAM 
        Instructions are loaded into program as 
        a int vector 
   */

    //input parameters for file streaming 
    string nameOfInstruction;
    int timeOfInstruction;
    vector<int> codes[10];


    //reads instructions' time from code files 
    for(int i=0; i<10; i++)
    {
        ifstream codeFile("code"+to_string(i+1)+".txt");
        while(codeFile>>nameOfInstruction)
        {   
            codeFile>>timeOfInstruction;
            codes[i].push_back(timeOfInstruction);
        }
        codeFile.close();
    }   
    


    /*
    PART II
        PROCESS INTO PROGRAM FROM DEFINITION.TXT 
            reads process from definition.txt 
            creates new processes
            detects first process arrived to cpu
    */
    ifstream definition("definition.txt");
    
    //input parameter for Process constructor
    string processName;
    int priority;
    string codeName;
    int arrivalTime;

    //generated from input parameter for each process 
    // code1 ==> 1
    int code;

    int firstProcessId = 0;

    //keeps all processes as a vector 
    vector<Process> processes;
    
    while(definition>>processName)
    {
        definition>>priority;
        definition>>codeName;
        definition>>arrivalTime;

        codeName = codeName.substr(4);
        code = stoi(codeName);

        Process p(processName,arrivalTime,codes[code-1],priority);
        p.id = processes.size();
        processes.push_back(p);
        
        if(processes[firstProcessId].arrivalTime>p.arrivalTime)
        {
            firstProcessId = processes.size()-1;
        }

    }
    definition.close();



    /*
    PART III
        TIME ITERATION 
        simulates time of events every 
        iteration includes completion
        of instruction
            OVERVIEW IN THREE PARTS

            checks new process arrived or not 
                while instruction is processing

            checks current process complete or not
                if current process is done then 
                decides next process will be

            time is iterated to next instruction

            In addition to overview, two parts was 
            needed because last process doesn't require 
            enter while loop (subpart I) and print is 
            required when new process arrived to queue
            (subpart II)
    */


    
    ofstream outFile("output.txt");
    ReadyQueue readyQ;
    
    print(outFile,readyQ.readyQ,0);
    

    // for a while loop iteration first process is provided beforehand
    Process p = processes[firstProcessId];
    processes[firstProcessId].outOfSystem = false;
    int timeOfEvent = p.arrivalTime;

    //indicates how many process hasn't arrived yet
    int remainingProcess = processes.size()-1;
    
    
    
    while(!readyQ.readyQ.empty() || remainingProcess != 0)
    {
        if(timeOfEvent==processes[0].arrivalTime)
        {
            outFile<<timeOfEvent<<":HEAD-"<<p.name<<"[1]-TAIL"<<endl;
        }

       
        /*
        WHILE PART 1
            arrived while instruction is processing
        */
        bool added = false;
        for(int i=0; i<processes.size(); i++)
        {
            if(processes[i].arrivalTime <= timeOfEvent && processes[i].outOfSystem)
            {  
                processes[i].outOfSystem = false;
                readyQ.insert(processes[i]);
                remainingProcess -= 1;
                added = true;
                
                
            }
        }
        
      
        
        /*
        WHILE PART 2
            checks whether process is completed or not 
        */
        if(p.currentInstruction < p.code.size() )
        {   
            readyQ.insert(p);

        }else 
        {
            // decides what next process will be 
            if(!added)
            {
                print(outFile,readyQ.readyQ,timeOfEvent);
            }
            
            
            processes[p.id].terminationTime = timeOfEvent;
            p = processes[p.id];
            if(readyQ.readyQ.empty())
            {
                //i need to know next process
                p = processes[getFirst(timeOfEvent,processes)];
                readyQ.insert(processes[getFirst(timeOfEvent,processes)]);
                remainingProcess -= 1;
                print(outFile,readyQ.readyQ,p.arrivalTime);



            }   
           
            
        }

        /*
        SUBPART I
            checks whether new process arrived to ready queue by boolean variable 'added'
        */
        if(added)
        {
            print(outFile,readyQ.readyQ,timeOfEvent);
        }
        
        p = readyQ.getProcess();

        
        
        

        /*
        WHILE PART 3
            time iterated to next step
        */
        timeOfEvent += p.code[p.currentInstruction];
        processes[p.id].executionTime += p.code[p.currentInstruction];
        processes[p.id].currentInstruction += 1;
        p = processes[p.id];
        

        
        /*
        SUBPART II
            time iteration of last process
        */
        if(readyQ.readyQ.empty() && remainingProcess == 0)
        {
            for(int i=1; i<p.code.size(); i++)
            {
                processes[p.id].executionTime += p.code[i];
                timeOfEvent += p.code[i];
            }
            processes[p.id].terminationTime = timeOfEvent;
        }

        //END OF THE WHILE LOOP FOR TIME ITERTION 
    }
    
    print(outFile,readyQ.readyQ,timeOfEvent);
    

    





    /*
    PART IV 
        PRINT FOR TURNAROUND & WAITING
    */

    outFile<<endl;
    
    for(int i=0; i < processes.size(); i++)
    {
        turnaroundWaitingCalculationNPrint(outFile,processes[i]);
    }
    


    

}
