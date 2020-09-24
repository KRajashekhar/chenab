/*
 *
 * @brief Parameters required for 
 * mysql_real_connect() function are declared as
 * global variables.
 * 
 */
#ifndef CONNECTION_H
#define CONNECTION_H




#define SERVER "localhost"   /*hostname*/
#define USER  "root"     /*username*/
#define PASSWORD    "prabhakars 589b"       /*blank password this user*/
#define DATABASE "esb_db"   /*name of the database*/
#define PORT  3306         /*port number*/
#define UNIX_SOCKET NULL   /*unix socket*/
#define FLAG 0             /*last parameter to mysql_real_connect*/


typedef struct transport_config_data
{
    char * config_key;
    char * config_value;
}transport_config;

typedef struct transform_config_data
{
    char * config_key;
    char * config_value;
}transform_config;


typedef struct Qinfo { 
    int id;
    char * sender;
    char * destination;
    char * message_type;
    char * data_location;
}task_node_info;



int insert_to_esb_request(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details,char *received_on);

int active_routes_from_source(char *sender,char * destination,char * message_type);

int check_id_in_transform_config(int route_id);

int check_id_in_transport_config(int route_id);
 
int select_status(char * status);

int  update_esb_request(char * status,int index);

task_node_info * select_task_info(void);

int active_routes_from_source(char *sender,char * destination, char * message_type);

char * call_function(const char *name, void* data ,void * data1);

transform_config *  fetch_transform_config_key_and_value(int route_id);

transport_config *  fetch_transport_config_key_and_value(int route_id);



 

#endif

