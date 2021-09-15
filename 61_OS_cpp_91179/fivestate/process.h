/*

Relationship between IOEvent::time and Process time:

IOEvent::time represents the number of time steps into a process execution that
an IO Event will occur. This value will be relative to Process::processorTime.

For example, if a Process has an IOEvent with a time value of 10, then that means 
that when the process hits it's 10th time step (i.e., Process::processorTime = 10)
it should enter a blocked state for IOEvent::duration time steps.

*/

#pragma once

#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<iomanip>

using namespace std;

struct IOEvent
{
    IOEvent() : time(-1), duration(0) {}

    long time;       // The time the event occurs during the process execution
    long duration;   // The duration that the process will be Blocked by this IOEvent
};

enum State { ready, processing, blocked, notArrived, done }; // Used to track the three process states

struct Process
{
    Process() : arrivalTime(-1), doneTime(-1), reqProcessorTime(0), processorTime(0), state(notArrived) {}

    long arrivalTime;       // When the process will start/become runnable
    long doneTime;          // Convenience variable, use this to keep track of when a process completes
    long reqProcessorTime;  // Total amount of processor time needed
    long processorTime;     // Amount of processor given to this process

    State state; // State of the process

    vector<IOEvent> ioEvents;  // The IO events for this process
    IOEvent currentEvent;      // Used to track the progress of the event when process is blocked

    void printProcess()
    {
        cout << setw(2) << arrivalTime << " |";
        cout << setw(3) << doneTime << " |";
        cout << setw(5) << reqProcessorTime << " |";
        cout << setw(3) << processorTime << " |"; 
        cout << setw(2) << state << " |";

        for (auto & event : ioEvents)
        {
            cout << " " << event.time << ", " << event.duration << ";";
        }

        cout << endl;
    }
};

// Read data from a file (param fileName) and parse it into a vector of Processes (param processVector) 
void initProcessSetFromFile(const string& fileName, vector<Process>& processVector);

// Print the state of all the processes in the vector
void printProcessStates(vector<Process>& processVector);

// Print all information about all processes from a vector (debugging function)
void printProcessSet(vector<Process>& processVector);

// Check if all of the processes are complete
bool allProcessesComplete(vector<Process>& processVector);
