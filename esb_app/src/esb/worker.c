#include <stdio.h>
#include <unistd.h>
#include "esb.h"
#include "../adapter/adapter.h"
#include <string.h>
// #include "../task_queue/task_queue.h"
#include "../db_access/connection.h"
#include "../bmd_extract/xml.h"


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
   while (i < 99)
   {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
        task_node_info * tn;
        char * content;
        char * transform_file_name; 
        char * file_name;
        
        /**
         * Step 3:
         */
        if ((tn=fetch_new_request_from_db())!=NULL)
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
              printf("%d\n",tn->id);
              
               if(update_esb_request("PROCESSING",tn->id) == -1){
                    fprintf(stderr,"cannot update status in esb\n");
                    return NULL;
               }

               int id = active_routes_from_source(tn->sender,tn->destination,tn->message_type);
               printf("id is %d \n",id);
               
               printf("Applying transformation and transporting steps.\n");
               transport_config * tp = fetch_transport_config_key_and_value(id);
	       transform_config * tf= fetch_transform_config_key_and_value(id);
               
               printf("data->location is %s\n ",tn->data_location);

               bmd * bd1 = parse_bmd_xml(((char *)tn->data_location));




               printf("%s\n%s\n-----\n%s\n%s\n",tf->config_key,tf->config_value,tp->config_key,tp->config_value);         
               if((tp!=NULL) && ((strcmp(tf->config_value,"string"))==0))
               {           
                  content = call_function(tp->config_key,tp->config_value,bd1->payload);
                  printf("content is \n %s\n",content);
                  file_name =  (char *) call_function("convert_to_json",content,bd1->payload);
                  printf("%s\n",file_name);
                  if((strcmp(((char *)call_function("email","Testmailchenab1@gmail.com",file_name)) ,"yes"))==0){
                     printf("sent the json file of destination service\n");
                      if(update_esb_request("DONE",tn->id) == -1){
                        fprintf(stderr,"cannot update status in esb\n");
                        return NULL;
                  }
               }
                     
                  else
                     printf("email cannot sent\n");         
               }
                
                else{
	          printf("WITH TRANSFORMATION\n");
                  transform_file_name = call_function(tf->config_key,bd1->payload,tf->config_value);
                  call_function(tp->config_key,tp->config_value,transform_file_name); 
                  content = call_function(tp->config_key,tp->config_value,bd1->payload);
                  printf("content is \n %s\n",content);
                  file_name =  (char *) call_function("convert_to_json",content,bd1->payload);
                  printf("%s\n",file_name);
                  if((strcmp(((char *)call_function("email","Testmailchenab1@gmail.com",file_name)) ,"yes"))==0){
                     printf("sent the json file of destination service\n");
                      if(update_esb_request("DONE",tn->id) == -1){
                        fprintf(stderr,"cannot update status in esb\n");
                        return NULL;
                  }
               }
                     
                  else
                     printf("email cannot sent\n");   
               }


        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
   }
}
