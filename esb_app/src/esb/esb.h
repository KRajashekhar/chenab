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

#endif
