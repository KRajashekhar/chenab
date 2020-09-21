#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "adapter.h"


/**
 * @brief Creates a json file containing
 * payload data and returns the path of the file.
 * All such created files are stored in assets directory.
 * 
 * @param payload_data and unique name to find the file
 * @return char* Path of the file.
 */
void * convert_to_json(void  * payload, void * name)
{
    printf("payload to json .....");

    char bmd_name[20];
    /*Creates file name of json as per name*/

    char file[50] ;
    sprintf(file,"output_%s.json",(char *) name);

    FILE *fp;
    fp = fopen(file, "w");
    if (fp == NULL)
    {
        printf("file opening failed");
        return NULL;
    }
    /* Writes into json file */
    fprintf(fp, "\n%s\n", (char *) payload);
    /* Closes file */
    fclose(fp);
    /* returns json file
      name */
    return strdup(file);
}
/*
int main()
{
	convert_to_json("001-01-1234","first");
	return 0;
	}
	*/
