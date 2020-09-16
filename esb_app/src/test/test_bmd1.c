#include <stdio.h>
#include "munit.h"
#include "../bmd_extract/xml.h"
#include<stdlib.h>

/**
* @brief storing entire data of a file into a string
* 
* @param file name
* @return string of entire data of a file
*/


char *get_file_data(char *file)
{
FILE  *infile;
char    *buffer;
long    numbytes;
 
/* open an existing file for reading */
infile = fopen(file, "r");
 
/* quit if the file does not exist */
if(infile == NULL)
    return NULL;
 
/* Get the number of bytes */
fseek(infile, 0L, SEEK_END);
numbytes = ftell(infile);
 
/* reset the file position indicator to 
the beginning of the file */
fseek(infile, 0L, SEEK_SET);	
 
/* grab sufficient memory for the 
buffer to hold the text */
buffer = (char*)calloc(numbytes, sizeof(char));	
 
/* memory error */
if(buffer == NULL)
    return NULL;
 
/* copy all the text into the buffer */
fread(buffer, sizeof(char), numbytes, infile);
fclose(infile);
 
/* confirm we have read the file by
outputing it to the console */
printf("The file called %s contains this text\n\n%s",file, buffer);
return buffer;
}

/* Test setup function */
static void *
xml_to_json_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum.xml";
  bmd *bd = parse_bmd_xml(file);
  char * file_created = xml_to_json(bd);
  printf("%s\n",file_created);
  /* Copy file data into string */
  char *json_data = get_file_data(file_created);
  return strdup(json_data);
}

/* Test function */
static MunitResult
test_xml_to_json(const MunitParameter params[], void *fixture)
{
  char *json_data = (char *)fixture;

  char *test_data = get_file_data("payload_test.json");
  munit_assert_string_equal(json_data, test_data);
  return MUNIT_OK;
}

static void
xml_to_json_tear_down(void *fixture)
{

  free(fixture);
}



static void *
xml_to_json1_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum1.xml";
  bmd *bd = parse_bmd_xml(file);
  char * file_created = xml_to_json(bd);
  printf("%s\n",file_created);
  /* Copy file data into string */
  char *json_data = get_file_data(file_created);
  return strdup(json_data);
}

/* Test function */
static MunitResult
test_xml_to_json1(const MunitParameter params[], void *fixture)
{
  char *json_data = (char *)fixture;

  char *test_data = get_file_data("payload_test1.json");
  munit_assert_string_equal(json_data, test_data);
  return MUNIT_OK;
}

static void
xml_to_json1_tear_down(void *fixture)
{

  free(fixture);
}


/* Test setup function creates bmd and returns it */
static void *
is_bmd_valid_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

/* Test function */
static MunitResult
test_is_bmd_valid(const MunitParameter params[], void *fixture)
{
  bmd  *test_bmd = (bmd *)fixture;
  /* is_bmd_valid returns 1 if valid */
  munit_assert(is_bmd_valid(test_bmd) == 1);
  return MUNIT_OK;
}

static void
is_bmd_valid_tear_down(void *fixture)
{
  free(fixture);
}

/* Test setup function creates bmd and returns it */
static void *
parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
  char *file = "../bmd_extract/test_files/dum.xml";
  bmd *b = parse_bmd_xml(file);
  return b;
}

bmd *get_bmd(void)
{
  bmd *bd = (bmd *) malloc(sizeof(bd));
  bmd_envelope *envl = (bmd_envelope *)malloc(sizeof(bmd_envelope));
  envl->Sender = "756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA";
  envl->Destination = "6393F82F-4687-433D-AA23-1966330381FE";
  envl->CreationDateTime = "2020-08-12T05:18:00+0000";
  envl->MessageID = "A9ECAEF2-107A-4452-9553-043B6D25386E";
  envl->MessageType = "CreditReport";
  envl->ReferenceID = "INV-PROFILE-889712";
  envl->Signature = "63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c";
  bd->envelope = envl;
  bd->payload = "001-01-1234";

  return bd;
}
/* Test function */
static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
  const char* foo;


  /* The "foo" parameter is specified as one of the following values:
   * "one", "two", or "three". */
  foo = munit_parameters_get(params, "foo");
  /* Similarly, "bar" is one of "four", "five", or "six". */
