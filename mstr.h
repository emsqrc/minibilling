/////////////////////////////////////////9.07.2020/////////////////////////////////////////////msqrc

#define MAXCHARDOUBLE 8
//#include <stdint>

class Tmstr{
int WMAXLENGTH;
protected:
char* pbyf;
void winit(char *wbyf, int len){//установить метку конца памяти
  for(int i=0; i<len-1;i++){
    *(wbyf+i) = 0;
  }
  *(wbyf+len-1) = 1;
}


int wlength(const char *wbyf){//узнать длину строки
  int i=0;
  while(*(wbyf+i)!=0){
    i++;
  }
return i;
}



inline void waddchar(char *wbyf,const char wc){//добавить символ в конец
  int n = wlength(wbyf);
  if((*(wbyf+n+1)!=1)){
    *(wbyf+n)=wc;
    *(wbyf+n+1) = 0;
  }
}

inline void waddcharin(char *wbyf,const char wc){//добавить символ
  if((*(wbyf+1)!=1)){
    *(wbyf)=wc;
    *(wbyf+1) = 0;
  }
}

inline void wclean(char *wbyf){//очистить строку
  if(*wbyf!=1){*wbyf = 0;};
}


void wextractnamb(const char *wbyf, char *wtempextr){//выделить цыфры
  int i = 0;
  char r = 0;
  wclean(wtempextr);
  while(r =*(wbyf+i), r!=0){
	i++;
	if((r>='0')&&(r<='9')){
	  waddchar(wtempextr,r);
	}
  }
}

void wdelnonamb(char *wbyf){//оставить только цыфры
  int i = 0;
  char r = 0;
  while(r =*(wbyf+i), r!=0){
	if((r<'0')||(r>'9')){
		wcopy(wbyf+i,wbyf+i+1);
	}else i++;
  }
}

bool wcmpfree(const char *wbyf, const char *wtemp){//сравнение строк
  int i = 0;
  bool r = true;
  while(*(wtemp+i)!=0){
    if(*(wbyf+i)==0){
      r = false;
      goto mi;
    };
    if(*(wtemp+i)!=*(wbyf+i)){
      r = false;
      goto mi;
    };
    i++;
  }
mi:
return r;
}

bool wcmp(const char *wbyf, const char *wtemp){//сравнение строк с учетом размера
  int i = 0;
  bool r = true;
  while(*(wtemp+i)!=0){
    if(*(wbyf+i)==0){
      r = false;
      goto mi;
    };
    if(*(wtemp+i)!=*(wbyf+i)){
      r = false;
      goto mi;
    };
    i++;
  }
if(*(wbyf+i)!=0){
  r = false;
};
mi:
return r;
}


void wcopy(char *wbyf, const char *wtemp){//копировать строку
  int i =0;
  while(*(wtemp+i)!=0){
    if(*(wbyf+i)==1){
      goto mi;
    };
    *(wbyf+i) = *(wtemp+i);
    i++;
  };
mi:
if(*(wbyf+i)==1){
  *(wbyf+i-1)=0;
}
else{
  *(wbyf+i)=0;
};
}

void wcopyin(char *wbyf, const char *wtemp){//копировать строку без завершающего 0
	int i=0;
	while((*(wtemp+i)!=0)&&(i<WMAXLENGTH-1)){
		if((*(wbyf+i)==1)){
			*(wbyf+i-1) = 0;
			return;
		}
		*(wbyf+i) = *(wtemp+i);
		i++;
	}
}

void wcopyinrevers(char *wbyf, const char *wtemp){ //копировать строку без завершающего 0
	int n = wlength(wtemp);
	for(int i = 0; i<n; i++){if(*(wbyf+i)==1) n = i;};
	for(int i = n-1; i>=0; i--){
		*(wbyf+i) = *(wtemp+i);
	}
}

void wcopyrevers(char *wbyf, const char *wtemp){ //копировать строку
	int n = wlength(wtemp);
	for(int i = 0; i<n; i++){if(*(wbyf+i)==1) n = i;};
	*(wbyf+n) = 0;
	for(int i = n-1; i>=0; i--){
		*(wbyf+i) = *(wtemp+i);
	}
}


void waddstr(char *wbyf, const char *wtemp){//добавить строку
  int n = wlength(wbyf);
  wcopy(wbyf+n,wtemp);
}


bool wfindok(const char *wbyf, const char *wtemp){//поиск подстроки
  bool r = false;
  int i = 0;
  while(*(wbyf+i)!=0){
    if(wcmpfree((wbyf+i),wtemp)){
      r = true;
      goto mi;
    }
  i++;
  }
  mi:
  return r;
}


int wfind(const char *wbyf, const char *wtemp){//поиск подстроки
  bool r = false;
  int i = 0;
  while(*(wbyf+i)!=0){
    if(wcmpfree((wbyf+i),wtemp)){
      r = true;
      goto mi;
    }
    i++;
  }
  mi:
  if(r){
    return i;
  }
  else{
    return -1;
  };
}

int wfind(const char *wbyf, const char wtemp){//поиск подстроки
  bool r = false;
  int i = 0;
  char wtempstr[2] = {wtemp,0};
  while(*(wbyf+i)!=0){
    if(wcmpfree((wbyf+i),&wtempstr[0])){
      r = true;
      goto mi;
    }
    i++;
  }
  mi:
  if(r){
    return i;
  }
  else{
    return -1;
  };
}

bool wgetcharisnamber(char s){
	return ((s>='0')&&(s<='9'));
}

bool wmcmpfree(const char *wbyf, const char *mask){//сравнение по маске (?, &, ^)
  int i = 0;
  bool r = true;
  while(*(mask+i)!=0){
    if(*(wbyf+i)==0){
      r = false;
      goto mi;
    };
    if(!((*(mask+i)==*(wbyf+i))||(*(mask+i)=='?')||((*(mask+i)=='&')&&(wgetcharisnamber(*(wbyf+i)))) ||((*(mask+i)=='^')&&(!wgetcharisnamber(*(wbyf+i)))) )){
      r = false;
      goto mi;
    };
    i++;
  }
mi:
return r;
}

bool wmcmpfree(const char *wbyf, const char *mask, int topos){//сравнение по маске (?, &, ^)
  int i = 0;
  bool r = true;
  while((*(mask+i)!=0)&&(i<topos)){
    if(*(wbyf+i)==0){
      r = false;
      goto mi;
    };
    if(!((*(mask+i)==*(wbyf+i))||(*(mask+i)=='?')||((*(mask+i)=='&')&&(wgetcharisnamber(*(wbyf+i)))) ||((*(mask+i)=='^')&&(!wgetcharisnamber(*(wbyf+i)))) )){
      r = false;
      goto mi;
    };
    i++;
  }
mi:
return r;
}


int wmfind(const char *wbyf,const char *mask){//поиск подстроки с маской (?,&)
  bool r = false;
  int i = 0;
  while(*(wbyf+i)!=0){
    if(wmcmpfree((wbyf+i),mask)){
      r = true;
      goto mi;
    }
    i++;
  }
  mi:
  if(r){
    return i;
  }
  else{
    return -1;
  };
}

int wmfind(const char *wbyf,const char *mask, int topos){//поиск подстроки с маской (?,&)
  bool r = false;
  int i = 0;
  while(*(wbyf+i)!=0){
    if(wmcmpfree((wbyf+i),mask,topos)){
      r = true;
      goto mi;
    }
    i++;
  }
  mi:
  if(r){
    return i;
  }
  else{
    return -1;
  };
}

bool wmfindok(const char *wbyf,const char *mask){//поиск подстроки с маской (?,&)
  bool r = false;
  int i = 0;
  while(*(wbyf+i)!=0){
    if(wmcmpfree((wbyf+i),mask)){
      r = true;
      goto mi;
    }
    i++;
  }
  mi:
  return r;
}

inline void wdelfrom(char *wbyf, int n){//удалить начиная с указанного символа
  if(n>=0){wclean(wbyf+n);};
}

inline void wdelend(char *wbyf){// удалить завершающий символ
  wdelfrom(wbyf,wlength(wbyf)-1);
}

inline void wdelto(char *wbyf, int n){//удалить до указанного символа
  if(n>=0){wcopy(wbyf,wbyf+n);};
}
inline void wdelbegin(char *wbyf){// удалить первый символ
  wdelto(wbyf,1);
}


bool wreplace(char *wbyf, const char *oldp, const char *newp){//замена подстроки
  int n = wfind(wbyf,oldp);
  bool r = false;
  if(n>=0){
	int m1 = wlength(oldp);
	if(m1==0) return false;
	int m2 = wlength(newp);
	if(m2==0){
		wdelsub(wbyf,oldp);
	}else if(m1<m2){
		wcopyrevers(wbyf+n+m2-1,wbyf+n+m1-1);
	}else if(m1>m2){
		wcopy(wbyf+n+m2-1,wbyf+n+m1-1);
	}
	wcopyin(wbyf+n,newp);
	r = true;
  };
  return r;
}

bool wreplace(char *wbyf, const char *oldp, const char *newp, int &frompos){//замена подстроки
  wbyf +=frompos;
  int n = wfind(wbyf,oldp);
  bool r = false;
  if(n>=0){
	int m1 = wlength(oldp);
	if(m1==0) return false;
	int m2 = wlength(newp);
	if(m2==0){
		wdelsub(wbyf,oldp);
	}else if(m1<m2){
		wcopyrevers(wbyf+n+m2-1,wbyf+n+m1-1);
	}else if(m1>m2){
		wcopy(wbyf+n+m2-1,wbyf+n+m1-1);
	}
	wcopyin(wbyf+n,newp);
	r = true;
	frompos +=(n+m2);
  };
  return r;
}

bool wdelsub(char *wbyf, const char *sub, int &frompos){//удалить подстроку
  wbyf +=frompos;
  int n = wfind(wbyf,sub);
  int m =0;
  bool r = false;
  if(n>=0){
    m = wlength(sub);
	wcopy(wbyf+n,wbyf+n+m);
	r = true;
	frompos +=n;
  };
  return r;
}
bool wdelsub(char *wbyf, const char *sub){
	int pos = 0;
	return wdelsub(wbyf,sub,pos);
}

void wdelsubspace(char *wbyf){//удалить пробел
  char sub[] = " ";
  int n = wfind(wbyf,sub);
  int m =0;
  if(n>=0){
    m = wlength(sub);
    wcopy(wbyf+n,wbyf+n+m);
  };
}



inline void wdeltostr(char *wbyf, const char *wsub){//удалить до подстроки
  int n = wfind(wbyf,wsub);
  if(n>0){
    wdelto(wbyf,n);
  }
}

inline void wdeltoandstr(char *wbyf, const char *wsub){//удалить до подстроки и подстроку
  int n = wfind(wbyf,wsub);
  if(n>0){
    n +=wlength(wsub);
    wdelto(wbyf,n);
  }
}


inline void wdelfromstr(char *wbyf, const char *wsub){//удалить после подстроки
  int n = wfind(wbyf,wsub);
  if(n>=0){
    n +=wlength(wsub);
    wdelfrom(wbyf,n);
  }
}

inline void wdelfromstrtoend(char *wbyf, const char *wsub){//удалить с подстроки и до конца
  int n = wfind(wbyf,wsub);
  if(n>=0){
    wdelfrom(wbyf,n);
  }
}

inline void wmdeltostr(char *wbyf, const char *wsub){//удалить до подстроки (с маской)
  int n = wmfind(wbyf,wsub);
  if(n>0){
    wdelto(wbyf,n);
  }
}


inline void wmdelfromstr(char *wbyf, const char *wsub){//удалить после подстроки (с маской)
  int n = wmfind(wbyf,wsub);
  if(n>=0){
	n +=wlength(wsub);
	wdelfrom(wbyf,n);
  }
}


bool wmsearch(const char *wbyf, const char *mask, int &Apos, int &Bpos){
	int a;
	int b;
	int l = wlength(wbyf);
	int lm = wlength(mask);
	int p;
	int pb;
	if((l>0)&&(lm>0)){
		if(*mask=='*'){
			a = 0;
			b = l;
			p = 1;
			pb = 0;
		}else{
			p = wfind(mask,'*');
			if(p==-1) p = lm;
			a = wmfind(wbyf,mask,p);
			if(a==-1) return false;
			b = a+p;
			pb = b;
		}
		while((p<lm)&&(pb<l)){
			if(*(mask+p)=='*'){
				b=l;
				p++;
			}else{
				int pt = wfind(mask+p,'*');
				if(pt==-1) pt = lm-p;
				int j = wmfind(wbyf+pb,mask+p,pt);
				if(j==-1) return false;
				p+=pt;
				b = pb+j+pt;
				pb = b;
			}
		}
	Apos = a;
	Bpos = b;
	return true;
	}
	return false;
}



bool wmextract(char *wbyf, const char *mask){   ///виделить в буфер
	int a,b;
	bool r = wmsearch(wbyf,mask,a,b);
	if(r){
    	wdelfrom(wbyf,b);
		wcopy(wbyf,wbyf+a);
	}
	return r;
}


bool wmdelsub(char *wbyf, const char *mask, int &frompos){ ///удалить
	wbyf +=frompos;
	int a,b;
	bool r = wmsearch(wbyf,mask,a,b);
	if(r){
		wcopy(wbyf+a,wbyf+b);
		frompos +=a;
	}
	return r;
}

bool wmreplace(char *wbyf, const char *mask, const char *wnew, int &frompos){ ///заменить
	wbyf +=frompos;
	int a,b;
	bool r = wmsearch(wbyf,mask,a,b);
	if(r){
		*(wbyf+a) = 0;
		int ll = wlength(wnew);
		if((b-a)<ll){
			wcopyrevers(wbyf+a+ll,wbyf+b);
		}else if((b-a)>ll){
			wcopy(wbyf+a+ll,wbyf+b);
		}
		wcopyin(wbyf+a,wnew);
		frompos +=(a+ll);
	}
	return r;
}

void wrevers(char *byf){//перевернуть строку
  int n = wlength(byf);
  int j = 0;
  int m = n/2;
  char c;
  for(int i=n-1;i>=m;i--){
	c =*(byf+j);
	*(byf+j) = *(byf+i);
	*(byf+i) = c;
    j++;
  }
}

bool wmextractminimal(char *wbyf, char *mask){//поиск по маске (минимальная длина)
  bool r = false;
  r = wmextract(wbyf,mask);
  if(r){
	wrevers(wbyf);
	wrevers(mask);
    wmextract(wbyf,mask);
	wrevers(wbyf);
	wrevers(mask);
  }
  return r;
}

bool wmmfindok(const char *wbyf, const char *mask){
  int a,b;
  return wmsearch(wbyf,mask,a,b);
}
long wpow(long a, long e){//поднесение к степени
    long t = a;
    if(e==0){return 1;};
    for(long i = 1; i<e; i++){
      t *= a;
    }
    return t;
}


long wstrtolong(char *wbyf){//строку в число
  wdelnonamb(wbyf);
  int n = wlength(wbyf);
  int e = n-1;
  long r = 0;
  for(int i=0;i<n;i++){
    r +=wpow(10,e-i)*(*(wbyf+i)-'0');
  }
  return r;
}
double wstrtodouble(char *wbyf){//строку в число
  wreplace(pbyf,",",".");
  if(wfindok(pbyf,".")){
		int n = wlength(wbyf);
		int p = wfind(pbyf,".");
		int e = p-1;
		long r = 0;
		for(int i=0;i<p;i++){
			r +=wpow(10,e-i)*(*(wbyf+i)-'0');
		}
		double r2 =0;
		int j = 1;
		for(int i=p+1;i<n;i++){
			r2 +=(*(wbyf+i)-'0')/(double)wpow(10,j);
			j++;
		}
		int k = n-1-(p+1);
		return r+r2;
		}
  else{
		return (double)wstrtolong(pbyf);
  }
}

void wlongtostr(long namb, char *wbyf){// число в строку
  int i = 0;
  wclean(wbyf);
  if(namb==0)waddchar(wbyf,'0');
  while((namb!=0)&&(i<=10)){
    waddchar(wbyf,namb%10+'0');
    namb /=10;
    i++;
  }
  wrevers(wbyf);
}


void wdelspace(char *wbyf){ //удалить все пробелы
  while(wfindok(wbyf," ")){
    wdelsubspace(wbyf);
  }
}

void wnormalize(char *wbyf){ //все маленькими буквами
  int i=0;
  while(*(wbyf+i)!=0){
    if((*(wbyf+i)>='A')&(*(wbyf+i)<='Z')){
      *(wbyf+i)='a'+(*(wbyf+i)-'A');
    }
    if((*(wbyf+i)>='А')&(*(wbyf+i)<='Я')){
          *(wbyf+i)='а'+(*(wbyf+i)-'А');
        }
    i++;
  }
}



long whextolong(char *str, uint8_t rate){
	if(rate>8) rate = 8;
	long r = 0;
	for(int i = 0; i<rate; i++){
		char c = *(str+i);
		short temp;
		switch(c){
		case 'f': temp = 15; break;
		case 'e': temp = 14; break;
		case 'd': temp = 13; break;
		case 'c': temp = 12; break;
		case 'b': temp = 11; break;
		case 'a': temp = 10; break;
		default: temp = c-'0';
		}
		r +=this->wpow(16,i)*temp;
	}
	return r;
}

int wlongtohex(char *str, long n, uint8_t rate){
	short m = 0;
	int i = 0;
	do{
		m = n%16;
		n=n>>4;
		switch(m){
		case 15: this->waddcharin(str+i,'f'); break;
		case 14: this->waddcharin(str+i,'e'); break;
		case 13: this->waddcharin(str+i,'d'); break;
		case 12: this->waddcharin(str+i,'c'); break;
		case 11: this->waddcharin(str+i,'b'); break;
		case 10: this->waddcharin(str+i,'a'); break;
		default: this->waddcharin(str+i,(char)m+'0');
		}
		rate--;
		i++;
	}while(rate>0);
	return i;
}


inline void classinit(int len){
	WMAXLENGTH = len+2;
	pbyf = new char[WMAXLENGTH];
	this->winit(pbyf,WMAXLENGTH);
}

uint8_t wgethash8(const char *str, int &l){
	int i = 0;
	uint16_t crc = 0;
	while(*(pbyf+i)>1){
		crc +=(*(pbyf+i))*211;
		crc = crc^(crc>>8);
		crc =crc&0xff;
		i++;
	}
	l = i;
	return crc;
}

uint8_t wgethash8(const char *str){
	int i = 0;
	return wgethash8(str,i);
}

uint16_t wgethash16(const char *str, int &l){
	int i = 0;
	uint32_t crc = 0;
	while(*(pbyf+i)>1){
		crc +=(*(pbyf+i))*44111;
		crc = crc^(crc>>16);
		crc =crc&0xffff;
		i++;
	}
	l = i;
	return crc;
}
uint16_t wgethash16(const char *str){
	int i = 0;
	return wgethash16(str,i);
}

void tohex(){
		int n = this->length()+1;
		this->wcopy(pbyf+n,pbyf);
		int j = 0;
		for(int i=0; i<n-1; i++){
			j += this->wlongtohex(pbyf+j,*(pbyf+n+i),2);
		}
	}


void fromhex(){
		int n = this->length();
		int j = 0;
		for(int i=0; i<n-1; i+=2){
			char temp = (char) this->whextolong(pbyf+i,2);
			*(pbyf+i) = 0;
			*(pbyf+i+1) = 0;
			this->waddcharin(pbyf+j,temp);
			j ++;
		}
}

void scramble(char *str, const char *key){
	int n = wlength(str);
	if(n==0) return;
	int nk = wlength(key);
	int ik = 0;
	char byf;
	int temppos;
	for(int i=0; i<n; i++){
		byf = *(pbyf+i);
		if(n-1>0) temppos = (*(key+ik))%(n-1); else temppos = 0;
		*(pbyf+i) = *(pbyf+temppos);
		*(pbyf+temppos) = byf;
		if(!(ik<nk-1))ik = 0; else ik++;
	}
}

void descramble(char *str, const char *key){
	int n = wlength(str);
	if(n==0) return;
	int nk = wlength(key);
	int ik = 0;
	if(nk>0) ik = (n-1)%(nk);
	char byf;
	int temppos;
	for(int i=n-1; i>=0; i--){
		byf = *(pbyf+i);
		if(n-1>0) temppos = (*(key+ik))%(n-1); else temppos = 0;
		*(pbyf+i) = *(pbyf+temppos);
		*(pbyf+temppos) = byf;
		if(!(ik>0))ik = nk-1; else ik--;
	}
}

void keyxortexttohex(char *str, const char *key){
		int n = this->wlength(str)+1;
		int nk = this->wlength(key)-1;
		int ik = 0;
		this->wcopy(str+n,str);
		int j = 0;
		for(int i=0; i<n-1; i++){
			j += this->wlongtohex(str+j,(*(str+n+i))^(*(key+ik)),2);
			if(!(ik<nk))ik = 0; else ik++;
		}
	}

void keyxortextfromhex(char *str, const char *key){
	int n = this->length();
	int nk = this->wlength(key)-1;
	int ik = 0;
	int j = 0;
	for(int i=0; i<n-1; i+=2){
		char temp = (char)this->whextolong(pbyf+i,2)^(*(key+ik));
		*(pbyf+i) = 0;
		*(pbyf+i+1) = 0;
		this->waddcharin(pbyf+j,temp);
		j ++;
		if(!(ik<nk))ik = 0; else ik++;
	}
}

public:
	int size(){
		return WMAXLENGTH;
	}
	Tmstr(int len){
		classinit(len);
	};
	Tmstr(const char *str){
		classinit(wlength(str));
		wcopy(pbyf,str);
	};
	Tmstr(Tmstr &str){
		classinit(str.size());
		wcopy(pbyf,str.charstr());
	};
	~Tmstr(){
    	delete[] pbyf;
	}
	void setsize(int len){
		int tl = len+2;
		char* temp = new char[tl];
		this->winit(temp, tl);
		this->wcopy(temp,pbyf);
		delete[] pbyf;
		pbyf = temp;
		WMAXLENGTH = tl;
		
	}
	int getfree(){
		return WMAXLENGTH-2-(this->length());
	}
	int length(){
    	return this->wlength(pbyf);
	}
	int length(char* str){
    	return this->wlength(str);
	}
	char *charstr(){
		return pbyf;
	}
	void add(const char s){
		this->waddchar(pbyf,s);
	}
	void add(const char *str){
		this->waddstr(pbyf,str);
	}
	void add(Tmstr &str){
		this->waddstr(pbyf,str.charstr());
	}
	void clean(){
    	this->wclean(pbyf);
	}
	bool mgetpos(char* mask, int &a, int& b){
    	return wmsearch(pbyf, mask, a, b);
	}
	int getpos(char* sub){
        return wfind(pbyf, sub);
	}
	void deltopos(int pos){
		wdelto(pbyf,pos);
	}
	void delfrompos(int pos){
		wdelfrom(pbyf,pos);
	}
	int integer(){
		if(*pbyf=='-') return -this->wstrtolong(pbyf);
		else return this->wstrtolong(pbyf);
	}
	double real(){
	   if(*pbyf=='-'){
	   	del("-");
		return -this->wstrtodouble(pbyf);
	   }
		else return this->wstrtodouble(pbyf);
    }

