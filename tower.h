#ifndef tower_H;
#define tower_H;
#include"geth.h"
#include<iostream>
using namespace std;
class tower{ 
	public:
		double Maxblood,nowblood,attack;	//最大血量,当前血量,攻击能力 
		int speed,camp,RNG;			//阵营,RNG攻击范围，range建筑占地范围
		pos p;
		bullet b[20];
		tower(int blood,int at,int ca,int x,int y):p(x,y,2),camp(ca),Maxblooc(blood),nowblood(blood),RNG(3),attack(at),destroyed(false){}
		double hit(kar **B);				//打击英雄 
		double attacked();					//被打击 
		void shoot();						//开火 
		bool destroyed;						//沦陷与否 
		void ifdestr();						//通过血量判断爆没爆	
		void runtower();					//塔总运行 
};

double tower::hit()
{
	
}

double tower::attacked()
{
	
}
#endif
