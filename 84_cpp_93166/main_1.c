#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"

//start off w structs given in webcourses

typedef struct monster
{
    char *name;
    char *element;
    int population;
} monster;

typedef struct region
{
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;

typedef struct itinerary
{
    int nregions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer
{
    char *name;
    itinerary *visits;
} trainer;

//first submission attempt code - right idea for createMonster function but readMonster was wrong. redo from scratch to fix. main is wrong anyways,doesnt start w required code 

/*
monster* createMonster(char *name, char *element, int population)
{
    monster *amonster = (monster*)malloc(sizeof(monster));
    amonster->name = (char*)malloc(sizeof(char)*(strlen(name)+1)); 
    amonster->element = (char*)malloc(sizeof(char)*(strlen(element)+1)); 
    strcpy( amonster->name, name ); 
    strcpy( amonster->element, element ); 
    amonster->population = population;
    return amonster;
}
monster** readMonsters(FILE* infile, int *monsterCount)
{
    char n[15], e[15];
    int p;
    monster **a_array = malloc(*monsterCount * sizeof(struct a*)); //struct a?
    for (int i = 0; i < *monsterCount; i++) {
        
        fscanf(infile,"%s %s %d",n, e, &p);
        printf("%s %s %d\n", n, e, p);
        a_array[i] = createMonster(n,e,p);
       
    }
    return a_array;
}
int main(){
    int monsterCount;
    char name[15];
    
    FILE *fp = fopen ( "in.txt", "r" );
    fscanf(fp,"%d %s",&monsterCount,name);
    monster **mptr = readMonsters(fp,&monsterCount);
    
    printf("%s %s %d\n", (mptr)[3]->name,(mptr)[3]->element,(mptr)[3]->population);
    
    fclose(fp);
    return 0;
}
*/


//Make a monster and give it's parameters of name, element and population
monster* createMonster(char *name, char *element, int population)
{
    monster *monster = malloc(sizeof(monster));
    monster->name = malloc((strlen(name) + 1) * sizeof(char));
    monster->element = malloc((strlen(element) + 1) * sizeof(char));
    strcpy(monster->name, name);
    strcpy(monster->element, element);
    monster->population = population;

    return monster;
}

//Make an array of monsters by calling on the createMonster function. Monster pointers are supposed to point to dynamically allocated monsters w fill-up info. Update passed variable ref w monsterCount
monster** readMonsters(FILE* infile, int *monsterCount)
{
    //name max length 50, element of monster length 50, pop max value 1 million
    char name[50];
    char element[50];
    int population;
    monster** monsterList = malloc(sizeof(monster) * *monsterCount);

    //for loop to go through each monsters name, element, and population
    for (int i = 0; i < *monsterCount; i++)
    {
        fscanf(infile, "%s %s %d", name, element, &population);
        monsterList[i] = createMonster(name, element, population);
        //printf("%s %s %d\n", monsterList[i]->name, monsterList[i]->element, monsterList[i]->population);
    }
    return monsterList;
}


//Split up the read region function. Need to first make the regions with the names, nmonsters, types and total population and then be able to make array of regions for each regions using the linked first half the function
//go back to the dma video. instructions say: return array of region pointers where each of them points to a dynamically allocated region


//Make a region and assign name, nmonsters, types of monsters and total population of them
region *makeRegion(FILE *infile, char *name, int nmonsters, int monsterCount, monster **monsters)
{
    char mName[50];

    region* region = malloc(sizeof(region));
    //need the +1 bc of same reason from in createMonster function
    region->name = malloc((strlen(name) + 1) * sizeof(char));
    strcpy(region->name, name);
    region->monsters = malloc(nmonsters * sizeof(monster));
    region->nmonsters = nmonsters;

    //printf("%s\n", region->name);
    //printf("%d monsters\n", nmonsters);
    int totalPop = 0;
    
    //count through number of monsters based on names

    for (int i = 0; i < nmonsters; i++)
    {
        fscanf(infile, "%s", mName);
        for (int j = 0; j < monsterCount; j++)
        {
            if (strcmp(monsters[j]->name, mName) == 0)
            {
                region->monsters[i] = monsters[j];
                totalPop += monsters[j]->population;
                //printf("%s\n", region->monsters[i]->name);
            }
        }
    }

    region->total_population = totalPop;

    return region;
}



//Make array of regions by calling makeRegions function per region 

region** readRegions(FILE* infile, int *countRegions, monster** monsterList, int monsterCount)
{
    int mcount;
    char num[50];
    char name[50];

    region** regionList = malloc(sizeof(region) * *countRegions);

    //go through the regions and grab the needed info
    for (int i = 0; i < *countRegions; i++)
    {
        fscanf(infile, "%s", name);
        fscanf(infile, "%d %s", &mcount, num);

        regionList[i] = makeRegion(infile, name, mcount, monsterCount, monsterList);

        //printf("\n\n");
    }

    return regionList;
}

//Make an aray of trainers and give their respective name, captures and regions
//NEED TO RETURN THE ITINERARY DON'T FORGET 

trainer* readTrainers(FILE* infile, int *trainerCount, region** regionList, int countRegions)
{
    char num[50];
    char name[50];
    char regionName[50];
    int captures;
    int regions;

    trainer* trainerList = malloc(*trainerCount * sizeof(trainer));

    for (int i = 0; i < *trainerCount; i++)
    {
        fscanf(infile, "%s", name);
        trainerList[i].name = malloc((strlen(name) + 1) * sizeof(char));
        strcpy(trainerList[i].name, name);

        fscanf(infile, "%d %s", &captures, num);
        fscanf(infile, "%d %s", &regions, num);

        trainerList[i].visits = malloc(sizeof(itinerary));
        trainerList[i].visits->nregions = regions;
        trainerList[i].visits->captures = captures;

        trainerList[i].visits->regions = malloc(regions * sizeof(region));

        //printf("%s\n", trainerList[i].name);
        //printf("%d captures\n", trainerList[i].visits->captures);
        //printf("%d regions\n", regions);

        for (int j = 0; j < regions; j++)
        {
            fscanf(infile, "%s", regionName);
            for (int k = 0; k < countRegions; k++)
            {
                if (strcmp(regionList[k]->name, regionName) == 0)
                {
                    trainerList[i].visits->regions[j] = regionList[k];
                    //printf("%s\n", trainerList[i].visits->regions[j]->name);
                }
            }
        }
        //printf("\n");
    }
    return trainerList;
}

//Use the itinerary to search and calculate the amount of monsters caught by a trainer in each region
void process_inputs(FILE *ofp, monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer *trainerList, int trainerCount)
{
  for (int i = 0; i < trainerCount; i++)
    {
      fprintf (ofp, "%s\n", trainerList[i].name);
      printf ("%s\n", trainerList[i].name);
      for (int j = 0; j < trainerList[i].visits->nregions; j++)
	{
	  int mPopulation;
	  fprintf (ofp, "%s\n", trainerList[i].visits->regions[j]->name);
	  printf ("%s\n", trainerList[i].visits->regions[j]->name);
	  for (int k = 0; k < trainerList[i].visits->regions[j]->nmonsters; k++)
	    {
	      int tPopulation = trainerList[i].visits->regions[j]->monsters[k]->population;
	      int captures = trainerList[i].visits->captures;
	      float mcount = (double) tPopulation / trainerList[i].visits->regions[j]->total_population;
	      mcount *= captures;
	      int caught = round (mcount);
	      if (caught != 0)
		{
		  fprintf (ofp, "%d %s\n", caught, trainerList[i].visits->regions[j]->monsters[k]->name);
		  printf ("%d %s\n", caught, trainerList[i].visits->regions[j]->monsters[k]->name);
		}
	    }
	  mPopulation = 0;
	}
      if (i < trainerCount - 1)
	{
	  fprintf (ofp, "\n");
	  printf ("\n");
	}
    }
}



//Release all memory that has been allocated through the prograam and for all the structures
void release_memory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount)
{

    //release monster count memory
    for (int i = 0; i < monsterCount; i++)
    {
        free(monsterList[i]->name);
        free(monsterList[i]->element);
        free(monsterList[i]);
    }

    free(monsterList);

    //release region count memory

    for (int i = 0; i < regionCount; i++)
    {
        free(regionList[i]->name);
        free(regionList[i]->monsters);
        free(regionList[i]);
    }

    free(regionList);

    //release trainerCount memory

    for (int i = 0; i < trainerCount; i++)
    {
        free(trainerList[i].name);
        free(trainerList[i].visits->regions);
        free(trainerList[i].visits);
    }
    free(trainerList);
}


//Go through and scan the functions: monsterCount, regionCount, trainerCount, and then intake and process the inputs and release the memory and write the data
int main(void)
{
    atexit(report_mem_leak); //for memory leak detector.
    FILE *inFile, *outFile;

    inFile = fopen("in.txt", "r");
    

    if (inFile != NULL)
    {
        char temp[50];
        int monsterCount;
        int regionCount;
        int trainerCount;

        fscanf(inFile, "%d %s", &monsterCount, temp);

        monster** monsterList = readMonsters(inFile, &monsterCount);

        fscanf(inFile, "%d %s", &regionCount, temp);

        region** regionList = readRegions(inFile, &regionCount, monsterList, monsterCount);

        fscanf(inFile, "%d %s", &trainerCount, temp);

        trainer* trainerList = readTrainers(inFile, &trainerCount, regionList, regionCount);

        outFile = fopen("out.txt", "w");

        process_inputs(outFile, monsterList, monsterCount, regionList, regionCount, trainerList, trainerCount);

        release_memory(monsterList, monsterCount, regionList, regionCount, trainerList, trainerCount);

        fclose(inFile);
        fclose(outFile);
    }
    else
    {
        printf("Please provide correct input file");
        exit(-1);
    }

    return 0;
}