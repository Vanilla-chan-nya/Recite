#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<map>
#include<set>
#include<queue>
#include<vector>
#include<fstream>
#include<windows.h>
#include<sstream>
#include<ctime>
#include<conio.h>
#define IL inline
#define re register
#define LL long long
#define ULL unsigned long long
#ifdef TH
#define debug printf("Now is %d\n",__LINE__);
#else
#define debug
#endif
using namespace std;
bool judge()
{
	string str;
	cin>>str;
	if(str=="Y"||str=="Yes"||str=="YES"||str=="yes"||str=="y") return 1;
	return 0;
}
//Settings
vector<string>setting;
vector<int>setting_value;
void settings()
{
	system("cls");
	int pos=0;
	for(unsigned int i=0;i<setting.size();i++)
	{
		cout<<i<<" "<<setting[i]<<endl;
	}
	char ch;
	while(1)
	{
		while(!kbhit()) Sleep(50);
		ch=getch();
		if(ch=='w'||ch=='W'||ch=='s'||ch=='S')
		{
			if(ch=='w'||ch=='W') pos=(pos-1+setting.size())%setting.size();
			if(ch=='s'||ch=='S') pos=(pos+1+setting.size())%setting.size();
		}
		
	}
}
const int A=10,B=11,C=12,D=13,E=14,F=15;

void gotoxy(int x, int y)
{
    COORD pos;
    pos.X =x;
    pos.Y =y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void SetColor(unsigned short BackGroundColor,unsigned short ForeColor)
{
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);  
    SetConsoleTextAttribute(hCon,(ForeColor%16)|(BackGroundColor%16*16));  
}

void SetColor(unsigned short x)
{
    HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);  
    SetConsoleTextAttribute(hCon,x);  
}

void hide()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
}

