#ifndef tower_H;
#define tower_H;
#include"geth.h"
#include<iostream>
using namespace std;
class tower{ 
	public:
		double Maxblood,nowblood,attack;	//���Ѫ��,��ǰѪ��,�������� 
		int speed,camp,RNG;			//��Ӫ,RNG������Χ��range����ռ�ط�Χ
		pos p;
		bullet b[20];
		tower(int blood,int at,int ca,int x,int y):p(x,y,2),camp(ca),Maxblooc(blood),nowblood(blood),RNG(3),attack(at),destroyed(false){}
		double hit(kar **B);				//���Ӣ�� 
		double attacked();					//����� 
		void shoot();						//���� 
		bool destroyed;						//������� 
		void ifdestr();						//ͨ��Ѫ���жϱ�û��	
		void runtower();					//�������� 
};

double tower::hit()
{
	
}

double tower::attacked()
{
	
}
#endif
