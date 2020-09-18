#include <stdio.h>
#include "../bmd_extract/xml.h"
#include "../db_access/connection.h"
#include "../adapter/adapter.h"



#ifndef ESB_H
#define ESB_H

int queue_the_request(bmd *b,char *file_path);
int process_esb_request(char* bmd_file_path);
task_node_info *  fetch_new_request_from_db();
void *poll_database_for_new_requets(void *vargp);
void free_transport_config(transport_config * config);
void free_transform_config(transform_config * config);
void free_request(task_node_info *t);
char *get_dir_name(const char *s);
void free_bmd(bmd *b);
void clean_dir(char *path);



#endif
