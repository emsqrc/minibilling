

class Tprivat{

AnsiString pr_md5(AnsiString byf){
   std::string st;
   AnsiString s=byf.c_str();
   st=s.c_str();
   s=md5(st).data();
   return s;
}

AnsiString pr_sha1(AnsiString byf){
	std::string st;
	SHA1 ch;
	AnsiString s=byf.c_str();
	st=s.c_str();
	ch.update(st);
	s=ch.final().data();
	return s;
}


public:

AnsiString id;
AnsiString key;
AnsiString card;

Tprivat(){
	db.select("bank","name='privat'");
	if(db.countL()>0){
		id=db.get_value(0,"idm");
		key=db.get_value(0,"keym");
        card=db.get_value(0,"card");
	}
}

AnsiString xml(AnsiString datafrom, AnsiString datato){
	Tmstr str(1024);
	AnsiString as=Form1->Memo2->Lines->Text;
	str=as.c_str();
	str.replace("=ID=",id.c_str());
	str.replace("=DATAFROM=",datafrom.c_str());
	str.replace("=DATATO=",datato.c_str());
	str.replace("=CARD=",card.c_str());
	Tmstr str1(1024);
	str1=str;
	str.extract("<data>*</data>");
	str.del("<data>");
	str.del("</data>");
	as=str.charstr();
    as+=key;
	as=pr_sha1(pr_md5(as));
	str1.replace("=SIGNATURE=",as.c_str());
	as=str1.charstr();
	return as;
}

AnsiString get(AnsiString datafrom, AnsiString datato){
    if((id=="")||(key=="")||(card=="")) return "";
    Tprivat pr;
	TMemoryStream *st=new TMemoryStream();
	AnsiString temp=pr.xml(datafrom,datato);
	st->Write(temp.c_str(),temp.Length());
	temp=Form1->IdHTTP1->Post("https://api.privatbank.ua/p24api/rest_fiz",st);
	delete st;
    return temp;
}

	void create(){
		db.select("bank","name='privat'");
		if(db.countL()>0) db.del("bank","name='privat'");
		db.clear();
		db.add("name","privat");
		db.add("idm",id);
		db.add("keym",key);
		db.add("card",card);
        db.insert("bank");
	}


};



