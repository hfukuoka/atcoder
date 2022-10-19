#include <iostream>
#include <string>
#include<queue>
#include<set>
using namespace std;

int step;
int H, W, si, sj, gi, gj;
int INF = 1<<30;
int di[4] = {0, 1, 0, -1};
int dj[4] = {1, 0, -1, 0};

vector<vector<pair<int, int>>> trainer;

int main(int argc, char *argv[]) {
  // このコードは標準入力と標準出力を用いたサンプルコードです。
  // このコードは好きなように編集・削除してもらって構いません。
  // ---
  // This is a sample code to use stdin and stdout.
  // Edit and remove this code as you like.

  cin >> step >> H >> W;
  vector<vector<char>> c(H, vector<char>(W));
  for(int i=0; i<H; ++i){
    for(int j=0; j<W; ++j){
      cin >> c[i][j];
      if(c[i][j]=='A'){
        si=i;
        sj=j;
      }
      if(c[i][j]=='B'){
        gi=i;
        gj=j;
      }
    }
  }
	trainer.assign(H, vector<pair<int, int>>(W, make_pair(-1, -1)));
  for(int i=0; i<H; ++i){
    for(int j=0; j<W; ++j){
			int v=-1;
      if(c[i][j]=='N')v = 3;
      if(c[i][j]=='E')v = 0;
			if(c[i][j]=='S')v = 1;
			if(c[i][j]=='W')v = 2;
			if(v == -1)continue;
			int a=1;
			while(1){
				int x = i+a*di[v];
				int y = j+a*dj[v];
        if(x<0 || x>=H || y<0 || y>=W)break;
        if(c[x][y]=='#' || c[x][y]=='N' || c[x][y]=='S' || c[x][y]=='E' || c[x][y]=='W') break;
				trainer[x][y] = make_pair(i, j);
				a++;
			}
    }
  }
  vector<vector<int>> dist(H, vector<int>(W, INF));
  vector<vector<int>> cnt(H, vector<int>(W, 0));
  dist[si][sj]=0;
  queue<pair<set<pair<int, int>>, pair<int, int>>> q;
  set<pair<int, int>> s0;
  q.push(make_pair(s0, make_pair(si, sj)));
  while(!q.empty()){
    pair<set<pair<int, int>>, pair<int, int>> p = q.front();
    q.pop();
    set<pair<int, int>> s = p.first;
    int i = p.second.first, j = p.second.second;
    for(int v=0; v<4; ++v){
      int ni=i+di[v], nj=j+dj[v];
      if(ni<0 || ni>=H || nj<0 || nj>=W)continue; // マップ外を禁止
      if(c[ni][nj]=='#' || c[ni][nj]=='N' || c[ni][nj]=='S' || c[ni][nj]=='E' || c[ni][nj]=='W') continue; // 壁やトレーナーの時は移動できない
			if(dist[ni][nj]<dist[i][j]+1) continue; // 最短経路でない場合を除く
			if(trainer[ni][nj]==make_pair(-1, -1) || s.count(trainer[ni][nj])){
				if(cnt[ni][nj]<=cnt[i][j]){
					cnt[ni][nj] = cnt[i][j];
				}else continue;
			}else{
				if(cnt[ni][nj]<=cnt[i][j]+1){
					cnt[ni][nj] = cnt[i][j]+1;
					s.insert(trainer[ni][nj]);
				}else continue;
			}
      dist[ni][nj] = dist[i][j]+1;
      if(c[ni][nj]=='B')continue;
      q.push(make_pair(s, make_pair(ni, nj)));
    }
  }
  cout << dist[gi][gj] << " " << cnt[gi][gj] << endl;
  return 0;
}
