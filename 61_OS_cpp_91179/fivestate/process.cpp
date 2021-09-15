#include "process.h"

void initProcessSetFromFile(const string& fileName, vector<Process>& processVector)
{
    stringstream ss;
    ifstream in(fileName.c_str());
    string line, strItem;
    Process proc;
    IOEvent io;

    processVector.clear();

    if(!in.good())
    {
        cerr << "initProcessSetFromFile error     unable to open file \"" << fileName << "\"" << endl;
        return;
    }

    processVector.reserve(20);

    while(getline(in, line))
    {
        ss.clear();
        ss.str(line);

        ss >> proc.arrivalTime;

        ss >> proc.reqProcessorTime;

        proc.ioEvents.clear();
        proc.ioEvents.reserve(20);
        while(ss >> io.time)
        {
            ss >> io.duration;

            proc.ioEvents.push_back(io);
        }

        processVector.push_back(proc);
    }
}

void printProcessStates(vector<Process>& processVector)
{
    char stateChar;
    for(auto & Proc : processVector)
    {
        switch (Proc.state)
        {
            case ready:
                stateChar = 'r';
                break;
            case processing:
                stateChar = 'p';
                break;
            case blocked:
                stateChar = 'b';
                break;
            case notArrived:
                stateChar = 'n';
                break;
            case done:
                stateChar = 'd';
                break;
        }
        cout << stateChar << ' ';
    }
    cout << endl;
}

void printProcessSet(vector<Process>& processVector)
{
    cout << "AT | DT | RQPT | PT | S | IO" << endl;
    for(auto & Proc : processVector)
    {
        Proc.printProcess();
    }
}

bool allProcessesComplete(vector<Process>& processVector)
{
    for(auto & Proc : processVector)
    {
        if(Proc.state != done)
        {
            return false;
        }
    }

    return true;
}