//  bar = munit_parameters_get(params, "bar");
  /* "baz" is a bit more complicated.  We don't actually specify a
   * list of valid values, so by default NULL is passed.  However, the
   * CLI will accept any value.  This is a good way to have a value
   * that is usually selected randomly by the test, but can be
   * overridden on the command line if desired. */
  /* const char* baz = munit_parameters_get(params, "baz"); */

  /* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */
  
  //printf("%s\n",(char *) foo);

  /*if (strcmp(foo, "../test_files/dum1.xml") == 0 ||
      strcmp(foo, "../test_files/dum2.xml") == 0 ||
      strcmp(foo, "../test_files/dum3.xml") == 0)
    return MUNIT_OK;*/

  bmd *test_bmd= parse_bmd_xml(foo);

  printf("testing namxnmsandm\n");

  if(strcmp(foo,"../test_files/test_xml_handle/dum.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
  {
    munit_assert_null(test_bmd->envelope->MessageID);
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  



  if(strcmp(foo,"../test_files/test_xml_handle/dum2.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_null(test_bmd->envelope->MessageType);
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum3.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_null(test_bmd->envelope->Sender);
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum4.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_null(test_bmd->envelope->Destination);
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum5.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_null(test_bmd->envelope->CreationDateTime);
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum6.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_null(test_bmd->envelope->ReferenceID);
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum7.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_null(test_bmd->envelope->Signature);
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum8.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_null(test_bmd->payload);
  }  

  
  
  return MUNIT_OK;
}

static void
parse_bmd_xml_tear_down(void *fixture)
{
  bmd *b = (bmd *)fixture;

  free(b->envelope);
  free(b->payload);
  free(b);

}


static MunitResult
test_bmd_xml(const MunitParameter params[], void* user_data) {
  const char* foo;


  /* The "foo" parameter is specified as one of the following values:
   * "one", "two", or "three". */
  foo = munit_parameters_get(params, "foo");
  /* Similarly, "bar" is one of "four", "five", or "six". */
//  bar = munit_parameters_get(params, "bar");
  /* "baz" is a bit more complicated.  We don't actually specify a
   * list of valid values, so by default NULL is passed.  However, the
   * CLI will accept any value.  This is a good way to have a value
   * that is usually selected randomly by the test, but can be
   * overridden on the command line if desired. */
  /* const char* baz = munit_parameters_get(params, "baz"); */

  /* Notice that we're returning MUNIT_FAIL instead of writing an
   * error message.  Error messages are generally preferable, since
   * they make it easier to diagnose the issue, but this is an
   * option.
   *
   * Possible values are:
   *  - MUNIT_OK: Sucess
   *  - MUNIT_FAIL: Failure
   *  - MUNIT_SKIP: The test was skipped; usually this happens when a
   *    particular feature isn't in use.  For example, if you're
   *    writing a test which uses a Wayland-only feature, but your
   *    application is running on X11.
   *  - MUNIT_ERROR: The test failed, but not because of anything you
   *    wanted to test.  For example, maybe your test downloads a
   *    remote resource and tries to parse it, but the network was
   *    down.
   */
  
  //printf("%s\n",(char *) foo);

  /*if (strcmp(foo, "../test_files/dum1.xml") == 0 ||
      strcmp(foo, "../test_files/dum2.xml") == 0 ||
      strcmp(foo, "../test_files/dum3.xml") == 0)
    return MUNIT_OK;*/

  bmd *test_bmd= parse_bmd_xml(foo);

  printf("testing namxnmsandm\n");

  if(strcmp(foo,"../test_files/test_xml_handle/dum.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum1.xml")==0)
  {
    munit_assert_null(test_bmd->envelope->MessageID);
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  



  if(strcmp(foo,"../test_files/test_xml_handle/dum2.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_null(test_bmd->envelope->MessageType);
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum3.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_null(test_bmd->envelope->Sender);
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum4.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_null(test_bmd->envelope->Destination);
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum5.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_null(test_bmd->envelope->CreationDateTime);
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum6.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_null(test_bmd->envelope->ReferenceID);
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum7.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_null(test_bmd->envelope->Signature);
    munit_assert_string_equal(test_bmd->payload,"001-01-1234");
  }  

  if(strcmp(foo,"../test_files/test_xml_handle/dum8.xml")==0)
  {
    munit_assert_string_equal(test_bmd->envelope->MessageID,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(test_bmd->envelope->MessageType,"CreditReport");
    munit_assert_string_equal(test_bmd->envelope->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(test_bmd->envelope->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(test_bmd->envelope->CreationDateTime,"2020-08-12T05:18:00+0000");
    munit_assert_string_equal(test_bmd->envelope->ReferenceID,"INV-PROFILE-889712");
    munit_assert_string_equal(test_bmd->envelope->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_null(test_bmd->payload);
  }  

  
  return MUNIT_OK;
}



static char* foo_params[] = {
// (char*) "../test_files/test_xml_handle/dum2.xml",
 (char*) "../test_files/test_xml_handle/dum.xml" , (char*) "../test_files/test_xml_handle/dum1.xml",(char*) "../test_files/test_xml_handle/dum3.xml",NULL
};

static MunitParameterEnum test_params[] = {
  { (char*) "foo", foo_params },
};


/* Put all unit tests here. */
MunitTest bmd_tests[] = {
    {
        "/parse_bmd_xml_test",   /* name */
        test_parse_bmd_xml,      /* test function */
        parse_bmd_xml_setup,     /* setup function for the test */
        parse_bmd_xml_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE,  /* options */
        test_params                     /* parameters */
    },



    {
        "/is_bmd_valid_test",   /* name */
        test_is_bmd_valid,      /* test function */
        is_bmd_valid_setup,     /* setup function for the test */
        is_bmd_valid_tear_down, /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                   /* parameters */
    },

    {
        "/xml_to_json_test",    /* name */
        test_xml_to_json,       /* test function */
        xml_to_json_setup,      /* setup function for the test */
        xml_to_json_tear_down,  /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },

    {
        "/xml_to_json1_test",    /* name */
        test_xml_to_json1,       /* test function */
        xml_to_json1_setup,      /* setup function for the test */
        xml_to_json1_tear_down,  /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */

    },

    { (char*) "/test/parameters", test_bmd_xml, NULL, NULL, MUNIT_TEST_OPTION_NONE, test_params },

    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
    "/bmd_tests",           /* name */
    bmd_tests,              /* tests */
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