	void trunc(int pos){
		if((pos<length())&&(pos>=0)) *(pbyf+pos) = 0;
	}
	/////////////////////
	bool search(const char *str){
		return this->wfindok(pbyf,str);
	}
	bool search(Tmstr &str){
		return search(str.charstr());
	}
		bool msearch(const char *str){
			return	this->wmmfindok(pbyf,str);
			}
		bool msearch(Tmstr &str){
			return msearch(str.charstr());
			}
	//////////////////////
	int searchcount(const char *str){
		int b = 0;
		int i = 0;
		int p = 0;
		while(b = wfind(pbyf+p,str),b>-1){
			p +=b+1;
			i++;
		}
		return i;
	}
	int searchcount(Tmstr str){
		return searchcount(str.charstr());
	}

		int msearchcount(const char *str){
			int a = 0;
			int b = 0;
			int i = 0;
			int p = 0;
			while(wmsearch(pbyf+p,str,a,b)){
				p +=b;
				i++;
			}
			return i;
		}
		int msearchcount(Tmstr str){
			return msearchcount(str.charstr());
		}
	////////////////////////////////
	bool extract(const char *str){
		return this->wmextract(pbyf, str);
	}
	bool extract(Tmstr &str){
		return extract(str.charstr());
	}
	bool extractminimal(char *str){
		return this->wmextractminimal(pbyf, str);
	}
	bool extractminimal(Tmstr &str){
		return this->extractminimal(str.charstr());
	}
	void tosmall(){
		this->wnormalize(pbyf);
	}
	//////////////////////////