int Pre=15;//prepare words
int trie[300000][26];
int f[300000];
int c[300000];
bool v[300000];
int cnt,n;
vector<string>dic_list;
map<int,string>mean;//pos to mean
map<int,string>word;//pos to word 
bool had[300000][20];
set<int>star;
map<int,double>prof;
void insert(string str,string m,int belong)
{
	int pos=0;
	for(unsigned int i=0;i<str.size();i++)
	{
		if(str[i]>='A'&&str[i]<='Z') str[i]+='a'-'A';
		if(!trie[pos][str[i]-'a']) trie[pos][str[i]-'a']=++cnt,f[cnt]=pos,c[cnt]=str[i]-'a';
		pos=trie[pos][str[i]-'a'];
	}
	if(had[pos][belong])
	{
		return;
	}
	had[pos][belong]=1;
	v[pos]=1;
	if(mean.find(pos)==mean.end()) n++;
	mean[pos]+="["+dic_list[belong]+"]\n"+m+"\n\n";
	word[pos]=str;
}
int find(string str)
{
	int pos=0;
	for(unsigned int i=0;i<str.size();i++)
	{
		if(!trie[pos][str[i]-'a']) return -1;
		pos=trie[pos][str[i]-'a'];	
	}
	if(v[pos]) return pos;
	return -1;
}
void save()
{
	ofstream fout("info.txt");
	fout<<star.size()<<endl;
	for(set<int>::iterator it=star.begin();it!=star.end();it++)
	{
		fout<<word[*it]<<endl;
	}
	fout<<prof.size()<<endl;
	for(map<int,double>::iterator it=prof.begin();it!=prof.end();it++)
	{
		fout<<word[it->first]<<" "<<it->second<<endl;
	}
	fout.close();
}
//inquire history
void put_his(string str)
{
	ofstream fout("his.txt",ios::app|ios::out);
	fout<<str<<endl;
	fout.close();
}
//detail mean
void out(int x)
{
	if(x==0) return;
	out(f[x]);
	putchar(c[x]+'a');
}
vector<int>tot;
queue<int>q;
void bfs(int x)
{
	if(x==0) return;
	if(tot.size()>=(unsigned int)Pre) return;
	while(q.size()) q.pop();
	q.push(x);
	while(q.size())
	{
		x=q.front();
		q.pop();
		if(v[x])
		{
			tot.push_back(x);
			gotoxy(0,tot.size());
			if(star.find(x)!=star.end()) SetColor(0,4);
			out(x);
			SetColor(0,7);
			if(tot.size()>=(unsigned int)Pre) return;
		}
		for(int i=0;i<26;i++)
		{
			if(trie[x][i]) q.push(trie[x][i]);
		}
	}
}
void dfs(int x)
{
	if(x==0) return;
	if(tot.size()>=(unsigned int)Pre) return;
	if(v[x])
	{
		tot.push_back(x);
		gotoxy(0,tot.size());
		if(star.find(x)!=star.end()) SetColor(0,4);
		out(x);
		SetColor(0,7);
	}
	for(int i=0;i<26;i++)
	{
		if(trie[x][i]) dfs(trie[x][i]);
	}
}
void pre(int x)
{
	tot.clear();
	for(int i=1;i<=Pre;i++) gotoxy(0,i),puts("                              ");
	dfs(x);
}
void detail(int x)
{
	if(tot.size()==0) return;
	char ch;
	string m;
	int line=0;
	gotoxy(0,line+1);SetColor(7,0);out(tot[0]);SetColor(0,7);
	gotoxy(0,tot.size()+2);
	m=mean[tot[line]];
	for(unsigned int i=0;i<m.size();i++)
	{
		putchar(m[i]);
	}
	while(1)
	{
		while(!kbhit()) Sleep(20);
		ch=getch();
		if(ch==-32)
		{
			while(!kbhit()) Sleep(20);
			ch=getch();
			if(ch==72) ch='w';
			if(ch==80) ch='s';
		}
		if(ch=='\t') return;
		if(ch=='\r')
		{
			if(star.find(tot[line])==star.end())
			{
				star.insert(tot[line]);
				gotoxy(0,line+1);
				SetColor(7,4);
				out(tot[line]);
				SetColor(0,7);
			}
			else
			{
				star.erase(tot[line]);
				gotoxy(0,line+1);
				SetColor(7,0);
				out(tot[line]);
			}
			//add to prof
			if(prof.find(tot[line])==prof.end()) prof[tot[line]]=1;
			save();
		}
		if(ch=='w')
		{
			line=(line+tot.size()-1)%tot.size();
		}
		if(ch=='s')
		{
			line=(line+1)%tot.size();
		}
		if(ch=='w'||ch=='s')
		{
			SetColor(0,7);
			system("cls");
			out(x);
			putchar('\n');
			for(unsigned int i=0;i<tot.size();i++)
			{
				if(star.find(tot[i])!=star.end()) SetColor(0,4);
				else SetColor(0,7);
				out(tot[i]);
				putchar('\n');
			}
			gotoxy(0,line+1);
			if(star.find(tot[line])!=star.end()) SetColor(7,4);
			else SetColor(7,0);
			out(tot[line]);
			//out mean
			SetColor(0,7);
			gotoxy(0,tot.size()+2);
			m=mean[tot[line]];
			for(unsigned int i=0;i<m.size();i++)
			{
				putchar(m[i]);
			}
		}
	}
}
/*
0 = ��ɫ       8 = ��ɫ
1 = ��ɫ       9 = ����ɫ
2 = ��ɫ       A = ����ɫ
3 = ǳ��ɫ     B = ��ǳ��ɫ
4 = ��ɫ       C = ����ɫ
5 = ��ɫ       D = ����ɫ
6 = ��ɫ       E = ����ɫ
7 = ��ɫ       F = ����ɫ
*/

void read_info()
{
	ifstream fin("info.txt");
	int sze,pos;
	double dt;
	string str;
	fin>>sze;
	for(int i=0;i<sze;i++)
	{
		fin>>str;
		pos=find(str);
		if(pos==-1)
		{
			cout<<"read error:"<<str<<" is not existed"<<endl;
			continue;
		}
		star.insert(pos);
	}
	fin>>sze;
	cout<<"size="<<sze<<endl;
	for(int i=0;i<sze;i++)
	{
		fin>>str;
//		cout<<str<<endl;
		fin>>dt;
		pos=find(str);
		if(pos==-1)
		{
			cout<<"read error:"<<str<<" is not existed"<<endl;
			continue;
		}
		prof[pos]=dt;
	}
}

