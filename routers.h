class Trouter{
Tmikrotik *mt;

public:
AnsiString name;
AnsiString model;
AnsiString firmware;
AnsiString ip;
AnsiString login;
AnsiString passwd;
AnsiString csip;
	Trouter(){
		mt=0;
        load();
	}
	~Trouter(){
		try{
		if(mt!=0) delete mt;
        }catch(...){};
	}
	void create(){
		db.select("routers");
		if(db.countL()>0) db.del("routers","id>0");
		db.clear();
		db.add("ip",ip);
		db.add("login",login);
		db.add("passwd",passwd);
        db.add("csip",csip);
		db.insert("routers");
	}
	void load(){
		db.select("routers");
		if(db.countL()>0){
			ip = db.get_value(0,"ip");
			login = db.get_value(0,"login");
			passwd = db.get_value(0,"passwd");
			csip = db.get_value(0,"csip");
			mt=new Tmikrotik(ip, login, passwd);
			if(!mt->open()) ShowMessage("router error...");
			mt->systemRouterboard(name, model, firmware);
			mt->close();

		}
	}
	bool add(Tclient &cl){
		bool r=true;
		mt->open();
		r&=mt->pppSecretAdd(cl.login, cl.passwd, csip, cl.ip, cl.name);
		r&=mt->ipFirewallAddresslistAdd("WhiteList", cl.ip, cl.login);
		r&=mt->queueSimpleAdd(cl.login, cl.ip, cl.tr.down, cl.tr.up);
		mt->close();
		return r;
	}
	bool del(Tclient &cl){
		bool r=true;
		mt->open();
		r&=mt->pppSecretRemove(cl.login);
		r&=mt->ipFirewallAddresslistRemove("WhiteList", cl.ip);
		r&=mt->queueSimpleRemove(cl.login);
		mt->pppActiveRemove(cl.login);
		mt->close();
		return r;
	}
	void del(std::vector<Tclient> &cls){
		mt->open();
		for(int i=0; i<cls.size(); i++){
			bool r=true;
			r&=mt->pppSecretRemove(cls[i].login);
			r&=mt->ipFirewallAddresslistRemove("WhiteList", cls[i].ip);
			r&=mt->queueSimpleRemove(cls[i].login);
            mt->pppActiveRemove(cls[i].login);
			if(!r){
                ShowMessage("error delete");
				Application->Terminate();
				return;
			}
		}
		mt->close();
	}
	bool discon(Tclient &cl){
		bool r=true;
		mt->open();
		r&=mt->pppActiveRemove(cl.login);
		mt->close();
		return r;
	}

	bool enable(Tclient &cl){
		bool r=true;
		mt->open();
		r&=mt->ipFirewallAddresslistAdd("WhiteList", cl.ip, cl.login);
		mt->close();
		return r;
	}
	bool disable(Tclient &cl){
		bool r=true;
		mt->open();
        r&=mt->ipFirewallAddresslistRemove("WhiteList", cl.ip);
		mt->close();
		return r;
	}
	bool online(Tclient &cl){
		AnsiString s="";
		mt->open();
		s = mt->findIdPppActive(cl.login);
		mt->close();
        if(s=="") return false; else return true;
	}
	AnsiString uptime(Tclient &cl){
		AnsiString s="";
		mt->open();
		s=mt->findIdPppActiveUptime(cl.login);
		mt->close();
        return s;
	}
	void onlineAll(TStringList *sl){
        mt->open();
		mt->findIdPppActivePrint(sl);
		mt->close();
	}
};