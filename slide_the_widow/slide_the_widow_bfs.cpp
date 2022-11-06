#include <bits/stdc++.h>

//#define endl '\n'
#define int short
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define ll long long
#define ii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define vii vector<ii>
 
// const int INF = 0x3f3f3f3f;
// const ll  LINF = 0x3f3f3f3f3f3f3f3fLL;
// const int maxn = 2e5+10;
// const int mod = 1e9+7;
 
using namespace std;

typedef struct _ {

  string path;
  vector<vi> curr_grid;
  ii zero_position;

  _(string p, vector<vi> cg, ii zp) {
    path = p;
    curr_grid = cg;
    zero_position = zp;
  }

}solver;

int n, m;

vector<vi> vs;

map<vector<vi>, bool> vis;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string dir = "cbed";

bool is_inside_matrix(int x,int y){
  return x>=0&&x<n&&y>=0&&y<m;
}

bool finish(solver s){
  bool its_over = true;

  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      if(s.curr_grid[i][j] != (i*m) + j) {
        its_over = false;
      }
    }
  }

  return its_over;
}

void solve(ii start){

  queue<solver> q;

  q.push(solver("", vs, start));

  while(!q.empty()) {

    solver s = q.front();

    q.pop();

    if(finish(s)) {
      cout << "found: " << s.path << " " << s.path.size() << endl;
      break;
    }

    vis[s.curr_grid] = 1;

    for(int i=0;i<4;++i){
      int x = s.zero_position.ff, y = s.zero_position.ss;
      int nx = s.zero_position.ff + dx[i], ny = s.zero_position.ss + dy[i];
      if(is_inside_matrix(nx, ny)){
        swap(s.curr_grid[x][y], s.curr_grid[nx][ny]);
        if(!vis[s.curr_grid]){
          q.push(solver(s.path + dir[i], s.curr_grid, {nx,ny}));
        }
        swap(s.curr_grid[x][y], s.curr_grid[nx][ny]);
      }
    }

  }

}

int32_t main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);


  cin >> n >> m;

  vs = vector<vi>(n, vi(m));

  ii start;

  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      cin >> vs[i][j];
      if(vs[i][j] == 0) start = {i, j};
    }
  }

  solve(start);

	return 0;
}