/**
 * @file testProject.c
 * 
 * @brief This is a test for the whole project. It tests all commands implemented.
 * This is meant to help find any errors with valgrind (such as memory leaks),
 * and compare execution times between using Maps and Lists using different 
 * implementations (such as ArrayList and LinkedList)
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "../Command.h"

void growthCOMMAND(PtList list); 

int main(int argc, char** argv)
{
    int iterations = 1;
    if(argc > 1) iterations = atoi(argv[1]);


    for(int i = 0; i < iterations; i++)
    {
        PtList patient_list = listCreate(3129);
        PtMap region_map = mapCreate(19);
        long int id;
        
        // Commands
        loadPatientsIntoList("patients.csv", patient_list);
        loadRegionIntoMap("regions.csv", region_map);
        printf("\nAVERAGE:\n");
        average(patient_list);
        printf("\nFOLLOW:\n");
        follow(patient_list, 1000000003);
        follow(patient_list, 1000000174);
        printf("\n\nSEX:\n");
        sex(patient_list);
        printf("\nSHOW:\n");
        show(patient_list, 1000000020);
        printf("\nTOP:\n");
        top(patient_list);
        printf("\nOLDEST:\n");
        oldest(patient_list);
        printf("\nGROWTH:\n");
        growthCOMMAND(patient_list);
        printf("\nMATRIX:\n");
        matrix(patient_list);
        printf("\nREGIONS:\n");
        regions(patient_list, region_map);
        printf("\nREPORT:\n");
        report(patient_list, region_map);

        // Clear allocated memory
        clearMemory(&patient_list, &region_map);  
    }
}

void growthCOMMAND(PtList list)
{
    PtDate date = dateCreate(25, 02, 2020);
    growth(list, date);
    dateDestroy(&date);
}