#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "adapter.h"




int main()
{
    char * d1 = "998";
    char * s= "jdsdsk0";
    int d =998;
    char * s1="https://ifsc.razorpay.com/";
    char * s2= "KARB0000001";
    char * file_name = (char *) call_function("APIURL", s1,s2);
    printf("%s\n", file_name);
    char * file =  (char *) call_function("convert_to_json",file_name,s2);
    printf("%s\n", file);
    printf("%s\n", (char *) call_function("email", "Testmailchenab1@gmail.com",file));
    printf("%s\n", (char *) call_function("ftp", "test",file));

    printf("%s\n", (char *) call_function("remove",file ,NULL));

    //remove(file);
    free(file_name);
    return 0;
}

