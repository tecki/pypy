
/************************************************************/
 /***  C header subsection: stack operations               ***/

#include <src/precommondefs.h>


#ifndef MAX_STACK_SIZE
#    define MAX_STACK_SIZE (3 << 18)    /* 768 kb */
#endif


typedef struct {
    char *stack_end;
    long stack_length;
    char report_error;
} rpy_stacktoobig_t;

RPY_EXTERN rpy_stacktoobig_t rpy_stacktoobig;

RPY_EXTERN
char LL_stack_too_big_slowpath(long);    /* returns 0 (ok) or 1 (too big) */
RPY_EXTERN
void LL_stack_set_length_fraction(double);

/* some macros referenced from rpython.rlib.rstack */
#define LL_stack_get_end() ((long)rpy_stacktoobig.stack_end)
#define LL_stack_get_length() rpy_stacktoobig.stack_length
#define LL_stack_get_end_adr()    ((long)&rpy_stacktoobig.stack_end)   /* JIT */
#define LL_stack_get_length_adr() ((long)&rpy_stacktoobig.stack_length)/* JIT */

#define LL_stack_criticalcode_start()  (rpy_stacktoobig.report_error = 0)
#define LL_stack_criticalcode_stop()   (rpy_stacktoobig.report_error = 1)


#ifdef __GNUC__
#  define PYPY_INHIBIT_TAIL_CALL()   asm("/* inhibit_tail_call */")
#else
#  define PYPY_INHIBIT_TAIL_CALL()   /* add hints for other compilers here */
#endif
