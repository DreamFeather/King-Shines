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
		int grade,speed,EXP,dir,attack;				//dir 1,x正 ,-1,x负 , -2y负,2y正
		pos prepos,nowpos;							//初始位置和当前位置
		int camp;									//隶属阵营
		int time,last;
		double blood,buff,Maxblood,Basicblood;		//当前血量,加成,最大血量,基础血量
		bullet *b[60];
		kar(string &n,double Bblood,int atta,int spe,int px,int py):name(n),Basicblood(Bblood),attack(atta),speed(spe),prepos(px,py)
		{
			nowpos=prepos;				//初始化当前位置 
			EXP=0;						//初始化经验为0 
			grade=1;					//初始化等级为1 
			blood=Maxblood=Basicblood;	//初始化血量 
			if(prepos.ix>25)			//初始化阵营与开场方向 
			{
				dir=-1;
				camp=2;
			}
			else
			{
				dir=1;
				camp=1;
			}
			time=0;						//当前记录时间 
			last=-11;					//上次复活时间 
			int i(0);
			for(; i<60; i++)b[i]=NULL;	//子弹位置初始化 
		}
		kar()						//无参初始化 
		{
			time=0;
			last=-11;
			int i(0);
			for(; i<60; i++)b[i]=NULL;
		}
		int attacted(double value);		//受击,并且返回经验值给攻击方 
		void move(char);				//移动 
		void upgrade();					//升级 
		void run();						//每次总运行 
		void ifkilled();				//被杀 
		void recover();					//回血 
		void relive();					//复活 
		void shoot();					//射击 
		void runbullet(kar **B);		//处理子弹 
		int scanbullet(int locx,int locy);		//子弹计数 
};


int kar::attacted(double value)
{
	if(blood<0)return 0;				//已死亡状态,不受伤害 
	blood-=value/buff;					//血量减少 
	if(blood<0)							//刚好死亡 
	{
		ifkilled();
		return grade+attack*buff;		//返回更多的经验值 
	}
	return grade;						//返回经验值 
}

void kar::upgrade()						//检查是否升级 
{
	grade=EXP/1000+1;
	if(grade>15)grade=15;
	Maxblood=Basicblood+(grade-1)*10+EXP/100;
	buff=(grade-1+Maxblood/1000+EXP/2000)/100.0+1;
}

void kar::ifkilled()					
{
	if(blood==0)return ;				//已经死亡,跳过计时 
	last=time;							//计时 
	if(blood<0)							//处理死亡位置 
	{
		nowpos.ix=-prepos.ix-1,blood=0;	//使之不在地图上显示 
	}
}

void kar::relive()						//复活 
{
	if(time-last>10)					//复活时间已到 
	{
		nowpos=prepos;					//位置为初始位置 
		blood=Maxblood;					//满血复活 
	}
}

void kar::run()							//英雄总操作 
{
	++time;								//时间+1 
	upgrade();							//级别处理 
	ifkilled();							//死亡是否可复活 
	relive();							//复活 
	if(blood>0)shoot();					//没死就开枪 
}

void kar::move(char c)
{
	if(blood<=0)return ;				//死亡不可移动 
	if(camp==1)							//阵营,左玩家或右玩家 
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

class bullet							//子弹类 
{
	public:							
		int dir,speed,range,camp,len;			//方向,速度,范围,阵营,最大飞行距离 
		pos prepos,nowpos;						//初始位置,现在位置 
		bool boom;								//爆炸与否 
		double attack;							//攻击力 
		kar *k;									//发射方(英雄) 
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
		int hit(kar *p);				//打击英雄 
		void run(kar **B);				//扫描场上英雄 
};

void bullet::run(kar **B)
{
	int i(0);
	for(; i<20; i++)				//在子弹移动前看是否有英雄撞上 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	if(boom)return ;				//已经爆炸 不再往下走 
	if(dir==1||dir==-1)				//飞行一次 
	{
		nowpos.ix+=dir*speed;
	}
	else
	{
		nowpos.iy+=dir*speed/2;
	}
	if(nowpos.ix>52||nowpos.ix<-3)boom=true;			//若超出地图范围 
	if(nowpos.iy<0||nowpos.iy>4)boom=true;				//默认爆炸,等待删除 
	for(i=0; i<20; i++)								// 走完之后再判断是否击中 
	{
		if(B[i]!=NULL)k->EXP+=hit(B[i]);
	}
	return ;
}

int bullet::hit(kar *p)								//遇到英雄 
{		
	if(p->camp==camp||p->blood==0)return 0;			//同阵营,已死亡的不算 
	if(!boom)										//没爆炸,造成击中伤害 
	{
		if(p->nowpos==nowpos)
		{
			boom=true;								//已爆炸 
			return p->attacted(attack);				//返回造成伤害获得的经验值 
		}
	}
	else if(p->nowpos-nowpos<=range)				//已爆炸造成范围伤害 
	{
		return p->attacted(attack);				//返回造成伤害获得的经验值 
	}
	return 0;
}

void kar::shoot()								//英雄开枪 
{
	int i(0);
	for(; i<60; i++)
	{
		if(b[i]==NULL)						//找到空位 
		{
			b[i]=new bullet(this);			//发射一颗 
			return ;
		}
	}
}

int kar::scanbullet(int locx,int locy=0)			//计算某位置的子弹 
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

void kar::runbullet(kar **B)				//子弹总运行 
{
	int i(0);
	for(; i<60; i++)
	{
		if(b[i]!=NULL)
		{
			b[i]->run(B);
			if(b[i]->boom||b[i]->nowpos-b[i]->prepos>=3||b[i]->nowpos-b[i]->prepos<=-3)
			{
				delete b[i];				//爆炸了或者超出飞行范围的子弹需要销毁 
				b[i]=NULL;
			}
		}
	}
}
#endif