	void addhash8(){
		int n = 0;
		uint8_t crc = this->wgethash8(pbyf,n);
		this->wlongtohex(pbyf+n,crc,2);
	}
	void addhash16(){
			int n = 0;
			uint16_t crc = this->wgethash16(pbyf,n);
			this->wlongtohex(pbyf+n,crc,4);
	}
	bool delhash8(){
		int l = length()-2;
		long n = this->whextolong(pbyf+l,2);
		this->trunc(l);
		long m = this->wgethash8(pbyf);
		return n==m;
	}
	bool delhash16(){
			int l = length()-4;
			long n = this->whextolong(pbyf+l,4);
			this->trunc(l);
			long m = this->wgethash16(pbyf);
			return n==m;
	}

	void encryption(const char *key){
		this->scramble(pbyf,key);
		keyxortexttohex(pbyf,key);
		this->scramble(pbyf,key);
	}
	void decryption(const char *key){
		this->descramble(pbyf,key);
		keyxortextfromhex(pbyf,key);
		this->descramble(pbyf,key);
	}
	//////////////////////////////////
	void replace(const char *oldstr,const char *newstr){
		int pos = 0;
		this->wreplace(pbyf,oldstr,newstr,pos);
	}
	void replace(Tmstr oldstr,Tmstr newstr){
		replace(oldstr.charstr(),newstr.charstr());
	}
	void replace(Tmstr oldstr,const char *newstr){
		replace(oldstr.charstr(),newstr);
	}
	void replace(const char *oldstr,Tmstr newstr){
		replace(oldstr,newstr.charstr());
	}

