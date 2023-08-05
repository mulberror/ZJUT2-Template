struct Bitset{
	using ull = unsigned long long;
	vector<ull> b;
	int n;
	Bitset(int x=0){
		n = x;
		b.resize((n+63)/64,0);
	}
	
	int get(int x){
		return (b[x>>6]>>(x&63))&1;
	}
	
	void set(int x,int y){
		b[x>>6] |= 1ULL<<(x&63);
		if(!y)b[x>>6] ^= 1ULL<<(x&63);
	}
	
	Bitset &operator&=(const Bitset &another){
		rep(i,min((int)b.size(),(int)another.b.size())){
			b[i] &= another.b[i];
		}
		return (*this);
	}
	
	Bitset operator&(const Bitset &another)const{
		return (Bitset(*this)&=another);
	}
	
	Bitset &operator|=(const Bitset &another){
		rep(i,min((int)b.size(),(int)another.b.size())){
			b[i] |= another.b[i];
		}
		return (*this);
	}
	
	Bitset operator|(const Bitset &another)const{
		return (Bitset(*this)|=another);
	}
	
	Bitset &operator^=(const Bitset &another){
		rep(i,min((int)b.size(),(int)another.b.size())){
			b[i] ^= another.b[i];
		}
		return (*this);
	}
	
	Bitset operator^(const Bitset &another)const{
		return (Bitset(*this)^=another);
	}
	
	Bitset &operator>>=(int x){
		if(x&63){
			rep(i,b.size()-1){
				b[i] >>= (x&63);
				b[i] ^= (b[i+1]<<(64-(x&63)));
			}
			b.back() >>= (x&63);
		}
		
		x>>=6;
		rep(i,b.size()){
			if(i+x<b.size())b[i] = b[i+x];
			else b[i]=0;
		}
		return (*this);
	}
	
	Bitset operator>>(int x)const{
		return (Bitset(*this)>>=x);
	}
	
	Bitset &operator<<=(int x){
		if(x&63){
			for(int i=b.size()-1;i>=1;i--){
				b[i] <<= (x&63);
				b[i] ^= b[i-1]>>(64-(x&63));
			}
			b[0] <<= x&63;
		}
		
		x>>=6;
		for(int i=b.size()-1;i>=0;i--){
			if(i-x>=0)b[i] = b[i-x];
			else b[i] = 0;
		}
		return (*this);
	}
	
	Bitset operator<<(int x)const{
		return (Bitset(*this)<<=x);
	}
	
};
