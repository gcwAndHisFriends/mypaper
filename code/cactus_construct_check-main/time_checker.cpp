#pragma GCC optmize(0)
#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<cmath>
#include<unordered_map>
#include<queue>
#include<stack>
#include<random>
#include<chrono>
using namespace std;
using namespace std::chrono;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
int randed_int(int a, int b) {
	return rnd()%(b-a+1)+a;
}

struct node_val_int{
	int u,v,w;//出发点 结束点 边权
};

bool Suitable_for_random(int m,int n){//判断是否适合用随机构造法
	return log(n+1)<1+log((n-m)+1);
}

double work(int m,int l,int r,int type){
    auto start = chrono::system_clock::now();
    vector<int>array;
    if(type){//随机
        unordered_map<int, int>mp;
        for (int i = 1; i <= m; i++) {
            int u;
            do{
                u = randed_int(l, r);
            }while(mp[u]);
            mp[u] = 1;
            array.push_back(u);
        }
    }else{
        for (int i = l; i <= r; i++) {
            array.push_back(i);
        }
        random_shuffle(array.begin(), array.end());
        array.erase(array.begin() + m, array.end());//把m之后的全删
    }
    auto end = chrono::system_clock::now();
    auto duration = duration_cast<chrono::microseconds>(end - start);
    return double(duration.count()) * milliseconds::period::num / milliseconds::period::den;
}

signed main(){
    //[1,120000]
    vector<int>ranges({100,500,1000,5000,10000,50000,99000});
    map<int,double>mp1,mp0;
    for(int k=1;k<=100;k++){
        for(auto i:ranges){
            mp1[i]+=work(i,1,100000,1);
            mp0[i]+=work(i,1,100000,0);
        }
    }
    cout<<"rand:"<<endl;
    for(auto i:mp1){
        cout<<i.first<<" "<<i.second/100<<endl;
    }
    cout<<"random_shuffle:"<<endl;
    for(auto i:mp0){
        cout<<i.first<<" "<<i.second/100<<endl;
    }

}