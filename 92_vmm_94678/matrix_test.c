#include <stdio.h>
#define DEBUG 1 
#define MAX 2
#define BPW 4
#define A_A 0
#define A_B ( A_A + sizeof( a ) )
#define A_C ( A_B + sizeof( b ) )
#define S( a, v ) printf( "w %5d %5d  ", a, v );
#define L( a    ) printf( "r %5d        ", a )
typedef int mat_tp[ MAX ][ MAX ]; 
mat_tp a, b, c; 
void init()
{ 
        for( int row = 0; row < MAX; ++row ) 
        {
                for( int col = 0; col < MAX; ++col ) 
                {
                        a[ row ][ col ] = row + 10 * col;
                        b[ row ][ col ] = row + col + 77;
                        c[ row ][ col ] = 0;
                } 
        } 
} 
void print( mat_tp m, char * msg )
{ 
        printf( "%s\n", msg );
        for( int row = 0; row < MAX; ++row ) 
        {
                for( int col = 0; col < MAX; ++col ) 
                {
                        printf( "%5d ", m[ row ][ col ] );
                } 
                printf( "\n" );
        } 
        printf( "\n" );
} 
#ifdef DEBUG
void print_all()
{ 
        print( a, "matrix a[][]" );
        print( b, "matrix b[][]" );
        print( c, "matrix c[][]" );
} 
#endif
void mat_mult( mat_tp m )
{ 
        for( int row = 0; row < MAX; ++row ) 
        {
                for( int col = 0; col < MAX; ++col ) 
                {
                        m[ row ][ col ] = 0;
                        for( int x = 0; x < MAX; ++x ) 
                        {
                                m[ row ][ col ] += a[ row ][ x ] * b[ x ][ col ];
                        } 
                } 
        } 
} 
void gen( )
{ 
        for( int row = 0; row < MAX; ++row ) 
        {
                for( int col = 0; col < MAX; ++col ) 
                {
                        for( int i = 0; i < MAX; ++ i ) 
                        {
                                if( ( i % 2 ) == 0 ) printf( "\n" );
                                S( A_C + BPW * ( row * MAX + col ), i );
                                L( A_C + BPW * ( row * MAX + col ) );
                                L( A_A + BPW * ( row * MAX + i ) );
                                L( A_B + BPW * ( i * MAX + col ) );
                        } 
                } 
        } 
        printf( "\n" );
} 
int main(int argc, char ** argv)
{ 
        printf( "If want larger matrix, change MAX. Now it is %d.\n", MAX );
        init();
        #ifdef DEBUG
        mat_mult( c );
        print_all();
        #endif
        gen();
        return 0;
} 


