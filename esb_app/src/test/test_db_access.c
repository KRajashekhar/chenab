#include <stdio.h>
#include <stdlib.h>
#include "munit.h"
//#include "munit.c"
#include "../bmd_extract/xml.h"
#include "../db_access/connection.h"



/* Test setup function creates bmd and returns it */
static void *
esb_request_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../test_files/dum8.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}


/* Test function for esb_request */
static MunitResult
test_esb_request(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  
 int rc = insert_to_esb_request(test_bmd->envelope->Sender,
   test_bmd->envelope->Destination,test_bmd->envelope->MessageType,
   test_bmd->envelope->ReferenceID,test_bmd->envelope->MessageID,
    "","RECEIVED","",test_bmd->envelope->CreationDateTime);
    
  munit_assert_int(rc,==,1);

  rc = insert_to_esb_request(test_bmd->envelope->Sender,
    test_bmd->envelope->Destination,test_bmd->envelope->MessageType,
    test_bmd->envelope->ReferenceID,test_bmd->envelope->MessageID,
    "","RECEIVED","",test_bmd->envelope->CreationDateTime);

  munit_assert_int(rc,==,-1);


  return MUNIT_OK;
}


/* free of allocated memory*/
static void
 esb_request_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelope);
  free(b->payload);
  free(b);

}




/* Test function for transform_config */
static MunitResult
test_check_id_in_transform_config(const MunitParameter params[], void *fixture)
{

  munit_assert_int(check_id_in_transform_config(15),==,1);
  munit_assert_int(check_id_in_transform_config(1),==,-1);

  return MUNIT_OK;
}




/* Test function for transport_config */
static MunitResult
test_check_id_in_transport_config(const MunitParameter params[], void *fixture)
{

  munit_assert_int(check_id_in_transport_config(15),==,1);
  munit_assert_int(check_id_in_transport_config(1),==,-1);

  return MUNIT_OK;
}


/* Test setup function creates bmd and returns it */
static void *
select_active_route_id_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}


/* Test function for esb_request */
static MunitResult
test_select_active_route_id(const MunitParameter params[], void *fixture)
{
  bmd *test_bmd = (bmd *)fixture;
  
 int rc = active_routes_from_source(test_bmd->envelope->Sender,
    test_bmd->envelope->Destination,test_bmd->envelope->MessageType);
    
    munit_assert_int(rc,==,15);

  rc = active_routes_from_source(test_bmd->envelope->Sender,
    "hjhbj",test_bmd->envelope->MessageType);  

  munit_assert_int(rc,==,-1);


  return MUNIT_OK;
}


/* free of allocated memory*/
static void
select_active_route_id_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelope);
  free(b->payload);
  free(b);

}




/* Test function for update_esb_request */
static MunitResult
test_update_esb_request(const MunitParameter params[], void *fixture)
{
    
  munit_assert_int(update_esb_request("PROCESSING",1),==,1);
  munit_assert_int(update_esb_request("PROCESSING",1),==,-1);
  munit_assert_int(update_esb_request("PROCESSING",1),==,-1);
  munit_assert_int(update_esb_request("DONE",1),==,1);
  munit_assert_int(update_esb_request("RECEIVED",1),==,1);

  return MUNIT_OK;
}



/* Test setup function creates bmd and returns it */
static void *
test_fetch_transform_config_key_and_value_setup(const MunitParameter params[], void *user_data)
{

  transform_config * tf= fetch_transform_config_key_and_value(15);
  return tf;
}



/* Test function for update_esb_request */
static MunitResult
test_fetch_transform_config_key_and_value(const MunitParameter params[], void *fixture)
{
  transform_config * tf = (transform_config *)fixture;

  munit_assert_string_equal(tf->config_key,"NO");
  munit_assert_string_equal(tf->config_value,"string");
  
  munit_assert_null(fetch_transform_config_key_and_value(1));

  return MUNIT_OK;
}


/* free of allocated memory*/
static void
test_fetch_transform_config_key_and_value_tear_down(void *fixture)
{
  transform_config * tf = (transform_config *)fixture;

  free(tf->config_key);
  free(tf->config_value);
  free(tf);
}


/* Test setup function creates bmd and returns it */
static void *
test_fetch_transport_config_key_and_value_setup(const MunitParameter params[], void *user_data)
{

  transport_config * tf= fetch_transport_config_key_and_value(15);
  return tf;
}