void read(string file,int belong)
{
	ifstream fin(file);
	string t,str,w;
	bool succ;
	while(fin.peek()&&!fin.eof())
	{
		getline(fin,t);
		while(t[0]=='-') getline(fin,t);
		str.clear();
		succ=1;
		w=t;
		getline(fin,t);
		while(t[0]!='-') str.push_back('\n'),str+=t,getline(fin,t);
		for(unsigned int i=0;i<w.size();i++)
		{
			if(w[i]>='A'&&w[i]<='Z') w[i]+='a'-'A';
			if(w[i]>'z'||w[i]<'a')
			{
				succ=0;
				break;
			}
		}
		if(succ) insert(w,str,belong);
	}
	fin.close();
	debug
}
void init()
{
	system("title Recite");
	//initialization settings
//	setting.push_back();
	
	//read dictionary
//	read_base();
	ifstream fin("wordlist.txt");
	int tn;
	fin>>tn;
	string t;
	cout<<"��"<<tn<<"���ֵ�"<<endl;
	for(int i=0;i<tn;i++)
	{
		fin>>t;
		dic_list.push_back(t);
		cout<<"read dic:"<<t<<endl;
		fin>>t;
		read("dictionary\\"+t,i);
		//D:\Github\Recite\dictionary\basemean.txt
		cout<<"now n="<<n<<endl;
	}
	//read personal information
	read_info();
}

