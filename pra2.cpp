#include <iostream>
#include <string>
#include<queue>
#include<set>
#include<stack>
using namespace std;

int step;
int H, W, si, sj, gi, gj;
char c[310][310];
int INF = 1<<30;
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};
vector<vector<int>> dist;
vector<vector<int>> cnt;


stack<pair<int, int>> hist; // 訪問履歴
set<pair<int, int>> s;
vector<vector<pair<int, int>>> trainer;



int main(int argc, char *argv[]) {
  // このコードは標準入力と標準出力を用いたサンプルコードです。
  // このコードは好きなように編集・削除してもらって構いません。
  // ---
  // This is a sample code to use stdin and stdout.
  // Edit and remove this code as you like.
  cin >> step >> H >> W;
	trainer.assign(H, vector<pair<int, int>>(W, make_pair(-1, -1)));
	for(auto v : trainer){
		for(auto p : v){
			cout << "(" << p.first << " " << p.second << ") ";
		}
		cout << endl;
	}
  // for(int i=0; i<H; ++i){
  //   for(int j=0; j<W; ++j){
  //     cin >> c[i][j];
  //     if(c[i][j]=='A'){
  //       si=i;
  //       sj=j;
  //     }
  //     if(c[i][j]=='B'){
  //       gi=i;
  //       gj=j;
  //     }
  //   }
  // }
  // for(int i=0; i<H; ++i){
  //   for(int j=0; j<W; ++j){
	// 		int v=-1;
  //     if(c[i][j]=='N')v = 3;
  //     if(c[i][j]=='E')v = 0;
	// 		if(c[i][j]=='S')v = 1;
	// 		if(c[i][j]=='W')v = 2;
	// 		if(v == -1)continue;
	// 		int a=1;
	// 		while(1){
	// 			int x = i+a*di[v];
	// 			int y = j+a*dj[v];
  //       if(x<0 || x>=H || y<0 || y>=W)break;
  //       if(c[x][y]=='#' || c[x][y]=='N' || c[x][y]=='S' || c[x][y]=='E' || c[x][y]=='W') break;
	// 			trainer[x][y] = make_pair(i, j);
	// 			a++;
	// 		}
  //   }
  // }
	// dist.assign(H, vector<int>(W, INF));
  // dist[si][sj]=0;
  // queue<pair<int, int>> q;
  // q.push(make_pair(si, sj));
  // while(!q.empty()){
  //   pair<int, int> p = q.front();
  //   q.pop();
  //   int i = p.first, j = p.second;
  //   for(int v=0; v<4; ++v){
  //     int ni=i+di[v], nj=j+dj[v];
  //     if(ni<0 || ni>=H || nj<0 || nj>=W)continue;
  //     if(c[ni][nj]=='#' || c[ni][nj]=='N' || c[ni][nj]=='S' || c[ni][nj]=='E' || c[ni][nj]=='W') continue;
  //     dist[ni][nj] = min(dist[i][j]+1, dist[ni][nj]);
  //     if(c[ni][nj]=='B')continue;
  //     if(dist[i][j]+1<dist[ni][nj])q.push(make_pair(ni, nj));
  //   }
  // }
	// cnt.assign(H, vector<int>(W, 0));
	// dfs(gi, gj, -1, -1);
  // cout << dist[gi][gj] << " " << cnt[0][0] << endl;
  return 0;
}
