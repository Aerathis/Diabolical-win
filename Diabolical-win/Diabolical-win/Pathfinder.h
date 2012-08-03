#ifndef _PATHFINDER_H
#define _PATHFINDER_H

#include <queue>
#include <string>
#include <math.h>

namespace pathfinder
{
	const int dir = 8;
	class node
	{
		int xPos;
		int yPos;

		int level;

		int priority;

	public:
		node(int xp, int yp, int d, int p)
		{
			xPos = xp; 
			yPos = yp; 
			level = d; 
			priority = p;
		}

		int getxPos() const 
		{
			return xPos;
		}

		int getyPos() const
		{
			return yPos;
		}

		int getLevel() const
		{
			return level;
		}

		int getPriority() const
		{
			return priority;
		}

		void updatePriority(const int &xDest, const int &yDest) 
		{
			priority = level + estimate(xDest, yDest)*10;
		}

		void nextLevel(const int &i)
		{
			level += (dir == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
		}

		const int& estimate(const int &xDest, const int &yDest) const
		{
			static int xd, yd, d;
			xd  = xDest - xPos;
			yd = yDest - yPos;

			d = static_cast<int>(sqrt(float(xd*xd+yd*yd)));

			return d;
		}
	};

	bool operator<(const node &a, const node &b)
	{
		return a.getPriority() > b.getPriority();
	}

	std::string pathFind(const int &xStart, const int &yStart, const int &xFinish, const int &yFinish)
	{
		static std::priority_queue<node> pq[2];
		static int pqi;
		static node* n0;
		static node* m0;
		static int i,j,x,y,xdx,ydy;
		static char c;
		pqi = 0;

		static int closed_nodes_map[20][20];
		static int open_nodes_map[20][20];
		static int dir_map[20][20];

		static int dx[dir] = {1,1,0,-1,-1,-1,0,1};
		static int dy[dir] = {0,1,1,1,0,-1,-1,-1};

		for (y=0;y<20;y++)
		{
			for (x=0;x<20;x++)
			{
				closed_nodes_map[x][y] = 0;
				open_nodes_map[x][y] = 0;
			}
		}

		n0 = new node(xStart,yStart,0,0);
		n0->updatePriority(xFinish,yFinish);
		pq[pqi].push(*n0);
		open_nodes_map[x][y] = n0->getPriority();

		while(!pq[pqi].empty())
		{
			n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),pq[pqi].top().getLevel(),pq[pqi].top().getPriority());

			x = n0->getxPos();
			y = n0->getyPos();

			pq[pqi].pop();
			open_nodes_map[x][y] = 0;
			closed_nodes_map[x][y] = 1;

			if (x == xFinish && y == yFinish)
			{
				string path = "";
				while (
			}
		}
	}
}

#endif //PATHFINDER_H