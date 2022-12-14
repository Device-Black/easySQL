/*******************************************************

AUTHOR: DeviceBlack
MAIL: dddeviceddd@gmail.com
TIME: 02/08/2022 22:49:32 BRT

Functions:
 - SQL_CreateTable(DB:handle, name[]);
 - SQL_DropTable(DB:handle, name[]);
 - SQL_TableExists(DB:handle, table[]);
 - SQL_AddTableColumn(DB:handle, table[], name[], type[], length);
 - SQL_ColumnExists(DB:handle, table[], column[]);

 - SQL_Select(DB:handle, table[], column[], value[]);
 - SQL_ReadInt(column[], &dest, Cache:cache_id);
 - SQL_ReadString(column[], dest[], size, Cache:cache_id);
 - Float:SQL_ReadFloat(column[], &Float:dest, Cache:cache_id);

 - SQL_Insert(DB:handle, table[]);
 - SQL_Update(DB:handle, table[], column[], value[]);
 - SQL_WriteInt(column[], value);
 - SQL_WriteString(column[], value[]);
 - SQL_WriteFloat(column[], Float:value);
 
 - SQL_SetResult(DBResult:cache);
 - DBResult:SQL_GetResult();
 
 - INT(value);
 - FLOAT(value);

*******************************************************/

#include <a_samp>

// ______________ [ HEADER SYSTEM ]
enum COL_VARS
{
	col_type,
	col_name[64],
	int_value,
	str_value[255],
	Float:float_value
}

static
	query[4096], varCol[32][COL_VARS],
	cols, DBResult:sv_cache;


// ______________ [ MAIN FUNCTIONS ]
stock SQL_CreateTable(DB:handle, const name[])
{
	if(!SQL_TableExists(handle, name))
	{
		format(query, sizeof(query), "CREATE TABLE IF NOT EXISTS %s (ID Integer primary key asc)", name);
		db_free_result(db_query(handle, query));
	}
	else return 0;
	return SQL_TableExists(handle, name);
}

stock SQL_DropTable(const name[])
{
	if(SQL_TableExists(name))
	{
		format(query, sizeof(query), "DROP TABLE IF EXISTS %s", name);
		db_free_result(db_query(handle, query));
	}
	else return 0;
	return !SQL_TableExists(name);
}

stock SQL_TableExists(DB:handle, const name[])
{
	format(query, sizeof(query), "SHOW TABLES LIKE '%s'", name);
	db_free_result(sv_cache);
	sv_cache = db_query(handle, query);
	return (db_num_rows(sv_cache) > 0);
}

stock SQL_AddTableColumn(DB:handle, const table[], const name[], const type[], length)
{
	if(strcmp(type, "float", true) && strcmp(type, "double", true))
		format(query, sizeof(query), "ALTER TABLE %s ADD %s %s(%d)", table, name, type, length);
	else
		format(query, sizeof(query), "ALTER TABLE %s ADD %s double(%d,%d)", table, name, type, length, length);
	
	db_free_result(sv_cache);
	sv_cache = db_query(handle, query);

	return SQL_ColumnExists(handle, table, name);
}

stock SQL_ColumnExists(DB:handle, const table[], const column[])
{
	format(query, sizeof(query), "SELECT * FROM pragma_table_info('%s') WHERE name = '%s'", table, column);
	db_free_result(sv_cache);
	sv_cache = db_query(handle, query);
	return (db_num_rows(sv_cache) > 0);
}

stock SQL_Select(DB:handle, const table[], const column[], value[])
{
	format(query, sizeof(query), "SELECT * FROM %s WHERE %s = '%s'", table, column, value);
	db_free_result(sv_cache);
	sv_cache = db_query(handle, query);
	return (db_num_rows(sv_cache) > 0);
}

stock SQL_Insert(DB:handle, const table[])
{
	format(query, sizeof(query), "INSERT INTO %s (", table);
	for(new i = 0; i < cols; i++)
	{
		if(varCol[i][col_type] == 0) continue;
		else if(i > 0) query[strlen(query)] = 44;
		strcat(query, varCol[i][col_name]);
	}
	
	format(query, sizeof(query), "%s) VALUES (", query);
	for(new i = 0; i < cols; i++)
	{
		if(varCol[i][col_type] == 0) continue;
		else if(i > 0) query[strlen(query)] = 44;

		switch(varCol[i][col_type])
		{
			case 1: format(query, sizeof(query), "%s %d", query, varCol[i][int_value]);
			case 2: format(query, sizeof(query), "%s '%s'", query, varCol[i][str_value]);
			case 3: format(query, sizeof(query), "%s %f", query, varCol[i][float_value]);
		}
	}

	cols = 0;
	query[strlen(query)] = 41;
	
	db_free_result(sv_cache);
	sv_cache = db_query(handle, query);
}

stock SQL_Update(DB:handle, const table[], const where[], const value[])
{
	format(query, sizeof(query), "UPDATE %s SET", table);
	for(new i = 0; i < cols; i++)
	{
		if(varCol[i][col_type] == 0) continue;
		else if(i > 0) query[strlen(query)] = 44;
		format(query, sizeof(query), "%s %s", query, varCol[i][col_name]);
		
		switch(varCol[i][col_type])
		{
			case 1: format(query, sizeof(query), "%s=%d", query, varCol[i][int_value]);
			case 2: format(query, sizeof(query), "%s='%s'", query, varCol[i][str_value]);
			case 3: format(query, sizeof(query), "%s=%f", query, varCol[i][float_value]);
		}
	}
	
	cols = 0;
	format(query, sizeof(query), "%s WHERE %s='%s'", where, value);
	
	db_free_result(sv_cache);
	sv_cache = db_query(handle, query);
}


// ______________ [ WRITE FUNCTIONS ]
stock SQL_WriteInt(const column[], value)
{
	varCol[cols][col_type] = 1;
	varCol[cols][int_value] = value;
	format(varCol[cols][col_name], 64, column);
	cols = (cols + 1) % 32;
}

stock SQL_WriteString(const column[], const value[])
{
	varCol[cols][col_type] = 2;
	format(varCol[cols][col_name], 64, column);
	format(varCol[cols][str_value], 255, value);
	cols = (cols + 1) % 32;
}

stock SQL_WriteFloat(const column[], Float:value)
{
	varCol[cols][col_type] = 3;
	varCol[cols][float_value] = value;
	format(varCol[cols][col_name], 64, column);
	cols = (cols + 1) % 32;
}


// ______________ [ READ FUNCTIONS ]
stock SQL_ReadInt(const column[])
{
	static dest = 0;
	if(sv_cache)
	{
		db_get_field_assoc_int(sv_cache, column);
	}
	return dest;
}

stock SQL_ReadString(const column[], dest[], length = sizeof(dest))
{
	if(sv_cache)
	{
		db_get_field_assoc(sv_cache, column, dest, length);
	}
	return strlen(dest);
}

stock Float:SQL_ReadFloat(const column[])
{
	static Float:dest = 0.0;
	if(sv_cache)
	{
		db_get_field_assoc_float(sv_cache, column);
	}
	return dest;
}


// ______________ [ CACHE FUNCTIONS ]
stock SQL_SetResult(DBResult:cache)
{
	sv_cache = cache;
}

stock DBResult:SQL_GetResult()
{
	return sv_cache;
}


// ______________ [ EXTRA FUNCTIONS ]
static convert[255];

stock INT(value)
{
	format(convert, sizeof(convert), "%d", value);
	return convert;
}

stock FLOAT(Float:value)
{
	format(convert, sizeof(convert), "%f", value);
	return convert;
}