/* Test function for update_esb_request */
static MunitResult
test_fetch_transport_config_key_and_value(const MunitParameter params[], void *fixture)
{
  transport_config * tf = (transport_config *)fixture;

  munit_assert_string_equal(tf->config_key,"APIURL");
  munit_assert_string_equal(tf->config_value,"https://ifsc.razorpay.com/");
  
  munit_assert_null(fetch_transform_config_key_and_value(1));

  return MUNIT_OK;
}


/* free of allocated memory*/
static void
test_fetch_transport_config_key_and_value_tear_down(void *fixture)
{
  transport_config * tf = (transport_config *)fixture;

  free(tf->config_key);
  free(tf->config_value);
  free(tf);

}




/* Test setup function creates bmd and returns it */
static void *
test_select_task_info_setup(const MunitParameter params[], void *user_data)
{

  task_node_info * tf= select_task_info();
  return tf;
}


/* Test function for update_esb_request */
static MunitResult
test_select_task_info(const MunitParameter params[], void *fixture)
{
  task_node_info * tf = (task_node_info  *)fixture;

  
  munit_assert_ptr_not_null(tf);

  return MUNIT_OK;
}


/* free of allocated memory*/
static void
test_select_task_info_tear_down(void *fixture)
{
  task_node_info  * tf = (task_node_info *)fixture;

  free(tf->message_type);
  free(tf->sender);
  free(tf->data_location);
  free(tf->destination);
  free(tf);

}



/* Test function for esb_request */
static MunitResult
test_select_status(const MunitParameter params[], void *fixture)
{
  
  munit_assert_int(select_status("RECEIVED"),>=,1);
  munit_assert_int(select_status("status"),==,-1);
  return MUNIT_OK;
}



/* Put all unit tests here. */
MunitTest db_access_functions_tests[] = {
    {
        "/insert_esb_request_test",   /* name */
        test_esb_request,      /* test function */
        esb_request_setup,     /* setup function for the test */
        esb_request_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        NULL                     /* parameters */
    },

    {
        "/check_id_in _transform_config_test",   /* name */
        test_check_id_in_transform_config,      /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */
    },

    {
        "/check_id_in _transport_config_test",   /* name */
        test_check_id_in_transport_config,      /* test function */
        NULL,     /* setup function for the test */
        NULL, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */
    },

    {
        "/select_active_route_id_test",   /* name */
        test_select_active_route_id,      /* test function */
        select_active_route_id_setup,     /* setup function for the test */
        select_active_route_id_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                  /* options */
        NULL                                     /* parameters */

    },

    
    {
        "/update_esb_request",             /* name */
        test_update_esb_request,           /* test function */
        NULL,                               /* setup function for the test */
        NULL,                              /* tear_down */
        MUNIT_TEST_OPTION_NONE,            /* options */
        NULL                               /* parameters */

    },
    
    {
       "/select_status_test",   /* name */
       test_select_status,      /* test function */
       NULL,                    /* setup function for the test */
       NULL,                    /* tear_down */
       MUNIT_TEST_OPTION_NONE,  /* options */
       NULL                     /* parameters */
    },


    {
       "/fetch_transform_config_key_and_value_test",        /* name */
        test_fetch_transform_config_key_and_value,          /* test function */
        test_fetch_transform_config_key_and_value_setup,     /* setup function for the test */
        test_fetch_transform_config_key_and_value_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                              /* options */
        NULL                                                 /* parameters */
    },


    {
        "/fetch_transport_config_key_and_value_test",        /* name */
        test_fetch_transport_config_key_and_value,           /* test function */
        test_fetch_transport_config_key_and_value_setup,     /* setup function for the test */
        test_fetch_transport_config_key_and_value_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                              /* options */
        NULL                                                 /* parameters */
    },


    {
        "/select_task_info_test",        /* name */
        test_select_task_info,           /* test function */
        test_select_task_info_setup,     /* setup function for the test */
        test_select_task_info_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,                              /* options */
        NULL                                                 /* parameters */
    },


    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/db_access_functions_tests",           /* name */
    db_access_functions_tests,              /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite 
int main(int argc, const char *argv[])
{
  return munit_suite_main(&suite, NULL, argc, NULL);
}
*/
