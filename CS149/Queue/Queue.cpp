#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int busnum, vannum, buslow, bushigh, vanlow, vanhigh;
	int totalTime, timer;
	int ship, shiptotal;
	double buswait, vanwait;
	linkQueue <int> busQueue, vanQueue;
	cout << "please type in the time to simulate(min):";
	cin >> totalTime;
	cout << "bus come time(low high):";
	cin >> buslow >> bushigh;
	cout << "van come time(low high):";
	cin >> vanlow >> vanhigh;

	srand(time(NULL));

	timer = 0;
	busnum = 0;
	while(true)
	{
		timer += rand() % (bushigh - buslow + 1) + buslow;
		if (timer > totalTime) break;
		busQueue.enQueue(timer);
	}

	timer = 0;
	vannum = 0;
	while (true)
	{
		timer += rand() % (vanhigh - vanlow + 1) + vanlow;
		if (timer > totalTime) break;
		vanQueue.enQueue(timer);
	}

	buswait = vanwait = 0;
	busnum = vannum = 0;
	shiptotal = 0;
	for (timer = 10; timer <= totalTime; timer += 10)
	{
		for (ship = 0; ship < 8 && !busQueue.isEmpty() && busQueue.getHead() <= timer; ++ship)
		{
			buswait = timer + buswait - busQueue.deQueue();
			++busnum;
		}
		for (;ship < 10 && !vanQueue.isEmpty() && vanQueue.getHead() <= timer; ++ship)
		{
			vanwait = timer + buswait - vanQueue.deQueue();
			++vannum;
		}
	}
	for (; ship < 10 && !busQueue.isEmpty() && busQueue.getHead() <= timer; ++ship)
	{
		buswait = timer + buswait - busQueue.deQueue();
		++busnum;
	}
	shiptotal = ship + shiptotal;
	cout << "goes" << shiptotal << "cars,and average every has" << shiptotal / ((timer - 10) / 10) << "cars" << endl;
	cout << "average time of bus waiting is:" << buswait / busnum << endl;
	cout << "average time of van waiting is:" << vanwait / vannum << endl;
	cout << "waiting bus:" << busnum << endl;
	cout << "waiting van:" << vannum << endl;
	return 0;
}
