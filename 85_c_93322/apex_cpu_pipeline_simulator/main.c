/*
 * main.c
 *
 * Author:
 * Copyright (c) 2020, Gaurav Kothari (gkothar1@binghamton.edu)
 * State University of New York at Binghamton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apex_cpu.h"
int isForwarding = 0; // 1 FOR FORWARDING AND 0 FOR NO FORWARDING
int isDisplay = 0;    // 1 FOR DISPLAY and 0 FOR SIMULATE
int numOfCycles = 0;
int main(int argc, char const *argv[])
{
    APEX_CPU *cpu;
    // fprintf("APEX_Help: Usage %s \n", argv[1]);
    fprintf(stderr, "APEX CPU Pipeline Simulator v%0.1lf\n", VERSION);

    if (argc != 4)
    {
        fprintf(stderr, "APEX_Help: Usage %s <input_file>\n", argv[0]);
        exit(1);
    }
    numOfCycles = atoi(argv[3]);

    char step[2];
    step[0] = argv[2][0];
    step[1] = '\0';
    if (strcmp(step, "s") == 0)
    {
        isDisplay = 0;
    }
    else
    {
        isDisplay = 1;
    }

    cpu = APEX_cpu_init(argv[1]);
    if (!cpu)
    {
        fprintf(stderr, "APEX_Error: Unable to initialize CPU\n");
        exit(1);
    }

    APEX_cpu_run(cpu);
    APEX_cpu_stop(cpu);
    return 0;
}