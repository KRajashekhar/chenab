#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "xml.h"
#include <string.h>
#include "../db_access/connection.h"

int main()
{

    char  * filepath= "../test_files/dum1.xml";
    bmd  * bd = (bmd*) malloc (sizeof(bmd));
    bd = parse_bmd_xml(filepath);
    printf("%s",bd->envelope->CreationDateTime);
    printf("%d\n",insert_to_esb_request ( bd->envelope->Sender, bd->envelope->Destination, bd->envelope->MessageType,
    		bd->envelope->ReferenceID, bd->envelope->MessageID,    \ 
    		"", "received","", bd->envelope->CreationDateTime));
     printf("\n------%d-------\n",is_bmd_valid(bd));
                              
    return 0;
}
