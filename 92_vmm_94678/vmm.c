#include <stdio.h>   
#include <stdlib.h>  

#define NULL 0 
#define BpW 4  
#define P_SZ 1024 
#define MAX_PAGES P_SZ * P_SZ 
#define P_OFF_MASK 0xfff 
#define PT_X_MASK 0x3ff000 
#define PD_X_MASK 0xffc00000 
#define TWO32 0xffffffff 
#define BITS22 22 
#define BITS12 12 
#define FALSE 0
#define TRUE 1
#define NO_VALUE -1  
#define BOOL unsigned  
#define CYC_MEM_ACC 10		
#define CYC_PAGE_FAULT_R 5000		
#define CYC_PAGE_FAULT_W 5000		

typedef struct page_e_tp	
{
    int v;           
    unsigned lru;          
    BOOL dirty;       
    BOOL present;      
} struct_page_e_tp;

typedef struct_page_e_tp page_tp[ P_SZ ];

#define PAGE_SIZE sizeof( page_tp )

typedef page_tp * page_ptr_tp; 
page_tp pd; 

typedef struct triple_tp 
{
    char action;
    int m_addr;
    int m_val;         
} struct_triple_tp;

#define TRIPLE_SIZE sizeof( struct_triple_tp )

struct_triple_tp triple;

unsigned access_cnt = 0;         
int triple_cnt = -1;          
unsigned swap_out_cnt = 0;          
unsigned malloc_page_cnt = 0;      
unsigned page_fault_cnt = 0;       

unsigned cycles = 0;         
unsigned cycles_no_vmm = 0; 

unsigned max_phys_pages = 0;        
unsigned max_pt_pages = 0;     
unsigned max_real_pages = 0;       
unsigned max_log_pages = MAX_PAGES; 
unsigned ws = 0;   
unsigned max_ws = 0;   

BOOL want_trace = FALSE;     
BOOL want_swap = FALSE;     
BOOL want_dump = FALSE; 

int indent = 0;

#define TRACE_CALL
#ifdef TRACE_CALL

void trace_in( fu_name )
char * fu_name;
{ 
    int i;
    indent++;
    
    for ( i = 0; i < indent; i++ ) 
    {
        if ( ( i % 10 ) == 0 ) 
        {
            printf( "." );
        }
        else
        {
            printf( " " );
        } 
    } 
    printf( " > %d %s\n", access_cnt, fu_name );
    fflush( stdout );
} 

void trace_out( fu_name )
char * fu_name;
{ 
    int i;
    
    for ( i = 0; i < indent; i++ ) 
    {
        if ( ( i % 10 ) == 0 ) 
        {
            printf( "." );
        }
        else
        {
            printf( " " );
        } 
    } 
    printf( " < %d %s\n", access_cnt, fu_name );
    indent--;
    fflush( stdout );
} 

#else

#define trace_in
#define trace_out

#endif 
void error( msg )
char * msg;
{ 
    printf( " **ERROR** %s. \n", msg );
} 

void assert( cond, msg )
int    cond;
char * msg;
{ 
    if ( ! cond ) 
    {
        printf( "\n * * * Assertion error! * * *\n" );
        error( msg );
    } 
}

void init_page( page )
page_tp page;
{ 
    int p_x;
    
    for ( p_x = 0; p_x < P_SZ; p_x++ ) 
    {
        page[ p_x ].v = NO_VALUE;
        page[ p_x ].lru = 0;
        page[ p_x ].dirty = FALSE;
        page[ p_x ].present = FALSE;
    }
} 

FILE * swap;

void init_vm_system( )
{ 
    trace_in( "init_vm_system" );
    
    if ( ! ( swap = fopen( "swap", "w" ) ) ) 
    {
        error( "Cannot open file 'swap'" );
    } 
    fprintf( swap, "swap information.\n" );
    init_page( pd );
    trace_out( "init_vm_system" );
} 

void put_triple( )
{ 
    if ( triple_cnt % 5 == 0 ) 
    {
        printf( "\n" );
    } 
    printf( "%c ", triple.action );
    printf( "%5d ", triple.m_addr );
    
    if ( triple.action == 'w' ) 
    {
        printf( "%4d  ", triple.m_val );
    }
    else
    {
        printf( " " );
    } 
} 

