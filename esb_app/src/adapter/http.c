
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "adapter.h"



struct memory {
  char *memory;
  size_t size;
};

static size_t
writecallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct memory *mem = (struct memory *)userp;

  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(ptr == NULL) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}



void *  tranport_to_ifsc_razorpay(void* ptr,void * ptr1)
 { 
    printf("yewe\n");
    char * s =  (char *) malloc((strlen(ptr)+strlen(ptr1)+1) * sizeof(char)); 
    strcat(s,ptr);
    strcat(s,ptr1);
    printf("Transformation for PO service: %s  : %s : %s \n", ((char*)ptr), ((char *)ptr1), s);

    CURL *curl;
    CURLcode res;
    struct memory chunk;

    chunk.memory = NULL;  /* will be grown as needed by the realloc above */
    chunk.size = 0;       /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl = curl_easy_init();

    /* specify URL to get */
  //  curl_easy_setopt(curl, CURLOPT_URL, "https://ifsc.razorpay.com/KARB0000001");

    curl_easy_setopt(curl, CURLOPT_URL, s);


    /* send all data to this function  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writecallback);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);

    /* get it! */
    res = curl_easy_perform(curl);

    /* check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
                return NULL;
    }
    else {
        /*
        * Now, our chunk.memory points to a memory block that is chunk.size
        * bytes big and contains the remote file.
        *
        * Do something nice with it!
        */

        printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
            printf("%s \n", chunk.memory);

    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl);

    free(chunk.memory);

    /* we're done with libcurl, so clean it up */
    curl_global_cleanup();

    return "yes";

}
