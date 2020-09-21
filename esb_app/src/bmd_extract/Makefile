

LIBXML_LIBS :=  -I/usr/include/libxml2 -lxml2
SQL_LIBS   :=  -I/usr/local/mysql/lib -lmysqlclient -lz

xml: validate_bmd_request.c xml_parser.c ../db_access/select_active_route_id.c ../db_access/insert_to_esb_request.c  ../db_access/check_id_in_transform_config.c ../db_access/check_id_in_transport_config.c
	gcc  -Wall  -o xml main.c validate_bmd_request.c  ../db_access/insert_to_esb_request.c \
	xml_parser.c \
	../db_access/select_active_route_id.c ../db_access/check_id_in_transform_config.c         \
	../db_access/check_id_in_transport_config.c  ${LIBXML_LIBS}  ${SQL_LIBS}




clean:
	rm *.o xml
