XML_HANDLER = ../bmd_extract/xml_parser.c ../bmd_extract/xml.h  ../bmd_extract/validate_bmd_request.c
SQL_API     = ../db_access/insert_to_esb_request.c ../db_access/select_active_route_id.c ../db_access/check_id_in_transform_config.c ../db_access/check_id_in_transport_config.c
SQL_API1    = ../db_access/update_esb_request.c  ../db_access/select_task_info.c ../db_access/fetch_transform_config_key_and_value.c ../db_access/fetch_transport_config_key_and_value.c
ADAPTER_API = ../adapter/dynamic_lookup.c ../adapter/email.c ../adapter/http.c ../adapter/convert_to_json.c
XML_LIB     =   `xml2-config --cflags` `xml2-config --libs`
SQL_LIB     =  `mysql_config --cflags --libs`
esb: esb.c
	gcc esb.c ${XML_HANDLER} ${SQL_API} ${SQL_API1}  -o esb ${SQL_LIB} ${XML_LIB}

# worker: worker.c
#	gcc worker.c ${XML_HANDLER} ${SQL_API1}  ${ADAPTER_API} -o worker ${SQL_LIB} ${XML_LIB}


clean:
	rm esb

