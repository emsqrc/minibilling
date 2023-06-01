#include "sqlite3.h"

namespace varfromdb{
String DBscolum;
String DBslist;

int callbackFromDB(void* t, int count, char** value, char** colum){
	for(int i=0; i<count; i++){
	   DBscolum+=colum[i];
	   DBscolum+="\n";
	   DBslist+=value[i];
	   DBslist+="\n";
	}
	return 0;
 }
}

class Tdb{
TStringList *listfordb;
TStringList *columfordb;
String filename;
TStringList *lw,*cw,*lr,*cr;
int COUNTC,COUNTL;
sqlite3 *db; // хэндл объекта соединение к БД
char *err;


void init(){
	lw=new TStringList();
	cw=new TStringList();
	lr=new TStringList();
	cr=new TStringList();
	listfordb=new TStringList();
	columfordb=new TStringList();
}

void deinit(){
	lw->Free();
	cw->Free();
	lr->Free();
	cr->Free();
	columfordb->Free();
    listfordb->Free();
}



void open_db(){
	AnsiString p=filename;
	sqlite3_open(p.c_str(), &db);
}

void close_db(){
   sqlite3_close(db);
}

void clean_lists_db(){
	listfordb->Clear();
	columfordb->Clear();
}

void sql_db(AnsiString sql){
	varfromdb::DBscolum="";
	varfromdb::DBslist="";
   sqlite3_exec(db, sql.c_str(), varfromdb::callbackFromDB, 0, &err);
   listfordb->Text=varfromdb::DBslist;
   columfordb->Text=varfromdb::DBscolum;
}

void create_table_db(String name){
	String s="CREATE TABLE IF NOT EXISTS "+name+"(id INTEGER PRIMARY KEY";
	for(int i = 0; i<columfordb->Count; i++){
		s+=",";
		s+=columfordb->Strings[i];
		s+=" TEXT";
	}
	s+=");";
	open_db();
	sql_db(s);
	close_db();
}

void insert_db(String name){
	String s="INSERT INTO "+name+"(";
	bool k=false;
	for(int i = 0; i<columfordb->Count; i++){
		if(k){
			s+=",";
			s+="'";
			s+=columfordb->Strings[i];
			s+="'";
		}else{
			s+="'";
			s+=columfordb->Strings[i];
			s+="'";
			k=true;
		}
	}
	s+=") VALUES(";
	k=false;
	for(int i = 0; i<listfordb->Count; i++){
		if(k){
			s+=",";
			s+="'";
			s+=listfordb->Strings[i];
			s+="'";
		}else{
			s+="'";
			s+=listfordb->Strings[i];
			s+="'";
			k=true;
		}
	}
	s+=");";
	open_db();
	sql_db(s);
	close_db();
}

void update_db(String name, String where){
	open_db();
	String s="UPDATE "+name+" SET ";
	for(int i=0; i<columfordb->Count; i++){
        if(i>0)s+=",";
		s+="'"+columfordb->Strings[i]+"'"+"='"+listfordb->Strings[i]+"'";
	}
    s+=" WHERE "+where+";";
	sql_db(s);
	close_db();
}

void delete_db(String name, String where){
	String s="DELETE FROM "+name+" WHERE "+where+";";
	open_db();
	sql_db(s);
	close_db();
}


void select_db(String name, String where){
	open_db();
	String s;
	if(where==""){
		s="SELECT * FROM "+name+";";
	}else{
		s="SELECT * FROM "+name+" WHERE "+where+";";
		//s="SELECT * FROM "+name+" "+where+";";
	}
	clean_lists_db();
	sql_db(s);
	close_db();
}

public:
	Tdb(){
	  init();
	}
	~Tdb(){
        close_db();
		deinit();
	}

void open(AnsiString path){
	filename=path;
    open_db();
	}

void update(String tablename, String where){
   clean_lists_db();
	for(int i=0; i<cw->Count; i++){
		columfordb->Add(cw->Strings[i]);
		listfordb->Add(lw->Strings[i]);
	}
	update_db(tablename,where);
}


private:

int count_colums(){
        if(cr->Count==0) return 0;
	String s=cr->Strings[0];
   for(int i=1; i<cr->Count; i++){
		if(cr->Strings[i]==s){
			return i;
		}
   }
   return cr->Count;
}

int count_lines(){
   int j=COUNTC;
   if(j==0) return 0;
   return cr->Count/j;
}

public:

void select(String name, String where){
	select_db(name, where);
	cr->Text=columfordb->Text;
	lr->Text=listfordb->Text;
	COUNTC=count_colums();
	COUNTL=count_lines();
}

void select(String name){
	select(name,"");
}

int countL(){
	return COUNTL;
}

int countC(){
	return COUNTC;
}

void create(String name){
   columfordb->Clear();
   columfordb->Text=cw->Text;
   create_table_db(name);
}

void insert(String tablename){
	clean_lists_db();
	for(int i=0; i<cw->Count; i++){
		columfordb->Add(cw->Strings[i]);
		listfordb->Add(lw->Strings[i]);
	}
	insert_db(tablename);
}

void del(String table, String where){
	delete_db(table,where);
}

String get_key(int index){
	return cr->Strings[index];
}
int get_index(String key){
	for(int i=0; i<COUNTC; i++){
		if(cr->Strings[i]==key) return i;
	}
	return -1;
}

String get_value(int lines, int key){
        if(COUNTC==0) return "";
	int index=lines*COUNTC+key;
	return lr->Strings[index];
}

String get_value(int lines, String key){
	String value=get_value(lines,get_index(key));
	value=StringReplace(value,"[#13#]","\n", TReplaceFlags()<< rfReplaceAll);
	value=StringReplace(value,"[#39#]","'", TReplaceFlags()<< rfReplaceAll);
	return value;
}

void clear(){
	lw->Clear();
	cw->Clear();
}
private:
bool find_key_in_cw(String key){
	for(int i=0; i<cw->Count; i++){
		if(cw->Strings[i]==key){
			return true;
		}
	}
	return false;
}
public:
void add(String key, String value){
   if(!find_key_in_cw(key)){
		   value=StringReplace(value,"\r","", TReplaceFlags()<< rfReplaceAll);
		   value=StringReplace(value,"\n","[#13#]", TReplaceFlags()<< rfReplaceAll);
		   value=StringReplace(value,"'","[#39#]", TReplaceFlags()<< rfReplaceAll);
	   cw->Add(key);
	   lw->Add(value);
   }
}
void add(String key){
   if(!find_key_in_cw(key)){
	   cw->Add(key);
	   lw->Add("");
   }
}
void edit(String key, String value){
   for(int i=0; i<cw->Count; i++){
		if(cw->Strings[i]==key){
			value=StringReplace(value,"\r","", TReplaceFlags()<< rfReplaceAll);
			value=StringReplace(value,"\n","[#13#]", TReplaceFlags()<< rfReplaceAll);
		    value=StringReplace(value,"'","[#39#]", TReplaceFlags()<< rfReplaceAll);
			lw->Strings[i]=value;
			break;
		}
   }
}

bool getrecord(String table, String whi){
	select(table, whi);
	if(this->countL()>0) return true; else return false;
}
};


