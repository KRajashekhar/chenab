
#ifndef ADAPTER_H
#define ADAPTER_H

char *  call_function(const char *name, void* data ,void * data1);
void *  tranport_to_ifsc_razorpay(void* ptr,void * ptr1);
void *  transport_email(void* ptr,void * ptr1) ;
void *  tranform_bmd_Credit_svc(void* ptr,void * ptr1);
void *  transport_bmd_Credit_svc(void* ptr,void * ptr1);
void *  convert_to_json(void* payload, void * name);


#endif
