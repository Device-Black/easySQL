/*****************************************************************************************************************************************
 native db_create_table(DB:handle, table[]);
 native db_drop_table(DB:handle, table[]);
 native db_table_exists(DB:handle, table[]);
 native db_add_column(DB:handle, table[], name[]);
 native db_column_exists(DB:handle, table[], column[]);
 native DBResult:db_pragma_table_info(DB:handle, table[]);
 native DBResult:db_select_all(DB:handle, table[], more[] = "");
 native db_delete(DB:handle, table[], more[] = "");

 // insert table values
 native db_insert_field(DB:handle, table[], column[], value[], id = -1);
 native db_insert_field_int(DB:handle, table[], column[], value, id = -1);
 native db_insert_field_float(DB:handle, table[], column[], Float:value, id = -1);
 
 // update table values
 native db_update_field(DB:handle, table[], column[], value[], more[] = "");
 native db_update_field_int(DB:handle, table[], column[], value, more[] = "");
 native db_update_field_float(DB:handle, table[], column[], Float:value, more[] = "");
 
 // formatting for 'more' options
 native StringColumn(string[], column[], sinal[] = "=");
 native DecimalColumn(decimal, column[], sinal[] = "=");
 native RealColumn(Float:real, column[], sinal[] = "=");
*****************************************************************************************************************************************/

#if defined easySQL_included
	#endinput
#endif
#define easySQL_included

#error 'include em atualizacao, nao me utilize ainda'

/*
static g_query[4096], DBResult:g_cache;

#pragma warning disable 239

stock db_create_table(DB:handle, table[])
{
	strcpy(g_query, "create table if not exists [%s] ([id] integer primary key asc);");
	format(g_query, sizeof g_query, g_query, table);
	db_free_result(db_query(handle, g_query));
}

stock db_drop_table(DB:handle, table[])
{
	format(g_query, sizeof g_query, "drop table [%s];", table);
	db_free_result(db_query(handle, g_query));
}

stock db_table_exists(DB:handle, table[])
{
	if(cache > DBResult:0) db_free_result(cache);
	cache = db_select(handle, table);
	return db_num_rows(cache);
}

stock db_add_column(DB:handle, table[], name[])
{
	format(query, sizeof g_query, "alter table [%s] add if not exists [%s];", table, name);
	db_free_result(db_query(handle, query));
}

stock db_column_exists(DB:handle, table[], column[])
{
	if(cache > DBResult:0) db_free_result(cache);
	format(query, sizeof g_query, "[name] = '%s'", column);
	cache = db_pragma_table_info(DB:handle, table, g_query);
}

stock DBResult:db_pragma_table_info(DB:handle, table[], more[] = "")
{
	format(g_query, sizeof g_query, "pragma_table_info('%s')", table);
	return db_select_all(handle, g_query, more);
}

stock DBResult:db_select_all(DB:handle, table[], more[] = "")
{
	format(g_query, sizeof g_query, "select * from [%s] %s;", table, more);
	return db_query(handle, g_query);
}

stock db_delete(DB:handle, table[], more[] = "")
{
	format(g_query, sizeof g_query, "delete from '%s' %s;", table, more);
	db_free_result(db_query(handle, g_query));
}

stock db_insert_field(DB:handle, table[], column[], value[], id = -1)
{
	if(id)
		format(g_query, sizeof g_query, "insert or replace into '%s' ('id', '%s') values ('%d', '%s')", table, column, id, value);
	else
		format(g_query, sizeof g_query, "insert or ignore into '%s' ('%s') values ('%s')", table, column, value);

	db_free_result(db_query(handle, g_query))

	if(id == 0)
	{
		if(cache > DBResult:0) db_free_result(cache);
		format(g_query, sizeof g_query, "where '%s' = '%s' limit '1'", column, value);
		cache = db_select(handle, table, g_query);
		id = db_get_field_assoc_int(cache, "id");
	}
	return id;
}

stock db_insert_field_int(DB:handle, table[], column[], value, id = -1)
{
	format(g_query, sizeof g_query, "%d", value);
	return db_insert_field(handle, table, column, g_query, id);
}

stock db_insert_field_float(DB:handle, table[], column[], Float:value, id = -1)
{
	format(g_query, sizeof g_query, "%f", value);
	return db_insert_field(handle, table, column, g_query, id);
}

stock db_update_field(DB:handle, table[], column[], value[], more[] = "")
{
	format(g_query, sizeof g_query, "update '%s' set '%s' = '%s' %s", table, column, value, more);
	return db_free_result(db_query(handle, g_query));
}

stock db_update_field_int(DB:handle, table[], column[], value, more[] = "")
{
	format(g_query, sizeof g_query, "update '%s' set '%s' = '%d' %s", table, column, value, more);
	return db_free_result(db_query(handle, g_query));
}

stock db_update_field_float(DB:handle, table[], column[], Float:value, more[] = "")
{
	format(g_query, sizeof g_query, "update '%s' set '%s' = '%f' %s", table, column, value, more);
	return db_free_result(db_query(handle, g_query));
}

stock StringColumn(string[], column[], sinal[] = "=")
{
	static str[510];
	format(str, sizeof str, "where '%s' %s '%s'", column, sinal, string);
	return str;
}

stock DecimalColumn(decimal, column[], sinal[] = "=")
{
	static str[510];
	format(str, sizeof str, "where '%s' %s '%s'", column, sinal, decimal);
	return str;
}

stock RealColumn(Float:real, column[], sinal[] = "=")
{
	static str[510];
	format(str, sizeof str, "where '%s' %s '%s'", column, sinal, real);
	return str;
}

#pragma warning enable 239
*/
