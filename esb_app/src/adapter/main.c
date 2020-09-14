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
    printf("%s\n", (char *) call_function("PO svc tranform", s1,s2));
    printf("%s\n", (char *) call_function("PO svc transport", "bpavankalyan1106@gmail.com","file.txt"));
    //call_function("Credit service tranform", &d,s);
    return 0;
}