	void replace(const char *oldstr,const char *newstr, int count){
		int pos = 0;
		while((count>0)&&(this->wreplace(pbyf,oldstr,newstr,pos))) count--;
	}
	void replace(Tmstr oldstr,Tmstr newstr, int count){
		replace(oldstr.charstr(),newstr.charstr(),count);
	}
	void replace(Tmstr oldstr,const char *newstr, int count){
		replace(oldstr.charstr(),newstr,count);
	}
	void replace(const char *oldstr,Tmstr newstr,int count){
		replace(oldstr,newstr.charstr(),count);
	}
	void replaceall(const char *oldstr,const char *newstr){
       int pos = 0;
	   while(this->wreplace(pbyf,oldstr,newstr,pos));
	}
	void replaceall(Tmstr oldstr,Tmstr newstr){
		replaceall(oldstr.charstr(),newstr.charstr());
	}
	void replaceall(Tmstr oldstr,const char *newstr){
		replaceall(oldstr.charstr(),newstr);
	}
	void replaceall(const char *oldstr,Tmstr newstr){
		replaceall(oldstr,newstr.charstr());
	}

		void mreplace(const char *oldstr,const char *newstr){
			int pos = 0;
			this->wmreplace(pbyf,oldstr,newstr,pos);
		}
		void mreplace(Tmstr oldstr,Tmstr newstr){
			mreplace(oldstr.charstr(),newstr.charstr());
		}
		void mreplace(Tmstr oldstr,const char *newstr){
			mreplace(oldstr.charstr(),newstr);
		}
		void mreplace(const char *oldstr,Tmstr newstr){
			mreplace(oldstr,newstr.charstr());
		}