void web_translation()
{
	SetColor(0,7);
	system("cls");
	cout<<"0\tback\n1\ten->zh\n2\tzh->en"<<endl;
	char t;
	string a,b;
	while(t!='1'&&t!='2')
	{
		while(!kbhit()) Sleep(50);
		t=getch();
		if(t=='0') return;
	}
	if(t=='1')
	{
		a="en";
		b="zh";
	} 
	else if(t=='2')
	{
		a="zh";
		b="en";
	}
	string str;
	system("cls");
	cout<<"��������Ҫ����ľ��ӣ���#��β"<<endl;
	getline(cin,str,'#');
	ofstream fout("sentence.txt");
	fout<<a<<endl<<b<<endl<<str;
	fout.close();
	system("python baidu-api.py"); 
	ifstream fin("ans.txt");
	string zt;
	getline(fin,zt);
	getline(fin,str);
	if(zt=="True")
	{
		cout<<"�������"<<endl<<str;
	}
	else
	{
		cout<<"����ʧ��"<<endl<<str;
	}
	putchar('\n');
	system("pause");
	web_translation();
}
vector<int>rand_list;
bool P(double x)
{
	return (rand()%10000)/10000.0<=pow(2,-x/50)*0.9+0.1;
}
int rand_pos()
{
	int res,stime=clock();
	while(1)
	{
		res=rand()*rand()%(cnt+1);
		if(v[res]) return res;
		if(clock()-stime>1000) break;
	}
	return 0;
}
void practice()
{
	system("cls");
	SetColor(0,7);
	char ch;
	rand_list.clear();for(map<int,double>::iterator it=prof.begin();it!=prof.end();it++) rand_list.push_back(it->first);
	system("title \"Recite:practice 0->back|Enter->continue|1->Random one word|2->Random ten words!\"");
	cout<<"��ӭ����������ϰ������֮ǰ��ϣ�����Լ������ĵ������Ѿ�֪���˴�ŵĹ���\n�������������֪��Ҳû�й�ϵ��������ʹ�÷�����"<<endl<<endl;
	cout<<"���ղع��ĵ��ʻ�������ʱ�����ʹȡ���ղ��ˣ����������Ȼ�����ʱ��С�\n����԰�Tab���鿴���ʱ���"<<endl<<endl;
	cout<<"Ŀǰ��ϰ��ʽ��Ҫ������:����ѡ��͵���ƴд����Ȼ��һ�ֺܼ򵥣��ǲ��ǣ�" <<endl<<endl;
	cout<<"��ͬ����Ŀ�Լ����Ĵ���ȷ��������������Ų�ͬ��Ӱ�죬���������ֻ�ʹ���Ƽ������ĵ��ʸ��ʲ�ͬ��\n������Խ�ͣ�Խ���ױ�������"<<endl<<endl;
	cout<<"�������̫�ٻ����������ȶ��ϸߣ���Ὠ�����������ʴʻ㣡"<<endl<<endl; 
	cout<<"Good luck to you!"<<endl<<endl;
	system("pause");
	unsigned int rd;
	string str;
	int choose[4];
	while(1)
	{
		system("cls");
		cout<<"--------------------------------------------------"<<endl;
		int i;
		for(i=1;i<=100;i++)
		{
			rd=rand()*rand()%rand_list.size();
			if(P(prof[rand_list[rd]])) break;
		}
		if(i>100)
		{
			rd=rand()*rand()%rand_list.size();
			cout<<"��Щ���ʺ��񶼺������˰���Ҫ��Ҫ�����´ʣ�"<<endl;
		}
		if(P(prof[rand_list[rd]]))//choose
		{
			cout<<"����"<<word[rand_list[rd]]<<"��ʲô��˼��"<<endl; 
			for(int i=1;i<=3;i++)
			{
				choose[i]=rand_pos();
				while(choose[i]==rand_list[rd]) choose[i]=rand_pos();
				if(choose[i]==0) cout<<"match error"<<endl;
			}
			choose[0]=rand_list[rd];
			random_shuffle(choose,choose+4);
			cout<<"----------"<<endl;
			for(int i=0;i<4;i++)
			{
				cout<<(char)(i+'A')<<endl<<mean[choose[i]]<<"----------"<<endl;
			}
			cin>>str;
			for(unsigned int i=0;i<str.size();i++) if(str[i]>='a'&&str[i]<='z') str[i]+='A'-'a';
			bool flag=0;
			for(unsigned int i=0;i<str.size();i++)
			{
				if(str[0]<='Z'&&str[0]>='A'&&str[0]-'A'<=3)
				{
					if(choose[str[0]-'A']==rand_list[rd])
					{
						cout<<"Right!"<<endl;
						flag=1;
						prof[rand_list[rd]]+=1;
					}
					else
					{
						cout<<"Wrong!The answer is "<<mean[rand_list[rd]]<<endl;
						prof[rand_list[rd]]*=0.4;
						flag=1;
					}
					break;
				}
			}
			if(!flag)
			{
				cout<<"Wrong!The answer is "<<mean[rand_list[rd]]<<endl;
				prof[rand_list[rd]]*=0.4;
			}
		}
		else//spell
		{
			cout<<"��ƴд��������ʣ�"<<endl;
			cout<<mean[rand_list[rd]]<<endl; 
			cin>>str;
			if(str==word[rand_list[rd]])
			{
				cout<<"Right!"<<endl;
				prof[rand_list[rd]]+=5;
			}
			else
			{
				cout<<"Wrong!The answer is "<<endl<<word[rand_list[rd]]<<endl;
				prof[rand_list[rd]]*=0.6;
			}
		}
		save();
		cin.sync();
		int t;
		Sleep(500);
		cout<<"���س�������ϰ\n��0��ESC���ز��ҳ��\nTab����ʾ������ϰ���\n";
		while(1)
		{
			while(!kbhit()) Sleep(50);
			ch=getch();
			if(ch=='\r'||ch=='\n') break;
			if(ch=='0'||ch==27) return;
			if(ch=='\t')
			{
				for(map<int,double>::iterator it=prof.begin();it!=prof.end();it++) cout<<word[it->first]<<" "<<it->second<<endl;
			}
			if(ch=='1')
			{
				prof[t=rand_pos()]+=1;
				cout<<"�����µ��ʣ�";
				out(t);
				cout<<mean[t]<<endl; 
				rand_list.clear();for(map<int,double>::iterator it=prof.begin();it!=prof.end();it++) rand_list.push_back(it->first);
				save();
			}
			if(ch=='2')
			{
				cout<<"����10���µ��ʣ�"<<endl;
				for(int i=0;i<10;i++) prof[t=rand_pos()]+=1,out(t),cout<<mean[t]<<endl;
				rand_list.clear();for(map<int,double>::iterator it=prof.begin();it!=prof.end();it++) rand_list.push_back(it->first);
				save();
			}
			if(ch==-32)
			{
				while(!kbhit()) Sleep(50);
				ch=getch();
				if(ch==83)
				{
					cout<<"��ȷ��Ҫɾ��\""<<word[rd]<<"\"���������?(Y/N)"<<endl;
					if(judge())
					{
						prof.erase(rd);
						rand_list.clear();for(map<int,double>::iterator it=prof.begin();it!=prof.end();it++) rand_list.push_back(it->first);
						cout<<"ɾ���ɹ�"<<endl; 
					}
				}
			}
		}
		
	}
}

