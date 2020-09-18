#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "esb.h"


void free_bmd(bmd *b)
{
    free(b->envelope->Sender);
    free(b->envelope->Destination);
    free(b->envelope->MessageID);
    free(b->envelope->MessageType);
    free(b->envelope->CreationDateTime);
    free(b->envelope->Signature);
    free(b->envelope->ReferenceID);
    free(b->envelope);
    free(b->payload);
}

char *get_dir_name(const char *s)
{
    char t = '/';
    const char *last = strrchr(s, t);
    if (last != NULL)
    {
        const size_t len = (size_t)(last - s);
        char *const n = malloc(len + 1);
        memcpy(n, s, len);
        n[len] = '\0';
        return strdup(n);
    }
    return NULL;
}

void clean_dir(char *path)
{ /* Deletes the BMD file specified by the path */
    
    remove(path);
    printf("removed :%s", path);
    path = get_dir_name(path);
    /* Removes the directory created by random numberes*/
    rmdir(path);
    printf("removed :%s", path);
    free(path);
}

void free_request(task_node_info *t)
{
    clean_dir(t->data_location);
    free(t->data_location);
    free(t->message_type);
    free(t->sender);
    free(t);
}


void free_transform_config(transform_config * config)
{
    free(config->config_key);
    free(config->config_value);
    free(config);
}

void free_transport_config(transport_config * config)
{
    free(config->config_key);
    free(config->config_value);
    free(config);
}
