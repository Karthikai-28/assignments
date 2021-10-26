#include <iostream>
# define MAX 4
typedef int mat_tp[MAX][MAX];
mat_tp a,b,c;

int main(int argc, char ** argv) 
{
    std::cout << "Hello, world!\n";
    return 0;
}

void mat_mult(mat_tp a, mat_tp b, mat_tp m) 
{
    for(int row = 0; row < MAX; row++) 
    {
        for(int col; col < MAX; col++) 
        {
            m[row][col] = 0;
            for(int i  = 0; i < MAX; i++) 
            {
                m[row][col] += a[row][i] * b[i][col];
            }
        }
    }
}

void init() 
{
    for(int col = 0; col < MAX; col++) 
    {
        for(int row = 0; row < MAX; row++) 
        {
            a[row][col] = 0;
            b[row][col] = 0;
        }
    }
}



