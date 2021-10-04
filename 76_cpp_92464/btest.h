/*
 * CS:APP Data Lab
 */

/* Colors -- m. toups */
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[1;37m"

/* Declare different function types */
typedef int (*funct_t) (void);
typedef int (*funct1_t)(int);
typedef int (*funct2_t)(int, int); 
typedef int (*funct3_t)(int, int, int); 

/* Combine all the information about a function and its tests as structure */
typedef struct {
    char *name;             /* String name */
    funct_t solution_funct; /* Function */
    funct_t test_funct;     /* Test function */
    int args;               /* Number of function arguments */
    char *ops;              /* List of legal operators. Special case: "$" for floating point */
    int op_limit;           /* Max number of ops allowed in solution */
    int rating;             /* Problem rating (1 -- 4) */
    int arg_ranges[3][2];   /* Argument ranges. Always defined for 3 args, even if */
                            /* the function takes fewer. Special case: First arg */
			    /* must be set to {1,1} for f.p. puzzles */
} test_rec, *test_ptr;

extern test_rec test_set[];







