

class Tclientonline{
	public:
	TStringList *sl;
	Tclientonline(){
		sl=new TStringList();
	}
	~Tclientonline(){
		try{
			delete sl;
        }catch(...){};
	}

};