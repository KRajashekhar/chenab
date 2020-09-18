DB_ACCESS = ../db_access/select_active_route_id.c ../db_access/check_id_in_transport_config.c  \
            ../db_access/check_id_in_transform_config.c   ../db_access/insert_to_esb_request.c 

DB_ACCESS1 = ../db_access/select_status.c ../db_access/fetch_transform_config_key_and_value.c  \
            ../db_access/fetch_transport_config_key_and_value.c   ../db_access/update_esb_request.c \
			../db_access/select_task_info.c

XML_HANDLER = ../bmd_extract/xml_parser.c ../bmd_extract/validate_bmd_request.c
INCLUDE = `mysql_config --cflags --libs` `xml2-config --cflags` `xml2-config --libs`
test: ${DB_ACCESS} ${XML_HANDLER}
	gcc  ${DB_ACCESS} ${DB_ACCESS1} ${XML_HANDLER} test_bmd.c -o test ../esb/esb.c ${INCLUDE}  munit.c





clean :
	rm test	
	rm test1
