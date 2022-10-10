#include"infection.h"
vector<vector<Person*> > whole_p;
//vector<Person*> temp_p1;
int infected_p;
mutex mtx;//变量锁
int No_0_infected;
void load_person() {//装载一个100x100的person二维数组
	for (int i = 0; i < 100; i++) {
		vector<Person*> temp_p1;
		for (int j = 0; j < 100; j++) {
			Person* newPerson = new Person(i, j);
			newPerson->inftype = InfType::Sus;
			temp_p1.push_back(newPerson);
		}
		whole_p.push_back(temp_p1);
	}
}
void newLurker(Lurker* lurker) {
	Sleep(500);
	setfillcolor(lurker->c);
	solidrectangle(lurker->coor_y * 4, lurker->coor_x * 4, lurker->coor_y * 4 + 3, lurker->coor_x * 4 + 3);
	int coor_x, coor_y;
	coor_x = lurker->coor_x;
	coor_y = lurker->coor_y;
	whole_p[coor_x][coor_y]->inftype = InfType::Lur;
	lurker->lurk_days--;
	if (lurker->lurk_days <= 0) {
		lurker->inftype = InfType::Inf;
		whole_p[coor_x][coor_y]->inftype = InfType::Inf;
		Infector* newInfector = new Infector(coor_x, coor_y);
		thread t(newInfection, newInfector);
		t.detach();
		//async(launch::async, newInfection, newInfector);
	}
	else
	{
		thread t(newLurker, lurker);
		t.detach();
		//async(launch::async, newLurker, lurker);
	}
}
void newInfection(Infector* infector) {
	//mtx.lock();
	infected_p++;
	Sleep(500);
	setfillcolor(infector->c);
	solidrectangle(infector->coor_y * 4, infector->coor_x * 4, infector->coor_y * 4 + 3, infector->coor_x * 4 + 3);
	int coor_x, coor_y;
	coor_x = infector->coor_x;
	coor_y = infector->coor_y;
	whole_p[coor_x][coor_y]->inftype = InfType::Inf;
	infector->can_move = false;
	if (coor_x > 1 && coor_y < 99 && coor_x < 99 && coor_y > 1) {
		
		if (whole_p[coor_x + 1][coor_y]->inftype == InfType::Sus && whole_p[coor_x + 1][coor_y]->if_alive == true) {
			//cout << "down" << endl;
			InfType p = infector->Infect(whole_p[coor_x + 1][coor_y]);
			if (p == InfType::Lur) {
				Lurker* newlurker = new Lurker(coor_x + 1, coor_y);
				thread t(newLurker, newlurker);
				t.detach();
				//async(launch::async, newLurker, newlurker);
			}
			if (p == InfType::Inf) {
				Infector* newInfector = new Infector(coor_x + 1, coor_y);
				thread t(newInfection, newInfector);
				t.detach();
				//async(launch::async, newInfection, newInfector);
			}
		}
		if (whole_p[coor_x][coor_y + 1]->inftype == InfType::Sus && whole_p[coor_x][coor_y + 1]->if_alive == true) {
			//cout << "right" << endl;
			InfType p = infector->Infect(whole_p[coor_x][coor_y + 1]);
			if (p == InfType::Lur) {
				Lurker* newlurker = new Lurker(coor_x, coor_y + 1);
				thread t(newLurker, newlurker);
				t.detach();
				//async(launch::async, newLurker, newlurker);
			}
			if (p == InfType::Inf) {
				Infector* newInfector = new Infector(coor_x, coor_y + 1);
				thread t(newInfection, newInfector);
				t.detach();
				//async(launch::async, newInfection, newInfector);
			}
		}
		if (whole_p[coor_x][coor_y - 1]->inftype == InfType::Sus && whole_p[coor_x][coor_y - 1]->if_alive == true) {
			//cout << "left" << endl;
			InfType p = infector->Infect(whole_p[coor_x][coor_y - 1]);
			if (p == InfType::Lur) {
				Lurker* newlurker = new Lurker(coor_x, coor_y - 1);
				thread t(newLurker, newlurker);
				t.detach();
				//async(launch::async, newLurker, newlurker);
			}
			if (p == InfType::Inf) {
				Infector* newInfector = new Infector(coor_x, coor_y - 1);
				thread t(newInfection, newInfector);
				t.detach();
				//async(launch::async, newInfection, newInfector);
			}
		}
		if (whole_p[coor_x - 1][coor_y]->inftype == InfType::Sus && whole_p[coor_x - 1][coor_y]->if_alive == true) {
			//cout << "up" << endl;
			InfType p = infector->Infect(whole_p[coor_x - 1][coor_y]);
			if (p == InfType::Lur) {
				Lurker* newlurker = new Lurker(coor_x - 1, coor_y);
				thread t(newLurker, newlurker);
				t.detach();
				//async(launch::async, newLurker, newlurker);
			}
			if (p == InfType::Inf) {
				Infector* newInfector = new Infector(coor_x - 1, coor_y);
				thread t(newInfection, newInfector);
				t.detach();
				//async(launch::async, newInfection, newInfector);
			}
		}
	}
	
	infector->if_dead();
	if (infector->if_alive == false) {
		setfillcolor(BLACK);
		solidrectangle(infector->coor_y * 4, infector->coor_x * 4, infector->coor_y * 4 + 3, infector->coor_x * 4 + 3);
	}
	infector->if_cure();
	if (infector->if_cured == true) {
		setfillcolor(GREEN);
		solidrectangle(infector->coor_y * 4, infector->coor_x * 4, infector->coor_y * 4 + 3, infector->coor_x * 4 + 3);
	}
	//mtx.unlock();
}
void zero_Infection() {
	int coor_x, coor_y;
	cout << "input number of No. 0 infected persons:";
	cin >> No_0_infected;
	for (int i = 0; i < No_0_infected; i++) {
		cout << "input the coordinate:";
		cin >> coor_x >> coor_y;
		Infector* zero_infector = new Infector(coor_x,coor_y);
		thread t(newInfection, zero_infector);
		t.detach();
		//async(launch::async, newInfection, zero_infector);
	}
}