

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "adapter.h"



#define FROM "Testmailchenab1@gmail.com"
#define CC "bpavankalyan1106@gmail.com"

struct upload_status
{
    int lines_read;
};





void *  transport_email(void* ptr,void * ptr1) 
{ 
   
   printf("email----\n");
   char * to =  (char *) malloc((strlen(ptr)+1)* sizeof(char)) ;
   to = (char *) ptr;
   char * file_path = (char *) malloc((strlen(ptr1)+1)* sizeof(char));
   file_path = (char *) ptr1;

    printf("Sending to %s\n", to);

    CURL *curl;
    CURLcode res = CURLE_OK;
    struct curl_slist *recipients = NULL;
    struct upload_status upload_ctx;

    upload_ctx.lines_read = 0;

    curl = curl_easy_init();
    if (curl)
    {
        /* Set username and password */
        curl_easy_setopt(curl, CURLOPT_USERNAME, "Testmailchenab1");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "Testmailchenab001@");

        /* URL for mail server */
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587/");

        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);

      
        /* FROM address */
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        /* Recipients */
        recipients = curl_slist_append(recipients, to);
        recipients = curl_slist_append(recipients, CC);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

      
        //curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        FILE *fp = fopen(file_path, "r");
        curl_easy_setopt(curl, CURLOPT_READDATA, fp);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

       /* Gives information about whats running inside libcurl */
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        /* Send the message */
        res = curl_easy_perform(curl);

        /* Check for errors */
        if (res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
            return "NO";
        }            

        /* Free the list of recipients */
        curl_slist_free_all(recipients);

        /* Always cleanup */
        curl_easy_cleanup(curl);
    }

   
 return  "yes";


}
