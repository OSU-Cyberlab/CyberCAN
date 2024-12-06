#include "TruckBenchmark.h"
#include "rtwtypes.h"
#include "mwmathutil.h"
#include "rt_look.h"
#include "rt_look1d.h"
#include <float.h>
#include "mwstringutil.h"
#include <stddef.h>
#include "TruckBenchmark_private.h"
#include "rt_logging_mmi.h"
#include "TruckBenchmark_capi.h"
#include "multiword_types.h"
#include "TruckBenchmark_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; void
raccelForceExtModeShutdown ( boolean_T extModeStartPktReceived ) { if ( !
extModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 6 , & stopRequested ) ; }
rtExtModeShutdown ( 6 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 7 ; const char_T
* gbl_raccel_Version = "10.7 (R2023a) 19-Nov-2022" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const int_T gblNumRootInportBlks = 0 ; const int_T
gblNumModelInputs = 0 ; extern const char * gblInportFileName ; extern
rtInportTUtable * gblInportTUtables ; const int_T gblInportDataTypeIdx [ ] =
{ - 1 } ; const int_T gblInportDims [ ] = { - 1 } ; const int_T
gblInportComplex [ ] = { - 1 } ; const int_T gblInportInterpoFlag [ ] = { - 1
} ; const int_T gblInportContinuous [ ] = { - 1 } ; int_T enableFcnCallFlag [
] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; const char *
raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const char *
inportFileName , int * matFileFormat ) { return rt_RAccelReadInportsMatFile (
S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
#define dcctc4vfs1 (-1)
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ;
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ;
#endif
void * rt_TDelayCreateBuf ( int_T numBuffer , int_T bufSz , int_T elemSz ) {
return ( ( void * ) utMalloc ( numBuffer * bufSz * elemSz ) ) ; }
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * uBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * uBufPtr + bufSz ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ;
if ( istransportdelay ) { numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; }
testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <=
tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
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
; } } return ( yp [ 0U ] ) ; } real_T rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx ,
int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete ,
boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2
, u1 , u2 ; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) && (
oldestIdx == 0 ) && ( tMinusDelay > tStart ) ) return initOutput ; if (
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
maxIndex , real_T * fraction , uint32_T * prevIndex ) { uint32_T bpIndex ; if
( u <= bp [ 0U ] ) { bpIndex = 0U ; * fraction = ( u - bp [ 0U ] ) / ( bp [
1U ] - bp [ 0U ] ) ; } else if ( u < bp [ maxIndex ] ) { bpIndex =
binsearch_u32d_prevIdx ( u , bp , * prevIndex , maxIndex ) ; * fraction = ( u
- bp [ bpIndex ] ) / ( bp [ bpIndex + 1U ] - bp [ bpIndex ] ) ; } else {
bpIndex = maxIndex - 1U ; * fraction = ( u - bp [ maxIndex - 1U ] ) / ( bp [
maxIndex ] - bp [ maxIndex - 1U ] ) ; } * prevIndex = bpIndex ; return
bpIndex ; } uint32_T binsearch_u32d_prevIdx ( real_T u , const real_T bp [ ]
, uint32_T startIndex , uint32_T maxIndex ) { uint32_T bpIndex ; uint32_T
found ; uint32_T iLeft ; uint32_T iRght ; bpIndex = startIndex ; iLeft = 0U ;
iRght = maxIndex ; found = 0U ; while ( found == 0U ) { if ( u < bp [ bpIndex
] ) { iRght = bpIndex - 1U ; bpIndex = ( ( bpIndex + iLeft ) - 1U ) >> 1U ; }
else if ( u < bp [ bpIndex + 1U ] ) { found = 1U ; } else { iLeft = bpIndex +
1U ; bpIndex = ( ( bpIndex + iRght ) + 1U ) >> 1U ; } } return bpIndex ; }
#ifndef __RTW_UTFREE__  
extern void utFree ( void * ) ;
#endif
void rt_TDelayFreeBuf ( void * buf ) { utFree ( buf ) ; } void MdlInitialize
( void ) { rtX . cwf2tewh2v = rtP . Integrator_IC ; rtX . lpegok4bfi = rtP .
Integrator1_IC ; rtX . akhhz2ar2w = rtP . model . engine . omega_t_Init ; rtX
. ekar034xyr = rtP . model . engine . p_im_Init ; rtX . aufcyghqde = rtP .
Integrator1_IC_mck3mtbbq3 ; rtDW . mluvktfvfy = rtP . scenario . gear_init ;
rtX . gdrfqkaj00 = rtP . model . engine . uInit_egr ; rtX . dl0s2litjt = rtP
. model . engine . uInit_egr ; rtDW . jtxmye3nth = rtP .
Memory3_InitialCondition ; rtX . a3o55becan = rtP . model . engine .
p_em_Init ; rtDW . mp0kaoewzv = rtP . Memory2_InitialCondition ; rtDW .
l2wwwtxl4l = rtP . model . engine . x_r_Init ; rtDW . ox1qbuvuuc = rtP .
model . engine . T_1_Init ; rtX . olhqyyiiqq = rtP . IntegratorX_Oim_IC ; rtX
. faiarhiizk = rtP . scenario . h_0 ; rtX . f10gbcy5as = rtP .
Integrator_IC_ikgusueg51 ; rtX . d0etugyxyo = rtP . model . engine .
uInit_vgt ; rtDW . jahel4guj4 = rtP . Memory1_InitialCondition ; rtX .
fteoprdfjw = rtP . IntegratorX_Oem_IC ; rtDW . ndy1r3lteo = dcctc4vfs1 ; rtDW
. ksp31oyn4z = false ; rtDW . gwi2bo5yvs = false ; rtDW . dedzusgrw0 = false
; rtDW . dqrx4b5l1l = false ; rtDW . ei55bolyl0 = false ; rtDW . frdq0ezqxz =
false ; rtDW . pu1q4zlmwb = 0U ; rtDW . n3jvfqlh1d = 0.0 ; rtDW . h1t2m1slzp
= 4.0 ; rtDW . jie24f0s0n = 0.0 ; rtDW . bih1twzowf = dcctc4vfs1 ; rtDW .
eda54vucfl = 0U ; rtDW . jcb0vgamw2 = dcctc4vfs1 ; rtDW . e4lgtlqce2 = 0U ;
rtDW . o0eadiapoc = 4.0 ; rtDW . asj3qcjbaz = true ; rtDW . evb2jcnsmb =
dcctc4vfs1 ; rtDW . mnycq5gn5i = 0U ; rtDW . bzxfv0jxlh = 4.0 ; rtDW .
adrllpi2ax = true ; rtDW . ozxovagibo = 4.0 ; rtDW . cqvouu2ka3 = true ; rtB
. n22fqqxpxo = rtP . gear_Y0 ; rtB . d3yr0hfu1a = rtP . u_vgt_Y0 ; rtB .
j2q40ay2j1 = rtP . u_egr_Y0 ; rtB . kc4ngec1x5 = rtP . u_delta_Y0 ; rtB .
b0oj4tfbt4 = rtP . F_brake_Y0 ; rtDW . ono0qix5io = dcctc4vfs1 ; rtDW .
pe5pl50ynw = 0U ; } void MdlEnable ( void ) { char_T * sErr ; sErr =
GetErrorBuffer ( & rtDW . ozecqffs1t [ 0U ] ) ; LibReset ( & rtDW .
ozecqffs1t [ 0U ] ) ; LibStart ( & rtDW . ozecqffs1t [ 0U ] ) ; if ( * sErr
!= 0 ) { ssSetErrorStatus ( rtS , sErr ) ; ssSetStopRequested ( rtS , 1 ) ; }
rtDW . ok1wan2u4e = false ; rtDW . imduqxhj3y = 1 ; _ssSetSampleHit ( rtS , 5
, 1 ) ; _ssSetTaskTime ( rtS , 5 , ssGetT ( rtS ) ) ; _ssSetVarNextHitTime (
rtS , 0 , ssGetT ( rtS ) ) ; ; } void MdlStart ( void ) { real_T stdIDsEnd ;
real_T stdIDsStart ; int32_T bitParams [ 4 ] ; int32_T bitParams_p [ 4 ] ;
int32_T idMaskParams [ 4 ] ; int32_T pathSize ; uint32_T extIDs ; uint32_T
stdIDs ; char_T * converterUpdatePath ; char_T * converterUpdatePath_p ;
char_T * libUpdatePath ; char_T * libUpdatePath_p ; char_T * pluginUpdatePath
; char_T * pluginUpdatePath_p ; char_T * sErr ; char_T * vendorUpdatePath ;
char_T * vendorUpdatePath_p ; { bool externalInputIsInDatasetFormat = false ;
void * pISigstreamManager = rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} { { { bool isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU
srcInfo ; sdiLabelU sigName = sdiGetLabelFromChars ( "CAN Pack" ) ; sdiLabelU
blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Controller/CAN TX//RX/To Workspace" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiHierarchyDefinition hTopBusHier ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
hTopBusHier = sdiCreateBusHierDefinition ( ( NULL ) , "CAN Pack" , & sigDims
, sizeof ( CAN_MESSAGE_BUS ) ) ; { sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_UINT8 ) ; { sdiComplexity
sigComplexity = REAL ; sdiLabelU units = sdiGetLabelFromChars ( "" ) ;
sdiDims childSigDims ; int_T childSigDimsArray [ 1 ] = { 1 } ; childSigDims .
nDims = 1 ; childSigDims . dimensions = childSigDimsArray ; sdiAddBusHierLeaf
( hTopBusHier , ".Extended" , units , 0 , hDT , sigComplexity , &
childSigDims , stCont ) ; sdiFreeLabel ( units ) ; } } {
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT8 ) ; { sdiComplexity sigComplexity = REAL ; sdiLabelU units =
sdiGetLabelFromChars ( "" ) ; sdiDims childSigDims ; int_T childSigDimsArray
[ 1 ] = { 1 } ; childSigDims . nDims = 1 ; childSigDims . dimensions =
childSigDimsArray ; sdiAddBusHierLeaf ( hTopBusHier , "Length" , units , 1 ,
hDT , sigComplexity , & childSigDims , stCont ) ; sdiFreeLabel ( units ) ; }
} { sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT8 ) ; { sdiComplexity sigComplexity = REAL ; sdiLabelU units =
sdiGetLabelFromChars ( "" ) ; sdiDims childSigDims ; int_T childSigDimsArray
[ 1 ] = { 1 } ; childSigDims . nDims = 1 ; childSigDims . dimensions =
childSigDimsArray ; sdiAddBusHierLeaf ( hTopBusHier , "Remote" , units , 2 ,
hDT , sigComplexity , & childSigDims , stCont ) ; sdiFreeLabel ( units ) ; }
} { sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT8 ) ; { sdiComplexity sigComplexity = REAL ; sdiLabelU units =
sdiGetLabelFromChars ( "" ) ; sdiDims childSigDims ; int_T childSigDimsArray
[ 1 ] = { 1 } ; childSigDims . nDims = 1 ; childSigDims . dimensions =
childSigDimsArray ; sdiAddBusHierLeaf ( hTopBusHier , "Error" , units , 3 ,
hDT , sigComplexity , & childSigDims , stCont ) ; sdiFreeLabel ( units ) ; }
} { sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT32 ) ; { sdiComplexity sigComplexity = REAL ; sdiLabelU units =
sdiGetLabelFromChars ( "" ) ; sdiDims childSigDims ; int_T childSigDimsArray
[ 1 ] = { 1 } ; childSigDims . nDims = 1 ; childSigDims . dimensions =
childSigDimsArray ; sdiAddBusHierLeaf ( hTopBusHier , "ID" , units , 4 , hDT
, sigComplexity , & childSigDims , stCont ) ; sdiFreeLabel ( units ) ; } } {
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ; sdiLabelU units =
sdiGetLabelFromChars ( "" ) ; sdiDims childSigDims ; int_T childSigDimsArray
[ 1 ] = { 1 } ; childSigDims . nDims = 1 ; childSigDims . dimensions =
childSigDimsArray ; sdiAddBusHierLeaf ( hTopBusHier , "Timestamp" , units , 8
, hDT , sigComplexity , & childSigDims , stCont ) ; sdiFreeLabel ( units ) ;
} } { sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT8 ) ; { sdiComplexity sigComplexity = REAL ; sdiLabelU units =
sdiGetLabelFromChars ( "" ) ; sdiDims childSigDims ; int_T childSigDimsArray
[ 1 ] = { 8 } ; childSigDims . nDims = 1 ; childSigDims . dimensions =
childSigDimsArray ; sdiAddBusHierLeaf ( hTopBusHier , "Data" , units , 16 ,
hDT , sigComplexity , & childSigDims , stCont ) ; sdiFreeLabel ( units ) ; }
} srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = (
sdiFullBlkPathU ) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ;
srcInfo . subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo .
signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . gtasy1jsdx .
AQHandles = sdiCreateAsyncQueueForNVBus ( & hTopBusHier , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"669c2346-e947-4210-8f6c-6b9e9fbf39b9" , 24 , & sigDims , stCont , 1 , 0 ,
"CAN Pack" , "" , "CAN Pack" ) ; if ( rtDW . gtasy1jsdx . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . gtasy1jsdx . AQHandles , "Continuous" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . gtasy1jsdx .
AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . gtasy1jsdx . AQHandles ,
ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetBlockPathDomain ( rtDW .
gtasy1jsdx . AQHandles ) ; } sdiFreeLabel ( sigName ) ; sdiFreeLabel (
blockPath ) ; sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"canraw" ) ; sdiRegisterWksVariable ( rtDW . gtasy1jsdx . AQHandles , varName
, "timeseries" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "gear" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "gear" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Controller/Controller/Gear control" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "gear" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . p4sflk0g2w . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "f1c67a3e-dc81-420a-9182-d6cebf4a8758" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . p4sflk0g2w . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . p4sflk0g2w . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . p4sflk0g2w . AQHandles , "Triggered" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . p4sflk0g2w .
AQHandles , 1.0 ) ; sdiSetRunStartTime ( rtDW . p4sflk0g2w . AQHandles ,
ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW .
p4sflk0g2w . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW .
p4sflk0g2w . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "u_delta" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "u_delta" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Controller/Controller/Saturation" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "u_delta" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . ofz4kqfoe0 . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "c423a44d-307c-477e-9ccb-dd7d5f3a6b55" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . ofz4kqfoe0 . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . ofz4kqfoe0 . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . ofz4kqfoe0 . AQHandles , "Triggered" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . ofz4kqfoe0 .
AQHandles , 1.0 ) ; sdiSetRunStartTime ( rtDW . ofz4kqfoe0 . AQHandles ,
ssGetTaskTime ( rtS , 4 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW .
ofz4kqfoe0 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW .
ofz4kqfoe0 . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "fuelConsumption" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "fuelConsumption" ) ; sdiLabelU propName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Fuel consumption dm^3//(100km)" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "fuelConsumption" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. p33krp3hyb . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"e8a43e5e-6d4f-4f9f-92ca-686ddd41bd20" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . p33krp3hyb . AQHandles , hDT , & srcInfo ) ; if ( rtDW . p33krp3hyb .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . p33krp3hyb . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
p33krp3hyb . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . p33krp3hyb .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . p33krp3hyb . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . p33krp3hyb . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "clutch_pos" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "clutch_pos" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Transmission Control Unit" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "clutch_pos" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. dzibnwkozv . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"d4e13f0c-9965-40af-ba06-5169a6a78e3e" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . dzibnwkozv . AQHandles , hDT , & srcInfo ) ; if ( rtDW . dzibnwkozv .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . dzibnwkozv . AQHandles ,
"2e-05" , 2.0E-5 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
dzibnwkozv . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . dzibnwkozv .
AQHandles , ssGetTaskTime ( rtS , 2 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . dzibnwkozv . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . dzibnwkozv . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "curr_gear" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "curr_gear" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Transmission Control Unit" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "curr_gear" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 1 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. m2ysthz4lp . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"fc22c2ed-60b3-421f-9e6e-a7a57cc0e8a2" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . m2ysthz4lp . AQHandles , hDT , & srcInfo ) ; if ( rtDW . m2ysthz4lp .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . m2ysthz4lp . AQHandles ,
"2e-05" , 2.0E-5 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
m2ysthz4lp . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . m2ysthz4lp .
AQHandles , ssGetTaskTime ( rtS , 2 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . m2ysthz4lp . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . m2ysthz4lp . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "n_engine" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "n_engine" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/rad//s -> RPM" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "n_engine" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . ltc2bikvjk . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "77cb1245-37e6-4302-8ff8-db075c654335" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . ltc2bikvjk . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . ltc2bikvjk . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . ltc2bikvjk . AQHandles , "Continuous" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . ltc2bikvjk .
AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . ltc2bikvjk . AQHandles ,
ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW .
ltc2bikvjk . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW .
ltc2bikvjk . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "x_distance" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "x_distance" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Chassi/Integrator1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "x_distance" )
; sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . fwhtblllbe . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "8a4c1310-1803-4840-8be5-041a7986f677" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . fwhtblllbe . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . fwhtblllbe . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . fwhtblllbe . AQHandles , "Continuous" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . fwhtblllbe .
AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . fwhtblllbe . AQHandles ,
ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW .
fwhtblllbe . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW .
fwhtblllbe . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "v_vehicle" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "v_vehicle" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Chassi/m//s -> km//h" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "v_vehicle" )
; sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . kyvzs2v1y5 . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "c4ac991a-69aa-4a95-b069-a18d8af132f7" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . kyvzs2v1y5 . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . kyvzs2v1y5 . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . kyvzs2v1y5 . AQHandles , "Continuous" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . kyvzs2v1y5 .
AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . kyvzs2v1y5 . AQHandles ,
ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW .
kyvzs2v1y5 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW .
kyvzs2v1y5 . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "M_c" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "M_c" ) ; sdiLabelU propName = sdiGetLabelFromChars
( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "M_c" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. a5wlo524la . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"8ba86b7f-f1b6-465c-87b7-39eb9a8e17e1" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . a5wlo524la . AQHandles , hDT , & srcInfo ) ; if ( rtDW . a5wlo524la .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . a5wlo524la . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
a5wlo524la . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . a5wlo524la .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . a5wlo524la . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . a5wlo524la . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "cl_lock" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "cl_lock" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits"
) ; sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "cl_lock" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. osoqnotoxt . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"ff7a4605-ab0f-43a0-ac03-b602c343430f" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . osoqnotoxt . AQHandles , hDT , & srcInfo ) ; if ( rtDW . osoqnotoxt .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . osoqnotoxt . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
osoqnotoxt . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . osoqnotoxt .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . osoqnotoxt . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . osoqnotoxt . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "M_c_max" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "M_c_max" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits"
) ; sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "M_c_max" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 1 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. afai5j1n5f . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"7ff6934c-061d-46e3-bdb8-0411d8b7d47c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . afai5j1n5f . AQHandles , hDT , & srcInfo ) ; if ( rtDW . afai5j1n5f .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . afai5j1n5f . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
afai5j1n5f . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . afai5j1n5f .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . afai5j1n5f . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . afai5j1n5f . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "Mux1" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "Mux1" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
(
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/To Workspace"
) ; sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "Mux1" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 3 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. gtasy1jsdxk . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"c46e591f-0528-47c5-a408-43e8ab65e6d9" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . gtasy1jsdxk . AQHandles , hDT , & srcInfo ) ; if ( rtDW . gtasy1jsdxk
. AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . gtasy1jsdxk . AQHandles
, "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
gtasy1jsdxk . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . gtasy1jsdxk .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . gtasy1jsdxk . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName
( rtDW . gtasy1jsdxk . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . gtasy1jsdxk . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"C" ) ; sdiRegisterWksVariable ( rtDW . gtasy1jsdxk . AQHandles , varName ,
"structwithtime" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "lambda" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "lambda" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "lambda" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . jtwmyt455q . AQHandles =
sdiStartAsyncioQueueCreation ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "9d2098b9-a8ea-4f0e-a828-c57639548f5f" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ;
sdiCompleteAsyncioQueueCreation ( rtDW . jtwmyt455q . AQHandles , hDT , &
srcInfo ) ; if ( rtDW . jtwmyt455q . AQHandles ) {
sdiSetSignalSampleTimeString ( rtDW . jtwmyt455q . AQHandles , "Continuous" ,
0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW . jtwmyt455q .
AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . jtwmyt455q . AQHandles ,
ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW .
jtwmyt455q . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW .
jtwmyt455q . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "k_slope" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "k_slope" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Road Slope Data/1-D Lookup Table" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "k_slope" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. o0cbjrpiwk . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"5e272ecd-5404-4946-8a8d-0fbc60e17d5c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . o0cbjrpiwk . AQHandles , hDT , & srcInfo ) ; if ( rtDW . o0cbjrpiwk .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . o0cbjrpiwk . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
o0cbjrpiwk . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . o0cbjrpiwk .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . o0cbjrpiwk . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . o0cbjrpiwk . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "altitude" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "altitude" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Road Slope Data/Integrator" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "altitude" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. dakk2fhtjk . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"7c0e52f0-8966-4668-a86f-6d9a95d475c0" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . dakk2fhtjk . AQHandles , hDT , & srcInfo ) ; if ( rtDW . dakk2fhtjk .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . dakk2fhtjk . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
dakk2fhtjk . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . dakk2fhtjk .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . dakk2fhtjk . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . dakk2fhtjk . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "BSR" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"BSR" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace33" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "BSR" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. bzrmj3zxqu . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"9d17ac33-5326-4469-8add-0fa1f68ee214" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . bzrmj3zxqu . AQHandles , hDT , & srcInfo ) ; if ( rtDW . bzrmj3zxqu .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . bzrmj3zxqu . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
bzrmj3zxqu . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . bzrmj3zxqu .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . bzrmj3zxqu . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . bzrmj3zxqu . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . bzrmj3zxqu . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simBSR" ) ; sdiRegisterWksVariable ( rtDW . bzrmj3zxqu . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "Clock" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "Clock" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace5" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "Clock" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. pudhr5q1sv . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"c1996d23-528a-4c3e-a81f-9199aa43a48d" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . pudhr5q1sv . AQHandles , hDT , & srcInfo ) ; if ( rtDW . pudhr5q1sv .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . pudhr5q1sv . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
pudhr5q1sv . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . pudhr5q1sv .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . pudhr5q1sv . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . pudhr5q1sv . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . pudhr5q1sv . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simTime" ) ; sdiRegisterWksVariable ( rtDW . pudhr5q1sv . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "M_e" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"M_e" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace13" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "M_e" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. ahb0xajdg5 . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"b628fd2e-7560-47ec-8510-4802ad11f326" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . ahb0xajdg5 . AQHandles , hDT , & srcInfo ) ; if ( rtDW . ahb0xajdg5 .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . ahb0xajdg5 . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
ahb0xajdg5 . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . ahb0xajdg5 .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . ahb0xajdg5 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . ahb0xajdg5 . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . ahb0xajdg5 . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simM_e" ) ; sdiRegisterWksVariable ( rtDW . ahb0xajdg5 . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "P_c" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"P_c" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace11" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "P_c" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. jj02cyrtix . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"89946ea5-0a95-45e1-bb2d-412a394fc0b4" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . jj02cyrtix . AQHandles , hDT , & srcInfo ) ; if ( rtDW . jj02cyrtix .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . jj02cyrtix . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
jj02cyrtix . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . jj02cyrtix .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . jj02cyrtix . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . jj02cyrtix . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . jj02cyrtix . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simP_c" ) ; sdiRegisterWksVariable ( rtDW . jj02cyrtix . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "P_tm" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "P_tm" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace12" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "P_tm" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. mduldnxlmb . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"e4735760-7d08-48b4-8bf9-6fa3c605fdb2" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . mduldnxlmb . AQHandles , hDT , & srcInfo ) ; if ( rtDW . mduldnxlmb .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . mduldnxlmb . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
mduldnxlmb . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . mduldnxlmb .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . mduldnxlmb . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . mduldnxlmb . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . mduldnxlmb . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simP_tm" ) ; sdiRegisterWksVariable ( rtDW . mduldnxlmb . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "T_1" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"T_1" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace31" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "T_1" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. o2domeg4ik . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"3eeda0f6-a873-46e5-bc38-8b0020dcb907" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . o2domeg4ik . AQHandles , hDT , & srcInfo ) ; if ( rtDW . o2domeg4ik .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . o2domeg4ik . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
o2domeg4ik . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . o2domeg4ik .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . o2domeg4ik . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . o2domeg4ik . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . o2domeg4ik . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simT_1" ) ; sdiRegisterWksVariable ( rtDW . o2domeg4ik . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "T_c" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"T_c" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "T_c" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. gtasy1jsdxk2 . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"e2a6f193-28d5-42bc-90de-1d5a8b123142" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . gtasy1jsdxk2 . AQHandles , hDT , & srcInfo ) ; if ( rtDW .
gtasy1jsdxk2 . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW .
gtasy1jsdxk2 . AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ;
sdiSetSignalRefRate ( rtDW . gtasy1jsdxk2 . AQHandles , 0.0 ) ;
sdiSetRunStartTime ( rtDW . gtasy1jsdxk2 . AQHandles , ssGetTaskTime ( rtS ,
0 ) ) ; sdiAsyncRepoSetSignalExportSettings ( rtDW . gtasy1jsdxk2 . AQHandles
, 1 , 0 ) ; sdiAsyncRepoSetSignalExportName ( rtDW . gtasy1jsdxk2 . AQHandles
, loggedName , origSigName , propName ) ; sdiAsyncRepoSetBlockPathDomain (
rtDW . gtasy1jsdxk2 . AQHandles ) ; } sdiFreeLabel ( sigName ) ; sdiFreeLabel
( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel ( propName ) ;
sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ; sdiFreeLabel (
subPath ) ; } } if ( ! isStreamoutAlreadyRegistered ) { { sdiLabelU varName =
sdiGetLabelFromChars ( "simT_c" ) ; sdiRegisterWksVariable ( rtDW .
gtasy1jsdxk2 . AQHandles , varName , "array" ) ; sdiFreeLabel ( varName ) ; }
} } } } { { { bool isStreamoutAlreadyRegistered = false ; {
sdiSignalSourceInfoU srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars (
"T_e" ) ; sdiLabelU origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "T_e" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace2" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "T_e" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. mhg3ukoydp . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"57f7197f-b2db-4b6e-8640-e4c735aca13c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . mhg3ukoydp . AQHandles , hDT , & srcInfo ) ; if ( rtDW . mhg3ukoydp .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . mhg3ukoydp . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
mhg3ukoydp . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . mhg3ukoydp .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . mhg3ukoydp . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . mhg3ukoydp . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . mhg3ukoydp . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simT_e" ) ; sdiRegisterWksVariable ( rtDW . mhg3ukoydp . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "T_em" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "T_em" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace29" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "T_em" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. kqufha1qme . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"a118fd13-3141-4f15-b4d4-123b6e630927" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . kqufha1qme . AQHandles , hDT , & srcInfo ) ; if ( rtDW . kqufha1qme .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . kqufha1qme . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
kqufha1qme . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . kqufha1qme .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . kqufha1qme . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . kqufha1qme . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . kqufha1qme . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simT_em" ) ; sdiRegisterWksVariable ( rtDW . kqufha1qme . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "W_c" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"W_c" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace7" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "W_c" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. ck00fvktvl . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"7beed1f0-06a7-429a-bda0-039cb013c387" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . ck00fvktvl . AQHandles , hDT , & srcInfo ) ; if ( rtDW . ck00fvktvl .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . ck00fvktvl . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
ck00fvktvl . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . ck00fvktvl .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . ck00fvktvl . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . ck00fvktvl . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . ck00fvktvl . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simW_c" ) ; sdiRegisterWksVariable ( rtDW . ck00fvktvl . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "W_egr" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "W_egr" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace6" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "W_egr" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. fsc12ul0nq . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"b6a6abf1-9795-482f-9ec8-cb3e4d65d655" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . fsc12ul0nq . AQHandles , hDT , & srcInfo ) ; if ( rtDW . fsc12ul0nq .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . fsc12ul0nq . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
fsc12ul0nq . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . fsc12ul0nq .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . fsc12ul0nq . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . fsc12ul0nq . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . fsc12ul0nq . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simW_egr" ) ; sdiRegisterWksVariable ( rtDW . fsc12ul0nq . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "W_ei" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "W_ei" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace9" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "W_ei" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. jk5klgbkjx . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"50085ef8-2b35-496f-8963-2aac2fb1e605" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . jk5klgbkjx . AQHandles , hDT , & srcInfo ) ; if ( rtDW . jk5klgbkjx .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . jk5klgbkjx . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
jk5klgbkjx . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . jk5klgbkjx .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . jk5klgbkjx . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . jk5klgbkjx . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . jk5klgbkjx . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simW_ei" ) ; sdiRegisterWksVariable ( rtDW . jk5klgbkjx . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "W_eo" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "W_eo" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace10" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "W_eo" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. bgmhbb2ggj . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"1a32456b-1e0e-41b4-804c-1153d584eb69" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . bgmhbb2ggj . AQHandles , hDT , & srcInfo ) ; if ( rtDW . bgmhbb2ggj .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . bgmhbb2ggj . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
bgmhbb2ggj . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . bgmhbb2ggj .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . bgmhbb2ggj . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . bgmhbb2ggj . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . bgmhbb2ggj . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simW_eo" ) ; sdiRegisterWksVariable ( rtDW . bgmhbb2ggj . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "W_f" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"W_f" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace22" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "W_f" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. jfed40pyro . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"fb58e013-3659-42a1-b1d7-77b96671e50c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . jfed40pyro . AQHandles , hDT , & srcInfo ) ; if ( rtDW . jfed40pyro .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . jfed40pyro . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
jfed40pyro . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . jfed40pyro .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . jfed40pyro . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . jfed40pyro . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . jfed40pyro . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simW_f" ) ; sdiRegisterWksVariable ( rtDW . jfed40pyro . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "W_t" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"W_t" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace8" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "W_t" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. mgmkqdnd4h . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"8271c8fa-a3fb-4472-bdcd-8627d063e86f" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . mgmkqdnd4h . AQHandles , hDT , & srcInfo ) ; if ( rtDW . mgmkqdnd4h .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . mgmkqdnd4h . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
mgmkqdnd4h . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . mgmkqdnd4h .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . mgmkqdnd4h . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . mgmkqdnd4h . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . mgmkqdnd4h . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simW_t" ) ; sdiRegisterWksVariable ( rtDW . mgmkqdnd4h . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "X_Oem" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "X_Oem" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace30" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "X_Oem" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. cqmz0ka510 . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"26477d8c-c018-4437-b435-5c2318e92cd0" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . cqmz0ka510 . AQHandles , hDT , & srcInfo ) ; if ( rtDW . cqmz0ka510 .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . cqmz0ka510 . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
cqmz0ka510 . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . cqmz0ka510 .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . cqmz0ka510 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . cqmz0ka510 . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . cqmz0ka510 . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simX_Oem" ) ; sdiRegisterWksVariable ( rtDW . cqmz0ka510 . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "X_Oim" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "X_Oim" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace25" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "X_Oim" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. awm3x1p030 . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"d5c86864-ea41-4c83-a5a6-b288abc912ae" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . awm3x1p030 . AQHandles , hDT , & srcInfo ) ; if ( rtDW . awm3x1p030 .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . awm3x1p030 . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
awm3x1p030 . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . awm3x1p030 .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . awm3x1p030 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . awm3x1p030 . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . awm3x1p030 . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simX_Oim" ) ; sdiRegisterWksVariable ( rtDW . awm3x1p030 . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "n_t" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"n_t" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace14" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "n_t" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. pz3v3lsswe . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"dcdae2dd-ba00-4dec-8653-0d48e3a2d35f" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . pz3v3lsswe . AQHandles , hDT , & srcInfo ) ; if ( rtDW . pz3v3lsswe .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . pz3v3lsswe . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
pz3v3lsswe . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . pz3v3lsswe .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . pz3v3lsswe . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . pz3v3lsswe . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . pz3v3lsswe . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simn_t" ) ; sdiRegisterWksVariable ( rtDW . pz3v3lsswe . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "lambda" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "lambda" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace15" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "lambda" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. nji534mx2v . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"27ccd7aa-0821-45ec-884e-be173d1cdd60" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . nji534mx2v . AQHandles , hDT , & srcInfo ) ; if ( rtDW . nji534mx2v .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . nji534mx2v . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
nji534mx2v . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . nji534mx2v .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . nji534mx2v . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . nji534mx2v . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . nji534mx2v . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simlambda" ) ; sdiRegisterWksVariable ( rtDW . nji534mx2v . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "u_delta" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "u_delta" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace16" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "u_delta" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. kn50mamzgm . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"2832c597-ff84-4e04-ada3-f3556359c57e" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . kn50mamzgm . AQHandles , hDT , & srcInfo ) ; if ( rtDW . kn50mamzgm .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . kn50mamzgm . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
kn50mamzgm . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . kn50mamzgm .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . kn50mamzgm . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . kn50mamzgm . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . kn50mamzgm . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simu_delta" ) ; sdiRegisterWksVariable ( rtDW . kn50mamzgm . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "u_egr" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "u_egr" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace17" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "u_egr" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. lz2njt4sro . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"f1c18344-5d03-44ed-bc95-d5de1323d527" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . lz2njt4sro . AQHandles , hDT , & srcInfo ) ; if ( rtDW . lz2njt4sro .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . lz2njt4sro . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
lz2njt4sro . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . lz2njt4sro .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . lz2njt4sro . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . lz2njt4sro . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . lz2njt4sro . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simu_egr" ) ; sdiRegisterWksVariable ( rtDW . lz2njt4sro . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "u_vgt" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "u_vgt" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace18" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "u_vgt" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. hw0crwwhgx . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"3075e332-ad17-4ed5-9938-85d5a1d38dc4" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . hw0crwwhgx . AQHandles , hDT , & srcInfo ) ; if ( rtDW . hw0crwwhgx .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . hw0crwwhgx . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
hw0crwwhgx . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . hw0crwwhgx .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . hw0crwwhgx . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . hw0crwwhgx . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . hw0crwwhgx . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simu_vgt" ) ; sdiRegisterWksVariable ( rtDW . hw0crwwhgx . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "n_e" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"n_e" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace19" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "n_e" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. odefyqi2dd . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"fff8dc25-4e6d-46ae-9e49-d5c3e8de550a" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . odefyqi2dd . AQHandles , hDT , & srcInfo ) ; if ( rtDW . odefyqi2dd .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . odefyqi2dd . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
odefyqi2dd . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . odefyqi2dd .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . odefyqi2dd . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . odefyqi2dd . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . odefyqi2dd . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simn_e" ) ; sdiRegisterWksVariable ( rtDW . odefyqi2dd . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "eta_t" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "eta_t" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace20" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "eta_t" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. jwv41mpadj . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"f4a87284-6e67-48bf-813d-983c8331ed5f" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . jwv41mpadj . AQHandles , hDT , & srcInfo ) ; if ( rtDW . jwv41mpadj .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . jwv41mpadj . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
jwv41mpadj . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . jwv41mpadj .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . jwv41mpadj . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . jwv41mpadj . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . jwv41mpadj . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simeta_tm" ) ; sdiRegisterWksVariable ( rtDW . jwv41mpadj . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "eta_c" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "eta_c" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace21" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "eta_c" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. mtia2gm3mn . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"0125278d-2536-4553-a2cb-5e69fe150391" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . mtia2gm3mn . AQHandles , hDT , & srcInfo ) ; if ( rtDW . mtia2gm3mn .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . mtia2gm3mn . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
mtia2gm3mn . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . mtia2gm3mn .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . mtia2gm3mn . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . mtia2gm3mn . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . mtia2gm3mn . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simeta_c" ) ; sdiRegisterWksVariable ( rtDW . mtia2gm3mn . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "x_egr" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "x_egr" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace24" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "x_egr" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. acteg3xdu0 . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"84dff3c2-1800-411b-9b42-ed6c9f96f8d1" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . acteg3xdu0 . AQHandles , hDT , & srcInfo ) ; if ( rtDW . acteg3xdu0 .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . acteg3xdu0 . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
acteg3xdu0 . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . acteg3xdu0 .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . acteg3xdu0 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . acteg3xdu0 . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . acteg3xdu0 . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simx_egr" ) ; sdiRegisterWksVariable ( rtDW . acteg3xdu0 . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "u_egract" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "u_egract" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace27" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "u_egract" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. dd50e1xu1m . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"0a54ed41-9668-4228-ae83-8ec8f855ba29" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . dd50e1xu1m . AQHandles , hDT , & srcInfo ) ; if ( rtDW . dd50e1xu1m .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . dd50e1xu1m . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
dd50e1xu1m . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . dd50e1xu1m .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . dd50e1xu1m . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . dd50e1xu1m . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . dd50e1xu1m . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simu_egract" ) ; sdiRegisterWksVariable ( rtDW . dd50e1xu1m . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "u_vgtact" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "u_vgtact" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace28" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "u_vgtact" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. phol22yedf . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"d832a8aa-ae54-444b-a74a-1483c2db429b" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . phol22yedf . AQHandles , hDT , & srcInfo ) ; if ( rtDW . phol22yedf .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . phol22yedf . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
phol22yedf . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . phol22yedf .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . phol22yedf . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . phol22yedf . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . phol22yedf . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simu_vgtact" ) ; sdiRegisterWksVariable ( rtDW . phol22yedf . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "p_im" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "p_im" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace3" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "p_im" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. pieup45y1d . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"3dd17632-dbd5-483a-981c-37793e7ddf99" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . pieup45y1d . AQHandles , hDT , & srcInfo ) ; if ( rtDW . pieup45y1d .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . pieup45y1d . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
pieup45y1d . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . pieup45y1d .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . pieup45y1d . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . pieup45y1d . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . pieup45y1d . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simp_im" ) ; sdiRegisterWksVariable ( rtDW . pieup45y1d . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "x_r" ) ; sdiLabelU origSigName
= sdiGetLabelFromChars ( "" ) ; sdiLabelU propName = sdiGetLabelFromChars (
"x_r" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace32" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "x_r" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. n4ipdfmwpg . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"4e52819b-6a99-4e70-b99b-9bf2a1c599ea" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . n4ipdfmwpg . AQHandles , hDT , & srcInfo ) ; if ( rtDW . n4ipdfmwpg .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . n4ipdfmwpg . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
n4ipdfmwpg . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . n4ipdfmwpg .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . n4ipdfmwpg . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . n4ipdfmwpg . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . n4ipdfmwpg . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simx_r" ) ; sdiRegisterWksVariable ( rtDW . n4ipdfmwpg . AQHandles , varName
, "array" ) ; sdiFreeLabel ( varName ) ; } } } } } { { { bool
isStreamoutAlreadyRegistered = false ; { sdiSignalSourceInfoU srcInfo ;
sdiLabelU loggedName = sdiGetLabelFromChars ( "p_em" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "p_em" ) ; sdiLabelU blockPath = sdiGetLabelFromChars
( "TruckBenchmark/Vehicle Model/Engine  Variables/To Workspace4" ) ;
sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "p_em" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. pp33uvzuj4 . AQHandles = sdiStartAsyncioQueueCreation ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"525c4e44-ed64-4802-948e-b2169b70439c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; sdiCompleteAsyncioQueueCreation (
rtDW . pp33uvzuj4 . AQHandles , hDT , & srcInfo ) ; if ( rtDW . pp33uvzuj4 .
AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . pp33uvzuj4 . AQHandles ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetSignalRefRate ( rtDW .
pp33uvzuj4 . AQHandles , 0.0 ) ; sdiSetRunStartTime ( rtDW . pp33uvzuj4 .
AQHandles , ssGetTaskTime ( rtS , 0 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . pp33uvzuj4 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . pp33uvzuj4 . AQHandles , loggedName , origSigName , propName ) ;
sdiAsyncRepoSetBlockPathDomain ( rtDW . pp33uvzuj4 . AQHandles ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } if ( !
isStreamoutAlreadyRegistered ) { { sdiLabelU varName = sdiGetLabelFromChars (
"simp_em" ) ; sdiRegisterWksVariable ( rtDW . pp33uvzuj4 . AQHandles ,
varName , "array" ) ; sdiFreeLabel ( varName ) ; } } } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ rtDW . ft5nitf1xd . CTLHandle = CTL_GetHandle ( "TruckBenchmark_Config1" )
; } } sErr = GetErrorBuffer ( & rtDW . lgjsvdiy5a [ 0U ] ) ; pathSize =
getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slhostlibcanreceive.dll"
) ; libUpdatePath = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slhostlibcanreceive.dll"
, & libUpdatePath ) ; CreateHostLibrary ( libUpdatePath , & rtDW . lgjsvdiy5a
[ 0U ] ) ; free ( libUpdatePath ) ; if ( * sErr == 0 ) { bitParams [ 0U ] = 1
; bitParams [ 1U ] = 4 ; bitParams [ 2U ] = 3 ; bitParams [ 3U ] = 1 ; stdIDs
= MAX_uint32_T ; extIDs = MAX_uint32_T ; stdIDsStart = 0.0 ; stdIDsEnd = 0.0
; idMaskParams [ 0U ] = 0 ; idMaskParams [ 1U ] = 2047 ; idMaskParams [ 2U ]
= 0 ; idMaskParams [ 3U ] = 536870911 ; pathSize = getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slmathworkswrapper.dll"
) ; vendorUpdatePath = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slmathworkswrapper.dll"
, & vendorUpdatePath ) ; pathSize = getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\canslconverter"
) ; converterUpdatePath = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\canslconverter"
, & converterUpdatePath ) ; pathSize = getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\mathworksplugin"
) ; pluginUpdatePath = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\mathworksplugin"
, & pluginUpdatePath ) ; LibCreate_CANReceive ( & rtDW . lgjsvdiy5a [ 0U ] ,
"mathworks" , vendorUpdatePath , "Virtual" , 0 , 1 , 1 , 1 ,
converterUpdatePath , pluginUpdatePath , 250000.0 , & bitParams [ 0U ] , 0 ,
0 , & stdIDs , 1 , 0 , & extIDs , 1 , & stdIDsStart , & stdIDsEnd , 1 , &
idMaskParams [ 0U ] , 0 ) ; free ( vendorUpdatePath ) ; free (
converterUpdatePath ) ; free ( pluginUpdatePath ) ; } if ( * sErr == 0 ) {
LibStart ( & rtDW . lgjsvdiy5a [ 0U ] ) ; } if ( * sErr != 0 ) {
ssSetErrorStatus ( rtS , sErr ) ; ssSetStopRequested ( rtS , 1 ) ; } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ rtDW . pegf1lgc5k . CTLHandle = CTL_GetHandle ( "TruckBenchmark_Config1" )
; } } sErr = GetErrorBuffer ( & rtDW . ozecqffs1t [ 0U ] ) ; pathSize =
getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slhostlibcantransmit.dll"
) ; libUpdatePath_p = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slhostlibcantransmit.dll"
, & libUpdatePath_p ) ; CreateHostLibrary ( libUpdatePath_p , & rtDW .
ozecqffs1t [ 0U ] ) ; free ( libUpdatePath_p ) ; if ( * sErr == 0 ) {
bitParams_p [ 0U ] = 1 ; bitParams_p [ 1U ] = 4 ; bitParams_p [ 2U ] = 3 ;
bitParams_p [ 3U ] = 1 ; pathSize = getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slmathworkswrapper.dll"
) ; vendorUpdatePath_p = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vntblks\\vntmex\\win64\\slmathworkswrapper.dll"
, & vendorUpdatePath_p ) ; pathSize = getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\canslconverter"
) ; converterUpdatePath_p = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\canslconverter"
, & converterUpdatePath_p ) ; pathSize = getReplacePathLength (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\mathworksplugin"
) ; pluginUpdatePath_p = malloc ( pathSize ) ; replacePath (
 "C:\\Program Files\\MATLAB\\R2023a\\toolbox\\vnt\\vnt\\private\\win64\\mathworksplugin"
, & pluginUpdatePath_p ) ; LibCreate_CANTransmit ( & rtDW . ozecqffs1t [ 0U ]
, "mathworks" , vendorUpdatePath_p , "Virtual" , 0 , 1 , 1 , 1 ,
converterUpdatePath_p , pluginUpdatePath_p , 250000.0 , & bitParams_p [ 0U ]
, 0 , 0 , 0 , 1.0 , 0 ) ; free ( vendorUpdatePath_p ) ; free (
converterUpdatePath_p ) ; free ( pluginUpdatePath_p ) ; } if ( * sErr == 0 )
{ LibStart ( & rtDW . ozecqffs1t [ 0U ] ) ; } if ( * sErr != 0 ) {
ssSetErrorStatus ( rtS , sErr ) ; ssSetStopRequested ( rtS , 1 ) ; } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ j1939Error ret ; HCONFIG configHandle = J1939GetHandle (
"TruckBenchmark_Config1" ) ; rtDW . jpjfz2svcl . CONFIGHANDLE = ( void * )
configHandle ; ret = J1939InitializeStack ( configHandle , 1U , 1U , 512 ,
512 , 255 , 25 ) ; if ( ret != J1939_ERROR_OK ) { char errMsg [ 256 ] ;
sprintf ( errMsg , "J1939 PStack Initialization Error: %d" , ret ) ;
ssSetErrorStatus ( rtS , errMsg ) ; ssSetStopRequested ( rtS , 1 ) ; return ;
} } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ j1939Error ret ; HCONFIG configHandle = J1939GetHandle (
"TruckBenchmark_Config2" ) ; rtDW . kbixsgmskc . CONFIGHANDLE = ( void * )
configHandle ; ret = J1939InitializeStack ( configHandle , 1U , 1U , 512 ,
512 , 255 , 25 ) ; if ( ret != J1939_ERROR_OK ) { char errMsg [ 256 ] ;
sprintf ( errMsg , "J1939 PStack Initialization Error: %d" , ret ) ;
ssSetErrorStatus ( rtS , errMsg ) ; ssSetStopRequested ( rtS , 1 ) ; return ;
} } } { j1939Error error ; CaEntry_T * nodePtr ; HCONFIG configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
maxcur2n31 . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . maxcur2n31
. CONFIGHANDLE != NULL ) { CA_NAME_TYPE ca_name ; ca_name . fields .
IdentityNumber = 0U ; ca_name . fields . ManufacturerCode = 0U ; ca_name .
fields . ECUInstance = 0U ; ca_name . fields . FunctionInstance = 0U ;
ca_name . fields . Function = 0U ; ca_name . fields . Reserved = 0U ; ca_name
. fields . VehicleSystem = 0U ; ca_name . fields . VehicleSystemInstance = 0U
; ca_name . fields . IndustryGroup = 0U ; ca_name . fields .
ArbitraryAddressCapable = 0U ; nodePtr = J1939RegisterNode ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0U , ca_name , & error ) ; if ( nodePtr !=
NULL ) { rtDW . maxcur2n31 . NODEPTR = ( void * ) nodePtr ; rtDW . gk4tvjl5km
. NODEADDR = 0U ; } else { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939 CA Initialization Error:%d \n" , error ) ; ssSetErrorStatus ( rtS ,
msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { j1939Error error
; CaEntry_T * nodePtr ; HCONFIG configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
alvst5aflb . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . alvst5aflb
. CONFIGHANDLE != NULL ) { CA_NAME_TYPE ca_name ; ca_name . fields .
IdentityNumber = 0U ; ca_name . fields . ManufacturerCode = 0U ; ca_name .
fields . ECUInstance = 0U ; ca_name . fields . FunctionInstance = 0U ;
ca_name . fields . Function = 8U ; ca_name . fields . Reserved = 0U ; ca_name
. fields . VehicleSystem = 0U ; ca_name . fields . VehicleSystemInstance = 0U
; ca_name . fields . IndustryGroup = 0U ; ca_name . fields .
ArbitraryAddressCapable = 0U ; nodePtr = J1939RegisterNode ( configHandle ,
"TruckBenchmark_Config1_Node2" , 50U , ca_name , & error ) ; if ( nodePtr !=
NULL ) { rtDW . alvst5aflb . NODEPTR = ( void * ) nodePtr ; rtDW . jqdnga4d0r
. NODEADDR = 50U ; } else { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939 CA Initialization Error:%d \n" , error ) ; ssSetErrorStatus ( rtS ,
msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
iuixpdicwr . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . iuixpdicwr
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 65265U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . iuixpdicwr . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
kzspl1dppk . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . kzspl1dppk
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 65190U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . kzspl1dppk . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
k2kbed5e0t . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . k2kbed5e0t
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 65217U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . k2kbed5e0t . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
osuhy0wf15 . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . osuhy0wf15
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 61450U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . osuhy0wf15 . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
clkxcrhgir . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . clkxcrhgir
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 61473U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . clkxcrhgir . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
e3hhsxef2w . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . e3hhsxef2w
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 61445U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . e3hhsxef2w . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
of3rn5nxd4 . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . of3rn5nxd4
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 6U , 65217U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . of3rn5nxd4 . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
bvdrbi2l1c . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . bvdrbi2l1c
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 6U , 65248U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . bvdrbi2l1c . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
e3ktwiowkd . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . e3ktwiowkd
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 3U , 61450U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . e3ktwiowkd . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
d4x2b0bhgu . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . d4x2b0bhgu
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 6U , 65190U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . d4x2b0bhgu . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
krc0v3lfqy . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . krc0v3lfqy
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 6U , 61473U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . krc0v3lfqy . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
kr1tkdktl0 . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . kr1tkdktl0
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 6U , 61445U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . kr1tkdktl0 . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
imsyrbpl23 . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . imsyrbpl23
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 6U , 65265U , TX_PGN , 8U , 1 , 255U ,
255U , & error ) ; rtDW . imsyrbpl23 . PGPTR = ( void * ) pgn_entry_ptr ; if
( pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Transmit: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { HCONFIG
configHandle ;
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ configHandle = J1939GetHandle ( "TruckBenchmark_Config1" ) ; rtDW .
ekxqe2lb2z . CONFIGHANDLE = ( void * ) configHandle ; if ( rtDW . ekxqe2lb2z
. CONFIGHANDLE != NULL ) { j1939Error error ; PgnEntry_T * pgn_entry_ptr ;
pgn_entry_ptr = J1939RegisterPG ( configHandle ,
"TruckBenchmark_Config1_Engine1" , 0 , 65248U , RX_PGN , 8U , 1 , 255U , 255U
, & error ) ; rtDW . ekxqe2lb2z . PGPTR = ( void * ) pgn_entry_ptr ; if (
pgn_entry_ptr == NULL ) { char_T msg [ 256 ] ; sprintf ( msg ,
"j1939Receive: PGN Registration Error: %d\n" , error ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } } { rt_LUTnWork
* TWork_start = ( rt_LUTnWork * ) & rtDW . bd2sguzpuq [ 0 ] ; void * *
bpDataSet = ( void * * ) & rtDW . j2t1smeuiz ; TWork_start -> m_dimSizes = (
const uint32_T * ) & rtP . uDLookupTable_dimSizes ; TWork_start ->
m_tableData = ( void * ) rtP . road . k_slopeVector ; TWork_start ->
m_bpDataSet = bpDataSet ; TWork_start -> m_bpIndex = & rtDW . g1tih4iurb ;
TWork_start -> m_bpLambda = & rtDW . bffjy4cqw3 ; TWork_start -> m_maxIndex =
( const uint32_T * ) & rtP . uDLookupTable_maxIndex ; bpDataSet [ 0 ] = (
void * ) rtP . road . x_distanceVector ; } { rt_LUTSplineWork * rt_SplWk = (
rt_LUTSplineWork * ) & rtDW . lqs2eqamfb [ 0 ] ; rt_SplWk -> m_TWork = (
rt_LUTnWork * ) & rtDW . bd2sguzpuq [ 0 ] ; rt_SplWk -> m_yyA = & rtDW .
omie0z5rtl ; rt_SplWk -> m_yyB = & rtDW . ltzscgd5af ; rt_SplWk -> m_yy2 = &
rtDW . iazakfnige ; rt_SplWk -> m_up = & rtDW . b1sjehltlg [ 0 ] ; rt_SplWk
-> m_y2 = & rtDW . hmg2uwdzcg [ 0 ] ; rt_SplWk -> m_numYWorkElts = rtP .
uDLookupTable_numYWorkElts ; rt_SplWk -> m_reCalc = & rtDW . nhh3pckv2z ; *
rt_SplWk -> m_reCalc = 1 ; } { char ptrKey [ 1024 ] ; { real_T * pBuffer = (
real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof ( real_T ) ) ; if ( pBuffer
== ( NULL ) ) { ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ;
return ; } rtDW . mf4tzazbhp . Tail = 0 ; rtDW . mf4tzazbhp . Head = 0 ; rtDW
. mf4tzazbhp . Last = 0 ; rtDW . mf4tzazbhp . CircularBufSize = 1024 ;
pBuffer [ 0 ] = ( rtP . model . engine . uInit_egr ) ; pBuffer [ 1024 ] =
ssGetT ( rtS ) ; rtDW . k4tau4hadb . TUbufferPtrs [ 0 ] = ( void * ) &
pBuffer [ 0 ] ; sprintf ( ptrKey ,
 "TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Transport\nDelay_TUbuffer%d"
, 0 ) ; slsaSaveRawMemoryForSimTargetOP ( rtS , ptrKey , ( void * * ) ( &
rtDW . k4tau4hadb . TUbufferPtrs [ 0 ] ) , 2 * 1024 * sizeof ( real_T ) , (
NULL ) , ( NULL ) ) ; } } { char ptrKey [ 1024 ] ; { real_T * pBuffer = (
real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof ( real_T ) ) ; if ( pBuffer
== ( NULL ) ) { ssSetErrorStatus ( rtS , "tdelay memory allocation error" ) ;
return ; } rtDW . pszwtqz0gn . Tail = 0 ; rtDW . pszwtqz0gn . Head = 0 ; rtDW
. pszwtqz0gn . Last = 0 ; rtDW . pszwtqz0gn . CircularBufSize = 1024 ;
pBuffer [ 0 ] = ( rtP . model . engine . uInit_vgt ) ; pBuffer [ 1024 ] =
ssGetT ( rtS ) ; rtDW . hku5cqszwy . TUbufferPtrs [ 0 ] = ( void * ) &
pBuffer [ 0 ] ; sprintf ( ptrKey ,
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Transport\nDelay1_TUbuffer%d"
, 0 ) ; slsaSaveRawMemoryForSimTargetOP ( rtS , ptrKey , ( void * * ) ( &
rtDW . hku5cqszwy . TUbufferPtrs [ 0 ] ) , 2 * 1024 * sizeof ( real_T ) , (
NULL ) , ( NULL ) ) ; } } MdlInitialize ( ) ; MdlEnable ( ) ; } void
MdlOutputs ( int_T tid ) { real_T j0n0q3ll5d [ 3 ] ; real_T k0n05ujcou ;
real_T mzft4ob5pz ; real_T ratio ; real_T taskTimeV ; int32_T isMsgAvailable
; int32_T isMsgReceived ; int32_T s6_iter ; int32_T tmp ; uint32_T numCycles
; char_T * sErr ; void * outputMsgRef ; srClearBC ( rtDW . bfmr5zictt ) ;
srClearBC ( rtDW . p1nnlsrxke ) ; srClearBC ( rtDW . dbfmnhxbxj ) ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX . cwf2tewh2v >= rtP .
Integrator_UpperSat ) { if ( rtX . cwf2tewh2v != rtP . Integrator_UpperSat )
{ rtX . cwf2tewh2v = rtP . Integrator_UpperSat ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . bcl2uuqmhl = 3
; } else if ( rtX . cwf2tewh2v <= rtP . Integrator_LowerSat ) { if ( rtX .
cwf2tewh2v != rtP . Integrator_LowerSat ) { rtX . cwf2tewh2v = rtP .
Integrator_LowerSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
rtDW . bcl2uuqmhl = 4 ; } else { if ( rtDW . bcl2uuqmhl != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . bcl2uuqmhl = 0
; } rtB . fefmeddlto = rtX . cwf2tewh2v ; } else { rtB . fefmeddlto = rtX .
cwf2tewh2v ; } rtB . fegajgngwz = rtB . fefmeddlto * rtP . model . vehicle .
r_w ; rtB . bmo2rqwngx = rtP . mskmh_Gain * rtB . fegajgngwz ; { } { } if (
ssIsSampleHit ( rtS , 3 , 0 ) && ssIsSampleHit ( rtS , 3 , 0 ) ) { sErr =
GetErrorBuffer ( & rtDW . lgjsvdiy5a [ 0U ] ) ; isMsgAvailable = 1 ;
isMsgReceived = 0 ; outputMsgRef = & rtB . hic4phvehd ; while (
isMsgAvailable == 1 ) { LibOutputs_CANReceive ( & rtDW . lgjsvdiy5a [ 0U ] ,
outputMsgRef , 2 , & isMsgReceived , & isMsgAvailable ) ; if ( * sErr != 0 )
{ ssSetErrorStatus ( rtS , sErr ) ; ssSetStopRequested ( rtS , 1 ) ; } if (
isMsgReceived == 1 ) { isMsgReceived = 0 ; CTL_ExecuteRx ( rtDW . ft5nitf1xd
. CTLHandle , & rtB . hic4phvehd , ( int ) ( rtP . Constant_Value ) ) ; rtDW
. bfmr5zictt = 4 ; } } { int_T numMsgs = 0 ; real_T * msgCount = ( real_T * )
& rtB . ffstplvowd ; numMsgs = CTL_ExecuteTx ( rtDW . pegf1lgc5k . CTLHandle
, & rtB . cua1wzatht [ 0 ] , ( int_T ) ( 20 ) ) ; * msgCount = numMsgs ; } if
( rtB . ffstplvowd < 2.147483648E+9 ) { if ( rtB . ffstplvowd >= -
2.147483648E+9 ) { tmp = ( int32_T ) rtB . ffstplvowd ; } else { tmp =
MIN_int32_T ; } } else if ( rtB . ffstplvowd >= 2.147483648E+9 ) { tmp =
MAX_int32_T ; } else { tmp = 0 ; } if ( tmp > 2147483646 ) { tmp = 2147483646
; } else if ( tmp < 0 ) { tmp = 0 ; } for ( s6_iter = 0 ; s6_iter < tmp ;
s6_iter ++ ) { rtB . fqxly0svox = rtB . cua1wzatht [ s6_iter ] ; sErr =
GetErrorBuffer ( & rtDW . ozecqffs1t [ 0U ] ) ; outputMsgRef = & rtB .
fqxly0svox ; LibOutputs_CANTransmit ( & rtDW . ozecqffs1t [ 0U ] ,
outputMsgRef , 1 ) ; if ( * sErr != 0 ) { ssSetErrorStatus ( rtS , sErr ) ;
ssSetStopRequested ( rtS , 1 ) ; } srUpdateBC ( rtDW . p1nnlsrxke ) ; } } {
HCONFIG configHandle = ( HCONFIG ) rtDW . maxcur2n31 . CONFIGHANDLE ; int_T
prevNodeAddress = rtDW . gk4tvjl5km . NODEADDR ; CaEntry_T * nodePtr = (
CaEntry_T * ) rtDW . maxcur2n31 . NODEPTR ; if ( ( uint8_T ) 0U != ( uint8_T
) prevNodeAddress ) { j1939Error ret ; rtDW . gk4tvjl5km . NODEADDR = 0U ;
ret = J1939UpdateNodeAddress ( configHandle , nodePtr , ( uint8_T ) 0U ) ; if
( ret != J1939_ERROR_OK ) { char_T msg [ 256 ] ; sprintf ( msg ,
"J1939 CA: Node Address Update failed (%d)\n" , ret ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } { HCONFIG
configHandle = ( HCONFIG ) rtDW . alvst5aflb . CONFIGHANDLE ; int_T
prevNodeAddress = rtDW . jqdnga4d0r . NODEADDR ; CaEntry_T * nodePtr = (
CaEntry_T * ) rtDW . alvst5aflb . NODEPTR ; if ( ( uint8_T ) 50U != ( uint8_T
) prevNodeAddress ) { j1939Error ret ; rtDW . jqdnga4d0r . NODEADDR = 50U ;
ret = J1939UpdateNodeAddress ( configHandle , nodePtr , ( uint8_T ) 50U ) ;
if ( ret != J1939_ERROR_OK ) { char_T msg [ 256 ] ; sprintf ( msg ,
"J1939 CA: Node Address Update failed (%d)\n" , ret ) ; ssSetErrorStatus (
rtS , msg ) ; ssSetStopRequested ( rtS , 1 ) ; return ; } } } if (
ssIsSampleHit ( rtS , 3 , 0 ) ) { { PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T
* ) rtDW . iuixpdicwr . PGPTR ; uint8_T output_port_offset = 0 ; uint8_T
newmsg = 0 ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active &&
LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr ->
TargetAddress = 255U ; pgn_entry_ptr -> DestinationType = 1U ; if (
pgn_entry_ptr -> NewMessage ) { newmsg = 1 ; { { real_T outValue = 0 ; {
uint8_T unpackedValue = 0 ; { uint8_T tempValue = ( uint8_T ) ( 0 ) ; {
tempValue = tempValue | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
pgn_entry_ptr -> DataBufferPtr [ 3 ] ) & ( uint8_T ) ( 0xC0U ) ) >> 6 ) ; }
unpackedValue = tempValue ; } outValue = ( real_T ) ( unpackedValue ) ; } {
real_T result = ( real_T ) outValue ; rtB . cjmcjehzib = result ; } } {
real_T outValue = 0 ; { uint8_T unpackedValue = 0 ; { uint8_T tempValue = (
uint8_T ) ( 0 ) ; { tempValue = tempValue | ( uint8_T ) ( pgn_entry_ptr ->
DataBufferPtr [ 5 ] ) ; } unpackedValue = tempValue ; } outValue = ( real_T )
( unpackedValue ) ; } { real_T result = ( real_T ) outValue ; rtB .
k13vzx0oza = result ; } } { real_T outValue = 0 ; { uint8_T unpackedValue = 0
; { uint8_T tempValue = ( uint8_T ) ( 0 ) ; { tempValue = tempValue | (
uint8_T ) ( ( uint8_T ) ( pgn_entry_ptr -> DataBufferPtr [ 6 ] ) & ( uint8_T
) ( 0x1FU ) ) ; } unpackedValue = tempValue ; } outValue = ( real_T ) (
unpackedValue ) ; } { real_T result = ( real_T ) outValue ; rtB . faymzhlev0
= result ; } } { real_T outValue = 0 ; { uint16_T unpackedValue = 0 ; {
uint16_T tempValue = ( uint16_T ) ( 0 ) ; { tempValue = tempValue | (
uint16_T ) ( pgn_entry_ptr -> DataBufferPtr [ 1 ] ) ; tempValue = tempValue |
( uint16_T ) ( ( uint16_T ) ( pgn_entry_ptr -> DataBufferPtr [ 2 ] ) << 8 ) ;
} unpackedValue = tempValue ; } outValue = ( real_T ) ( unpackedValue ) ; } {
real_T result = ( real_T ) outValue ; result = result * 0.00390625 ; rtB .
cb4di0dti4 = result ; } } } pgn_entry_ptr -> NewMessage = 0 ; }
UNLOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ; } } { PgnEntry_T *
pgn_entry_ptr = ( PgnEntry_T * ) rtDW . kzspl1dppk . PGPTR ; uint8_T
output_port_offset = 0 ; uint8_T newmsg = 0 ; if ( pgn_entry_ptr != NULL &&
pgn_entry_ptr -> CA -> Active && LOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ; pgn_entry_ptr ->
DestinationType = 1U ; if ( pgn_entry_ptr -> NewMessage ) { newmsg = 1 ; { {
real_T outValue = 0 ; { uint16_T unpackedValue = 0 ; { uint16_T tempValue = (
uint16_T ) ( 0 ) ; { tempValue = tempValue | ( uint16_T ) ( pgn_entry_ptr ->
DataBufferPtr [ 0 ] ) ; tempValue = tempValue | ( uint16_T ) ( ( uint16_T ) (
pgn_entry_ptr -> DataBufferPtr [ 1 ] ) << 8 ) ; } unpackedValue = tempValue ;
} outValue = ( real_T ) ( unpackedValue ) ; } { real_T result = ( real_T )
outValue ; result = result * 0.125 ; rtB . klpxz3py2k = result ; } } }
pgn_entry_ptr -> NewMessage = 0 ; } UNLOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ; } } { PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T * ) rtDW .
k2kbed5e0t . PGPTR ; uint8_T output_port_offset = 0 ; uint8_T newmsg = 0 ; if
( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active && LOCK_PGN_ENTRY (
pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ;
pgn_entry_ptr -> DestinationType = 1U ; if ( pgn_entry_ptr -> NewMessage ) {
newmsg = 1 ; { { real_T outValue = 0 ; { uint32_T unpackedValue = 0 ; {
uint32_T tempValue = ( uint32_T ) ( 0 ) ; { tempValue = tempValue | (
uint32_T ) ( pgn_entry_ptr -> DataBufferPtr [ 4 ] ) ; tempValue = tempValue |
( uint32_T ) ( ( uint32_T ) ( pgn_entry_ptr -> DataBufferPtr [ 5 ] ) << 8 ) ;
tempValue = tempValue | ( uint32_T ) ( ( uint32_T ) ( pgn_entry_ptr ->
DataBufferPtr [ 6 ] ) << 16 ) ; tempValue = tempValue | ( uint32_T ) ( (
uint32_T ) ( pgn_entry_ptr -> DataBufferPtr [ 7 ] ) << 24 ) ; } unpackedValue
= tempValue ; } outValue = ( real_T ) ( unpackedValue ) ; } { real_T result =
( real_T ) outValue ; result = result * 5.0 ; rtB . cgnmu1btuu = result ; } }
} pgn_entry_ptr -> NewMessage = 0 ; } UNLOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ; } } { PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T * ) rtDW .
osuhy0wf15 . PGPTR ; uint8_T output_port_offset = 0 ; uint8_T newmsg = 0 ; if
( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active && LOCK_PGN_ENTRY (
pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ;
pgn_entry_ptr -> DestinationType = 1U ; if ( pgn_entry_ptr -> NewMessage ) {
newmsg = 1 ; { { real_T outValue = 0 ; { uint16_T unpackedValue = 0 ; {
uint16_T tempValue = ( uint16_T ) ( 0 ) ; { tempValue = tempValue | (
uint16_T ) ( pgn_entry_ptr -> DataBufferPtr [ 2 ] ) ; tempValue = tempValue |
( uint16_T ) ( ( uint16_T ) ( pgn_entry_ptr -> DataBufferPtr [ 3 ] ) << 8 ) ;
} unpackedValue = tempValue ; } outValue = ( real_T ) ( unpackedValue ) ; } {
real_T result = ( real_T ) outValue ; result = result * 0.05 ; rtB .
lsjheazm1j = result ; } } } pgn_entry_ptr -> NewMessage = 0 ; }
UNLOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ; } } { PgnEntry_T *
pgn_entry_ptr = ( PgnEntry_T * ) rtDW . clkxcrhgir . PGPTR ; uint8_T
output_port_offset = 0 ; uint8_T newmsg = 0 ; if ( pgn_entry_ptr != NULL &&
pgn_entry_ptr -> CA -> Active && LOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ; pgn_entry_ptr ->
DestinationType = 1U ; if ( pgn_entry_ptr -> NewMessage ) { newmsg = 1 ; { {
real_T outValue = 0 ; { uint16_T unpackedValue = 0 ; { uint16_T tempValue = (
uint16_T ) ( 0 ) ; { tempValue = tempValue | ( uint16_T ) ( pgn_entry_ptr ->
DataBufferPtr [ 0 ] ) ; tempValue = tempValue | ( uint16_T ) ( ( uint16_T ) (
pgn_entry_ptr -> DataBufferPtr [ 1 ] ) << 8 ) ; } unpackedValue = tempValue ;
} outValue = ( real_T ) ( unpackedValue ) ; } { real_T result = ( real_T )
outValue ; result = result * 0.5 ; rtB . mkgmrqsz4m = result ; } } }
pgn_entry_ptr -> NewMessage = 0 ; } UNLOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ; } } { PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T * ) rtDW .
e3hhsxef2w . PGPTR ; uint8_T output_port_offset = 0 ; uint8_T newmsg = 0 ; if
( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active && LOCK_PGN_ENTRY (
pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ;
pgn_entry_ptr -> DestinationType = 1U ; if ( pgn_entry_ptr -> NewMessage ) {
newmsg = 1 ; { { real_T outValue = 0 ; { uint8_T unpackedValue = 0 ; {
uint8_T tempValue = ( uint8_T ) ( 0 ) ; { tempValue = tempValue | ( uint8_T )
( pgn_entry_ptr -> DataBufferPtr [ 3 ] ) ; } unpackedValue = tempValue ; }
outValue = ( real_T ) ( unpackedValue ) ; } { real_T result = ( real_T )
outValue ; result = result + - 125.0 ; rtB . gmmxsb1ncz = result ; } } }
pgn_entry_ptr -> NewMessage = 0 ; } UNLOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ; } } } if ( ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX .
lpegok4bfi >= rtP . Integrator1_UpperSat ) { if ( rtX . lpegok4bfi != rtP .
Integrator1_UpperSat ) { rtX . lpegok4bfi = rtP . Integrator1_UpperSat ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . nxjlr5banb = 3
; } else if ( rtX . lpegok4bfi <= rtP . Integrator1_LowerSat ) { if ( rtX .
lpegok4bfi != rtP . Integrator1_LowerSat ) { rtX . lpegok4bfi = rtP .
Integrator1_LowerSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
rtDW . nxjlr5banb = 4 ; } else { if ( rtDW . nxjlr5banb != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . nxjlr5banb = 0
; } rtB . pd4h1x0zka = rtX . lpegok4bfi ; } else { rtB . pd4h1x0zka = rtX .
lpegok4bfi ; } rtB . d33i42nznw = rtP . Gain1_Gain * rtB . pd4h1x0zka ; rtB .
hrozmhet10 = rtP . Gain2_Gain * rtB . pd4h1x0zka ; if ( ssIsSampleHit ( rtS ,
5 , 0 ) ) { taskTimeV = ssGetTaskTime ( rtS , 5 ) ; if (
ssGetTNextWasAdjusted ( rtS , 5 ) ) { rtDW . kpmtixcj35 =
_ssGetVarNextHitTime ( rtS , 0 ) ; } if ( rtDW . imduqxhj3y != 0 ) { rtDW .
imduqxhj3y = 0 ; if ( taskTimeV >= rtP . PulseGenerator_PhaseDelay ) { ratio
= ( taskTimeV - rtP . PulseGenerator_PhaseDelay ) / rtP .
PulseGenerator_Period ; numCycles = ( uint32_T ) muDoubleScalarFloor ( ratio
) ; if ( muDoubleScalarAbs ( ( real_T ) ( numCycles + 1U ) - ratio ) <
DBL_EPSILON * ratio ) { numCycles ++ ; } rtDW . ki10t4re5z = numCycles ;
ratio = ( ( real_T ) numCycles * rtP . PulseGenerator_Period + rtP .
PulseGenerator_PhaseDelay ) + rtP . PulseGenerator_Duty * rtP .
PulseGenerator_Period / 100.0 ; if ( taskTimeV < ratio ) { rtDW . h0ytymzc2i
= 1 ; rtDW . kpmtixcj35 = ratio ; } else { rtDW . h0ytymzc2i = 0 ; rtDW .
kpmtixcj35 = ( real_T ) ( numCycles + 1U ) * rtP . PulseGenerator_Period +
rtP . PulseGenerator_PhaseDelay ; } } else { rtDW . ki10t4re5z = rtP .
PulseGenerator_PhaseDelay != 0.0 ? - 1 : 0 ; rtDW . h0ytymzc2i = 0 ; rtDW .
kpmtixcj35 = rtP . PulseGenerator_PhaseDelay ; } } else if ( rtDW .
kpmtixcj35 <= taskTimeV ) { if ( rtDW . h0ytymzc2i == 1 ) { rtDW . h0ytymzc2i
= 0 ; rtDW . kpmtixcj35 = ( real_T ) ( rtDW . ki10t4re5z + 1LL ) * rtP .
PulseGenerator_Period + rtP . PulseGenerator_PhaseDelay ; } else { rtDW .
ki10t4re5z ++ ; rtDW . h0ytymzc2i = 1 ; rtDW . kpmtixcj35 = ( rtP .
PulseGenerator_Duty * rtP . PulseGenerator_Period * 0.01 + ( real_T ) rtDW .
ki10t4re5z * rtP . PulseGenerator_Period ) + rtP . PulseGenerator_PhaseDelay
; } } _ssSetVarNextHitTime ( rtS , 0 , rtDW . kpmtixcj35 ) ; if ( rtDW .
h0ytymzc2i == 1 ) { rtB . nnky4aaqaz = rtP . PulseGenerator_Amp ; } else {
rtB . nnky4aaqaz = 0.0 ; } } { HCONFIG configHandle = ( HCONFIG ) rtDW .
of3rn5nxd4 . CONFIGHANDLE ; PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T * )
rtDW . of3rn5nxd4 . PGPTR ; uint32_T pgn ; uint32_T active = 0 ; PGN_TYPE *
pgn_fields ; int_T j ; uint16_T nOutputBytes ; active = ( uint32_T ) rtB .
nnky4aaqaz ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active &&
active && LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr
-> TargetAddress = 255U ; nOutputBytes = 8U ; for ( j = 0 ; j < nOutputBytes
; j ++ ) { pgn_entry_ptr -> DataBufferPtr [ j ] = 0xFF ; } pgn = 65217U ;
pgn_fields = ( PGN_TYPE * ) & pgn ; { real_T outValue = 0 ; { real_T result =
rtB . d33i42nznw ; result = result * ( 1 / 5.0 ) ; outValue = round ( result
) ; } { uint32_T packedValue ; if ( outValue < ( real_T ) ( 0 ) ) {
packedValue = ( uint32_T ) 0 ; } else { packedValue = ( uint32_T ) ( outValue
) ; } { { pgn_entry_ptr -> DataBufferPtr [ 0 ] = pgn_entry_ptr ->
DataBufferPtr [ 0 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) (
packedValue & ( uint32_T ) 0xFFU ) ^ ( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr
-> DataBufferPtr [ 1 ] = pgn_entry_ptr -> DataBufferPtr [ 1 ] & ( uint8_T ) ~
( ( uint8_T ) ( ( uint32_T ) ( ( uint32_T ) ( packedValue & ( uint32_T )
0xFF00U ) >> 8 ) ^ ( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [
2 ] = pgn_entry_ptr -> DataBufferPtr [ 2 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint32_T ) ( ( uint32_T ) ( packedValue & ( uint32_T ) 0xFF0000U ) >> 16 ) ^
( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr
-> DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( (
uint32_T ) ( packedValue & ( uint32_T ) 0xFF000000U ) >> 24 ) ^ ( uint32_T )
0xFFU ) ) ; } } } } { real_T outValue = 0 ; { real_T result = rtB .
hrozmhet10 ; result = result * ( 1 / 5.0 ) ; outValue = round ( result ) ; }
{ uint32_T packedValue ; if ( outValue < ( real_T ) ( 0 ) ) { packedValue = (
uint32_T ) 0 ; } else { packedValue = ( uint32_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 4 ] = pgn_entry_ptr -> DataBufferPtr [ 4 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( packedValue & ( uint32_T ) 0xFFU
) ^ ( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 5 ] =
pgn_entry_ptr -> DataBufferPtr [ 5 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint32_T ) ( ( uint32_T ) ( packedValue & ( uint32_T ) 0xFF00U ) >> 8 ) ^ (
uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 6 ] = pgn_entry_ptr
-> DataBufferPtr [ 6 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( (
uint32_T ) ( packedValue & ( uint32_T ) 0xFF0000U ) >> 16 ) ^ ( uint32_T )
0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 7 ] = pgn_entry_ptr ->
DataBufferPtr [ 7 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( ( uint32_T
) ( packedValue & ( uint32_T ) 0xFF000000U ) >> 24 ) ^ ( uint32_T ) 0xFFU ) )
; } } } } J1939SendMessage ( configHandle , pgn_entry_ptr ) ;
UNLOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ; } } rtB . kpnuhs4yan =
rtP . Gain3_Gain * rtB . pd4h1x0zka ; rtB . ai3npgqmd0 = rtP . Gain4_Gain *
rtB . pd4h1x0zka ; { HCONFIG configHandle = ( HCONFIG ) rtDW . bvdrbi2l1c .
CONFIGHANDLE ; PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T * ) rtDW .
bvdrbi2l1c . PGPTR ; uint32_T pgn ; uint32_T active = 0 ; PGN_TYPE *
pgn_fields ; int_T j ; uint16_T nOutputBytes ; active = ( uint32_T ) rtB .
nnky4aaqaz ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active &&
active && LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr
-> TargetAddress = 255U ; nOutputBytes = 8U ; for ( j = 0 ; j < nOutputBytes
; j ++ ) { pgn_entry_ptr -> DataBufferPtr [ j ] = 0xFF ; } pgn = 65248U ;
pgn_fields = ( PGN_TYPE * ) & pgn ; { real_T outValue = 0 ; { real_T result =
rtB . kpnuhs4yan ; result = result * ( 1 / 0.125 ) ; outValue = round (
result ) ; } { uint32_T packedValue ; if ( outValue < ( real_T ) ( 0 ) ) {
packedValue = ( uint32_T ) 0 ; } else { packedValue = ( uint32_T ) ( outValue
) ; } { { pgn_entry_ptr -> DataBufferPtr [ 4 ] = pgn_entry_ptr ->
DataBufferPtr [ 4 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) (
packedValue & ( uint32_T ) 0xFFU ) ^ ( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr
-> DataBufferPtr [ 5 ] = pgn_entry_ptr -> DataBufferPtr [ 5 ] & ( uint8_T ) ~
( ( uint8_T ) ( ( uint32_T ) ( ( uint32_T ) ( packedValue & ( uint32_T )
0xFF00U ) >> 8 ) ^ ( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [
6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint32_T ) ( ( uint32_T ) ( packedValue & ( uint32_T ) 0xFF0000U ) >> 16 ) ^
( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 7 ] = pgn_entry_ptr
-> DataBufferPtr [ 7 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( (
uint32_T ) ( packedValue & ( uint32_T ) 0xFF000000U ) >> 24 ) ^ ( uint32_T )
0xFFU ) ) ; } } } } { real_T outValue = 0 ; { real_T result = rtB .
ai3npgqmd0 ; result = result * ( 1 / 0.125 ) ; outValue = round ( result ) ;
} { uint32_T packedValue ; if ( outValue < ( real_T ) ( 0 ) ) { packedValue =
( uint32_T ) 0 ; } else { packedValue = ( uint32_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 0 ] = pgn_entry_ptr -> DataBufferPtr [ 0 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( packedValue & ( uint32_T ) 0xFFU
) ^ ( uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 1 ] =
pgn_entry_ptr -> DataBufferPtr [ 1 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint32_T ) ( ( uint32_T ) ( packedValue & ( uint32_T ) 0xFF00U ) >> 8 ) ^ (
uint32_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 2 ] = pgn_entry_ptr
-> DataBufferPtr [ 2 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( (
uint32_T ) ( packedValue & ( uint32_T ) 0xFF0000U ) >> 16 ) ^ ( uint32_T )
0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr ->
DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint32_T ) ( ( uint32_T
) ( packedValue & ( uint32_T ) 0xFF000000U ) >> 24 ) ^ ( uint32_T ) 0xFFU ) )
; } } } } J1939SendMessage ( configHandle , pgn_entry_ptr ) ;
UNLOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ; } } if (
ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX . akhhz2ar2w >= rtP .
Integratoromega_t_UpperSat ) { if ( rtX . akhhz2ar2w != rtP .
Integratoromega_t_UpperSat ) { rtX . akhhz2ar2w = rtP .
Integratoromega_t_UpperSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS
) ; } rtDW . ja1c4asgaz = 3 ; } else if ( rtX . akhhz2ar2w <= rtP .
Integratoromega_t_LowerSat ) { if ( rtX . akhhz2ar2w != rtP .
Integratoromega_t_LowerSat ) { rtX . akhhz2ar2w = rtP .
Integratoromega_t_LowerSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS
) ; } rtDW . ja1c4asgaz = 4 ; } else { if ( rtDW . ja1c4asgaz != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . ja1c4asgaz = 0
; } rtB . c0cwgduetq = rtX . akhhz2ar2w ; } else { rtB . c0cwgduetq = rtX .
akhhz2ar2w ; } if ( ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX . ekar034xyr
>= 10.0 * rtP . model . engine . p_amb ) { if ( 10.0 * rtP . model . engine .
p_amb != rtX . ekar034xyr ) { rtX . ekar034xyr = 10.0 * rtP . model . engine
. p_amb ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW .
btigisbrqf = 3 ; } else if ( rtX . ekar034xyr <= 0.5 * rtP . model . engine .
p_amb ) { if ( 0.5 * rtP . model . engine . p_amb != rtX . ekar034xyr ) { rtX
. ekar034xyr = 0.5 * rtP . model . engine . p_amb ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . btigisbrqf = 4
; } else { if ( rtDW . btigisbrqf != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . btigisbrqf = 0
; } rtB . kiwuycktce = rtX . ekar034xyr ; } else { rtB . kiwuycktce = rtX .
ekar034xyr ; } rtB . bdsfootlbo = rtB . kiwuycktce / rtP . model . engine .
p_amb ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . ig3aydedki = rtB .
bdsfootlbo ; rtDW . ckyfoeqie5 = 0 ; if ( ( rtB . bdsfootlbo != rtB .
bdsfootlbo ) || ( rtP . Constant1_Value_foo0ytc1ur > rtB . bdsfootlbo ) ) {
rtB . ig3aydedki = rtP . Constant1_Value_foo0ytc1ur ; rtDW . ckyfoeqie5 = 1 ;
} } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable
++ ) { rtB . ig3aydedki = rtB . bdsfootlbo ; if ( rtDW . ckyfoeqie5 == 1 ) {
rtB . ig3aydedki = rtP . Constant1_Value_foo0ytc1ur ; } } } rtB . egg3t2uoo3
= rtP . model . engine . c_wpsiVec [ 0 ] ; for ( isMsgAvailable = 1 ;
isMsgAvailable < 3 ; isMsgAvailable ++ ) { rtB . egg3t2uoo3 = rtB .
egg3t2uoo3 * rtB . c0cwgduetq + rtP . model . engine . c_wpsiVec [
isMsgAvailable ] ; } if ( ssIsModeUpdateTimeStep ( rtS ) ) { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
bahf0ftnyg = rtB . egg3t2uoo3 ; rtDW . ixaqaxatlt = 0 ; if ( ( rtB .
egg3t2uoo3 != rtB . egg3t2uoo3 ) || ( rtP . Constant1_Value_kvscu5x5rd > rtB
. egg3t2uoo3 ) ) { rtB . bahf0ftnyg = rtP . Constant1_Value_kvscu5x5rd ; rtDW
. ixaqaxatlt = 1 ; } } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1
; isMsgAvailable ++ ) { rtB . bahf0ftnyg = rtB . egg3t2uoo3 ; if ( rtDW .
ixaqaxatlt == 1 ) { rtB . bahf0ftnyg = rtP . Constant1_Value_kvscu5x5rd ; } }
} if ( rtB . ig3aydedki < 0.0 ) { taskTimeV = - muDoubleScalarPower ( - rtB .
ig3aydedki , 0.28387734915924823 ) ; } else { taskTimeV = muDoubleScalarPower
( rtB . ig3aydedki , 0.28387734915924823 ) ; } rtB . mocnuvcpgp = 1.0 -
muDoubleScalarPower ( 2022.0 * rtP . model . engine . T_amb * ( taskTimeV -
1.0 ) / ( 0.0016 * muDoubleScalarPower ( rtB . c0cwgduetq , 2.0 ) ) , 2.0 ) *
rtB . bahf0ftnyg ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
laxl1bi23g = rtP . Constant_Value_cfl4aorgnt ; rtDW . fshou35ift = 0 ; if ( (
rtP . Constant_Value_cfl4aorgnt != rtP . Constant_Value_cfl4aorgnt ) || ( rtB
. mocnuvcpgp > rtP . Constant_Value_cfl4aorgnt ) ) { rtB . laxl1bi23g = rtB .
mocnuvcpgp ; rtDW . fshou35ift = 1 ; } } } else { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . laxl1bi23g = rtP .
Constant_Value_cfl4aorgnt ; if ( rtDW . fshou35ift == 1 ) { rtB . laxl1bi23g
= rtB . mocnuvcpgp ; } } } rtB . nyt5uikcfo = rtP . model . engine .
c_wphiVec [ 0 ] ; for ( isMsgAvailable = 1 ; isMsgAvailable < 3 ;
isMsgAvailable ++ ) { rtB . nyt5uikcfo = rtB . nyt5uikcfo * rtB . c0cwgduetq
+ rtP . model . engine . c_wphiVec [ isMsgAvailable ] ; } if (
ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ; isMsgAvailable
< 1 ; isMsgAvailable ++ ) { rtB . ebhzjlfncx = rtB . nyt5uikcfo ; rtDW .
cflc32uwnd = 0 ; if ( ( rtB . nyt5uikcfo != rtB . nyt5uikcfo ) || ( rtP .
Constant3_Value > rtB . nyt5uikcfo ) ) { rtB . ebhzjlfncx = rtP .
Constant3_Value ; rtDW . cflc32uwnd = 1 ; } } } else { for ( isMsgAvailable =
0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . ebhzjlfncx = rtB .
nyt5uikcfo ; if ( rtDW . cflc32uwnd == 1 ) { rtB . ebhzjlfncx = rtP .
Constant3_Value ; } } } taskTimeV = rtB . laxl1bi23g / rtB . ebhzjlfncx ; if
( taskTimeV < 0.0 ) { rtB . lsrw5owmej = - muDoubleScalarSqrt ( - taskTimeV )
; } else { rtB . lsrw5owmej = muDoubleScalarSqrt ( taskTimeV ) ; } if (
ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ; isMsgAvailable
< 1 ; isMsgAvailable ++ ) { rtB . jdemdb52qn = rtP .
Constant2_Value_dfqgdtofyy ; rtDW . oqko4zquza = 0 ; if ( ( rtP .
Constant2_Value_dfqgdtofyy != rtP . Constant2_Value_dfqgdtofyy ) || ( rtB .
lsrw5owmej > rtP . Constant2_Value_dfqgdtofyy ) ) { rtB . jdemdb52qn = rtB .
lsrw5owmej ; rtDW . oqko4zquza = 1 ; } } } else { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . jdemdb52qn = rtP .
Constant2_Value_dfqgdtofyy ; if ( rtDW . oqko4zquza == 1 ) { rtB . jdemdb52qn
= rtB . lsrw5owmej ; } } } rtB . fzqijlk23t = rtP . model . engine . p_amb *
3.1415926535897931 * 6.4000000000000011E-5 * rtB . c0cwgduetq * rtB .
jdemdb52qn / ( 287.0 * rtP . model . engine . T_amb ) ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . h3mr0riybw = rtB . fzqijlk23t >=
rtP . Saturation_UpperSat_i32xa2dnvv ? 1 : rtB . fzqijlk23t > rtP .
Saturation_LowerSat_f5etl5uivq ? 0 : - 1 ; } rtB . hmqeokdrxe = rtDW .
h3mr0riybw == 1 ? rtP . Saturation_UpperSat_i32xa2dnvv : rtDW . h3mr0riybw ==
- 1 ? rtP . Saturation_LowerSat_f5etl5uivq : rtB . fzqijlk23t ; rtB .
paczzqkqdw = rtP . Gain6_Gain * rtB . hmqeokdrxe ; { HCONFIG configHandle = (
HCONFIG ) rtDW . e3ktwiowkd . CONFIGHANDLE ; PgnEntry_T * pgn_entry_ptr = (
PgnEntry_T * ) rtDW . e3ktwiowkd . PGPTR ; uint32_T pgn ; uint32_T active = 0
; PGN_TYPE * pgn_fields ; int_T j ; uint16_T nOutputBytes ; active = (
uint32_T ) rtB . nnky4aaqaz ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr ->
CA -> Active && active && LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) )
{ pgn_entry_ptr -> TargetAddress = 255U ; nOutputBytes = 8U ; for ( j = 0 ; j
< nOutputBytes ; j ++ ) { pgn_entry_ptr -> DataBufferPtr [ j ] = 0xFF ; } pgn
= 61450U ; pgn_fields = ( PGN_TYPE * ) & pgn ; { real_T outValue = 0 ; {
real_T result = rtB . fgbfua1b4j ; result = result * ( 1 / 0.05 ) ; outValue
= round ( result ) ; } { uint16_T packedValue ; if ( outValue > ( real_T ) (
65535 ) ) { packedValue = ( uint16_T ) 65535 ; } else if ( outValue < (
real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; } else { packedValue = (
uint16_T ) ( outValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 0 ] =
pgn_entry_ptr -> DataBufferPtr [ 0 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T ) 0xFFU ) ) ;
pgn_entry_ptr -> DataBufferPtr [ 1 ] = pgn_entry_ptr -> DataBufferPtr [ 1 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T ) ( packedValue & (
uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; } } } } { real_T
outValue = 0 ; { real_T result = rtB . fgbfua1b4j ; result = result * ( 1 /
0.05 ) ; outValue = round ( result ) ; } { uint16_T packedValue ; if (
outValue > ( real_T ) ( 65535 ) ) { packedValue = ( uint16_T ) 65535 ; } else
if ( outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; } else {
packedValue = ( uint16_T ) ( outValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 4 ] = pgn_entry_ptr -> DataBufferPtr [ 4 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 5 ] = pgn_entry_ptr ->
DataBufferPtr [ 5 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } { real_T outValue = 0 ; { real_T result = rtB . paczzqkqdw ; result =
result * ( 1 / 0.05 ) ; outValue = round ( result ) ; } { uint16_T
packedValue ; if ( outValue > ( real_T ) ( 65535 ) ) { packedValue = (
uint16_T ) 65535 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue =
( uint16_T ) 0 ; } else { packedValue = ( uint16_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 2 ] = pgn_entry_ptr -> DataBufferPtr [ 2 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU
) ^ ( uint16_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 3 ] =
pgn_entry_ptr -> DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint16_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ (
uint16_T ) 0xFFU ) ) ; } } } } J1939SendMessage ( configHandle ,
pgn_entry_ptr ) ; UNLOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ; } }
rtB . kp3tvzs4pj = rtP . Gain5_Gain * rtB . kiwuycktce ; { HCONFIG
configHandle = ( HCONFIG ) rtDW . d4x2b0bhgu . CONFIGHANDLE ; PgnEntry_T *
pgn_entry_ptr = ( PgnEntry_T * ) rtDW . d4x2b0bhgu . PGPTR ; uint32_T pgn ;
uint32_T active = 0 ; PGN_TYPE * pgn_fields ; int_T j ; uint16_T nOutputBytes
; active = ( uint32_T ) rtB . nnky4aaqaz ; if ( pgn_entry_ptr != NULL &&
pgn_entry_ptr -> CA -> Active && active && LOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ; nOutputBytes =
8U ; for ( j = 0 ; j < nOutputBytes ; j ++ ) { pgn_entry_ptr -> DataBufferPtr
[ j ] = 0xFF ; } pgn = 65190U ; pgn_fields = ( PGN_TYPE * ) & pgn ; { real_T
outValue = 0 ; { real_T result = rtB . kp3tvzs4pj ; result = result * ( 1 /
0.125 ) ; outValue = round ( result ) ; } { uint16_T packedValue ; if (
outValue > ( real_T ) ( 65535 ) ) { packedValue = ( uint16_T ) 65535 ; } else
if ( outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; } else {
packedValue = ( uint16_T ) ( outValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 0 ] = pgn_entry_ptr -> DataBufferPtr [ 0 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 1 ] = pgn_entry_ptr ->
DataBufferPtr [ 1 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } { real_T outValue = 0 ; { real_T result = rtB . kp3tvzs4pj ; result =
result * ( 1 / 0.125 ) ; outValue = round ( result ) ; } { uint16_T
packedValue ; if ( outValue > ( real_T ) ( 65535 ) ) { packedValue = (
uint16_T ) 65535 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue =
( uint16_T ) 0 ; } else { packedValue = ( uint16_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 2 ] = pgn_entry_ptr -> DataBufferPtr [ 2 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU
) ^ ( uint16_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 3 ] =
pgn_entry_ptr -> DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint16_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ (
uint16_T ) 0xFFU ) ) ; } } } } { real_T outValue = 0 ; { real_T result = rtB
. kp3tvzs4pj ; result = result * ( 1 / 0.125 ) ; outValue = round ( result )
; } { uint16_T packedValue ; if ( outValue > ( real_T ) ( 65535 ) ) {
packedValue = ( uint16_T ) 65535 ; } else if ( outValue < ( real_T ) ( 0 ) )
{ packedValue = ( uint16_T ) 0 ; } else { packedValue = ( uint16_T ) (
outValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 4 ] = pgn_entry_ptr ->
DataBufferPtr [ 4 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) (
packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T ) 0xFFU ) ) ; pgn_entry_ptr
-> DataBufferPtr [ 5 ] = pgn_entry_ptr -> DataBufferPtr [ 5 ] & ( uint8_T ) ~
( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T ) ( packedValue & ( uint16_T )
0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; } } } } { real_T outValue = 0 ; {
real_T result = rtB . kp3tvzs4pj ; result = result * ( 1 / 0.125 ) ; outValue
= round ( result ) ; } { uint16_T packedValue ; if ( outValue > ( real_T ) (
65535 ) ) { packedValue = ( uint16_T ) 65535 ; } else if ( outValue < (
real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; } else { packedValue = (
uint16_T ) ( outValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 6 ] =
pgn_entry_ptr -> DataBufferPtr [ 6 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T ) 0xFFU ) ) ;
pgn_entry_ptr -> DataBufferPtr [ 7 ] = pgn_entry_ptr -> DataBufferPtr [ 7 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T ) ( packedValue & (
uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; } } } }
J1939SendMessage ( configHandle , pgn_entry_ptr ) ; UNLOCK_PGN_ENTRY (
pgn_entry_ptr , J1939_APP_TASK ) ; } } if ( ssIsModeUpdateTimeStep ( rtS ) )
{ if ( rtX . aufcyghqde >= rtP . Integrator1_UpperSat_pktoycczal ) { if ( rtX
. aufcyghqde != rtP . Integrator1_UpperSat_pktoycczal ) { rtX . aufcyghqde =
rtP . Integrator1_UpperSat_pktoycczal ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . pfmhktgqz5 = 3
; } else if ( rtX . aufcyghqde <= rtP . Integrator1_LowerSat_ofks0duo33 ) {
if ( rtX . aufcyghqde != rtP . Integrator1_LowerSat_ofks0duo33 ) { rtX .
aufcyghqde = rtP . Integrator1_LowerSat_ofks0duo33 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . pfmhktgqz5 = 4
; } else { if ( rtDW . pfmhktgqz5 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . pfmhktgqz5 = 0
; } rtB . pgdssncn1o = rtX . aufcyghqde ; } else { rtB . pgdssncn1o = rtX .
aufcyghqde ; } rtB . hc01pdzof3 = rtP . radsRPM_Gain * rtB . pgdssncn1o ; rtB
. gs1ggdpy4b = rtP . Gain8_Gain * rtB . hc01pdzof3 ; { HCONFIG configHandle =
( HCONFIG ) rtDW . krc0v3lfqy . CONFIGHANDLE ; PgnEntry_T * pgn_entry_ptr = (
PgnEntry_T * ) rtDW . krc0v3lfqy . PGPTR ; uint32_T pgn ; uint32_T active = 0
; PGN_TYPE * pgn_fields ; int_T j ; uint16_T nOutputBytes ; active = (
uint32_T ) rtB . nnky4aaqaz ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr ->
CA -> Active && active && LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) )
{ pgn_entry_ptr -> TargetAddress = 255U ; nOutputBytes = 8U ; for ( j = 0 ; j
< nOutputBytes ; j ++ ) { pgn_entry_ptr -> DataBufferPtr [ j ] = 0xFF ; } pgn
= 61473U ; pgn_fields = ( PGN_TYPE * ) & pgn ; { real_T outValue = 0 ; {
real_T result = rtP . dummy2_Value ; outValue = round ( result ) ; } {
uint8_T packedValue ; if ( outValue > ( real_T ) ( 3 ) ) { packedValue = (
uint8_T ) 3 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue = (
uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { real_T outValue =
0 ; { real_T result = rtP . dummy2_Value ; outValue = round ( result ) ; } {
uint8_T packedValue ; if ( outValue > ( real_T ) ( 3 ) ) { packedValue = (
uint8_T ) 3 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue = (
uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 4 ) ) ; } } } } { real_T outValue =
0 ; { real_T result = rtP . dummy2_Value ; outValue = round ( result ) ; } {
uint8_T packedValue ; if ( outValue > ( real_T ) ( 3 ) ) { packedValue = (
uint8_T ) 3 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue = (
uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( outValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { real_T outValue =
0 ; { real_T result = rtB . gs1ggdpy4b ; result = result * ( 1 / 0.5 ) ;
outValue = round ( result ) ; } { uint16_T packedValue ; if ( outValue > (
real_T ) ( 65535 ) ) { packedValue = ( uint16_T ) 65535 ; } else if (
outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; } else {
packedValue = ( uint16_T ) ( outValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 0 ] = pgn_entry_ptr -> DataBufferPtr [ 0 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 1 ] = pgn_entry_ptr ->
DataBufferPtr [ 1 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } { real_T outValue = 0 ; { real_T result = rtB . gs1ggdpy4b ; result =
result * ( 1 / 0.5 ) ; outValue = round ( result ) ; } { uint16_T packedValue
; if ( outValue > ( real_T ) ( 65535 ) ) { packedValue = ( uint16_T ) 65535 ;
} else if ( outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; }
else { packedValue = ( uint16_T ) ( outValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 2 ] = pgn_entry_ptr -> DataBufferPtr [ 2 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr ->
DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } { real_T outValue = 0 ; { real_T result = rtB . gs1ggdpy4b ; result =
result * ( 1 / 0.5 ) ; outValue = round ( result ) ; } { uint16_T packedValue
; if ( outValue > ( real_T ) ( 65535 ) ) { packedValue = ( uint16_T ) 65535 ;
} else if ( outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; }
else { packedValue = ( uint16_T ) ( outValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 4 ] = pgn_entry_ptr -> DataBufferPtr [ 4 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 5 ] = pgn_entry_ptr ->
DataBufferPtr [ 5 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } J1939SendMessage ( configHandle , pgn_entry_ptr ) ; UNLOCK_PGN_ENTRY (
pgn_entry_ptr , J1939_APP_TASK ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) {
rtB . gze5jcom5s = rtDW . mluvktfvfy ; } rtB . ha4qtjrmin = ssGetT ( rtS ) ;
if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . ndy1r3lteo = dcctc4vfs1 ; if (
! rtDW . dqrx4b5l1l ) { rtDW . dqrx4b5l1l = true ; rtDW . ksp31oyn4z = true ;
rtDW . gwi2bo5yvs = true ; rtDW . ei55bolyl0 = true ; rtDW . c1a2ddum24 = rtB
. gze5jcom5s ; rtDW . od5y3smrxh = rtB . ha4qtjrmin ; rtDW . frdq0ezqxz =
true ; rtDW . dedzusgrw0 = true ; } if ( ( rtB . ha4qtjrmin < rtDW .
od5y3smrxh ) && ( rtDW . n3jvfqlh1d > 0.0 ) ) { if ( rtB . ha4qtjrmin - rtDW
. jie24f0s0n < 0.5 ) { rtDW . n3jvfqlh1d = 1.0 ; } else if ( rtB . ha4qtjrmin
- rtDW . jie24f0s0n < 1.5 ) { rtDW . n3jvfqlh1d = 2.0 ; } else if ( rtB .
ha4qtjrmin - rtDW . jie24f0s0n < 2.0 ) { rtDW . n3jvfqlh1d = 3.0 ; } else {
rtDW . n3jvfqlh1d = 0.0 ; } } rtDW . od5y3smrxh = rtB . ha4qtjrmin ; rtDW .
jescywanqo = rtDW . n3jvfqlh1d ; switch ( ( int32_T ) rtDW . n3jvfqlh1d ) {
case 0 : if ( rtB . gze5jcom5s != rtDW . c1a2ddum24 ) { rtDW . jie24f0s0n =
rtB . ha4qtjrmin ; rtDW . h1t2m1slzp = rtB . gze5jcom5s ; rtDW . n3jvfqlh1d =
1.0 ; } mzft4ob5pz = 1.0 ; k0n05ujcou = rtDW . c1a2ddum24 ; break ; case 1 :
if ( rtB . ha4qtjrmin - rtDW . jie24f0s0n > 0.5 ) { rtDW . n3jvfqlh1d = 2.0 ;
mzft4ob5pz = 0.0 ; } else { mzft4ob5pz = 1.0 - ( rtB . ha4qtjrmin - rtDW .
jie24f0s0n ) / 0.5 ; } k0n05ujcou = rtDW . c1a2ddum24 ; break ; case 2 : if (
rtB . ha4qtjrmin > ( rtDW . jie24f0s0n + 0.5 ) + 1.0 ) { rtDW . n3jvfqlh1d =
3.0 ; mzft4ob5pz = ( rtB . ha4qtjrmin - ( ( rtDW . jie24f0s0n + 0.5 ) + 1.0 )
) / 0.5 ; } else { mzft4ob5pz = 0.0 ; } k0n05ujcou = rtDW . h1t2m1slzp ;
break ; case 3 : if ( rtB . ha4qtjrmin > ( ( rtDW . jie24f0s0n + 0.5 ) + 1.0
) + 0.5 ) { rtDW . n3jvfqlh1d = 0.0 ; mzft4ob5pz = 1.0 ; } else { mzft4ob5pz
= ( rtB . ha4qtjrmin - ( ( rtDW . jie24f0s0n + 0.5 ) + 1.0 ) ) / 0.5 ; }
k0n05ujcou = rtDW . h1t2m1slzp ; rtDW . c1a2ddum24 = rtDW . h1t2m1slzp ;
break ; } rtB . nmprwynq2w = mzft4ob5pz ; rtB . n0gg0eojnl = k0n05ujcou ; rtB
. diwh55j5zr = rtP . Gain9_Gain * rtB . n0gg0eojnl ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { { HCONFIG configHandle = ( HCONFIG ) rtDW . kr1tkdktl0 .
CONFIGHANDLE ; PgnEntry_T * pgn_entry_ptr = ( PgnEntry_T * ) rtDW .
kr1tkdktl0 . PGPTR ; uint32_T pgn ; uint32_T active = 0 ; PGN_TYPE *
pgn_fields ; int_T j ; uint16_T nOutputBytes ; active = ( uint32_T ) rtB .
nnky4aaqaz ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr -> CA -> Active &&
active && LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ) { pgn_entry_ptr
-> TargetAddress = 255U ; nOutputBytes = 8U ; for ( j = 0 ; j < nOutputBytes
; j ++ ) { pgn_entry_ptr -> DataBufferPtr [ j ] = 0xFF ; } pgn = 61445U ;
pgn_fields = ( PGN_TYPE * ) & pgn ; { real_T outValue = 0 ; { real_T result =
rtB . k4n1klhres ; result = result * ( 1 / 0.001 ) ; outValue = round (
result ) ; } { uint16_T packedValue ; if ( outValue > ( real_T ) ( 65535 ) )
{ packedValue = ( uint16_T ) 65535 ; } else if ( outValue < ( real_T ) ( 0 )
) { packedValue = ( uint16_T ) 0 ; } else { packedValue = ( uint16_T ) (
outValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 1 ] = pgn_entry_ptr ->
DataBufferPtr [ 1 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) (
packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T ) 0xFFU ) ) ; pgn_entry_ptr
-> DataBufferPtr [ 2 ] = pgn_entry_ptr -> DataBufferPtr [ 2 ] & ( uint8_T ) ~
( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T ) ( packedValue & ( uint16_T )
0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; } } } } { real_T outValue = 0 ; {
real_T result = rtB . diwh55j5zr ; result = result - - 125.0 ; outValue =
round ( result ) ; } { uint8_T packedValue ; if ( outValue > ( real_T ) ( 255
) ) { packedValue = ( uint8_T ) 255 ; } else if ( outValue < ( real_T ) ( 0 )
) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
outValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr ->
DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( packedValue ^ ( uint8_T )
0xFFU ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T result = (
uint32_T ) ( rtB . fvm1pndj51 [ 0 ] ) ; packingValue = result ; } { uint16_T
packedValue ; packedValue = ( uint16_T ) ( packingValue ) ; { { pgn_entry_ptr
-> DataBufferPtr [ 6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] & ( uint8_T ) ~
( ( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ (
uint16_T ) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 7 ] = pgn_entry_ptr
-> DataBufferPtr [ 7 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( (
uint16_T ) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU
) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T )
( rtB . kminp3y1kp [ 0 ] ) ; packingValue = result ; } { uint16_T packedValue
; packedValue = ( uint16_T ) ( packingValue ) ; { { pgn_entry_ptr ->
DataBufferPtr [ 4 ] = pgn_entry_ptr -> DataBufferPtr [ 4 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 5 ] = pgn_entry_ptr ->
DataBufferPtr [ 5 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } { real_T outValue = 0 ; { real_T result = rtB . diwh55j5zr ; result =
result - - 125.0 ; outValue = round ( result ) ; } { uint8_T packedValue ; if
( outValue > ( real_T ) ( 255 ) ) { packedValue = ( uint8_T ) 255 ; } else if
( outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else {
packedValue = ( uint8_T ) ( outValue ) ; } { { pgn_entry_ptr -> DataBufferPtr
[ 0 ] = pgn_entry_ptr -> DataBufferPtr [ 0 ] & ( uint8_T ) ~ ( ( uint8_T ) (
packedValue ^ ( uint8_T ) 0xFFU ) ) ; } } } } J1939SendMessage ( configHandle
, pgn_entry_ptr ) ; UNLOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) ; } }
} if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . deirtazmpx = rtB . nmprwynq2w
; } rtB . hzphm3vuhc = rtB . bmo2rqwngx ; { HCONFIG configHandle = ( HCONFIG
) rtDW . imsyrbpl23 . CONFIGHANDLE ; PgnEntry_T * pgn_entry_ptr = (
PgnEntry_T * ) rtDW . imsyrbpl23 . PGPTR ; uint32_T pgn ; uint32_T active = 0
; PGN_TYPE * pgn_fields ; int_T j ; uint16_T nOutputBytes ; active = (
uint32_T ) rtB . nnky4aaqaz ; if ( pgn_entry_ptr != NULL && pgn_entry_ptr ->
CA -> Active && active && LOCK_PGN_ENTRY ( pgn_entry_ptr , J1939_APP_TASK ) )
{ pgn_entry_ptr -> TargetAddress = 255U ; nOutputBytes = 8U ; for ( j = 0 ; j
< nOutputBytes ; j ++ ) { pgn_entry_ptr -> DataBufferPtr [ j ] = 0xFF ; } pgn
= 65265U ; pgn_fields = ( PGN_TYPE * ) & pgn ; { uint32_T packingValue = 0 ;
{ uint32_T result = ( uint32_T ) ( rtB . efkmx5vf54 ) ; packingValue = result
; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) {
packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 )
) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr
-> DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 4 ) ) ;
} } } } { real_T outValue = 0 ; { real_T result = rtB . deirtazmpx ; outValue
= round ( result ) ; } { uint8_T packedValue ; if ( outValue > ( real_T ) ( 3
) ) { packedValue = ( uint8_T ) 3 ; } else if ( outValue < ( real_T ) ( 0 ) )
{ packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( outValue
) ; } { { pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr ->
DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T )
( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } {
uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB .
kvxbfpgjze ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 4 ] = pgn_entry_ptr -> DataBufferPtr [ 4 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^
( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T packingValue = 0 ; {
uint32_T result = ( uint32_T ) ( rtB . d4fubsaq1v ) ; packingValue = result ;
} { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) {
packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 )
) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr
-> DataBufferPtr [ 3 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . ooofdxrsnp ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 4 ] =
pgn_entry_ptr -> DataBufferPtr [ 4 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U
) << 2 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T result = (
uint32_T ) ( rtB . bk2poabk1f ) ; packingValue = result ; } { uint8_T
packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue = (
uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue
= ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( packingValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 3 ] = pgn_entry_ptr -> DataBufferPtr [ 3 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . awfdpaljkk ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 0 ] =
pgn_entry_ptr -> DataBufferPtr [ 0 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U
) << 4 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T result = (
uint32_T ) ( rtB . klnxngbb1k ) ; packingValue = result ; } { uint8_T
packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue = (
uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue
= ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( packingValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 4 ] = pgn_entry_ptr -> DataBufferPtr [ 4 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . bajmf2pksh ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 255 ) ) { packedValue = ( uint8_T ) 255 ; } else if (
packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else {
packedValue = ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 5 ] = pgn_entry_ptr -> DataBufferPtr [ 5 ] & ( uint8_T ) ~ (
( uint8_T ) ( packedValue ^ ( uint8_T ) 0xFFU ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . l0kuu0ds13 ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 4 ] =
pgn_entry_ptr -> DataBufferPtr [ 4 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) ) ; } } } }
{ uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB .
a33eudfoqk ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 7 ) ) { packedValue = ( uint8_T ) 7 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x7U ) ^
( uint8_T ) 0x7U ) << 5 ) ) ; } } } } { uint32_T packingValue = 0 ; {
uint32_T result = ( uint32_T ) ( rtB . dn5b4tnvem ) ; packingValue = result ;
} { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) {
packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 )
) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 7 ] = pgn_entry_ptr
-> DataBufferPtr [ 7 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 2 ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB
. bmptpxj5fu ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 7 ] = pgn_entry_ptr -> DataBufferPtr [ 7 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T )
0x3U ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T result = (
uint32_T ) ( rtB . p5dhuulwqq ) ; packingValue = result ; } { uint8_T
packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue = (
uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue
= ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( packingValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 7 ] = pgn_entry_ptr -> DataBufferPtr [ 7 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . dlya0nsoeh ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 7 ] =
pgn_entry_ptr -> DataBufferPtr [ 7 ] & ( uint8_T ) ~ ( ( uint8_T ) ( (
uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U
) << 4 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T result = (
uint32_T ) ( rtB . jro4altozu ) ; packingValue = result ; } { uint8_T
packedValue ; if ( packingValue > ( boolean_T ) ( 31 ) ) { packedValue = (
uint8_T ) 31 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue
= ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) ( packingValue ) ; } { {
pgn_entry_ptr -> DataBufferPtr [ 6 ] = pgn_entry_ptr -> DataBufferPtr [ 6 ] &
( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x1FU )
^ ( uint8_T ) 0x1FU ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( rtB . lq3cbmwulo ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue
= ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) {
packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 0 ] = pgn_entry_ptr
-> DataBufferPtr [ 0 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) << 6 ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB
. d4bourvq1r ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 0 ] = pgn_entry_ptr -> DataBufferPtr [ 0 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ^
( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue = 0 ; {
uint32_T result = ( uint32_T ) ( rtB . eskiwmqp4i ) ; packingValue = result ;
} { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) {
packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 )
) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { pgn_entry_ptr -> DataBufferPtr [ 0 ] = pgn_entry_ptr
-> DataBufferPtr [ 0 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) ^ ( uint8_T ) 0x3U ) ) ; } } } } { real_T
outValue = 0 ; { real_T result = rtB . hzphm3vuhc ; result = result * ( 1 /
0.00390625 ) ; outValue = round ( result ) ; } { uint16_T packedValue ; if (
outValue > ( real_T ) ( 65535 ) ) { packedValue = ( uint16_T ) 65535 ; } else
if ( outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint16_T ) 0 ; } else {
packedValue = ( uint16_T ) ( outValue ) ; } { { pgn_entry_ptr ->
DataBufferPtr [ 1 ] = pgn_entry_ptr -> DataBufferPtr [ 1 ] & ( uint8_T ) ~ (
( uint8_T ) ( ( uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ^ ( uint16_T
) 0xFFU ) ) ; pgn_entry_ptr -> DataBufferPtr [ 2 ] = pgn_entry_ptr ->
DataBufferPtr [ 2 ] & ( uint8_T ) ~ ( ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ^ ( uint16_T ) 0xFFU ) ) ; }
} } } J1939SendMessage ( configHandle , pgn_entry_ptr ) ; UNLOCK_PGN_ENTRY (
pgn_entry_ptr , J1939_APP_TASK ) ; } } rtB . pdpozm2pyi . ID = 419361278U ;
rtB . pdpozm2pyi . Length = 8U ; rtB . pdpozm2pyi . Extended = 1U ; rtB .
pdpozm2pyi . Remote = 0 ; rtB . pdpozm2pyi . Data [ 0 ] = 0 ; rtB .
pdpozm2pyi . Data [ 1 ] = 0 ; rtB . pdpozm2pyi . Data [ 2 ] = 0 ; rtB .
pdpozm2pyi . Data [ 3 ] = 0 ; rtB . pdpozm2pyi . Data [ 4 ] = 0 ; rtB .
pdpozm2pyi . Data [ 5 ] = 0 ; rtB . pdpozm2pyi . Data [ 6 ] = 0 ; rtB .
pdpozm2pyi . Data [ 7 ] = 0 ; { { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( rtB . efkmx5vf54 ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue
= ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) {
packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 3 ] = rtB . pdpozm2pyi .
Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 4 ) ) ; } } } } { real_T outValue = 0 ; { real_T result =
rtB . deirtazmpx ; outValue = round ( result ) ; } { uint8_T packedValue ; if
( outValue > ( real_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if (
outValue < ( real_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else {
packedValue = ( uint8_T ) ( outValue ) ; } { { rtB . pdpozm2pyi . Data [ 3 ]
= rtB . pdpozm2pyi . Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( rtB . kvxbfpgjze ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 4 ] = rtB . pdpozm2pyi .
Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( rtB . d4fubsaq1v ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue
= ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) {
packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 3 ] = rtB . pdpozm2pyi .
Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB
. ooofdxrsnp ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi .
Data [ 4 ] = rtB . pdpozm2pyi . Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . bk2poabk1f ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 3 ] = rtB .
pdpozm2pyi . Data [ 3 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( rtB . awfdpaljkk ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 0 ] = rtB . pdpozm2pyi .
Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( rtB . klnxngbb1k ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) ) { packedValue
= ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0 ) ) {
packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 4 ] = rtB . pdpozm2pyi .
Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) ( packedValue & (
uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T packingValue = 0 ; { uint32_T
result = ( uint32_T ) ( rtB . bajmf2pksh ) ; packingValue = result ; } {
uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 255 ) ) {
packedValue = ( uint8_T ) 255 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 5 ] = rtB . pdpozm2pyi .
Data [ 5 ] | ( uint8_T ) ( packedValue ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( rtB . l0kuu0ds13 ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 4 ] = rtB . pdpozm2pyi .
Data [ 4 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB
. a33eudfoqk ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 7 ) ) { packedValue = ( uint8_T ) 7 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi .
Data [ 6 ] = rtB . pdpozm2pyi . Data [ 6 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x7U ) << 5 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . dn5b4tnvem ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 7 ] = rtB .
pdpozm2pyi . Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( rtB . bmptpxj5fu ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 7 ] = rtB . pdpozm2pyi .
Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB
. p5dhuulwqq ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi .
Data [ 7 ] = rtB . pdpozm2pyi . Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . dlya0nsoeh ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 7 ] = rtB .
pdpozm2pyi . Data [ 7 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 4 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( rtB . jro4altozu ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 31 ) )
{ packedValue = ( uint8_T ) 31 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 6 ] = rtB . pdpozm2pyi .
Data [ 6 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x1FU ) )
; } } } } { uint32_T packingValue = 0 ; { uint32_T result = ( uint32_T ) (
rtB . lq3cbmwulo ) ; packingValue = result ; } { uint8_T packedValue ; if (
packingValue > ( boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else
if ( packingValue < ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; }
else { packedValue = ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi .
Data [ 0 ] = rtB . pdpozm2pyi . Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( (
uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) << 6 ) ) ; } } } } { uint32_T
packingValue = 0 ; { uint32_T result = ( uint32_T ) ( rtB . d4bourvq1r ) ;
packingValue = result ; } { uint8_T packedValue ; if ( packingValue > (
boolean_T ) ( 3 ) ) { packedValue = ( uint8_T ) 3 ; } else if ( packingValue
< ( boolean_T ) ( 0 ) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue
= ( uint8_T ) ( packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 0 ] = rtB .
pdpozm2pyi . Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( ( uint8_T ) (
packedValue & ( uint8_T ) 0x3U ) << 2 ) ) ; } } } } { uint32_T packingValue =
0 ; { uint32_T result = ( uint32_T ) ( rtB . eskiwmqp4i ) ; packingValue =
result ; } { uint8_T packedValue ; if ( packingValue > ( boolean_T ) ( 3 ) )
{ packedValue = ( uint8_T ) 3 ; } else if ( packingValue < ( boolean_T ) ( 0
) ) { packedValue = ( uint8_T ) 0 ; } else { packedValue = ( uint8_T ) (
packingValue ) ; } { { rtB . pdpozm2pyi . Data [ 0 ] = rtB . pdpozm2pyi .
Data [ 0 ] | ( uint8_T ) ( ( uint8_T ) ( packedValue & ( uint8_T ) 0x3U ) ) ;
} } } } { real_T outValue = 0 ; { real_T result = rtB . hzphm3vuhc ; result =
result * ( 1 / 0.0039062 ) ; outValue = round ( result ) ; } { uint16_T
packedValue ; if ( outValue > ( real_T ) ( 65535 ) ) { packedValue = (
uint16_T ) 65535 ; } else if ( outValue < ( real_T ) ( 0 ) ) { packedValue =
( uint16_T ) 0 ; } else { packedValue = ( uint16_T ) ( outValue ) ; } { { rtB
. pdpozm2pyi . Data [ 1 ] = rtB . pdpozm2pyi . Data [ 1 ] | ( uint8_T ) ( (
uint16_T ) ( packedValue & ( uint16_T ) 0xFFU ) ) ; rtB . pdpozm2pyi . Data [
2 ] = rtB . pdpozm2pyi . Data [ 2 ] | ( uint8_T ) ( ( uint16_T ) ( ( uint16_T
) ( packedValue & ( uint16_T ) 0xFF00U ) >> 8 ) ) ; } } } } } { if ( rtDW .
gtasy1jsdx . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
gtasy1jsdx . AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB .
pdpozm2pyi + 0 ) ; } } if ( ssIsSampleHit ( rtS , 3 , 0 ) ) { { PgnEntry_T *
pgn_entry_ptr = ( PgnEntry_T * ) rtDW . ekxqe2lb2z . PGPTR ; uint8_T
output_port_offset = 0 ; uint8_T newmsg = 0 ; if ( pgn_entry_ptr != NULL &&
pgn_entry_ptr -> CA -> Active && LOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ) { pgn_entry_ptr -> TargetAddress = 255U ; pgn_entry_ptr ->
DestinationType = 1U ; if ( pgn_entry_ptr -> NewMessage ) { newmsg = 1 ; { }
pgn_entry_ptr -> NewMessage = 0 ; } UNLOCK_PGN_ENTRY ( pgn_entry_ptr ,
J1939_APP_TASK ) ; } } } rtB . pcmk2laltd = rtP . radsRPM_Gain_edopox2oep *
rtB . c0cwgduetq ; rtB . ihfhxuyjzv = rtX . gdrfqkaj00 ; rtB . cofo4dglob =
rtX . dl0s2litjt ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtDW .
jtxmye3nth > rtP . Saturation_UpperSat_enesi2iumz ) { rtB . mtn4j2z4x0 = rtP
. Saturation_UpperSat_enesi2iumz ; } else if ( rtDW . jtxmye3nth < rtP .
Saturation_LowerSat_bn3le4gtty ) { rtB . mtn4j2z4x0 = rtP .
Saturation_LowerSat_bn3le4gtty ; } else { rtB . mtn4j2z4x0 = rtDW .
jtxmye3nth ; } } if ( rtP . model . engine . with_egr_act_model >= rtP .
Switch_Threshold ) { rtB . mbcrayrbd0 = ( rtP . model . engine . K_egr - 1.0
) * rtB . cofo4dglob ; rtB . elz2or5t0r = rtP . model . engine . K_egr * rtB
. ihfhxuyjzv ; rtB . mb3bxfx2lb = rtB . elz2or5t0r - rtB . mbcrayrbd0 ; rtB .
kaqpmomne3 = rtB . mb3bxfx2lb ; } else { rtB . kaqpmomne3 = rtB . mtn4j2z4x0
; } if ( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . px4ho0kp5r = rtB .
kaqpmomne3 ; rtDW . mquiy4fzeb = 0 ; if ( ( rtB . kaqpmomne3 != rtB .
kaqpmomne3 ) || ( rtP . Constant1_Value < rtB . kaqpmomne3 ) ) { rtB .
px4ho0kp5r = rtP . Constant1_Value ; rtDW . mquiy4fzeb = 1 ; } } } else { for
( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
px4ho0kp5r = rtB . kaqpmomne3 ; if ( rtDW . mquiy4fzeb == 1 ) { rtB .
px4ho0kp5r = rtP . Constant1_Value ; } } } rtB . fnlh0owg0m = rtP . model .
engine . c_egr [ 0 ] ; for ( isMsgAvailable = 1 ; isMsgAvailable < 3 ;
isMsgAvailable ++ ) { rtB . fnlh0owg0m = rtB . fnlh0owg0m * rtB . px4ho0kp5r
+ rtP . model . engine . c_egr [ isMsgAvailable ] ; } if (
ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ; isMsgAvailable
< 1 ; isMsgAvailable ++ ) { rtB . beztzub33z = rtB . fnlh0owg0m ; rtDW .
omeqzycfh2 = 0 ; if ( ( rtB . fnlh0owg0m != rtB . fnlh0owg0m ) || ( rtP .
Constant_Value_gcvl5az0p5 > rtB . fnlh0owg0m ) ) { rtB . beztzub33z = rtP .
Constant_Value_gcvl5az0p5 ; rtDW . omeqzycfh2 = 1 ; } } } else { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
beztzub33z = rtB . fnlh0owg0m ; if ( rtDW . omeqzycfh2 == 1 ) { rtB .
beztzub33z = rtP . Constant_Value_gcvl5az0p5 ; } } } if (
ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX . a3o55becan >= 20.0 * rtP .
model . engine . p_amb ) { if ( 20.0 * rtP . model . engine . p_amb != rtX .
a3o55becan ) { rtX . a3o55becan = 20.0 * rtP . model . engine . p_amb ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . imt2dcvft2 = 3
; } else if ( rtX . a3o55becan <= 0.5 * rtP . model . engine . p_amb ) { if (
0.5 * rtP . model . engine . p_amb != rtX . a3o55becan ) { rtX . a3o55becan =
0.5 * rtP . model . engine . p_amb ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . imt2dcvft2 = 4
; } else { if ( rtDW . imt2dcvft2 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . imt2dcvft2 = 0
; } rtB . nvtq3ka1ru = rtX . a3o55becan ; } else { rtB . nvtq3ka1ru = rtX .
a3o55becan ; } rtB . lx4vqnwa25 = rtB . kiwuycktce / rtB . nvtq3ka1ru ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . cwyukvwtwb = rtB . lx4vqnwa25 >=
rtP . Saturation_UpperSat_hto0bhsqhd ? 1 : rtB . lx4vqnwa25 > rtP . model .
engine . PI_egropt ? 0 : - 1 ; rtDW . ipcifxvj5x = rtB . hc01pdzof3 >= rtP .
Saturation1_UpperSat ? 1 : rtB . hc01pdzof3 > rtP . Saturation1_LowerSat ? 0
: - 1 ; } rtB . hniruipvai = rtDW . cwyukvwtwb == 1 ? rtP .
Saturation_UpperSat_hto0bhsqhd : rtDW . cwyukvwtwb == - 1 ? rtP . model .
engine . PI_egropt : rtB . lx4vqnwa25 ; rtB . aw3ze00r1f = rtB . nvtq3ka1ru /
rtB . kiwuycktce ; rtB . h1jzkaxeay = rtDW . ipcifxvj5x == 1 ? rtP .
Saturation1_UpperSat : rtDW . ipcifxvj5x == - 1 ? rtP . Saturation1_LowerSat
: rtB . hc01pdzof3 ; rtB . et2uhmlji2 = look1_binlxpw ( rtB . h1jzkaxeay ,
rtP . model . engine . limit_n_e , rtP . model . engine . limit_m_f , 32U ) ;
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { taskTimeV = rtB . nmprwynq2w * rtDW .
mp0kaoewzv ; if ( taskTimeV > rtP . Saturation_UpperSat_atvgvohnm4 ) { rtB .
fagi55uakt = rtP . Saturation_UpperSat_atvgvohnm4 ; } else if ( taskTimeV <
rtP . Saturation_LowerSat_bnot2t5v4i ) { rtB . fagi55uakt = rtP .
Saturation_LowerSat_bnot2t5v4i ; } else { rtB . fagi55uakt = taskTimeV ; } }
if ( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . ds5nytnni5 = rtB .
et2uhmlji2 ; rtDW . c2dyuklr3i = 0 ; if ( ( rtB . et2uhmlji2 != rtB .
et2uhmlji2 ) || ( rtB . fagi55uakt < rtB . et2uhmlji2 ) ) { rtB . ds5nytnni5
= rtB . fagi55uakt ; rtDW . c2dyuklr3i = 1 ; } } } else { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
ds5nytnni5 = rtB . et2uhmlji2 ; if ( rtDW . c2dyuklr3i == 1 ) { rtB .
ds5nytnni5 = rtB . fagi55uakt ; } } } rtB . hr10hckzct = rtP . model . engine
. n_cyl * 1.0E-6 / 120.0 * rtB . ds5nytnni5 * rtB . h1jzkaxeay ; if ( rtB .
kiwuycktce < 0.0 ) { taskTimeV = - muDoubleScalarSqrt ( - rtB . kiwuycktce )
; } else { taskTimeV = muDoubleScalarSqrt ( rtB . kiwuycktce ) ; } if ( rtB .
h1jzkaxeay < 0.0 ) { ratio = - muDoubleScalarSqrt ( - rtB . h1jzkaxeay ) ; }
else { ratio = muDoubleScalarSqrt ( rtB . h1jzkaxeay ) ; } rtB . kzvckvcpof =
( ( - 0.00020816619843224996 * taskTimeV + - 0.0034465158052700592 * ratio )
+ 1.1497021021059144 ) * rtB . kiwuycktce * rtB . h1jzkaxeay / rtP . model .
engine . T_im * ( rtP . model . engine . V_d / ( rtP . model . engine . R_a *
60.0 * 2.0 ) ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . fitzivdg3v =
rtDW . l2wwwtxl4l ; rtB . njcgrc3zvm = rtDW . ox1qbuvuuc ; } mzft4ob5pz = rtB
. hr10hckzct * 42900000.0 * ( 1.0 - rtB . fitzivdg3v ) / ( rtB . hr10hckzct +
rtB . kzvckvcpof ) ; k0n05ujcou = mzft4ob5pz * 2.3370584441920436e-14 / (
724.0 * rtB . njcgrc3zvm * 3.0744032413269453 ) + 1.0 ; if ( rtB . aw3ze00r1f
< 0.0 ) { taskTimeV = - muDoubleScalarPower ( - rtB . aw3ze00r1f ,
0.28387734915924823 ) ; } else { taskTimeV = muDoubleScalarPower ( rtB .
aw3ze00r1f , 0.28387734915924823 ) ; } if ( k0n05ujcou < 0.0 ) { ratio = -
muDoubleScalarPower ( - k0n05ujcou , - 0.28387734915924823 ) ; } else { ratio
= muDoubleScalarPower ( k0n05ujcou , - 0.28387734915924823 ) ; } rtB .
k5apsyzoda = 1.1015294624801442 * taskTimeV * 0.32526637578237438 * ratio * (
mzft4ob5pz * 0.00098911968348171036 + rtB . njcgrc3zvm * 3.0744032413269453 )
; if ( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . pgniezqsr0 = rtP .
Constant_Value_b5ccgfu4yk ; rtDW . p40fsqbchl = 0 ; if ( ( rtP .
Constant_Value_b5ccgfu4yk != rtP . Constant_Value_b5ccgfu4yk ) || ( rtB .
k5apsyzoda < rtP . Constant_Value_b5ccgfu4yk ) ) { rtB . pgniezqsr0 = rtB .
k5apsyzoda ; rtDW . p40fsqbchl = 1 ; } } } else { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . pgniezqsr0 = rtP .
Constant_Value_b5ccgfu4yk ; if ( rtDW . p40fsqbchl == 1 ) { rtB . pgniezqsr0
= rtB . k5apsyzoda ; } } } rtB . forqmcoyzl = rtB . kzvckvcpof + rtB .
hr10hckzct ; rtB . linntx1wlj = muDoubleScalarExp ( - 60.491655470984995 / (
rtB . forqmcoyzl * 1332.0 ) ) * ( rtB . pgniezqsr0 - 298.46362195121958 ) +
298.46362195121958 ; ratio = rtB . linntx1wlj * 286.0 ; if ( ratio < 0.0 ) {
taskTimeV = - muDoubleScalarSqrt ( - ratio ) ; } else { taskTimeV =
muDoubleScalarSqrt ( ratio ) ; } rtB . eixkduik4f = ( 1.0 -
muDoubleScalarPower ( ( 1.0 - rtB . hniruipvai ) / 0.34999595167386044 - 1.0
, 2.0 ) ) * ( 0.0004 * rtB . beztzub33z * rtB . nvtq3ka1ru ) / taskTimeV ;
rtB . drzrfcyncc = rtB . hmqeokdrxe + rtB . eixkduik4f ; rtB . bvz3zvgshe =
rtB . eixkduik4f / rtB . drzrfcyncc ; if ( ssIsModeUpdateTimeStep ( rtS ) ) {
for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
jyisic03f3 = rtB . hr10hckzct ; rtDW . l4mfodlgua = 0 ; if ( ( rtB .
hr10hckzct != rtB . hr10hckzct ) || ( rtP . FuelLimit_Value > rtB .
hr10hckzct ) ) { rtB . jyisic03f3 = rtP . FuelLimit_Value ; rtDW . l4mfodlgua
= 1 ; } } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ;
isMsgAvailable ++ ) { rtB . jyisic03f3 = rtB . hr10hckzct ; if ( rtDW .
l4mfodlgua == 1 ) { rtB . jyisic03f3 = rtP . FuelLimit_Value ; } } } if (
ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX . olhqyyiiqq >= rtP .
IntegratorX_Oim_UpperSat ) { if ( rtX . olhqyyiiqq != rtP .
IntegratorX_Oim_UpperSat ) { rtX . olhqyyiiqq = rtP .
IntegratorX_Oim_UpperSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } rtDW . kf0zhsqe1e = 3 ; } else if ( rtX . olhqyyiiqq <= rtP .
IntegratorX_Oim_LowerSat ) { if ( rtX . olhqyyiiqq != rtP .
IntegratorX_Oim_LowerSat ) { rtX . olhqyyiiqq = rtP .
IntegratorX_Oim_LowerSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } rtDW . kf0zhsqe1e = 4 ; } else { if ( rtDW . kf0zhsqe1e != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . kf0zhsqe1e = 0
; } rtB . ogasawbx31 = rtX . olhqyyiiqq ; } else { rtB . ogasawbx31 = rtX .
olhqyyiiqq ; } rtB . otng3qjdpw = 1.0 / ( rtP . model . engine . AFs * rtP .
model . engine . X_Oc ) * rtB . kzvckvcpof / rtB . jyisic03f3 * rtB .
ogasawbx31 ; rtB . ldefe4o41v = look_SplNBinXScd ( 1U , & rtB . pd4h1x0zka ,
( rt_LUTSplineWork * ) & rtDW . lqs2eqamfb [ 0 ] ) ; if ( ssIsSampleHit ( rtS
, 4 , 0 ) ) { rtDW . bih1twzowf = dcctc4vfs1 ; rtB . e10ply524g = 0.0 ; rtDW
. jcb0vgamw2 = dcctc4vfs1 ; if ( ( rtDW . o0eadiapoc != rtB . n0gg0eojnl ) ||
( rtB . nmprwynq2w != 1.0 ) ) { rtB . n22fqqxpxo = rtDW . o0eadiapoc ; } else
if ( ( rtB . hc01pdzof3 > 1250.0 ) && ( rtB . n0gg0eojnl < 14.0 ) ) { if ( (
rtB . hc01pdzof3 > 1800.0 ) && ( rtB . n0gg0eojnl < 13.0 ) ) { rtB .
n22fqqxpxo = rtB . n0gg0eojnl + 2.0 ; } else { rtB . n22fqqxpxo = rtB .
n0gg0eojnl + 1.0 ; } } else if ( ( rtB . hc01pdzof3 < 900.0 ) && ( rtB .
n0gg0eojnl > 4.0 ) ) { rtB . n22fqqxpxo = rtB . n0gg0eojnl - 1.0 ; } else {
rtB . n22fqqxpxo = rtB . n0gg0eojnl ; } rtB . n22fqqxpxo = muDoubleScalarMin
( muDoubleScalarMax ( rtB . n22fqqxpxo , 4.0 ) , 14.0 ) ; rtDW . o0eadiapoc =
rtB . n22fqqxpxo ; { if ( rtDW . p4sflk0g2w . AQHandles && ssGetLogOutput (
rtS ) ) { sdiWriteSignal ( rtDW . p4sflk0g2w . AQHandles , ssGetTaskTime (
rtS , 4 ) , ( char * ) & rtB . n22fqqxpxo + 0 ) ; } } rtDW . evb2jcnsmb =
dcctc4vfs1 ; taskTimeV = 0.0012 * rtB . kiwuycktce ; if ( rtDW . ozxovagibo <
rtB . n0gg0eojnl ) { taskTimeV *= 0.7 ; } rtDW . ozxovagibo = rtDW .
bzxfv0jxlh ; rtDW . bzxfv0jxlh = rtB . n0gg0eojnl ; taskTimeV =
muDoubleScalarMin ( ( rtP . control . v_set - rtB . bmo2rqwngx ) * 300.0 ,
taskTimeV ) ; if ( taskTimeV > rtP . Saturation_UpperSat ) { rtB . kc4ngec1x5
= rtP . Saturation_UpperSat ; } else if ( taskTimeV < rtP .
Saturation_LowerSat ) { rtB . kc4ngec1x5 = rtP . Saturation_LowerSat ; } else
{ rtB . kc4ngec1x5 = taskTimeV ; } { if ( rtDW . ofz4kqfoe0 . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . ofz4kqfoe0 . AQHandles ,
ssGetTaskTime ( rtS , 4 ) , ( char * ) & rtB . kc4ngec1x5 + 0 ) ; } } rtB .
d3yr0hfu1a = rtP . control . u_vgt ; rtB . j2q40ay2j1 = rtP . control . u_egr
; rtB . b0oj4tfbt4 = rtP . brake_Value ; rtB . m1vu5h1j0f = ssGetTaskTime (
rtS , 4 ) ; rtDW . dbfmnhxbxj = 4 ; } rtB . ksirzoklu3 = rtX . faiarhiizk ;
rtB . j1zi0jrhi4 = rtX . f10gbcy5as ; rtDW . ono0qix5io = dcctc4vfs1 ; if (
rtB . pd4h1x0zka > 1000.0 ) { rtB . eq0q3y5jp5 = rtB . j1zi0jrhi4 / ( 0.8 *
rtB . pd4h1x0zka / 100000.0 ) ; } else { rtB . eq0q3y5jp5 = ( rtNaN ) ; } if
( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . ktvccmzbfr = rtB .
otng3qjdpw ; rtDW . ie2rbfy2dj = 0 ; if ( ( rtB . otng3qjdpw != rtB .
otng3qjdpw ) || ( rtP . Constant_Value_nm5d5hyfni < rtB . otng3qjdpw ) ) {
rtB . ktvccmzbfr = rtP . Constant_Value_nm5d5hyfni ; rtDW . ie2rbfy2dj = 1 ;
} } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable
++ ) { rtB . ktvccmzbfr = rtB . otng3qjdpw ; if ( rtDW . ie2rbfy2dj == 1 ) {
rtB . ktvccmzbfr = rtP . Constant_Value_nm5d5hyfni ; } } } rtB . b4k3rvzg1m =
rtP . model . engine . eta_igch * rtB . ktvccmzbfr ; rtB . hotpdqr22m = rtB .
b4k3rvzg1m * rtP . Constant2_Value * rtB . ds5nytnni5 * ( rtP . model .
engine . q_HV * 1.0E-6 * rtP . model . engine . n_cyl ) ; rtB . ky5hu1sl5r =
rtB . nvtq3ka1ru - rtB . kiwuycktce ; rtB . opyybpyray = rtP . model . engine
. V_d * rtB . ky5hu1sl5r ; rtB . fp2bci2nfq = rtP . n_eratio_Gain * rtB .
h1jzkaxeay ; rtB . f04oqjsfjx = rtP . model . engine . c_fricVec [ 0 ] ; for
( isMsgAvailable = 1 ; isMsgAvailable < 3 ; isMsgAvailable ++ ) { rtB .
f04oqjsfjx = rtB . f04oqjsfjx * rtB . fp2bci2nfq + rtP . model . engine .
c_fricVec [ isMsgAvailable ] ; } rtB . evvikftrhr = rtP . model . engine .
V_d * 100000.0 * rtB . f04oqjsfjx ; rtB . ly5zsvwobo = ( rtB . hotpdqr22m -
rtB . opyybpyray ) - rtB . evvikftrhr ; rtB . ibko4nml5o = rtP . GainM_e_Gain
* rtB . ly5zsvwobo ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW .
p33krp3hyb . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
p33krp3hyb . AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB .
eq0q3y5jp5 + 0 ) ; } } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { { if ( rtDW .
dzibnwkozv . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
dzibnwkozv . AQHandles , ssGetTaskTime ( rtS , 2 ) , ( char * ) & rtB .
nmprwynq2w + 0 ) ; } } { if ( rtDW . m2ysthz4lp . AQHandles && ssGetLogOutput
( rtS ) ) { sdiWriteSignal ( rtDW . m2ysthz4lp . AQHandles , ssGetTaskTime (
rtS , 2 ) , ( char * ) & rtB . n0gg0eojnl + 0 ) ; } } } if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { { if ( rtDW . ltc2bikvjk . AQHandles && ssGetLogOutput (
rtS ) ) { sdiWriteSignal ( rtDW . ltc2bikvjk . AQHandles , ssGetTaskTime (
rtS , 1 ) , ( char * ) & rtB . hc01pdzof3 + 0 ) ; } } { if ( rtDW .
fwhtblllbe . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW .
fwhtblllbe . AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB .
pd4h1x0zka + 0 ) ; } } { if ( rtDW . kyvzs2v1y5 . AQHandles && ssGetLogOutput
( rtS ) ) { sdiWriteSignal ( rtDW . kyvzs2v1y5 . AQHandles , ssGetTaskTime (
rtS , 1 ) , ( char * ) & rtB . bmo2rqwngx + 0 ) ; } } } rtB . bbjwnzbysv =
0.5 * rtP . model . vehicle . rho * rtP . model . vehicle . C_d * rtP . model
. vehicle . A * ( rtB . fegajgngwz * rtB . fegajgngwz ) ; if ( ssIsSampleHit
( rtS , 4 , 0 ) ) { if ( rtB . b0oj4tfbt4 > rtP .
Saturation_UpperSat_fgktzvfm2k ) { taskTimeV = rtP .
Saturation_UpperSat_fgktzvfm2k ; } else if ( rtB . b0oj4tfbt4 < rtP .
Saturation_LowerSat_eegm4iokxr ) { taskTimeV = rtP .
Saturation_LowerSat_eegm4iokxr ; } else { taskTimeV = rtB . b0oj4tfbt4 ; }
rtB . k2q4u3lafs = muDoubleScalarMin ( rtP . BrakeGain_Gain * taskTimeV , rtB
. abyfl0makg ) ; } rtB . ay21w05qrx = rtB . fegajgngwz * rtP . const_Value ;
rtB . okv40fdgvu = rtB . ay21w05qrx * rtB . ay21w05qrx * rtP . model .
vehicle . c_r1 ; rtB . hwekqshicu = rtB . okv40fdgvu + rtP . model . vehicle
. c_r0 ; rtB . omwgk4e1kl = rtP . model . vehicle . m * rtP . model . vehicle
. g * muDoubleScalarCos ( rtB . ldefe4o41v ) ; rtB . oeo3ys3ci4 = rtB .
hwekqshicu * rtB . omwgk4e1kl ; rtB . bk4hs1x304 = rtP . model . vehicle . m
* rtP . model . vehicle . g * muDoubleScalarSin ( rtB . ldefe4o41v ) ; rtB .
mvg3ssqh31 = ( ( rtB . k2q4u3lafs + rtB . bbjwnzbysv ) + rtB . oeo3ys3ci4 ) +
rtB . bk4hs1x304 ; rtB . dwqarhpyfj = rtP . model . vehicle . r_w * rtB .
mvg3ssqh31 ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . ouddd1bq5c = rtP .
model . transmission . i_f * rt_Lookup ( & rtP . model . transmission .
r_gearNumbers [ 0 ] , 15 , rtB . n0gg0eojnl , & rtP . model . transmission .
r_gearRatios [ 0 ] ) ; } rtB . iinqiuxn3i = ( rtB . ibko4nml5o * rtB .
mms3wxyzqm / muDoubleScalarPower ( rtB . ouddd1bq5c , 2.0 ) + rtP . model .
engine . J_e * rtB . dwqarhpyfj / rtB . ouddd1bq5c ) / ( rtB . mms3wxyzqm /
muDoubleScalarPower ( rtB . ouddd1bq5c , 2.0 ) + rtP . model . engine . J_e )
; rtB . aiuwtukjl2 = rtB . pgdssncn1o - rtB . fefmeddlto * rtB . ouddd1bq5c ;
if ( ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . bi3ryeji3q = ( rtB .
aiuwtukjl2 >= 0.0 ) ; } rtB . jzkj5ctoqn = rtDW . bi3ryeji3q > 0 ? rtB .
aiuwtukjl2 : - rtB . aiuwtukjl2 ; if ( ssIsModeUpdateTimeStep ( rtS ) ) {
rtDW . hpyvhbyyfk = ( ( rtB . jzkj5ctoqn >= rtP . Relay1_OnVal ) || ( ( ! (
rtB . jzkj5ctoqn <= rtP . Relay1_OffVal ) ) && rtDW . hpyvhbyyfk ) ) ; rtDW .
gexhlxucmx = ( rtB . iinqiuxn3i >= 0.0 ) ; } if ( rtDW . hpyvhbyyfk ) { rtB .
p0pelhou1r = rtP . Relay1_YOn ; } else { rtB . p0pelhou1r = rtP . Relay1_YOff
; } rtB . jzm0xgagji = rtDW . gexhlxucmx > 0 ? rtB . iinqiuxn3i : - rtB .
iinqiuxn3i ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . ewquelfwcj = rtP .
model . clutch . M_max * rtB . nmprwynq2w ; rtB . pobigfdmnk = ( rtB .
ouddd1bq5c > rtP . Constant_Value_eler4bv4qe ) ; } if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . mv3mphax4f = ( ( rtB . aiuwtukjl2
>= rtP . Relay2_OnVal ) || ( ( ! ( rtB . aiuwtukjl2 <= rtP . Relay2_OffVal )
) && rtDW . mv3mphax4f ) ) ; } if ( rtDW . mv3mphax4f ) { taskTimeV = rtP .
Relay2_YOn ; } else { taskTimeV = rtP . Relay2_YOff ; } if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { rtB . mtgpjerup5 = rtB . ewquelfwcj * rtB . pobigfdmnk *
taskTimeV ; rtB . iwb3403aih = muDoubleScalarAbs ( rtB . mtgpjerup5 ) ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . dyrzzohb5s = ( rtB . jzm0xgagji <
rtB . iwb3403aih ) ; } rtB . dtbeclhhb3 = ( ( rtB . p0pelhou1r != 0.0 ) &&
rtDW . dyrzzohb5s ) ; } if ( rtB . dtbeclhhb3 ) { rtB . kny5u5cuyg = rtB .
iinqiuxn3i ; } else { rtB . kny5u5cuyg = rtB . mtgpjerup5 ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW . a5wlo524la . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . a5wlo524la . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . kny5u5cuyg + 0 ) ; } } { if (
rtDW . osoqnotoxt . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal (
rtDW . osoqnotoxt . AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB
. p0pelhou1r + 0 ) ; } } { if ( rtDW . afai5j1n5f . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . afai5j1n5f . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . mtgpjerup5 + 0 ) ; } } } rtB .
pyprhl40ct = rtB . ibko4nml5o - rtB . kny5u5cuyg ; rtB . n0czoqzhzp = rtB .
pyprhl40ct / rtP . model . engine . J_e ; if ( ssIsSampleHit ( rtS , 1 , 0 )
) { j0n0q3ll5d [ 0 ] = rtB . mtgpjerup5 ; j0n0q3ll5d [ 1 ] = taskTimeV ;
j0n0q3ll5d [ 2 ] = rtB . p0pelhou1r ; { if ( rtDW . gtasy1jsdxk . AQHandles
&& ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . gtasy1jsdxk . AQHandles
, ssGetTaskTime ( rtS , 1 ) , ( char * ) & j0n0q3ll5d [ 0 ] + 0 ) ; } } } rtB
. dcjlzvgjdk = rtB . kny5u5cuyg * rtB . ouddd1bq5c ; rtB . fwampsknte = rtB .
dcjlzvgjdk - rtB . dwqarhpyfj ; rtB . onmzapip3s = rtB . fwampsknte / rtB .
mms3wxyzqm ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW . jtwmyt455q
. AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . jtwmyt455q
. AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . otng3qjdpw + 0 )
; } } } if ( rtB . aw3ze00r1f < 0.0 ) { taskTimeV = - muDoubleScalarPower ( -
rtB . aw3ze00r1f , 0.71612265084075177 ) ; } else { taskTimeV =
muDoubleScalarPower ( rtB . aw3ze00r1f , 0.71612265084075177 ) ; } if (
k0n05ujcou < 0.0 ) { ratio = - muDoubleScalarPower ( - k0n05ujcou , -
0.71612265084075177 ) ; } else { ratio = muDoubleScalarPower ( k0n05ujcou , -
0.71612265084075177 ) ; } rtB . k2xcyxwsbw = taskTimeV * ratio / ( (
mzft4ob5pz * 0.99999999999997657 / ( ( mzft4ob5pz * 2.3370584441920436e-14 /
724.0 + rtB . njcgrc3zvm * 3.0744032413269453 ) * 1011.0 ) + 1.0 ) * 17.0 ) ;
if ( ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . bzymrve3xd = rtB . k2xcyxwsbw
>= rtP . Saturation_UpperSat_ehbc0hou2u ? 1 : rtB . k2xcyxwsbw > rtP .
Saturation_LowerSat_e2gfsq1ep3 ? 0 : - 1 ; } rtB . l2ijibgtxt = rtDW .
bzymrve3xd == 1 ? rtP . Saturation_UpperSat_ehbc0hou2u : rtDW . bzymrve3xd ==
- 1 ? rtP . Saturation_LowerSat_e2gfsq1ep3 : rtB . k2xcyxwsbw ; rtB .
did2wrnqd3 = ( 1.0 - rtB . l2ijibgtxt ) * rtP . model . engine . T_im + rtB .
l2ijibgtxt * rtB . pgniezqsr0 ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { rtDW
. cjg2lxwx3p = rtB . did2wrnqd3 >= rtP . Saturation1_UpperSat_haikx2purp ? 1
: rtB . did2wrnqd3 > rtP . Saturation1_LowerSat_ja3qpjhkdu ? 0 : - 1 ; } rtB
. j51psxbbsa = rtDW . cjg2lxwx3p == 1 ? rtP . Saturation1_UpperSat_haikx2purp
: rtDW . cjg2lxwx3p == - 1 ? rtP . Saturation1_LowerSat_ja3qpjhkdu : rtB .
did2wrnqd3 ; rtB . k5zbpv0nhl = ( rtB . kzvckvcpof * rtB . ogasawbx31 - rtB .
jyisic03f3 * 14.57 * 0.2314 ) / ( rtB . kzvckvcpof + rtB . jyisic03f3 ) ; if
( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . eqthr4105d = rtB .
k5zbpv0nhl ; rtDW . jbxbvwznkw = 0 ; if ( ( rtB . k5zbpv0nhl != rtB .
k5zbpv0nhl ) || ( rtP . Constant2_Value_c3vhbw33ec > rtB . k5zbpv0nhl ) ) {
rtB . eqthr4105d = rtP . Constant2_Value_c3vhbw33ec ; rtDW . jbxbvwznkw = 1 ;
} } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable
++ ) { rtB . eqthr4105d = rtB . k5zbpv0nhl ; if ( rtDW . jbxbvwznkw == 1 ) {
rtB . eqthr4105d = rtP . Constant2_Value_c3vhbw33ec ; } } } { real_T * *
uBuffer = ( real_T * * ) & rtDW . k4tau4hadb . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - ( rtP . model .
engine . tau_degr ) ; rtB . ahq1w0grid = rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , rtDW . mf4tzazbhp . CircularBufSize , & rtDW . mf4tzazbhp .
Last , rtDW . mf4tzazbhp . Tail , rtDW . mf4tzazbhp . Head , ( rtP . model .
engine . uInit_egr ) , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ( *
uBuffer + rtDW . mf4tzazbhp . CircularBufSize ) [ rtDW . mf4tzazbhp . Head ]
== ssGetT ( rtS ) ) ) ) ; } rtB . orgilm5inb = rtB . ahq1w0grid - rtB .
ihfhxuyjzv ; rtB . ojsnbdpor2 = 1.0 / rtP . model . engine . tau_egr1 * rtB .
orgilm5inb ; rtB . nlmicoqsbz = rtB . ahq1w0grid - rtB . cofo4dglob ; rtB .
kntt0fbjnf = 1.0 / rtP . model . engine . tau_egr2 * rtB . nlmicoqsbz ; rtB .
os3kqcyax0 = rtP . model . engine . p_amb / rtB . nvtq3ka1ru ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ; isMsgAvailable
< 1 ; isMsgAvailable ++ ) { rtB . jfjgbdkox2 = rtB . os3kqcyax0 ; rtDW .
ofeqpav0z1 = 0 ; if ( ( rtB . os3kqcyax0 != rtB . os3kqcyax0 ) || ( rtP .
Constant_Value_dwh2dts0z5 < rtB . os3kqcyax0 ) ) { rtB . jfjgbdkox2 = rtP .
Constant_Value_dwh2dts0z5 ; rtDW . ofeqpav0z1 = 1 ; } } } else { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
jfjgbdkox2 = rtB . os3kqcyax0 ; if ( rtDW . ofeqpav0z1 == 1 ) { rtB .
jfjgbdkox2 = rtP . Constant_Value_dwh2dts0z5 ; } } } rtB . kbxdatlwxl = rtX .
d0etugyxyo ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtDW . jahel4guj4 >
rtP . Saturation_UpperSat_imjkncmbbp ) { rtB . ko0hu3j2c1 = rtP .
Saturation_UpperSat_imjkncmbbp ; } else if ( rtDW . jahel4guj4 < rtP .
Saturation_LowerSat_jenqmbtgcj ) { rtB . ko0hu3j2c1 = rtP .
Saturation_LowerSat_jenqmbtgcj ; } else { rtB . ko0hu3j2c1 = rtDW .
jahel4guj4 ; } } if ( rtP . model . engine . with_vgt_act_model >= rtP .
Switch_Threshold_oyf5ishr1i ) { rtB . niafhsfiuh = rtB . kbxdatlwxl ; } else
{ rtB . niafhsfiuh = rtB . ko0hu3j2c1 ; } rtB . denq2sx3ui = 1.0 -
muDoubleScalarPower ( ( rtB . niafhsfiuh - 117.14474688230767 ) /
126.87193572285548 , 2.0 ) ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
iuxkrw4e5c = rtB . denq2sx3ui ; rtDW . f2rh3pjcf4 = 0 ; if ( ( rtB .
denq2sx3ui != rtB . denq2sx3ui ) || ( rtP . Constant_Value_pi0lofejm1 > rtB .
denq2sx3ui ) ) { rtB . iuxkrw4e5c = rtP . Constant_Value_pi0lofejm1 ; rtDW .
f2rh3pjcf4 = 1 ; } } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ;
isMsgAvailable ++ ) { rtB . iuxkrw4e5c = rtB . denq2sx3ui ; if ( rtDW .
f2rh3pjcf4 == 1 ) { rtB . iuxkrw4e5c = rtP . Constant_Value_pi0lofejm1 ; } }
} if ( rtB . iuxkrw4e5c < 0.0 ) { taskTimeV = - muDoubleScalarSqrt ( - rtB .
iuxkrw4e5c ) ; } else { taskTimeV = muDoubleScalarSqrt ( rtB . iuxkrw4e5c ) ;
} rtB . fgov33fphh = 1.9479627004385558 * taskTimeV - 0.77631189328675043 ;
if ( ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ;
isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . pzxkphoemf = rtB .
fgov33fphh ; rtDW . czpni4mnff = 0 ; if ( ( rtB . fgov33fphh != rtB .
fgov33fphh ) || ( rtP . Constant1_Value_cjbf34ugrc > rtB . fgov33fphh ) ) {
rtB . pzxkphoemf = rtP . Constant1_Value_cjbf34ugrc ; rtDW . czpni4mnff = 1 ;
} } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable
++ ) { rtB . pzxkphoemf = rtB . fgov33fphh ; if ( rtDW . czpni4mnff == 1 ) {
rtB . pzxkphoemf = rtP . Constant1_Value_cjbf34ugrc ; } } } if ( rtB .
jfjgbdkox2 < 0.0 ) { taskTimeV = - muDoubleScalarPower ( - rtB . jfjgbdkox2 ,
2.89019266110711 ) ; } else { taskTimeV = muDoubleScalarPower ( rtB .
jfjgbdkox2 , 2.89019266110711 ) ; } ratio = rtB . linntx1wlj * 286.0 ; if (
1.0 - taskTimeV < 0.0 ) { taskTimeV = - muDoubleScalarSqrt ( - ( 1.0 -
taskTimeV ) ) ; } else { taskTimeV = muDoubleScalarSqrt ( 1.0 - taskTimeV ) ;
} if ( ratio < 0.0 ) { ratio = - muDoubleScalarSqrt ( - ratio ) ; } else {
ratio = muDoubleScalarSqrt ( ratio ) ; } rtB . ivokndy15y =
0.00084557672626438816 * rtB . nvtq3ka1ru * taskTimeV * rtB . pzxkphoemf /
ratio ; rtB . kwjng0hwid = ( rtB . forqmcoyzl - rtB . ivokndy15y ) - rtB .
eixkduik4f ; rtB . obqy5rqktf = 286.0 * rtB . kwjng0hwid * rtB . linntx1wlj /
0.02 ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtX . fteoprdfjw >= rtP .
IntegratorX_Oem_UpperSat ) { if ( rtX . fteoprdfjw != rtP .
IntegratorX_Oem_UpperSat ) { rtX . fteoprdfjw = rtP .
IntegratorX_Oem_UpperSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } rtDW . edzwglzc12 = 3 ; } else if ( rtX . fteoprdfjw <= rtP .
IntegratorX_Oem_LowerSat ) { if ( rtX . fteoprdfjw != rtP .
IntegratorX_Oem_LowerSat ) { rtX . fteoprdfjw = rtP .
IntegratorX_Oem_LowerSat ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; } rtDW . edzwglzc12 = 4 ; } else { if ( rtDW . edzwglzc12 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } rtDW . edzwglzc12 = 0
; } rtB . dq2gexc5is = rtX . fteoprdfjw ; } else { rtB . dq2gexc5is = rtX .
fteoprdfjw ; } rtB . j2u4yltrpp = 286.0 * rtB . linntx1wlj / rtB . nvtq3ka1ru
/ 0.02 * rtB . forqmcoyzl * ( rtB . eqthr4105d - rtB . dq2gexc5is ) ; rtB .
kyljpuifbw = rtB . drzrfcyncc - rtB . kzvckvcpof ; rtB . blszti35p5 = 287.0 *
rtB . kyljpuifbw * rtP . model . engine . T_im / 0.022 ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ; isMsgAvailable
< 1 ; isMsgAvailable ++ ) { rtB . ja1ga1numg = rtB . bvz3zvgshe ; rtDW .
kcrt4gkpma = 0 ; if ( ( rtB . bvz3zvgshe != rtB . bvz3zvgshe ) || ( rtP .
Constant1_Value_fe1czv4ovb < rtB . bvz3zvgshe ) ) { rtB . ja1ga1numg = rtP .
Constant1_Value_fe1czv4ovb ; rtDW . kcrt4gkpma = 1 ; } } } else { for (
isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
ja1ga1numg = rtB . bvz3zvgshe ; if ( rtDW . kcrt4gkpma == 1 ) { rtB .
ja1ga1numg = rtP . Constant1_Value_fe1czv4ovb ; } } } rtB . jx23xarepd =
287.0 * rtP . model . engine . T_im / rtB . kiwuycktce / 0.022 * ( ( rtB .
dq2gexc5is - rtB . ogasawbx31 ) * rtB . eixkduik4f + ( 0.2314 - rtB .
ogasawbx31 ) * rtB . hmqeokdrxe ) ; rtB . gqm1fborqv [ 0 ] = rtB . hmqeokdrxe
- 0.27533757461959213 ; if ( rtB . ig3aydedki - 1.0 < 0.0 ) { taskTimeV = -
muDoubleScalarPower ( - ( rtB . ig3aydedki - 1.0 ) , 0.27075947387648991 ) ;
} else { taskTimeV = muDoubleScalarPower ( rtB . ig3aydedki - 1.0 ,
0.27075947387648991 ) ; } rtB . gqm1fborqv [ 1 ] = taskTimeV -
1.0455177468256369 ; rtB . oat5nwyvfb [ 0 ] = rtB . gqm1fborqv [ 0 ] ;
mzft4ob5pz = rtP . model . engine . Q_c [ 0 ] * rtB . gqm1fborqv [ 0 ] + rtB
. gqm1fborqv [ 1 ] * rtP . model . engine . Q_c [ 2 ] ; rtB . hmrufe3ypk [ 0
] = mzft4ob5pz ; taskTimeV = rtB . gqm1fborqv [ 0 ] * mzft4ob5pz ; rtB .
oat5nwyvfb [ 1 ] = rtB . gqm1fborqv [ 1 ] ; mzft4ob5pz = rtB . gqm1fborqv [ 0
] * rtP . model . engine . Q_c [ 1 ] + rtB . gqm1fborqv [ 1 ] * rtP . model .
engine . Q_c [ 3 ] ; rtB . hmrufe3ypk [ 1 ] = mzft4ob5pz ; rtB . dnrdowihpt =
rtB . gqm1fborqv [ 1 ] * mzft4ob5pz + taskTimeV ; rtB . hrhovrq2gk =
0.7363607879724583 - rtB . dnrdowihpt ; if ( ssIsModeUpdateTimeStep ( rtS ) )
{ for ( isMsgAvailable = 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB .
mqo4dyjf2d = rtB . hrhovrq2gk ; rtDW . gdkaitdhn2 = 0 ; if ( ( rtB .
hrhovrq2gk != rtB . hrhovrq2gk ) || ( rtP . Constant2_Value_imre1apqn2 > rtB
. hrhovrq2gk ) ) { rtB . mqo4dyjf2d = rtP . Constant2_Value_imre1apqn2 ; rtDW
. gdkaitdhn2 = 1 ; } } } else { for ( isMsgAvailable = 0 ; isMsgAvailable < 1
; isMsgAvailable ++ ) { rtB . mqo4dyjf2d = rtB . hrhovrq2gk ; if ( rtDW .
gdkaitdhn2 == 1 ) { rtB . mqo4dyjf2d = rtP . Constant2_Value_imre1apqn2 ; } }
} if ( rtB . ig3aydedki < 0.0 ) { taskTimeV = - muDoubleScalarPower ( - rtB .
ig3aydedki , 0.28387734915924823 ) ; } else { taskTimeV = muDoubleScalarPower
( rtB . ig3aydedki , 0.28387734915924823 ) ; } mzft4ob5pz = ( taskTimeV - 1.0
) * rtP . model . engine . T_amb / rtB . mqo4dyjf2d ; rtB . m0hw1e23zq = rtB
. hmqeokdrxe * 1011.0 * mzft4ob5pz ; rtB . llwhjyi5kh = mzft4ob5pz + rtP .
model . engine . T_amb ; { real_T * * uBuffer = ( real_T * * ) & rtDW .
hku5cqszwy . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( rtS ) ; real_T
tMinusDelay = simTime - ( rtP . model . engine . tau_dvgt ) ; rtB .
izbygssgku = rt_TDelayInterpolate ( tMinusDelay , 0.0 , * uBuffer , rtDW .
pszwtqz0gn . CircularBufSize , & rtDW . pszwtqz0gn . Last , rtDW . pszwtqz0gn
. Tail , rtDW . pszwtqz0gn . Head , ( rtP . model . engine . uInit_vgt ) , 1
, ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) && ( ( * uBuffer + rtDW .
pszwtqz0gn . CircularBufSize ) [ rtDW . pszwtqz0gn . Head ] == ssGetT ( rtS )
) ) ) ; } rtB . kadspyijan = rtB . izbygssgku - rtB . kbxdatlwxl ; rtB .
n5mu2ryb4f = 1.0 / rtP . model . engine . tau_vgt * rtB . kadspyijan ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { for ( isMsgAvailable = 0 ; isMsgAvailable
< 1 ; isMsgAvailable ++ ) { rtB . npvqij5mhv = rtP .
Constant_Value_ajsql1lpqg ; rtDW . j4aiaaqlli = 0 ; if ( ( rtP .
Constant_Value_ajsql1lpqg != rtP . Constant_Value_ajsql1lpqg ) || ( rtB .
c0cwgduetq > rtP . Constant_Value_ajsql1lpqg ) ) { rtB . npvqij5mhv = rtB .
c0cwgduetq ; rtDW . j4aiaaqlli = 1 ; } } rtDW . apmlxbmuwh = ( rtB .
npvqij5mhv >= rtP . model . engine . w_tlin ) ; } else { for ( isMsgAvailable
= 0 ; isMsgAvailable < 1 ; isMsgAvailable ++ ) { rtB . npvqij5mhv = rtP .
Constant_Value_ajsql1lpqg ; if ( rtDW . j4aiaaqlli == 1 ) { rtB . npvqij5mhv
= rtB . c0cwgduetq ; } } } if ( rtDW . apmlxbmuwh ) { if ( rtB . npvqij5mhv -
2769.2092015766916 < 0.0 ) { taskTimeV = - muDoubleScalarPower ( - ( rtB .
npvqij5mhv - 2769.2092015766916 ) , 0.010000098744565608 ) ; } else {
taskTimeV = muDoubleScalarPower ( rtB . npvqij5mhv - 2769.2092015766916 ,
0.010000098744565608 ) ; } rtB . dxjp03lei3 = 1.3563440681098633 * taskTimeV
; rtB . flepa2gomd = rtB . dxjp03lei3 ; } else { rtB . gpuw4gaeyd = ( rtB .
npvqij5mhv - 2769.2092015766916 ) * 1.4021470818125312 / 27.692092015766775 ;
rtB . flepa2gomd = rtB . gpuw4gaeyd ; } if ( rtB . jfjgbdkox2 < 0.0 ) {
taskTimeV = - muDoubleScalarPower ( - rtB . jfjgbdkox2 , 0.21471471471471471
) ; } else { taskTimeV = muDoubleScalarPower ( rtB . jfjgbdkox2 ,
0.21471471471471471 ) ; } taskTimeV = 2664.0 * rtB . linntx1wlj * ( 1.0 -
taskTimeV ) ; if ( taskTimeV < 0.0 ) { taskTimeV = - muDoubleScalarSqrt ( -
taskTimeV ) ; } else { taskTimeV = muDoubleScalarSqrt ( taskTimeV ) ; } rtB .
cyuyr3knsa = 0.04 * rtB . c0cwgduetq / taskTimeV ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . jw31kvp3ln = rtB . cyuyr3knsa >=
2.0 * rtP . model . engine . BSR_opt ? 1 : rtB . cyuyr3knsa > rtP .
Saturation_LowerSat_kzgxh2ssqh ? 0 : - 1 ; } rtB . ig43bemqvs = rtDW .
jw31kvp3ln == 1 ? 2.0 * rtP . model . engine . BSR_opt : rtDW . jw31kvp3ln ==
- 1 ? rtP . Saturation_LowerSat_kzgxh2ssqh : rtB . cyuyr3knsa ; rtB .
b1uoph40ee = 0.818002726891074 - muDoubleScalarPower ( rtB . ig43bemqvs -
0.97552031618020918 , 2.0 ) * rtB . flepa2gomd ; if ( ssIsModeUpdateTimeStep
( rtS ) ) { rtDW . aetkdo2sks = rtB . b1uoph40ee >= rtP .
Saturation1_UpperSat_pjh2z4fnof ? 1 : rtB . b1uoph40ee > rtP .
Saturation1_LowerSat_o3inkji2se ? 0 : - 1 ; } rtB . p1pmwhnw1j = rtDW .
aetkdo2sks == 1 ? rtP . Saturation1_UpperSat_pjh2z4fnof : rtDW . aetkdo2sks
== - 1 ? rtP . Saturation1_LowerSat_o3inkji2se : rtB . b1uoph40ee ; if ( rtB
. jfjgbdkox2 < 0.0 ) { taskTimeV = - muDoubleScalarPower ( - rtB . jfjgbdkox2
, 0.21471471471471471 ) ; } else { taskTimeV = muDoubleScalarPower ( rtB .
jfjgbdkox2 , 0.21471471471471471 ) ; } rtB . fn1q2rgqt1 = ( 1.0 - taskTimeV )
* rtB . linntx1wlj * rtB . p1pmwhnw1j * ( rtB . ivokndy15y * 1332.0 ) ; rtB .
nawvezg5up = rtB . fn1q2rgqt1 - rtB . m0hw1e23zq ; rtB . ks5oubt5ho = rtB .
nawvezg5up / rtB . c0cwgduetq ; rtB . oahz3ap5xd = 1.0 / rtP . model . engine
. J_t * rtB . ks5oubt5ho ; rtB . egpw0yftwz = rtP . Gain2_Gain_jj2oxunwb2 *
rtB . c0cwgduetq ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . ogaaumd32e = ( rtB . pd4h1x0zka >=
rtP . road . x_distanceVector [ 9904 ] ) ; } if ( rtDW . ogaaumd32e ) {
ssSetStopRequested ( rtS , 1 ) ; } { if ( rtDW . o0cbjrpiwk . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . o0cbjrpiwk . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . ldefe4o41v + 0 ) ; } } { if (
rtDW . dakk2fhtjk . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal (
rtDW . dakk2fhtjk . AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB
. ksirzoklu3 + 0 ) ; } } } rtB . lcmzvp5mvt = rtP . kmhms_Gain * rtB .
bmo2rqwngx ; rtB . ayyewbsw5d = muDoubleScalarSin ( rtB . ldefe4o41v ) * rtB
. lcmzvp5mvt ; { if ( rtDW . bzrmj3zxqu . AQHandles && ssGetLogOutput ( rtS )
) { sdiWriteSignal ( rtDW . bzrmj3zxqu . AQHandles , ssGetTaskTime ( rtS , 0
) , ( char * ) & rtB . ig43bemqvs + 0 ) ; } } mzft4ob5pz = ssGetT ( rtS ) ; {
if ( rtDW . pudhr5q1sv . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . pudhr5q1sv . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & mzft4ob5pz + 0 ) ; } } { if ( rtDW . ahb0xajdg5 . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . ahb0xajdg5 . AQHandles ,
ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . ibko4nml5o + 0 ) ; } } { if (
rtDW . jj02cyrtix . AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal (
rtDW . jj02cyrtix . AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB
. m0hw1e23zq + 0 ) ; } } { if ( rtDW . mduldnxlmb . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . mduldnxlmb . AQHandles ,
ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . fn1q2rgqt1 + 0 ) ; } } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW . o2domeg4ik . AQHandles &&
ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . o2domeg4ik . AQHandles ,
ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . njcgrc3zvm + 0 ) ; } } } { if
( rtDW . gtasy1jsdxk2 . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . gtasy1jsdxk2 . AQHandles , ssGetTaskTime ( rtS , 0 )
, ( char * ) & rtB . llwhjyi5kh + 0 ) ; } } { if ( rtDW . mhg3ukoydp .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . mhg3ukoydp .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . pgniezqsr0 + 0 ) ;
} } { if ( rtDW . kqufha1qme . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . kqufha1qme . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . linntx1wlj + 0 ) ; } } { if ( rtDW . ck00fvktvl .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . ck00fvktvl .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . hmqeokdrxe + 0 ) ;
} } { if ( rtDW . fsc12ul0nq . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . fsc12ul0nq . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . eixkduik4f + 0 ) ; } } { if ( rtDW . jk5klgbkjx .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . jk5klgbkjx .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . kzvckvcpof + 0 ) ;
} } { if ( rtDW . bgmhbb2ggj . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . bgmhbb2ggj . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . forqmcoyzl + 0 ) ; } } { if ( rtDW . jfed40pyro .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . jfed40pyro .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . hr10hckzct + 0 ) ;
} } { if ( rtDW . mgmkqdnd4h . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . mgmkqdnd4h . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . ivokndy15y + 0 ) ; } } { if ( rtDW . cqmz0ka510 .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . cqmz0ka510 .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . dq2gexc5is + 0 ) ;
} } { if ( rtDW . awm3x1p030 . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . awm3x1p030 . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . ogasawbx31 + 0 ) ; } } { if ( rtDW . pz3v3lsswe .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . pz3v3lsswe .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . egpw0yftwz + 0 ) ;
} } { if ( rtDW . nji534mx2v . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . nji534mx2v . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . otng3qjdpw + 0 ) ; } } { if ( rtDW . kn50mamzgm .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . kn50mamzgm .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . ds5nytnni5 + 0 ) ;
} } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW . lz2njt4sro .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . lz2njt4sro .
AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . mtn4j2z4x0 + 0 ) ;
} } { if ( rtDW . hw0crwwhgx . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . hw0crwwhgx . AQHandles , ssGetTaskTime ( rtS , 1 ) ,
( char * ) & rtB . ko0hu3j2c1 + 0 ) ; } } } { if ( rtDW . odefyqi2dd .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . odefyqi2dd .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . h1jzkaxeay + 0 ) ;
} } { if ( rtDW . jwv41mpadj . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . jwv41mpadj . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . p1pmwhnw1j + 0 ) ; } } { if ( rtDW . mtia2gm3mn .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . mtia2gm3mn .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . mqo4dyjf2d + 0 ) ;
} } { if ( rtDW . acteg3xdu0 . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . acteg3xdu0 . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . ja1ga1numg + 0 ) ; } } { if ( rtDW . dd50e1xu1m .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . dd50e1xu1m .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . kaqpmomne3 + 0 ) ;
} } { if ( rtDW . phol22yedf . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . phol22yedf . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . niafhsfiuh + 0 ) ; } } { if ( rtDW . pieup45y1d .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . pieup45y1d .
AQHandles , ssGetTaskTime ( rtS , 0 ) , ( char * ) & rtB . kiwuycktce + 0 ) ;
} } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( rtDW . n4ipdfmwpg .
AQHandles && ssGetLogOutput ( rtS ) ) { sdiWriteSignal ( rtDW . n4ipdfmwpg .
AQHandles , ssGetTaskTime ( rtS , 1 ) , ( char * ) & rtB . fitzivdg3v + 0 ) ;
} } } { if ( rtDW . pp33uvzuj4 . AQHandles && ssGetLogOutput ( rtS ) ) {
sdiWriteSignal ( rtDW . pp33uvzuj4 . AQHandles , ssGetTaskTime ( rtS , 0 ) ,
( char * ) & rtB . nvtq3ka1ru + 0 ) ; } } UNUSED_PARAMETER ( tid ) ; } void
MdlOutputsTID6 ( int_T tid ) { int32_T i ; int32_T tmp_e ; uint32_T arg3 ;
uint8_T tmp [ 31 ] ; uint8_T tmp_p [ 31 ] ; SimStruct * S ; void * diag ;
void * fqdzhdprux ; void * py1vce1vad ; tmp_e = suStringStackSize ( ) ; rtB .
l0kuu0ds13 = ( rtP . Constant29_Value != 0.0 ) ; rtB . a33eudfoqk = ( rtP .
Constant21_Value != 0.0 ) ; rtB . dn5b4tnvem = ( rtP . Constant22_Value !=
0.0 ) ; rtB . bmptpxj5fu = ( rtP . Constant32_Value != 0.0 ) ; rtB .
p5dhuulwqq = ( rtP . Constant23_Value != 0.0 ) ; rtB . dlya0nsoeh = ( rtP .
Constant24_Value != 0.0 ) ; rtB . jro4altozu = ( rtP . Constant25_Value !=
0.0 ) ; rtB . lq3cbmwulo = ( rtP . Constant26_Value != 0.0 ) ; rtB .
d4bourvq1r = ( rtP . Constant27_Value != 0.0 ) ; rtB . eskiwmqp4i = ( rtP .
Constant28_Value != 0.0 ) ; rtB . bajmf2pksh = ( rtP . Gain11_Gain * rtP .
Constant39_Value != 0.0 ) ; rtB . bk2poabk1f = ( rtP . Constant36_Value !=
0.0 ) ; rtB . awfdpaljkk = ( rtP . Constant37_Value != 0.0 ) ; rtB .
klnxngbb1k = ( rtP . Constant38_Value != 0.0 ) ; rtB . efkmx5vf54 = ( rtP .
Constant30_Value != 0.0 ) ; rtB . kvxbfpgjze = ( rtP . Constant33_Value !=
0.0 ) ; rtB . d4fubsaq1v = ( rtP . Constant34_Value != 0.0 ) ; rtB .
ooofdxrsnp = ( rtP . Constant35_Value != 0.0 ) ; rtB . k4n1klhres = rtP .
Gain10_Gain * rtP . dummy3_Value ; rtB . fgbfua1b4j = rtP . Gain7_Gain * rtP
. dummy1_Value ; py1vce1vad = suAddStackString ( NULL ) ; suCopyString (
py1vce1vad , rtP . StringConstant_String ) ; fqdzhdprux = suAddStackString (
NULL ) ; suCopyString ( fqdzhdprux , rtP . StringConstant1_String ) ; arg3 =
( uint32_T ) suStrlen ( py1vce1vad ) ; if ( arg3 > 31U ) { S = rtS ; diag =
CreateDiagnosticAsVoidPtr ( "Simulink:StringBlocks:StringBufferOverflow" , 4
, 1 , 1 , 5 , "TruckBenchmark/Controller/CAN TX//RX/String to ASCII" , 1 ,
arg3 , 1 , 31 ) ; rt_ssReportDiagnosticAsWarning ( S , diag ) ; }
suStrToAscii ( & tmp [ 0 ] , 31 , py1vce1vad ) ; for ( i = 0 ; i < 31 ; i ++
) { rtB . kminp3y1kp [ i ] = tmp [ i ] ; } arg3 = ( uint32_T ) suStrlen (
fqdzhdprux ) ; if ( arg3 > 31U ) { S = rtS ; diag = CreateDiagnosticAsVoidPtr
( "Simulink:StringBlocks:StringBufferOverflow" , 4 , 1 , 1 , 5 ,
"TruckBenchmark/Controller/CAN TX//RX/String to ASCII1" , 1 , arg3 , 1 , 31 )
; rt_ssReportDiagnosticAsWarning ( S , diag ) ; } suStrToAscii ( & tmp_p [ 0
] , 31 , fqdzhdprux ) ; for ( i = 0 ; i < 31 ; i ++ ) { rtB . fvm1pndj51 [ i
] = tmp_p [ i ] ; } rtB . mms3wxyzqm = rtP . model . vehicle . r_w * rtP .
model . vehicle . r_w * rtP . model . vehicle . m ; rtB . abyfl0makg = rtP .
model . vehicle . g * rtP . model . vehicle . m ;
suMoveReturnedStringsToTopOfCallerStack ( tmp_e , 0 ) ; UNUSED_PARAMETER (
tid ) ; } void MdlUpdate ( int_T tid ) { XDis * _rtXdis ; _rtXdis = ( ( XDis
* ) ssGetContStateDisabled ( rtS ) ) ; switch ( rtDW . bcl2uuqmhl ) { case 3
: if ( rtB . onmzapip3s < 0.0 ) { rtDW . bcl2uuqmhl = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; case 4 : if (
rtB . onmzapip3s > 0.0 ) { rtDW . bcl2uuqmhl = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
cwf2tewh2v = ( ( rtDW . bcl2uuqmhl == 3 ) || ( rtDW . bcl2uuqmhl == 4 ) ) ;
switch ( rtDW . nxjlr5banb ) { case 3 : if ( rtB . fegajgngwz < 0.0 ) { rtDW
. nxjlr5banb = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
break ; case 4 : if ( rtB . fegajgngwz > 0.0 ) { rtDW . nxjlr5banb = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
lpegok4bfi = ( ( rtDW . nxjlr5banb == 3 ) || ( rtDW . nxjlr5banb == 4 ) ) ;
switch ( rtDW . ja1c4asgaz ) { case 3 : if ( rtB . oahz3ap5xd < 0.0 ) { rtDW
. ja1c4asgaz = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
break ; case 4 : if ( rtB . oahz3ap5xd > 0.0 ) { rtDW . ja1c4asgaz = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
akhhz2ar2w = ( ( rtDW . ja1c4asgaz == 3 ) || ( rtDW . ja1c4asgaz == 4 ) ) ;
switch ( rtDW . btigisbrqf ) { case 3 : if ( rtB . blszti35p5 < 0.0 ) { rtDW
. btigisbrqf = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
break ; case 4 : if ( rtB . blszti35p5 > 0.0 ) { rtDW . btigisbrqf = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
ekar034xyr = ( ( rtDW . btigisbrqf == 3 ) || ( rtDW . btigisbrqf == 4 ) ) ;
switch ( rtDW . pfmhktgqz5 ) { case 3 : if ( rtB . n0czoqzhzp < 0.0 ) { rtDW
. pfmhktgqz5 = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
break ; case 4 : if ( rtB . n0czoqzhzp > 0.0 ) { rtDW . pfmhktgqz5 = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
aufcyghqde = ( ( rtDW . pfmhktgqz5 == 3 ) || ( rtDW . pfmhktgqz5 == 4 ) ) ;
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . mluvktfvfy = rtB . n22fqqxpxo ;
rtDW . jtxmye3nth = rtB . j2q40ay2j1 ; } switch ( rtDW . imt2dcvft2 ) { case
3 : if ( rtB . obqy5rqktf < 0.0 ) { rtDW . imt2dcvft2 = 1 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; case 4 : if (
rtB . obqy5rqktf > 0.0 ) { rtDW . imt2dcvft2 = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
a3o55becan = ( ( rtDW . imt2dcvft2 == 3 ) || ( rtDW . imt2dcvft2 == 4 ) ) ;
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . mp0kaoewzv = rtB . kc4ngec1x5 ;
rtDW . l2wwwtxl4l = rtB . l2ijibgtxt ; rtDW . ox1qbuvuuc = rtB . j51psxbbsa ;
} switch ( rtDW . kf0zhsqe1e ) { case 3 : if ( rtB . jx23xarepd < 0.0 ) {
rtDW . kf0zhsqe1e = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
} break ; case 4 : if ( rtB . jx23xarepd > 0.0 ) { rtDW . kf0zhsqe1e = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
olhqyyiiqq = ( ( rtDW . kf0zhsqe1e == 3 ) || ( rtDW . kf0zhsqe1e == 4 ) ) ; {
real_T * * uBuffer = ( real_T * * ) & rtDW . k4tau4hadb . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( rtS ) ; rtDW . mf4tzazbhp . Head = ( ( rtDW .
mf4tzazbhp . Head < ( rtDW . mf4tzazbhp . CircularBufSize - 1 ) ) ? ( rtDW .
mf4tzazbhp . Head + 1 ) : 0 ) ; if ( rtDW . mf4tzazbhp . Head == rtDW .
mf4tzazbhp . Tail ) { if ( ! rt_TDelayUpdateTailOrGrowBuf ( & rtDW .
mf4tzazbhp . CircularBufSize , & rtDW . mf4tzazbhp . Tail , & rtDW .
mf4tzazbhp . Head , & rtDW . mf4tzazbhp . Last , simTime - ( rtP . model .
engine . tau_degr ) , uBuffer , ( boolean_T ) 0 , false , & rtDW . mf4tzazbhp
. MaxNewBufSize ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; }
slsaSaveRawMemoryForSimTargetOP ( rtS ,
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Transport\nDelay_TUbuffer0"
, ( void * * ) ( & uBuffer [ 0 ] ) , 2 * rtDW . mf4tzazbhp . CircularBufSize
* sizeof ( real_T ) , ( NULL ) , ( NULL ) ) ; } ( * uBuffer + rtDW .
mf4tzazbhp . CircularBufSize ) [ rtDW . mf4tzazbhp . Head ] = simTime ; ( *
uBuffer ) [ rtDW . mf4tzazbhp . Head ] = rtB . mtn4j2z4x0 ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . jahel4guj4 = rtB . d3yr0hfu1a ; }
switch ( rtDW . edzwglzc12 ) { case 3 : if ( rtB . j2u4yltrpp < 0.0 ) { rtDW
. edzwglzc12 = 1 ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
break ; case 4 : if ( rtB . j2u4yltrpp > 0.0 ) { rtDW . edzwglzc12 = 2 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; } _rtXdis ->
fteoprdfjw = ( ( rtDW . edzwglzc12 == 3 ) || ( rtDW . edzwglzc12 == 4 ) ) ; {
real_T * * uBuffer = ( real_T * * ) & rtDW . hku5cqszwy . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( rtS ) ; rtDW . pszwtqz0gn . Head = ( ( rtDW .
pszwtqz0gn . Head < ( rtDW . pszwtqz0gn . CircularBufSize - 1 ) ) ? ( rtDW .
pszwtqz0gn . Head + 1 ) : 0 ) ; if ( rtDW . pszwtqz0gn . Head == rtDW .
pszwtqz0gn . Tail ) { if ( ! rt_TDelayUpdateTailOrGrowBuf ( & rtDW .
pszwtqz0gn . CircularBufSize , & rtDW . pszwtqz0gn . Tail , & rtDW .
pszwtqz0gn . Head , & rtDW . pszwtqz0gn . Last , simTime - ( rtP . model .
engine . tau_dvgt ) , uBuffer , ( boolean_T ) 0 , false , & rtDW . pszwtqz0gn
. MaxNewBufSize ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; }
slsaSaveRawMemoryForSimTargetOP ( rtS ,
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Transport\nDelay1_TUbuffer0"
, ( void * * ) ( & uBuffer [ 0 ] ) , 2 * rtDW . pszwtqz0gn . CircularBufSize
* sizeof ( real_T ) , ( NULL ) , ( NULL ) ) ; } ( * uBuffer + rtDW .
pszwtqz0gn . CircularBufSize ) [ rtDW . pszwtqz0gn . Head ] = simTime ; ( *
uBuffer ) [ rtDW . pszwtqz0gn . Head ] = rtB . ko0hu3j2c1 ; }
UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID6 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { XDis * _rtXdis ;
XDot * _rtXdot ; _rtXdis = ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ;
_rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; if ( _rtXdis -> cwf2tewh2v ) {
_rtXdot -> cwf2tewh2v = 0.0 ; } else { _rtXdot -> cwf2tewh2v = rtB .
onmzapip3s ; } if ( _rtXdis -> lpegok4bfi ) { _rtXdot -> lpegok4bfi = 0.0 ; }
else { _rtXdot -> lpegok4bfi = rtB . fegajgngwz ; } if ( _rtXdis ->
akhhz2ar2w ) { _rtXdot -> akhhz2ar2w = 0.0 ; } else { _rtXdot -> akhhz2ar2w =
rtB . oahz3ap5xd ; } if ( _rtXdis -> ekar034xyr ) { _rtXdot -> ekar034xyr =
0.0 ; } else { _rtXdot -> ekar034xyr = rtB . blszti35p5 ; } if ( _rtXdis ->
aufcyghqde ) { _rtXdot -> aufcyghqde = 0.0 ; } else { _rtXdot -> aufcyghqde =
rtB . n0czoqzhzp ; } _rtXdot -> gdrfqkaj00 = rtB . ojsnbdpor2 ; _rtXdot ->
dl0s2litjt = rtB . kntt0fbjnf ; if ( _rtXdis -> a3o55becan ) { _rtXdot ->
a3o55becan = 0.0 ; } else { _rtXdot -> a3o55becan = rtB . obqy5rqktf ; } if (
_rtXdis -> olhqyyiiqq ) { _rtXdot -> olhqyyiiqq = 0.0 ; } else { _rtXdot ->
olhqyyiiqq = rtB . jx23xarepd ; } _rtXdot -> faiarhiizk = rtB . ayyewbsw5d ;
_rtXdot -> f10gbcy5as = rtB . hr10hckzct ; _rtXdot -> d0etugyxyo = rtB .
n5mu2ryb4f ; if ( _rtXdis -> fteoprdfjw ) { _rtXdot -> fteoprdfjw = 0.0 ; }
else { _rtXdot -> fteoprdfjw = rtB . j2u4yltrpp ; } } void MdlProjection (
void ) { } void MdlZeroCrossings ( void ) { ZCV * _rtZCSV ; _rtZCSV = ( ( ZCV
* ) ssGetSolverZcSignalVector ( rtS ) ) ; switch ( rtDW . bcl2uuqmhl ) { case
1 : _rtZCSV -> lr3ji2rgwk = 0.0 ; _rtZCSV -> eommou5amd = rtP .
Integrator_UpperSat - rtP . Integrator_LowerSat ; break ; case 2 : _rtZCSV ->
lr3ji2rgwk = rtP . Integrator_LowerSat - rtP . Integrator_UpperSat ; _rtZCSV
-> eommou5amd = 0.0 ; break ; default : _rtZCSV -> lr3ji2rgwk = rtX .
cwf2tewh2v - rtP . Integrator_UpperSat ; _rtZCSV -> eommou5amd = rtX .
cwf2tewh2v - rtP . Integrator_LowerSat ; break ; } if ( ( rtDW . bcl2uuqmhl
== 3 ) || ( rtDW . bcl2uuqmhl == 4 ) ) { _rtZCSV -> b32en0czi5 = rtB .
onmzapip3s ; } else { _rtZCSV -> b32en0czi5 = 0.0 ; } switch ( rtDW .
nxjlr5banb ) { case 1 : _rtZCSV -> mlu3auj0vq = 0.0 ; _rtZCSV -> cacjlcr1nt =
rtP . Integrator1_UpperSat - rtP . Integrator1_LowerSat ; break ; case 2 :
_rtZCSV -> mlu3auj0vq = rtP . Integrator1_LowerSat - rtP .
Integrator1_UpperSat ; _rtZCSV -> cacjlcr1nt = 0.0 ; break ; default :
_rtZCSV -> mlu3auj0vq = rtX . lpegok4bfi - rtP . Integrator1_UpperSat ;
_rtZCSV -> cacjlcr1nt = rtX . lpegok4bfi - rtP . Integrator1_LowerSat ; break
; } if ( ( rtDW . nxjlr5banb == 3 ) || ( rtDW . nxjlr5banb == 4 ) ) { _rtZCSV
-> cw2v4azdro = rtB . fegajgngwz ; } else { _rtZCSV -> cw2v4azdro = 0.0 ; }
switch ( rtDW . ja1c4asgaz ) { case 1 : _rtZCSV -> cflsczbppg = 0.0 ; _rtZCSV
-> b5pki20a5d = rtP . Integratoromega_t_UpperSat - rtP .
Integratoromega_t_LowerSat ; break ; case 2 : _rtZCSV -> cflsczbppg = rtP .
Integratoromega_t_LowerSat - rtP . Integratoromega_t_UpperSat ; _rtZCSV ->
b5pki20a5d = 0.0 ; break ; default : _rtZCSV -> cflsczbppg = rtX . akhhz2ar2w
- rtP . Integratoromega_t_UpperSat ; _rtZCSV -> b5pki20a5d = rtX . akhhz2ar2w
- rtP . Integratoromega_t_LowerSat ; break ; } if ( ( rtDW . ja1c4asgaz == 3
) || ( rtDW . ja1c4asgaz == 4 ) ) { _rtZCSV -> dj0cbnt1la = rtB . oahz3ap5xd
; } else { _rtZCSV -> dj0cbnt1la = 0.0 ; } switch ( rtDW . btigisbrqf ) {
case 1 : _rtZCSV -> m0i4snnkas = 0.0 ; _rtZCSV -> owwq5xupbf = 10.0 * rtP .
model . engine . p_amb - 0.5 * rtP . model . engine . p_amb ; break ; case 2
: _rtZCSV -> m0i4snnkas = 0.5 * rtP . model . engine . p_amb - 10.0 * rtP .
model . engine . p_amb ; _rtZCSV -> owwq5xupbf = 0.0 ; break ; default :
_rtZCSV -> m0i4snnkas = rtX . ekar034xyr - 10.0 * rtP . model . engine .
p_amb ; _rtZCSV -> owwq5xupbf = rtX . ekar034xyr - 0.5 * rtP . model . engine
. p_amb ; break ; } if ( ( rtDW . btigisbrqf == 3 ) || ( rtDW . btigisbrqf ==
4 ) ) { _rtZCSV -> jdg1ombjey = rtB . blszti35p5 ; } else { _rtZCSV ->
jdg1ombjey = 0.0 ; } if ( ( rtP . Constant1_Value_foo0ytc1ur != rtP .
Constant1_Value_foo0ytc1ur ) || ( rtB . bdsfootlbo > rtP .
Constant1_Value_foo0ytc1ur ) ) { if ( rtDW . ckyfoeqie5 == 0 ) { _rtZCSV ->
cnqckg51m5 = rtB . bdsfootlbo - rtB . bdsfootlbo ; } else { _rtZCSV ->
cnqckg51m5 = rtB . bdsfootlbo - rtP . Constant1_Value_foo0ytc1ur ; } } else
if ( rtDW . ckyfoeqie5 == 0 ) { _rtZCSV -> cnqckg51m5 = rtP .
Constant1_Value_foo0ytc1ur - rtB . bdsfootlbo ; } else { _rtZCSV ->
cnqckg51m5 = rtP . Constant1_Value_foo0ytc1ur - rtP .
Constant1_Value_foo0ytc1ur ; } if ( ( rtP . Constant1_Value_kvscu5x5rd != rtP
. Constant1_Value_kvscu5x5rd ) || ( rtB . egg3t2uoo3 > rtP .
Constant1_Value_kvscu5x5rd ) ) { if ( rtDW . ixaqaxatlt == 0 ) { _rtZCSV ->
ahmiwlbhvm = rtB . egg3t2uoo3 - rtB . egg3t2uoo3 ; } else { _rtZCSV ->
ahmiwlbhvm = rtB . egg3t2uoo3 - rtP . Constant1_Value_kvscu5x5rd ; } } else
if ( rtDW . ixaqaxatlt == 0 ) { _rtZCSV -> ahmiwlbhvm = rtP .
Constant1_Value_kvscu5x5rd - rtB . egg3t2uoo3 ; } else { _rtZCSV ->
ahmiwlbhvm = rtP . Constant1_Value_kvscu5x5rd - rtP .
Constant1_Value_kvscu5x5rd ; } if ( ( rtB . mocnuvcpgp != rtB . mocnuvcpgp )
|| ( rtP . Constant_Value_cfl4aorgnt > rtB . mocnuvcpgp ) ) { if ( rtDW .
fshou35ift == 0 ) { _rtZCSV -> ow1efrp4un = rtP . Constant_Value_cfl4aorgnt -
rtP . Constant_Value_cfl4aorgnt ; } else { _rtZCSV -> ow1efrp4un = rtP .
Constant_Value_cfl4aorgnt - rtB . mocnuvcpgp ; } } else if ( rtDW .
fshou35ift == 0 ) { _rtZCSV -> ow1efrp4un = rtB . mocnuvcpgp - rtP .
Constant_Value_cfl4aorgnt ; } else { _rtZCSV -> ow1efrp4un = rtB . mocnuvcpgp
- rtB . mocnuvcpgp ; } if ( ( rtP . Constant3_Value != rtP . Constant3_Value
) || ( rtB . nyt5uikcfo > rtP . Constant3_Value ) ) { if ( rtDW . cflc32uwnd
== 0 ) { _rtZCSV -> a3zb3vrb30 = rtB . nyt5uikcfo - rtB . nyt5uikcfo ; } else
{ _rtZCSV -> a3zb3vrb30 = rtB . nyt5uikcfo - rtP . Constant3_Value ; } } else
if ( rtDW . cflc32uwnd == 0 ) { _rtZCSV -> a3zb3vrb30 = rtP . Constant3_Value
- rtB . nyt5uikcfo ; } else { _rtZCSV -> a3zb3vrb30 = rtP . Constant3_Value -
rtP . Constant3_Value ; } if ( ( rtB . lsrw5owmej != rtB . lsrw5owmej ) || (
rtP . Constant2_Value_dfqgdtofyy > rtB . lsrw5owmej ) ) { if ( rtDW .
oqko4zquza == 0 ) { _rtZCSV -> fzprjsbtph = rtP . Constant2_Value_dfqgdtofyy
- rtP . Constant2_Value_dfqgdtofyy ; } else { _rtZCSV -> fzprjsbtph = rtP .
Constant2_Value_dfqgdtofyy - rtB . lsrw5owmej ; } } else if ( rtDW .
oqko4zquza == 0 ) { _rtZCSV -> fzprjsbtph = rtB . lsrw5owmej - rtP .
Constant2_Value_dfqgdtofyy ; } else { _rtZCSV -> fzprjsbtph = rtB .
lsrw5owmej - rtB . lsrw5owmej ; } _rtZCSV -> gmq4134fkn = rtB . fzqijlk23t -
rtP . Saturation_UpperSat_i32xa2dnvv ; _rtZCSV -> bgmfgfnqlx = rtB .
fzqijlk23t - rtP . Saturation_LowerSat_f5etl5uivq ; switch ( rtDW .
pfmhktgqz5 ) { case 1 : _rtZCSV -> kyjae5h2lu = 0.0 ; _rtZCSV -> berjub23jg =
rtP . Integrator1_UpperSat_pktoycczal - rtP . Integrator1_LowerSat_ofks0duo33
; break ; case 2 : _rtZCSV -> kyjae5h2lu = rtP .
Integrator1_LowerSat_ofks0duo33 - rtP . Integrator1_UpperSat_pktoycczal ;
_rtZCSV -> berjub23jg = 0.0 ; break ; default : _rtZCSV -> kyjae5h2lu = rtX .
aufcyghqde - rtP . Integrator1_UpperSat_pktoycczal ; _rtZCSV -> berjub23jg =
rtX . aufcyghqde - rtP . Integrator1_LowerSat_ofks0duo33 ; break ; } if ( (
rtDW . pfmhktgqz5 == 3 ) || ( rtDW . pfmhktgqz5 == 4 ) ) { _rtZCSV ->
mr4zgvyklq = rtB . n0czoqzhzp ; } else { _rtZCSV -> mr4zgvyklq = 0.0 ; } if (
( rtP . Constant1_Value != rtP . Constant1_Value ) || ( rtB . kaqpmomne3 <
rtP . Constant1_Value ) ) { if ( rtDW . mquiy4fzeb == 0 ) { _rtZCSV ->
fnrxk55avd = rtB . kaqpmomne3 - rtB . kaqpmomne3 ; } else { _rtZCSV ->
fnrxk55avd = rtB . kaqpmomne3 - rtP . Constant1_Value ; } } else if ( rtDW .
mquiy4fzeb == 0 ) { _rtZCSV -> fnrxk55avd = rtP . Constant1_Value - rtB .
kaqpmomne3 ; } else { _rtZCSV -> fnrxk55avd = rtP . Constant1_Value - rtP .
Constant1_Value ; } if ( ( rtP . Constant_Value_gcvl5az0p5 != rtP .
Constant_Value_gcvl5az0p5 ) || ( rtB . fnlh0owg0m > rtP .
Constant_Value_gcvl5az0p5 ) ) { if ( rtDW . omeqzycfh2 == 0 ) { _rtZCSV ->
g5znlndipk = rtB . fnlh0owg0m - rtB . fnlh0owg0m ; } else { _rtZCSV ->
g5znlndipk = rtB . fnlh0owg0m - rtP . Constant_Value_gcvl5az0p5 ; } } else if
( rtDW . omeqzycfh2 == 0 ) { _rtZCSV -> g5znlndipk = rtP .
Constant_Value_gcvl5az0p5 - rtB . fnlh0owg0m ; } else { _rtZCSV -> g5znlndipk
= rtP . Constant_Value_gcvl5az0p5 - rtP . Constant_Value_gcvl5az0p5 ; }
switch ( rtDW . imt2dcvft2 ) { case 1 : _rtZCSV -> mp4zunr0sq = 0.0 ; _rtZCSV
-> itbeoarcd1 = 20.0 * rtP . model . engine . p_amb - 0.5 * rtP . model .
engine . p_amb ; break ; case 2 : _rtZCSV -> mp4zunr0sq = 0.5 * rtP . model .
engine . p_amb - 20.0 * rtP . model . engine . p_amb ; _rtZCSV -> itbeoarcd1
= 0.0 ; break ; default : _rtZCSV -> mp4zunr0sq = rtX . a3o55becan - 20.0 *
rtP . model . engine . p_amb ; _rtZCSV -> itbeoarcd1 = rtX . a3o55becan - 0.5
* rtP . model . engine . p_amb ; break ; } if ( ( rtDW . imt2dcvft2 == 3 ) ||
( rtDW . imt2dcvft2 == 4 ) ) { _rtZCSV -> k35urubxm5 = rtB . obqy5rqktf ; }
else { _rtZCSV -> k35urubxm5 = 0.0 ; } _rtZCSV -> bf2qk2fhkd = rtB .
lx4vqnwa25 - rtP . Saturation_UpperSat_hto0bhsqhd ; _rtZCSV -> erjapnyqdp =
rtB . lx4vqnwa25 - rtP . model . engine . PI_egropt ; _rtZCSV -> cbu2blq4ae =
rtB . hc01pdzof3 - rtP . Saturation1_UpperSat ; _rtZCSV -> j5yhl3xbkg = rtB .
hc01pdzof3 - rtP . Saturation1_LowerSat ; if ( ( rtB . fagi55uakt != rtB .
fagi55uakt ) || ( rtB . et2uhmlji2 < rtB . fagi55uakt ) ) { if ( rtDW .
c2dyuklr3i == 0 ) { _rtZCSV -> bfmk1h5e3o = rtB . et2uhmlji2 - rtB .
et2uhmlji2 ; } else { _rtZCSV -> bfmk1h5e3o = rtB . et2uhmlji2 - rtB .
fagi55uakt ; } } else if ( rtDW . c2dyuklr3i == 0 ) { _rtZCSV -> bfmk1h5e3o =
rtB . fagi55uakt - rtB . et2uhmlji2 ; } else { _rtZCSV -> bfmk1h5e3o = rtB .
fagi55uakt - rtB . fagi55uakt ; } if ( ( rtB . k5apsyzoda != rtB . k5apsyzoda
) || ( rtP . Constant_Value_b5ccgfu4yk < rtB . k5apsyzoda ) ) { if ( rtDW .
p40fsqbchl == 0 ) { _rtZCSV -> fajvkrccpi = rtP . Constant_Value_b5ccgfu4yk -
rtP . Constant_Value_b5ccgfu4yk ; } else { _rtZCSV -> fajvkrccpi = rtP .
Constant_Value_b5ccgfu4yk - rtB . k5apsyzoda ; } } else if ( rtDW .
p40fsqbchl == 0 ) { _rtZCSV -> fajvkrccpi = rtB . k5apsyzoda - rtP .
Constant_Value_b5ccgfu4yk ; } else { _rtZCSV -> fajvkrccpi = rtB . k5apsyzoda
- rtB . k5apsyzoda ; } if ( ( rtP . FuelLimit_Value != rtP . FuelLimit_Value
) || ( rtB . hr10hckzct > rtP . FuelLimit_Value ) ) { if ( rtDW . l4mfodlgua
== 0 ) { _rtZCSV -> h4kzxcctcg = rtB . hr10hckzct - rtB . hr10hckzct ; } else
{ _rtZCSV -> h4kzxcctcg = rtB . hr10hckzct - rtP . FuelLimit_Value ; } } else
if ( rtDW . l4mfodlgua == 0 ) { _rtZCSV -> h4kzxcctcg = rtP . FuelLimit_Value
- rtB . hr10hckzct ; } else { _rtZCSV -> h4kzxcctcg = rtP . FuelLimit_Value -
rtP . FuelLimit_Value ; } switch ( rtDW . kf0zhsqe1e ) { case 1 : _rtZCSV ->
lpahibq2y5 = 0.0 ; _rtZCSV -> grarlpksb3 = rtP . IntegratorX_Oim_UpperSat -
rtP . IntegratorX_Oim_LowerSat ; break ; case 2 : _rtZCSV -> lpahibq2y5 = rtP
. IntegratorX_Oim_LowerSat - rtP . IntegratorX_Oim_UpperSat ; _rtZCSV ->
grarlpksb3 = 0.0 ; break ; default : _rtZCSV -> lpahibq2y5 = rtX . olhqyyiiqq
- rtP . IntegratorX_Oim_UpperSat ; _rtZCSV -> grarlpksb3 = rtX . olhqyyiiqq -
rtP . IntegratorX_Oim_LowerSat ; break ; } if ( ( rtDW . kf0zhsqe1e == 3 ) ||
( rtDW . kf0zhsqe1e == 4 ) ) { _rtZCSV -> m30aod4wy4 = rtB . jx23xarepd ; }
else { _rtZCSV -> m30aod4wy4 = 0.0 ; } if ( ( rtP . Constant_Value_nm5d5hyfni
!= rtP . Constant_Value_nm5d5hyfni ) || ( rtB . otng3qjdpw < rtP .
Constant_Value_nm5d5hyfni ) ) { if ( rtDW . ie2rbfy2dj == 0 ) { _rtZCSV ->
aokmth3ymy = rtB . otng3qjdpw - rtB . otng3qjdpw ; } else { _rtZCSV ->
aokmth3ymy = rtB . otng3qjdpw - rtP . Constant_Value_nm5d5hyfni ; } } else if
( rtDW . ie2rbfy2dj == 0 ) { _rtZCSV -> aokmth3ymy = rtP .
Constant_Value_nm5d5hyfni - rtB . otng3qjdpw ; } else { _rtZCSV -> aokmth3ymy
= rtP . Constant_Value_nm5d5hyfni - rtP . Constant_Value_nm5d5hyfni ; }
_rtZCSV -> dbecdvs4zo = rtB . aiuwtukjl2 ; if ( rtDW . hpyvhbyyfk ) { _rtZCSV
-> mag3ujlaw0 = rtB . jzkj5ctoqn - rtP . Relay1_OffVal ; } else { _rtZCSV ->
mag3ujlaw0 = rtB . jzkj5ctoqn - rtP . Relay1_OnVal ; } _rtZCSV -> eowuh1hss2
= rtB . iinqiuxn3i ; if ( rtDW . mv3mphax4f ) { _rtZCSV -> jolmx4ixju = rtB .
aiuwtukjl2 - rtP . Relay2_OffVal ; } else { _rtZCSV -> jolmx4ixju = rtB .
aiuwtukjl2 - rtP . Relay2_OnVal ; } _rtZCSV -> ox5rpwyxco = rtB . jzm0xgagji
- rtB . iwb3403aih ; _rtZCSV -> l0g3le5jog = rtB . k2xcyxwsbw - rtP .
Saturation_UpperSat_ehbc0hou2u ; _rtZCSV -> frmdrgx4zt = rtB . k2xcyxwsbw -
rtP . Saturation_LowerSat_e2gfsq1ep3 ; _rtZCSV -> lsktlgrwa4 = rtB .
did2wrnqd3 - rtP . Saturation1_UpperSat_haikx2purp ; _rtZCSV -> bkushmsqu4 =
rtB . did2wrnqd3 - rtP . Saturation1_LowerSat_ja3qpjhkdu ; if ( ( rtP .
Constant2_Value_c3vhbw33ec != rtP . Constant2_Value_c3vhbw33ec ) || ( rtB .
k5zbpv0nhl > rtP . Constant2_Value_c3vhbw33ec ) ) { if ( rtDW . jbxbvwznkw ==
0 ) { _rtZCSV -> azbolayp2y = rtB . k5zbpv0nhl - rtB . k5zbpv0nhl ; } else {
_rtZCSV -> azbolayp2y = rtB . k5zbpv0nhl - rtP . Constant2_Value_c3vhbw33ec ;
} } else if ( rtDW . jbxbvwznkw == 0 ) { _rtZCSV -> azbolayp2y = rtP .
Constant2_Value_c3vhbw33ec - rtB . k5zbpv0nhl ; } else { _rtZCSV ->
azbolayp2y = rtP . Constant2_Value_c3vhbw33ec - rtP .
Constant2_Value_c3vhbw33ec ; } if ( ( rtP . Constant_Value_dwh2dts0z5 != rtP
. Constant_Value_dwh2dts0z5 ) || ( rtB . os3kqcyax0 < rtP .
Constant_Value_dwh2dts0z5 ) ) { if ( rtDW . ofeqpav0z1 == 0 ) { _rtZCSV ->
lrm3laizhh = rtB . os3kqcyax0 - rtB . os3kqcyax0 ; } else { _rtZCSV ->
lrm3laizhh = rtB . os3kqcyax0 - rtP . Constant_Value_dwh2dts0z5 ; } } else if
( rtDW . ofeqpav0z1 == 0 ) { _rtZCSV -> lrm3laizhh = rtP .
Constant_Value_dwh2dts0z5 - rtB . os3kqcyax0 ; } else { _rtZCSV -> lrm3laizhh
= rtP . Constant_Value_dwh2dts0z5 - rtP . Constant_Value_dwh2dts0z5 ; } if (
( rtP . Constant_Value_pi0lofejm1 != rtP . Constant_Value_pi0lofejm1 ) || (
rtB . denq2sx3ui > rtP . Constant_Value_pi0lofejm1 ) ) { if ( rtDW .
f2rh3pjcf4 == 0 ) { _rtZCSV -> h1ma3waard = rtB . denq2sx3ui - rtB .
denq2sx3ui ; } else { _rtZCSV -> h1ma3waard = rtB . denq2sx3ui - rtP .
Constant_Value_pi0lofejm1 ; } } else if ( rtDW . f2rh3pjcf4 == 0 ) { _rtZCSV
-> h1ma3waard = rtP . Constant_Value_pi0lofejm1 - rtB . denq2sx3ui ; } else {
_rtZCSV -> h1ma3waard = rtP . Constant_Value_pi0lofejm1 - rtP .
Constant_Value_pi0lofejm1 ; } if ( ( rtP . Constant1_Value_cjbf34ugrc != rtP
. Constant1_Value_cjbf34ugrc ) || ( rtB . fgov33fphh > rtP .
Constant1_Value_cjbf34ugrc ) ) { if ( rtDW . czpni4mnff == 0 ) { _rtZCSV ->
hp0dszoqof = rtB . fgov33fphh - rtB . fgov33fphh ; } else { _rtZCSV ->
hp0dszoqof = rtB . fgov33fphh - rtP . Constant1_Value_cjbf34ugrc ; } } else
if ( rtDW . czpni4mnff == 0 ) { _rtZCSV -> hp0dszoqof = rtP .
Constant1_Value_cjbf34ugrc - rtB . fgov33fphh ; } else { _rtZCSV ->
hp0dszoqof = rtP . Constant1_Value_cjbf34ugrc - rtP .
Constant1_Value_cjbf34ugrc ; } switch ( rtDW . edzwglzc12 ) { case 1 :
_rtZCSV -> oqm0wqx0fh = 0.0 ; _rtZCSV -> daocbbswlk = rtP .
IntegratorX_Oem_UpperSat - rtP . IntegratorX_Oem_LowerSat ; break ; case 2 :
_rtZCSV -> oqm0wqx0fh = rtP . IntegratorX_Oem_LowerSat - rtP .
IntegratorX_Oem_UpperSat ; _rtZCSV -> daocbbswlk = 0.0 ; break ; default :
_rtZCSV -> oqm0wqx0fh = rtX . fteoprdfjw - rtP . IntegratorX_Oem_UpperSat ;
_rtZCSV -> daocbbswlk = rtX . fteoprdfjw - rtP . IntegratorX_Oem_LowerSat ;
break ; } if ( ( rtDW . edzwglzc12 == 3 ) || ( rtDW . edzwglzc12 == 4 ) ) {
_rtZCSV -> oh2odqlmhf = rtB . j2u4yltrpp ; } else { _rtZCSV -> oh2odqlmhf =
0.0 ; } if ( ( rtP . Constant1_Value_fe1czv4ovb != rtP .
Constant1_Value_fe1czv4ovb ) || ( rtB . bvz3zvgshe < rtP .
Constant1_Value_fe1czv4ovb ) ) { if ( rtDW . kcrt4gkpma == 0 ) { _rtZCSV ->
pn0xl2qz2l = rtB . bvz3zvgshe - rtB . bvz3zvgshe ; } else { _rtZCSV ->
pn0xl2qz2l = rtB . bvz3zvgshe - rtP . Constant1_Value_fe1czv4ovb ; } } else
if ( rtDW . kcrt4gkpma == 0 ) { _rtZCSV -> pn0xl2qz2l = rtP .
Constant1_Value_fe1czv4ovb - rtB . bvz3zvgshe ; } else { _rtZCSV ->
pn0xl2qz2l = rtP . Constant1_Value_fe1czv4ovb - rtP .
Constant1_Value_fe1czv4ovb ; } if ( ( rtP . Constant2_Value_imre1apqn2 != rtP
. Constant2_Value_imre1apqn2 ) || ( rtB . hrhovrq2gk > rtP .
Constant2_Value_imre1apqn2 ) ) { if ( rtDW . gdkaitdhn2 == 0 ) { _rtZCSV ->
ieehakhyry = rtB . hrhovrq2gk - rtB . hrhovrq2gk ; } else { _rtZCSV ->
ieehakhyry = rtB . hrhovrq2gk - rtP . Constant2_Value_imre1apqn2 ; } } else
if ( rtDW . gdkaitdhn2 == 0 ) { _rtZCSV -> ieehakhyry = rtP .
Constant2_Value_imre1apqn2 - rtB . hrhovrq2gk ; } else { _rtZCSV ->
ieehakhyry = rtP . Constant2_Value_imre1apqn2 - rtP .
Constant2_Value_imre1apqn2 ; } if ( ( rtB . c0cwgduetq != rtB . c0cwgduetq )
|| ( rtP . Constant_Value_ajsql1lpqg > rtB . c0cwgduetq ) ) { if ( rtDW .
j4aiaaqlli == 0 ) { _rtZCSV -> f3wc1505sm = rtP . Constant_Value_ajsql1lpqg -
rtP . Constant_Value_ajsql1lpqg ; } else { _rtZCSV -> f3wc1505sm = rtP .
Constant_Value_ajsql1lpqg - rtB . c0cwgduetq ; } } else if ( rtDW .
j4aiaaqlli == 0 ) { _rtZCSV -> f3wc1505sm = rtB . c0cwgduetq - rtP .
Constant_Value_ajsql1lpqg ; } else { _rtZCSV -> f3wc1505sm = rtB . c0cwgduetq
- rtB . c0cwgduetq ; } _rtZCSV -> ebzwzq5ona = rtB . npvqij5mhv - rtP . model
. engine . w_tlin ; _rtZCSV -> inijbjlsfi = rtB . cyuyr3knsa - 2.0 * rtP .
model . engine . BSR_opt ; _rtZCSV -> e5dtngaiji = rtB . cyuyr3knsa - rtP .
Saturation_LowerSat_kzgxh2ssqh ; _rtZCSV -> cpjm0zpnk1 = rtB . b1uoph40ee -
rtP . Saturation1_UpperSat_pjh2z4fnof ; _rtZCSV -> ld5xmcvr3e = rtB .
b1uoph40ee - rtP . Saturation1_LowerSat_o3inkji2se ; _rtZCSV -> dlmfqjncno =
rtB . pd4h1x0zka - rtP . road . x_distanceVector [ 9904 ] ; } void
MdlTerminate ( void ) { char_T * sErr ; sErr = GetErrorBuffer ( & rtDW .
lgjsvdiy5a [ 0U ] ) ; LibTerminate ( & rtDW . lgjsvdiy5a [ 0U ] ) ; if ( *
sErr != 0 ) { ssSetErrorStatus ( rtS , sErr ) ; ssSetStopRequested ( rtS , 1
) ; } LibDestroy ( & rtDW . lgjsvdiy5a [ 0U ] , 0 ) ; DestroyHostLibrary ( &
rtDW . lgjsvdiy5a [ 0U ] ) ; {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . ft5nitf1xd . CTLHandle != NULL ) { CTL_ReleaseHandle ( rtDW .
ft5nitf1xd . CTLHandle ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . pegf1lgc5k . CTLHandle != NULL ) { CTL_ReleaseHandle ( rtDW .
pegf1lgc5k . CTLHandle ) ; } } } sErr = GetErrorBuffer ( & rtDW . ozecqffs1t
[ 0U ] ) ; LibTerminate ( & rtDW . ozecqffs1t [ 0U ] ) ; if ( * sErr != 0 ) {
ssSetErrorStatus ( rtS , sErr ) ; ssSetStopRequested ( rtS , 1 ) ; }
LibDestroy ( & rtDW . ozecqffs1t [ 0U ] , 0 ) ; DestroyHostLibrary ( & rtDW .
ozecqffs1t [ 0U ] ) ; {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . jpjfz2svcl . CONFIGHANDLE != NULL ) { J1939ReleaseHandle ( (
HCONFIG ) rtDW . jpjfz2svcl . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . kbixsgmskc . CONFIGHANDLE != NULL ) { J1939ReleaseHandle ( (
HCONFIG ) rtDW . kbixsgmskc . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . maxcur2n31 . CONFIGHANDLE != NULL ) { J1939ReleaseHandle ( (
HCONFIG ) rtDW . maxcur2n31 . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . alvst5aflb . CONFIGHANDLE != NULL ) { J1939ReleaseHandle ( (
HCONFIG ) rtDW . alvst5aflb . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . iuixpdicwr . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . iuixpdicwr . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . iuixpdicwr . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . kzspl1dppk . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . kzspl1dppk . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . kzspl1dppk . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . k2kbed5e0t . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . k2kbed5e0t . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . k2kbed5e0t . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . osuhy0wf15 . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . osuhy0wf15 . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . osuhy0wf15 . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . clkxcrhgir . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . clkxcrhgir . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . clkxcrhgir . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . e3hhsxef2w . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . e3hhsxef2w . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . e3hhsxef2w . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . of3rn5nxd4 . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . of3rn5nxd4 . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . of3rn5nxd4 . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . bvdrbi2l1c . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . bvdrbi2l1c . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . bvdrbi2l1c . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . e3ktwiowkd . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . e3ktwiowkd . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . e3ktwiowkd . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . d4x2b0bhgu . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . d4x2b0bhgu . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . d4x2b0bhgu . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . krc0v3lfqy . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . krc0v3lfqy . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . krc0v3lfqy . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . kr1tkdktl0 . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . kr1tkdktl0 . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . kr1tkdktl0 . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . imsyrbpl23 . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . imsyrbpl23 . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . imsyrbpl23 . CONFIGHANDLE ) ; } } } {
#if defined(XPCMSVISUALC) && !defined(MATLAB_MEX_FILE)
if ( ! xpcIsModelInit ( ) )
#endif
{ if ( rtDW . ekxqe2lb2z . CONFIGHANDLE != NULL ) { J1939DestroyPG ( (
PgnEntry_T * ) rtDW . ekxqe2lb2z . PGPTR ) ; J1939ReleaseHandle ( ( HCONFIG )
rtDW . ekxqe2lb2z . CONFIGHANDLE ) ; } } } rt_TDelayFreeBuf ( rtDW .
k4tau4hadb . TUbufferPtrs [ 0 ] ) ; rt_TDelayFreeBuf ( rtDW . hku5cqszwy .
TUbufferPtrs [ 0 ] ) ; { if ( rtDW . gtasy1jsdx . AQHandles ) {
sdiTerminateStreaming ( & rtDW . gtasy1jsdx . AQHandles ) ; } } { if ( rtDW .
p4sflk0g2w . AQHandles ) { sdiTerminateStreaming ( & rtDW . p4sflk0g2w .
AQHandles ) ; } } { if ( rtDW . ofz4kqfoe0 . AQHandles ) {
sdiTerminateStreaming ( & rtDW . ofz4kqfoe0 . AQHandles ) ; } } { if ( rtDW .
p33krp3hyb . AQHandles ) { sdiTerminateStreaming ( & rtDW . p33krp3hyb .
AQHandles ) ; } } { if ( rtDW . dzibnwkozv . AQHandles ) {
sdiTerminateStreaming ( & rtDW . dzibnwkozv . AQHandles ) ; } } { if ( rtDW .
m2ysthz4lp . AQHandles ) { sdiTerminateStreaming ( & rtDW . m2ysthz4lp .
AQHandles ) ; } } { if ( rtDW . ltc2bikvjk . AQHandles ) {
sdiTerminateStreaming ( & rtDW . ltc2bikvjk . AQHandles ) ; } } { if ( rtDW .
fwhtblllbe . AQHandles ) { sdiTerminateStreaming ( & rtDW . fwhtblllbe .
AQHandles ) ; } } { if ( rtDW . kyvzs2v1y5 . AQHandles ) {
sdiTerminateStreaming ( & rtDW . kyvzs2v1y5 . AQHandles ) ; } } { if ( rtDW .
a5wlo524la . AQHandles ) { sdiTerminateStreaming ( & rtDW . a5wlo524la .
AQHandles ) ; } } { if ( rtDW . osoqnotoxt . AQHandles ) {
sdiTerminateStreaming ( & rtDW . osoqnotoxt . AQHandles ) ; } } { if ( rtDW .
afai5j1n5f . AQHandles ) { sdiTerminateStreaming ( & rtDW . afai5j1n5f .
AQHandles ) ; } } { if ( rtDW . gtasy1jsdxk . AQHandles ) {
sdiTerminateStreaming ( & rtDW . gtasy1jsdxk . AQHandles ) ; } } { if ( rtDW
. jtwmyt455q . AQHandles ) { sdiTerminateStreaming ( & rtDW . jtwmyt455q .
AQHandles ) ; } } { if ( rtDW . o0cbjrpiwk . AQHandles ) {
sdiTerminateStreaming ( & rtDW . o0cbjrpiwk . AQHandles ) ; } } { if ( rtDW .
dakk2fhtjk . AQHandles ) { sdiTerminateStreaming ( & rtDW . dakk2fhtjk .
AQHandles ) ; } } { if ( rtDW . bzrmj3zxqu . AQHandles ) {
sdiTerminateStreaming ( & rtDW . bzrmj3zxqu . AQHandles ) ; } } { if ( rtDW .
pudhr5q1sv . AQHandles ) { sdiTerminateStreaming ( & rtDW . pudhr5q1sv .
AQHandles ) ; } } { if ( rtDW . ahb0xajdg5 . AQHandles ) {
sdiTerminateStreaming ( & rtDW . ahb0xajdg5 . AQHandles ) ; } } { if ( rtDW .
jj02cyrtix . AQHandles ) { sdiTerminateStreaming ( & rtDW . jj02cyrtix .
AQHandles ) ; } } { if ( rtDW . mduldnxlmb . AQHandles ) {
sdiTerminateStreaming ( & rtDW . mduldnxlmb . AQHandles ) ; } } { if ( rtDW .
o2domeg4ik . AQHandles ) { sdiTerminateStreaming ( & rtDW . o2domeg4ik .
AQHandles ) ; } } { if ( rtDW . gtasy1jsdxk2 . AQHandles ) {
sdiTerminateStreaming ( & rtDW . gtasy1jsdxk2 . AQHandles ) ; } } { if ( rtDW
. mhg3ukoydp . AQHandles ) { sdiTerminateStreaming ( & rtDW . mhg3ukoydp .
AQHandles ) ; } } { if ( rtDW . kqufha1qme . AQHandles ) {
sdiTerminateStreaming ( & rtDW . kqufha1qme . AQHandles ) ; } } { if ( rtDW .
ck00fvktvl . AQHandles ) { sdiTerminateStreaming ( & rtDW . ck00fvktvl .
AQHandles ) ; } } { if ( rtDW . fsc12ul0nq . AQHandles ) {
sdiTerminateStreaming ( & rtDW . fsc12ul0nq . AQHandles ) ; } } { if ( rtDW .
jk5klgbkjx . AQHandles ) { sdiTerminateStreaming ( & rtDW . jk5klgbkjx .
AQHandles ) ; } } { if ( rtDW . bgmhbb2ggj . AQHandles ) {
sdiTerminateStreaming ( & rtDW . bgmhbb2ggj . AQHandles ) ; } } { if ( rtDW .
jfed40pyro . AQHandles ) { sdiTerminateStreaming ( & rtDW . jfed40pyro .
AQHandles ) ; } } { if ( rtDW . mgmkqdnd4h . AQHandles ) {
sdiTerminateStreaming ( & rtDW . mgmkqdnd4h . AQHandles ) ; } } { if ( rtDW .
cqmz0ka510 . AQHandles ) { sdiTerminateStreaming ( & rtDW . cqmz0ka510 .
AQHandles ) ; } } { if ( rtDW . awm3x1p030 . AQHandles ) {
sdiTerminateStreaming ( & rtDW . awm3x1p030 . AQHandles ) ; } } { if ( rtDW .
pz3v3lsswe . AQHandles ) { sdiTerminateStreaming ( & rtDW . pz3v3lsswe .
AQHandles ) ; } } { if ( rtDW . nji534mx2v . AQHandles ) {
sdiTerminateStreaming ( & rtDW . nji534mx2v . AQHandles ) ; } } { if ( rtDW .
kn50mamzgm . AQHandles ) { sdiTerminateStreaming ( & rtDW . kn50mamzgm .
AQHandles ) ; } } { if ( rtDW . lz2njt4sro . AQHandles ) {
sdiTerminateStreaming ( & rtDW . lz2njt4sro . AQHandles ) ; } } { if ( rtDW .
hw0crwwhgx . AQHandles ) { sdiTerminateStreaming ( & rtDW . hw0crwwhgx .
AQHandles ) ; } } { if ( rtDW . odefyqi2dd . AQHandles ) {
sdiTerminateStreaming ( & rtDW . odefyqi2dd . AQHandles ) ; } } { if ( rtDW .
jwv41mpadj . AQHandles ) { sdiTerminateStreaming ( & rtDW . jwv41mpadj .
AQHandles ) ; } } { if ( rtDW . mtia2gm3mn . AQHandles ) {
sdiTerminateStreaming ( & rtDW . mtia2gm3mn . AQHandles ) ; } } { if ( rtDW .
acteg3xdu0 . AQHandles ) { sdiTerminateStreaming ( & rtDW . acteg3xdu0 .
AQHandles ) ; } } { if ( rtDW . dd50e1xu1m . AQHandles ) {
sdiTerminateStreaming ( & rtDW . dd50e1xu1m . AQHandles ) ; } } { if ( rtDW .
phol22yedf . AQHandles ) { sdiTerminateStreaming ( & rtDW . phol22yedf .
AQHandles ) ; } } { if ( rtDW . pieup45y1d . AQHandles ) {
sdiTerminateStreaming ( & rtDW . pieup45y1d . AQHandles ) ; } } { if ( rtDW .
n4ipdfmwpg . AQHandles ) { sdiTerminateStreaming ( & rtDW . n4ipdfmwpg .
AQHandles ) ; } } { if ( rtDW . pp33uvzuj4 . AQHandles ) {
sdiTerminateStreaming ( & rtDW . pp33uvzuj4 . AQHandles ) ; } } } static void
mr_TruckBenchmark_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int
j , const void * srcData , size_t numBytes ) ; static void
mr_TruckBenchmark_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int
j , const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_TruckBenchmark_restoreDataFromMxArray ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static
void mr_TruckBenchmark_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_TruckBenchmark_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) ; static void
mr_TruckBenchmark_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i ,
int j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j ,
mxCreateDoubleScalar ( ( real_T ) bitVal ) ) ; } static uint_T
mr_TruckBenchmark_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) ; static uint_T
mr_TruckBenchmark_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T )
mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( (
1u << numBits ) - 1u ) ; } static void
mr_TruckBenchmark_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
; static void mr_TruckBenchmark_cacheDataToMxArrayWithOffset ( mxArray *
destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_TruckBenchmark_restoreDataFromMxArrayWithOffset ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) ; static void mr_TruckBenchmark_restoreDataFromMxArrayWithOffset (
void * destData , const mxArray * srcArray , mwIndex i , int j , mwIndex
offset , size_t numBytes ) { const uint8_T * varData = ( const uint8_T * )
mxGetData ( mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T *
) destData , ( const uint8_T * ) & varData [ offset * numBytes ] , numBytes )
; } static void mr_TruckBenchmark_cacheBitFieldToCellArrayWithOffset (
mxArray * destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal )
; static void mr_TruckBenchmark_cacheBitFieldToCellArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , uint_T fieldVal ) {
mxSetCell ( mxGetFieldByNumber ( destArray , i , j ) , offset ,
mxCreateDoubleScalar ( ( real_T ) fieldVal ) ) ; } static uint_T
mr_TruckBenchmark_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_TruckBenchmark_extractBitFieldFromCellArrayWithOffset ( const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) {
const uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell (
mxGetFieldByNumber ( srcArray , i , j ) , offset ) ) ; return fieldVal & ( (
1u << numBits ) - 1u ) ; } mxArray * mr_TruckBenchmark_GetDWork ( ) { static
const char_T * ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "NULL_PrevZCX" , } ;
mxArray * ssDW = mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & (
rtB ) , sizeof ( rtB ) ) ; { static const char_T * rtdwDataFieldNames [ 119 ]
= { "rtDW.kpmtixcj35" , "rtDW.mluvktfvfy" , "rtDW.jtxmye3nth" ,
"rtDW.mp0kaoewzv" , "rtDW.l2wwwtxl4l" , "rtDW.ox1qbuvuuc" , "rtDW.bffjy4cqw3"
, "rtDW.omie0z5rtl" , "rtDW.ltzscgd5af" , "rtDW.iazakfnige" ,
"rtDW.b1sjehltlg" , "rtDW.hmg2uwdzcg" , "rtDW.jahel4guj4" , "rtDW.c1a2ddum24"
, "rtDW.h1t2m1slzp" , "rtDW.jescywanqo" , "rtDW.n3jvfqlh1d" ,
"rtDW.jie24f0s0n" , "rtDW.od5y3smrxh" , "rtDW.bzxfv0jxlh" , "rtDW.ozxovagibo"
, "rtDW.o0eadiapoc" , "rtDW.lgjsvdiy5a" , "rtDW.ozecqffs1t" ,
"rtDW.ki10t4re5z" , "rtDW.kgxadfuhgr" , "rtDW.ldxvb4zcz0" , "rtDW.imduqxhj3y"
, "rtDW.h0ytymzc2i" , "rtDW.ndy1r3lteo" , "rtDW.ono0qix5io" ,
"rtDW.bih1twzowf" , "rtDW.evb2jcnsmb" , "rtDW.jcb0vgamw2" , "rtDW.g1tih4iurb"
, "rtDW.gk4tvjl5km" , "rtDW.jqdnga4d0r" , "rtDW.khs2ujrsdq" ,
"rtDW.hoc4ujevyd" , "rtDW.pqjv5ubgvq" , "rtDW.dzwszeq5uo" , "rtDW.lru3e1mvrz"
, "rtDW.luuegejdc0" , "rtDW.nva3c2aiue" , "rtDW.p1lgfwsxn3" ,
"rtDW.ozura1lel3" , "rtDW.cn5pwf5utq" , "rtDW.c1d5q3vumy" , "rtDW.flfjax3w0e"
, "rtDW.gluwhgdkil" , "rtDW.onwpqbmdms" , "rtDW.n0wxb1xzlc" ,
"rtDW.mf4tzazbhp" , "rtDW.pszwtqz0gn" , "rtDW.dhwxr34two" , "rtDW.bcl2uuqmhl"
, "rtDW.nxjlr5banb" , "rtDW.ja1c4asgaz" , "rtDW.btigisbrqf" ,
"rtDW.ckyfoeqie5" , "rtDW.ixaqaxatlt" , "rtDW.fshou35ift" , "rtDW.cflc32uwnd"
, "rtDW.oqko4zquza" , "rtDW.h3mr0riybw" , "rtDW.pfmhktgqz5" ,
"rtDW.mquiy4fzeb" , "rtDW.omeqzycfh2" , "rtDW.imt2dcvft2" , "rtDW.cwyukvwtwb"
, "rtDW.ipcifxvj5x" , "rtDW.c2dyuklr3i" , "rtDW.p40fsqbchl" ,
"rtDW.l4mfodlgua" , "rtDW.kf0zhsqe1e" , "rtDW.ie2rbfy2dj" , "rtDW.bi3ryeji3q"
, "rtDW.gexhlxucmx" , "rtDW.bzymrve3xd" , "rtDW.cjg2lxwx3p" ,
"rtDW.jbxbvwznkw" , "rtDW.ofeqpav0z1" , "rtDW.f2rh3pjcf4" , "rtDW.czpni4mnff"
, "rtDW.edzwglzc12" , "rtDW.kcrt4gkpma" , "rtDW.gdkaitdhn2" ,
"rtDW.j4aiaaqlli" , "rtDW.jw31kvp3ln" , "rtDW.aetkdo2sks" , "rtDW.dbfmnhxbxj"
, "rtDW.p1nnlsrxke" , "rtDW.bfmr5zictt" , "rtDW.nhh3pckv2z" ,
"rtDW.pu1q4zlmwb" , "rtDW.pe5pl50ynw" , "rtDW.eda54vucfl" , "rtDW.mnycq5gn5i"
, "rtDW.e4lgtlqce2" , "rtDW.hpyvhbyyfk" , "rtDW.mv3mphax4f" ,
"rtDW.dyrzzohb5s" , "rtDW.apmlxbmuwh" , "rtDW.ogaaumd32e" , "rtDW.gvkgxqsg5w"
, "rtDW.ksp31oyn4z" , "rtDW.gwi2bo5yvs" , "rtDW.dedzusgrw0" ,
"rtDW.dqrx4b5l1l" , "rtDW.ei55bolyl0" , "rtDW.frdq0ezqxz" , "rtDW.hc5kmkcx43"
, "rtDW.bp0lxwi25f" , "rtDW.nd3tkuvjly" , "rtDW.adrllpi2ax" ,
"rtDW.cqvouu2ka3" , "rtDW.j4h3zrlxtn" , "rtDW.asj3qcjbaz" , "rtDW.ok1wan2u4e"
, } ; mxArray * rtdwData = mxCreateStructMatrix ( 1 , 1 , 119 ,
rtdwDataFieldNames ) ; mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 ,
0 , ( const void * ) & ( rtDW . kpmtixcj35 ) , sizeof ( rtDW . kpmtixcj35 ) )
; mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * )
& ( rtDW . mluvktfvfy ) , sizeof ( rtDW . mluvktfvfy ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) &
( rtDW . jtxmye3nth ) , sizeof ( rtDW . jtxmye3nth ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) &
( rtDW . mp0kaoewzv ) , sizeof ( rtDW . mp0kaoewzv ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) &
( rtDW . l2wwwtxl4l ) , sizeof ( rtDW . l2wwwtxl4l ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) &
( rtDW . ox1qbuvuuc ) , sizeof ( rtDW . ox1qbuvuuc ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) &
( rtDW . bffjy4cqw3 ) , sizeof ( rtDW . bffjy4cqw3 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) &
( rtDW . omie0z5rtl ) , sizeof ( rtDW . omie0z5rtl ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) &
( rtDW . ltzscgd5af ) , sizeof ( rtDW . ltzscgd5af ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) &
( rtDW . iazakfnige ) , sizeof ( rtDW . iazakfnige ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) &
( rtDW . b1sjehltlg ) , sizeof ( rtDW . b1sjehltlg ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const void * ) &
( rtDW . hmg2uwdzcg ) , sizeof ( rtDW . hmg2uwdzcg ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const void * ) &
( rtDW . jahel4guj4 ) , sizeof ( rtDW . jahel4guj4 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const void * ) &
( rtDW . c1a2ddum24 ) , sizeof ( rtDW . c1a2ddum24 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 14 , ( const void * ) &
( rtDW . h1t2m1slzp ) , sizeof ( rtDW . h1t2m1slzp ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 15 , ( const void * ) &
( rtDW . jescywanqo ) , sizeof ( rtDW . jescywanqo ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 16 , ( const void * ) &
( rtDW . n3jvfqlh1d ) , sizeof ( rtDW . n3jvfqlh1d ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 17 , ( const void * ) &
( rtDW . jie24f0s0n ) , sizeof ( rtDW . jie24f0s0n ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 18 , ( const void * ) &
( rtDW . od5y3smrxh ) , sizeof ( rtDW . od5y3smrxh ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 19 , ( const void * ) &
( rtDW . bzxfv0jxlh ) , sizeof ( rtDW . bzxfv0jxlh ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 20 , ( const void * ) &
( rtDW . ozxovagibo ) , sizeof ( rtDW . ozxovagibo ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 21 , ( const void * ) &
( rtDW . o0eadiapoc ) , sizeof ( rtDW . o0eadiapoc ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 22 , ( const void * ) &
( rtDW . lgjsvdiy5a ) , sizeof ( rtDW . lgjsvdiy5a ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 23 , ( const void * ) &
( rtDW . ozecqffs1t ) , sizeof ( rtDW . ozecqffs1t ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 24 , ( const void * ) &
( rtDW . ki10t4re5z ) , sizeof ( rtDW . ki10t4re5z ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 25 , ( const void * ) &
( rtDW . kgxadfuhgr ) , sizeof ( rtDW . kgxadfuhgr ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 26 , ( const void * ) &
( rtDW . ldxvb4zcz0 ) , sizeof ( rtDW . ldxvb4zcz0 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 27 , ( const void * ) &
( rtDW . imduqxhj3y ) , sizeof ( rtDW . imduqxhj3y ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 28 , ( const void * ) &
( rtDW . h0ytymzc2i ) , sizeof ( rtDW . h0ytymzc2i ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 29 , ( const void * ) &
( rtDW . ndy1r3lteo ) , sizeof ( rtDW . ndy1r3lteo ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 30 , ( const void * ) &
( rtDW . ono0qix5io ) , sizeof ( rtDW . ono0qix5io ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 31 , ( const void * ) &
( rtDW . bih1twzowf ) , sizeof ( rtDW . bih1twzowf ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 32 , ( const void * ) &
( rtDW . evb2jcnsmb ) , sizeof ( rtDW . evb2jcnsmb ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 33 , ( const void * ) &
( rtDW . jcb0vgamw2 ) , sizeof ( rtDW . jcb0vgamw2 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 34 , ( const void * ) &
( rtDW . g1tih4iurb ) , sizeof ( rtDW . g1tih4iurb ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 35 , ( const void * ) &
( rtDW . gk4tvjl5km ) , sizeof ( rtDW . gk4tvjl5km ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 36 , ( const void * ) &
( rtDW . jqdnga4d0r ) , sizeof ( rtDW . jqdnga4d0r ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 37 , ( const void * ) &
( rtDW . khs2ujrsdq ) , sizeof ( rtDW . khs2ujrsdq ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 38 , ( const void * ) &
( rtDW . hoc4ujevyd ) , sizeof ( rtDW . hoc4ujevyd ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 39 , ( const void * ) &
( rtDW . pqjv5ubgvq ) , sizeof ( rtDW . pqjv5ubgvq ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 40 , ( const void * ) &
( rtDW . dzwszeq5uo ) , sizeof ( rtDW . dzwszeq5uo ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 41 , ( const void * ) &
( rtDW . lru3e1mvrz ) , sizeof ( rtDW . lru3e1mvrz ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 42 , ( const void * ) &
( rtDW . luuegejdc0 ) , sizeof ( rtDW . luuegejdc0 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 43 , ( const void * ) &
( rtDW . nva3c2aiue ) , sizeof ( rtDW . nva3c2aiue ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 44 , ( const void * ) &
( rtDW . p1lgfwsxn3 ) , sizeof ( rtDW . p1lgfwsxn3 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 45 , ( const void * ) &
( rtDW . ozura1lel3 ) , sizeof ( rtDW . ozura1lel3 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 46 , ( const void * ) &
( rtDW . cn5pwf5utq ) , sizeof ( rtDW . cn5pwf5utq ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 47 , ( const void * ) &
( rtDW . c1d5q3vumy ) , sizeof ( rtDW . c1d5q3vumy ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 48 , ( const void * ) &
( rtDW . flfjax3w0e ) , sizeof ( rtDW . flfjax3w0e ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 49 , ( const void * ) &
( rtDW . gluwhgdkil ) , sizeof ( rtDW . gluwhgdkil ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 50 , ( const void * ) &
( rtDW . onwpqbmdms ) , sizeof ( rtDW . onwpqbmdms ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 51 , ( const void * ) &
( rtDW . n0wxb1xzlc ) , sizeof ( rtDW . n0wxb1xzlc ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 52 , ( const void * ) &
( rtDW . mf4tzazbhp ) , sizeof ( rtDW . mf4tzazbhp ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 53 , ( const void * ) &
( rtDW . pszwtqz0gn ) , sizeof ( rtDW . pszwtqz0gn ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 54 , ( const void * ) &
( rtDW . dhwxr34two ) , sizeof ( rtDW . dhwxr34two ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 55 , ( const void * ) &
( rtDW . bcl2uuqmhl ) , sizeof ( rtDW . bcl2uuqmhl ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 56 , ( const void * ) &
( rtDW . nxjlr5banb ) , sizeof ( rtDW . nxjlr5banb ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 57 , ( const void * ) &
( rtDW . ja1c4asgaz ) , sizeof ( rtDW . ja1c4asgaz ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 58 , ( const void * ) &
( rtDW . btigisbrqf ) , sizeof ( rtDW . btigisbrqf ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 59 , ( const void * ) &
( rtDW . ckyfoeqie5 ) , sizeof ( rtDW . ckyfoeqie5 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 60 , ( const void * ) &
( rtDW . ixaqaxatlt ) , sizeof ( rtDW . ixaqaxatlt ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 61 , ( const void * ) &
( rtDW . fshou35ift ) , sizeof ( rtDW . fshou35ift ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 62 , ( const void * ) &
( rtDW . cflc32uwnd ) , sizeof ( rtDW . cflc32uwnd ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 63 , ( const void * ) &
( rtDW . oqko4zquza ) , sizeof ( rtDW . oqko4zquza ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 64 , ( const void * ) &
( rtDW . h3mr0riybw ) , sizeof ( rtDW . h3mr0riybw ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 65 , ( const void * ) &
( rtDW . pfmhktgqz5 ) , sizeof ( rtDW . pfmhktgqz5 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 66 , ( const void * ) &
( rtDW . mquiy4fzeb ) , sizeof ( rtDW . mquiy4fzeb ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 67 , ( const void * ) &
( rtDW . omeqzycfh2 ) , sizeof ( rtDW . omeqzycfh2 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 68 , ( const void * ) &
( rtDW . imt2dcvft2 ) , sizeof ( rtDW . imt2dcvft2 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 69 , ( const void * ) &
( rtDW . cwyukvwtwb ) , sizeof ( rtDW . cwyukvwtwb ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 70 , ( const void * ) &
( rtDW . ipcifxvj5x ) , sizeof ( rtDW . ipcifxvj5x ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 71 , ( const void * ) &
( rtDW . c2dyuklr3i ) , sizeof ( rtDW . c2dyuklr3i ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 72 , ( const void * ) &
( rtDW . p40fsqbchl ) , sizeof ( rtDW . p40fsqbchl ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 73 , ( const void * ) &
( rtDW . l4mfodlgua ) , sizeof ( rtDW . l4mfodlgua ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 74 , ( const void * ) &
( rtDW . kf0zhsqe1e ) , sizeof ( rtDW . kf0zhsqe1e ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 75 , ( const void * ) &
( rtDW . ie2rbfy2dj ) , sizeof ( rtDW . ie2rbfy2dj ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 76 , ( const void * ) &
( rtDW . bi3ryeji3q ) , sizeof ( rtDW . bi3ryeji3q ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 77 , ( const void * ) &
( rtDW . gexhlxucmx ) , sizeof ( rtDW . gexhlxucmx ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 78 , ( const void * ) &
( rtDW . bzymrve3xd ) , sizeof ( rtDW . bzymrve3xd ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 79 , ( const void * ) &
( rtDW . cjg2lxwx3p ) , sizeof ( rtDW . cjg2lxwx3p ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 80 , ( const void * ) &
( rtDW . jbxbvwznkw ) , sizeof ( rtDW . jbxbvwznkw ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 81 , ( const void * ) &
( rtDW . ofeqpav0z1 ) , sizeof ( rtDW . ofeqpav0z1 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 82 , ( const void * ) &
( rtDW . f2rh3pjcf4 ) , sizeof ( rtDW . f2rh3pjcf4 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 83 , ( const void * ) &
( rtDW . czpni4mnff ) , sizeof ( rtDW . czpni4mnff ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 84 , ( const void * ) &
( rtDW . edzwglzc12 ) , sizeof ( rtDW . edzwglzc12 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 85 , ( const void * ) &
( rtDW . kcrt4gkpma ) , sizeof ( rtDW . kcrt4gkpma ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 86 , ( const void * ) &
( rtDW . gdkaitdhn2 ) , sizeof ( rtDW . gdkaitdhn2 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 87 , ( const void * ) &
( rtDW . j4aiaaqlli ) , sizeof ( rtDW . j4aiaaqlli ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 88 , ( const void * ) &
( rtDW . jw31kvp3ln ) , sizeof ( rtDW . jw31kvp3ln ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 89 , ( const void * ) &
( rtDW . aetkdo2sks ) , sizeof ( rtDW . aetkdo2sks ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 90 , ( const void * ) &
( rtDW . dbfmnhxbxj ) , sizeof ( rtDW . dbfmnhxbxj ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 91 , ( const void * ) &
( rtDW . p1nnlsrxke ) , sizeof ( rtDW . p1nnlsrxke ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 92 , ( const void * ) &
( rtDW . bfmr5zictt ) , sizeof ( rtDW . bfmr5zictt ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 93 , ( const void * ) &
( rtDW . nhh3pckv2z ) , sizeof ( rtDW . nhh3pckv2z ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 94 , ( const void * ) &
( rtDW . pu1q4zlmwb ) , sizeof ( rtDW . pu1q4zlmwb ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 95 , ( const void * ) &
( rtDW . pe5pl50ynw ) , sizeof ( rtDW . pe5pl50ynw ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 96 , ( const void * ) &
( rtDW . eda54vucfl ) , sizeof ( rtDW . eda54vucfl ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 97 , ( const void * ) &
( rtDW . mnycq5gn5i ) , sizeof ( rtDW . mnycq5gn5i ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 98 , ( const void * ) &
( rtDW . e4lgtlqce2 ) , sizeof ( rtDW . e4lgtlqce2 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 99 , ( const void * ) &
( rtDW . hpyvhbyyfk ) , sizeof ( rtDW . hpyvhbyyfk ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 100 , ( const void * )
& ( rtDW . mv3mphax4f ) , sizeof ( rtDW . mv3mphax4f ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 101 , ( const void * )
& ( rtDW . dyrzzohb5s ) , sizeof ( rtDW . dyrzzohb5s ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 102 , ( const void * )
& ( rtDW . apmlxbmuwh ) , sizeof ( rtDW . apmlxbmuwh ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 103 , ( const void * )
& ( rtDW . ogaaumd32e ) , sizeof ( rtDW . ogaaumd32e ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 104 , ( const void * )
& ( rtDW . gvkgxqsg5w ) , sizeof ( rtDW . gvkgxqsg5w ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 105 , ( const void * )
& ( rtDW . ksp31oyn4z ) , sizeof ( rtDW . ksp31oyn4z ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 106 , ( const void * )
& ( rtDW . gwi2bo5yvs ) , sizeof ( rtDW . gwi2bo5yvs ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 107 , ( const void * )
& ( rtDW . dedzusgrw0 ) , sizeof ( rtDW . dedzusgrw0 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 108 , ( const void * )
& ( rtDW . dqrx4b5l1l ) , sizeof ( rtDW . dqrx4b5l1l ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 109 , ( const void * )
& ( rtDW . ei55bolyl0 ) , sizeof ( rtDW . ei55bolyl0 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 110 , ( const void * )
& ( rtDW . frdq0ezqxz ) , sizeof ( rtDW . frdq0ezqxz ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 111 , ( const void * )
& ( rtDW . hc5kmkcx43 ) , sizeof ( rtDW . hc5kmkcx43 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 112 , ( const void * )
& ( rtDW . bp0lxwi25f ) , sizeof ( rtDW . bp0lxwi25f ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 113 , ( const void * )
& ( rtDW . nd3tkuvjly ) , sizeof ( rtDW . nd3tkuvjly ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 114 , ( const void * )
& ( rtDW . adrllpi2ax ) , sizeof ( rtDW . adrllpi2ax ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 115 , ( const void * )
& ( rtDW . cqvouu2ka3 ) , sizeof ( rtDW . cqvouu2ka3 ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 116 , ( const void * )
& ( rtDW . j4h3zrlxtn ) , sizeof ( rtDW . j4h3zrlxtn ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 117 , ( const void * )
& ( rtDW . asj3qcjbaz ) , sizeof ( rtDW . asj3qcjbaz ) ) ;
mr_TruckBenchmark_cacheDataAsMxArray ( rtdwData , 0 , 118 , ( const void * )
& ( rtDW . ok1wan2u4e ) , sizeof ( rtDW . ok1wan2u4e ) ) ; mxSetFieldByNumber
( ssDW , 0 , 1 , rtdwData ) ; } return ssDW ; } void
mr_TruckBenchmark_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0 ,
0 , sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW
, 0 , 1 ) ; mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW .
kpmtixcj35 ) , rtdwData , 0 , 0 , sizeof ( rtDW . kpmtixcj35 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . mluvktfvfy )
, rtdwData , 0 , 1 , sizeof ( rtDW . mluvktfvfy ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jtxmye3nth )
, rtdwData , 0 , 2 , sizeof ( rtDW . jtxmye3nth ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . mp0kaoewzv )
, rtdwData , 0 , 3 , sizeof ( rtDW . mp0kaoewzv ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . l2wwwtxl4l )
, rtdwData , 0 , 4 , sizeof ( rtDW . l2wwwtxl4l ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ox1qbuvuuc )
, rtdwData , 0 , 5 , sizeof ( rtDW . ox1qbuvuuc ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bffjy4cqw3 )
, rtdwData , 0 , 6 , sizeof ( rtDW . bffjy4cqw3 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . omie0z5rtl )
, rtdwData , 0 , 7 , sizeof ( rtDW . omie0z5rtl ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ltzscgd5af )
, rtdwData , 0 , 8 , sizeof ( rtDW . ltzscgd5af ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . iazakfnige )
, rtdwData , 0 , 9 , sizeof ( rtDW . iazakfnige ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . b1sjehltlg )
, rtdwData , 0 , 10 , sizeof ( rtDW . b1sjehltlg ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . hmg2uwdzcg )
, rtdwData , 0 , 11 , sizeof ( rtDW . hmg2uwdzcg ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jahel4guj4 )
, rtdwData , 0 , 12 , sizeof ( rtDW . jahel4guj4 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . c1a2ddum24 )
, rtdwData , 0 , 13 , sizeof ( rtDW . c1a2ddum24 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . h1t2m1slzp )
, rtdwData , 0 , 14 , sizeof ( rtDW . h1t2m1slzp ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jescywanqo )
, rtdwData , 0 , 15 , sizeof ( rtDW . jescywanqo ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . n3jvfqlh1d )
, rtdwData , 0 , 16 , sizeof ( rtDW . n3jvfqlh1d ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jie24f0s0n )
, rtdwData , 0 , 17 , sizeof ( rtDW . jie24f0s0n ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . od5y3smrxh )
, rtdwData , 0 , 18 , sizeof ( rtDW . od5y3smrxh ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bzxfv0jxlh )
, rtdwData , 0 , 19 , sizeof ( rtDW . bzxfv0jxlh ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ozxovagibo )
, rtdwData , 0 , 20 , sizeof ( rtDW . ozxovagibo ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . o0eadiapoc )
, rtdwData , 0 , 21 , sizeof ( rtDW . o0eadiapoc ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . lgjsvdiy5a )
, rtdwData , 0 , 22 , sizeof ( rtDW . lgjsvdiy5a ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ozecqffs1t )
, rtdwData , 0 , 23 , sizeof ( rtDW . ozecqffs1t ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ki10t4re5z )
, rtdwData , 0 , 24 , sizeof ( rtDW . ki10t4re5z ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . kgxadfuhgr )
, rtdwData , 0 , 25 , sizeof ( rtDW . kgxadfuhgr ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ldxvb4zcz0 )
, rtdwData , 0 , 26 , sizeof ( rtDW . ldxvb4zcz0 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . imduqxhj3y )
, rtdwData , 0 , 27 , sizeof ( rtDW . imduqxhj3y ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . h0ytymzc2i )
, rtdwData , 0 , 28 , sizeof ( rtDW . h0ytymzc2i ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ndy1r3lteo )
, rtdwData , 0 , 29 , sizeof ( rtDW . ndy1r3lteo ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ono0qix5io )
, rtdwData , 0 , 30 , sizeof ( rtDW . ono0qix5io ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bih1twzowf )
, rtdwData , 0 , 31 , sizeof ( rtDW . bih1twzowf ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . evb2jcnsmb )
, rtdwData , 0 , 32 , sizeof ( rtDW . evb2jcnsmb ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jcb0vgamw2 )
, rtdwData , 0 , 33 , sizeof ( rtDW . jcb0vgamw2 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . g1tih4iurb )
, rtdwData , 0 , 34 , sizeof ( rtDW . g1tih4iurb ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . gk4tvjl5km )
, rtdwData , 0 , 35 , sizeof ( rtDW . gk4tvjl5km ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jqdnga4d0r )
, rtdwData , 0 , 36 , sizeof ( rtDW . jqdnga4d0r ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . khs2ujrsdq )
, rtdwData , 0 , 37 , sizeof ( rtDW . khs2ujrsdq ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . hoc4ujevyd )
, rtdwData , 0 , 38 , sizeof ( rtDW . hoc4ujevyd ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . pqjv5ubgvq )
, rtdwData , 0 , 39 , sizeof ( rtDW . pqjv5ubgvq ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . dzwszeq5uo )
, rtdwData , 0 , 40 , sizeof ( rtDW . dzwszeq5uo ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . lru3e1mvrz )
, rtdwData , 0 , 41 , sizeof ( rtDW . lru3e1mvrz ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . luuegejdc0 )
, rtdwData , 0 , 42 , sizeof ( rtDW . luuegejdc0 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . nva3c2aiue )
, rtdwData , 0 , 43 , sizeof ( rtDW . nva3c2aiue ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . p1lgfwsxn3 )
, rtdwData , 0 , 44 , sizeof ( rtDW . p1lgfwsxn3 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ozura1lel3 )
, rtdwData , 0 , 45 , sizeof ( rtDW . ozura1lel3 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . cn5pwf5utq )
, rtdwData , 0 , 46 , sizeof ( rtDW . cn5pwf5utq ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . c1d5q3vumy )
, rtdwData , 0 , 47 , sizeof ( rtDW . c1d5q3vumy ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . flfjax3w0e )
, rtdwData , 0 , 48 , sizeof ( rtDW . flfjax3w0e ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . gluwhgdkil )
, rtdwData , 0 , 49 , sizeof ( rtDW . gluwhgdkil ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . onwpqbmdms )
, rtdwData , 0 , 50 , sizeof ( rtDW . onwpqbmdms ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . n0wxb1xzlc )
, rtdwData , 0 , 51 , sizeof ( rtDW . n0wxb1xzlc ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . mf4tzazbhp )
, rtdwData , 0 , 52 , sizeof ( rtDW . mf4tzazbhp ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . pszwtqz0gn )
, rtdwData , 0 , 53 , sizeof ( rtDW . pszwtqz0gn ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . dhwxr34two )
, rtdwData , 0 , 54 , sizeof ( rtDW . dhwxr34two ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bcl2uuqmhl )
, rtdwData , 0 , 55 , sizeof ( rtDW . bcl2uuqmhl ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . nxjlr5banb )
, rtdwData , 0 , 56 , sizeof ( rtDW . nxjlr5banb ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ja1c4asgaz )
, rtdwData , 0 , 57 , sizeof ( rtDW . ja1c4asgaz ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . btigisbrqf )
, rtdwData , 0 , 58 , sizeof ( rtDW . btigisbrqf ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ckyfoeqie5 )
, rtdwData , 0 , 59 , sizeof ( rtDW . ckyfoeqie5 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ixaqaxatlt )
, rtdwData , 0 , 60 , sizeof ( rtDW . ixaqaxatlt ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . fshou35ift )
, rtdwData , 0 , 61 , sizeof ( rtDW . fshou35ift ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . cflc32uwnd )
, rtdwData , 0 , 62 , sizeof ( rtDW . cflc32uwnd ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . oqko4zquza )
, rtdwData , 0 , 63 , sizeof ( rtDW . oqko4zquza ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . h3mr0riybw )
, rtdwData , 0 , 64 , sizeof ( rtDW . h3mr0riybw ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . pfmhktgqz5 )
, rtdwData , 0 , 65 , sizeof ( rtDW . pfmhktgqz5 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . mquiy4fzeb )
, rtdwData , 0 , 66 , sizeof ( rtDW . mquiy4fzeb ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . omeqzycfh2 )
, rtdwData , 0 , 67 , sizeof ( rtDW . omeqzycfh2 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . imt2dcvft2 )
, rtdwData , 0 , 68 , sizeof ( rtDW . imt2dcvft2 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . cwyukvwtwb )
, rtdwData , 0 , 69 , sizeof ( rtDW . cwyukvwtwb ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ipcifxvj5x )
, rtdwData , 0 , 70 , sizeof ( rtDW . ipcifxvj5x ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . c2dyuklr3i )
, rtdwData , 0 , 71 , sizeof ( rtDW . c2dyuklr3i ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . p40fsqbchl )
, rtdwData , 0 , 72 , sizeof ( rtDW . p40fsqbchl ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . l4mfodlgua )
, rtdwData , 0 , 73 , sizeof ( rtDW . l4mfodlgua ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . kf0zhsqe1e )
, rtdwData , 0 , 74 , sizeof ( rtDW . kf0zhsqe1e ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ie2rbfy2dj )
, rtdwData , 0 , 75 , sizeof ( rtDW . ie2rbfy2dj ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bi3ryeji3q )
, rtdwData , 0 , 76 , sizeof ( rtDW . bi3ryeji3q ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . gexhlxucmx )
, rtdwData , 0 , 77 , sizeof ( rtDW . gexhlxucmx ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bzymrve3xd )
, rtdwData , 0 , 78 , sizeof ( rtDW . bzymrve3xd ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . cjg2lxwx3p )
, rtdwData , 0 , 79 , sizeof ( rtDW . cjg2lxwx3p ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jbxbvwznkw )
, rtdwData , 0 , 80 , sizeof ( rtDW . jbxbvwznkw ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ofeqpav0z1 )
, rtdwData , 0 , 81 , sizeof ( rtDW . ofeqpav0z1 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . f2rh3pjcf4 )
, rtdwData , 0 , 82 , sizeof ( rtDW . f2rh3pjcf4 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . czpni4mnff )
, rtdwData , 0 , 83 , sizeof ( rtDW . czpni4mnff ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . edzwglzc12 )
, rtdwData , 0 , 84 , sizeof ( rtDW . edzwglzc12 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . kcrt4gkpma )
, rtdwData , 0 , 85 , sizeof ( rtDW . kcrt4gkpma ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . gdkaitdhn2 )
, rtdwData , 0 , 86 , sizeof ( rtDW . gdkaitdhn2 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . j4aiaaqlli )
, rtdwData , 0 , 87 , sizeof ( rtDW . j4aiaaqlli ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . jw31kvp3ln )
, rtdwData , 0 , 88 , sizeof ( rtDW . jw31kvp3ln ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . aetkdo2sks )
, rtdwData , 0 , 89 , sizeof ( rtDW . aetkdo2sks ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . dbfmnhxbxj )
, rtdwData , 0 , 90 , sizeof ( rtDW . dbfmnhxbxj ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . p1nnlsrxke )
, rtdwData , 0 , 91 , sizeof ( rtDW . p1nnlsrxke ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bfmr5zictt )
, rtdwData , 0 , 92 , sizeof ( rtDW . bfmr5zictt ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . nhh3pckv2z )
, rtdwData , 0 , 93 , sizeof ( rtDW . nhh3pckv2z ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . pu1q4zlmwb )
, rtdwData , 0 , 94 , sizeof ( rtDW . pu1q4zlmwb ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . pe5pl50ynw )
, rtdwData , 0 , 95 , sizeof ( rtDW . pe5pl50ynw ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . eda54vucfl )
, rtdwData , 0 , 96 , sizeof ( rtDW . eda54vucfl ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . mnycq5gn5i )
, rtdwData , 0 , 97 , sizeof ( rtDW . mnycq5gn5i ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . e4lgtlqce2 )
, rtdwData , 0 , 98 , sizeof ( rtDW . e4lgtlqce2 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . hpyvhbyyfk )
, rtdwData , 0 , 99 , sizeof ( rtDW . hpyvhbyyfk ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . mv3mphax4f )
, rtdwData , 0 , 100 , sizeof ( rtDW . mv3mphax4f ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . dyrzzohb5s )
, rtdwData , 0 , 101 , sizeof ( rtDW . dyrzzohb5s ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . apmlxbmuwh )
, rtdwData , 0 , 102 , sizeof ( rtDW . apmlxbmuwh ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ogaaumd32e )
, rtdwData , 0 , 103 , sizeof ( rtDW . ogaaumd32e ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . gvkgxqsg5w )
, rtdwData , 0 , 104 , sizeof ( rtDW . gvkgxqsg5w ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ksp31oyn4z )
, rtdwData , 0 , 105 , sizeof ( rtDW . ksp31oyn4z ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . gwi2bo5yvs )
, rtdwData , 0 , 106 , sizeof ( rtDW . gwi2bo5yvs ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . dedzusgrw0 )
, rtdwData , 0 , 107 , sizeof ( rtDW . dedzusgrw0 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . dqrx4b5l1l )
, rtdwData , 0 , 108 , sizeof ( rtDW . dqrx4b5l1l ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ei55bolyl0 )
, rtdwData , 0 , 109 , sizeof ( rtDW . ei55bolyl0 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . frdq0ezqxz )
, rtdwData , 0 , 110 , sizeof ( rtDW . frdq0ezqxz ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . hc5kmkcx43 )
, rtdwData , 0 , 111 , sizeof ( rtDW . hc5kmkcx43 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . bp0lxwi25f )
, rtdwData , 0 , 112 , sizeof ( rtDW . bp0lxwi25f ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . nd3tkuvjly )
, rtdwData , 0 , 113 , sizeof ( rtDW . nd3tkuvjly ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . adrllpi2ax )
, rtdwData , 0 , 114 , sizeof ( rtDW . adrllpi2ax ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . cqvouu2ka3 )
, rtdwData , 0 , 115 , sizeof ( rtDW . cqvouu2ka3 ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . j4h3zrlxtn )
, rtdwData , 0 , 116 , sizeof ( rtDW . j4h3zrlxtn ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . asj3qcjbaz )
, rtdwData , 0 , 117 , sizeof ( rtDW . asj3qcjbaz ) ) ;
mr_TruckBenchmark_restoreDataFromMxArray ( ( void * ) & ( rtDW . ok1wan2u4e )
, rtdwData , 0 , 118 , sizeof ( rtDW . ok1wan2u4e ) ) ; } } mxArray *
mr_TruckBenchmark_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 11 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char_T * blockType [ 11 ] = { "Scope" , "S-Function" , "S-Function" ,
"S-Function" , "S-Function" , "S-Function" , "Scope" , "Scope" , "S-Function"
, "S-Function" , "" , } ; static const char_T * blockPath [ 11 ] = {
"TruckBenchmark/Controller/Scope" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Network Configuration1" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Network Configuration2" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Node Configuration" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Node Configuration3" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ,
"TruckBenchmark/Controller/Scope1" ,
"TruckBenchmark/Controller/CAN TX//RX/Signals3" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive3" ,
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive2" , "" , } ; static const
int reason [ 11 ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 , } ; for (
subs [ 0 ] = 0 ; subs [ 0 ] < 11 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] = 0 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateDoubleScalar ( ( real_T ) reason [ subs [ 0 ] ] ) ) ; } }
return data ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS ,
13 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ;
ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ;
ssSetNumSampleTimes ( rtS , 6 ) ; ssSetNumBlocks ( rtS , 434 ) ;
ssSetNumBlockIO ( rtS , 243 ) ; ssSetNumBlockParams ( rtS , 134 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetSampleTime ( rtS , 2 , 2.0E-5 ) ;
ssSetSampleTime ( rtS , 3 , 0.00054 ) ; ssSetSampleTime ( rtS , 4 , 1.0 ) ;
ssSetSampleTime ( rtS , 5 , - 2.0 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS , 2 , 0.0 ) ;
ssSetOffsetTime ( rtS , 3 , 0.0 ) ; ssSetOffsetTime ( rtS , 4 , 0.0 ) ;
ssSetOffsetTime ( rtS , 5 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 2564456923U ) ; ssSetChecksumVal ( rtS , 1 ,
14143646U ) ; ssSetChecksumVal ( rtS , 2 , 2799630258U ) ; ssSetChecksumVal (
rtS , 3 , 17045496U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; ( void ) memset ( ( char_T * )
rtS , 0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char_T * ) & mdlInfo ,
0 , sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char_T * ) &
blkInfo2 , 0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char_T *
) & blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ;
ssSetBlkInfo2Ptr ( rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , &
blkInfoSLSize ) ; ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo (
rtS , executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T
mdlPeriod [ NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ;
static time_T mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [
NSAMPLE_TIMES ] ; static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static
boolean_T mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T
mdlPerTaskSampleHits [ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T
mdlTimeOfNextSampleHit [ NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i <
NSAMPLE_TIMES ; i ++ ) { mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ;
mdlTaskTimes [ i ] = 0.0 ; mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } }
ssSetSampleTimePtr ( rtS , & mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , &
mdlOffset [ 0 ] ) ; ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ;
ssSetTPtr ( rtS , & mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , &
mdlSampleHits [ 0 ] ) ; ssSetTNextWasAdjustedPtr ( rtS , &
mdlTNextWasAdjustedPtr [ 0 ] ) ; ssSetPerTaskSampleHitsPtr ( rtS , &
mdlPerTaskSampleHits [ 0 ] ) ; ssSetTimeOfNextSampleHitPtr ( rtS , &
mdlTimeOfNextSampleHit [ 0 ] ) ; } ssSetSolverMode ( rtS ,
SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS , ( ( void * ) & rtB ) ) ;
( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof ( B ) ) ; { int32_T i ;
for ( i = 0 ; i < 20 ; i ++ ) { rtB . cua1wzatht [ i ] = CAN_DATATYPE_GROUND
; } rtB . hic4phvehd = CAN_DATATYPE_GROUND ; rtB . fqxly0svox =
CAN_DATATYPE_GROUND ; } } { real_T * x = ( real_T * ) & rtX ; ssSetContStates
( rtS , x ) ; ( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void
* dwork = ( void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void )
memset ( dwork , 0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ;
( void ) memset ( ( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ;
ssSetModelMappingInfo ( rtS , & dtInfo ) ; dtInfo . numDataTypes = 35 ;
dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = &
rtDataTypeNames [ 0 ] ; dtInfo . BTransTable = & rtBTransTable ; dtInfo .
PTransTable = & rtPTransTable ; dtInfo . dataTypeInfoTable =
rtDataTypeInfoTable ; } TruckBenchmark_InitializeDataMapInfo ( ) ;
ssSetIsRapidAcceleratorActive ( rtS , true ) ; ssSetRootSS ( rtS , rtS ) ;
ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS ,
"TruckBenchmark" ) ; ssSetPath ( rtS , "TruckBenchmark" ) ; ssSetTStart ( rtS
, 0.0 ) ; ssSetTFinal ( rtS , 500.0 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = ( NULL ) ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { { static int_T
rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
1 } ; static int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 , 1
, 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static int_T rt_LoggedStateDimensions [ ] = {
1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 } ; static boolean_T
rt_LoggedStateIsVarDims [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
, 0 } ; static BuiltInDTypeId rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ;
static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 , 0 , 0 , 0 , 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingStatePreprocessingFcnPtrs [ ] = { ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) ,
( NULL ) , ( NULL ) , ( NULL ) } ; static const char_T * rt_LoggedStateLabels
[ ] = { "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" ,
"CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" }
; static const char_T * rt_LoggedStateBlockNames [ ] = {
 "TruckBenchmark/Vehicle Model/Clutch and\nTransmission/Vehicle Dynamics/Integrator"
, "TruckBenchmark/Vehicle Model/Chassi/Integrator1" ,
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Integrator\nomega_t" ,
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Integrator p_im" ,
 "TruckBenchmark/Vehicle Model/Clutch and\nTransmission/Engine Dynamics/Integrator1"
, "TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator1/Integrator"
, "TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator2/Integrator"
, "TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Integrator p_em" ,
 "TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Subsystem X_Oim/Integrator X_Oim"
, "TruckBenchmark/Vehicle Model/Road Slope Data/Integrator" ,
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Integrator" ,
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Actuator/Integrator" ,
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Subsystem/Integrator X_Oem"
} ; static const char_T * rt_LoggedStateNames [ ] = { "" , "" , "" , "" , ""
, "" , "" , "" , "" , "" , "" , "" , "" } ; static boolean_T
rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 } ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 , 1 ,
2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 , 11 , 12 } ; static RTWLogSignalInfo
rt_LoggedStateSignalInfo = { 13 , rt_LoggedStateWidths ,
rt_LoggedStateNumDimensions , rt_LoggedStateDimensions ,
rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) , rt_LoggedStateDataTypeIds ,
rt_LoggedStateComplexSignals , ( NULL ) , rt_LoggingStatePreprocessingFcnPtrs
, { rt_LoggedStateLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 13 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . cwf2tewh2v ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . lpegok4bfi ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . akhhz2ar2w ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . ekar034xyr ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . aufcyghqde ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) & rtX . gdrfqkaj00 ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) & rtX . dl0s2litjt ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) & rtX . a3o55becan ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtX . olhqyyiiqq ;
rt_LoggedStateSignalPtrs [ 9 ] = ( void * ) & rtX . faiarhiizk ;
rt_LoggedStateSignalPtrs [ 10 ] = ( void * ) & rtX . f10gbcy5as ;
rt_LoggedStateSignalPtrs [ 11 ] = ( void * ) & rtX . d0etugyxyo ;
rt_LoggedStateSignalPtrs [ 12 ] = ( void * ) & rtX . fteoprdfjw ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "tmp_raccel_xout" ) ; rtliSetLogXFinal (
ssGetRTWLogInfo ( rtS ) , "xFinal" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 2 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 1000 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS ,
& statesInfo2 ) ; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 13 ] ;
static real_T absTol [ 13 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 } ;
static uint8_T absTolControl [ 13 ] = { 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U
, 0U , 0U , 0U , 0U , 0U } ; static real_T contStateJacPerturbBoundMinVec [
13 ] ; static real_T contStateJacPerturbBoundMaxVec [ 13 ] ; static uint8_T
zcAttributes [ 63 ] = { ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN
) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN
) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL_UP ) ,
( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) } ; static
ssNonContDerivSigInfo nonContDerivSigInfo [ 9 ] = { { 1 * sizeof ( real_T ) ,
( char * ) ( & rtB . ko0hu3j2c1 ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) ,
( char * ) ( & rtB . dtbeclhhb3 ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . mtgpjerup5 ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . ouddd1bq5c ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . k2q4u3lafs ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . njcgrc3zvm ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . fitzivdg3v ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . fagi55uakt ) , ( NULL ) } , { 1 * sizeof ( real_T ) , (
char * ) ( & rtB . mtn4j2z4x0 ) , ( NULL ) } } ; { int i ; for ( i = 0 ; i <
13 ; ++ i ) { contStateJacPerturbBoundMinVec [ i ] = 0 ;
contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } } ssSetSolverRelTol (
rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 )
; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 2.0E-5 ) ; ssSetSolverMaxOrder ( rtS , - 1 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
9 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS , "ode23s" ) ;
ssSetVariableStepSolver ( rtS , 1 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol )
; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 63 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 63 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 2564456923U ) ; ssSetChecksumVal ( rtS , 1 ,
14143646U ) ; ssSetChecksumVal ( rtS , 2 , 2799630258U ) ; ssSetChecksumVal (
rtS , 3 , 17045496U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 13 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = ( sysRanDType * ) &
rtDW . p1nnlsrxke ; systemRan [ 2 ] = ( sysRanDType * ) & rtDW . bfmr5zictt ;
systemRan [ 3 ] = & rtAlwaysEnabled ; systemRan [ 4 ] = ( sysRanDType * ) &
rtDW . dbfmnhxbxj ; systemRan [ 5 ] = ( sysRanDType * ) & rtDW . dbfmnhxbxj ;
systemRan [ 6 ] = ( sysRanDType * ) & rtDW . dbfmnhxbxj ; systemRan [ 7 ] = (
sysRanDType * ) & rtDW . dbfmnhxbxj ; systemRan [ 8 ] = & rtAlwaysEnabled ;
systemRan [ 9 ] = & rtAlwaysEnabled ; systemRan [ 10 ] = & rtAlwaysEnabled ;
systemRan [ 11 ] = & rtAlwaysEnabled ; systemRan [ 12 ] = & rtAlwaysEnabled ;
rteiSetModelMappingInfoPtr ( ssGetRTWExtModeInfo ( rtS ) , &
ssGetModelMappingInfo ( rtS ) ) ; rteiSetChecksumsPtr ( ssGetRTWExtModeInfo (
rtS ) , ssGetChecksums ( rtS ) ) ; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS )
, ssGetTPtr ( rtS ) ) ; } slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_TruckBenchmark_GetSimStateDisallowedBlocks ) ;
slsaGetWorkFcnForSimTargetOP ( rtS , mr_TruckBenchmark_GetDWork ) ;
slsaSetWorkFcnForSimTargetOP ( rtS , mr_TruckBenchmark_SetDWork ) ; rtP .
Integrator_UpperSat = rtInf ; rtP . Integrator1_UpperSat = rtInf ; rtP .
Saturation_UpperSat_i32xa2dnvv = rtInf ; rtP .
Integrator1_UpperSat_pktoycczal = rtInf ; rtP .
Saturation1_UpperSat_haikx2purp = rtInf ; rt_RapidReadMatFileAndUpdateParams
( rtS ) ; if ( ssGetErrorStatus ( rtS ) ) { return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 6 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID6 ( tid ) ; }
