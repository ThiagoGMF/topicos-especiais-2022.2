#include <bits/stdc++.h>

//#define endl '\n'
//#define int long long
#define pb push_back
#define ff first
#define ss second
#define all(x) (x).begin(), (x).end()
#define ll long long
#define ii pair<int,int>
#define vi vector<int>
#define vll vector<ll>
#define vii vector<ii>

const int INF = 0x3f3f3f3f;
const ll  LINF = 0x3f3f3f3f3f3f3f3fLL;
const int maxn = 2e5+10;
const int mod = 1e9+7;

using namespace std;

typedef struct _ {

  int sum_of_dists;
  string path;
  vector<vi> curr_grid;
  int size_of_path;
  ii zero_position;

  _(int s, string p, vector<vi> cg, ii zp, int sop) {
    sum_of_dists = s;
    path = p;
    curr_grid = cg;
    zero_position = zp;
    size_of_path = sop;
  }

  bool operator < (struct _ p) const {
    if(p.sum_of_dists != sum_of_dists){
      return sum_of_dists < p.sum_of_dists;
    }
    return size_of_path < p.size_of_path;
  }

}solver;

int n, m;

vector<vi> vs;

map<vector<vi>, int> vis;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
string dir = "cbed";

bool is_inside_matrix(int x,int y){
  return x>=0&&x<n&&y>=0&&y<m;
}

ii get_final_coordinate_of_value(int value){
  return { value / m, value % m};
}

int get_distance_from_final_pos(ii curr_pos, ii final_pos){
  return abs(curr_pos.ff - final_pos.ff) + abs(curr_pos.ss - final_pos.ss);
}

int get_sum_of_dists(vector<vi> &vec = vs){

  int s = 0;

  for(int i=0;i<n;++i){
    for(int j=0;j<m;++j){
      s += get_distance_from_final_pos({i, j}, get_final_coordinate_of_value(vec[i][j]));
    }
  }

  return s;
}

void solve(ii start){

  priority_queue<solver> pq;

  int d = get_sum_of_dists();

  pq.push(solver(-d, "", vs, start, 0));

  while(!pq.empty()) {

    solver s = pq.top();

    s.sum_of_dists *= -1;
    s.size_of_path *= -1;

    pq.pop();

    if(vis[s.curr_grid] != 0 && s.size_of_path > vis[s.curr_grid])
      continue;

    if(s.sum_of_dists == 0) {
      cout << "found: " << s.path << " " << s.size_of_path << endl;
      break;
    }

    vis[s.curr_grid] = s.size_of_path;

    for(int i=0;i<4;++i){
      int x = s.zero_position.ff, y = s.zero_position.ss;
      int nx = s.zero_position.ff + dx[i], ny = s.zero_position.ss + dy[i];
      if(is_inside_matrix(nx, ny)){
        swap(s.curr_grid[x][y], s.curr_grid[nx][ny]);
        if(!vis[s.curr_grid]){
          pq.push(solver(-get_sum_of_dists(s.curr_grid) , s.path + dir[i], s.curr_grid, {nx,ny}, -(s.size_of_path + 1)));
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