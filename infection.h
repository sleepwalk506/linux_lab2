//#ifndef INFECTION_H
//#define INFECTION_H
#pragma once
#include"Person.h"
#include<cstdlib>
#include<future>
#include<vector>
#include<thread>
#define MAX_PEOPLE 10000;
#define MAX_INFECTOR 3000;
using namespace std;
void load_person();
void newInfection(Infector* infector);
void zero_Infection();
//#endif