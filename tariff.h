

class Ttariff{
TStringList *sl;
public:
	AnsiString name;
	AnsiString up;
	AnsiString down;
	AnsiString sum;
	AnsiString trid;
	Ttariff(){
		sl=new TStringList();
	}
	~Ttariff(){
		try{
          delete sl;
        }catch(...){};
	}
	bool load_id(AnsiString id){
		trid=id;
		db.select("tariffs","id="+id);
		if(db.countL()>0){
			name=db.get_value(0,"name");
			up=db.get_value(0,"up");
			down=db.get_value(0,"down");
			sum=db.get_value(0,"sum");
			return true;
		}
		return false;
	}
	bool load_name(AnsiString name){
		db.select("tariffs","name='"+name+"'");
		if(db.countL()>0){
			name=db.get_value(0,"name");
			up=db.get_value(0,"up");
			down=db.get_value(0,"down");
			sum=db.get_value(0,"sum");
			trid=db.get_value(0,"id");
			return true;
		}
        return false;
	}
	bool create(AnsiString name, AnsiString sum, AnsiString up, AnsiString down){
		db.select("tariffs","name='"+name+"'");
		if(db.countL()>0) return false;
		db.clear();
		db.add("name",name);
		db.add("sum",sum);
		db.add("up",up);
		db.add("down",down);
        db.insert("tariffs");
        return true;
	}
	bool create(){
		db.select("tariffs","name='"+name+"'");
		if(db.countL()>0) return false;
		db.clear();
		db.add("name",name);
		db.add("sum",sum);
		db.add("up",up);
		db.add("down",down);
		db.insert("tariffs");
        return true;
	}
	TStringList *getAllName(){
		sl->Text="";
		db.select("tariffs");
		for(int i=0; i<db.countL(); i++){
			sl->Add(db.get_value(i,"name"));
		}
        return sl;
	}
};