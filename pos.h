#ifndef pos_H
#define pos_H
#include<iostream>
using namespace std;
#include<math.h> 
class pos
{
	public:
		int ix,iy;						//ix,iy,,x,y坐标,
		int range;
		pos(int x=0,int y=0,int r=0):ix(x),iy(y),range(r){}	//初始化位置和范围 
		double operator -(pos &a)		//位置差 
		{
			int x=(ix-a.ix)*(ix-a.ix),y=(iy-a.iy)*(iy-a.iy);
			return sqrt(x+y);	//返回勾股定理 
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
