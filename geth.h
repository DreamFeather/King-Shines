#ifndef kar_H
#define kar_H
#include<iostream>
#include"pos.h"
class bullet;
using namespace std;
class kar
{
	public:
		string name;
		int grade,speed,EXP,dir,attack;				//dir 1,x�� ,-1,x�� , -2y��,2y��
		pos prepos,nowpos;							//��ʼλ�ú͵�ǰλ��
		int camp;									//������Ӫ
		int time,last;
		double blood,buff,Maxblood,Basicblood;		//��ǰѪ��,�ӳ�,���Ѫ��,����Ѫ��
		bullet *b[60];
		kar(string &n,double Bblood,int atta,int spe,int px,int py):name(n),Basicblood(Bblood),attack(atta),speed(spe),prepos(px,py)
		{
			nowpos=prepos;				//��ʼ����ǰλ�� 
			EXP=0;						//��ʼ������Ϊ0 
			grade=1;					//��ʼ���ȼ�Ϊ1 
			blood=Maxblood=Basicblood;	//��ʼ��Ѫ�� 
			if(prepos.ix>25)			//��ʼ����Ӫ�뿪������ 
			{
				dir=-1;
				camp=2;
			}
			else
			{
				dir=1;
				camp=1;
			}
			time=0;						//��ǰ��¼ʱ�� 
			last=-11;					//�ϴθ���ʱ�� 
			int i(0);
			for(; i<60; i++)b[i]=NULL;	//�ӵ�λ�ó�ʼ�� 
		}
		kar()						//�޲γ�ʼ�� 
		{
			time=0;
			last=-11;
			int i(0);
			for(; i<60; i++)b[i]=NULL;
		}
		int attacted(double value);		//�ܻ�,���ҷ��ؾ���ֵ�������� 
		void move(char);				//�ƶ� 
		void upgrade();					//���� 
		void run();						//ÿ�������� 
		void ifkilled();				//��ɱ 
		void recover();					//��Ѫ 
		void relive();					//���� 
		void shoot();					//��� 
		void runbullet(kar **B);		//�����ӵ� 
		int scanbullet(int locx,int locy);		//�ӵ����� 
};


int kar::attacted(double value)
{
	if(blood<0)return 0;				//������״̬,�����˺� 
	blood-=value/buff;					//Ѫ������ 
	if(blood<0)							//�պ����� 
	{
		ifkilled();
		return grade+attack*buff;		//���ظ���ľ���ֵ 
	}
	return grade;						//���ؾ���ֵ 
}

void kar::upgrade()						//����Ƿ����� 
{
	grade=EXP/1000+1;
	if(grade>15)grade=15;
	Maxblood=Basicblood+(grade-1)*10+EXP/100;
	buff=(grade-1+Maxblood/1000+EXP/2000)/100.0+1;
}

void kar::ifkilled()					
{
	if(blood==0)return ;				//�Ѿ�����,������ʱ 
	last=time;							//��ʱ 
	if(blood<0)							//��������λ�� 
	{
		nowpos.ix=-prepos.ix-1,blood=0;	//ʹ֮���ڵ�ͼ����ʾ 
	}
}

void kar::relive()						//���� 
{
	if(time-last>10)					//����ʱ���ѵ� 
	{
		nowpos=prepos;					//λ��Ϊ��ʼλ�� 
		blood=Maxblood;					//��Ѫ���� 
	}
}

void kar::run()							//Ӣ���ܲ��� 
{
	++time;								//ʱ��+1 
	upgrade();							//������ 
	ifkilled();							//�����Ƿ�ɸ��� 
	relive();							//���� 
	if(blood>0)shoot();					//û���Ϳ�ǹ 
}

void kar::move(char c)
{
	if(blood<=0)return ;				//���������ƶ� 
	if(camp==1)							//��Ӫ,����һ������ 
	{
		switch (c)
		{
			case 'a':
				dir=-1;
				nowpos.ix+=speed*dir;
				if(nowpos.ix<0)nowpos.ix=0;
				break;
			case 'd':
				dir=1;
				nowpos.ix+=speed*dir;
				if(nowpos.ix>49)nowpos.ix=49;
				break;
			case 'w':
				dir=-2;
				nowpos.iy+=speed*dir/2;
				if(nowpos.iy<0)nowpos.iy=0;
				break;
			case 's':
				dir=2;
				nowpos.iy+=speed*dir/2;
				if(nowpos.iy>4)nowpos.iy=4;
				break;
			case 'q':
				dir=-1;
				break;
			case 'e':
				dir=1;
				break;
		}
	}
	else
	{
		switch (c)
		{
			case 'K':
				dir=-1;
				nowpos.ix+=speed*dir;
				if(nowpos.ix<0)nowpos.ix=0;
				break;
			case 'M':
				dir=1;
				nowpos.ix+=speed*dir;
				if(nowpos.ix>49)nowpos.ix=49;
				break;
			case 'H':
				dir=-2;
				nowpos.iy+=speed*dir/2;
				if(nowpos.iy<0)nowpos.iy=0;
				break;
			case 'P':
				dir=2;
				nowpos.iy+=speed*dir/2;
				if(nowpos.iy>4)nowpos.iy=4;
				break;
			case '4':
				dir=-1;
				break;
			case '6':
				dir=1;
				break;
		}
	}
}

