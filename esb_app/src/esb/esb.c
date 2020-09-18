#include <stdlib.h>
#include <stdio.h>
#include "../adapter/adapter.h"

#include "../bmd_extract/xml.h"

#include "esb.h"

/** Module that has mysql C API functions */

#include "../db_access/connection.h"



#if 0
task_node_info *  fetch_new_request_from_db()
{
   // 1 => OK, -1 => Errors
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
    
    // select_info picks up the oldest row in esb_request table 
    printf("Checking for new requests in esb_requests table.\n");
    task_node_info * tn = (task_node_info *) malloc(sizeof(task_node_info));
    if(( tn = select_task_info()) != NULL){
         return tn; 
    }
    
    return NULL;     
}

#endif

int queue_the_request(bmd *b,char * file_path) {
    int success = 1; // 1 => OK, -1 => Error cases

    /**
     * @brief Implements the Query:
     * INSERT INTO                            
     * esb_request(sender_id,dest_id,message_type,reference_id,      
     * message_id,data_location,status,status_details)               
     * VALUES(?,?,?,?,?,?,?,?)
     * function returns 1 on successful insertion. 
     * function is defined in db_access module
     */
    int rc = insert_to_esb_request(b->envelope->Sender,
    b->envelope->Destination,b->envelope->MessageType,
    b->envelope->ReferenceID,b->envelope->MessageID,
    file_path,"RECEIVED","",b->envelope->CreationDateTime);
    if(rc ==1)
    return success;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    
    bmd *b = parse_bmd_xml(bmd_file_path);

    /** defined in bmd_extract module*/
    if (is_bmd_valid(b)!=1)
    {
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
                printf("BMD is valid!\n");
        status = queue_the_request(b,bmd_file_path);
       if(status==1) printf("Queued..!\n");
       else          printf("NOT queued!\n");
    }
    
    return status;
}


/*
int main () {
    int status = process_esb_request("../test_files/dum1.xml");
    
    if(status != 1) {
        printf("Status[%d]: Request processing failed",status);
        return EXIT_FAILURE;
        }
        printf("Status[%d]: Request processing sucess",status);
    task_node_info * tn;
       
        if ((tn=fetch_new_request_from_db(tn))!=NULL)
        {
            
              
              printf("yesss\n\n");
              printf("%d\n",tn->id);
              
               if(update_esb_request("PROCESSING",tn->id) == -1){
                    fprintf(stderr,"cannot update status in esb\n");
                   // return NULL;
               }

               int id = active_routes_from_source(tn->sender,tn->destination,tn->message_type);
               
               printf("Applying transformation and transporting steps.\n");
               transport_config * tp = fetch_transport_config_key_and_value(id);
               transform_config * tf = fetch_transform_config_key_and_value(id);
               
               printf("data->location is %s\n ",tn->data_location);

               bmd * bd = parse_bmd_xml(tn->data_location);
                   printf("%s",bd->payload);

        }


    
      
    return EXIT_SUCCESS;
}
*/