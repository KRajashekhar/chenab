#include <stdio.h>
#include <unistd.h>
#include "esb.h"
// #include "../task_queue/task_queue.h"
#include "../db_access/connection.h"


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

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requests(void *vargp)
{
    // Step 1: Open a DB connection
    int i = 0;
  //  while (i < 99)
   // {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
        task_node_info * tn;
        /**
         * Step 3:
         */
        if ((tn=fetch_new_request_from_db(tn))!=NULL)
        {
            /**
              * Found a new request, so we will now process it.
              * See the ESB specs to find out what needs to be done
              * in this step. Basically, you will be doing:
              * 1. Find if there is any transformation to be applied to
              *    the payload before transporting it to destination.
              * 2. If needed, transform the request.
              * 3. Transport the transformed data to destination.
              * 4. Update the status of the request in esb_requests table
              *    to mark it as done (or error) depending on the outcomes
              *    of this step.
              * 5. Cleanup
              */
              
              printf("yesss\n\n");
              printf("%d\n",tn->id);
              
               if(update_esb_request("PROCESSING",tn->id) == -1){
                    fprintf(stderr,"cannot update status in esb\n");
                    return NULL;
               }
               
               printf("Applying transformation and transporting steps.\n");
               transport_config * tp = fetch_transport_config_key_and_value(tn->id);
               transform_config * tf = fetch_transform_config_key_and_value(tn->id);
                         
               if(tp && tf ){
               
                /** 
                 * TODO:  Transforming and transporting steps using adapter
                 *
                 */
               
               }
              

        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        //printf("Sleeping for 5 seconds.\n");
      //  sleep(5);
   // }
}
