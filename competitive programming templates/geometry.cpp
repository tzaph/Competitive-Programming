#include <bits/stdc++.h>
using namespace std;

#define ld long double
#define ll long long
const ld eps = 1e-9;

inline ld sign(ld x){return (x>0)-(x<0);}
inline ll sign(ll x){return (x>0)-(x<0);}
inline int sign(int x){return (x>0)-(x<0);}
struct pt{
	ld x, y;
	pt(){}
	pt(ld _x, ld _y):x(_x), y(_y){}
	bool operator<(pt p){return tie(x, y)<tie(p.x, p.y);}
	bool operator==(pt p){return tie(x, y)==tie(p.x, p.y);}
	pt operator+(pt p){return {x+p.x, y+p.y};}
	pt operator-(pt p){return {x-p.x, y-p.y};}
	pt operator*(ld d){return {x*d, y*d};}
	pt operator/(ld d){return {x/d, y/d};}
	ld dot(pt p){return x*p.x+y*p.y;}
	ld det(pt p){return x*p.y-y*p.x;}
	ld cross(pt p, pt q){return (p-*this).det(q-*this);}
	ld dist(){return sqrtl(x*x+y*y);}
	pt rot90(){return pt(-y, x);}
	pt unit(){return *this/dist();}
	ld angle(){return atan2(y, x);}
	pt rot(ld an){return {x*cos(an)-y*sin(an), x*sin(an)+y*cos(an)};}
	void read(){cin>>x>>y;}
	void readInt(){int a,b;cin>>a>>b;x=a,y=b;}
	void write(){cout<<"("<<x<<","<<y<<")"<<endl;}
};
 
struct seg{
	pt fi, sc;
	seg(){}
	seg(pt _fi, pt _sc):fi(_fi), sc(_sc){}
	ld dist(pt C){
		if(fi==sc) return (C-fi).dist();
		ld d=pow((sc-fi).dist(), 2);
		ld t=min(d, max((ld)0.0, (C-fi).dot(sc-fi)));
		return ((C-fi)*d-(sc-fi)*t).dist()/d;
	}
	ld len(){return (fi-sc).dist();}
	bool on_seg(pt C){
		return abs(C.cross(fi, sc))<eps && (fi-C).dot(sc-C)<=eps;
	}
	vector<pt>intersect(seg rhs){
		ld oa=rhs.fi.cross(rhs.sc, fi);
		ld ob=rhs.fi.cross(rhs.sc, sc);
		ld oc=fi.cross(sc, rhs.fi);
		ld od=fi.cross(sc, rhs.sc);
		if(sign(oa)*sign(ob)<0 && sign(oc)*sign(od)<0)
			return {(fi*ob-sc*oa)/(ob-oa)};
		vector<pt>ans;
		if(rhs.on_seg(fi)) ans.push_back(fi);
		if(rhs.on_seg(sc)) ans.push_back(sc);
		if(on_seg(rhs.fi)) ans.push_back(rhs.fi);
		if(on_seg(rhs.sc)) ans.push_back(rhs.sc);
		return ans;
	}
};
 
struct line{
	ld a, b, c; //line a*x+b*y=c
	line(pt p1, pt p2){
		assert(!(p1==p2));
		a=p2.y-p1.y;
		b=p1.x-p2.x;
		c=a*p1.x+b*p1.y;
	}
	line(seg x){
		a=x.sc.y-x.fi.y;
		b=x.fi.x-x.sc.x;
		c=a*x.fi.x+b*x.fi.y;
	}
	line(){}
	line(ld _a, ld _b, ld _c):a(_a), b(_b), c(_c){}
	ld dist(pt p){
		return fabs(a*p.x+b*p.y-c)/sqrtl(a*a+b*b);
	}
	pair<int, pt>intersect(line rhs){
		ld dett=a*rhs.b-b*rhs.a;
		if(fabs(dett)<=eps){
			ld det2=c*rhs.a-a*rhs.c;
			if(fabs(det2)<=eps)
				return {-1, pt()}; //infinte
			return {0, pt()}; //no sol
		}
		return {1, pt((c*rhs.b-rhs.c*b)/dett, (a*rhs.c-c*rhs.a)/dett)};
	}
};
 
pt reflect(pt A, line L){
	line perpendicular(-L.b, L.a, -L.b*A.x+L.a*A.y);
	pt insect=perpendicular.intersect(L).second;
	return insect*(ld)2.0-A;
}

int ori(pt a0, pt a1, pt a2){
	ld get = (a1.y - a0.y) * 1ll * (a2.x - a1.x) - (a1.x - a0.x) * 1ll * (a2.y - a1.y);
	if(fabs(get) <= eps) return 0;
	else if(get <= eps) return -1; // ccw
	else return 1; // cw
}

void convex_hull(vector<pt> &v){
	if(v.size() == 1) return;

	sort(v.begin(), v.end());
	vector<pt> up, dn;
	pt p1 = v[0], p2 = v.back();
	up.push_back(p1); dn.push_back(p1);
	for(int i = 1; i < v.size(); i ++){
		if(i == v.size() - 1 || ori(p1, v[i], p2) == 1){
			while(up.size() >= 2 && ori(up[up.size() - 2], up.back(), v[i]) != 1)
				up.pop_back();
			up.push_back(v[i]);
		}
		if(i == v.size() - 1 || ori(p1, v[i], p2) == -1){
			while(dn.size() >= 2 && ori(dn[dn.size() - 2], dn.back(), v[i]) != -1)
				dn.pop_back();
			dn.push_back(v[i]);
		}
	}

	v.clear();
	for(int i = 0; i < up.size(); i ++)
		v.push_back(up[i]);
	for(int i = dn.size() - 2; i > 0; i --)
		v.push_back(dn[i]);
}

ld distpt(pt a, pt b){
	return sqrtl(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

ld dist_pt_to_seg(pt a, seg c){
	ld cx = c.sc.x - c.fi.x, cy = c.sc.y -c.fi.y;
	ld lf = 0.0, rg = 1.0;
	for(int tp = 0; tp < 100; tp ++){
		ld md1 = (lf + lf + rg) / 3.0, md2 = (lf + rg + rg) / 3.0;
		pt m1; m1.x = c.fi.x + cx * md1; m1.y = c.fi.y + cy * md1;
		pt m2; m2.x = c.fi.x + cx * md2; m2.y = c.fi.y + cy * md2;
		if(distpt(a, m1) < distpt(a, m2)) rg = md2;
		else lf = md1;
	}

	ld md = (lf + rg) / 2.0;
	pt m; m.x = c.fi.x + cx * md; m.y = c.fi.y + cy * md;
	return distpt(a, m);
}

ld area(vector<pt> v){
	ld ans = 0.0;
	for(int i = 0; i < v.size(); i ++)
		ans += v[i].x * v[(i + 1) % v.size()].y;
	for(int i = 0; i < v.size(); i ++)
		ans -= v[i].y * v[(i + 1) % v.size()].x;
	ans /= 2.0;
	return fabs(ans);
}