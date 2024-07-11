#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;
        
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define ff first
#define ss second
#define pb push_back
typedef long long ll;

int globalState = 0;
        
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

bool possible(vector<vector<int>>& board, int y, int x, int n){

  for(int i = 0; i < 9; i++){
    if(board[i][x] == n) return false;
  }

  for(int i = 0; i < 9; i++){
    if(board[y][i] == n) return false;
  }

  int x0 = (x/3) * 3, y0 = (y/3) * 3;

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(board[y0 + i][x0 + j] == n) return false;
    }
  }

  return true;
}

int mostCommumNumber(vector<vector<int>>& board){
  vector<int> quant(10, 0);
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(board[i][j] != 0) quant[board[i][j]]++;
    }
  }

  int b = 0, ans = 0;
  for(int i = 1; i < 10; i++){
    if(quant[i] >= b && quant[i] != 9){
      ans = i;
      b = quant[i];
    }
  }

  return ans;
}

int complete(vector<vector<int>>& board){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(board[i][j] == 0) return false;
    }
  }

  return true;
}

int bfs(vector<vector<int>>& board){

  queue<vector<vector<int>>> q;
  int states = 0;

  for(int i = 0; i < 9; i++){
    bool done = false;
    for(int j = 0; j < 9; j++){
      if(board[i][j] == 0){
        for(int k = 1; k < 10; k++){
          if(possible(board, i, j, k)){
            board[i][j] = k; q.push(board);
            done = true;
            states++;
          }
        }
        break;
      }
    }
    if(done) break;
  }

  while(!q.empty()){
    vector<vector<int>> aux = q.front(); q.pop();
    bool done = false;
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(aux[i][j] == 0){
          for(int k = 1; k < 10; k++){
            if(possible(aux, i, j, k)){
              aux[i][j] = k; q.push(aux); 
              states++;
            }
          }
          done = true;
          break;
        }
      }
      if(done) break;
    }
    if(done) board = aux;
  }
  return states;
}

bool dls(vector<vector<int>>& board, int limit){
    if(limit == 0) return false;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(board[i][j] == 0){
                for(int k = 1; k < 10; k++){
                    if(possible(board, i, j, k)){
                        globalState++;
                        board[i][j] = k;
                        if(dls(board, limit - 1)) return true;
                        board[i][j] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

bool idfs(vector<vector<int>>& board, int max_depth){
    for(int i = 1; i <= max_depth; i++){
        if(dls(board, i)) return true;
    }
    return false;
}

int ucs(vector<vector<int>>& board){
  priority_queue<pair<int, vector<vector<int>>>> q;

  int c = 0;
  int states = 0;
  for(int i = 0; i < 9; i++){
    bool done = false;
    for(int j = 0; j < 9; j++){
      if(board[i][j] == 0){
        c--;
        for(int k = 1; k < 10; k++){
          if(possible(board, i, j, k)){
            board[i][j] = k; q.push({c, board});
            done = true;
            states++;
          }
        }
        break;
      }
    }
    if(done) break;
  }

  
  while(!q.empty()){
    vector<vector<int>> aux = q.top().second; q.pop();
    bool done = false;
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(aux[i][j] == 0){
          c--;
          for(int k = 1; k < 10; k++){
            if(possible(aux, i, j, k)){
              aux[i][j] = k; q.push({c, aux}); states++;
            }
          }
          done = true;
          break;
        }
      }
      if(done) break;
    }
    if(done) board = aux;
  }

  return states;
}

bool dfs(vector<vector<int>>& board) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0) {
        for (int k = 1; k < 10; k++) {
          if (possible(board, i, j, k)) {
            board[i][j] = k;
            globalState++;
            if (dfs(board)) { 
              return true;  
            } 
            board[i][j] = 0; 
          }
        }
        return false;
      }
    }
  }
  return true;
}

bool greedy(vector<vector<int>>& board) {
  int n = mostCommumNumber(board);
  if(n == 0) return true;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (board[i][j] == 0 && possible(board, i, j, n)) {
        board[i][j] = n;
        globalState++;
        if (greedy(board)) return true;
        board[i][j] = 0; 
      }
    }
  }

  return false;

}

int findOptions(vector<vector<int>>& board, int row, int col) {
    int num = 0;
    for (int i = 1; i <= 9; ++i) {
        if (possible(board, row, col, i)) num++;
    }
    return num;
}

int aStarSearch(vector<vector<int>>& board) {
    // Fila de prioridade para armazenar as células vazias com base no número de opções
    priority_queue<pair<int, pair <pair<int, int>, vector<vector<int>>>>> q;
    int c = 0, states = 0, m = INT_MAX;

    pair<int, int> p;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == 0) {
              int aux = findOptions(board, i, j);
              if(aux < m){
                m = aux; p.ff = i; p.ss = j;
              }
            }
        }
    }

    q.push({c, {p, board}});

    
    while (!q.empty()) {
      m = INT_MAX;
        vector<vector<int>> aux = q.top().ss.ss;
        int row = q.top().ss.ff.ff;
        int col = q.top().ss.ff.ss;
        q.pop();
        
        for(int k = 1; k < 10; k++){
          if(possible(aux, row, col, k)){
            aux[row][col] = k;
            for (int i = 0; i < 9; ++i) {
              for (int j = 0; j < 9; ++j) {
                  if (aux[i][j] == 0) {
                    int a = findOptions(aux, i, j);
                    if(a < m){
                      m = a; p.ff = i; p.ss = j;
                    }
                  }
              }
            }
            c--;
            q.push({c, {{p.ff, p.ss},aux}}); states++;
          }
        }
        board = aux;
    }

    return states;
}

void setBoard(vector<vector<int>>& board, const string& input) {
    int idx = 0;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            while (input[idx] == ' ') idx++; 
            board[i][j] = input[idx++] - '0'; 
        }
    }
}

void printBoard(vector<vector<int>>& board){ 
    for (int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout << board[i][j];
        }
        cout << " ";
    }   
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <algorithm_character> <board_input>" << endl;
        return 1;
    }

    char c = argv[1][0];
    string input = argv[2];

    vector<vector<int>> board(9, vector<int>(9, 0));
    setBoard(board, input);
    int n;

    auto start = high_resolution_clock::now();

    switch (c) {
        case 'B': // BFS
            n = bfs(board);
            break;
        case 'I': // Iterative deepening search
            idfs(board, 81);
            break;
        case 'U': // Uniform-cost search
            n = ucs(board);
            break;
        case 'A': // A* search
            n = aStarSearch(board);
            break;
        case 'G': // Greedy best-first search
            greedy(board);
            break;
        case 'D': // DFS
            dfs(board);
            break;
        default:
            cerr << "Invalid input." << endl;
            return 1;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (c == 'B' || c == 'U' || c == 'A') {
        cout << n << " " << duration.count() << endl;
    } else if (c == 'I' || c == 'D' || c == 'G') {
        cout << globalState << " " << duration.count() << endl;
    }

    printBoard(board);

    return 0;
}