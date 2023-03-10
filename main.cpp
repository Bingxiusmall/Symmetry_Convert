#include<bits/stdc++.h>
using namespace std;
/*
input:
1 4 0 0 1 0 4 0 1 0 0 4
(1 4 0 0->x^4,1 0 4 0->y^4,1 0 0 4->z^4)
output:
p^4-4p^2*q+4pr+2q^2
*/
struct sym{
	int l,x,y,z;
	inline bool operator<(const sym &other) const{return x!=other.x?x>other.x:y!=other.y?y>other.y:z>other.z;}
	inline bool operator==(const sym &other) const{return x==other.x&&y==other.y&&z==other.z;}
	inline sym operator*(const sym &other) const{return (sym){l*other.l,x+other.x,y+other.y,z+other.z};}
	inline sym operator+() const{return (sym){1,x,y,z};}
}x={1,1,0,0},y={1,0,1,0},z={1,0,0,1};
struct symhsh{inline std::size_t operator()(sym other) const{return hash<int>()(other.x)^hash<int>()(other.y^0x8a0f9bc)^hash<int>()(other.z^0x7928ba8)^hash<int>()(other.l^0xa809fb1);}};
struct expr{
	deque<sym> q;
	inline void sort(){std::sort(q.begin(),q.end());}
	inline expr operator-(const expr &other){
		register expr w={},a(*this),b(other);
		while(!a.q.empty()&&!b.q.empty()){
			if(a.q.front()==b.q.front()){if(a.q.front().l!=b.q.front().l) w.q.push_back((sym){a.q.front().l-b.q.front().l,a.q.front().x,a.q.front().y,a.q.front().z});a.q.pop_front(),b.q.pop_front();}
			else if(a.q.front()<b.q.front()) w.q.push_back(a.q.front()),a.q.pop_front();
			else w.q.push_back((sym){-b.q.front().l,b.q.front().x,b.q.front().y,b.q.front().z}),b.q.pop_front();
		}
		while(!a.q.empty()) w.q.push_back(a.q.front()),a.q.pop_front();
		while(!b.q.empty()) w.q.push_back((sym){-b.q.front().l,b.q.front().x,b.q.front().y,b.q.front().z}),b.q.pop_front();
		return w.sort(),w;
	}
	inline expr& operator-=(const expr &other){return *this=*this-other;}
	inline expr operator*(const expr &other){
		register expr w={};
		register unordered_map<sym,int,symhsh> k;
		for(sym i:q) for(sym j:other.q) k[+(i*j)]+=i.l*j.l;
		for(auto i:k) if(i.second) w.q.push_back((sym){i.second,i.first.x,i.first.y,i.first.z});
		return w.sort(),w;
	}
	inline expr operator*(const int &other){
		if(!other) return (expr){{}};
		register expr w={};
		for(sym i:q) w.q.push_back((sym){other*i.l,i.x,i.y,i.z});
		return w;
	}
	inline expr pow(int n){return !n?(expr){{(sym){1}}}:n&1?(*this**this).pow(n>>1)**this:(*this**this).pow(n>>1);}
}p={{x,y,z}},q={{x*y,x*z,y*z}},r={{x*y*z}},t,ans;
int a,b,c,g;
inline istream& operator>>(istream& inf,expr &q){
	register int l,x,y,z;
	q.q.clear();
	while(inf>>l>>x>>y>>z) q.q.push_back((sym){l,x,y,z});
	return inf;
}
inline ostream& operator<<(ostream& ouf,expr q){
	bool flag=0;
	if(q.q.empty()) return ouf<<'0';
	for(sym i:q.q) flag&&i.l>0&&(ouf<<'+',0),i.l==1?(i.x||i.y||i.z?ouf:ouf<<'1'):i.l==-1?(i.x||i.y||i.z?ouf<<'-':ouf<<"-1"):ouf<<i.l,i.x&&(ouf<<'p',i.x!=1&&(ouf<<"^"<<i.x)),i.y&&(i.x<2?ouf:ouf<<'*',ouf<<'q',i.y!=1&&(ouf<<"^"<<i.y)),i.z&&(i.y==1||(!i.y&&i.x<2)?ouf:ouf<<'*',ouf<<'r',i.z!=1&&(ouf<<"^"<<i.z)),flag=1;
	return ouf;
}
int main(){
	cin>>t,t.sort();
	while(!t.q.empty()) g=t.q.front().l,c=t.q.front().z,b=t.q.front().y-c,a=t.q.front().x-b-c,t-=r.pow(c)*q.pow(b)*p.pow(a)*g,ans.q.push_back((sym){g,a,b,c});
	return ans.sort(),cout<<ans*(expr){{(sym){1,0,0,0}}},system("pause >nul"),0;
}
