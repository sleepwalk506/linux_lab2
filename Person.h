//#ifndef INFECTION_H
//#define INFECTION_H
#pragma once
#include<graphics.h>
#include<time.h>
#include<iostream>
#include<random>
#define random(x) rand()%(x)
using namespace std;
void seeds();
enum class InfType
{
    Sus, Lur, Inf, Cur
};
class Person{//person基类
public:
    int coor_x;
    int coor_y;
    bool if_alive = true;
    bool if_cured = false;
    bool can_move = true;
    COLORREF c;
    InfType inftype = InfType::Sus;
public:
    Person() { }
    Person(int x, int y) {
        //seeds();
        this->coor_x = x;
        this->coor_y = y;
    }
   
};
class Susceptible : public Person {//易感者类
    //未患病，与感染者I接触有几率患病
public:
    double infection_rate = 0.3;//初始患病几率
    COLORREF c = WHITE;
public:
    Susceptible(int coor_x,int coor_y):Person(coor_x,coor_y) {}
};
class Lurker : public Person {//潜伏者类，无传染能力
public:
    int lurk_days = 14;//已经潜伏了days
    double cure_rate = 0.5;
    COLORREF c = YELLOW;
public:
    InfType different(Person* p) {//潜伏者分化
        //default_random_engine e(time(0));//引擎生成随机序列，设置种子
        //uniform_real_distribution<double> u(0, 1.0);
        //double rate = 1.0 * (rand() / (RAND_MAX + 1.0));
        std::random_device dev;
        default_random_engine e(dev());
        uniform_real_distribution<double> dd(0, 1.0);
        double rate = dd(e);
        if (lurk_days >= 14) {
            if (rate > cure_rate) {
                return InfType::Inf;
            }
        }
        return InfType::Cur;
    }
    Lurker(int coor_x, int coor_y) :Person(coor_x, coor_y) {}
};
class Infector : public Person {
public:
    double death_rate = 0.1;//死亡率
    double E_rate = 0.5;//变E几率
    double I_rate = 0.2;//跳过E直接变成I的几率
    double N_rate = 0.3;//不被感染的几率
    double C_rate = 0.4;//被治愈的概率
    COLORREF c = RED;
public:
    InfType Infect(Person* p){
        //double rate = 1.0 * (rand() / (RAND_MAX + 1.0));
        std::random_device dev;
        default_random_engine e(dev());
        uniform_real_distribution<double> dd(0, 1.0);
        double rate = dd(e);
        //cout << "infect" << rate << endl;
        if (rate > N_rate) {//被感染
            if (rate <= N_rate + E_rate) {//被感染成E
                return InfType::Lur;
            }
            else if (rate > N_rate + E_rate && rate <= 1) {//被感染成I
                return InfType::Inf;
            }
        }
        return InfType::Sus;
    }
    Infector(int coor_x, int coor_y) :Person(coor_x, coor_y) {}
    void if_dead() {
        //default_random_engine e(time(0));//引擎生成随机序列，设置种子
        //uniform_real_distribution<double> u(0, 1.0);
        //double rate = u(e);
        //double rate = 1.0 * (rand() / (RAND_MAX + 1.0));
        std::random_device dev;
        default_random_engine e(dev());
        uniform_real_distribution<double> dd(0, 1.0);
        double rate = dd(e);
        //cout << "dead" << rate << endl;
        if (rate <= death_rate) {
            this->if_alive = false;
        }
    }
    void if_cure() {
        std::random_device dev;
        default_random_engine e(dev());
        uniform_real_distribution<double> dd(0, 1.0);
        double rate = dd(e);
        if (rate <= C_rate) {
            this->if_cured = true;
        }
    }
};
class Cured : public Person {
public:
    int immune_days = 30;//免疫期限
    Cured(int coor_x, int coor_y) :Person(coor_x, coor_y) {}
};
//#endif