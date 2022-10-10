//#pragma once

#include"Person.h"
#include"infection.h"
//#include"Person.cpp"
//#include"infection.cpp"
int main(){
	//新建一个图形界面
	initgraph(400, 400, EX_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	
	//std::random_device dev;
	//default_random_engine e(dev());
	//uniform_real_distribution<double> dd(0, 1.0);
	//srand((unsigned)time(NULL));
	//seeds();
	load_person();
	zero_Infection();
	getchar();
	getchar();
	return 0;
}