
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql.h>
#include "connection.h"



#define STRING_SIZE 1000

#define SELECT_SAMPLE "SELECT id, sender_id, dest_id, message_type,data_location FROM esb_request where status = 'RECEIVED'"


task_node_info * select_task_info(void){

	MYSQL_STMT    *stmt;
	MYSQL_BIND    bind[5];
	MYSQL_RES     *prepare_meta_result;
	MYSQL_TIME    ts;
	unsigned long length[5];
	int           param_count, column_count, row_count;
	short         small_data;
	int           int_data;
	char          sender[STRING_SIZE];
	char          destination[STRING_SIZE];
	char          message_type[STRING_SIZE];
	char          data_location[STRING_SIZE];
	bool          is_null[5];
	
	
	MYSQL * mysql;

    mysql = mysql_init(NULL);
         
    if (mysql == NULL) {
       fprintf(stderr, "mysql_init() failed\n");
       return NULL;
    }  
  
    if (mysql_real_connect(mysql, SERVER,USER,PASSWORD,DATABASE,PORT,UNIX_SOCKET,FLAG) == NULL) {
	    fprintf(stderr, "Error [%d]: %s \n",mysql_errno(mysql),mysql_error(mysql));
	    mysql_close(mysql);
	    return NULL;
    }  
        
	/* Prepare a SELECT query to fetch data from test_table */
	stmt = mysql_stmt_init(mysql);
	if (!stmt)
	{
	  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
	    return NULL;
	}
	if (mysql_stmt_prepare(stmt, SELECT_SAMPLE, strlen(SELECT_SAMPLE)))
	{
	  fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}
	fprintf(stdout, " prepare, SELECT successful\n");

	/* Get the parameter count from the statement */
	param_count= mysql_stmt_param_count(stmt);
	fprintf(stdout, " total parameters in SELECT: %d\n", param_count);

	if (param_count != 0) /* validate parameter count */
	{
	  fprintf(stderr, " invalid parameter count returned by MySQL\n");
	    return NULL;
	}

	/* Fetch result set meta information */
	prepare_meta_result = mysql_stmt_result_metadata(stmt);
	if (!prepare_meta_result)
	{
	  fprintf(stderr,
		 " mysql_stmt_result_metadata(), returned no meta information\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Get total columns in the query */
	column_count= mysql_num_fields(prepare_meta_result);
	fprintf(stdout, " total columns in SELECT statement: %d\n", column_count);

	if (column_count != 5) /* validate column count */
	{
	  fprintf(stderr, " invalid column count returned by MySQL\n");
	    return NULL;
	}

	/* Execute the SELECT query */
	if (mysql_stmt_execute(stmt))
	{
	  fprintf(stderr, " mysql_stmt_execute(), failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Bind the result buffers for all 4 columns before fetching them */

	memset(bind, 0, sizeof(bind));

	/* INTEGER COLUMN */
	bind[0].buffer_type= MYSQL_TYPE_LONG;
	bind[0].buffer= (char *)&int_data;
	bind[0].is_null= &is_null[0];
	bind[0].length= &length[0];

	/* SENDER  COLUMN */
	bind[1].buffer_type= MYSQL_TYPE_STRING;
	bind[1].buffer= (char *)sender;
	bind[1].buffer_length= STRING_SIZE;
	bind[1].is_null= &is_null[1];
	bind[1].length= &length[1];

	/* DESTINATION COLUMN */
	bind[2].buffer_type= MYSQL_TYPE_STRING;
	bind[2].buffer= (char *)destination;
	bind[2].buffer_length= STRING_SIZE;
	bind[2].is_null= &is_null[2];
	bind[2].length= &length[2];
	
	
	/* MESSAGE_TYPE COLUMN */
	bind[3].buffer_type= MYSQL_TYPE_STRING;
	bind[3].buffer= (char *)message_type;
	bind[3].buffer_length= STRING_SIZE;
	bind[3].is_null= &is_null[3];
	bind[3].length= &length[3];
	
	/* DATA_LOCATION COLUMN */
	bind[4].buffer_type= MYSQL_TYPE_STRING;
	bind[4].buffer= (char *)data_location;
	bind[4].buffer_length= STRING_SIZE;
	bind[4].is_null= &is_null[4];
	bind[4].length= &length[4];

	/* Bind the result buffers */
	if (mysql_stmt_bind_result(stmt, bind))
	{
	  fprintf(stderr, " mysql_stmt_bind_result() failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Now buffer all results to client */
	if (mysql_stmt_store_result(stmt))
	{
	  fprintf(stderr, " mysql_stmt_store_result() failed\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	}

	/* Fetch all rows */
	row_count= 0;
	fprintf(stdout, "Fetching results ...\n");
	task_node_info * task_node= (task_node_info *) malloc(sizeof(task_node_info));
	if (!mysql_stmt_fetch(stmt))
	{
	  row_count++;
	  fprintf(stdout, "  row %d\n", row_count);

	  /* column 1 */
	  fprintf(stdout, "   column1 (integer)  : ");
	  if (is_null[0])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %d\n", int_data);
	    task_node->id=int_data;

	  /* column 2 */
	  fprintf(stdout, "   column2 (string)   : ");
	  if (is_null[1])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s\n", sender);
	    task_node->sender=strdup(sender);
            fprintf(stdout, " %s\n", task_node->sender);
           
	  /* column 3 */
	  fprintf(stdout, "   column3 (string) : ");
	  if (is_null[2])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s\n", destination);
	    task_node->destination=strdup(destination);
	    fprintf(stdout, " %s\n", task_node->destination);

	  /* column 4 */
	  fprintf(stdout, "   column4 (STRING): ");
	  if (is_null[3])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s\n", message_type);
	    task_node->message_type=strdup(message_type);
	    
	   /* column 5 */
	  fprintf(stdout, "   column4 (STRING): ");
	  if (is_null[3])
	    fprintf(stdout, " NULL\n");
	  else
	    fprintf(stdout, " %s\n", data_location);
	    task_node->data_location = strdup(data_location);  
	    
	    /* Free the prepared result metadata */
	   mysql_free_result(prepare_meta_result);


	  /* Close the statement */
	  if (mysql_stmt_close(stmt))
	  {
	    fprintf(stderr, " failed while closing the statement\n");
	    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	    return NULL;
	  }
	  return task_node;

	}

	/* Validate rows fetched */
	
	/* Free the prepared result metadata */
	mysql_free_result(prepare_meta_result);


	/* Close the statement */
	if (mysql_stmt_close(stmt))
	{
	  fprintf(stderr, " failed while closing the statement\n");
	  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
	return NULL;
	}
	
	return NULL;
}	

/*

int main()
{
	task_node_info * tn = select_task_info();
    fprintf(stdout, " %s\n", tn->sender);
	printf("%d\n%s\n%s\n%s\n%s\n", tn->id, tn->sender,tn->destination,tn->message_type,tn->data_location);
	printf("%d\n", active_routes_from_source(tn->sender,tn->destination,tn->message_type));
	return 0;
}
*/
