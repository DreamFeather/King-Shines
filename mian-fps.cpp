#include<iostream>
#include<fstream>
#include"geth.h"
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
clock_t bg,ed;
using namespace std;
kar *x[100],**s=&x[0],**l=&x[1];
char warning[]="�ܱ�Ǹ,��Ϸ�����쳣,�����˳�!";
char teller[]="�ļ�ȱʧ"; 
char NPC[7][11]={"С��","������","����","�����","����","����"};
string file[7]={"С��.txt","������.txt","����.txt","�����.txt","����.txt","����.txt"};
ifstream ope[7];
char screen[2000];
char *now=screen;
void write(const char *p);

void Scrinit()				//���ڳ�ʼ�� 
{
	system("title ���߹�ҫ ����Ӣ������");
	system("mode con cols=140 lines=40");
	system("color fc");
}

inline void Set_mouse(const int &x,const int &y)//�ػ�ͼ��,���ù�� 
{
	HANDLE h =GetStdHandle(STD_OUTPUT_HANDLE);
	COORD p;
	p.X=x;p.Y=y;
	SetConsoleCursorPosition(h,p);
}

struct info			//�����ݴ�Ӣ�ۻ�����Ϣ 
{
	string name;		//���� 
	double blood;		//����Ѫ�� 
	double attack;		//�������� 
	int speed;			//�ٶ� 
}N[7];					//6������ 

void EXIT()				//�˳���Ϸ��ʾ 
{
	cout<<"\a";			//��ʾ�� 
	int ret=MessageBox(NULL,TEXT("�˳���Ϸ��"),TEXT("���߹�ҫ"),MB_YESNO|MB_ICONQUESTION);
	if(ret==IDYES)exit(0);
}

void loadhero(const int &i,const int &j)		//ѡ����ɫ���ʼ�� 
{
	*s=new kar(N[i].name,N[i].blood,N[i].attack,N[i].speed,0,2);	 
	*l=new kar(N[j].name,N[j].blood,N[j].attack,N[j].speed,49,2);	//����������ս����,����������Ϊ��ʼλ�� 
}

void loadinfo()									//���ļ�������Ӣ����Ϣ 
{
	int x;
	for(x=0;x<6;x++)
	{
		system("cls"); 
		ope[x].open(file[x].c_str());
		if(ope[x]==NULL)				//�ļ���ʧ�� 
		{
			MessageBox(NULL,TEXT(warning),TEXT(teller),MB_OK|MB_ICONWARNING);
			exit(0); 
		}
		ope[x]>>N[x].name>>N[x].blood>>N[x].attack>>N[x].speed;
		cout<<"		����������..."<<x+1<<"/"<<6;
	}
	cout<<endl<<"		�������";
}

void Selecthero()								//��Ӧѡ��Ӣ�۽��� 
{
	int x;
	loadinfo();
	now=screen;
	cout<<endl<<endl<<"			Press any key to start!"<<endl; 
	int i(0),j(5);
	char g=0;
	if(g=getch())system("cls");
	while(1)
	{
		g=getch();
		switch(g)
		{
			case 0x4B:j-=1;break;//left
			case 0x48:j-=1;break;//up
			case 0x4D:j+=1;break;//right
			case 0x50:j+=1;break;//down
			//case  224:break;
			case   97:i-=1;break;//a
			case  119:i-=1;break;//w
			case  100:i+=1;break;//d
			case  115:i+=1;break;//s
			case   27:EXIT();break;
			case   13:loadhero(i,j);return ;
		}
		i=(i+6)%6;j=(j+6)%6;
		now=screen;
		for(x=0;x<6;x++)
		{
			if(i==x)write("		��");
			else write("		 ");
			write("		 ");
			write(NPC[x]);
			if(j==x)write("		��");
			else write("		 "); 
			write("\n");
		}
		Set_mouse(0,0);//system("cls");
		cout<<"��ѡ��Ӣ��---(Enterȷ��)"<<endl<<endl;
		printf(screen);
		cout<<endl<<endl<<"		"<<"player1:"<<NPC[i]<<"			"<<"player2:"<<NPC[j]<<endl;
		cout<<endl<<"		"<<"����"<<"		"<<"����"<<"		"<<"����"<<endl<<endl;
		for(x=0;x<6;x++)
		{
			cout<<N[x].name<<"		"<<N[x].blood<<"		"<<N[x].attack<<"		"<<N[x].speed<<endl<<endl;
		}			//��ʾӢ�۲����Թ�ѡ��ο� 
	} 
}

void Hide_mouse()				//��ͼ���ع�� 
{
	CONSOLE_CURSOR_INFO mouse={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&mouse);
 } 

