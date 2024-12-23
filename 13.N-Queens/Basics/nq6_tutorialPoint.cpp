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
   // checking if queen is in the left or not
   for (int i = 0; i < col; i++)    
      if (B[r][i])
         return false;
   for (int i = r, j = col; i >= 0 && j >= 0; i--, j--)
      //checking if queen is in the left upper diagonal or not
      if (B[i][j])       
         return false;
   for (int i = r, j = col; j >= 0 && i < n; i++, j--)
      //checking if queen is in the left lower diagonal or not
      if (B[i][j])      
         return false;
   return true;
}
bool solveProblem(int B[n][n], int col) {
   //when n queens are placed successfully
   if (col >= n)           
      return true;
   // checking placement of queen is possible or not
   for (int i = 0; i < n; i++) {     
      if (isQueenPlaceValid(B, i, col)) {
         //if validate, place the queen at place (i, col)
         B[i][col] = 1;     
         //Go for the other columns recursively
         if (solveProblem(B, col + 1))    
            return true;          
         //When no place is vacant remove that queen   
         B[i][col] = 0;        
      }
   }
   return false;      
}
bool displaySolution() {
   int B[n][n];
   for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
         //set all elements to 0
         B[i][j] = 0;      
   //starting from 0th column
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