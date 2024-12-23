#include<iostream>
using namespace std;
#define n 4
void displayChess(int B[n][n]) {
   for (int row = 0; row < n; row++) {
      for (int col = 0; col < n; col++)
         cout << B[row][col] << " ";
      cout << endl;
   }
}
bool isQueenPlaceValid(int B[n][n], int r, int col) {
   for (int i = 0; i < col; i++)    
      if (B[r][i])
         return false;
   for (int i = r, j = col; i >= 0 && j >= 0; i--, j--)
      if (B[i][j])       
         return false;
   for (int i = r, j = col; j >= 0 && i < n; i++, j--)
      if (B[i][j])      
         return false;
   return true;
}
bool solveProblem(int B[n][n], int col) {
   if (col >= n)           
      return true;
   for (int i = 0; i < n; i++) {     
      if (isQueenPlaceValid(B, i, col)) {
         B[i][col] = 1;     
         if (solveProblem(B, col + 1))    
            return true;           
         B[i][col] = 0;        
      }
   }
   return false;      
}
bool displaySolution() {
   int B[n][n];
   for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
         B[i][j] = 0;      
   if (solveProblem(B, 0) == false) {     
      cout << "Solution does not exist";
      return false;
   }
   displayChess(B);
   return true;
}
int main() {
   displaySolution();
}