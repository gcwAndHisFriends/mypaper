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
#include<fstream>
using namespace std;
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

//构造数列
vector<int> 
get_array(int m, int l, int r, bool unique) {
	vector<int>array;
	int n=r-l+1;
	if (unique) {
		if (r - l + 1 < m)
			return {};//不可能构造
		if (Suitable_for_random(m,n)) {//密度较低,可以使用随机性算法
			unordered_map<int, int>mp;
			for (int i = 1; i <= m; i++) {
				int u;
                do{
                    u = randed_int(l, r);
                }while(mp[u]);
				mp[u] = 1;
				array.push_back(u);
			}
			return array;
		} 
		else { //不适合使用随机性算法进行构造
			for (int i = l; i <= r; i++) {
				array.push_back(i);
			}
			random_shuffle(array.begin(), array.end());
			array.erase(array.begin() + m, array.end());//把m之后的全删
			return array;
		}
	}else{
		for (int i = 1; i <= m; i++) {
			array.push_back(randed_int(l, r));
		}
		return array;
	}	
}

//构造树
vector<node_val_int> 
get_tree(int n, int l, int r, bool unique) {
    if (unique && l + n > r)
        return {};
    vector<node_val_int>g_line;
    vector<int>tree_val = get_array(n - 1, l, r, unique);
    for (int i = 2; i <= n; i++) {
        int fa = randed_int(1, i - 1);
        g_line.push_back({fa, i, tree_val[i - 2]});
    }
    return g_line;
}			
//仙人掌
vector<node_val_int>
get_cactus(int n,int l, int r, bool unique_val) {
	
    int m=n-1;
    
    vector<int>head(n+5),a(n+5),b(n+5),top(n+5),fa(n+5),ver(n*2+5),Next(n*2),vis(n+5);
    int tot=0;
    //链式向前星
    auto add=[&](auto add,int x,int y){
        ver[++tot] = y;
        Next[tot] = head[x];
        head[x] = tot;
    };
    for(int i=2;i<=n;i++){
        a[i-1]=i,b[i-1]=randed_int(1,i-1);
        add(add,a[i - 1], b[i - 1]), add(add,b[i - 1], a[i - 1]);
    }
    int rt =randed_int(1,n);//随机根节点
    auto dfs=[&](auto &dfs,int x,int f,int p)->void {
        top[x] = p, fa[x] = f;
        if (head[x] && ver[head[x]] != f)//随机选择一个节点进行剖分
            dfs(dfs,ver[head[x]], x, p);
        for (int i = Next[head[x]], y; i; i = Next[i]) {
            if ((y = ver[i]) == f)continue;
            dfs(dfs,y, x, y);
        }
    };
    cout<<"------"<<endl;
    dfs(dfs,rt,0,rt);
    cout<<"------"<<endl;
    for (int i = 1; i <= n; i++)
        if (!vis[top[i]] && top[i] != i && top[i] != fa[i])
            a[++m] = i, b[m] = top[i], vis[top[i]] = true;
    cout<<"------"<<endl;
    vector<int>map_val = get_array(m, l, r, unique_val);
    cout<<"------"<<endl;
    vector<node_val_int>map_line;
    for (int i = 1; i <= m; i++) {
        map_line.push_back({a[i], b[i], map_val[i - 1]});
    }
    cout<<"------"<<endl;
    return map_line;
}

void construct(int n,int id){
	auto it=get_cactus(n,1,1e9,0);
	string url="C:\\Users\\xiasui\\Desktop\\论文\\code\\cactus\\construct_data\\algorithm1_construct\\"+to_string(n)+"\\"+to_string(id)+".txt";
	cout<<"------"<<endl;
	ofstream ofs;
	ofs.open(url,ios::out);
	if(!ofs){
		cout<<"no"<<endl;
	}
	for(auto &i:it){
		ofs<<i.u<<" "<<i.v<<'\n';	
	}
	ofs.close();
	
}

signed main(){
	
	for(int i=100;i<=100;i*=10){
		for(int j=1;j<=1;j++){
			construct(i,j);
		}	
	}
	

}


