#include "process.h"

#include <chrono> // for sleep
#include <thread> // for sleep

int main(int argc, char* argv[])
{
    // single thread processor
    // it's either processing something or it's not
    bool processorAvailable = true;
    // acts as a processorAvailable in the for loop
    bool tempAvailable = true;
    // vector of processes, fill by reading from a file
    vector<Process> processList;
    // number of processes in the processList
    unsigned long processes;
    // tracks the event number in the processes 
    vector<unsigned long>  eventIndex;
    // tracks the time an event has been active
    vector<long> eventDuration;
    
    // Do not touch
    long time = 1;
    long sleepDuration = 50;
    string file;
    stringstream ss;

    // Do not touch
    switch(argc)
    {
        case 1:
            file = "procList.txt";  // default input file
            break;
        case 2:
            file = argv[1];         // file given from command line
            break;
        case 3:
            file = argv[1];         // file given
            ss.str(argv[2]);        // sleep duration given
            ss >> sleepDuration;
            break;
        default:
            cerr << "incorrect number of command line arguments" << endl;
            cout << "usage: " << argv[0] << " [file] [sleepDuration]" << endl;
            return 1;
            break;
    }

    // Read in from the file
    initProcessSetFromFile(file, processList);
    processes = processList.size();
    // reserve data for the vectors
    eventIndex.reserve(processes);
    eventDuration.reserve(processes);

    // fill the vectors 
    for ( unsigned long i = 0; i < processes; i++ )
    {
        eventIndex.push_back(0);
        eventDuration.push_back(0);
    }

    // main loop for processing functionality
    while( allProcessesComplete(processList) == false )
    {
        // processes all the processes in processList
        for ( unsigned long i = 0; i < processes; i++ )
        {
            // checks for processes that have not arrived
            if ( processList.at(i).state == notArrived )
            {
                if ( processList.at(i).arrivalTime == time )
                {
                    processList.at(i).state = ready;

                    // setting the first currentEvent
                    if ( processList.at(i).ioEvents.size() != 0 )
                        processList.at(i).currentEvent = processList.at(i).ioEvents.at(0);

                    // Handling of 0 processing time process
                    if ( processList.at(i).reqProcessorTime == 0 )
                    {
                        processList.at(i).state = done;
                        processList.at(i).processorTime = 0;
                        processList.at(i).doneTime = time;
                    }
                }
            }

            if ( processorAvailable == true )
            {
                // processes the next available process
                for ( unsigned long j = 0; j < processes; j++ )
                {
                    if ( ( processList.at(j).state == ready ) && ( tempAvailable == true ))
                    {
                        tempAvailable = false;
                        processorAvailable = tempAvailable;
                        processList.at(j).state = processing;
                    }
                }
            }    

            // Sets processes that are finished to done and block the process if there is an ioevent
            if ( processList.at(i).state == processing )
            {
                processList.at(i).processorTime++;
                    
                if ( processList.at(i).processorTime == processList.at(i).reqProcessorTime )
                {
                    processList.at(i).state = done;
                    processList.at(i).doneTime = time;
                    processorAvailable = true;
                }

                else if (( processList.at(i).ioEvents.size() != 0 ) && ( processList.at(i).currentEvent.time == processList.at(i).processorTime ))
                {
                    processList.at(i).state = blocked;
                    processorAvailable = true;
                }    
            }

            // Unblocks processes if their ioevent is finished and continues if it is not finished 
            if ( processList.at(i).state == blocked )
            {
                eventDuration.at(i)++; 

                if ( eventDuration.at(i) == processList.at(i).currentEvent.duration )
                {
                    processList.at(i).state = ready;
                    eventDuration.at(i) = 0;
                    eventIndex.at(i)++;

                    if ( eventIndex.at(i) < processList.at(i).ioEvents.size() )
                    {
                        processList.at(i).currentEvent = processList.at(i).ioEvents.at(eventIndex.at(i));
                    }
                }      
            }    
        }

        tempAvailable = processorAvailable;

        // Do not touch
        cout << time++ << '\t'; // Do not touch
        // You may wish to use a second vector of processes (you don't need to, but you can)
        printProcessStates(processList); // change processList to another vector of processes if desired
        this_thread::sleep_for(chrono::milliseconds(sleepDuration)); // Do not touch
    }

    return 0;
}
