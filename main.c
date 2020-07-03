/* 
* PROJETO  ATAD 2019-20
*
* Francisco Zacarias nº190221105
* João Rosete nº190221109
*
* Turma: 1ºL_EI-01
* Docente Laboratório: Patrícia Macedo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "Command.h"

typedef char String[255];

/**
 * @brief Main loop of the project
 * 
 * @param argc How many arguments were given when program was called
 * @param argv Vector with arguments given when program was called
 * 
 * @return int EXIT_SUCCESS  
 */
int main(int argc, char** argv) 
{
	PtList patient_list = NULL;
	PtMap region_map = NULL;
	String command;
	int quit = 0;
	long int id;

	setlocale(LC_ALL, "PT");
	while (!quit) 
	{	
		printCommandsMenu();
		fgets(command, sizeof(command), stdin);
		command[strlen(command) - 1] = '\0';
		
		if (equalsStringIgnoreCase(command, "QUIT")) 
		{
			quit = 1;
		}
		else if (equalsStringIgnoreCase(command, "LOADP")) 
		{
			loadPatients(&patient_list);
		}
		else if (equalsStringIgnoreCase(command, "LOADR")) 
		{
			loadRegions(&region_map);
		}
		else if (equalsStringIgnoreCase(command, "CLEAR")) 
		{
			clearMemory(&patient_list, &region_map);
		}
		else if (equalsStringIgnoreCase(command, "AVERAGE")) 
		{
			average(patient_list);
		}
		else if (equalsStringIgnoreCase(command, "FOLLOW")) 
		{
			String id; printf("ID> "); 
			fgets(id, sizeof(command), stdin);
			follow(patient_list, strtol(id, NULL, 10));
		}
		else if (equalsStringIgnoreCase(command, "SEX")) 
		{
			sex(patient_list);
		}
		else if (equalsStringIgnoreCase(command, "SHOW"))
		{
			String id; printf("ID> "); 
			fgets(id, sizeof(command), stdin);
			show(patient_list, strtol(id, NULL, 10));
		}
		else if (equalsStringIgnoreCase(command, "TOP5")) 
		{
			top(patient_list);
		}
		else if (equalsStringIgnoreCase(command, "OLDEST")) 
		{
			oldest(patient_list);
		}
		else if (equalsStringIgnoreCase(command, "GROWTH")) 
		{
			String dt; printf("DATE (DD/MM/YYYY)> ");
			fgets(dt, sizeof(command), stdin);
			char **tokens = split(dt, 3, "/");
			PtDate date = dateCreate(atoi(tokens[0]), atoi(tokens[1]), atoi(tokens[2]));
			free(tokens);
			growth(patient_list, date);
			dateDestroy(&date);
		}	
		else if (equalsStringIgnoreCase(command, "MATRIX")) 
		{
			matrix(patient_list);
		}
		else if (equalsStringIgnoreCase(command, "REGIONS")) 
		{
			regions(patient_list, region_map);
		}	
		else if (equalsStringIgnoreCase(command, "REPORT")) 
		{
			report(patient_list, region_map);
		}
		else 
		{
			printf("%s : Comando não encontrado.\n", command);
		}
	}

	clearMemory(&patient_list, &region_map);

	return (EXIT_SUCCESS);
}