void initial()					//�����ʼ�� 
{
	Scrinit();					// ������ 
	Hide_mouse();				//���ع�� 
	Selecthero();				//���ѡ��Ӣ�� 
	system("cls");
}

void write(const char *p)				//�����������д����������� 
{
	int i(0);
	while(p[i]!='\0')
	{
		*now++=p[i++];
	}
	*now='\0';
}

void scan()							//ɨ���ͼ����ͼ 
{
	now=screen;
	register int i(0);
	int j,x;write("\n");
	int r;
	for(i=0;i<100;i++)				//���Ƶ�ͼ�ϱ߿� 
	{
		if(i>1&&i<98)
		{
			if(i%2==0)write("��");
			else write("��");
		}
		if(i==0||i==98)write("�X");
		if(i==1||i==99)write("�[");
	}
	
	write("\n");
	
	for(i=0;i<50;i++)					//ͻ�����1Ӣ��λ�� 
	{
		if((*s)->nowpos.ix==i)write("��");
		else if((*s)->scanbullet(i))write("��");
		else write("��");
	}
	write("\n");
	
	
	for(r=0;r<5;r++)					//ս������ 
	{
		for(i=0;i<50;i++)
		{
			j=(*s)->scanbullet(i,r);
			x=(*l)->scanbullet(i,r);
			if(j)
			{
				if(j==1)
				write("��");
				else write("��");
				continue;
			}
			if(x)
			{
				if(x==1)
				write(" �b");
				else write(" �e");
				continue;
			}
			if((*s)->nowpos.ix==i&&(*s)->nowpos.iy==r)
			{
				if((*s)->dir==1)write("��");
				else write("��");
				continue;
			}
			if((*l)->nowpos.ix==i&&(*l)->nowpos.iy==r)
			{
				if((*l)->dir==1)write("��");
				else write("��");
				continue;
			}
			write("��");
		}
		write("\n");
	}
	
	for(i=0;i<50;i++)					//ͻ�����2Ӣ��λ�� 
	{
		if((*l)->nowpos.ix==i)write("��");
		else if((*l)->scanbullet(i))write("��");
		else write("��");
	}
	
	write("\n");
	
	for(i=0;i<100;i++)					//���Ƶ�ͼ�±߿� 
	{
		if(i>1&&i<98)
		{
			if(i%2==0)write("��");
			else write("��");
		}
		if(i==0||i==98)write("�^");
		if(i==1||i==99)write("�a");
	}
	write("\n");
}

void disp()								//���ʵʱ��ս˫����Ϣ 
{
	Set_mouse(0,0);				//��귵����λ�� 
	printf(screen);
	cout<<"���:		"<<(*s)->name<<"			"<<(*l)->name<<endl;
	cout<<"Ѫ��:		"<<(*s)->blood<<"/"<<(*s)->Maxblood<<"                 "<<(*l)->blood<<"/"<<(*l)->Maxblood<<"                      "<<endl;
	cout<<"�����ӳ�:	"<<(*s)->buff*100<<"%"<<"                   "<<(*l)->buff*100<<"%"<<endl;
	cout<<"EXP:		"<<(*s)->EXP<<"				"<<(*l)->EXP<<"			"<<endl;
	int count(kar *);
	cout<<"�����ӵ���:	"<<count((*s))<<"				"<<count((*l))<<endl;
}

void play(char &A,char &B)			//�������� 
{
	(*s)->runbullet(x);
	(*l)->runbullet(x);
	if(A)
	(*s)->move(A);
	if(B)
	(*l)->move(B);
	(*s)->run();
	(*l)->run();
	A=B=0;
}

int count(kar *z)				//���ӵ� 
{
	bullet **a=z->b;
	int i,j(0);
	for(i=0;i<60;i++)if(a[i]!=NULL)j++;
	return j;
}


int main()
{
	initial();				//�����ʼ�� 
	char move1,move2,m;
	int m1(0),m2(0);
	scan();					
	disp();// ɨ�貢�����ʼ����ĵ�ͼ 
	while(1)
	{
		m1=m2=0;
		if(kbhit())
		{
			m=getch();
			if(m==27)EXIT();			//ESC�˳���ʾ 
			if(m>90)move1=m;
			else	move2=m;
		}
		bg=clock();				//�����ʱ 
		play(move1,move2);//���� 
		scan();				
		disp();				//�����ͼ 
		ed=clock();
		cout<<"�ӳ�:"<<(ed-bg)<<endl;
		cout<<"֡��:"<<1000.0/(ed-bg)<<endl; 
	}
}
