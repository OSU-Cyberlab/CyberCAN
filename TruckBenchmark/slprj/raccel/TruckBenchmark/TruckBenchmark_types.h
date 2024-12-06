#ifndef RTW_HEADER_TruckBenchmark_types_h_
#define RTW_HEADER_TruckBenchmark_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
#define DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
typedef struct { uint8_T Extended ; uint8_T Length ; uint8_T Remote ; uint8_T
Error ; uint32_T ID ; real_T Timestamp ; uint8_T Data [ 8 ] ; }
CAN_MESSAGE_BUS ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_8L4f4gB0y0ox512d7wKmvG_
#define DEFINED_TYPEDEF_FOR_struct_8L4f4gB0y0ox512d7wKmvG_
typedef struct { real_T u_egract ; real_T u_vgtact ; real_T u_egr ; real_T
u_vgt ; real_T Ts ; real_T k_smoke ; real_T v_set ; }
struct_8L4f4gB0y0ox512d7wKmvG ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_viKi95lWyopdIho8t2U8eB_
#define DEFINED_TYPEDEF_FOR_struct_viKi95lWyopdIho8t2U8eB_
typedef struct { real_T r_gearNumbers [ 15 ] ; real_T r_gearRatios [ 15 ] ;
real_T i_f ; } struct_viKi95lWyopdIho8t2U8eB ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_WiP9horN26ElKVOW4YTxdC_
#define DEFINED_TYPEDEF_FOR_struct_WiP9horN26ElKVOW4YTxdC_
typedef struct { real_T r_w ; real_T C_d ; real_T g ; real_T m ; real_T A ;
real_T c_r0 ; real_T c_r1 ; real_T rho ; } struct_WiP9horN26ElKVOW4YTxdC ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_Jff5mszvfldlVC6RiPMV3C_
#define DEFINED_TYPEDEF_FOR_struct_Jff5mszvfldlVC6RiPMV3C_
typedef struct { real_T M_max ; } struct_Jff5mszvfldlVC6RiPMV3C ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_O5m41ToDtdmOFFdeNwuUzD_
#define DEFINED_TYPEDEF_FOR_struct_O5m41ToDtdmOFFdeNwuUzD_
typedef struct { real_T c_pa ; real_T c_pe ; real_T R_a ; real_T R_e ; real_T
c_va ; real_T c_ve ; real_T gamma_a ; real_T gamma_e ; real_T gamma_c ;
real_T T_amb ; real_T p_amb ; real_T V_im ; real_T p_im_Init ; real_T T_im ;
real_T V_em ; real_T p_em_Init ; real_T r_c ; real_T V_d ; real_T q_HV ;
real_T AFs ; real_T n_cyl ; real_T T_w ; real_T d_pipe ; real_T l_pipe ;
real_T n_pipe ; real_T R_c ; real_T c_psi2 ; real_T c_phi2 ; real_T c_wpsiVec
[ 3 ] ; real_T c_wphiVec [ 3 ] ; real_T Q_c [ 4 ] ; real_T eta_cmax ; real_T
w_copt ; real_T pi_copt ; real_T c_volVec [ 3 ] ; real_T T_1_Init ; real_T
x_r_Init ; real_T eta_sc ; real_T x_cv ; real_T h_tot ; real_T eta_igch ;
real_T A_egrmax ; real_T tau_degr ; real_T uInit_egr ; real_T PI_egropt ;
real_T A_vgtmax ; real_T R_t ; real_T BSR_opt ; real_T c_mVec [ 3 ] ; real_T
w_tlin ; real_T c_mlin ; real_T tau_vgt ; real_T uInit_vgt ; real_T K_t ;
real_T c_f1 ; real_T c_f2 ; real_T c_vgt1 ; real_T c_vgt2 ; real_T J_t ;
real_T omega_t_Init ; real_T c_egr [ 3 ] ; real_T eta_tmmax ; real_T tau_egr1
; real_T tau_egr2 ; real_T K_egr ; real_T tau_dvgt ; real_T X_Oc ; real_T
c_pi ; real_T c_fricVec [ 3 ] ; real_T J_e ; real_T limit_n_e [ 33 ] ; real_T
limit_m_f [ 33 ] ; real_T with_egr_act_model ; real_T with_vgt_act_model ; }
struct_O5m41ToDtdmOFFdeNwuUzD ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_EUK64LV9KqFNVcz2dp6tHB_
#define DEFINED_TYPEDEF_FOR_struct_EUK64LV9KqFNVcz2dp6tHB_
typedef struct { struct_viKi95lWyopdIho8t2U8eB transmission ;
struct_WiP9horN26ElKVOW4YTxdC vehicle ; struct_Jff5mszvfldlVC6RiPMV3C clutch
; struct_O5m41ToDtdmOFFdeNwuUzD engine ; } struct_EUK64LV9KqFNVcz2dp6tHB ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_AgOSJRrmuL6uVtDSBEmT8F_
#define DEFINED_TYPEDEF_FOR_struct_AgOSJRrmuL6uVtDSBEmT8F_
typedef struct { real_T k_slopeVector [ 9905 ] ; real_T x_distanceVector [
9905 ] ; } struct_AgOSJRrmuL6uVtDSBEmT8F ;
#endif
#ifndef DEFINED_TYPEDEF_FOR_struct_gwPC03F18UUnIJczODLOeC_
#define DEFINED_TYPEDEF_FOR_struct_gwPC03F18UUnIJczODLOeC_
typedef struct { real_T v_init ; real_T gear_init ; real_T vehicleMass ;
real_T v_set ; struct_AgOSJRrmuL6uVtDSBEmT8F road ; real_T h_0 ; }
struct_gwPC03F18UUnIJczODLOeC ;
#endif
#ifndef SS_UINT64
#define SS_UINT64 29
#endif
#ifndef SS_INT64
#define SS_INT64 30
#endif
typedef struct P_ P ;
#endif
