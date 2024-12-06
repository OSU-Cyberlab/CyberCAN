#ifndef RTW_HEADER_TruckBenchmark_acc_h_
#define RTW_HEADER_TruckBenchmark_acc_h_
#ifndef TruckBenchmark_acc_COMMON_INCLUDES_
#define TruckBenchmark_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <math.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "can_message.h"
#endif
#include "TruckBenchmark_acc_types.h"
#include <stddef.h>
#include "rtsplntypes.h"
#include <float.h>
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { CAN_MESSAGE_BUS B_12_57_0 ; CAN_DATATYPE B_2_0_1 ;
CAN_DATATYPE B_2_2_0 [ 20 ] ; CAN_DATATYPE B_1_1_0 ; real_T B_12_0_0 ; real_T
B_12_1_0 ; real_T B_12_2_0 ; real_T B_12_9_0 ; real_T B_12_9_1 ; real_T
B_12_9_2 ; real_T B_12_9_3 ; real_T B_12_9_4 ; real_T B_12_9_5 ; real_T
B_12_9_6 ; real_T B_12_9_7 ; real_T B_12_9_8 ; real_T B_12_9_9 ; real_T
B_12_9_10 ; real_T B_12_9_11 ; real_T B_12_9_12 ; real_T B_12_9_13 ; real_T
B_12_9_14 ; real_T B_12_9_15 ; real_T B_12_9_16 ; real_T B_12_9_17 ; real_T
B_12_9_18 ; real_T B_12_9_19 ; real_T B_12_12_0 ; real_T B_12_12_1 ; real_T
B_12_12_2 ; real_T B_12_12_3 ; real_T B_12_13_0 ; real_T B_12_13_1 ; real_T
B_12_14_0 ; real_T B_12_14_1 ; real_T B_12_14_2 ; real_T B_12_15_0 ; real_T
B_12_15_1 ; real_T B_12_15_2 ; real_T B_12_15_3 ; real_T B_12_15_4 ; real_T
B_12_15_5 ; real_T B_12_17_0 ; real_T B_12_17_1 ; real_T B_12_17_2 ; real_T
B_12_17_3 ; real_T B_12_17_4 ; real_T B_12_18_0 ; real_T B_12_19_0 ; real_T
B_12_20_0 ; real_T B_12_21_0 ; real_T B_12_23_0 ; real_T B_12_24_0 ; real_T
B_12_26_0 ; real_T B_12_27_0 ; real_T B_12_28_0 ; real_T B_12_29_0 ; real_T
B_12_31_0 ; real_T B_12_32_0 ; real_T B_12_33_0 ; real_T B_12_34_0 ; real_T
B_12_35_0 ; real_T B_12_36_0 ; real_T B_12_37_0 ; real_T B_12_38_0 ; real_T
B_12_39_0 ; real_T B_12_40_0 ; real_T B_12_41_0 ; real_T B_12_43_0 ; real_T
B_12_45_0 ; real_T B_12_46_0 ; real_T B_12_47_0 ; real_T B_12_49_0 ; real_T
B_12_50_0 ; real_T B_12_52_0 ; real_T B_12_59_0 ; real_T B_12_59_1 ; real_T
B_12_60_0 ; real_T B_12_61_0 ; real_T B_12_62_0 ; real_T B_12_64_0 ; real_T
B_12_66_0 ; real_T B_12_67_0 ; real_T B_12_68_0 ; real_T B_12_69_0 ; real_T
B_12_70_0 ; real_T B_12_71_0 ; real_T B_12_72_0 ; real_T B_12_74_0 ; real_T
B_12_75_0 ; real_T B_12_76_0 ; real_T B_12_79_0 ; real_T B_12_80_0 ; real_T
B_12_81_0 ; real_T B_12_83_0 ; real_T B_12_84_0 ; real_T B_12_86_0 ; real_T
B_12_88_0 ; real_T B_12_89_0 ; real_T B_12_90_0 ; real_T B_12_91_0 ; real_T
B_12_92_0 ; real_T B_12_93_0 ; real_T B_12_94_0 ; real_T B_12_95_0 ; real_T
B_12_96_0 ; real_T B_12_97_0 ; real_T B_12_98_0 ; real_T B_12_101_0 ; real_T
B_12_103_0 ; real_T B_12_107_0 ; real_T B_12_108_0 ; real_T B_12_109_0 ;
real_T B_12_110_0 ; real_T B_12_111_0 ; real_T B_12_112_0 ; real_T B_12_113_0
; real_T B_12_114_0 ; real_T B_12_115_0 ; real_T B_12_116_0 ; real_T
B_12_125_0 ; real_T B_12_128_0 ; real_T B_12_129_0 ; real_T B_12_131_0 ;
real_T B_12_132_0 ; real_T B_12_134_0 ; real_T B_12_135_0 ; real_T B_12_137_0
; real_T B_12_138_0 ; real_T B_12_139_0 ; real_T B_12_141_0 ; real_T
B_12_142_0 ; real_T B_12_144_0 ; real_T B_12_145_0 ; real_T B_12_146_0 ;
real_T B_12_147_0 ; real_T B_12_148_0 ; real_T B_12_150_0 ; real_T B_12_152_0
; real_T B_12_153_0 ; real_T B_12_156_0 ; real_T B_12_160_0 ; real_T
B_12_161_0 ; real_T B_12_164_0 ; real_T B_12_165_0 ; real_T B_12_166_0 ;
real_T B_12_169_0 ; real_T B_12_170_0 ; real_T B_12_171_0 ; real_T B_12_172_0
; real_T B_12_173_0 ; real_T B_12_174_0 ; real_T B_12_175_0 ; real_T
B_12_176_0 ; real_T B_12_177_0 ; real_T B_12_178_0 ; real_T B_12_179_0 ;
real_T B_12_180_0 ; real_T B_12_181_0 ; real_T B_12_182_0 ; real_T B_12_184_0
; real_T B_12_185_0 ; real_T B_12_186_0 ; real_T B_12_187_0 ; real_T
B_12_188_0 ; real_T B_12_189_0 ; real_T B_12_190_0 ; real_T B_12_191_0 ;
real_T B_12_192_0 ; real_T B_12_193_0 ; real_T B_12_194_0 ; real_T B_12_195_0
; real_T B_12_196_0 ; real_T B_12_197_0 ; real_T B_12_198_0 ; real_T
B_12_202_0 [ 2 ] ; real_T B_12_203_0 [ 2 ] ; real_T B_12_204_0 [ 2 ] ; real_T
B_12_205_0 ; real_T B_12_206_0 ; real_T B_12_207_0 ; real_T B_12_209_0 ;
real_T B_12_210_0 ; real_T B_12_211_0 ; real_T B_12_212_0 ; real_T B_12_213_0
; real_T B_12_214_0 ; real_T B_12_217_0 ; real_T B_12_218_0 ; real_T
B_12_219_0 ; real_T B_12_220_0 ; real_T B_12_221_0 ; real_T B_12_223_0 ;
real_T B_12_224_0 ; real_T B_12_225_0 ; real_T B_12_226_0 ; real_T B_12_227_0
; real_T B_12_235_0 ; real_T B_12_236_0 ; real_T B_12_40_0_m ; real_T
B_12_42_0 ; real_T B_12_47_0_c ; real_T B_12_49_0_k ; real_T B_12_52_0_c ;
real_T B_12_53_0 ; real_T B_12_54_0 ; real_T B_12_55_0 ; real_T B_12_56_0 ;
real_T B_12_57_0_b ; real_T B_12_58_0 ; real_T B_12_59_0_p ; real_T
B_12_60_0_c ; real_T B_12_61_0_f ; real_T B_12_62_0_g ; real_T B_12_63_0 ;
real_T B_12_64_0_g ; real_T B_12_65_0 ; real_T B_12_66_0_m ; real_T
B_12_67_0_n ; real_T B_12_68_0_p ; real_T B_12_69_0_l ; real_T B_12_70_0_j ;
real_T B_12_71_0_d ; real_T B_12_72_0_g ; real_T B_12_73_0 ; real_T
B_12_74_0_l ; real_T B_12_75_0_d ; real_T B_12_76_0_d ; real_T B_12_77_0 ;
real_T B_12_78_0 ; real_T B_12_79_0_l ; real_T B_12_80_0_o ; real_T
B_12_81_0_b ; real_T B_12_82_0 ; real_T B_12_83_0_n ; real_T B_12_84_0_b ;
real_T B_12_85_0 ; real_T B_12_86_0_l ; real_T B_12_87_0 ; real_T B_11_0_1 ;
real_T B_11_0_2 ; real_T B_10_0_0 ; real_T B_9_0_0 ; real_T B_8_0_0 ; real_T
B_8_1_0 ; real_T B_8_2_0 ; real_T B_7_0_1 ; real_T B_6_13_0 ; real_T B_6_15_0
; real_T B_6_16_0 ; real_T B_6_17_0 ; real_T B_6_18_0 ; real_T B_6_0_0 [ 9905
] ; real_T B_6_1_0 [ 9905 ] ; real_T B_6_2_0 ; real_T B_6_5_0 ; real_T
B_6_6_0 ; real_T B_6_7_0 ; real_T B_5_0_1 ; real_T B_4_0_1 ; real_T B_3_0_1 ;
real_T B_2_2_1 ; real_T B_0_0_0 ; uint8_T B_12_45_0_h [ 31 ] ; uint8_T
B_12_46_0_b [ 31 ] ; boolean_T B_12_155_0 ; boolean_T B_12_20_0_d ; boolean_T
B_12_21_0_e ; boolean_T B_12_22_0 ; boolean_T B_12_23_0_b ; boolean_T
B_12_24_0_j ; boolean_T B_12_25_0 ; boolean_T B_12_26_0_f ; boolean_T
B_12_27_0_a ; boolean_T B_12_28_0_j ; boolean_T B_12_29_0_j ; boolean_T
B_12_31_0_o ; boolean_T B_12_32_0_n ; boolean_T B_12_33_0_i ; boolean_T
B_12_34_0_o ; boolean_T B_12_35_0_n ; boolean_T B_12_36_0_m ; boolean_T
B_12_37_0_c ; boolean_T B_12_38_0_m ; char_T pad_B_12_38_0_m [ 7 ] ; }
B_TruckBenchmark_T ; typedef struct { real_T nextTime ; real_T
Memory4_PreviousInput ; real_T Memory3_PreviousInput ; real_T
Memory2_PreviousInput ; real_T x_rOld_PreviousInput ; real_T
T_1Old_PreviousInput ; real_T m_bpLambda ; real_T m_yyA ; real_T m_yyB ;
real_T m_yy2 ; real_T m_up [ 9905 ] ; real_T m_y2 [ 9905 ] ; real_T
Memory1_PreviousInput ; real_T Controller_lastCallTime ; real_T
CANReceive_CANReceive [ 137 ] ; real_T CANTransmit_CANTransmit [ 137 ] ;
real_T J1939TransportLayerReceiveSubsystem_lastCallTime ; int64_T
numCompleteCycles ; struct { real_T modelTStart ; } TransportDelay_RWORK ;
struct { real_T modelTStart ; } TransportDelay1_RWORK ; void * Scope_PWORK ;
struct { void * CONFIGHANDLE ; } J1939NetworkConfiguration1_PWORK ; struct {
void * CONFIGHANDLE ; } J1939NetworkConfiguration2_PWORK ; struct { void *
NODEPTR ; void * CONFIGHANDLE ; } J1939NodeConfiguration_PWORK ; struct {
void * NODEPTR ; void * CONFIGHANDLE ; } J1939NodeConfiguration3_PWORK ;
struct { void * PGPTR ; void * CONFIGHANDLE ; } J1939Receive7_PWORK ; void *
Scope1_PWORK ; void * Signals3_PWORK [ 4 ] ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Receive3_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Receive2_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Receive4_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Receive5_PWORK ; void * Scope1_PWORK_e ; struct { void
* PGPTR ; void * CONFIGHANDLE ; } J1939Receive6_PWORK ; struct { void * PGPTR
; void * CONFIGHANDLE ; } J1939Transmit1_PWORK ; struct { void * PGPTR ; void
* CONFIGHANDLE ; } J1939Transmit2_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Transmit3_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Transmit4_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Transmit5_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Transmit6_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Transmit7_PWORK ; void * Scope_PWORK_i ; void *
Signals4_PWORK [ 4 ] ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace_PWORK ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } J1939Receive1_PWORK ; void * m_bpDataSet ; void * TWork [ 6
] ; void * SWork [ 9 ] ; void * Scope1_PWORK_a ; void * Scope2_PWORK ; void *
Scope3_PWORK ; void * Scope4_PWORK ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_Fuelconsumptiondm3100km_at_outport_0_PWORK ; struct
{ void * AQHandles ; }
TAQSigLogging_InsertedFor_TransmissionControlUnit_at_outport_0_PWORK ; struct
{ void * AQHandles ; }
TAQSigLogging_InsertedFor_TransmissionControlUnit_at_outport_1_PWORK ; struct
{ void * AQHandles ; } TAQSigLogging_InsertedFor_radsRPM_at_outport_0_PWORK ;
struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_Integrator1_at_outport_0_PWORK ; struct { void *
AQHandles ; } TAQSigLogging_InsertedFor_mskmh_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_ClutchTransfer_at_outport_0_PWORK ; struct { void *
AQHandles ; }
TAQSigLogging_InsertedFor_SpeedDifferenceClutchLimits_at_outport_0_PWORK ;
struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_SpeedDifferenceClutchLimits_at_outport_1_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace_PWORK_e ;
struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_lambda_at_outport_0_PWORK ; struct { void *
TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs [
2 ] ; } TransportDelay1_PWORK ; void * Scope1_PWORK_j ; void * Scope2_PWORK_m
; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_1DLookupTable_at_outport_0_PWORK ; struct { void *
AQHandles ; } TAQSigLogging_InsertedFor_Integrator_at_outport_0_PWORK ; void
* BSRScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace33_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace5_PWORK ; void * M_eScope_PWORK ; struct
{ void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace13_PWORK ; void *
P_cScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace11_PWORK ; void * P_tmScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace12_PWORK ;
void * T_1Scope2_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace31_PWORK ; void * T_cScope_PWORK ; struct
{ void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace_PWORK_e3 ; void *
T_eScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace2_PWORK ; void * T_emScope1_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace29_PWORK ;
void * W_cScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace7_PWORK ; void * W_egrScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace6_PWORK ;
void * W_eiScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace9_PWORK ; void * W_eoScope_PWORK ; struct
{ void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace10_PWORK ; void *
W_fScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace22_PWORK ; void * W_tScope_PWORK ; struct
{ void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace8_PWORK ; void *
X_OemScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace30_PWORK ; void * X_OimScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace25_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace14_PWORK ;
void * n_tScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace15_PWORK ; void * lambdaScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace16_PWORK ;
void * u_deltaScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace17_PWORK ; void * u_egrScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace18_PWORK ;
void * u_vgtScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace19_PWORK ; void * n_eScope_PWORK ; struct
{ void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace20_PWORK ; void *
eta_tmScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace21_PWORK ; void * eta_cScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace24_PWORK ;
void * x_egrScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace27_PWORK ; void * u_egractScope_PWORK ;
struct { void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace28_PWORK ;
void * u_vgtactScope_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace3_PWORK ; void * p_imScope_PWORK ; struct
{ void * AQHandles ; } _asyncqueue_inserted_for_ToWorkspace32_PWORK ; void *
x_rScope3_PWORK ; struct { void * AQHandles ; }
_asyncqueue_inserted_for_ToWorkspace4_PWORK ; void * p_emScope_PWORK ; void *
Scope1_PWORK_l ; void * Scope2_PWORK_k ; void * Scope4_PWORK_o ; void *
Scope5_PWORK ; void * Scope6_PWORK ; void * Scope7_PWORK ; void *
Scope8_PWORK ; void * Scope9_PWORK ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_Gearcontrol_at_outport_0_PWORK ; struct { void *
AQHandles ; } TAQSigLogging_InsertedFor_Saturation_at_outport_0_PWORK ;
struct { void * CTLHandle ; } J1939TransportLayerTransmit_PWORK ; struct {
void * CTLHandle ; } J1939TransportLayerReceive_PWORK ; int32_T justEnabled ;
int32_T currentValue ; int32_T TransmissionControlUnit_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchPSIInport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchPSIInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
Fuelconsumptiondm3100km_sysIdxToRun ; int32_T Controller_sysIdxToRun ;
int32_T PIspeedcontrol1_sysIdxToRun ; int32_T Pspeedcontrol_sysIdxToRun ;
int32_T Gearcontrol_sysIdxToRun ; int32_T J1939CANTransportLayer1_sysIdxToRun
; int32_T CANTransmitSubsystem_sysIdxToRun ; int32_T
J1939TransportLayerReceiveSubsystem_sysIdxToRun ; uint32_T m_bpIndex ; struct
{ int_T NODEADDR ; } J1939NodeConfiguration_IWORK ; struct { int_T NODEADDR ;
} J1939NodeConfiguration3_IWORK ; char J1939Receive7_ModeSignalID [ 4 ] ;
char J1939Receive3_ModeSignalID [ 4 ] ; char J1939Receive2_ModeSignalID [ 4 ]
; char J1939Receive4_ModeSignalID [ 4 ] ; char J1939Receive5_ModeSignalID [ 4
] ; char J1939Receive6_ModeSignalID [ 4 ] ; char J1939Transmit1_ModeSignalID
[ 4 ] ; char J1939Transmit2_ModeSignalID [ 4 ] ; char
J1939Transmit3_ModeSignalID [ 4 ] ; char J1939Transmit4_ModeSignalID [ 4 ] ;
char J1939Transmit5_ModeSignalID [ 4 ] ; char J1939Transmit6_ModeSignalID [ 4
] ; char J1939Transmit7_ModeSignalID [ 4 ] ; int_T CANPack_ModeSignalID ;
char J1939Receive1_ModeSignalID [ 4 ] ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay1_IWORK ; int_T
CANTransmit_PortWidth ; int_T Integrator_MODE ; int_T Integrator1_MODE ;
int_T Integratoromega_t_MODE ; int_T Integratorp_im_MODE ; int_T MinMax1_MODE
; int_T MinMax1_MODE_i ; int_T MinMax_MODE ; int_T MinMax3_MODE ; int_T
MinMax2_MODE ; int_T Saturation_MODE ; int_T Integrator1_MODE_g ; int_T
MinMax1_MODE_e ; int_T MinMax_MODE_h ; int_T Integratorp_em_MODE ; int_T
Saturation_MODE_a ; int_T Saturation1_MODE ; int_T MinMax_MODE_c ; int_T
MinMax_MODE_p ; int_T Max1_MODE ; int_T IntegratorX_Oim_MODE ; int_T
MinMax_MODE_d ; int_T Abs_MODE ; int_T Abs_MODE_f ; int_T Saturation_MODE_a1
; int_T Saturation1_MODE_k ; int_T MinMax_MODE_pf ; int_T MinMax_MODE_n ;
int_T MinMax_MODE_m ; int_T MinMax1_MODE_l ; int_T IntegratorX_Oem_MODE ;
int_T MinMax1_MODE_n ; int_T MinMax2_MODE_m ; int_T MinMax_MODE_j ; int_T
Saturation_MODE_k ; int_T Saturation1_MODE_e ; int8_T Controller_SubsysRanBC
; int8_T CANTransmitSubsystem_SubsysRanBC ; int8_T
J1939TransportLayerReceiveSubsystem_SubsysRanBC ; uint8_T
reCalcSecDerivFirstDimCoeffs ; boolean_T Relay1_Mode ; boolean_T Relay2_Mode
; boolean_T RelationalOperator_Mode ; boolean_T SwitchPSI_Mode ; boolean_T
RelationalOperator_Mode_n ; boolean_T CANTransmit_BlockDisabled ; boolean_T
Controller_MODE ; boolean_T J1939TransportLayerReceiveSubsystem_MODE ; char_T
pad_J1939TransportLayerReceiveSubsystem_MODE [ 4 ] ; } DW_TruckBenchmark_T ;
typedef struct { real_T Integrator_CSTATE ; real_T Integrator1_CSTATE ;
real_T Integratoromega_t_CSTATE ; real_T Integratorp_im_CSTATE ; real_T
Integrator1_CSTATE_c ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_hj ; real_T Integratorp_em_CSTATE ; real_T
IntegratorX_Oim_CSTATE ; real_T Integrator_CSTATE_f ; real_T
Integrator_CSTATE_k ; real_T Integrator_CSTATE_j ; real_T
IntegratorX_Oem_CSTATE ; } X_TruckBenchmark_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator1_CSTATE ; real_T
Integratoromega_t_CSTATE ; real_T Integratorp_im_CSTATE ; real_T
Integrator1_CSTATE_c ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_hj ; real_T Integratorp_em_CSTATE ; real_T
IntegratorX_Oim_CSTATE ; real_T Integrator_CSTATE_f ; real_T
Integrator_CSTATE_k ; real_T Integrator_CSTATE_j ; real_T
IntegratorX_Oem_CSTATE ; } XDot_TruckBenchmark_T ; typedef struct { boolean_T
Integrator_CSTATE ; boolean_T Integrator1_CSTATE ; boolean_T
Integratoromega_t_CSTATE ; boolean_T Integratorp_im_CSTATE ; boolean_T
Integrator1_CSTATE_c ; boolean_T Integrator_CSTATE_h ; boolean_T
Integrator_CSTATE_hj ; boolean_T Integratorp_em_CSTATE ; boolean_T
IntegratorX_Oim_CSTATE ; boolean_T Integrator_CSTATE_f ; boolean_T
Integrator_CSTATE_k ; boolean_T Integrator_CSTATE_j ; boolean_T
IntegratorX_Oem_CSTATE ; } XDis_TruckBenchmark_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator1_CSTATE ; real_T
Integratoromega_t_CSTATE ; real_T Integratorp_im_CSTATE ; real_T
Integrator1_CSTATE_c ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_hj ; real_T Integratorp_em_CSTATE ; real_T
IntegratorX_Oim_CSTATE ; real_T Integrator_CSTATE_f ; real_T
Integrator_CSTATE_k ; real_T Integrator_CSTATE_j ; real_T
IntegratorX_Oem_CSTATE ; } CStateAbsTol_TruckBenchmark_T ; typedef struct {
real_T Integrator_CSTATE ; real_T Integrator1_CSTATE ; real_T
Integratoromega_t_CSTATE ; real_T Integratorp_im_CSTATE ; real_T
Integrator1_CSTATE_c ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_hj ; real_T Integratorp_em_CSTATE ; real_T
IntegratorX_Oim_CSTATE ; real_T Integrator_CSTATE_f ; real_T
Integrator_CSTATE_k ; real_T Integrator_CSTATE_j ; real_T
IntegratorX_Oem_CSTATE ; } CXPtMin_TruckBenchmark_T ; typedef struct { real_T
Integrator_CSTATE ; real_T Integrator1_CSTATE ; real_T
Integratoromega_t_CSTATE ; real_T Integratorp_im_CSTATE ; real_T
Integrator1_CSTATE_c ; real_T Integrator_CSTATE_h ; real_T
Integrator_CSTATE_hj ; real_T Integratorp_em_CSTATE ; real_T
IntegratorX_Oim_CSTATE ; real_T Integrator_CSTATE_f ; real_T
Integrator_CSTATE_k ; real_T Integrator_CSTATE_j ; real_T
IntegratorX_Oem_CSTATE ; } CXPtMax_TruckBenchmark_T ; typedef struct { real_T
Integrator_IntgUpLimit_ZC ; real_T Integrator_IntgLoLimit_ZC ; real_T
Integrator_LeaveSaturate_ZC ; real_T Integrator1_IntgUpLimit_ZC ; real_T
Integrator1_IntgLoLimit_ZC ; real_T Integrator1_LeaveSaturate_ZC ; real_T
Integratoromega_t_IntgUpLimit_ZC ; real_T Integratoromega_t_IntgLoLimit_ZC ;
real_T Integratoromega_t_LeaveSaturate_ZC ; real_T
Integratorp_im_IntgUpLimit_ZC ; real_T Integratorp_im_IntgLoLimit_ZC ; real_T
Integratorp_im_LeaveSaturate_ZC ; real_T MinMax1_MinmaxInput_ZC ; real_T
MinMax1_MinmaxInput_ZC_n ; real_T MinMax_MinmaxInput_ZC ; real_T
MinMax3_MinmaxInput_ZC ; real_T MinMax2_MinmaxInput_ZC ; real_T
Saturation_UprLim_ZC ; real_T Saturation_LwrLim_ZC ; real_T
Integrator1_IntgUpLimit_ZC_k ; real_T Integrator1_IntgLoLimit_ZC_e ; real_T
Integrator1_LeaveSaturate_ZC_l ; real_T MinMax1_MinmaxInput_ZC_k ; real_T
MinMax_MinmaxInput_ZC_c ; real_T Integratorp_em_IntgUpLimit_ZC ; real_T
Integratorp_em_IntgLoLimit_ZC ; real_T Integratorp_em_LeaveSaturate_ZC ;
real_T Saturation_UprLim_ZC_i ; real_T Saturation_LwrLim_ZC_l ; real_T
Saturation1_UprLim_ZC ; real_T Saturation1_LwrLim_ZC ; real_T
MinMax_MinmaxInput_ZC_d ; real_T MinMax_MinmaxInput_ZC_g ; real_T
Max1_MinmaxInput_ZC ; real_T IntegratorX_Oim_IntgUpLimit_ZC ; real_T
IntegratorX_Oim_IntgLoLimit_ZC ; real_T IntegratorX_Oim_LeaveSaturate_ZC ;
real_T MinMax_MinmaxInput_ZC_gw ; real_T Abs_AbsZc_ZC ; real_T
Relay1_RelayZC_ZC ; real_T Abs_AbsZc_ZC_d ; real_T Relay2_RelayZC_ZC ; real_T
RelationalOperator_RelopInput_ZC ; real_T Saturation_UprLim_ZC_g ; real_T
Saturation_LwrLim_ZC_a ; real_T Saturation1_UprLim_ZC_o ; real_T
Saturation1_LwrLim_ZC_d ; real_T MinMax_MinmaxInput_ZC_gl ; real_T
MinMax_MinmaxInput_ZC_l ; real_T MinMax_MinmaxInput_ZC_m ; real_T
MinMax1_MinmaxInput_ZC_m ; real_T IntegratorX_Oem_IntgUpLimit_ZC ; real_T
IntegratorX_Oem_IntgLoLimit_ZC ; real_T IntegratorX_Oem_LeaveSaturate_ZC ;
real_T MinMax1_MinmaxInput_ZC_d ; real_T MinMax2_MinmaxInput_ZC_g ; real_T
MinMax_MinmaxInput_ZC_mz ; real_T SwitchPSI_SwitchCond_ZC ; real_T
Saturation_UprLim_ZC_i4 ; real_T Saturation_LwrLim_ZC_d ; real_T
Saturation1_UprLim_ZC_a ; real_T Saturation1_LwrLim_ZC_k ; real_T
RelationalOperator_RelopInput_ZC_g ; } ZCV_TruckBenchmark_T ; typedef struct
{ ZCSigState Integrator_IntgUpLimit_ZCE ; ZCSigState
Integrator_IntgLoLimit_ZCE ; ZCSigState Integrator_LeaveSaturate_ZCE ;
ZCSigState Integrator1_IntgUpLimit_ZCE ; ZCSigState
Integrator1_IntgLoLimit_ZCE ; ZCSigState Integrator1_LeaveSaturate_ZCE ;
ZCSigState Integratoromega_t_IntgUpLimit_ZCE ; ZCSigState
Integratoromega_t_IntgLoLimit_ZCE ; ZCSigState
Integratoromega_t_LeaveSaturate_ZCE ; ZCSigState
Integratorp_im_IntgUpLimit_ZCE ; ZCSigState Integratorp_im_IntgLoLimit_ZCE ;
ZCSigState Integratorp_im_LeaveSaturate_ZCE ; ZCSigState
MinMax1_MinmaxInput_ZCE ; ZCSigState MinMax1_MinmaxInput_ZCE_h ; ZCSigState
MinMax_MinmaxInput_ZCE ; ZCSigState MinMax3_MinmaxInput_ZCE ; ZCSigState
MinMax2_MinmaxInput_ZCE ; ZCSigState Saturation_UprLim_ZCE ; ZCSigState
Saturation_LwrLim_ZCE ; ZCSigState Integrator1_IntgUpLimit_ZCE_h ; ZCSigState
Integrator1_IntgLoLimit_ZCE_d ; ZCSigState Integrator1_LeaveSaturate_ZCE_o ;
ZCSigState MinMax1_MinmaxInput_ZCE_n ; ZCSigState MinMax_MinmaxInput_ZCE_k ;
ZCSigState Integratorp_em_IntgUpLimit_ZCE ; ZCSigState
Integratorp_em_IntgLoLimit_ZCE ; ZCSigState Integratorp_em_LeaveSaturate_ZCE
; ZCSigState Saturation_UprLim_ZCE_h ; ZCSigState Saturation_LwrLim_ZCE_d ;
ZCSigState Saturation1_UprLim_ZCE ; ZCSigState Saturation1_LwrLim_ZCE ;
ZCSigState MinMax_MinmaxInput_ZCE_n ; ZCSigState MinMax_MinmaxInput_ZCE_b ;
ZCSigState Max1_MinmaxInput_ZCE ; ZCSigState IntegratorX_Oim_IntgUpLimit_ZCE
; ZCSigState IntegratorX_Oim_IntgLoLimit_ZCE ; ZCSigState
IntegratorX_Oim_LeaveSaturate_ZCE ; ZCSigState MinMax_MinmaxInput_ZCE_e ;
ZCSigState Abs_AbsZc_ZCE ; ZCSigState Relay1_RelayZC_ZCE ; ZCSigState
Abs_AbsZc_ZCE_f ; ZCSigState Relay2_RelayZC_ZCE ; ZCSigState
RelationalOperator_RelopInput_ZCE ; ZCSigState Saturation_UprLim_ZCE_k ;
ZCSigState Saturation_LwrLim_ZCE_j ; ZCSigState Saturation1_UprLim_ZCE_d ;
ZCSigState Saturation1_LwrLim_ZCE_i ; ZCSigState MinMax_MinmaxInput_ZCE_l ;
ZCSigState MinMax_MinmaxInput_ZCE_ke ; ZCSigState MinMax_MinmaxInput_ZCE_nn ;
ZCSigState MinMax1_MinmaxInput_ZCE_e ; ZCSigState
IntegratorX_Oem_IntgUpLimit_ZCE ; ZCSigState IntegratorX_Oem_IntgLoLimit_ZCE
; ZCSigState IntegratorX_Oem_LeaveSaturate_ZCE ; ZCSigState
MinMax1_MinmaxInput_ZCE_m ; ZCSigState MinMax2_MinmaxInput_ZCE_c ; ZCSigState
MinMax_MinmaxInput_ZCE_ef ; ZCSigState SwitchPSI_SwitchCond_ZCE ; ZCSigState
Saturation_UprLim_ZCE_hx ; ZCSigState Saturation_LwrLim_ZCE_e ; ZCSigState
Saturation1_UprLim_ZCE_l ; ZCSigState Saturation1_LwrLim_ZCE_k ; ZCSigState
RelationalOperator_RelopInput_ZCE_o ; } PrevZCX_TruckBenchmark_T ; typedef
struct { const real_T B_12_0_0 ; } ConstB_TruckBenchmark_T ;
#define TruckBenchmark_rtC(S) ((ConstB_TruckBenchmark_T *) _ssGetConstBlockIO(S))
struct P_TruckBenchmark_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T
P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 [ 9905 ]
; real_T P_9 [ 9905 ] ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13
; real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ;
real_T P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T
P_24 ; real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ;
real_T P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T
P_35 ; real_T P_36 ; real_T P_37 ; real_T P_38 [ 3 ] ; real_T P_39 [ 3 ] ;
real_T P_40 ; real_T P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T
P_45 ; real_T P_46 ; real_T P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ;
real_T P_51 ; real_T P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T
P_56 ; real_T P_57 ; real_T P_58 [ 3 ] ; real_T P_59 ; real_T P_60 ; real_T
P_61 ; real_T P_62 ; real_T P_63 ; real_T P_64 ; real_T P_65 ; real_T P_66 [
33 ] ; real_T P_67 [ 33 ] ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T
P_71 ; real_T P_72 ; real_T P_73 ; real_T P_74 ; real_T P_75 ; real_T P_76 [
9905 ] ; real_T P_77 [ 9905 ] ; real_T P_78 ; real_T P_79 ; real_T P_80 ;
real_T P_81 ; real_T P_82 ; real_T P_83 [ 3 ] ; real_T P_84 ; real_T P_85 ;
real_T P_86 ; real_T P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 ; real_T
P_91 [ 15 ] ; real_T P_92 [ 15 ] ; real_T P_93 ; real_T P_94 ; real_T P_95 ;
real_T P_96 ; real_T P_97 ; real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T
P_101 ; real_T P_102 ; real_T P_103 ; real_T P_104 ; real_T P_105 ; real_T
P_106 ; real_T P_107 ; real_T P_108 ; real_T P_109 ; real_T P_110 ; real_T
P_111 ; real_T P_112 ; real_T P_113 ; real_T P_114 ; real_T P_115 ; real_T
P_116 ; real_T P_117 ; real_T P_118 ; real_T P_119 [ 4 ] ; real_T P_120 ;
real_T P_121 ; real_T P_122 ; real_T P_123 ; real_T P_124 ; real_T P_125 ;
real_T P_126 ; real_T P_127 ; real_T P_128 ; real_T P_129 ; real_T P_130 ;
real_T P_131 ; real_T P_132 ; real_T P_133 ; real_T P_134 ; real_T P_135 ;
real_T P_136 ; real_T P_137 ; real_T P_138 ; real_T P_139 ; real_T P_140 ;
real_T P_141 ; real_T P_142 ; real_T P_143 ; real_T P_144 ; real_T P_145 ;
real_T P_146 ; real_T P_147 ; real_T P_148 ; real_T P_149 ; real_T P_150 ;
real_T P_151 ; real_T P_152 ; real_T P_153 ; real_T P_154 ; real_T P_155 ;
real_T P_156 ; real_T P_157 ; real_T P_158 ; real_T P_159 ; real_T P_160 ;
real_T P_161 ; real_T P_162 ; real_T P_163 ; real_T P_164 ; real_T P_165 ;
real_T P_166 ; real_T P_167 ; real_T P_168 ; real_T P_169 ; real_T P_170 ;
real_T P_171 ; real_T P_172 ; real_T P_173 ; real_T P_174 ; real_T P_175 ;
real_T P_176 ; real_T P_177 ; real_T P_178 ; real_T P_179 ; real_T P_180 ;
real_T P_181 ; real_T P_182 ; real_T P_183 ; real_T P_184 ; real_T P_185 ;
real_T P_186 ; real_T P_187 ; real_T P_188 ; real_T P_189 ; real_T P_190 ;
real_T P_191 ; void * P_192 ; void * P_193 ; uint32_T P_194 ; uint32_T P_195
; uint32_T P_196 [ 2 ] ; } ; extern P_TruckBenchmark_T
TruckBenchmark_rtDefaultP ; extern const ConstB_TruckBenchmark_T
TruckBenchmark_rtInvariant ;
#endif
