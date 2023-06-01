#include "librouteros.h"
#include "db.h"


class Tmikrotik{

AnsiString _ip;
int _port;
AnsiString _login;
AnsiString _pass;

ros_result *res;
ros_connection *con;

void readToEnd(){
	while (res && res->re){
		ros_result_free(res);
		res = ros_read_packet(con);
	}
}

AnsiString findIdIpAddress(AnsiString ip){
		ip="?address="+ip;
		res = ros_send_command_wait(con, "/ip/address/print",ip.c_str(), NULL);
		AnsiString r = ros_get(res,"=.id");
		readToEnd();
		return r;
	}
AnsiString findIdIpFirewallAddresslist(AnsiString list, AnsiString ip){
		ip="?address="+ip;
		list="?list="+list;
		res = ros_send_command_wait(con, "/ip/firewall/address-list/print",ip.c_str(),list.c_str(), NULL);
        AnsiString r = ros_get(res,"=.id");
		readToEnd();
		return r;
	}
AnsiString findIdPppSecret(AnsiString user){
		user="?name="+user;
		res = ros_send_command_wait(con, "/ppp/secret/print", user.c_str(), NULL);
		AnsiString r = ros_get(res,"=.id");
		readToEnd();
		return r;
	}
AnsiString findIdQueueSimple(AnsiString name){
		name="?name="+name;
		res = ros_send_command_wait(con, "/queue/simple/print", name.c_str(), NULL);
		AnsiString r = ros_get(res,"=.id");
		readToEnd();
		return r;
	}

public:
	Tmikrotik(AnsiString ip, int port, AnsiString login, AnsiString pass){
		_ip=ip;
		_port=port;
		_login=login;
		_pass=pass;
	}
	Tmikrotik(AnsiString ip, AnsiString login, AnsiString pass){
		_ip=ip;
		_port=8728;
		_login=login;
		_pass=pass;
	}
    bool open(){
		con=ros_connect(_ip.c_str(),_port);
		return ros_login(con,_login.c_str(),_pass.c_str());
	}
	void close(){
		ros_result_free(res);
		ros_disconnect(con);
	}
	bool ipAddressAdd(AnsiString ip, AnsiString interf, AnsiString comment){
		ip="=address="+ip;
		interf="=interface="+interf;
		if(comment=="") res = ros_send_command_wait(con, "/ip/address/add",ip.c_str(),interf.c_str(), NULL);
		else{
			comment="=comment="+comment;
            res = ros_send_command_wait(con, "/ip/address/add",ip.c_str(),interf.c_str(),comment.c_str(), NULL);
        }
		return res->done;
	}
	bool ipAddressRemove(AnsiString ip){
		AnsiString id = findIdIpAddress(ip);
        if(id=="") return false;
		id="=.id="+id;
		res = ros_send_command_wait(con, "/ip/address/remove",id.c_str(), NULL);
		return res->done;
	}
	bool ipFirewallAddresslistAdd(AnsiString name, AnsiString ip, AnsiString comment){
		ip="=address="+ip;
		name="=list="+name;
		if(comment=="") res = ros_send_command_wait(con, "/ip/firewall/address-list/add",name.c_str(),ip.c_str(), NULL);
		else{
			comment="=comment="+comment;
			res = ros_send_command_wait(con, "/ip/firewall/address-list/add",name.c_str(),ip.c_str(),comment.c_str(), NULL);
        }
		return res->done;
	}
	bool ipFirewallAddresslistRemove(AnsiString list, AnsiString ip){
		AnsiString id = findIdIpFirewallAddresslist(list, ip);
		if(id=="") return false;
		id="=.id="+id;
		res = ros_send_command_wait(con, "/ip/firewall/address-list/remove",id.c_str(), NULL);
		return res->done;
	}
	bool pppSecretAdd(AnsiString user, AnsiString pass, AnsiString localip, AnsiString remoteip, AnsiString comment){
		user="=name="+user;
		pass="=password="+pass;
		localip="=local-address="+localip;
		remoteip="=remote-address="+remoteip;
		if(comment=="") res = ros_send_command_wait(con, "/ppp/secret/add",user.c_str(),pass.c_str(), localip.c_str(), remoteip.c_str(), NULL);
		else{
			comment="=comment="+comment;
            res = ros_send_command_wait(con, "/ppp/secret/add",user.c_str(),pass.c_str(), localip.c_str(), remoteip.c_str(), comment.c_str(), NULL);
        }
		return res->done;
	}
	bool pppSecretRemove(AnsiString user){
		AnsiString id = findIdPppSecret(user);
		if(id=="") return false;
		id="=.id="+id;
		res = ros_send_command_wait(con, "/ppp/secret/remove",id.c_str(), NULL);
		return res->done;
	}
	bool queueSimpleAdd(AnsiString name, AnsiString ip, AnsiString down, AnsiString up){
		name="=name="+name;
		ip="=target="+ip;
		AnsiString limit="=max-limit="+up+"/"+down;
		res = ros_send_command_wait(con, "/queue/simple/add",ip.c_str(),name.c_str(),limit.c_str(), NULL);
		return res->done;
	}
	bool queueSimpleRemove(AnsiString name){
		AnsiString id = findIdQueueSimple(name);
        if(id=="") return false;
		id="=.id="+id;
		res = ros_send_command_wait(con, "/queue/simple/remove",id.c_str(), NULL);
		return res->done;
	}
	AnsiString findIdPppActive(AnsiString login){
		login="?name="+login;
		res = ros_send_command_wait(con, "/ppp/active/print", login.c_str(), NULL);
		AnsiString r = ros_get(res,"=.id");
		readToEnd();
		return r;
	}
	void systemRouterboard(AnsiString &name, AnsiString &model, AnsiString &firmware){
		res = ros_send_command_wait(con, "/system/routerboard/print",  NULL);
		name = ros_get(res,"=board-name");
		model = ros_get(res,"=model");
		firmware = ros_get(res,"=upgrade-firmware");
		readToEnd();
	}

	AnsiString findIdPppActiveUptime(AnsiString login){
		login="?name="+login;
		res = ros_send_command_wait(con, "/ppp/active/print", login.c_str(), NULL);
		AnsiString r = ros_get(res,"=uptime");
		readToEnd();
		return r;
	}

	void findIdPppActivePrint(TStringList *sl){
		res = ros_send_command_wait(con, "/ppp/active/print", NULL);
		sl->Clear();
		while (res && res->re){
			sl->Add(ros_get(res,"=name"));
			ros_result_free(res);
			res = ros_read_packet(con);
		}
	}

	bool pppActiveRemove(AnsiString login){
		AnsiString id=findIdPppActive(login);
		if(id=="") return false;
        id="=.id="+id;
		res = ros_send_command_wait(con, "/ppp/active/remove",id.c_str(), NULL);
        return res->done;
	}

};
