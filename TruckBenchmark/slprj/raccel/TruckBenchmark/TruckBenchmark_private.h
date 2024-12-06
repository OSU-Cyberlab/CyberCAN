#ifndef RTW_HEADER_TruckBenchmark_private_h_
#define RTW_HEADER_TruckBenchmark_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "TruckBenchmark_types.h"
#include "TruckBenchmark.h"
#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)     if(!(ptr)) {\
    ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
    }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((ptr));\
    (ptr) = (NULL);\
    }
#else
#define rt_FREE(ptr)     if((ptr) != (NULL)) {\
    free((void *)(ptr));\
    (ptr) = (NULL);\
    }
#endif
#endif
#ifndef __RTW_UTFREE__
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
void * rt_TDelayCreateBuf ( int_T numBuffer , int_T bufSz , int_T elemSz ) ;
boolean_T rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * uBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
; real_T look_SplNBinXScd ( uint32_T numDims , const real_T * u , const
rt_LUTSplineWork * const SWork ) ; void rt_Spline2Derivd ( const real_T * x ,
const real_T * y , uint32_T n , real_T * u , real_T * y2 ) ; real_T
intrp_NSplcd ( uint32_T numDims , const rt_LUTSplineWork * const splWork ,
uint32_T extrapMethod ) ; real_T rt_TDelayInterpolate ( real_T tMinusDelay ,
real_T tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T
oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) ; extern real_T look1_binlxpw ( real_T u0 ,
const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) ; extern
uint32_T plook_binxp ( real_T u , const real_T bp [ ] , uint32_T maxIndex ,
real_T * fraction , uint32_T * prevIndex ) ; extern uint32_T
binsearch_u32d_prevIdx ( real_T u , const real_T bp [ ] , uint32_T startIndex
, uint32_T maxIndex ) ; void rt_TDelayFreeBuf ( void * buf ) ;
#if defined(MULTITASKING)
#error Models using the variable step solvers cannot define MULTITASKING
#endif
#endif