int main()
{
	hide();
	srand(time(0));
	init();
	cout<<"������"<<n<<"�����ʣ���ʱ"<<clock()/1000.0<<"s"<<endl;
	cout<<"cnt="<<cnt<<endl;
	cout<<"��ȡ�������ݣ�"<<endl<<"�ղ���"<<star.size()<<"������"<<endl<<"���ʱ�����"<<prof.size()<<"������"<<endl; 
	Sleep(1500);
	system("cls");
	int pos=0;
	char ch;
	string str;
	while(1)
	{
//		stringstream ss;
//		ss<<pos;
//		system(("title "+ss.str()).c_str());
		while(!kbhit()) Sleep(20);
		ch=getch();
		if(ch=='0')
		{
			SetColor(0,7);
			system("cls");
			pos=0;
			str.clear();
		}
		if(ch==-32)
		{
			while(!kbhit()) Sleep(20);
			ch=getch();
			if(ch==83)
			{
				SetColor(0,7);
				system("cls");
				pos=0;
				str.clear();
				continue;
			}
			else continue;
		}
		if(ch=='\t')
		{
			put_his(str);
			detail(pos);
			SetColor(0,7);
			system("cls");
			gotoxy(0,0);
			cout<<str;
			pre(pos);
			gotoxy(str.size(),0);
		}
		if(ch=='1')
		{
			settings();
			SetColor(0,7);
			system("cls");
			gotoxy(0,0);
			cout<<str;
			pre(pos);
			gotoxy(str.size(),0);
		}
		if(ch=='2')
		{
			web_translation();
			SetColor(0,7);
			system("cls");
			gotoxy(0,0);
			cout<<str;
			pre(pos);
			gotoxy(str.size(),0);
		}
		if(ch=='3')
		{
			practice();
			SetColor(0,7);
			system("cls");
			gotoxy(0,0);
			cout<<str;
			pre(pos);
			gotoxy(str.size(),0);
			system("title Recite");
		}
		if(ch=='\b')
		{
			if(str.size())
			{
				gotoxy(str.size(),0);
				str.pop_back();
				putchar('\b');
				putchar(' ');
				putchar('\b');
				pos=f[pos];
				pre(pos);
				gotoxy(str.size(),0);
			}
			continue;
		}
		if(ch>='A'&&ch<='Z') ch-='A'-'a';
		if(ch>='a'&&ch<='z')
		{
			gotoxy(str.size(),0);putchar(ch);
			str.push_back(ch);
			if(!trie[pos][ch-'a']) trie[pos][ch-'a']=++cnt,f[cnt]=pos,c[cnt]=ch-'a';
			pos=trie[pos][ch-'a'];
			pre(pos);
			gotoxy(str.size(),0);
		}
	}
	
	
	return 0;
}


