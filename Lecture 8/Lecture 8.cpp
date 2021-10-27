/* 1. Разработать программу, которая включает два потока один поток моделирует полет шарика, второй отображает
в текстовом виде положение шарика на экране с заданной частотой.

Информация о траектории полета (координаты и метка времени) должны заносится в std::vector

Масса, начальная скорость и положение шарика должны задаваться в качестве параметров командной строки.

Вариант 2

Моделируем полет брошенного с  со скоростью vx (горизонтальная составляющая) и vy (вертикальная составляющая) шарика массой m.
При соударении с землей шарик теряет определенный процент кинетической энергии (задается константой)  и отскакивает (угол падения равен углу отражения).*/
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <cmath>
#include <iomanip>
#include <sstream>

using namespace std;

const double gravity = -9.80665;
const double deltaTime = 0.01;
const int c_delay = 40;
const int p_delay = 60;
const double lossPercent = 90;

struct Location 
{
	double time;
	double y;
	double x;
};


vector <Location> locations(0);
mutex locker;

double collision(double highest,vector<Location>& vect,double timeOfCollision) //обработка столкновения, возвращающая значение проекции скорости на ось OY после столкновения
{
	double t = timeOfCollision;
	double ty = 0;
	double tx = vect.back().x;
	Location inputer({t,ty,tx});
	vect.push_back(inputer);
	double vy = sqrt((100 - lossPercent) / 100 * (vx * vx + prev_vy * prev_vy) - vx * vx);
	return vy;
}


void print_vec()
{
	Location pr;
	
	do
	{
		this_thread::sleep_for(chrono::milliseconds(c_delay));
		locker.lock();
		pr = locations.back();
		locker.unlock();
		cout << fixed << setprecision(6);
		cout << "Time = " << pr.time << "; ";
		cout << "xPos = " << pr.x << "; ";
		cout << "yPos = " << pr.y << endl;
	} while (pr.y > 0.001);
	
}

void emulation(const double mass, double tvx, double tvy, double x, double y)
{
	Location st({0,0,0});
	locations.push_back(st);
	locations.back().time = 0;
	locations.back().x = x;
	locations.back().y = y;
	double vx = tvx;
	double vy = tvy;
	double timeOfCollision = sqrt(2.0 * y / (-gravity));
	double highest = y;
	while (highest > 0.001)
	{
		while (locations.back().time < timeOfCollision - deltaTime)
		{
			double h = locations.back().y;
			h += vy * deltaTime + gravity * deltaTime * deltaTime / 2;
			vy += gravity * deltaTime;
			double t = locations.back().time + deltaTime;
			double nextx = locations.back().x + vx * deltaTime;

			locker.lock();
			locations.push_back({t, h, nextx});
			locker.unlock();
			this_thread::sleep_for(chrono::milliseconds(p_delay));
		}
		cout << endl << endl;
		vy = collision(highest, locations, timeOfCollision);
		double tmax = vy / (-gravity); //время подъема после отскока
		highest = vy * tmax + gravity * tmax * tmax / 2; //наибольшая высота подъема после отскока
		cout << "NEXT HIGHEST POS = " << highest << endl;
		timeOfCollision += 2 * tmax;
	}
}



int main(int argc, char* argv[]) 
{
	double mas, vx, vy, x, y;
	cout << argc << endl;
	if (argc != 6)
	{
		cout << "Troubles with arguments" << endl;
		return -1;
	}
	else {
		stringstream convert{ argv[1] };
		if (!(convert >> mas))
		{
			cout << "Mass convertation error!" << endl;
			return -1;
		}

		convert.str(argv[2]);
		if (!(convert >> vx))
		{
			cout << "xSpeed convertation error!" << endl;
			return -1;
		}

		convert.str(argv[3]);
		if (!(convert >> vy))
		{
			cout << "ySpeed convertation error!" << endl;
			return -1;
		}

		convert.str(argv[4]);
		if (!(convert >> x))
		{
			cout << "xPos convertation error!" << endl;
			return -1;
		}

		convert.str(argv[5]);
		if (!(convert >> y))
		{
			cout << "yPos convertation error!" << endl;
			return -1;
		}
	}
	thread thread_emul(emulation,mas,vx,vy,x,y);
	thread thread_print(print_vec);

	thread_emul.join();
	thread_print.join();
}
