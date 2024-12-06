#include "TruckBenchmark_acc.h"
#include <string.h>
#include "mwmathutil.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include <float.h>
#include "rtwtypes.h"
#include "mwstringutil.h"
#include <stddef.h>
#include "TruckBenchmark_acc_private.h"
#include "multiword_types.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T TruckBenchmark_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr
, int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T tMinusDelay ,
real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T istransportdelay ,
int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = * tailPtr ; int_T
bufSz = * bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ; real_T * xBuf = (
NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) { numBuffer = 3 ; xBuf
= * uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 )
: 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ;
real_T * tempT ; real_T * tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf =
* uBufPtr ; int_T newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr
) { * maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer
* newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false
) ; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
uBufPtr = tempU ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
look_SplNBinXScd ( uint32_T numDims , const real_T * u , const
rt_LUTSplineWork * const SWork ) { rt_LUTnWork * const TWork_look = SWork ->
m_TWork ; real_T * const fraction = ( real_T * ) TWork_look -> m_bpLambda ;
uint32_T * const bpIdx = TWork_look -> m_bpIndex ; const uint32_T * const
maxIndex = TWork_look -> m_maxIndex ; uint32_T k ; for ( k = 0U ; k < numDims
; k ++ ) { const real_T * const bpData = ( ( const real_T * const * )
TWork_look -> m_bpDataSet ) [ k ] ; bpIdx [ k ] = plook_binxp ( u [ k ] ,
bpData , maxIndex [ k ] , & fraction [ k ] , & bpIdx [ k ] ) ; } return (
intrp_NSplcd ( numDims , SWork , 2U ) ) ; } void rt_Spline2Derivd ( const
real_T * x , const real_T * y , uint32_T n , real_T * u , real_T * y2 ) {
real_T p , qn , sig , un ; uint32_T n1 , i , k ; n1 = n - 1U ; y2 [ 0U ] =
0.0 ; u [ 0U ] = 0.0 ; for ( i = 1U ; i < n1 ; i ++ ) { real_T dxm1 = x [ i ]
- x [ i - 1U ] ; real_T dxp1 = x [ i + 1U ] - x [ i ] ; real_T dxpm = dxp1 +
dxm1 ; sig = dxm1 / dxpm ; p = ( sig * y2 [ i - 1U ] ) + 2.0 ; y2 [ i ] = (
sig - 1.0 ) / p ; u [ i ] = ( ( y [ i + 1U ] - y [ i ] ) / dxp1 ) - ( ( y [ i
] - y [ i - 1U ] ) / dxm1 ) ; u [ i ] = ( ( ( 6.0 * u [ i ] ) / dxpm ) - (
sig * u [ i - 1U ] ) ) / p ; } qn = 0.0 ; un = 0.0 ; y2 [ n1 ] = ( un - ( qn
* u [ n1 - 1U ] ) ) / ( ( qn * y2 [ n1 - 1U ] ) + 1.0 ) ; for ( k = n1 ; k >
0U ; k -- ) { y2 [ k - 1U ] = ( y2 [ k - 1U ] * y2 [ k ] ) + u [ k - 1U ] ; }
return ; } real_T intrp_NSplcd ( uint32_T numDims , const rt_LUTSplineWork *
const splWork , uint32_T extrapMethod ) { uint32_T il ; uint32_T iu , k , i ;
real_T h , s , p , smsq , pmsq ; const rt_LUTnWork * TWork_interp = ( const
rt_LUTnWork * ) splWork -> m_TWork ; const real_T * fraction = ( real_T * )
TWork_interp -> m_bpLambda ; const real_T * yp = ( real_T * ) TWork_interp ->
m_tableData ; real_T * yyA = ( real_T * ) splWork -> m_yyA ; real_T * yyB = (
real_T * ) splWork -> m_yyB ; real_T * yy2 = ( real_T * ) splWork -> m_yy2 ;
real_T * up = ( real_T * ) splWork -> m_up ; real_T * y2 = ( real_T * )
splWork -> m_y2 ; uint8_T * reCalc = splWork -> m_reCalc ; const real_T * *
bpDataSet = ( const real_T * * ) TWork_interp -> m_bpDataSet ; const real_T *
xp = bpDataSet [ 0U ] ; real_T * yy = yyA ; uint32_T bufBank = 0U ; uint32_T
len = TWork_interp -> m_maxIndex [ 0U ] + 1U ; if ( * reCalc == 1 ) { for ( i
= 0U ; i < splWork -> m_numYWorkElts [ 0U ] ; i ++ ) { rt_Spline2Derivd ( xp
, yp , len , up , y2 ) ; yp = & yp [ len ] ; y2 = & y2 [ len ] ; } yp = (
const real_T * ) TWork_interp -> m_tableData ; y2 = ( real_T * ) splWork ->
m_y2 ; } * reCalc = 0 ; for ( k = 0U ; k < numDims ; k ++ ) { xp = bpDataSet
[ k ] ; len = TWork_interp -> m_maxIndex [ k ] + 1U ; il = TWork_interp ->
m_bpIndex [ k ] ; iu = il + 1U ; h = xp [ iu ] - xp [ il ] ; p = fraction [ k
] ; s = 1.0 - p ; pmsq = p * ( ( p * p ) - 1.0 ) ; smsq = s * ( ( s * s ) -
1.0 ) ; if ( ( p > 1.0 ) && ( extrapMethod == 2U ) ) { real_T slope ; for ( i
= 0U ; i < splWork -> m_numYWorkElts [ k ] ; i ++ ) { slope = ( yp [ iu ] -
yp [ il ] ) + ( ( y2 [ il ] * h * h ) * ( 1.0 / 6.0 ) ) ; yy [ i ] = yp [ iu
] + ( slope * ( p - 1.0 ) ) ; yp = & yp [ len ] ; y2 = & y2 [ len ] ; } }
else if ( ( p < 0.0 ) && ( extrapMethod == 2U ) ) { real_T slope ; for ( i =
0U ; i < splWork -> m_numYWorkElts [ k ] ; i ++ ) { slope = ( yp [ iu ] - yp
[ il ] ) - ( ( y2 [ iu ] * h * h ) * ( 1.0 / 6.0 ) ) ; yy [ i ] = yp [ il ] +
( slope * p ) ; yp = & yp [ len ] ; y2 = & y2 [ len ] ; } } else { for ( i =
0U ; i < splWork -> m_numYWorkElts [ k ] ; i ++ ) { yy [ i ] = yp [ il ] + p
* ( yp [ iu ] - yp [ il ] ) + ( ( smsq * y2 [ il ] + pmsq * y2 [ iu ] ) * h *
h ) * ( 1.0 / 6.0 ) ; yp = & yp [ len ] ; y2 = & y2 [ len ] ; } } yp = yy ;
y2 = yy2 ; if ( splWork -> m_numYWorkElts [ k + 1U ] > 0U ) { uint32_T
nextLen = TWork_interp -> m_maxIndex [ k + 1U ] + 1U ; const real_T * nextXp
= bpDataSet [ k + 1U ] ; for ( i = 0U ; i < splWork -> m_numYWorkElts [ k +
1U ] ; i ++ ) { rt_Spline2Derivd ( nextXp , yp , nextLen , up , y2 ) ; yp = &
yp [ nextLen ] ; y2 = & y2 [ nextLen ] ; } } yp = yy ; y2 = yy2 ; if (
bufBank == 0U ) { yy = yyA ; bufBank = 1U ; } else { yy = yyB ; bufBank = 0U
; } } return ( yp [ 0U ] ) ; } real_T TruckBenchmark_acc_rt_TDelayInterpolate
( real_T tMinusDelay , real_T tStart , real_T * uBuf , int_T bufSz , int_T *
lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T
discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout
, t1 , t2 , u1 , u2 ; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) &&
( oldestIdx == 0 ) && ( tMinusDelay > tStart ) ) return initOutput ; if (
tMinusDelay <= tStart ) return initOutput ; if ( ( tMinusDelay <= tBuf [
oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [ oldestIdx ] ) ; } else {
int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ;
t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ;
u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout =
u2 ; } else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2
- t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; }
} if ( minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx
== newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx ==
newIdx ) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ;
if ( tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i
== newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else {
while ( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ;
} i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete
) { double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } real_T look1_binlxpw ( real_T
u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T maxIndex ) {
real_T frac ; real_T yL_0d0 ; uint32_T bpIdx ; uint32_T iLeft ; uint32_T
iRght ; if ( u0 <= bp0 [ 0U ] ) { iLeft = 0U ; frac = ( u0 - bp0 [ 0U ] ) / (
bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx =
maxIndex >> 1U ; iLeft = 0U ; iRght = maxIndex ; while ( iRght - iLeft > 1U )
{ if ( u0 < bp0 [ bpIdx ] ) { iRght = bpIdx ; } else { iLeft = bpIdx ; }
bpIdx = ( iRght + iLeft ) >> 1U ; } frac = ( u0 - bp0 [ iLeft ] ) / ( bp0 [
iLeft + 1U ] - bp0 [ iLeft ] ) ; } else { iLeft = maxIndex - 1U ; frac = ( u0
- bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; }
yL_0d0 = table [ iLeft ] ; return ( table [ iLeft + 1U ] - yL_0d0 ) * frac +
yL_0d0 ; } uint32_T plook_binxp ( real_T u , const real_T bp [ ] , uint32_T
maxIndex , real_T * fraction , uint32_T * prevIndex ) { uint32_T bpIndex ;
uint32_T startIndex ; if ( u <= bp [ 0U ] ) { bpIndex = 0U ; * fraction = ( u
- bp [ 0U ] ) / ( bp [ 1U ] - bp [ 0U ] ) ; } else if ( u < bp [ maxIndex ] )
{ startIndex = * prevIndex ; bpIndex = binsearch_u32d_prevIdx ( u , bp ,
startIndex , maxIndex ) ; * fraction = ( u - bp [ bpIndex ] ) / ( bp [
bpIndex + 1U ] - bp [ bpIndex ] ) ; } else { bpIndex = maxIndex - 1U ; *
fraction = ( u - bp [ maxIndex - 1U ] ) / ( bp [ maxIndex ] - bp [ maxIndex -
1U ] ) ; } * prevIndex = bpIndex ; return bpIndex ; } uint32_T
binsearch_u32d_prevIdx ( real_T u , const real_T bp [ ] , uint32_T startIndex
, uint32_T maxIndex ) { uint32_T bpIndex ; uint32_T found ; uint32_T iLeft ;
uint32_T iRght ; bpIndex = startIndex ; iLeft = 0U ; iRght = maxIndex ; found
= 0U ; while ( found == 0U ) { if ( u < bp [ bpIndex ] ) { iRght = bpIndex -
1U ; bpIndex = ( ( bpIndex + iLeft ) - 1U ) >> 1U ; } else if ( u < bp [
bpIndex + 1U ] ) { found = 1U ; } else { iLeft = bpIndex + 1U ; bpIndex = ( (
bpIndex + iRght ) + 1U ) >> 1U ; } } return bpIndex ; } void
rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * *
path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void
rt_ssSet_slErrMsg ( void * S , void * diag ) { SimStruct * castedS = (
SimStruct * ) S ; if ( ! _ssIsErrorStatusAslErrMsg ( castedS ) ) {
_ssSet_slErrMsg ( castedS , diag ) ; } else { _ssDiscardDiagnostic ( castedS
, diag ) ; } } void rt_ssReportDiagnosticAsWarning ( void * S , void * diag )
{ _ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } static void
mdlOutputs ( SimStruct * S , int_T tid ) { B_TruckBenchmark_T * _rtB ;
DW_TruckBenchmark_T * _rtDW ; P_TruckBenchmark_T * _rtP ; X_TruckBenchmark_T
* _rtX ; real_T rtb_B_12_162_0 [ 3 ] ; real_T ratio ; real_T rtb_B_12_151_0 ;
real_T taskTimeV ; real_T tmp ; int32_T isHit ; int32_T s6_iter ; uint32_T
numCycles ; _rtDW = ( ( DW_TruckBenchmark_T * ) ssGetRootDWork ( S ) ) ; _rtX
= ( ( X_TruckBenchmark_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_TruckBenchmark_T
* ) _ssGetModelBlockIO ( S ) ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { if (
_rtX -> Integrator_CSTATE >= _rtP -> P_18 ) { if ( _rtX -> Integrator_CSTATE
!= _rtP -> P_18 ) { _rtX -> Integrator_CSTATE = _rtP -> P_18 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> Integrator_MODE
= 3 ; } else if ( _rtX -> Integrator_CSTATE <= _rtP -> P_19 ) { if ( _rtX ->
Integrator_CSTATE != _rtP -> P_19 ) { _rtX -> Integrator_CSTATE = _rtP ->
P_19 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator_MODE = 4 ; } else { if ( _rtDW -> Integrator_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW -> Integrator_MODE
= 0 ; } _rtB -> B_12_0_0 = _rtX -> Integrator_CSTATE ; } else { _rtB ->
B_12_0_0 = _rtX -> Integrator_CSTATE ; } _rtB -> B_12_1_0 = _rtB -> B_12_0_0
* _rtB -> B_12_49_0_k ; _rtB -> B_12_2_0 = _rtP -> P_20 * _rtB -> B_12_1_0 ;
ssCallAccelRunBlock ( S , 12 , 3 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 4 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 5 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0 ) { isHit = ssIsSampleHit ( S ,
3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 2 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 2 , 2 , SS_CALL_MDL_OUTPUTS
) ; if ( _rtB -> B_2_2_1 < 2.147483648E+9 ) { if ( _rtB -> B_2_2_1 >= -
2.147483648E+9 ) { isHit = ( int32_T ) _rtB -> B_2_2_1 ; } else { isHit =
MIN_int32_T ; } } else if ( _rtB -> B_2_2_1 >= 2.147483648E+9 ) { isHit =
MAX_int32_T ; } else { isHit = 0 ; } if ( isHit > 2147483646 ) { isHit =
2147483646 ; } else if ( isHit < 0 ) { isHit = 0 ; } for ( s6_iter = 0 ;
s6_iter < isHit ; s6_iter ++ ) { _rtB -> B_1_1_0 = _rtB -> B_2_2_0 [ s6_iter
] ; ssCallAccelRunBlock ( S , 1 , 2 , SS_CALL_MDL_OUTPUTS ) ; srUpdateBC (
_rtDW -> CANTransmitSubsystem_SubsysRanBC ) ; } ssCallAccelRunBlock ( S , 2 ,
4 , SS_CALL_MDL_OUTPUTS ) ; } } ssCallAccelRunBlock ( S , 12 , 7 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 8 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 3 , 0 ) ; if ( isHit != 0
) { ssCallAccelRunBlock ( S , 12 , 9 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 10 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 11 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 12 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 13 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 14 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 15 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 16 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 17 , SS_CALL_MDL_OUTPUTS ) ; } if (
ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX -> Integrator1_CSTATE >= _rtP ->
P_22 ) { if ( _rtX -> Integrator1_CSTATE != _rtP -> P_22 ) { _rtX ->
Integrator1_CSTATE = _rtP -> P_22 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator1_MODE = 3 ; } else if ( _rtX -> Integrator1_CSTATE <= _rtP -> P_23
) { if ( _rtX -> Integrator1_CSTATE != _rtP -> P_23 ) { _rtX ->
Integrator1_CSTATE = _rtP -> P_23 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator1_MODE = 4 ; } else { if ( _rtDW -> Integrator1_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator1_MODE = 0 ; } _rtB -> B_12_18_0 = _rtX -> Integrator1_CSTATE ; }
else { _rtB -> B_12_18_0 = _rtX -> Integrator1_CSTATE ; } _rtB -> B_12_19_0 =
_rtP -> P_24 * _rtB -> B_12_18_0 ; _rtB -> B_12_20_0 = _rtP -> P_25 * _rtB ->
B_12_18_0 ; isHit = ssIsSampleHit ( S , 5 , 0 ) ; if ( isHit != 0 ) {
taskTimeV = ssGetTaskTime ( S , 5 ) ; if ( ssGetTNextWasAdjusted ( S , 5 ) !=
0 ) { _rtDW -> nextTime = _ssGetVarNextHitTime ( S , 0 ) ; } if ( _rtDW ->
justEnabled != 0 ) { _rtDW -> justEnabled = 0 ; if ( taskTimeV >= _rtP ->
P_29 ) { ratio = ( taskTimeV - _rtP -> P_29 ) / _rtP -> P_27 ; numCycles = (
uint32_T ) muDoubleScalarFloor ( ratio ) ; if ( muDoubleScalarAbs ( ( real_T
) ( numCycles + 1U ) - ratio ) < DBL_EPSILON * ratio ) { numCycles ++ ; }
_rtDW -> numCompleteCycles = numCycles ; ratio = ( ( real_T ) numCycles *
_rtP -> P_27 + _rtP -> P_29 ) + _rtP -> P_28 * _rtP -> P_27 / 100.0 ; if (
taskTimeV < ratio ) { _rtDW -> currentValue = 1 ; _rtDW -> nextTime = ratio ;
} else { _rtDW -> currentValue = 0 ; _rtDW -> nextTime = ( real_T ) (
numCycles + 1U ) * _rtP -> P_27 + _rtP -> P_29 ; } } else { _rtDW ->
numCompleteCycles = _rtP -> P_29 != 0.0 ? - 1 : 0 ; _rtDW -> currentValue = 0
; _rtDW -> nextTime = _rtP -> P_29 ; } } else if ( _rtDW -> nextTime <=
taskTimeV ) { if ( _rtDW -> currentValue == 1 ) { _rtDW -> currentValue = 0 ;
_rtDW -> nextTime = ( real_T ) ( _rtDW -> numCompleteCycles + 1LL ) * _rtP ->
P_27 + _rtP -> P_29 ; } else { _rtDW -> numCompleteCycles ++ ; _rtDW ->
currentValue = 1 ; _rtDW -> nextTime = ( _rtP -> P_28 * _rtP -> P_27 * 0.01 +
( real_T ) _rtDW -> numCompleteCycles * _rtP -> P_27 ) + _rtP -> P_29 ; } }
_ssSetVarNextHitTime ( S , 0 , _rtDW -> nextTime ) ; if ( _rtDW ->
currentValue == 1 ) { _rtB -> B_12_21_0 = _rtP -> P_26 ; } else { _rtB ->
B_12_21_0 = 0.0 ; } } ssCallAccelRunBlock ( S , 12 , 22 , SS_CALL_MDL_OUTPUTS
) ; _rtB -> B_12_23_0 = _rtP -> P_30 * _rtB -> B_12_18_0 ; _rtB -> B_12_24_0
= _rtP -> P_31 * _rtB -> B_12_18_0 ; ssCallAccelRunBlock ( S , 12 , 25 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX ->
Integratoromega_t_CSTATE >= _rtP -> P_33 ) { if ( _rtX ->
Integratoromega_t_CSTATE != _rtP -> P_33 ) { _rtX -> Integratoromega_t_CSTATE
= _rtP -> P_33 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW
-> Integratoromega_t_MODE = 3 ; } else if ( _rtX -> Integratoromega_t_CSTATE
<= _rtP -> P_34 ) { if ( _rtX -> Integratoromega_t_CSTATE != _rtP -> P_34 ) {
_rtX -> Integratoromega_t_CSTATE = _rtP -> P_34 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratoromega_t_MODE = 4 ; } else { if ( _rtDW -> Integratoromega_t_MODE !=
0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratoromega_t_MODE = 0 ; } _rtB -> B_12_26_0 = _rtX ->
Integratoromega_t_CSTATE ; } else { _rtB -> B_12_26_0 = _rtX ->
Integratoromega_t_CSTATE ; } if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX
-> Integratorp_im_CSTATE >= _rtP -> P_36 ) { if ( _rtX ->
Integratorp_im_CSTATE != _rtP -> P_36 ) { _rtX -> Integratorp_im_CSTATE =
_rtP -> P_36 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratorp_im_MODE = 3 ; } else if ( _rtX -> Integratorp_im_CSTATE <= _rtP
-> P_37 ) { if ( _rtX -> Integratorp_im_CSTATE != _rtP -> P_37 ) { _rtX ->
Integratorp_im_CSTATE = _rtP -> P_37 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratorp_im_MODE = 4 ; } else { if ( _rtDW -> Integratorp_im_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratorp_im_MODE = 0 ; } _rtB -> B_12_27_0 = _rtX -> Integratorp_im_CSTATE
; } else { _rtB -> B_12_27_0 = _rtX -> Integratorp_im_CSTATE ; } _rtB ->
B_12_28_0 = _rtB -> B_12_27_0 / _rtB -> B_12_85_0 ; if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_28_0 ; _rtDW
-> MinMax1_MODE = 0 ; if ( ( _rtB -> B_12_28_0 != _rtB -> B_12_28_0 ) || (
_rtB -> B_12_75_0_d > _rtB -> B_12_28_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_75_0_d ; _rtDW -> MinMax1_MODE = 1 ; } _rtB -> B_12_29_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_28_0 ; if ( _rtDW ->
MinMax1_MODE == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_75_0_d ; } _rtB ->
B_12_29_0 = rtb_B_12_151_0 ; } if ( _rtB -> B_12_29_0 < 0.0 ) {
rtb_B_12_151_0 = - muDoubleScalarPower ( - _rtB -> B_12_29_0 ,
0.28387734915924823 ) ; } else { rtb_B_12_151_0 = muDoubleScalarPower ( _rtB
-> B_12_29_0 , 0.28387734915924823 ) ; } taskTimeV = 2022.0 * _rtB ->
B_12_86_0_l * ( rtb_B_12_151_0 - 1.0 ) / ( 0.0016 * muDoubleScalarPower (
_rtB -> B_12_26_0 , 2.0 ) ) ; _rtB -> B_12_31_0 = _rtP -> P_38 [ 0 ] ; _rtB
-> B_12_31_0 = _rtB -> B_12_31_0 * _rtB -> B_12_26_0 + _rtP -> P_38 [ 1 ] ;
_rtB -> B_12_31_0 = _rtB -> B_12_31_0 * _rtB -> B_12_26_0 + _rtP -> P_38 [ 2
] ; if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_31_0
; _rtDW -> MinMax1_MODE_i = 0 ; if ( ( _rtB -> B_12_31_0 != _rtB -> B_12_31_0
) || ( _rtB -> B_12_77_0 > _rtB -> B_12_31_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_77_0 ; _rtDW -> MinMax1_MODE_i = 1 ; } _rtB -> B_12_32_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_31_0 ; if ( _rtDW ->
MinMax1_MODE_i == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_77_0 ; } _rtB ->
B_12_32_0 = rtb_B_12_151_0 ; } _rtB -> B_12_33_0 = 1.0 - _rtB -> B_12_32_0 *
muDoubleScalarPower ( taskTimeV , 2.0 ) ; if ( ssIsModeUpdateTimeStep ( S ) )
{ rtb_B_12_151_0 = _rtB -> B_12_76_0_d ; _rtDW -> MinMax_MODE = 0 ; if ( (
_rtB -> B_12_76_0_d != _rtB -> B_12_76_0_d ) || ( _rtB -> B_12_33_0 > _rtB ->
B_12_76_0_d ) ) { rtb_B_12_151_0 = _rtB -> B_12_33_0 ; _rtDW -> MinMax_MODE =
1 ; } _rtB -> B_12_34_0 = rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB ->
B_12_76_0_d ; if ( _rtDW -> MinMax_MODE == 1 ) { rtb_B_12_151_0 = _rtB ->
B_12_33_0 ; } _rtB -> B_12_34_0 = rtb_B_12_151_0 ; } _rtB -> B_12_35_0 = _rtP
-> P_39 [ 0 ] ; _rtB -> B_12_35_0 = _rtB -> B_12_35_0 * _rtB -> B_12_26_0 +
_rtP -> P_39 [ 1 ] ; _rtB -> B_12_35_0 = _rtB -> B_12_35_0 * _rtB ->
B_12_26_0 + _rtP -> P_39 [ 2 ] ; if ( ssIsModeUpdateTimeStep ( S ) ) {
rtb_B_12_151_0 = _rtB -> B_12_35_0 ; _rtDW -> MinMax3_MODE = 0 ; if ( ( _rtB
-> B_12_35_0 != _rtB -> B_12_35_0 ) || ( _rtB -> B_12_79_0_l > _rtB ->
B_12_35_0 ) ) { rtb_B_12_151_0 = _rtB -> B_12_79_0_l ; _rtDW -> MinMax3_MODE
= 1 ; } _rtB -> B_12_36_0 = rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB
-> B_12_35_0 ; if ( _rtDW -> MinMax3_MODE == 1 ) { rtb_B_12_151_0 = _rtB ->
B_12_79_0_l ; } _rtB -> B_12_36_0 = rtb_B_12_151_0 ; } rtb_B_12_151_0 = _rtB
-> B_12_34_0 / _rtB -> B_12_36_0 ; if ( rtb_B_12_151_0 < 0.0 ) { _rtB ->
B_12_37_0 = - muDoubleScalarSqrt ( - rtb_B_12_151_0 ) ; } else { _rtB ->
B_12_37_0 = muDoubleScalarSqrt ( rtb_B_12_151_0 ) ; } if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_78_0 ; _rtDW
-> MinMax2_MODE = 0 ; if ( ( _rtB -> B_12_78_0 != _rtB -> B_12_78_0 ) || (
_rtB -> B_12_37_0 > _rtB -> B_12_78_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_37_0 ; _rtDW -> MinMax2_MODE = 1 ; } _rtB -> B_12_38_0 = rtb_B_12_151_0
; } else { rtb_B_12_151_0 = _rtB -> B_12_78_0 ; if ( _rtDW -> MinMax2_MODE ==
1 ) { rtb_B_12_151_0 = _rtB -> B_12_37_0 ; } _rtB -> B_12_38_0 =
rtb_B_12_151_0 ; } _rtB -> B_12_39_0 = _rtB -> B_12_85_0 * 3.1415926535897931
* 6.4000000000000011E-5 * _rtB -> B_12_26_0 * _rtB -> B_12_38_0 / ( 287.0 *
_rtB -> B_12_86_0_l ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Saturation_MODE = _rtB -> B_12_39_0 >= _rtP -> P_40 ? 1 : _rtB -> B_12_39_0 >
_rtP -> P_41 ? 0 : - 1 ; } _rtB -> B_12_40_0 = _rtDW -> Saturation_MODE == 1
? _rtP -> P_40 : _rtDW -> Saturation_MODE == - 1 ? _rtP -> P_41 : _rtB ->
B_12_39_0 ; _rtB -> B_12_41_0 = _rtP -> P_42 * _rtB -> B_12_40_0 ;
ssCallAccelRunBlock ( S , 12 , 42 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_12_43_0
= _rtP -> P_43 * _rtB -> B_12_27_0 ; ssCallAccelRunBlock ( S , 12 , 44 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { if ( _rtX ->
Integrator1_CSTATE_c >= _rtP -> P_45 ) { if ( _rtX -> Integrator1_CSTATE_c !=
_rtP -> P_45 ) { _rtX -> Integrator1_CSTATE_c = _rtP -> P_45 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator1_MODE_g = 3 ; } else if ( _rtX -> Integrator1_CSTATE_c <= _rtP ->
P_46 ) { if ( _rtX -> Integrator1_CSTATE_c != _rtP -> P_46 ) { _rtX ->
Integrator1_CSTATE_c = _rtP -> P_46 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator1_MODE_g = 4 ; } else { if ( _rtDW -> Integrator1_MODE_g != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integrator1_MODE_g = 0 ; } _rtB -> B_12_45_0 = _rtX -> Integrator1_CSTATE_c ;
} else { _rtB -> B_12_45_0 = _rtX -> Integrator1_CSTATE_c ; } _rtB ->
B_12_46_0 = _rtP -> P_47 * _rtB -> B_12_45_0 ; _rtB -> B_12_47_0 = _rtP ->
P_48 * _rtB -> B_12_46_0 ; ssCallAccelRunBlock ( S , 12 , 48 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { _rtB -> B_12_49_0 = _rtDW -> Memory4_PreviousInput ; } _rtB -> B_12_50_0
= ssGetT ( S ) ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 11 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_12_52_0
= _rtP -> P_50 * _rtB -> B_11_0_2 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ;
if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 12 , 53 , SS_CALL_MDL_OUTPUTS )
; } ssCallAccelRunBlock ( S , 12 , 54 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 55 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 12 , 56 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_12_57_0
. ID = 419361278U ; _rtB -> B_12_57_0 . Length = 8U ; _rtB -> B_12_57_0 .
Extended = 1U ; _rtB -> B_12_57_0 . Remote = 0 ; _rtB -> B_12_57_0 . Data [ 0
] = 0 ; _rtB -> B_12_57_0 . Data [ 1 ] = 0 ; _rtB -> B_12_57_0 . Data [ 2 ] =
0 ; _rtB -> B_12_57_0 . Data [ 3 ] = 0 ; _rtB -> B_12_57_0 . Data [ 4 ] = 0 ;
_rtB -> B_12_57_0 . Data [ 5 ] = 0 ; _rtB -> B_12_57_0 . Data [ 6 ] = 0 ;
_rtB -> B_12_57_0 . Data [ 7 ] = 0 ; { { uint32_T packingValue = 0 ; {
uint32_T result = ( uint32_T ) ( _rtB -> B_12_35_0_n ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 3 ] = _rtB -> B_12_57_0 .
Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 4 ) ) ; } } } } { real_T outValue = 0 ; { real_T result =
_rtB -> B_11_0_1 ; outValue = round ( result ) ; } { uint8_T packedValue ; if
( outValue > ( real_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if (
outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else {
packedValue = ( uint8_T ) ( outValue ) ; } { { _rtB -> B_12_57_0 . Data [ 3 ]
= _rtB -> B_12_57_0 . Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_36_0_m ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 4 ] = _rtB -> B_12_57_0 .
Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( _rtB -> B_12_37_0_c ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue
= ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) {
packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 3 ] = _rtB -> B_12_57_0 .
Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB
-> B_12_38_0_m ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 .
Data [ 4 ] = _rtB -> B_12_57_0 . Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_32_0_n ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 3 ] = _rtB
-> B_12_57_0 . Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_33_0_i ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 0 ] = _rtB -> B_12_57_0 .
Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( _rtB -> B_12_34_0_o ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue
= ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) {
packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 4 ] = _rtB -> B_12_57_0 .
Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( _rtB -> B_12_31_0_o ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 255 ) ) {
packedValue = ( uint8_T ) 255 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 5 ] = _rtB -> B_12_57_0 .
Data [ 5 ] | ( uint8_T ) ( packedValue ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_20_0_d ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 4 ] = _rtB -> B_12_57_0 .
Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB
-> B_12_21_0_e ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 7 ) ) { packedValue = ( uint8_T ) 7 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 .
Data [ 6 ] = _rtB -> B_12_57_0 . Data [ 6 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x7U ) << 5 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_22_0 ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 7 ] = _rtB
-> B_12_57_0 . Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_23_0_b ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 7 ] = _rtB -> B_12_57_0 .
Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB
-> B_12_24_0_j ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 .
Data [ 7 ] = _rtB -> B_12_57_0 . Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_25_0 ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 7 ] = _rtB
-> B_12_57_0 . Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_26_0_f ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 31 ) )
{ packedValue = ( uint8_T ) 31 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 6 ] = _rtB -> B_12_57_0 .
Data [ 6 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x1FU ) )
; } } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) (
_rtB -> B_12_27_0_a ) ; packingValue = result ; } { uint8_T packedValue ; if
( packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 .
Data [ 0 ] = _rtB -> B_12_57_0 . Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_28_0_j ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 0 ] = _rtB
-> B_12_57_0 . Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( _rtB -> B_12_29_0_j ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { _rtB -> B_12_57_0 . Data [ 0 ] = _rtB -> B_12_57_0 .
Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { real_T outValue = 0 ; { real_T result = _rtB -> B_12_2_0 ; result =
result * ( 1 / 0.0039062 ) ; outValue = round ( result ) ; } { uint16_T
packedValue ; if ( outValue > ( real_T ) ( 65535 ) ) { packedValue = (
uint16_T ) 65535 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue =
( uint16_T ) 0 ; } else { packedValue = ( uint16_T ) ( outValue ) ; } { {
_rtB -> B_12_57_0 . Data [ 1 ] = _rtB -> B_12_57_0 . Data [ 1 ] | ( uint8_T )
( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ) ; _rtB -> B_12_57_0 .
Data [ 2 ] = _rtB -> B_12_57_0 . Data [ 2 ] | ( uint8_T ) ( ( uint16_T ) ( (
uint16_T ) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ) ; } } } } } { if (
_rtDW -> _asyncqueue_inserted_for_ToWorkspace_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace_PWORK . AQHandles , ssGetTaskTime ( S ,
0 ) , ( char * ) & _rtB -> B_12_57_0 + 0 ) ; } } isHit = ssIsSampleHit ( S ,
3 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 12 , 59 ,
SS_CALL_MDL_OUTPUTS ) ; } _rtB -> B_12_60_0 = _rtP -> P_51 * _rtB ->
B_12_26_0 ; _rtB -> B_12_61_0 = _rtX -> Integrator_CSTATE_h ; _rtB ->
B_12_62_0 = _rtX -> Integrator_CSTATE_hj ; isHit = ssIsSampleHit ( S , 1 , 0
) ; if ( isHit != 0 ) { if ( _rtDW -> Memory3_PreviousInput > _rtP -> P_55 )
{ _rtB -> B_12_64_0 = _rtP -> P_55 ; } else if ( _rtDW ->
Memory3_PreviousInput < _rtP -> P_56 ) { _rtB -> B_12_64_0 = _rtP -> P_56 ; }
else { _rtB -> B_12_64_0 = _rtDW -> Memory3_PreviousInput ; } } if ( _rtB ->
B_12_69_0_l >= _rtP -> P_57 ) { _rtB -> B_8_0_0 = _rtP -> P_14 * _rtB ->
B_12_62_0 ; _rtB -> B_8_1_0 = _rtP -> P_15 * _rtB -> B_12_61_0 ; _rtB ->
B_8_2_0 = _rtB -> B_8_1_0 - _rtB -> B_8_0_0 ; _rtB -> B_12_66_0 = _rtB ->
B_8_2_0 ; } else { _rtB -> B_12_66_0 = _rtB -> B_12_64_0 ; } if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_66_0 ; _rtDW
-> MinMax1_MODE_e = 0 ; if ( ( _rtB -> B_12_66_0 != _rtB -> B_12_66_0 ) || (
_rtB -> B_12_71_0_d < _rtB -> B_12_66_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_71_0_d ; _rtDW -> MinMax1_MODE_e = 1 ; } _rtB -> B_12_67_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_66_0 ; if ( _rtDW ->
MinMax1_MODE_e == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_71_0_d ; } _rtB ->
B_12_67_0 = rtb_B_12_151_0 ; } _rtB -> B_12_68_0 = _rtP -> P_58 [ 0 ] ; _rtB
-> B_12_68_0 = _rtB -> B_12_68_0 * _rtB -> B_12_67_0 + _rtP -> P_58 [ 1 ] ;
_rtB -> B_12_68_0 = _rtB -> B_12_68_0 * _rtB -> B_12_67_0 + _rtP -> P_58 [ 2
] ; if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_68_0
; _rtDW -> MinMax_MODE_h = 0 ; if ( ( _rtB -> B_12_68_0 != _rtB -> B_12_68_0
) || ( _rtB -> B_12_70_0_j > _rtB -> B_12_68_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_70_0_j ; _rtDW -> MinMax_MODE_h = 1 ; } _rtB -> B_12_69_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_68_0 ; if ( _rtDW ->
MinMax_MODE_h == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_70_0_j ; } _rtB ->
B_12_69_0 = rtb_B_12_151_0 ; } if ( ssIsModeUpdateTimeStep ( S ) ) { if (
_rtX -> Integratorp_em_CSTATE >= _rtP -> P_60 ) { if ( _rtX ->
Integratorp_em_CSTATE != _rtP -> P_60 ) { _rtX -> Integratorp_em_CSTATE =
_rtP -> P_60 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratorp_em_MODE = 3 ; } else if ( _rtX -> Integratorp_em_CSTATE <= _rtP
-> P_61 ) { if ( _rtX -> Integratorp_em_CSTATE != _rtP -> P_61 ) { _rtX ->
Integratorp_em_CSTATE = _rtP -> P_61 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratorp_em_MODE = 4 ; } else { if ( _rtDW -> Integratorp_em_MODE != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Integratorp_em_MODE = 0 ; } _rtB -> B_12_70_0 = _rtX -> Integratorp_em_CSTATE
; } else { _rtB -> B_12_70_0 = _rtX -> Integratorp_em_CSTATE ; } _rtB ->
B_12_71_0 = _rtB -> B_12_27_0 / _rtB -> B_12_70_0 ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Saturation_MODE_a = _rtB ->
B_12_71_0 >= _rtP -> P_62 ? 1 : _rtB -> B_12_71_0 > _rtP -> P_63 ? 0 : - 1 ;
} _rtB -> B_12_72_0 = _rtDW -> Saturation_MODE_a == 1 ? _rtP -> P_62 : _rtDW
-> Saturation_MODE_a == - 1 ? _rtP -> P_63 : _rtB -> B_12_71_0 ; _rtB ->
B_12_74_0 = _rtB -> B_12_70_0 / _rtB -> B_12_27_0 ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Saturation1_MODE = _rtB ->
B_12_46_0 >= _rtP -> P_64 ? 1 : _rtB -> B_12_46_0 > _rtP -> P_65 ? 0 : - 1 ;
} _rtB -> B_12_75_0 = _rtDW -> Saturation1_MODE == 1 ? _rtP -> P_64 : _rtDW
-> Saturation1_MODE == - 1 ? _rtP -> P_65 : _rtB -> B_12_46_0 ; _rtB ->
B_12_76_0 = look1_binlxpw ( _rtB -> B_12_75_0 , _rtP -> P_67 , _rtP -> P_66 ,
32U ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { taskTimeV =
_rtB -> B_11_0_1 * _rtDW -> Memory2_PreviousInput ; if ( taskTimeV > _rtP ->
P_69 ) { _rtB -> B_12_79_0 = _rtP -> P_69 ; } else if ( taskTimeV < _rtP ->
P_70 ) { _rtB -> B_12_79_0 = _rtP -> P_70 ; } else { _rtB -> B_12_79_0 =
taskTimeV ; } } if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB
-> B_12_76_0 ; _rtDW -> MinMax_MODE_c = 0 ; if ( ( _rtB -> B_12_76_0 != _rtB
-> B_12_76_0 ) || ( _rtB -> B_12_79_0 < _rtB -> B_12_76_0 ) ) {
rtb_B_12_151_0 = _rtB -> B_12_79_0 ; _rtDW -> MinMax_MODE_c = 1 ; } _rtB ->
B_12_80_0 = rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_76_0 ; if
( _rtDW -> MinMax_MODE_c == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_79_0 ; } _rtB
-> B_12_80_0 = rtb_B_12_151_0 ; } _rtB -> B_12_81_0 = _rtB -> B_12_60_0_c *
_rtB -> B_12_80_0 * _rtB -> B_12_75_0 ; if ( _rtB -> B_12_27_0 < 0.0 ) {
rtb_B_12_151_0 = - muDoubleScalarSqrt ( - _rtB -> B_12_27_0 ) ; } else {
rtb_B_12_151_0 = muDoubleScalarSqrt ( _rtB -> B_12_27_0 ) ; } if ( _rtB ->
B_12_75_0 < 0.0 ) { tmp = - muDoubleScalarSqrt ( - _rtB -> B_12_75_0 ) ; }
else { tmp = muDoubleScalarSqrt ( _rtB -> B_12_75_0 ) ; } _rtB -> B_12_83_0 =
( ( - 0.00020816619843224996 * rtb_B_12_151_0 + - 0.0034465158052700592 * tmp
) + 1.1497021021059144 ) * _rtB -> B_12_27_0 * _rtB -> B_12_75_0 / _rtB ->
B_12_72_0_g * _rtB -> B_12_61_0_f ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_12_84_0 = _rtDW -> x_rOld_PreviousInput ; }
taskTimeV = _rtB -> B_12_81_0 * 42900000.0 * ( 1.0 - _rtB -> B_12_84_0 ) / (
_rtB -> B_12_81_0 + _rtB -> B_12_83_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 )
; if ( isHit != 0 ) { _rtB -> B_12_86_0 = _rtDW -> T_1Old_PreviousInput ; }
ratio = taskTimeV * 2.3370584441920436e-14 / ( 724.0 * _rtB -> B_12_86_0 *
3.0744032413269453 ) + 1.0 ; if ( _rtB -> B_12_74_0 < 0.0 ) { rtb_B_12_151_0
= - muDoubleScalarPower ( - _rtB -> B_12_74_0 , 0.28387734915924823 ) ; }
else { rtb_B_12_151_0 = muDoubleScalarPower ( _rtB -> B_12_74_0 ,
0.28387734915924823 ) ; } if ( ratio < 0.0 ) { tmp = - muDoubleScalarPower (
- ratio , - 0.28387734915924823 ) ; } else { tmp = muDoubleScalarPower (
ratio , - 0.28387734915924823 ) ; } _rtB -> B_12_88_0 = 1.1015294624801442 *
rtb_B_12_151_0 * 0.32526637578237438 * tmp * ( taskTimeV *
0.00098911968348171036 + _rtB -> B_12_86_0 * 3.0744032413269453 ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_62_0_g ; _rtDW
-> MinMax_MODE_p = 0 ; if ( ( _rtB -> B_12_62_0_g != _rtB -> B_12_62_0_g ) ||
( _rtB -> B_12_88_0 < _rtB -> B_12_62_0_g ) ) { rtb_B_12_151_0 = _rtB ->
B_12_88_0 ; _rtDW -> MinMax_MODE_p = 1 ; } _rtB -> B_12_89_0 = rtb_B_12_151_0
; } else { rtb_B_12_151_0 = _rtB -> B_12_62_0_g ; if ( _rtDW -> MinMax_MODE_p
== 1 ) { rtb_B_12_151_0 = _rtB -> B_12_88_0 ; } _rtB -> B_12_89_0 =
rtb_B_12_151_0 ; } _rtB -> B_12_90_0 = _rtB -> B_12_83_0 + _rtB -> B_12_81_0
; _rtB -> B_12_91_0 = muDoubleScalarExp ( - 60.491655470984995 / ( _rtB ->
B_12_90_0 * 1332.0 ) ) * ( _rtB -> B_12_89_0 - 298.46362195121958 ) +
298.46362195121958 ; rtb_B_12_151_0 = _rtB -> B_12_91_0 * 286.0 ; if (
rtb_B_12_151_0 < 0.0 ) { rtb_B_12_151_0 = - muDoubleScalarSqrt ( -
rtb_B_12_151_0 ) ; } else { rtb_B_12_151_0 = muDoubleScalarSqrt (
rtb_B_12_151_0 ) ; } _rtB -> B_12_92_0 = ( 1.0 - muDoubleScalarPower ( ( 1.0
- _rtB -> B_12_72_0 ) / 0.34999595167386044 - 1.0 , 2.0 ) ) * ( 0.0004 * _rtB
-> B_12_69_0 * _rtB -> B_12_70_0 ) / rtb_B_12_151_0 ; _rtB -> B_12_93_0 =
_rtB -> B_12_40_0 + _rtB -> B_12_92_0 ; _rtB -> B_12_94_0 = _rtB -> B_12_92_0
/ _rtB -> B_12_93_0 ; if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 =
_rtB -> B_12_81_0 ; _rtDW -> Max1_MODE = 0 ; if ( ( _rtB -> B_12_81_0 != _rtB
-> B_12_81_0 ) || ( _rtB -> B_12_68_0_p > _rtB -> B_12_81_0 ) ) {
rtb_B_12_151_0 = _rtB -> B_12_68_0_p ; _rtDW -> Max1_MODE = 1 ; } _rtB ->
B_12_95_0 = rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_81_0 ; if
( _rtDW -> Max1_MODE == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_68_0_p ; } _rtB
-> B_12_95_0 = rtb_B_12_151_0 ; } if ( ssIsModeUpdateTimeStep ( S ) ) { if (
_rtX -> IntegratorX_Oim_CSTATE >= _rtP -> P_74 ) { if ( _rtX ->
IntegratorX_Oim_CSTATE != _rtP -> P_74 ) { _rtX -> IntegratorX_Oim_CSTATE =
_rtP -> P_74 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
IntegratorX_Oim_MODE = 3 ; } else if ( _rtX -> IntegratorX_Oim_CSTATE <= _rtP
-> P_75 ) { if ( _rtX -> IntegratorX_Oim_CSTATE != _rtP -> P_75 ) { _rtX ->
IntegratorX_Oim_CSTATE = _rtP -> P_75 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
IntegratorX_Oim_MODE = 4 ; } else { if ( _rtDW -> IntegratorX_Oim_MODE != 0 )
{ ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
IntegratorX_Oim_MODE = 0 ; } _rtB -> B_12_96_0 = _rtX ->
IntegratorX_Oim_CSTATE ; } else { _rtB -> B_12_96_0 = _rtX ->
IntegratorX_Oim_CSTATE ; } _rtB -> B_12_97_0 = 1.0 / _rtB -> B_12_66_0_m *
_rtB -> B_12_83_0 / _rtB -> B_12_95_0 * _rtB -> B_12_96_0 ; _rtB -> B_12_98_0
= look_SplNBinXScd ( 1U , & _rtB -> B_12_18_0 , ( rt_LUTSplineWork * ) &
_rtDW -> SWork [ 0 ] ) ; isHit = ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit !=
0 ) { ssCallAccelRunBlock ( S , 6 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 6 , 1 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock
( S , 6 , 2 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 3 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 5 , 0 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 6 , 5 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 6 , 6 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock
( S , 6 , 7 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 8 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 9 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 3 , 0 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_Gearcontrol_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Gearcontrol_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 4 ) , ( char * ) & _rtB -> B_3_0_1 + 0 ) ; } }
ssCallAccelRunBlock ( S , 4 , 0 , SS_CALL_MDL_OUTPUTS ) ; if ( _rtB ->
B_4_0_1 > _rtP -> P_6 ) { _rtB -> B_6_13_0 = _rtP -> P_6 ; } else if ( _rtB
-> B_4_0_1 < _rtP -> P_7 ) { _rtB -> B_6_13_0 = _rtP -> P_7 ; } else { _rtB
-> B_6_13_0 = _rtB -> B_4_0_1 ; } { if ( _rtDW ->
TAQSigLogging_InsertedFor_Saturation_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Saturation_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 4 ) , ( char * ) & _rtB -> B_6_13_0 + 0 ) ; } } _rtB ->
B_6_15_0 = _rtB -> B_6_5_0 ; _rtB -> B_6_16_0 = _rtB -> B_6_6_0 ; _rtB ->
B_6_17_0 = _rtB -> B_6_7_0 ; _rtB -> B_6_18_0 = ssGetTaskTime ( S , 4 ) ;
ssCallAccelRunBlock ( S , 6 , 19 , SS_CALL_MDL_OUTPUTS ) ; _rtDW ->
Controller_SubsysRanBC = 4 ; } _rtB -> B_12_101_0 = _rtX ->
Integrator_CSTATE_f ; ssCallAccelRunBlock ( S , 12 , 102 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_12_103_0 = _rtX -> Integrator_CSTATE_k ;
ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock
( S , 12 , 105 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 106 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0
= _rtB -> B_12_97_0 ; _rtDW -> MinMax_MODE_d = 0 ; if ( ( _rtB -> B_12_97_0
!= _rtB -> B_12_97_0 ) || ( _rtB -> B_12_63_0 < _rtB -> B_12_97_0 ) ) {
rtb_B_12_151_0 = _rtB -> B_12_63_0 ; _rtDW -> MinMax_MODE_d = 1 ; } _rtB ->
B_12_107_0 = rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_97_0 ;
if ( _rtDW -> MinMax_MODE_d == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_63_0 ; }
_rtB -> B_12_107_0 = rtb_B_12_151_0 ; } _rtB -> B_12_108_0 = _rtP -> P_80 *
_rtB -> B_12_107_0 ; _rtB -> B_12_109_0 = _rtB -> B_12_108_0 * _rtB ->
B_12_65_0 * _rtB -> B_12_80_0 * _rtB -> B_12_64_0_g ; _rtB -> B_12_110_0 =
_rtB -> B_12_70_0 - _rtB -> B_12_27_0 ; _rtB -> B_12_111_0 = _rtP -> P_81 *
_rtB -> B_12_110_0 ; _rtB -> B_12_112_0 = _rtP -> P_82 * _rtB -> B_12_75_0 ;
_rtB -> B_12_113_0 = _rtP -> P_83 [ 0 ] ; _rtB -> B_12_113_0 = _rtB ->
B_12_113_0 * _rtB -> B_12_112_0 + _rtP -> P_83 [ 1 ] ; _rtB -> B_12_113_0 =
_rtB -> B_12_113_0 * _rtB -> B_12_112_0 + _rtP -> P_83 [ 2 ] ; _rtB ->
B_12_114_0 = _rtP -> P_84 * _rtB -> B_12_113_0 ; _rtB -> B_12_115_0 = ( _rtB
-> B_12_109_0 - _rtB -> B_12_111_0 ) - _rtB -> B_12_114_0 ; _rtB ->
B_12_116_0 = _rtP -> P_85 * _rtB -> B_12_115_0 ; ssCallAccelRunBlock ( S , 12
, 117 , SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_Fuelconsumptiondm3100km_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Fuelconsumptiondm3100km_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_0_1 + 0 ) ; }
} } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_TransmissionControlUnit_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_TransmissionControlUnit_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 2 ) , ( char * ) & _rtB -> B_11_0_1 + 0 ) ; }
} { if ( _rtDW ->
TAQSigLogging_InsertedFor_TransmissionControlUnit_at_outport_1_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_TransmissionControlUnit_at_outport_1_PWORK .
AQHandles , ssGetTaskTime ( S , 2 ) , ( char * ) & _rtB -> B_11_0_2 + 0 ) ; }
} } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_radsRPM_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_radsRPM_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_46_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_Integrator1_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Integrator1_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_18_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_mskmh_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_mskmh_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_2_0 + 0 ) ; } } } _rtB ->
B_12_125_0 = _rtB -> B_12_1_0 * _rtB -> B_12_1_0 * _rtP -> P_86 ; isHit =
ssIsSampleHit ( S , 4 , 0 ) ; if ( isHit != 0 ) { if ( _rtB -> B_6_17_0 >
_rtP -> P_87 ) { rtb_B_12_151_0 = _rtP -> P_87 ; } else if ( _rtB -> B_6_17_0
< _rtP -> P_88 ) { rtb_B_12_151_0 = _rtP -> P_88 ; } else { rtb_B_12_151_0 =
_rtB -> B_6_17_0 ; } _rtB -> B_12_128_0 = muDoubleScalarMin ( _rtP -> P_89 *
rtb_B_12_151_0 , _rtB -> B_12_58_0 ) ; } _rtB -> B_12_129_0 = _rtB ->
B_12_1_0 * _rtB -> B_12_56_0 ; _rtB -> B_12_131_0 = _rtB -> B_12_129_0 * _rtB
-> B_12_129_0 * _rtB -> B_12_55_0 ; _rtB -> B_12_132_0 = _rtB -> B_12_131_0 +
_rtB -> B_12_54_0 ; _rtB -> B_12_134_0 = muDoubleScalarCos ( _rtB ->
B_12_98_0 ) * _rtB -> B_12_57_0_b ; _rtB -> B_12_135_0 = _rtB -> B_12_132_0 *
_rtB -> B_12_134_0 ; _rtB -> B_12_137_0 = muDoubleScalarSin ( _rtB ->
B_12_98_0 ) * _rtB -> B_12_53_0 ; _rtB -> B_12_138_0 = ( ( _rtB -> B_12_128_0
+ _rtB -> B_12_125_0 ) + _rtB -> B_12_135_0 ) + _rtB -> B_12_137_0 ; _rtB ->
B_12_139_0 = _rtP -> P_90 * _rtB -> B_12_138_0 ; isHit = ssIsSampleHit ( S ,
2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_12_141_0 = _rtP -> P_93 * rt_Lookup (
& _rtP -> P_91 [ 0 ] , 15 , _rtB -> B_11_0_2 , & _rtP -> P_92 [ 0 ] ) ; }
_rtB -> B_12_142_0 = ( _rtB -> B_12_116_0 * _rtB -> B_12_52_0_c /
muDoubleScalarPower ( _rtB -> B_12_141_0 , 2.0 ) + _rtB -> B_12_59_0_p * _rtB
-> B_12_139_0 / _rtB -> B_12_141_0 ) / ( _rtB -> B_12_52_0_c /
muDoubleScalarPower ( _rtB -> B_12_141_0 , 2.0 ) + _rtB -> B_12_59_0_p ) ;
_rtB -> B_12_144_0 = _rtB -> B_12_45_0 - _rtB -> B_12_0_0 * _rtB ->
B_12_141_0 ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Abs_MODE = ( _rtB
-> B_12_144_0 >= 0.0 ) ; } _rtB -> B_12_145_0 = _rtDW -> Abs_MODE > 0 ? _rtB
-> B_12_144_0 : - _rtB -> B_12_144_0 ; if ( ssIsModeUpdateTimeStep ( S ) ) {
_rtDW -> Relay1_Mode = ( ( _rtB -> B_12_145_0 >= _rtP -> P_94 ) || ( ( ! (
_rtB -> B_12_145_0 <= _rtP -> P_95 ) ) && _rtDW -> Relay1_Mode ) ) ; } if (
_rtDW -> Relay1_Mode ) { _rtB -> B_12_146_0 = _rtP -> P_96 ; } else { _rtB ->
B_12_146_0 = _rtP -> P_97 ; } if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Abs_MODE_f = ( _rtB -> B_12_142_0 >= 0.0 ) ; } _rtB -> B_12_147_0 = _rtDW ->
Abs_MODE_f > 0 ? _rtB -> B_12_142_0 : - _rtB -> B_12_142_0 ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_12_148_0 = _rtP
-> P_98 * _rtB -> B_11_0_1 ; _rtB -> B_12_150_0 = ( _rtB -> B_12_141_0 >
TruckBenchmark_rtC ( S ) -> B_12_0_0 ) ; } if ( ssIsModeUpdateTimeStep ( S )
) { _rtDW -> Relay2_Mode = ( ( _rtB -> B_12_144_0 >= _rtP -> P_99 ) || ( ( !
( _rtB -> B_12_144_0 <= _rtP -> P_100 ) ) && _rtDW -> Relay2_Mode ) ) ; } if
( _rtDW -> Relay2_Mode ) { rtb_B_12_151_0 = _rtP -> P_101 ; } else {
rtb_B_12_151_0 = _rtP -> P_102 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_12_152_0 = _rtB -> B_12_148_0 * _rtB -> B_12_150_0 *
rtb_B_12_151_0 ; _rtB -> B_12_153_0 = muDoubleScalarAbs ( _rtB -> B_12_152_0
) ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode =
( _rtB -> B_12_147_0 < _rtB -> B_12_153_0 ) ; } _rtB -> B_12_155_0 = ( ( _rtB
-> B_12_146_0 != 0.0 ) && _rtDW -> RelationalOperator_Mode ) ; } if ( _rtB ->
B_12_155_0 ) { _rtB -> B_12_156_0 = _rtB -> B_12_142_0 ; } else { _rtB ->
B_12_156_0 = _rtB -> B_12_152_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_ClutchTransfer_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_ClutchTransfer_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_156_0 + 0 ) ; } } { if (
_rtDW ->
TAQSigLogging_InsertedFor_SpeedDifferenceClutchLimits_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_SpeedDifferenceClutchLimits_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_146_0 + 0 ) ;
} } { if ( _rtDW ->
TAQSigLogging_InsertedFor_SpeedDifferenceClutchLimits_at_outport_1_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_SpeedDifferenceClutchLimits_at_outport_1_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_152_0 + 0 ) ;
} } } _rtB -> B_12_160_0 = _rtB -> B_12_116_0 - _rtB -> B_12_156_0 ; _rtB ->
B_12_161_0 = _rtB -> B_12_160_0 / _rtB -> B_12_59_0_p ; isHit = ssIsSampleHit
( S , 1 , 0 ) ; if ( isHit != 0 ) { rtb_B_12_162_0 [ 0 ] = _rtB -> B_12_152_0
; rtb_B_12_162_0 [ 1 ] = rtb_B_12_151_0 ; rtb_B_12_162_0 [ 2 ] = _rtB ->
B_12_146_0 ; { if ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace_PWORK_e .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace_PWORK_e . AQHandles , ssGetTaskTime ( S
, 1 ) , ( char * ) & rtb_B_12_162_0 [ 0 ] + 0 ) ; } } } _rtB -> B_12_164_0 =
_rtB -> B_12_156_0 * _rtB -> B_12_141_0 ; _rtB -> B_12_165_0 = _rtB ->
B_12_164_0 - _rtB -> B_12_139_0 ; _rtB -> B_12_166_0 = _rtB -> B_12_165_0 /
_rtB -> B_12_52_0_c ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ { if ( _rtDW -> TAQSigLogging_InsertedFor_lambda_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_lambda_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_97_0 + 0 ) ; } } } if (
_rtB -> B_12_74_0 < 0.0 ) { rtb_B_12_151_0 = - muDoubleScalarPower ( - _rtB
-> B_12_74_0 , 0.71612265084075177 ) ; } else { rtb_B_12_151_0 =
muDoubleScalarPower ( _rtB -> B_12_74_0 , 0.71612265084075177 ) ; } if (
ratio < 0.0 ) { tmp = - muDoubleScalarPower ( - ratio , - 0.71612265084075177
) ; } else { tmp = muDoubleScalarPower ( ratio , - 0.71612265084075177 ) ; }
_rtB -> B_12_169_0 = rtb_B_12_151_0 * tmp / ( ( taskTimeV *
0.99999999999997657 / ( ( taskTimeV * 2.3370584441920436e-14 / 724.0 + _rtB
-> B_12_86_0 * 3.0744032413269453 ) * 1011.0 ) + 1.0 ) * 17.0 ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Saturation_MODE_a1 = _rtB ->
B_12_169_0 >= _rtP -> P_103 ? 1 : _rtB -> B_12_169_0 > _rtP -> P_104 ? 0 : -
1 ; } _rtB -> B_12_170_0 = _rtDW -> Saturation_MODE_a1 == 1 ? _rtP -> P_103 :
_rtDW -> Saturation_MODE_a1 == - 1 ? _rtP -> P_104 : _rtB -> B_12_169_0 ;
_rtB -> B_12_171_0 = ( 1.0 - _rtB -> B_12_170_0 ) * _rtB -> B_12_72_0_g +
_rtB -> B_12_170_0 * _rtB -> B_12_89_0 ; if ( ssIsModeUpdateTimeStep ( S ) )
{ _rtDW -> Saturation1_MODE_k = _rtB -> B_12_171_0 >= _rtP -> P_105 ? 1 :
_rtB -> B_12_171_0 > _rtP -> P_106 ? 0 : - 1 ; } _rtB -> B_12_172_0 = _rtDW
-> Saturation1_MODE_k == 1 ? _rtP -> P_105 : _rtDW -> Saturation1_MODE_k == -
1 ? _rtP -> P_106 : _rtB -> B_12_171_0 ; _rtB -> B_12_173_0 = ( _rtB ->
B_12_83_0 * _rtB -> B_12_96_0 - _rtB -> B_12_95_0 * 14.57 * 0.2314 ) / ( _rtB
-> B_12_83_0 + _rtB -> B_12_95_0 ) ; if ( ssIsModeUpdateTimeStep ( S ) ) {
rtb_B_12_151_0 = _rtB -> B_12_173_0 ; _rtDW -> MinMax_MODE_pf = 0 ; if ( (
_rtB -> B_12_173_0 != _rtB -> B_12_173_0 ) || ( _rtB -> B_12_67_0_n > _rtB ->
B_12_173_0 ) ) { rtb_B_12_151_0 = _rtB -> B_12_67_0_n ; _rtDW ->
MinMax_MODE_pf = 1 ; } _rtB -> B_12_174_0 = rtb_B_12_151_0 ; } else {
rtb_B_12_151_0 = _rtB -> B_12_173_0 ; if ( _rtDW -> MinMax_MODE_pf == 1 ) {
rtb_B_12_151_0 = _rtB -> B_12_67_0_n ; } _rtB -> B_12_174_0 = rtb_B_12_151_0
; } { real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - _rtP -> P_107 ; _rtB -> B_12_175_0 =
TruckBenchmark_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer ,
_rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW ->
TransportDelay_IWORK . Head , _rtP -> P_108 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK . Head ] == ssGetT ( S ) )
) ) ; } _rtB -> B_12_176_0 = _rtB -> B_12_175_0 - _rtB -> B_12_61_0 ; _rtB ->
B_12_177_0 = _rtP -> P_109 * _rtB -> B_12_176_0 ; _rtB -> B_12_178_0 = _rtB
-> B_12_175_0 - _rtB -> B_12_62_0 ; _rtB -> B_12_179_0 = _rtP -> P_110 * _rtB
-> B_12_178_0 ; _rtB -> B_12_180_0 = _rtB -> B_12_85_0 / _rtB -> B_12_70_0 ;
if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_180_0 ;
_rtDW -> MinMax_MODE_n = 0 ; if ( ( _rtB -> B_12_180_0 != _rtB -> B_12_180_0
) || ( _rtB -> B_12_81_0_b < _rtB -> B_12_180_0 ) ) { rtb_B_12_151_0 = _rtB
-> B_12_81_0_b ; _rtDW -> MinMax_MODE_n = 1 ; } _rtB -> B_12_181_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_180_0 ; if ( _rtDW ->
MinMax_MODE_n == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_81_0_b ; } _rtB ->
B_12_181_0 = rtb_B_12_151_0 ; } _rtB -> B_12_182_0 = _rtX ->
Integrator_CSTATE_j ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 )
{ if ( _rtDW -> Memory1_PreviousInput > _rtP -> P_113 ) { _rtB -> B_12_184_0
= _rtP -> P_113 ; } else if ( _rtDW -> Memory1_PreviousInput < _rtP -> P_114
) { _rtB -> B_12_184_0 = _rtP -> P_114 ; } else { _rtB -> B_12_184_0 = _rtDW
-> Memory1_PreviousInput ; } } if ( _rtB -> B_12_80_0_o >= _rtP -> P_115 ) {
_rtB -> B_12_185_0 = _rtB -> B_12_182_0 ; } else { _rtB -> B_12_185_0 = _rtB
-> B_12_184_0 ; } _rtB -> B_12_186_0 = 1.0 - muDoubleScalarPower ( ( _rtB ->
B_12_185_0 - 117.14474688230767 ) / 126.87193572285548 , 2.0 ) ; if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_186_0 ; _rtDW
-> MinMax_MODE_m = 0 ; if ( ( _rtB -> B_12_186_0 != _rtB -> B_12_186_0 ) || (
_rtB -> B_12_82_0 > _rtB -> B_12_186_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_82_0 ; _rtDW -> MinMax_MODE_m = 1 ; } _rtB -> B_12_187_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_186_0 ; if ( _rtDW ->
MinMax_MODE_m == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_82_0 ; } _rtB ->
B_12_187_0 = rtb_B_12_151_0 ; } if ( _rtB -> B_12_187_0 < 0.0 ) {
rtb_B_12_151_0 = - muDoubleScalarSqrt ( - _rtB -> B_12_187_0 ) ; } else {
rtb_B_12_151_0 = muDoubleScalarSqrt ( _rtB -> B_12_187_0 ) ; } _rtB ->
B_12_188_0 = 1.9479627004385558 * rtb_B_12_151_0 - 0.77631189328675043 ; if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_188_0 ; _rtDW
-> MinMax1_MODE_l = 0 ; if ( ( _rtB -> B_12_188_0 != _rtB -> B_12_188_0 ) ||
( _rtB -> B_12_83_0_n > _rtB -> B_12_188_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_83_0_n ; _rtDW -> MinMax1_MODE_l = 1 ; } _rtB -> B_12_189_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_188_0 ; if ( _rtDW ->
MinMax1_MODE_l == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_83_0_n ; } _rtB ->
B_12_189_0 = rtb_B_12_151_0 ; } if ( _rtB -> B_12_181_0 < 0.0 ) { tmp = -
muDoubleScalarPower ( - _rtB -> B_12_181_0 , 2.89019266110711 ) ; } else {
tmp = muDoubleScalarPower ( _rtB -> B_12_181_0 , 2.89019266110711 ) ; }
rtb_B_12_151_0 = _rtB -> B_12_91_0 * 286.0 ; if ( 1.0 - tmp < 0.0 ) { tmp = -
muDoubleScalarSqrt ( - ( 1.0 - tmp ) ) ; } else { tmp = muDoubleScalarSqrt (
1.0 - tmp ) ; } if ( rtb_B_12_151_0 < 0.0 ) { rtb_B_12_151_0 = -
muDoubleScalarSqrt ( - rtb_B_12_151_0 ) ; } else { rtb_B_12_151_0 =
muDoubleScalarSqrt ( rtb_B_12_151_0 ) ; } _rtB -> B_12_190_0 =
0.00084557672626438816 * _rtB -> B_12_70_0 * tmp * _rtB -> B_12_189_0 /
rtb_B_12_151_0 ; _rtB -> B_12_191_0 = ( _rtB -> B_12_90_0 - _rtB ->
B_12_190_0 ) - _rtB -> B_12_92_0 ; _rtB -> B_12_192_0 = 286.0 * _rtB ->
B_12_191_0 * _rtB -> B_12_91_0 / 0.02 ; if ( ssIsModeUpdateTimeStep ( S ) ) {
if ( _rtX -> IntegratorX_Oem_CSTATE >= _rtP -> P_117 ) { if ( _rtX ->
IntegratorX_Oem_CSTATE != _rtP -> P_117 ) { _rtX -> IntegratorX_Oem_CSTATE =
_rtP -> P_117 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
IntegratorX_Oem_MODE = 3 ; } else if ( _rtX -> IntegratorX_Oem_CSTATE <= _rtP
-> P_118 ) { if ( _rtX -> IntegratorX_Oem_CSTATE != _rtP -> P_118 ) { _rtX ->
IntegratorX_Oem_CSTATE = _rtP -> P_118 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
IntegratorX_Oem_MODE = 4 ; } else { if ( _rtDW -> IntegratorX_Oem_MODE != 0 )
{ ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
IntegratorX_Oem_MODE = 0 ; } _rtB -> B_12_193_0 = _rtX ->
IntegratorX_Oem_CSTATE ; } else { _rtB -> B_12_193_0 = _rtX ->
IntegratorX_Oem_CSTATE ; } _rtB -> B_12_194_0 = 286.0 * _rtB -> B_12_91_0 /
_rtB -> B_12_70_0 / 0.02 * _rtB -> B_12_90_0 * ( _rtB -> B_12_174_0 - _rtB ->
B_12_193_0 ) ; _rtB -> B_12_195_0 = _rtB -> B_12_93_0 - _rtB -> B_12_83_0 ;
_rtB -> B_12_196_0 = 287.0 * _rtB -> B_12_195_0 * _rtB -> B_12_72_0_g / 0.022
; if ( ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_94_0 ;
_rtDW -> MinMax1_MODE_n = 0 ; if ( ( _rtB -> B_12_94_0 != _rtB -> B_12_94_0 )
|| ( _rtB -> B_12_73_0 < _rtB -> B_12_94_0 ) ) { rtb_B_12_151_0 = _rtB ->
B_12_73_0 ; _rtDW -> MinMax1_MODE_n = 1 ; } _rtB -> B_12_197_0 =
rtb_B_12_151_0 ; } else { rtb_B_12_151_0 = _rtB -> B_12_94_0 ; if ( _rtDW ->
MinMax1_MODE_n == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_73_0 ; } _rtB ->
B_12_197_0 = rtb_B_12_151_0 ; } _rtB -> B_12_198_0 = 287.0 * _rtB ->
B_12_72_0_g / _rtB -> B_12_27_0 / 0.022 * ( ( _rtB -> B_12_193_0 - _rtB ->
B_12_96_0 ) * _rtB -> B_12_92_0 + ( 0.2314 - _rtB -> B_12_96_0 ) * _rtB ->
B_12_40_0 ) ; _rtB -> B_12_202_0 [ 0 ] = _rtB -> B_12_40_0 -
0.27533757461959213 ; if ( _rtB -> B_12_29_0 - 1.0 < 0.0 ) { rtb_B_12_151_0 =
- muDoubleScalarPower ( - ( _rtB -> B_12_29_0 - 1.0 ) , 0.27075947387648991 )
; } else { rtb_B_12_151_0 = muDoubleScalarPower ( _rtB -> B_12_29_0 - 1.0 ,
0.27075947387648991 ) ; } _rtB -> B_12_202_0 [ 1 ] = rtb_B_12_151_0 -
1.0455177468256369 ; _rtB -> B_12_203_0 [ 0 ] = _rtB -> B_12_202_0 [ 0 ] ;
taskTimeV = _rtP -> P_119 [ 0 ] * _rtB -> B_12_202_0 [ 0 ] + _rtB ->
B_12_202_0 [ 1 ] * _rtP -> P_119 [ 2 ] ; _rtB -> B_12_204_0 [ 0 ] = taskTimeV
; rtb_B_12_151_0 = _rtB -> B_12_202_0 [ 0 ] * taskTimeV ; _rtB -> B_12_203_0
[ 1 ] = _rtB -> B_12_202_0 [ 1 ] ; taskTimeV = _rtB -> B_12_202_0 [ 0 ] *
_rtP -> P_119 [ 1 ] + _rtB -> B_12_202_0 [ 1 ] * _rtP -> P_119 [ 3 ] ; _rtB
-> B_12_204_0 [ 1 ] = taskTimeV ; rtb_B_12_151_0 += _rtB -> B_12_202_0 [ 1 ]
* taskTimeV ; _rtB -> B_12_205_0 = rtb_B_12_151_0 ; _rtB -> B_12_206_0 =
0.7363607879724583 - _rtB -> B_12_205_0 ; if ( ssIsModeUpdateTimeStep ( S ) )
{ rtb_B_12_151_0 = _rtB -> B_12_206_0 ; _rtDW -> MinMax2_MODE_m = 0 ; if ( (
_rtB -> B_12_206_0 != _rtB -> B_12_206_0 ) || ( _rtB -> B_12_74_0_l > _rtB ->
B_12_206_0 ) ) { rtb_B_12_151_0 = _rtB -> B_12_74_0_l ; _rtDW ->
MinMax2_MODE_m = 1 ; } _rtB -> B_12_207_0 = rtb_B_12_151_0 ; } else {
rtb_B_12_151_0 = _rtB -> B_12_206_0 ; if ( _rtDW -> MinMax2_MODE_m == 1 ) {
rtb_B_12_151_0 = _rtB -> B_12_74_0_l ; } _rtB -> B_12_207_0 = rtb_B_12_151_0
; } if ( _rtB -> B_12_29_0 < 0.0 ) { rtb_B_12_151_0 = - muDoubleScalarPower (
- _rtB -> B_12_29_0 , 0.28387734915924823 ) ; } else { rtb_B_12_151_0 =
muDoubleScalarPower ( _rtB -> B_12_29_0 , 0.28387734915924823 ) ; } taskTimeV
= ( rtb_B_12_151_0 - 1.0 ) * _rtB -> B_12_86_0_l / _rtB -> B_12_207_0 ; _rtB
-> B_12_209_0 = _rtB -> B_12_40_0 * 1011.0 * taskTimeV ; _rtB -> B_12_210_0 =
taskTimeV + _rtB -> B_12_86_0_l ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T tMinusDelay = simTime - _rtP -> P_120 ; _rtB -> B_12_211_0 =
TruckBenchmark_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer ,
_rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail , _rtDW
-> TransportDelay1_IWORK . Head , _rtP -> P_121 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay1_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay1_IWORK . Head ] == ssGetT ( S ) )
) ) ; } _rtB -> B_12_212_0 = _rtB -> B_12_211_0 - _rtB -> B_12_182_0 ; _rtB
-> B_12_213_0 = _rtP -> P_122 * _rtB -> B_12_212_0 ; if (
ssIsModeUpdateTimeStep ( S ) ) { rtb_B_12_151_0 = _rtB -> B_12_84_0_b ; _rtDW
-> MinMax_MODE_j = 0 ; if ( ( _rtB -> B_12_84_0_b != _rtB -> B_12_84_0_b ) ||
( _rtB -> B_12_26_0 > _rtB -> B_12_84_0_b ) ) { rtb_B_12_151_0 = _rtB ->
B_12_26_0 ; _rtDW -> MinMax_MODE_j = 1 ; } _rtB -> B_12_214_0 =
rtb_B_12_151_0 ; _rtDW -> SwitchPSI_Mode = ( _rtB -> B_12_214_0 >= _rtP ->
P_123 ) ; } else { rtb_B_12_151_0 = _rtB -> B_12_84_0_b ; if ( _rtDW ->
MinMax_MODE_j == 1 ) { rtb_B_12_151_0 = _rtB -> B_12_26_0 ; } _rtB ->
B_12_214_0 = rtb_B_12_151_0 ; } if ( _rtDW -> SwitchPSI_Mode ) { if ( _rtB ->
B_12_214_0 - 2769.2092015766916 < 0.0 ) { rtb_B_12_151_0 = -
muDoubleScalarPower ( - ( _rtB -> B_12_214_0 - 2769.2092015766916 ) ,
0.010000098744565608 ) ; } else { rtb_B_12_151_0 = muDoubleScalarPower ( _rtB
-> B_12_214_0 - 2769.2092015766916 , 0.010000098744565608 ) ; } _rtB ->
B_9_0_0 = 1.3563440681098633 * rtb_B_12_151_0 ; _rtB -> B_12_217_0 = _rtB ->
B_9_0_0 ; } else { _rtB -> B_10_0_0 = ( _rtB -> B_12_214_0 -
2769.2092015766916 ) * 1.4021470818125312 / 27.692092015766775 ; _rtB ->
B_12_217_0 = _rtB -> B_10_0_0 ; } if ( _rtB -> B_12_181_0 < 0.0 ) {
rtb_B_12_151_0 = - muDoubleScalarPower ( - _rtB -> B_12_181_0 ,
0.21471471471471471 ) ; } else { rtb_B_12_151_0 = muDoubleScalarPower ( _rtB
-> B_12_181_0 , 0.21471471471471471 ) ; } rtb_B_12_151_0 = 2664.0 * _rtB ->
B_12_91_0 * ( 1.0 - rtb_B_12_151_0 ) ; if ( rtb_B_12_151_0 < 0.0 ) {
rtb_B_12_151_0 = - muDoubleScalarSqrt ( - rtb_B_12_151_0 ) ; } else {
rtb_B_12_151_0 = muDoubleScalarSqrt ( rtb_B_12_151_0 ) ; } _rtB -> B_12_218_0
= 0.04 * _rtB -> B_12_26_0 / rtb_B_12_151_0 ; if ( ssIsModeUpdateTimeStep ( S
) ) { _rtDW -> Saturation_MODE_k = _rtB -> B_12_218_0 >= _rtP -> P_124 ? 1 :
_rtB -> B_12_218_0 > _rtP -> P_125 ? 0 : - 1 ; } _rtB -> B_12_219_0 = _rtDW
-> Saturation_MODE_k == 1 ? _rtP -> P_124 : _rtDW -> Saturation_MODE_k == - 1
? _rtP -> P_125 : _rtB -> B_12_218_0 ; _rtB -> B_12_220_0 = 0.818002726891074
- muDoubleScalarPower ( _rtB -> B_12_219_0 - 0.97552031618020918 , 2.0 ) *
_rtB -> B_12_217_0 ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Saturation1_MODE_e = _rtB -> B_12_220_0 >= _rtP -> P_126 ? 1 : _rtB ->
B_12_220_0 > _rtP -> P_127 ? 0 : - 1 ; } _rtB -> B_12_221_0 = _rtDW ->
Saturation1_MODE_e == 1 ? _rtP -> P_126 : _rtDW -> Saturation1_MODE_e == - 1
? _rtP -> P_127 : _rtB -> B_12_220_0 ; if ( _rtB -> B_12_181_0 < 0.0 ) {
rtb_B_12_151_0 = - muDoubleScalarPower ( - _rtB -> B_12_181_0 ,
0.21471471471471471 ) ; } else { rtb_B_12_151_0 = muDoubleScalarPower ( _rtB
-> B_12_181_0 , 0.21471471471471471 ) ; } _rtB -> B_12_223_0 = ( 1.0 -
rtb_B_12_151_0 ) * _rtB -> B_12_91_0 * _rtB -> B_12_221_0 * ( _rtB ->
B_12_190_0 * 1332.0 ) ; _rtB -> B_12_224_0 = _rtB -> B_12_223_0 - _rtB ->
B_12_209_0 ; _rtB -> B_12_225_0 = _rtB -> B_12_224_0 / _rtB -> B_12_26_0 ;
_rtB -> B_12_226_0 = _rtP -> P_128 * _rtB -> B_12_225_0 ; _rtB -> B_12_227_0
= _rtP -> P_129 * _rtB -> B_12_26_0 ; ssCallAccelRunBlock ( S , 12 , 228 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 12 , 229 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> RelationalOperator_Mode_n
= ( _rtB -> B_12_18_0 >= _rtB -> B_12_87_0 ) ; } if ( _rtDW ->
RelationalOperator_Mode_n ) { ssSetStopRequested ( S , 1 ) ; } { if ( _rtDW
-> TAQSigLogging_InsertedFor_1DLookupTable_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_1DLookupTable_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_98_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_Integrator_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Integrator_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_12_101_0 + 0 ) ; } } } _rtB
-> B_12_235_0 = _rtP -> P_130 * _rtB -> B_12_2_0 ; _rtB -> B_12_236_0 =
muDoubleScalarSin ( _rtB -> B_12_98_0 ) * _rtB -> B_12_235_0 ;
ssCallAccelRunBlock ( S , 12 , 237 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace33_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace33_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_219_0 + 0 ) ; } } taskTimeV = ssGetT ( S )
; { if ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace5_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace5_PWORK . AQHandles , ssGetTaskTime ( S ,
0 ) , ( char * ) & taskTimeV + 0 ) ; } } ssCallAccelRunBlock ( S , 12 , 241 ,
SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace13_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace13_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_116_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 243 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace11_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace11_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_209_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 245 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace12_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace12_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_223_0 + 0 ) ; } } isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( isHit != 0 ) { ssCallAccelRunBlock ( S , 12 , 247 ,
SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace31_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace31_PWORK . AQHandles , ssGetTaskTime ( S
, 1 ) , ( char * ) & _rtB -> B_12_86_0 + 0 ) ; } } } ssCallAccelRunBlock ( S
, 12 , 249 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace_PWORK_e3 . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace_PWORK_e3 . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_210_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 251 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace2_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace2_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_12_89_0 + 0 ) ;
} } ssCallAccelRunBlock ( S , 12 , 253 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW
-> _asyncqueue_inserted_for_ToWorkspace29_PWORK . AQHandles && ssGetLogOutput
( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace29_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_91_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 255 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace7_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace7_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_12_40_0 + 0 ) ;
} } ssCallAccelRunBlock ( S , 12 , 257 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW
-> _asyncqueue_inserted_for_ToWorkspace6_PWORK . AQHandles && ssGetLogOutput
( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace6_PWORK . AQHandles , ssGetTaskTime ( S ,
0 ) , ( char * ) & _rtB -> B_12_92_0 + 0 ) ; } } ssCallAccelRunBlock ( S , 12
, 259 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace9_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace9_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_12_83_0 + 0 ) ;
} } ssCallAccelRunBlock ( S , 12 , 261 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW
-> _asyncqueue_inserted_for_ToWorkspace10_PWORK . AQHandles && ssGetLogOutput
( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace10_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_90_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 263 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace22_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace22_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_81_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 265 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace8_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace8_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_12_190_0 + 0 ) ;
} } ssCallAccelRunBlock ( S , 12 , 267 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW
-> _asyncqueue_inserted_for_ToWorkspace30_PWORK . AQHandles && ssGetLogOutput
( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace30_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_193_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 269 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace25_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace25_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_96_0 + 0 ) ; } } { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace14_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace14_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_227_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 272 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace15_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace15_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_97_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 274 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace16_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace16_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_80_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 276 , SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { { if ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace17_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace17_PWORK . AQHandles , ssGetTaskTime ( S
, 1 ) , ( char * ) & _rtB -> B_12_64_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 278 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace18_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace18_PWORK . AQHandles , ssGetTaskTime ( S
, 1 ) , ( char * ) & _rtB -> B_12_184_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 280 , SS_CALL_MDL_OUTPUTS ) ; } { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace19_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace19_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_75_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 282 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace20_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace20_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_221_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 284 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace21_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace21_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_207_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 286 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace24_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace24_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_197_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 288 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace27_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace27_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_66_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 290 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace28_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace28_PWORK . AQHandles , ssGetTaskTime ( S
, 0 ) , ( char * ) & _rtB -> B_12_185_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 292 , SS_CALL_MDL_OUTPUTS ) ; { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace3_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace3_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_12_27_0 + 0 ) ;
} } ssCallAccelRunBlock ( S , 12 , 294 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace32_PWORK . AQHandles && ssGetLogOutput (
S ) ) { sdiWriteSignal ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace32_PWORK . AQHandles , ssGetTaskTime ( S
, 1 ) , ( char * ) & _rtB -> B_12_84_0 + 0 ) ; } } ssCallAccelRunBlock ( S ,
12 , 296 , SS_CALL_MDL_OUTPUTS ) ; } { if ( _rtDW ->
_asyncqueue_inserted_for_ToWorkspace4_PWORK . AQHandles && ssGetLogOutput ( S
) ) { sdiWriteSignal ( _rtDW -> _asyncqueue_inserted_for_ToWorkspace4_PWORK .
AQHandles , ssGetTaskTime ( S , 0 ) , ( char * ) & _rtB -> B_12_70_0 + 0 ) ;
} } ssCallAccelRunBlock ( S , 12 , 298 , SS_CALL_MDL_OUTPUTS ) ;
UNUSED_PARAMETER ( tid ) ; } static void mdlOutputsTID6 ( SimStruct * S ,
int_T tid ) { B_TruckBenchmark_T * _rtB ; P_TruckBenchmark_T * _rtP ; int32_T
i ; int32_T tmp_1 ; uint32_T arg3 ; uint8_T tmp [ 31 ] ; uint8_T tmp_0 [ 31 ]
; void * diag ; void * rtb_B_12_43_0 ; void * rtb_B_12_44_0 ; _rtP = ( (
P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_TruckBenchmark_T
* ) _ssGetModelBlockIO ( S ) ) ; tmp_1 = suStringStackSize ( ) ; _rtB ->
B_0_0_0 = _rtP -> P_0 ; memcpy ( & _rtB -> B_6_0_0 [ 0 ] , & _rtP -> P_8 [ 0
] , 9905U * sizeof ( real_T ) ) ; memcpy ( & _rtB -> B_6_1_0 [ 0 ] , & _rtP
-> P_9 [ 0 ] , 9905U * sizeof ( real_T ) ) ; _rtB -> B_6_2_0 = _rtP -> P_10 ;
_rtB -> B_6_5_0 = _rtP -> P_11 ; _rtB -> B_6_6_0 = _rtP -> P_12 ; _rtB ->
B_6_7_0 = _rtP -> P_13 ; _rtB -> B_12_20_0_d = ( _rtP -> P_139 != 0.0 ) ;
_rtB -> B_12_21_0_e = ( _rtP -> P_131 != 0.0 ) ; _rtB -> B_12_22_0 = ( _rtP
-> P_132 != 0.0 ) ; _rtB -> B_12_23_0_b = ( _rtP -> P_141 != 0.0 ) ; _rtB ->
B_12_24_0_j = ( _rtP -> P_133 != 0.0 ) ; _rtB -> B_12_25_0 = ( _rtP -> P_134
!= 0.0 ) ; _rtB -> B_12_26_0_f = ( _rtP -> P_135 != 0.0 ) ; _rtB ->
B_12_27_0_a = ( _rtP -> P_136 != 0.0 ) ; _rtB -> B_12_28_0_j = ( _rtP ->
P_137 != 0.0 ) ; _rtB -> B_12_29_0_j = ( _rtP -> P_138 != 0.0 ) ; _rtB ->
B_12_31_0_o = ( _rtP -> P_149 * _rtP -> P_148 != 0.0 ) ; _rtB -> B_12_32_0_n
= ( _rtP -> P_145 != 0.0 ) ; _rtB -> B_12_33_0_i = ( _rtP -> P_146 != 0.0 ) ;
_rtB -> B_12_34_0_o = ( _rtP -> P_147 != 0.0 ) ; _rtB -> B_12_35_0_n = ( _rtP
-> P_140 != 0.0 ) ; _rtB -> B_12_36_0_m = ( _rtP -> P_142 != 0.0 ) ; _rtB ->
B_12_37_0_c = ( _rtP -> P_143 != 0.0 ) ; _rtB -> B_12_38_0_m = ( _rtP ->
P_144 != 0.0 ) ; _rtB -> B_12_40_0_m = _rtP -> P_151 * _rtP -> P_150 ; _rtB
-> B_12_42_0 = _rtP -> P_153 * _rtP -> P_152 ; rtb_B_12_43_0 =
suAddStackString ( NULL ) ; suCopyString ( rtb_B_12_43_0 , _rtP -> P_192 ) ;
rtb_B_12_44_0 = suAddStackString ( NULL ) ; suCopyString ( rtb_B_12_44_0 ,
_rtP -> P_193 ) ; arg3 = ( uint32_T ) suStrlen ( rtb_B_12_43_0 ) ; if ( arg3
> 31U ) { diag = CreateDiagnosticAsVoidPtr (
"Simulink:StringBlocks:StringBufferOverflow" , 4 , 1 , 1 , 5 ,
"TruckBenchmark/Controller/CAN TX//RX/String to ASCII" , 1 , arg3 , 1 , 31 )
; rt_ssReportDiagnosticAsWarning ( S , diag ) ; } suStrToAscii ( & tmp [ 0 ]
, 31 , rtb_B_12_43_0 ) ; for ( i = 0 ; i < 31 ; i ++ ) { _rtB -> B_12_45_0_h
[ i ] = tmp [ i ] ; } arg3 = ( uint32_T ) suStrlen ( rtb_B_12_44_0 ) ; if (
arg3 > 31U ) { diag = CreateDiagnosticAsVoidPtr (
"Simulink:StringBlocks:StringBufferOverflow" , 4 , 1 , 1 , 5 ,
"TruckBenchmark/Controller/CAN TX//RX/String to ASCII1" , 1 , arg3 , 1 , 31 )
; rt_ssReportDiagnosticAsWarning ( S , diag ) ; } suStrToAscii ( & tmp_0 [ 0
] , 31 , rtb_B_12_44_0 ) ; for ( i = 0 ; i < 31 ; i ++ ) { _rtB ->
B_12_46_0_b [ i ] = tmp_0 [ i ] ; } _rtB -> B_12_47_0_c = _rtP -> P_154 ;
_rtB -> B_12_49_0_k = _rtP -> P_156 ; _rtB -> B_12_52_0_c = _rtB ->
B_12_49_0_k * _rtB -> B_12_49_0_k * _rtP -> P_157 ; _rtB -> B_12_53_0 = _rtP
-> P_158 ; _rtB -> B_12_54_0 = _rtP -> P_159 ; _rtB -> B_12_55_0 = _rtP ->
P_160 ; _rtB -> B_12_56_0 = _rtP -> P_161 ; _rtB -> B_12_57_0_b = _rtP ->
P_162 ; _rtB -> B_12_58_0 = _rtP -> P_155 * _rtP -> P_157 ; _rtB ->
B_12_59_0_p = _rtP -> P_163 ; _rtB -> B_12_60_0_c = _rtP -> P_164 ; _rtB ->
B_12_61_0_f = _rtP -> P_165 ; _rtB -> B_12_62_0_g = _rtP -> P_166 ; _rtB ->
B_12_63_0 = _rtP -> P_167 ; _rtB -> B_12_64_0_g = _rtP -> P_168 ; _rtB ->
B_12_65_0 = _rtP -> P_169 ; _rtB -> B_12_66_0_m = _rtP -> P_170 ; _rtB ->
B_12_67_0_n = _rtP -> P_171 ; _rtB -> B_12_68_0_p = _rtP -> P_172 ; _rtB ->
B_12_69_0_l = _rtP -> P_173 ; _rtB -> B_12_70_0_j = _rtP -> P_174 ; _rtB ->
B_12_71_0_d = _rtP -> P_175 ; _rtB -> B_12_72_0_g = _rtP -> P_176 ; _rtB ->
B_12_73_0 = _rtP -> P_177 ; _rtB -> B_12_74_0_l = _rtP -> P_178 ; _rtB ->
B_12_75_0_d = _rtP -> P_179 ; _rtB -> B_12_76_0_d = _rtP -> P_180 ; _rtB ->
B_12_77_0 = _rtP -> P_181 ; _rtB -> B_12_78_0 = _rtP -> P_182 ; _rtB ->
B_12_79_0_l = _rtP -> P_183 ; _rtB -> B_12_80_0_o = _rtP -> P_184 ; _rtB ->
B_12_81_0_b = _rtP -> P_185 ; _rtB -> B_12_82_0 = _rtP -> P_186 ; _rtB ->
B_12_83_0_n = _rtP -> P_187 ; _rtB -> B_12_84_0_b = _rtP -> P_188 ; _rtB ->
B_12_85_0 = _rtP -> P_189 ; _rtB -> B_12_86_0_l = _rtP -> P_190 ; _rtB ->
B_12_87_0 = _rtP -> P_191 ; suMoveReturnedStringsToTopOfCallerStack ( tmp_1 ,
0 ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { B_TruckBenchmark_T *
_rtB ; DW_TruckBenchmark_T * _rtDW ; P_TruckBenchmark_T * _rtP ;
XDis_TruckBenchmark_T * _rtXdis ; int32_T isHit ; _rtDW = ( (
DW_TruckBenchmark_T * ) ssGetRootDWork ( S ) ) ; _rtXdis = ( (
XDis_TruckBenchmark_T * ) ssGetContStateDisabled ( S ) ) ; _rtP = ( (
P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_TruckBenchmark_T
* ) _ssGetModelBlockIO ( S ) ) ; switch ( _rtDW -> Integrator_MODE ) { case 3
: if ( _rtB -> B_12_166_0 < 0.0 ) { _rtDW -> Integrator_MODE = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_12_166_0 > 0.0 ) { _rtDW -> Integrator_MODE = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator_CSTATE = ( ( _rtDW -> Integrator_MODE == 3 ) || ( _rtDW ->
Integrator_MODE == 4 ) ) ; switch ( _rtDW -> Integrator1_MODE ) { case 3 : if
( _rtB -> B_12_1_0 < 0.0 ) { _rtDW -> Integrator1_MODE = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_12_1_0 > 0.0 ) { _rtDW -> Integrator1_MODE = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator1_CSTATE = ( ( _rtDW -> Integrator1_MODE == 3 ) || ( _rtDW ->
Integrator1_MODE == 4 ) ) ; switch ( _rtDW -> Integratoromega_t_MODE ) { case
3 : if ( _rtB -> B_12_226_0 < 0.0 ) { _rtDW -> Integratoromega_t_MODE = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_12_226_0 > 0.0 ) { _rtDW -> Integratoromega_t_MODE = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integratoromega_t_CSTATE = ( ( _rtDW -> Integratoromega_t_MODE == 3 ) || (
_rtDW -> Integratoromega_t_MODE == 4 ) ) ; switch ( _rtDW ->
Integratorp_im_MODE ) { case 3 : if ( _rtB -> B_12_196_0 < 0.0 ) { _rtDW ->
Integratorp_im_MODE = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} break ; case 4 : if ( _rtB -> B_12_196_0 > 0.0 ) { _rtDW ->
Integratorp_im_MODE = 2 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} break ; } _rtXdis -> Integratorp_im_CSTATE = ( ( _rtDW ->
Integratorp_im_MODE == 3 ) || ( _rtDW -> Integratorp_im_MODE == 4 ) ) ;
switch ( _rtDW -> Integrator1_MODE_g ) { case 3 : if ( _rtB -> B_12_161_0 <
0.0 ) { _rtDW -> Integrator1_MODE_g = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_12_161_0 > 0.0 ) { _rtDW -> Integrator1_MODE_g = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
Integrator1_CSTATE_c = ( ( _rtDW -> Integrator1_MODE_g == 3 ) || ( _rtDW ->
Integrator1_MODE_g == 4 ) ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtDW -> Memory4_PreviousInput = _rtB -> B_3_0_1 ; _rtDW ->
Memory3_PreviousInput = _rtB -> B_6_16_0 ; } switch ( _rtDW ->
Integratorp_em_MODE ) { case 3 : if ( _rtB -> B_12_192_0 < 0.0 ) { _rtDW ->
Integratorp_em_MODE = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} break ; case 4 : if ( _rtB -> B_12_192_0 > 0.0 ) { _rtDW ->
Integratorp_em_MODE = 2 ; ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
} break ; } _rtXdis -> Integratorp_em_CSTATE = ( ( _rtDW ->
Integratorp_em_MODE == 3 ) || ( _rtDW -> Integratorp_em_MODE == 4 ) ) ; isHit
= ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Memory2_PreviousInput = _rtB -> B_6_13_0 ; _rtDW -> x_rOld_PreviousInput =
_rtB -> B_12_170_0 ; _rtDW -> T_1Old_PreviousInput = _rtB -> B_12_172_0 ; }
switch ( _rtDW -> IntegratorX_Oim_MODE ) { case 3 : if ( _rtB -> B_12_198_0 <
0.0 ) { _rtDW -> IntegratorX_Oim_MODE = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_12_198_0 > 0.0 ) { _rtDW -> IntegratorX_Oim_MODE = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
IntegratorX_Oim_CSTATE = ( ( _rtDW -> IntegratorX_Oim_MODE == 3 ) || ( _rtDW
-> IntegratorX_Oim_MODE == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( ! TruckBenchmark_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_107 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_12_64_0 ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Memory1_PreviousInput = _rtB ->
B_6_15_0 ; } switch ( _rtDW -> IntegratorX_Oem_MODE ) { case 3 : if ( _rtB ->
B_12_194_0 < 0.0 ) { _rtDW -> IntegratorX_Oem_MODE = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; case 4 : if (
_rtB -> B_12_194_0 > 0.0 ) { _rtDW -> IntegratorX_Oem_MODE = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } break ; } _rtXdis ->
IntegratorX_Oem_CSTATE = ( ( _rtDW -> IntegratorX_Oem_MODE == 3 ) || ( _rtDW
-> IntegratorX_Oem_MODE == 4 ) ) ; { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; _rtDW -> TransportDelay1_IWORK . Head = ( ( _rtDW ->
TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
TruckBenchmark_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_120 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay1_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = _rtB -> B_12_184_0 ; } UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID6 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_TruckBenchmark_T * _rtB ;
XDis_TruckBenchmark_T * _rtXdis ; XDot_TruckBenchmark_T * _rtXdot ; _rtXdis =
( ( XDis_TruckBenchmark_T * ) ssGetContStateDisabled ( S ) ) ; _rtXdot = ( (
XDot_TruckBenchmark_T * ) ssGetdX ( S ) ) ; _rtB = ( ( B_TruckBenchmark_T * )
_ssGetModelBlockIO ( S ) ) ; if ( _rtXdis -> Integrator_CSTATE ) { _rtXdot ->
Integrator_CSTATE = 0.0 ; } else { _rtXdot -> Integrator_CSTATE = _rtB ->
B_12_166_0 ; } if ( _rtXdis -> Integrator1_CSTATE ) { _rtXdot ->
Integrator1_CSTATE = 0.0 ; } else { _rtXdot -> Integrator1_CSTATE = _rtB ->
B_12_1_0 ; } if ( _rtXdis -> Integratoromega_t_CSTATE ) { _rtXdot ->
Integratoromega_t_CSTATE = 0.0 ; } else { _rtXdot -> Integratoromega_t_CSTATE
= _rtB -> B_12_226_0 ; } if ( _rtXdis -> Integratorp_im_CSTATE ) { _rtXdot ->
Integratorp_im_CSTATE = 0.0 ; } else { _rtXdot -> Integratorp_im_CSTATE =
_rtB -> B_12_196_0 ; } if ( _rtXdis -> Integrator1_CSTATE_c ) { _rtXdot ->
Integrator1_CSTATE_c = 0.0 ; } else { _rtXdot -> Integrator1_CSTATE_c = _rtB
-> B_12_161_0 ; } _rtXdot -> Integrator_CSTATE_h = _rtB -> B_12_177_0 ;
_rtXdot -> Integrator_CSTATE_hj = _rtB -> B_12_179_0 ; if ( _rtXdis ->
Integratorp_em_CSTATE ) { _rtXdot -> Integratorp_em_CSTATE = 0.0 ; } else {
_rtXdot -> Integratorp_em_CSTATE = _rtB -> B_12_192_0 ; } if ( _rtXdis ->
IntegratorX_Oim_CSTATE ) { _rtXdot -> IntegratorX_Oim_CSTATE = 0.0 ; } else {
_rtXdot -> IntegratorX_Oim_CSTATE = _rtB -> B_12_198_0 ; } _rtXdot ->
Integrator_CSTATE_f = _rtB -> B_12_236_0 ; _rtXdot -> Integrator_CSTATE_k =
_rtB -> B_12_81_0 ; _rtXdot -> Integrator_CSTATE_j = _rtB -> B_12_213_0 ; if
( _rtXdis -> IntegratorX_Oem_CSTATE ) { _rtXdot -> IntegratorX_Oem_CSTATE =
0.0 ; } else { _rtXdot -> IntegratorX_Oem_CSTATE = _rtB -> B_12_194_0 ; } }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { B_TruckBenchmark_T * _rtB ;
DW_TruckBenchmark_T * _rtDW ; P_TruckBenchmark_T * _rtP ; X_TruckBenchmark_T
* _rtX ; ZCV_TruckBenchmark_T * _rtZCSV ; _rtDW = ( ( DW_TruckBenchmark_T * )
ssGetRootDWork ( S ) ) ; _rtZCSV = ( ( ZCV_TruckBenchmark_T * )
ssGetSolverZcSignalVector ( S ) ) ; _rtX = ( ( X_TruckBenchmark_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_TruckBenchmark_T * ) ssGetModelRtp ( S
) ) ; _rtB = ( ( B_TruckBenchmark_T * ) _ssGetModelBlockIO ( S ) ) ; switch (
_rtDW -> Integrator_MODE ) { case 1 : _rtZCSV -> Integrator_IntgUpLimit_ZC =
0.0 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = _rtP -> P_18 - _rtP -> P_19 ;
break ; case 2 : _rtZCSV -> Integrator_IntgUpLimit_ZC = _rtP -> P_19 - _rtP
-> P_18 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = 0.0 ; break ; default :
_rtZCSV -> Integrator_IntgUpLimit_ZC = _rtX -> Integrator_CSTATE - _rtP ->
P_18 ; _rtZCSV -> Integrator_IntgLoLimit_ZC = _rtX -> Integrator_CSTATE -
_rtP -> P_19 ; break ; } if ( ( _rtDW -> Integrator_MODE == 3 ) || ( _rtDW ->
Integrator_MODE == 4 ) ) { _rtZCSV -> Integrator_LeaveSaturate_ZC = _rtB ->
B_12_166_0 ; } else { _rtZCSV -> Integrator_LeaveSaturate_ZC = 0.0 ; } switch
( _rtDW -> Integrator1_MODE ) { case 1 : _rtZCSV ->
Integrator1_IntgUpLimit_ZC = 0.0 ; _rtZCSV -> Integrator1_IntgLoLimit_ZC =
_rtP -> P_22 - _rtP -> P_23 ; break ; case 2 : _rtZCSV ->
Integrator1_IntgUpLimit_ZC = _rtP -> P_23 - _rtP -> P_22 ; _rtZCSV ->
Integrator1_IntgLoLimit_ZC = 0.0 ; break ; default : _rtZCSV ->
Integrator1_IntgUpLimit_ZC = _rtX -> Integrator1_CSTATE - _rtP -> P_22 ;
_rtZCSV -> Integrator1_IntgLoLimit_ZC = _rtX -> Integrator1_CSTATE - _rtP ->
P_23 ; break ; } if ( ( _rtDW -> Integrator1_MODE == 3 ) || ( _rtDW ->
Integrator1_MODE == 4 ) ) { _rtZCSV -> Integrator1_LeaveSaturate_ZC = _rtB ->
B_12_1_0 ; } else { _rtZCSV -> Integrator1_LeaveSaturate_ZC = 0.0 ; } switch
( _rtDW -> Integratoromega_t_MODE ) { case 1 : _rtZCSV ->
Integratoromega_t_IntgUpLimit_ZC = 0.0 ; _rtZCSV ->
Integratoromega_t_IntgLoLimit_ZC = _rtP -> P_33 - _rtP -> P_34 ; break ; case
2 : _rtZCSV -> Integratoromega_t_IntgUpLimit_ZC = _rtP -> P_34 - _rtP -> P_33
; _rtZCSV -> Integratoromega_t_IntgLoLimit_ZC = 0.0 ; break ; default :
_rtZCSV -> Integratoromega_t_IntgUpLimit_ZC = _rtX ->
Integratoromega_t_CSTATE - _rtP -> P_33 ; _rtZCSV ->
Integratoromega_t_IntgLoLimit_ZC = _rtX -> Integratoromega_t_CSTATE - _rtP ->
P_34 ; break ; } if ( ( _rtDW -> Integratoromega_t_MODE == 3 ) || ( _rtDW ->
Integratoromega_t_MODE == 4 ) ) { _rtZCSV ->
Integratoromega_t_LeaveSaturate_ZC = _rtB -> B_12_226_0 ; } else { _rtZCSV ->
Integratoromega_t_LeaveSaturate_ZC = 0.0 ; } switch ( _rtDW ->
Integratorp_im_MODE ) { case 1 : _rtZCSV -> Integratorp_im_IntgUpLimit_ZC =
0.0 ; _rtZCSV -> Integratorp_im_IntgLoLimit_ZC = _rtP -> P_36 - _rtP -> P_37
; break ; case 2 : _rtZCSV -> Integratorp_im_IntgUpLimit_ZC = _rtP -> P_37 -
_rtP -> P_36 ; _rtZCSV -> Integratorp_im_IntgLoLimit_ZC = 0.0 ; break ;
default : _rtZCSV -> Integratorp_im_IntgUpLimit_ZC = _rtX ->
Integratorp_im_CSTATE - _rtP -> P_36 ; _rtZCSV ->
Integratorp_im_IntgLoLimit_ZC = _rtX -> Integratorp_im_CSTATE - _rtP -> P_37
; break ; } if ( ( _rtDW -> Integratorp_im_MODE == 3 ) || ( _rtDW ->
Integratorp_im_MODE == 4 ) ) { _rtZCSV -> Integratorp_im_LeaveSaturate_ZC =
_rtB -> B_12_196_0 ; } else { _rtZCSV -> Integratorp_im_LeaveSaturate_ZC =
0.0 ; } if ( ( _rtB -> B_12_75_0_d != _rtB -> B_12_75_0_d ) || ( _rtB ->
B_12_28_0 > _rtB -> B_12_75_0_d ) ) { if ( _rtDW -> MinMax1_MODE == 0 ) {
_rtZCSV -> MinMax1_MinmaxInput_ZC = _rtB -> B_12_28_0 - _rtB -> B_12_28_0 ; }
else { _rtZCSV -> MinMax1_MinmaxInput_ZC = _rtB -> B_12_28_0 - _rtB ->
B_12_75_0_d ; } } else if ( _rtDW -> MinMax1_MODE == 0 ) { _rtZCSV ->
MinMax1_MinmaxInput_ZC = _rtB -> B_12_75_0_d - _rtB -> B_12_28_0 ; } else {
_rtZCSV -> MinMax1_MinmaxInput_ZC = _rtB -> B_12_75_0_d - _rtB -> B_12_75_0_d
; } if ( ( _rtB -> B_12_77_0 != _rtB -> B_12_77_0 ) || ( _rtB -> B_12_31_0 >
_rtB -> B_12_77_0 ) ) { if ( _rtDW -> MinMax1_MODE_i == 0 ) { _rtZCSV ->
MinMax1_MinmaxInput_ZC_n = _rtB -> B_12_31_0 - _rtB -> B_12_31_0 ; } else {
_rtZCSV -> MinMax1_MinmaxInput_ZC_n = _rtB -> B_12_31_0 - _rtB -> B_12_77_0 ;
} } else if ( _rtDW -> MinMax1_MODE_i == 0 ) { _rtZCSV ->
MinMax1_MinmaxInput_ZC_n = _rtB -> B_12_77_0 - _rtB -> B_12_31_0 ; } else {
_rtZCSV -> MinMax1_MinmaxInput_ZC_n = _rtB -> B_12_77_0 - _rtB -> B_12_77_0 ;
} if ( ( _rtB -> B_12_33_0 != _rtB -> B_12_33_0 ) || ( _rtB -> B_12_76_0_d >
_rtB -> B_12_33_0 ) ) { if ( _rtDW -> MinMax_MODE == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC = _rtB -> B_12_76_0_d - _rtB -> B_12_76_0_d ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC = _rtB -> B_12_76_0_d - _rtB -> B_12_33_0 ;
} } else if ( _rtDW -> MinMax_MODE == 0 ) { _rtZCSV -> MinMax_MinmaxInput_ZC
= _rtB -> B_12_33_0 - _rtB -> B_12_76_0_d ; } else { _rtZCSV ->
MinMax_MinmaxInput_ZC = _rtB -> B_12_33_0 - _rtB -> B_12_33_0 ; } if ( ( _rtB
-> B_12_79_0_l != _rtB -> B_12_79_0_l ) || ( _rtB -> B_12_35_0 > _rtB ->
B_12_79_0_l ) ) { if ( _rtDW -> MinMax3_MODE == 0 ) { _rtZCSV ->
MinMax3_MinmaxInput_ZC = _rtB -> B_12_35_0 - _rtB -> B_12_35_0 ; } else {
_rtZCSV -> MinMax3_MinmaxInput_ZC = _rtB -> B_12_35_0 - _rtB -> B_12_79_0_l ;
} } else if ( _rtDW -> MinMax3_MODE == 0 ) { _rtZCSV ->
MinMax3_MinmaxInput_ZC = _rtB -> B_12_79_0_l - _rtB -> B_12_35_0 ; } else {
_rtZCSV -> MinMax3_MinmaxInput_ZC = _rtB -> B_12_79_0_l - _rtB -> B_12_79_0_l
; } if ( ( _rtB -> B_12_37_0 != _rtB -> B_12_37_0 ) || ( _rtB -> B_12_78_0 >
_rtB -> B_12_37_0 ) ) { if ( _rtDW -> MinMax2_MODE == 0 ) { _rtZCSV ->
MinMax2_MinmaxInput_ZC = _rtB -> B_12_78_0 - _rtB -> B_12_78_0 ; } else {
_rtZCSV -> MinMax2_MinmaxInput_ZC = _rtB -> B_12_78_0 - _rtB -> B_12_37_0 ; }
} else if ( _rtDW -> MinMax2_MODE == 0 ) { _rtZCSV -> MinMax2_MinmaxInput_ZC
= _rtB -> B_12_37_0 - _rtB -> B_12_78_0 ; } else { _rtZCSV ->
MinMax2_MinmaxInput_ZC = _rtB -> B_12_37_0 - _rtB -> B_12_37_0 ; } _rtZCSV ->
Saturation_UprLim_ZC = _rtB -> B_12_39_0 - _rtP -> P_40 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_12_39_0 - _rtP -> P_41 ; switch ( _rtDW ->
Integrator1_MODE_g ) { case 1 : _rtZCSV -> Integrator1_IntgUpLimit_ZC_k = 0.0
; _rtZCSV -> Integrator1_IntgLoLimit_ZC_e = _rtP -> P_45 - _rtP -> P_46 ;
break ; case 2 : _rtZCSV -> Integrator1_IntgUpLimit_ZC_k = _rtP -> P_46 -
_rtP -> P_45 ; _rtZCSV -> Integrator1_IntgLoLimit_ZC_e = 0.0 ; break ;
default : _rtZCSV -> Integrator1_IntgUpLimit_ZC_k = _rtX ->
Integrator1_CSTATE_c - _rtP -> P_45 ; _rtZCSV -> Integrator1_IntgLoLimit_ZC_e
= _rtX -> Integrator1_CSTATE_c - _rtP -> P_46 ; break ; } if ( ( _rtDW ->
Integrator1_MODE_g == 3 ) || ( _rtDW -> Integrator1_MODE_g == 4 ) ) { _rtZCSV
-> Integrator1_LeaveSaturate_ZC_l = _rtB -> B_12_161_0 ; } else { _rtZCSV ->
Integrator1_LeaveSaturate_ZC_l = 0.0 ; } if ( ( _rtB -> B_12_71_0_d != _rtB
-> B_12_71_0_d ) || ( _rtB -> B_12_66_0 < _rtB -> B_12_71_0_d ) ) { if (
_rtDW -> MinMax1_MODE_e == 0 ) { _rtZCSV -> MinMax1_MinmaxInput_ZC_k = _rtB
-> B_12_66_0 - _rtB -> B_12_66_0 ; } else { _rtZCSV ->
MinMax1_MinmaxInput_ZC_k = _rtB -> B_12_66_0 - _rtB -> B_12_71_0_d ; } } else
if ( _rtDW -> MinMax1_MODE_e == 0 ) { _rtZCSV -> MinMax1_MinmaxInput_ZC_k =
_rtB -> B_12_71_0_d - _rtB -> B_12_66_0 ; } else { _rtZCSV ->
MinMax1_MinmaxInput_ZC_k = _rtB -> B_12_71_0_d - _rtB -> B_12_71_0_d ; } if (
( _rtB -> B_12_70_0_j != _rtB -> B_12_70_0_j ) || ( _rtB -> B_12_68_0 > _rtB
-> B_12_70_0_j ) ) { if ( _rtDW -> MinMax_MODE_h == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_c = _rtB -> B_12_68_0 - _rtB -> B_12_68_0 ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_c = _rtB -> B_12_68_0 - _rtB -> B_12_70_0_j
; } } else if ( _rtDW -> MinMax_MODE_h == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_c = _rtB -> B_12_70_0_j - _rtB -> B_12_68_0 ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_c = _rtB -> B_12_70_0_j - _rtB ->
B_12_70_0_j ; } switch ( _rtDW -> Integratorp_em_MODE ) { case 1 : _rtZCSV ->
Integratorp_em_IntgUpLimit_ZC = 0.0 ; _rtZCSV ->
Integratorp_em_IntgLoLimit_ZC = _rtP -> P_60 - _rtP -> P_61 ; break ; case 2
: _rtZCSV -> Integratorp_em_IntgUpLimit_ZC = _rtP -> P_61 - _rtP -> P_60 ;
_rtZCSV -> Integratorp_em_IntgLoLimit_ZC = 0.0 ; break ; default : _rtZCSV ->
Integratorp_em_IntgUpLimit_ZC = _rtX -> Integratorp_em_CSTATE - _rtP -> P_60
; _rtZCSV -> Integratorp_em_IntgLoLimit_ZC = _rtX -> Integratorp_em_CSTATE -
_rtP -> P_61 ; break ; } if ( ( _rtDW -> Integratorp_em_MODE == 3 ) || (
_rtDW -> Integratorp_em_MODE == 4 ) ) { _rtZCSV ->
Integratorp_em_LeaveSaturate_ZC = _rtB -> B_12_192_0 ; } else { _rtZCSV ->
Integratorp_em_LeaveSaturate_ZC = 0.0 ; } _rtZCSV -> Saturation_UprLim_ZC_i =
_rtB -> B_12_71_0 - _rtP -> P_62 ; _rtZCSV -> Saturation_LwrLim_ZC_l = _rtB
-> B_12_71_0 - _rtP -> P_63 ; _rtZCSV -> Saturation1_UprLim_ZC = _rtB ->
B_12_46_0 - _rtP -> P_64 ; _rtZCSV -> Saturation1_LwrLim_ZC = _rtB ->
B_12_46_0 - _rtP -> P_65 ; if ( ( _rtB -> B_12_79_0 != _rtB -> B_12_79_0 ) ||
( _rtB -> B_12_76_0 < _rtB -> B_12_79_0 ) ) { if ( _rtDW -> MinMax_MODE_c ==
0 ) { _rtZCSV -> MinMax_MinmaxInput_ZC_d = _rtB -> B_12_76_0 - _rtB ->
B_12_76_0 ; } else { _rtZCSV -> MinMax_MinmaxInput_ZC_d = _rtB -> B_12_76_0 -
_rtB -> B_12_79_0 ; } } else if ( _rtDW -> MinMax_MODE_c == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_d = _rtB -> B_12_79_0 - _rtB -> B_12_76_0 ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_d = _rtB -> B_12_79_0 - _rtB -> B_12_79_0 ;
} if ( ( _rtB -> B_12_88_0 != _rtB -> B_12_88_0 ) || ( _rtB -> B_12_62_0_g <
_rtB -> B_12_88_0 ) ) { if ( _rtDW -> MinMax_MODE_p == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_g = _rtB -> B_12_62_0_g - _rtB -> B_12_62_0_g ; } else
{ _rtZCSV -> MinMax_MinmaxInput_ZC_g = _rtB -> B_12_62_0_g - _rtB ->
B_12_88_0 ; } } else if ( _rtDW -> MinMax_MODE_p == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_g = _rtB -> B_12_88_0 - _rtB -> B_12_62_0_g ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_g = _rtB -> B_12_88_0 - _rtB -> B_12_88_0 ;
} if ( ( _rtB -> B_12_68_0_p != _rtB -> B_12_68_0_p ) || ( _rtB -> B_12_81_0
> _rtB -> B_12_68_0_p ) ) { if ( _rtDW -> Max1_MODE == 0 ) { _rtZCSV ->
Max1_MinmaxInput_ZC = _rtB -> B_12_81_0 - _rtB -> B_12_81_0 ; } else {
_rtZCSV -> Max1_MinmaxInput_ZC = _rtB -> B_12_81_0 - _rtB -> B_12_68_0_p ; }
} else if ( _rtDW -> Max1_MODE == 0 ) { _rtZCSV -> Max1_MinmaxInput_ZC = _rtB
-> B_12_68_0_p - _rtB -> B_12_81_0 ; } else { _rtZCSV -> Max1_MinmaxInput_ZC
= _rtB -> B_12_68_0_p - _rtB -> B_12_68_0_p ; } switch ( _rtDW ->
IntegratorX_Oim_MODE ) { case 1 : _rtZCSV -> IntegratorX_Oim_IntgUpLimit_ZC =
0.0 ; _rtZCSV -> IntegratorX_Oim_IntgLoLimit_ZC = _rtP -> P_74 - _rtP -> P_75
; break ; case 2 : _rtZCSV -> IntegratorX_Oim_IntgUpLimit_ZC = _rtP -> P_75 -
_rtP -> P_74 ; _rtZCSV -> IntegratorX_Oim_IntgLoLimit_ZC = 0.0 ; break ;
default : _rtZCSV -> IntegratorX_Oim_IntgUpLimit_ZC = _rtX ->
IntegratorX_Oim_CSTATE - _rtP -> P_74 ; _rtZCSV ->
IntegratorX_Oim_IntgLoLimit_ZC = _rtX -> IntegratorX_Oim_CSTATE - _rtP ->
P_75 ; break ; } if ( ( _rtDW -> IntegratorX_Oim_MODE == 3 ) || ( _rtDW ->
IntegratorX_Oim_MODE == 4 ) ) { _rtZCSV -> IntegratorX_Oim_LeaveSaturate_ZC =
_rtB -> B_12_198_0 ; } else { _rtZCSV -> IntegratorX_Oim_LeaveSaturate_ZC =
0.0 ; } if ( ( _rtB -> B_12_63_0 != _rtB -> B_12_63_0 ) || ( _rtB ->
B_12_97_0 < _rtB -> B_12_63_0 ) ) { if ( _rtDW -> MinMax_MODE_d == 0 ) {
_rtZCSV -> MinMax_MinmaxInput_ZC_gw = _rtB -> B_12_97_0 - _rtB -> B_12_97_0 ;
} else { _rtZCSV -> MinMax_MinmaxInput_ZC_gw = _rtB -> B_12_97_0 - _rtB ->
B_12_63_0 ; } } else if ( _rtDW -> MinMax_MODE_d == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_gw = _rtB -> B_12_63_0 - _rtB -> B_12_97_0 ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_gw = _rtB -> B_12_63_0 - _rtB -> B_12_63_0 ;
} _rtZCSV -> Abs_AbsZc_ZC = _rtB -> B_12_144_0 ; if ( _rtDW -> Relay1_Mode )
{ _rtZCSV -> Relay1_RelayZC_ZC = _rtB -> B_12_145_0 - _rtP -> P_95 ; } else {
_rtZCSV -> Relay1_RelayZC_ZC = _rtB -> B_12_145_0 - _rtP -> P_94 ; } _rtZCSV
-> Abs_AbsZc_ZC_d = _rtB -> B_12_142_0 ; if ( _rtDW -> Relay2_Mode ) {
_rtZCSV -> Relay2_RelayZC_ZC = _rtB -> B_12_144_0 - _rtP -> P_100 ; } else {
_rtZCSV -> Relay2_RelayZC_ZC = _rtB -> B_12_144_0 - _rtP -> P_99 ; } _rtZCSV
-> RelationalOperator_RelopInput_ZC = _rtB -> B_12_147_0 - _rtB -> B_12_153_0
; _rtZCSV -> Saturation_UprLim_ZC_g = _rtB -> B_12_169_0 - _rtP -> P_103 ;
_rtZCSV -> Saturation_LwrLim_ZC_a = _rtB -> B_12_169_0 - _rtP -> P_104 ;
_rtZCSV -> Saturation1_UprLim_ZC_o = _rtB -> B_12_171_0 - _rtP -> P_105 ;
_rtZCSV -> Saturation1_LwrLim_ZC_d = _rtB -> B_12_171_0 - _rtP -> P_106 ; if
( ( _rtB -> B_12_67_0_n != _rtB -> B_12_67_0_n ) || ( _rtB -> B_12_173_0 >
_rtB -> B_12_67_0_n ) ) { if ( _rtDW -> MinMax_MODE_pf == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_gl = _rtB -> B_12_173_0 - _rtB -> B_12_173_0 ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_gl = _rtB -> B_12_173_0 - _rtB ->
B_12_67_0_n ; } } else if ( _rtDW -> MinMax_MODE_pf == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_gl = _rtB -> B_12_67_0_n - _rtB -> B_12_173_0 ; } else
{ _rtZCSV -> MinMax_MinmaxInput_ZC_gl = _rtB -> B_12_67_0_n - _rtB ->
B_12_67_0_n ; } if ( ( _rtB -> B_12_81_0_b != _rtB -> B_12_81_0_b ) || ( _rtB
-> B_12_180_0 < _rtB -> B_12_81_0_b ) ) { if ( _rtDW -> MinMax_MODE_n == 0 )
{ _rtZCSV -> MinMax_MinmaxInput_ZC_l = _rtB -> B_12_180_0 - _rtB ->
B_12_180_0 ; } else { _rtZCSV -> MinMax_MinmaxInput_ZC_l = _rtB -> B_12_180_0
- _rtB -> B_12_81_0_b ; } } else if ( _rtDW -> MinMax_MODE_n == 0 ) { _rtZCSV
-> MinMax_MinmaxInput_ZC_l = _rtB -> B_12_81_0_b - _rtB -> B_12_180_0 ; }
else { _rtZCSV -> MinMax_MinmaxInput_ZC_l = _rtB -> B_12_81_0_b - _rtB ->
B_12_81_0_b ; } if ( ( _rtB -> B_12_82_0 != _rtB -> B_12_82_0 ) || ( _rtB ->
B_12_186_0 > _rtB -> B_12_82_0 ) ) { if ( _rtDW -> MinMax_MODE_m == 0 ) {
_rtZCSV -> MinMax_MinmaxInput_ZC_m = _rtB -> B_12_186_0 - _rtB -> B_12_186_0
; } else { _rtZCSV -> MinMax_MinmaxInput_ZC_m = _rtB -> B_12_186_0 - _rtB ->
B_12_82_0 ; } } else if ( _rtDW -> MinMax_MODE_m == 0 ) { _rtZCSV ->
MinMax_MinmaxInput_ZC_m = _rtB -> B_12_82_0 - _rtB -> B_12_186_0 ; } else {
_rtZCSV -> MinMax_MinmaxInput_ZC_m = _rtB -> B_12_82_0 - _rtB -> B_12_82_0 ;
} if ( ( _rtB -> B_12_83_0_n != _rtB -> B_12_83_0_n ) || ( _rtB -> B_12_188_0
> _rtB -> B_12_83_0_n ) ) { if ( _rtDW -> MinMax1_MODE_l == 0 ) { _rtZCSV ->
MinMax1_MinmaxInput_ZC_m = _rtB -> B_12_188_0 - _rtB -> B_12_188_0 ; } else {
_rtZCSV -> MinMax1_MinmaxInput_ZC_m = _rtB -> B_12_188_0 - _rtB ->
B_12_83_0_n ; } } else if ( _rtDW -> MinMax1_MODE_l == 0 ) { _rtZCSV ->
MinMax1_MinmaxInput_ZC_m = _rtB -> B_12_83_0_n - _rtB -> B_12_188_0 ; } else
{ _rtZCSV -> MinMax1_MinmaxInput_ZC_m = _rtB -> B_12_83_0_n - _rtB ->
B_12_83_0_n ; } switch ( _rtDW -> IntegratorX_Oem_MODE ) { case 1 : _rtZCSV
-> IntegratorX_Oem_IntgUpLimit_ZC = 0.0 ; _rtZCSV ->
IntegratorX_Oem_IntgLoLimit_ZC = _rtP -> P_117 - _rtP -> P_118 ; break ; case
2 : _rtZCSV -> IntegratorX_Oem_IntgUpLimit_ZC = _rtP -> P_118 - _rtP -> P_117
; _rtZCSV -> IntegratorX_Oem_IntgLoLimit_ZC = 0.0 ; break ; default : _rtZCSV
-> IntegratorX_Oem_IntgUpLimit_ZC = _rtX -> IntegratorX_Oem_CSTATE - _rtP ->
P_117 ; _rtZCSV -> IntegratorX_Oem_IntgLoLimit_ZC = _rtX ->
IntegratorX_Oem_CSTATE - _rtP -> P_118 ; break ; } if ( ( _rtDW ->
IntegratorX_Oem_MODE == 3 ) || ( _rtDW -> IntegratorX_Oem_MODE == 4 ) ) {
_rtZCSV -> IntegratorX_Oem_LeaveSaturate_ZC = _rtB -> B_12_194_0 ; } else {
_rtZCSV -> IntegratorX_Oem_LeaveSaturate_ZC = 0.0 ; } if ( ( _rtB ->
B_12_73_0 != _rtB -> B_12_73_0 ) || ( _rtB -> B_12_94_0 < _rtB -> B_12_73_0 )
) { if ( _rtDW -> MinMax1_MODE_n == 0 ) { _rtZCSV -> MinMax1_MinmaxInput_ZC_d
= _rtB -> B_12_94_0 - _rtB -> B_12_94_0 ; } else { _rtZCSV ->
MinMax1_MinmaxInput_ZC_d = _rtB -> B_12_94_0 - _rtB -> B_12_73_0 ; } } else
if ( _rtDW -> MinMax1_MODE_n == 0 ) { _rtZCSV -> MinMax1_MinmaxInput_ZC_d =
_rtB -> B_12_73_0 - _rtB -> B_12_94_0 ; } else { _rtZCSV ->
MinMax1_MinmaxInput_ZC_d = _rtB -> B_12_73_0 - _rtB -> B_12_73_0 ; } if ( (
_rtB -> B_12_74_0_l != _rtB -> B_12_74_0_l ) || ( _rtB -> B_12_206_0 > _rtB
-> B_12_74_0_l ) ) { if ( _rtDW -> MinMax2_MODE_m == 0 ) { _rtZCSV ->
MinMax2_MinmaxInput_ZC_g = _rtB -> B_12_206_0 - _rtB -> B_12_206_0 ; } else {
_rtZCSV -> MinMax2_MinmaxInput_ZC_g = _rtB -> B_12_206_0 - _rtB ->
B_12_74_0_l ; } } else if ( _rtDW -> MinMax2_MODE_m == 0 ) { _rtZCSV ->
MinMax2_MinmaxInput_ZC_g = _rtB -> B_12_74_0_l - _rtB -> B_12_206_0 ; } else
{ _rtZCSV -> MinMax2_MinmaxInput_ZC_g = _rtB -> B_12_74_0_l - _rtB ->
B_12_74_0_l ; } if ( ( _rtB -> B_12_26_0 != _rtB -> B_12_26_0 ) || ( _rtB ->
B_12_84_0_b > _rtB -> B_12_26_0 ) ) { if ( _rtDW -> MinMax_MODE_j == 0 ) {
_rtZCSV -> MinMax_MinmaxInput_ZC_mz = _rtB -> B_12_84_0_b - _rtB ->
B_12_84_0_b ; } else { _rtZCSV -> MinMax_MinmaxInput_ZC_mz = _rtB ->
B_12_84_0_b - _rtB -> B_12_26_0 ; } } else if ( _rtDW -> MinMax_MODE_j == 0 )
{ _rtZCSV -> MinMax_MinmaxInput_ZC_mz = _rtB -> B_12_26_0 - _rtB ->
B_12_84_0_b ; } else { _rtZCSV -> MinMax_MinmaxInput_ZC_mz = _rtB ->
B_12_26_0 - _rtB -> B_12_26_0 ; } _rtZCSV -> SwitchPSI_SwitchCond_ZC = _rtB
-> B_12_214_0 - _rtP -> P_123 ; _rtZCSV -> Saturation_UprLim_ZC_i4 = _rtB ->
B_12_218_0 - _rtP -> P_124 ; _rtZCSV -> Saturation_LwrLim_ZC_d = _rtB ->
B_12_218_0 - _rtP -> P_125 ; _rtZCSV -> Saturation1_UprLim_ZC_a = _rtB ->
B_12_220_0 - _rtP -> P_126 ; _rtZCSV -> Saturation1_LwrLim_ZC_k = _rtB ->
B_12_220_0 - _rtP -> P_127 ; _rtZCSV -> RelationalOperator_RelopInput_ZC_g =
_rtB -> B_12_18_0 - _rtB -> B_12_87_0 ; } static void mdlInitializeSizes (
SimStruct * S ) { ssSetChecksumVal ( S , 0 , 2007992507U ) ; ssSetChecksumVal
( S , 1 , 3418777030U ) ; ssSetChecksumVal ( S , 2 , 1896028202U ) ;
ssSetChecksumVal ( S , 3 , 371624180U ) ; { mxArray * slVerStructMat = ( NULL
) ; mxArray * slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10
] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat ,
"ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField (
slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) { status = 1 ;
} else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.7" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != ( SLSize ) sizeof ( DW_TruckBenchmark_T ) ) { static char msg [ 256 ]
; sprintf ( msg , "Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof ( DW_TruckBenchmark_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } if ( ssGetSizeofGlobalBlockIO ( S ) != (
SLSize ) sizeof ( B_TruckBenchmark_T ) ) { static char msg [ 256 ] ; sprintf
( msg , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof (
B_TruckBenchmark_T ) ) ; ssSetErrorStatus ( S , msg ) ; } { int
ssSizeofParams ; ssGetSizeofParams ( S , & ssSizeofParams ) ; if (
ssSizeofParams != sizeof ( P_TruckBenchmark_T ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_TruckBenchmark_T ) ) ; ssSetErrorStatus ( S , msg
) ; } } _ssSetModelRtp ( S , ( real_T * ) & TruckBenchmark_rtDefaultP ) ;
_ssSetConstBlockIO ( S , & TruckBenchmark_rtInvariant ) ; rt_InitInfAndNaN (
sizeof ( real_T ) ) ; ( ( P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) ->
P_18 = rtInf ; ( ( P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) -> P_22 =
rtInf ; ( ( P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) -> P_40 = rtInf ; (
( P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) -> P_45 = rtInf ; ( (
P_TruckBenchmark_T * ) ssGetModelRtp ( S ) ) -> P_105 = rtInf ; } static void
mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct * childS ;
SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 2 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 3 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 4 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 5 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 6 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID6 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
