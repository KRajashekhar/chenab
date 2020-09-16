
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "adapter.h"

/**
 * These should come from the header file of the respective service
 * provider's implementation of the transformation and transport.
 */






void * tranform_bmd_Credit_svc(void* ptr,void * ptr1) { printf("Transformation for Credit service: %d : %s \n", *((int*)ptr), ((char *)ptr1));
   return "YES"; }
void * transport_bmd_Credit_svc(void* ptr,void * ptr1) { printf("Transport for Credit service %d : %s \n",*((int*)ptr), ((char *)ptr1));
   return "YES"; }

/* The ESB would have this table */
const static struct
{
    const char *name;
    void *  (*func)(void*, void *);
} function_map[] = {
    {"APIURL",tranport_to_ifsc_razorpay},
    {"email", transport_email},
    {"convert_to_json",convert_to_json},
    {"Credit service tranform", tranform_bmd_Credit_svc},
    {"Credit service transport", transport_bmd_Credit_svc}
};

/* This is how the ESB may dynamically invoke the service adapter functions */
char * call_function(const char *name, void* data ,void * data1)
{
    for (int i = 0; i < (sizeof(function_map) / sizeof(function_map[0])); i++)
    {
        if (!strcmp(function_map[i].name, name) && function_map[i].func)
        {
            return function_map[i].func(data,data1);
        }
    }
    return "NO";
}
