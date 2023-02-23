#ifndef _H_YRR_MEM_H_
#define _H_YRR_MEM_H_

#ifdef YRR_MALLOC 
    #include <yrr-test.h>
    
    #define malloc(N) yrr_test_malloc(N)
    #define realloc(PTR, N) yrr_test_realloc(PTR, N)
    #define free(PTR) yrr_test_free(PTR)
#else
    #include <stdlib.h>
#endif

#endif
