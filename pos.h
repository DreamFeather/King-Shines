#ifndef pos_H
#define pos_H
#include<iostream>
using namespace std;
#include<math.h> 
class pos
{
	public:
		int ix,iy;						//ix,iy,,x,y����,
		int range;
		pos(int x=0,int y=0,int r=0):ix(x),iy(y),range(r){}	//��ʼ��λ�úͷ�Χ 
		double operator -(pos &a)		//λ�ò� 
		{
			int x=(ix-a.ix)*(ix-a.ix),y=(iy-a.iy)*(iy-a.iy);
			return sqrt(x+y);	//���ع��ɶ��� 
		}
		void operator =(pos &a)
		{
			ix=a.ix;iy=a.iy;
		}
		pos(pos &a)
		{
			ix=a.ix;iy=a.iy;
		}
		bool operator ==(pos &a)
		{
			return (a.ix==ix&&a.iy==iy);
		}
};

#endif
