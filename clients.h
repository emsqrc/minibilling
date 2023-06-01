class Tclient{

public:
AnsiString login;
AnsiString passwd;
AnsiString name;
AnsiString phone;
AnsiString address;
AnsiString ip;
AnsiString balance;
AnsiString status;
Ttariff tr;
	Tclient(){

	}
	Tclient(AnsiString _login){
        load(_login);
	}
	void load(AnsiString _login){
		db.select("clients","login='"+_login+"'");
		if(db.countL()>0){
		   AnsiString id = db.get_value(0,"tariff");
		   login=db.get_value(0,"login");
		   passwd=db.get_value(0,"passwd");
		   name=db.get_value(0,"name");
		   phone=db.get_value(0,"phone");
           address=db.get_value(0,"address");
		   ip=db.get_value(0,"ip");
		   balance=db.get_value(0,"balance");
		   status=db.get_value(0,"status");
		   tr.load_id(id);
		}
	}
	void create(AnsiString _login, AnsiString _passwd, AnsiString _name, AnsiString _phone, AnsiString _address, AnsiString _ip,  AnsiString _balance, AnsiString idtariff){
		login = _login;
		passwd = _passwd;
		name = _name;
		phone = _phone;
        address = _address;
		ip = _ip;
		balance = _balance;
        tr.load_id(idtariff);
		db.clear();
		db.add("login",login);
		db.add("passwd",passwd);
		db.add("name",name);
		db.add("phone",phone);
        db.add("address",address);
		db.add("ip",ip);
        db.add("balance",balance);
		db.add("tariff",idtariff);
        db.add("status","enable");
        db.insert("clients");
	}
		void create(AnsiString idtariff){
        tr.load_id(idtariff);
		db.clear();
		db.add("login",login);
		db.add("passwd",passwd);
		db.add("name",name);
		db.add("phone",phone);
        db.add("address",address);
		db.add("ip",ip);
        db.add("balance",balance);
		db.add("tariff",idtariff);
        db.add("status","enable");
        db.insert("clients");
	}

	void del(){
		db.del("clients","login='"+login+"'");
	}

	void enable(bool e){
        db.clear();
		if(e) db.add("status","enable"); else db.add("status","disable");
		db.update("clients","login='"+login+"'");
        load(login);
	}


};