		void mreplace(const char *oldstr,const char *newstr, int count){
			int pos = 0;
			while((count>0)&&(this->wmreplace(pbyf,oldstr,newstr,pos))) count--;
		}
		void mreplace(Tmstr oldstr,Tmstr newstr, int count){
			mreplace(oldstr.charstr(),newstr.charstr(),count);
		}
		void mreplace(Tmstr oldstr,const char *newstr, int count){
			mreplace(oldstr.charstr(),newstr,count);
		}
		void mreplace(const char *oldstr,Tmstr newstr,int count){
			mreplace(oldstr,newstr.charstr(),count);
		}
		void mreplaceall(const char *oldstr,const char *newstr){
	       int pos = 0;
		while(this->wmreplace(pbyf,oldstr,newstr,pos));
		}
		void mreplaceall(Tmstr oldstr,Tmstr newstr){
			mreplaceall(oldstr.charstr(),newstr.charstr());
		}
		void mreplaceall(Tmstr oldstr,const char *newstr){
			mreplaceall(oldstr.charstr(),newstr);
		}
		void mreplaceall(const char *oldstr,Tmstr newstr){
			mreplaceall(oldstr,newstr.charstr());
		}
	/////////////////////////////////////////////////
	void insert(int pos, const char *str){
		if(wlength(pbyf+pos)>0){
			int l = wlength(str);
			wcopyrevers(pbyf+l+pos,pbyf+pos);
			wcopyin(pbyf+pos,str);
		}else{
			wcopy(pbyf+pos,str);
        }
	}
	void insert(int pos, Tmstr str){
		insert(pos,str.charstr());
	}
	void insert(int pos, const char c){
		char s[] = {c,0};
		insert(pos,&s[0]);
	}
	////////////////////////////////////
	void del(const char *str){
		int pos = 0;
		wdelsub(pbyf,str,pos);
	}
	void del(Tmstr str){
		del(str.charstr());
	}
	void del(const char *str, int count){
		int pos = 0;
		while((count>0)&&(wdelsub(pbyf,str,pos))) count--;
	}
	void del(Tmstr str, int count){
		del(str.charstr(),count);
	}
	void delall(const char *str){
		int pos = 0;
		while(wdelsub(pbyf,str,pos));
	}
	void delall(Tmstr str){
		delall(str.charstr());
	}
        void toHex(int value,int a){
                wlongtohex(pbyf,value,a);
        }


