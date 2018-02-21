#include <algorithm>
#include <chrono>
#include <deque>
#include <fstream>
#include <functional>
#include <iterator>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <limits>
#include <list>
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>
#include <queue>

#include <thread>

#include <clocale>
#include <cmath>

using namespace std;


using i64 = long long;

using vc = vector<i64>;

using Pair = pair<i64, i64>;

const double eps = 0.1;

bool eq(double x, i64 y) {
	return abs(x - y) < eps;
}

using vcp = vector<Pair>;


struct SegmentTree {

	struct Node {
		Node* leftx;
		Node* rightx;
		Node* lefty;
		Node* righty;
		i64 lx;
		i64 rx;
		i64 ly;
		i64 ry;
		i64 val;

		Node(){}
		Node(i64 _lx, i64 _rx, i64 _ly, i64 _ry) {
			lx=_lx;
			rx=_rx;
			ly=_ly;
			ry=_ry;
		}

		i64 tmx() {
			return (lx + rx) / 2;
		}
		i64 tmy() {
			return (ly + ry) / 2;
		}
	};

	Node* root;

	i64 _maxx;
	i64 _minx;
	i64 _maxy;
	i64 _miny;
	i64 i;
	vector<Node> nodes;

	Node* create(i64 lx, i64 rx, i64 ly, i64 ry) {
		nodes.push_back(Node(lx,rx,ly,ry));
		return &nodes.back();
	}

	SegmentTree()
	{
		nodes = vector<Node>();
	}

	void build(vcp& Vals, i64 minx, i64 maxx, i64 miny, i64 maxy) {
		_maxx = maxx;
		_minx = minx;
		_maxy = maxy;
		_miny = miny;
		root = create(minx, maxx, miny, maxy);
	}

	i64 GetVal(double lx, double rx, double ly, double ry) {
		double _lx = lx;
		double _rx = rx;
		double _ly = ly;
		double _ry = ry;
		if (_rx < _minx) return 0;
		if (_lx > _maxx) return 0;
		if (_ry < _miny) return 0;
		if (_ly > _maxx) return 0;
		_lx = max(_lx, (double)_minx);
		_rx = min(_rx, (double)_maxx);
		_ly = max(_ly, (double)_miny);
		_ry = min(_ry, (double)_maxy);
		return Sum_x(root, _lx, _rx, _ly, _ry);
	}
	void Add(Pair& p) {
		Update_x(root, p);
	}
	void Update_x(Node* current, Pair& p) 
	{
		if (current->lx != current->rx) {
			i64 tm = (current->lx+current->rx)/2;
			if (p.first <= tm) {
				if (!current->leftx) {
					current->leftx = create(current->lx, tm, current->ly, current->ry);
				}
				Update_x(current->leftx, p);
			}
			else {
				if (!current->rightx) {
					current->rightx = create(tm + 1, current->rx, current->ly, current->ry);
				}
				Update_x(current->rightx, p);
			}
		}
		Update_y(current, p);
	}
	
	void Update_y(Node* current, Pair p) {
		if (current->ly == current->ry) {
			++current->val;
			return;
		}
		i64 tm = (current->ly + current->ry) / 2;
		if (p.second <= tm) {
			if (!current->lefty) {
				current->lefty = create(current->lx, current->rx, current->ly, tm);
			}
			Update_y(current->lefty, p);
		}
		else {
			if (!current->righty) {
				current->righty = create(current->lx, current->rx, tm + 1, current->ly);
			}
		}
		++current->val;
	}

	i64 Sum_x(Node* current,double lx, double rx, double ly, double ry) {
		if (eq(lx,current->lx) &&(eq(rx,current->rx))) 
		{
			return Sum_y(current, ly, ry);
		}
		i64 tm = (current->lx + current->rx) / 2;
		i64 tempres = 0;
		if (lx <= tm&&current->leftx) {
			tempres += Sum_x(current->leftx,lx,min(rx,(double)current->rx),ly,ry);
		}
		if (rx>= tm+1&& current->rightx) {
			tempres += Sum_x(current->rightx, max(lx, (double)current->lx), rx, ly, ry);
		}
		return tempres;
	}

	i64 Sum_y(Node* current, double ly, double ry) {
		if (eq(ly, current->ly) && eq(ry, current->ry))
			return current->val;
		i64 tm = (current->ly + current->ry) / 2;
		i64 tempres = 0;
		if (ly <= tm && current->lefty) {
			tempres += Sum_y(current->lefty, ly, min(ry, (double)current->ry));
		}
		if (ry >= tm + 1 && current->righty) {
			tempres += Sum_y(current->righty, max(ly, (double)current->ly), ry);
		}
	}

};


void main() {
	i64 maxx = numeric_limits<i64>::min();
	i64 minx = numeric_limits<i64>::max();
	i64 maxy = numeric_limits<i64>::min();
	i64 miny = numeric_limits<i64>::max();
	size_t r;
	cin >> r;
	vcp Pairs = vcp();
	Pairs.reserve(r);
	for (size_t i = 0; i < r; ++i)
	{
		i64 x, y;
		cin >> x >> y;
		i64 nx, ny;
		nx = x + y;
		ny = y - x;
		maxx = max(maxx, nx);
		minx = min(minx, nx);
		miny = min(miny, ny);
		maxy = max(maxy, ny);
		Pairs.push_back(Pair(nx, ny));
	}
	SegmentTree tree = SegmentTree();
	tree.build(Pairs, minx, maxx, miny, maxy);
	for (size_t i = 0; i < r; i++)
	{
		tree.Add(Pairs[i]);
	}
	size_t q;
	cin >> q;
	double root2 = sqrt(2);
	vc answers = vc();
	answers.reserve(q);
	for (size_t i = 0; i < q; ++i)
	{
		i64 x, y, d;
		cin >> x >> y >> d;
		i64 nx, ny;
		nx = x + y;
		ny = y - x;
		double nd = d*root2;
		answers.push_back(tree.GetVal(nx - nd, nx + nd, ny - nd, ny + nd));
	}
	for (auto a : answers)
		cout << a << " ";

}