class bullet							//�ӵ��� 
{
	public:							
		int dir,speed,range,camp,len;			//����,�ٶ�,��Χ,��Ӫ,�����о��� 
		pos prepos,nowpos;						//��ʼλ��,����λ�� 
		bool boom;								//��ը��� 
		double attack;							//������ 
		kar *k;									//���䷽(Ӣ��) 
		bullet(kar *A):k(A),boom(false),len(3),dir(A->dir),speed(1),range(0),attack(A->attack*A->buff),camp(A->camp)
		{
			switch (A->dir)
			{
				case -1:prepos.ix=A->nowpos.ix-1,prepos.iy=A->prepos.iy;break;
				case -2:prepos.ix=A->nowpos.ix,prepos.iy=A->prepos.iy-1;break;
				case  1:prepos.ix=A->nowpos.ix+1,prepos.iy=A->prepos.iy;break;
				case  2:prepos.ix=A->nowpos.ix,prepos.iy=A->prepos.iy+1;break;
			}
			nowpos.ix=prepos.ix;
			nowpos.iy=prepos.iy;
		}
		int hit(kar *p);				//���Ӣ�� 
		void run(kar **B);				//ɨ�賡��Ӣ�� 
};

void bullet::run(kar **B)
{
	int i(0);
	for(; i<20; i++)				//���ӵ��ƶ�ǰ���Ƿ���Ӣ��ײ�� 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	if(boom)return ;				//�Ѿ���ը ���������� 
	if(dir==1||dir==-1)				//����һ�� 
	{
		nowpos.ix+=dir*speed;
	}
	else
	{
		nowpos.iy+=dir*speed/2;
	}
	if(nowpos.ix>52||nowpos.ix<-3)boom=true;			//��������ͼ��Χ 
	if(nowpos.iy<0||nowpos.iy>4)boom=true;				//Ĭ�ϱ�ը,�ȴ�ɾ�� 
	for(i=0; i<20; i++)								// ����֮�����ж��Ƿ���� 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	return ;
}

int bullet::hit(kar *p)								//����Ӣ�� 
{		
	if(p->camp==camp||p->blood==0)return 0;			//ͬ��Ӫ,�������Ĳ��� 
	if(!boom)										//û��ը,��ɻ����˺� 
	{
		if(p->nowpos==nowpos)
		{
			boom=true;								//�ѱ�ը 
			return p->attacted(attack);				//��������˺���õľ���ֵ 
		}
	}
	else if(p->nowpos-nowpos<=range)				//�ѱ�ը��ɷ�Χ�˺� 
	{
		return p->attacted(attack);				//��������˺���õľ���ֵ 
	}
	return 0;
}

void kar::shoot()								//Ӣ�ۿ�ǹ 
{
	int i(0);
	for(; i<60; i++)
	{
		if(b[i]==NULL)						//�ҵ���λ 
		{
			b[i]=new bullet(this);			//����һ�� 
			return ;
		}
	}
}

int kar::scanbullet(int locx,int locy=0)			//����ĳλ�õ��ӵ� 
{
	int i(0);
	pos p(locx,locy);
	for(; i<60; i++)
		if(b[i]&&b[i]->nowpos==p)
		{
			return b[i]->dir;
		}
	return 0;
}

void kar::runbullet(kar **B)				//�ӵ������� 
{
	int i(0);
	for(; i<60; i++)
	{
		if(b[i]!=NULL)
		{
			b[i]->run(B);
			if(b[i]->boom||b[i]->nowpos-b[i]->prepos>=3||b[i]->nowpos-b[i]->prepos<=-3)
			{
				delete b[i];				//��ը�˻��߳������з�Χ���ӵ���Ҫ���� 
				b[i]=NULL;
			}
		}
	}
}
#endif