unsigned get_triple( )
{ 
    char action = ' ';
    int length;
    int value;

    #define DONE 0
    #define MORE 1

    trace_in( "get_triple" );
    triple_cnt++;
    
    while ( action == ' ' ) 
    {
        length = scanf( "%s", & action );
    
        if ( length == EOF ) 
        {
            trace_out( "get_triple" );
            return DONE;
        }
        else
        {
            assert( ( length == 1 ), "Wrong number of bytes read" );
    
            switch ( action ) 
            {
                case 'r':
                case 'w':
                case 'p':
                case ' ':
                break;
                case '\t':
                action = ' ';
                break;
                default:
                printf( "Illegal action. Found '%c'. Only p r w allowed.\n", action );
            } 
        } 
    } 
    triple.action = action;
    length = scanf( "%d", & value );
    
    if ( length == EOF ) 
    {
        trace_out( "get_triple" );
        return DONE;
    } 
    triple.m_addr = value;
    triple.m_val  = NO_VALUE;

    if ( action == 'w' ) 
    {
        length = scanf( "%d", & value );
    
        if (  length == EOF ) 
        {
            trace_out( "get_triple" );
            return DONE;
        } 
        triple.m_val = value;
    }
    
    else if ( action == 'p' ) 
    {
        if ( 0 == max_phys_pages ) 
        {
            max_phys_pages = value;
        }
        else
        {
            printf( "physical pages already set to %d\n", max_phys_pages );
        } 
    } 
    trace_out( "get_triple" );
    return MORE;
}

char * my_malloc( size )
unsigned size;
{ 
    char * ptr = (char *)malloc( size );
    assert( ( size % BpW == 0 ), "Non-aligned memory request" );
    assert( ( ptr != NULL ), "No more heap space" );
    return ptr;
} 

void statistics( )
{ 
    printf( "\n\n * * * Paging Activity Statistics * * *\n\n" );
    printf( " number of memory accesses = %d\n", access_cnt );
    printf( " number of triples (1 + access) = %d\n", triple_cnt );
    printf( " number of swap ins (faults) = %d\n", page_fault_cnt );
    printf( " number of swap outs = %d\n", swap_out_cnt );
    printf( " total number of pages malloced = %d\n", malloc_page_cnt );
    printf( " number of pages for Tape Tables = %d\n", max_pt_pages );
    printf( " number of real pages for user = %d\n", max_real_pages );
    printf( " total memory cycles = %d\n", cycles );
    printf( " cycles w/o vmm = %d\n", cycles_no_vmm );
    printf( " 2 * cycles w/o vmm would be = %d\n", 2 * cycles_no_vmm );
    printf( " cycles per swap_in = %d\n", CYC_PAGE_FAULT_R );
    printf( " cycles per swap_out = %d\n", CYC_PAGE_FAULT_W );
    printf( " last working set size = %d\n", ws );
    printf( " max working set size ever = %d\n", max_ws );
    printf( " max physical pages = %d\n", max_phys_pages );
    printf( " page size = 0x%x = %d\n", BpW * P_SZ, BpW * P_SZ );
    printf( " Address range = 0x%x = %u\n", TWO32, TWO32 );
} 

void inc( new_cycles )
int new_cycles;
{ 
    cycles += new_cycles;
} 

void show_page_structure( msg1, msg2 )
char * msg1;
char * msg2;
{ 
    page_ptr_tp pt = NULL;
    page_ptr_tp p = NULL;
    unsigned pd_x;
    unsigned pt_x;
    trace_in( "show_page_structure" );
    fprintf( swap, "\n  * * * %s %s * * *\n\n", msg1, msg2 );
    fprintf( swap, "Dumping Page Directory:\n" );
    
    for ( pd_x = 0; pd_x < P_SZ; pd_x++ ) 
    {
        if ( pd[ pd_x ].present ) 
        {
            pt = (page_ptr_tp) pd[ pd_x ].v;
            fprintf( swap, "pd[%d].v   = 0x%x\n", pd_x, (unsigned) pt );
            fprintf( swap, "pd[%d].lru = %d\n",   pd_x, pd[ pd_x ].lru );
        } 
    }
    fflush( swap );
    fprintf( swap, "\nDumping Page Tables:\n" );
    
    for ( pd_x = 0; pd_x < P_SZ; pd_x++ ) 
    {
        if ( pd[ pd_x ].present ) 
        {
            pt = (page_ptr_tp) pd[ pd_x ].v;
            fprintf( swap, "Page Dir entry %d:\n", pd_x );
            
            for ( pt_x = 0; pt_x < P_SZ; pt_x++ ) 
            {
                if ( (*pt)[ pt_x ].present ) 
                {
                    p = (page_ptr_tp) (*pt)[ pt_x ].v;
                    fprintf( swap, "pt[%d].v = 0x%07x, ", pt_x, (unsigned) p );
                    fprintf( swap, "lru = %d", (*pt)[ pt_x ].lru );
            
                    if ( (*pt)[ pt_x ].dirty ) 
                    {
                        fprintf( swap, ", written" );
                    } 
                    fprintf( swap, "\n" );
                    fflush( swap );
                } 
            } 
        } 
    } 
    fflush( swap );
    trace_out( "show_page_structure" );
} 

