#include "common.h"

/****************N Queen start***************/
struct Queen {
  int x, y;
  Queen(int xx = 0, int yy = 0) : x(xx), y(yy){};
  bool operator==(Queen const& q) const {
    return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) ||
           (x - y == q.x - q.y);
  }
  bool operator!=(Queen const& q) const { return !(*this == q); }
  int find(stack<Queen> q_stack) {
    while (!q_stack.empty()) {
        Queen q = q_stack.top();
        q_stack.pop();
        if(*this==q) return 1;
    }
    return 0;
  }
};

// void NQueen(int N) {
//     stack<Queen> solu;
//     Queen q(0,0);
//     do{
//         if(){

//         }else{

//         }
//     }while(q.x<N || q.y<N);
// }
/****************N Queen end***************/
