# easySQL
Um jeito mais facil de usar SQL no Pawn
<br />
```pwn
native db_create_table(DB:handle, table[]);
native db_drop_table(DB:handle, table[]);
native db_table_exists(DB:handle, table[]);
native db_add_column(DB:handle, table[], name[], type[], length = 11, bool:notnull = false, default[] = "");
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
```
<br />
Nova versao! nao testado. <br />
Nessa versao o objetivo era deixar o mais semelhante possivel com o a_sampdb
dessa forma seria mais convidativo a entender essa biblioteca que poucos usam
<br />
<br />

# Update 22/10
<br />
Foi testado e funciona... mas ainda nao esta do jeito que quero, vou aperfeicoar o codigo imediatamente!