void swap_out( msg )
char * msg;
{ 
    unsigned lru = TWO32;
    unsigned x = 0;
    unsigned pd_x = 0;
    unsigned pt_x = 0;
    BOOL initial = TRUE;
    page_ptr_tp pt = NULL;
    page_ptr_tp ptr;
    trace_in( "swap_out" );
    swap_out_cnt++;
    assert( ws >= max_phys_pages, "Why swap out page if room in working set?" );
    ptr = (page_ptr_tp )pd[ 0 ].v;
    
    for ( pd_x = 0; pd_x < P_SZ; pd_x++ ) 
    {
    
        if ( pd[ pd_x ].present ) 
        {
            pt = (page_ptr_tp) pd[ pd_x ].v;
    
            for ( pt_x = 0; pt_x < P_SZ; pt_x++ ) 
            {
    
                if ( (*pt)[ pt_x ].present ) 
                {
                    assert( (*pt)[ pt_x ].v != NO_VALUE, "pt has no value" );
    
                    if ( (*pt)[ pt_x ].lru <= lru ) 
                    {
                        initial = FALSE;
                        lru = (*pt)[ pt_x ].lru;
                        ptr = pt;
                        x   = pt_x;
                    } 
                } 
            } 
        } 
    }
    assert( !initial, "Never found a real page to be swapped out." );
    ws--;
    assert( ws < max_phys_pages, "There must be room in working set" );
    assert( x >= 0, "X is <= 0" );
    assert( x < P_SZ, "X is >= P_SZ" );
    assert( ptr != NULL, "Null ptr" );
    assert( (*ptr)[ x ].v > 0, "Null (*ptr)[x].v" );
    assert( (*ptr)[ x ].v != NO_VALUE, "(*ptr)[ x ].v == NO_VALUE" );
    assert( (*ptr)[ x ].present, "How swap out if NOT present?" );
    (*ptr)[ x ].present = FALSE;
    
    if ( (*ptr)[ x ].dirty ) 
    {
        inc( CYC_PAGE_FAULT_W );
    }
    
    if ( want_swap ) 
    {
        show_page_structure( " swapped out a page", msg );
    } 
    trace_out( "swap_out" );
} 

void swap_in( msg, p_frame, p_x )
char * msg;
page_ptr_tp p_frame;
int p_x;
{ 
    page_ptr_tp ptr = NULL;
    trace_in( "swap_in" );
    page_fault_cnt++;
    assert( p_x >= 0, "p_x must be >= 0" );
    assert( p_x < P_SZ, "p_x must be < P_SZ" );
    assert( ! (*p_frame)[ p_x ].present, "resident page cannot be swapped in" );
    assert( ws <= max_phys_pages, "Working set size exceeded" );
    
    if ( ws >= max_phys_pages ) 
    {
        swap_out( "ws full in 'swap_in'; must 'swap_out'" );
        assert( ws < max_phys_pages, "After swap out no room in working set" );
    } 
    ws++;

    (*p_frame)[ p_x ].present = TRUE;
    (*p_frame)[ p_x ].lru     = 0;
    (*p_frame)[ p_x ].dirty   = FALSE;
    
    if ( max_ws < ws ) 
    {
        max_ws = ws;
    } 
    inc( CYC_PAGE_FAULT_R );
    
    if ( want_swap ) 
    {
        show_page_structure( " swapped in a page", msg );
    } 
    trace_out( "swap_in" );
} 
 
#include <stdio.h>
#define DEBUG 1
#define MAX 4
#define BPW 4
#define A_A 0
#define A_B ( A_A + sizeof( a ) )
#define A_C ( A_B + sizeof( b ) )
#define S( a, v ) printf( "w %5d %5d ", a, v );
#define L( a ) printf( "r %5d ", a )
 
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

int main( int argc, char ** argv )
{ 
    printf( "If want larger matrix, change MAX. Now it is %d.\n", MAX );
    init();
    #ifdef DEBUG
    mat_mult( c ); 
    print_all();
    #endif
    gen();
    statistics();
    return 0;
} 



 
