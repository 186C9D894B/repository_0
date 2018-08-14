#include<iostream>
#include<conio.h>
#include<ctime>
#include<fstream>
#include<map>
#include<random>
#include<sstream>
#include<string>
#include<vector>
#define NEW(X) static Word X(#X".txt")
using namespace std;
static default_random_engine Seed(time(nullptr));
uniform_real_distribution<double>Rand_2;
class Word
{
  private:
    vector<string>List;
    uniform_int_distribution<unsigned short>Rand;
  public:
    Word(const char*const Name)
    {
      string Temp;
      ifstream Data(Name);
      while(Data>>Temp)
        List.push_back(Temp);
      Rand=uniform_int_distribution<unsigned short>(0,List.size()-1);
    }
    string&operator()(void)
    {
      return List.at(Rand(Seed));
    }
};
static map<const char,Word*>Use;
void LINK(const char c,Word&w)
{
  Use[c]=&w;
  return;
}
NEW(Data);
NEW(A);
NEW(Ad);
NEW(Au);
NEW(Co);
NEW(D);
NEW(Nc);
NEW(Nu);
NEW(SO);
NEW(Te);
NEW(V0);
NEW(V1);
NEW(B);
NEW(Cl);
NEW(Lo);
void Link(void)
{
  LINK('j',A);
  LINK('v',Ad);
  LINK('A',Au);
  LINK('D',D);
  LINK('C',Co);
  LINK('n',Nc);
  LINK('N',Nu);
  LINK('S',SO);
  LINK('O',SO);
  LINK('T',Te);
  LINK('0',V0);
  LINK('1',V1);
  LINK('B',B);
  LINK('L',Cl);
  LINK('l',Lo);
  return;
}
string number()
{
  string d1="";
  if(Rand_2(Seed)<=0.1)
  d1+="n";
  else
  d1+="NC";
  return d1;
}
string adjective()
{
  string d1="";
  if(Rand_2(Seed)<=0.3)
  d1+="D";
  d1+="j";
  return d1;
}
string subject()
{
  string d1="";
  if(Rand_2(Seed)<=0.6)
  d1+=number();
  if(Rand_2(Seed)<=0.6)
  d1+=adjective();
  d1+="S";
  return d1;
}
string object()
{
  string d1="";
  if(Rand_2(Seed)<=0.6)
  d1+=number();
  if(Rand_2(Seed)<=0.6)
  d1+=adjective();
  d1+="O";
  return d1;
}
string cnnumber(char s)
{
  switch(s)
  	{
  	  case '0':
  	  	return "〇";
  	  case '1':
  	  	return "一";
  	  case '2':
  	  	return "二";
  	  case '3':
  	  	return "三";
  	  case '4':
  	  	return "四";
  	  case '5':
  	  	return "五";
  	  case '6':
  	  	return "六";
  	  case '7':
  	  	return "七";
  	  case '8':
  	  	return "八";
  	  case '9':
  	  	return "九";
  	  default:
		return "";
    }
}
string cnnumber1(string s)
{
  string s1=s;
  string d="";
  char d1[4]="";
  string d2="";
  int i=0;
  bool m=0;
  int iszero=0;
  if(s=="0")
  {
  	d=cnnumber('0');
  	return d;
  }
  for(i=0;;i++)
  {
  	for(int j=0;j<4;j++)
  	{
  	  d1[3-j]='\0'; 
	  if(s1.size()>0)
  	  {
  	  	d1[3-j]=s1[s1.size()-1];
  	  	s1=s1.substr(0,s1.size()-1);
	  }
  	  else
  	    m=1;
	}
	iszero=0;
	for(int j=0;j<4;j++)
	{
	  if(d1[j]>='1'&&d1[j]<='9')
	  {
	  	if(iszero==2)
	  	{
	  	  d2+=cnnumber('0');
		}
		iszero=1;
	  	if(d2!=""||j!=2||d1[j]!='1')
		  d2+=cnnumber(d1[j]);
	  	switch(j)
	    {
	      case 0:
	  	    d2+="千";
		    break;
		  case 1:
	  	    d2+="百";
	    	break;
	      case 2:
	  	    d2+="十";
		    break;
     	}
	  }
	  if(d1[j]=='0'&&iszero==1)
	  {
	  	iszero=2;
	  }
	}
	if(d2.size())
	  switch(i)
	  {
	  	case 1:
	  	  d2+="万";
		  break;
		case 2:
	  	  d2+="亿";
		  break;
		case 3:
	  	  d2+="兆";
		  break;
		case 4:
	  	  d2+="京";
		  break;
	  }
	d=d2+d;
	d2="";
	if(m)
	break;
  }
  return d;
}
string cnnumber0(string s)
{
  string d="";
  string d1="";
  int i=0;
  bool isint=1;
  bool isnum=0;
  for(i=0;s[i]!='\0';i++)
  {
  	if(s[i]>='0'&&s[i]<='9'&&isint)
  	  {
  	  	d1+=s[i];
  	  	isnum=1;
  	  	continue;
      }
    d+=cnnumber1(d1);
    d1="";
    d+=cnnumber(s[i]);
	switch(s[i])
  	{
  	  case '.':
  	  	d+="点";
  	  	isint=0;
  	  	isnum=1;
  	  	break;
  	  case '+':
  	  	if(isnum)
	    d+="加";
	    else
	    d+="正";
  	  	isint=1;
  	  	isnum=0;
  	  	break;
  	  case '-':
  	    if(isnum)
	    d+="减";
	     else
	    d+="负";
        isint=1;
  	    isnum=0;
  	    break;
  	    break;
  	  case 'i':
  	  	d+="i";
  	  	break;
    }
  }
  d+=cnnumber1(d1);
  return d;
}
string Sentence(void)
{
  string d="";
  if(Rand_2(Seed)<=0.2)
  {
    d+=subject();
	if(Rand_2(Seed)<=0.1)
	{
	  d+="l";
	  d+=subject();
	}
    if(Rand_2(Seed)<=0.4)
    d+="T";
    if(Rand_2(Seed)<=0.6)
    d+="v";
    d+="L";
  }
  d+=subject();
  if(Rand_2(Seed)<=0.1)
	{
	  d+="l";
	  d+=subject();
	}
  if(Rand_2(Seed)<=0.4)
  d+="T";
  if(Rand_2(Seed)<=0.6)
  d+="v";
  if(Rand_2(Seed)<=0.7)
  {
    if(Rand_2(Seed)<=0.3)
    {
      d+="B";
      if(Rand_2(Seed)<=0.7)
      {
        d+=object();
        if(Rand_2(Seed)<=0.1)
	{
	  d+="l";
	  d+=object();
	}
      }
      d+="1";
      if(Rand_2(Seed)<=0.4)
      d+="A";
    }
    else
    {
      d+="1";
      if(Rand_2(Seed)<=0.4)
      d+="A";
      d+=object();
    }
  }
  else
  {
    d+="0";
    if(Rand_2(Seed)<=0.4)
    d+="A";
  }
  string s;
  char buffer[32]="";
  for(auto c:d)
  {
    if(c!='N'||Rand_2(Seed)<=0.1)
    s+=Use[c]->operator()();
    else
    {
    double a;
    string s1;
    a=16*Rand_2(Seed);
    if(Rand_2(Seed)<=0.5)
      a=256/a;
    if(Rand_2(Seed)<=0.5)
      a=static_cast<long long>(a);
    if(Rand_2(Seed)<=0.5)
      a=-a;
    sprintf(buffer,"%g",a);
	s1+=buffer;
    if(Rand_2(Seed)<=0.5)
      s1=cnnumber0(s1);
	s+=s1;
    }
  }
  return s;
}
int main(void)
{
  Link();
  while(true)
  {
    cout<<Sentence()<<endl;;
    getch();
  }
  return 0;
}