	void mdel(const char *str){
			int pos = 0;
			this->wmdelsub(pbyf,str,pos);
		}
		void mdel(Tmstr str){
			mdel(str.charstr());
		}
		void mdel(const char *str, int count){
			int pos = 0;
			while((count>0)&&(this->wmdelsub(pbyf,str,pos))) count--;
		}
		void mdel(Tmstr str, int count){
			mdel(str.charstr(),count);
		}
		void mdelall(const char *str){
			int pos = 0;
			while(this->wmdelsub(pbyf,str,pos));
		}
		void mdelall(Tmstr str){
			mdelall(str.charstr());
		}
		void revers(){
        	wrevers(pbyf);
		}
	///////////////////////////////////
	Tmstr & operator = (Tmstr &s){
		if(this!=&s){
			this->wclean(pbyf);
			this->wcopy(pbyf,s.charstr());
		}
		return *this;
	}
	Tmstr & operator = (const char *s){
		this->wclean(pbyf);
		this->wcopy(pbyf,s);
		return *this;
	}
	Tmstr & operator = (int a){
		this->wclean(pbyf);
		if(a<0){
			this->waddchar(pbyf,'-');
			a =-a;
			this->wlongtostr(a,pbyf+1);
		}else this->wlongtostr(a,pbyf);
		return *this;
	}
	Tmstr & operator = (double a){
		this->wclean(pbyf);
		int t = (int)a;
		(*this) += t;
		waddchar(pbyf,'.');
		a-=t;
		if(a<0) a*=-1;
		int i = 0;
		while((a!=0)&&(i<MAXCHARDOUBLE)){
			a*=10;
			t=(int)(a);
			(*this) += t;
			a-=t;
			i++;
		}
		while(*(pbyf+length()-1)=='0') *(pbyf+length()-1)=0;
		if(*(pbyf+length()-1)=='.') *(pbyf+length()-1)=0;
	}
	void operator += (const char *s){
		this->waddstr(pbyf,s);
	}
	void operator += (int a){
		if(a<0){
			this->waddchar(pbyf,'-');
			a =-a;
		}
		int l = this->length();
		this->wlongtostr((long)a,pbyf+l);
	}
	void operator += (const char c){
		this->waddchar(pbyf,c);
	}
	void operator += (Tmstr &s){
		this->waddstr(pbyf,s.charstr());
	}
	void operator -= (const char *s){
		this->wdelsub(pbyf,s);
	}
	void operator -= (const char c){
		char s[2] = {c,0};
		this->wdelsub(pbyf,&s[0]);
	}
	void operator -= (Tmstr &s){
		this->wdelsub(pbyf,s.charstr());
	}
	char & operator [] (int i){
		if(i<0){
			int a = this->length()+i;
			return *(pbyf+a);
		}else{
			return *(pbyf+i);
        }
	}
	bool operator [] (Tmstr &s){
		return this->wfindok(pbyf,s.charstr());
	}
	bool operator [] (const char *s){
    	return this->wfindok(pbyf,s);
	}
	bool operator == (const char *s){
    	return this->wcmp(pbyf,s);
	}
	bool operator == (Tmstr &s){
		return this->wcmp(pbyf,s.charstr());
	}
};
