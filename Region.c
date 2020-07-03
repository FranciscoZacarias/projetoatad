/**
 * @file Region.c
 * 
 * @brief Provides an implementation of the Region data structure
 * 
 * @authors Francisco Zacarias nº190221105, João Rosete nº190221109
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Region.h"

PtRegion regionCreate(char *name, char *capital, float area, int population)
{
    PtRegion region = (PtRegion)malloc(sizeof(Region));
    if (region == NULL) return NULL;
    
    strcpy(region->name, name);
    strcpy(region->capital, capital);
    
    region->population = population;
    region->area = area;

    return region;
}

int regionDestroy(PtRegion *ptRegion)
{
    PtRegion region = *ptRegion;
    if (region == NULL) return REGION_NULL;

    free(region);

    *ptRegion = NULL;

    return REGION_OK;
}

void regionPrint(PtRegion ptRegion)
{
    if(ptRegion == NULL) 
    {
        printf("(REGION NULL)");
        return;
    }
    
    printf("REGION(Name: %s | Capital: %s | Area: %.2f | Population: %d)\n",
            ptRegion->name, ptRegion->capital, ptRegion->area, ptRegion->population);
}

void regionCopy(PtRegion original, PtRegion *copy)
{
    *copy = regionCreate(original->name, original->capital, original->area, original->population);
}