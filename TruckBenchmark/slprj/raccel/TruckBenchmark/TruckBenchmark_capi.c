#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "TruckBenchmark_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 29
#endif
#ifndef SS_INT64
#define SS_INT64 30
#endif
#else
#include "builtin_typeid_types.h"
#include "TruckBenchmark.h"
#include "TruckBenchmark_capi.h"
#include "TruckBenchmark_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 4 , TARGET_STRING (
"TruckBenchmark/Controller/Controller" ) , TARGET_STRING ( "<gear>" ) , 0 , 0
, 0 , 0 , 0 } , { 1 , 7 , TARGET_STRING (
"TruckBenchmark/Controller/Controller" ) , TARGET_STRING ( "<u_vgt>" ) , 1 ,
0 , 0 , 0 , 0 } , { 2 , 7 , TARGET_STRING (
"TruckBenchmark/Controller/Controller" ) , TARGET_STRING ( "<u_egr>" ) , 2 ,
0 , 0 , 0 , 0 } , { 3 , 7 , TARGET_STRING (
"TruckBenchmark/Controller/Controller" ) , TARGET_STRING ( "<u_delta>" ) , 3
, 0 , 0 , 0 , 0 } , { 4 , 7 , TARGET_STRING (
"TruckBenchmark/Controller/Controller" ) , TARGET_STRING ( "<u_brake>" ) , 4
, 0 , 0 , 0 , 0 } , { 5 , 8 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Fuel consumption dm^3//(100km)" ) ,
TARGET_STRING ( "fuelConsumption" ) , 0 , 0 , 0 , 0 , 1 } , { 6 , 0 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Fuel consumption dm^3//(100km)/is_active_c3_TruckBenchmark"
) , TARGET_STRING ( "is_active_c3_TruckBenchmark" ) , 0 , 1 , 0 , 0 , 1 } , {
7 , 12 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Transmission Control Unit" ) , TARGET_STRING (
"clutch_pos" ) , 0 , 0 , 0 , 0 , 2 } , { 8 , 12 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Transmission Control Unit" ) , TARGET_STRING (
"curr_gear" ) , 1 , 0 , 0 , 0 , 2 } , { 9 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Transmission Control Unit/is_active_c2_TruckBenchmark"
) , TARGET_STRING ( "is_active_c2_TruckBenchmark" ) , 0 , 1 , 0 , 0 , 2 } , {
10 , 0 , TARGET_STRING ( "TruckBenchmark/Vehicle Model/Clock" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 11 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/rad//s -> RPM" ) , TARGET_STRING ( "n_engine" )
, 0 , 0 , 0 , 0 , 1 } , { 12 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Memory4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 3 } , { 13 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion10" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 14 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion11" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 15 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion12" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 16 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion13" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 17 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion14" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 18 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion15" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 19 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion16" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 20 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion17" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 21 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion18" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 22 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion19" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 23 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion20" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 24 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion21" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 25 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion22" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 26 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion23" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 27 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion24" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 28 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 29 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion6" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 30 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion7" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 31 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion8" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 32 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Data Type Conversion9" ) ,
TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 4 } , { 33 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Pulse Generator" ) , TARGET_STRING (
"Trigger" ) , 0 , 0 , 0 , 0 , 5 } , { 34 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain1" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 35 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain10" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 4 } , { 36 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain2" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 37 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain3" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 38 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain4" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 39 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain5" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 40 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain6" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 41 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain7" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 4 } , { 42 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain8" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 43 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain9" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 2 } , { 44 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/CAN Pack" ) , TARGET_STRING ( "" ) , 0
, 4 , 0 , 0 , 1 } , { 45 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive1" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 46 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive1" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 47 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive2" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 48 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive2" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 49 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive3" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 50 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive3" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 51 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive3" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 6 } , { 52 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive3" ) , TARGET_STRING ( ""
) , 3 , 0 , 0 , 0 , 6 } , { 53 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive4" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 54 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive4" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 55 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive4" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 6 } , { 56 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive5" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 57 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive5" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 58 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive5" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 6 } , { 59 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive5" ) , TARGET_STRING ( ""
) , 3 , 0 , 0 , 0 , 6 } , { 60 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive5" ) , TARGET_STRING ( ""
) , 4 , 0 , 0 , 0 , 6 } , { 61 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive5" ) , TARGET_STRING ( ""
) , 5 , 0 , 0 , 0 , 6 } , { 62 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive6" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 63 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive6" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 64 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive6" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 6 } , { 65 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive6" ) , TARGET_STRING ( ""
) , 3 , 0 , 0 , 0 , 6 } , { 66 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive6" ) , TARGET_STRING ( ""
) , 4 , 0 , 0 , 0 , 6 } , { 67 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 6 } , { 68 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 1 , 0 , 0 , 0 , 6 } , { 69 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 2 , 0 , 0 , 0 , 6 } , { 70 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 3 , 0 , 0 , 0 , 6 } , { 71 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 4 , 0 , 0 , 0 , 6 } , { 72 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 5 , 0 , 0 , 0 , 6 } , { 73 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 6 , 0 , 0 , 0 , 6 } , { 74 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 7 , 0 , 0 , 0 , 6 } , { 75 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 8 , 0 , 0 , 0 , 6 } , { 76 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 9 , 0 , 0 , 0 , 6 } , { 77 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 10 , 0 , 0 , 0 , 6 } , { 78 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 11 , 0 , 0 , 0 , 6 } , { 79 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 12 , 0 , 0 , 0 , 6 } , { 80 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 13 , 0 , 0 , 0 , 6 } , { 81 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 14 , 0 , 0 , 0 , 6 } , { 82 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 15 , 0 , 0 , 0 , 6 } , { 83 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 16 , 0 , 0 , 0 , 6 } , { 84 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 17 , 0 , 0 , 0 , 6 } , { 85 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 18 , 0 , 0 , 0 , 6 } , { 86 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 Receive7" ) , TARGET_STRING ( ""
) , 19 , 0 , 0 , 0 , 6 } , { 87 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/String to ASCII" ) , TARGET_STRING ( ""
) , 0 , 1 , 2 , 0 , 4 } , { 88 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/String to ASCII1" ) , TARGET_STRING (
"" ) , 0 , 1 , 2 , 0 , 4 } , { 89 , 4 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/Gear control" ) , TARGET_STRING (
"gear" ) , 0 , 0 , 0 , 0 , 0 } , { 90 , 0 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/Gear control/is_active_c5_TruckBenchmark"
) , TARGET_STRING ( "is_active_c5_TruckBenchmark" ) , 0 , 1 , 0 , 0 , 7 } , {
91 , 0 , TARGET_STRING (
 "TruckBenchmark/Controller/Controller/P speed control/is_active_c1_TruckBenchmark"
) , TARGET_STRING ( "is_active_c1_TruckBenchmark" ) , 0 , 1 , 0 , 0 , 7 } , {
92 , 6 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/PI speed control1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 93 , 0 , TARGET_STRING (
 "TruckBenchmark/Controller/Controller/PI speed control1/is_active_c4_TruckBenchmark"
) , TARGET_STRING ( "is_active_c4_TruckBenchmark" ) , 0 , 1 , 0 , 0 , 7 } , {
94 , 7 , TARGET_STRING ( "TruckBenchmark/Controller/Controller/Digital Clock"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 95 , 7 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/Saturation" ) , TARGET_STRING (
"u_delta" ) , 0 , 0 , 0 , 0 , 0 } , { 96 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/F -> M1" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 97 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/m//s -> km//h" ) , TARGET_STRING (
"v_vehicle" ) , 0 , 0 , 0 , 0 , 1 } , { 98 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Integrator1" ) , TARGET_STRING (
"x_distance" ) , 0 , 0 , 0 , 0 , 1 } , { 99 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/MinMax" ) , TARGET_STRING (
"brake_force" ) , 0 , 0 , 0 , 0 , 7 } , { 100 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Equivalent vehicle inertia - J" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 4 } , { 101 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/m g" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 4 } , { 102 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/v [m//s]" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 103 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Sum2" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 104 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer" ) ,
TARGET_STRING ( "M_c" ) , 0 , 0 , 0 , 0 , 1 } , { 105 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits"
) , TARGET_STRING ( "cl_lock" ) , 0 , 0 , 0 , 0 , 3 } , { 106 , 0 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits"
) , TARGET_STRING ( "M_c_max" ) , 1 , 0 , 0 , 0 , 3 } , { 107 , 0 ,
TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Final Drive gear ratio"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 108 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/km//h -> m//s " ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 109 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/Integrator" ) , TARGET_STRING (
"altitude" ) , 0 , 0 , 0 , 0 , 1 } , { 110 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/1-D Lookup Table" ) ,
TARGET_STRING ( "k_slope" ) , 0 , 0 , 0 , 0 , 1 } , { 111 , 0 , TARGET_STRING
( "TruckBenchmark/Vehicle Model/Road Slope Data/h dot" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 112 , 3 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/J1939 CAN Transport Layer1/CAN Receive"
) , TARGET_STRING ( "" ) , 0 , 5 , 0 , 0 , 6 } , { 113 , 3 , TARGET_STRING (
 "TruckBenchmark/Controller/CAN TX//RX/J1939 CAN Transport Layer1/J1939 Transport Layer Transmit"
) , TARGET_STRING ( "" ) , 0 , 5 , 3 , 0 , 6 } , { 114 , 3 , TARGET_STRING (
 "TruckBenchmark/Controller/CAN TX//RX/J1939 CAN Transport Layer1/J1939 Transport Layer Transmit"
) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0 , 6 } , { 115 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Aerodynamic  resistance/0.5*rho_air*A*C_d"
) , TARGET_STRING ( "F_a" ) , 0 , 0 , 0 , 0 , 1 } , { 116 , 0 , TARGET_STRING
( "TruckBenchmark/Vehicle Model/Chassi/Gravitational force/mult2" ) ,
TARGET_STRING ( "F_g" ) , 0 , 0 , 0 , 0 , 1 } , { 117 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Rolling resistance/mult" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 118 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Rolling resistance/mult1" ) ,
TARGET_STRING ( "F_r" ) , 0 , 0 , 0 , 0 , 1 } , { 119 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Rolling resistance/mult2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 120 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Rolling resistance/mult3" ) ,
TARGET_STRING ( "v [km/h]" ) , 0 , 0 , 0 , 0 , 1 } , { 121 , 0 ,
TARGET_STRING ( "TruckBenchmark/Vehicle Model/Chassi/Rolling resistance/Sum1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 122 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer/Abs" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 123 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer/Abs1" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 124 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer/Calc Mc"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 125 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer/Logical Operator"
) , TARGET_STRING ( "" ) , 0 , 2 , 0 , 0 , 3 } , { 126 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Clutch Transfer/Switch"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 127 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Engine Dynamics/Integrator1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 128 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Engine Dynamics/w dot4"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 129 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Engine Dynamics/Sum2" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 130 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Abs"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 131 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Data Type Conversion"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 132 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Maximum Transmissable Clutch Torque"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 133 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Product"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 134 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 135 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 136 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/Integrator"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 137 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/w dot3"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 138 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/w dot5"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 139 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/Sum1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 140 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda" ) , TARGET_STRING (
"lambda" ) , 0 , 0 , 0 , 0 , 1 } , { 141 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Integrator" ) , TARGET_STRING (
"m_fuelTot" ) , 0 , 0 , 0 , 0 , 1 } , { 142 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Fuel Max Torque Limiter" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 143 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/MinMax" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 144 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/W_f" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 145 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Saturation" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 3 } , { 146 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Saturation1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 147 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Sum" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 148 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/Fcn W_egr" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 149 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/PI_egr" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 150 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/Saturation" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 3 } , { 151 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/Switch" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 152 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Fcn" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 153 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Integrator p_em" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 154 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Sum" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 155 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Fcn" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 156 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Integrator p_im" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 157 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/MinMax1" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 158 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Product" ) , TARGET_STRING
( "r_egr" ) , 0 , 0 , 0 , 0 , 1 } , { 159 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Sum" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 160 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Sum1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 161 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/rad//s -> RPM" ) , TARGET_STRING (
"n_t" ) , 0 , 0 , 0 , 0 , 1 } , { 162 , 1 , TARGET_STRING (
 "TruckBenchmark/Controller/CAN TX//RX/J1939 CAN Transport Layer1/CAN Transmit Subsystem/Index Vector"
) , TARGET_STRING ( "" ) , 0 , 5 , 0 , 0 , 0 } , { 163 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder flow/Product W_ei" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 164 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/T1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 165 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/T_1Old"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 166 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/x_rOld"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 3 } , { 167 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/MinMax"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 168 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/PI_e"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 169 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Saturation"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 170 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Saturation1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 171 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/Gain M_e" ) ,
TARGET_STRING ( "M_e" ) , 0 , 0 , 0 , 0 , 1 } , { 172 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/W_fric" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 173 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/W_p" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 174 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 175 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/n_eratio" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 176 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/MinMax" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 177 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/FMEP [bar]" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 178 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/W_ig" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 179 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 180 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/Sum1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 181 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Exhaust temp drop/Fcn T_out" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 182 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda/Fcn" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 183 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda/Max1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 184 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda/MinMax" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 185 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda/lambda" ) , TARGET_STRING (
"r_lambdaOut" ) , 0 , 0 , 0 , 0 , 1 } , { 186 , 9 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Gain" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 187 , 9 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Gain1" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 188 , 9 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Subtract" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 189 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Transport Delay" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 190 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/PSI_egr/Saturation" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 191 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/f_egr/MinMax" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 192 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/f_egr/MinMax1" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 193 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/f_egr/Polynomial" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 194 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Subsystem/Fcn1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 195 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Subsystem/Integrator X_Oem"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 196 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Subsystem X_Oim/Fcn1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 197 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Subsystem X_Oim/Integrator X_Oim"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 198 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Fcn P_c" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 199 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sum" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 200 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Fcn P_t*eta_m" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 201 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Saturation" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 3 } , { 202 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Switch" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 203 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Transport Delay1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 204 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Gain" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 205 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Gain2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 206 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Integrator omega_t" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 207 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Divide" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 208 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Sum" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 209 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Sub T_e/Fcn T_e"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 210 , 0 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/x_r/Fcn x_r"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 211 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator1/Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 212 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator1/Integrator" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 213 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator1/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 214 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator2/Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 215 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator2/Integrator" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 216 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/EGR act/Actuator2/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 217 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub PI_c/MinMax1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 218 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub PI_c/Div PI_c" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 219 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/Fcn W_c" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 220 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/Saturation" ) ,
TARGET_STRING ( "dm_airInlet" ) , 0 , 0 , 0 , 0 , 1 } , { 221 , 0 ,
TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Actuator/Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 222 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Actuator/Integrator" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 223 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Actuator/Sum" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 224 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/PI_t/MinMax" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 225 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/PI_t/Div PI_t" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 226 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/Fcn W_t" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 227 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/BSR" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 228 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/Fcn eta_t" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 229 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/Saturation" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 230 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/Saturation1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 231 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/DeltaT_c/eta_c/Fcn eta_c"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 232 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/DeltaT_c/eta_c/Matrix Gain"
) , TARGET_STRING ( "" ) , 0 , 0 , 4 , 0 , 1 } , { 233 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/DeltaT_c/eta_c/transp" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 5 , 0 , 1 } , { 234 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/DeltaT_c/eta_c/MinMax2" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 235 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/DeltaT_c/eta_c/Product" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 236 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/fcn" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 237 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/fcn1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 238 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/MinMax" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 239 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/MinMax1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 240 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/MinMax2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 241 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/MinMax3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 242 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/c_phi1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 243 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/c_psi1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 244 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/f_vgt/Fcn f_vgt" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 245 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/f_vgt/Fcn1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 246 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/f_vgt/MinMax" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 247 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/f_vgt/MinMax1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 248 , 11 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/c_m/c_m linear" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 249 , 10 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/c_m/c_m power" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 250 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/c_m/MinMax" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 251 , 0 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/c_m/Switch PSI" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 0 , 0 , ( NULL ) , ( NULL ) ,
0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 252 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/rad//s -> RPM" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 253 , TARGET_STRING ( "TruckBenchmark/Vehicle Model/Memory1" )
, TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 254 , TARGET_STRING
( "TruckBenchmark/Vehicle Model/Memory2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 255 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Memory3" ) , TARGET_STRING ( "InitialCondition"
) , 0 , 0 , 0 } , { 256 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant21" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 257 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant22" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 258 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant23" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 259 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant24" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 260 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant25" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 261 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant26" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 262 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant27" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 263 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant28" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 264 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant29" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 265 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant30" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 266 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant32" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 267 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant33" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 268 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant34" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 269 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant35" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 270 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant36" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 271 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant37" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 272 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant38" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 273 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Constant39" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 274 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/dummy 1" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 275 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/dummy 2" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 276 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/dummy 3" ) , TARGET_STRING ( "Value" )
, 0 , 0 , 0 } , { 277 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Pulse Generator" ) , TARGET_STRING (
"Amplitude" ) , 0 , 0 , 0 } , { 278 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Pulse Generator" ) , TARGET_STRING (
"Period" ) , 0 , 0 , 0 } , { 279 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Pulse Generator" ) , TARGET_STRING (
"PulseWidth" ) , 0 , 0 , 0 } , { 280 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Pulse Generator" ) , TARGET_STRING (
"PhaseDelay" ) , 0 , 0 , 0 } , { 281 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain1" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 282 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain10" ) , TARGET_STRING ( "Gain" ) ,
0 , 0 , 0 } , { 283 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain11" ) , TARGET_STRING ( "Gain" ) ,
0 , 0 , 0 } , { 284 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain2" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 285 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain3" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 286 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain4" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 287 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain5" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 288 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain6" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 289 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain7" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 290 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain8" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 291 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/Gain9" ) , TARGET_STRING ( "Gain" ) , 0
, 0 , 0 } , { 292 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/String Constant" ) , TARGET_STRING (
"String" ) , 6 , 0 , 0 } , { 293 , TARGET_STRING (
"TruckBenchmark/Controller/CAN TX//RX/String Constant1" ) , TARGET_STRING (
"String" ) , 6 , 0 , 0 } , { 294 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/gear" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 295 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/u_vgt" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 296 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/u_egr" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 297 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/u_delta" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 298 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/F_brake" ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 299 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/brake" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 300 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 301 , TARGET_STRING (
"TruckBenchmark/Controller/Controller/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 302 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Brake Gain" ) , TARGET_STRING ( "Gain" )
, 0 , 0 , 0 } , { 303 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/m//s -> km//h" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 304 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Integrator1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 305 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Integrator1" ) , TARGET_STRING (
"UpperSaturationLimit" ) , 0 , 0 , 0 } , { 306 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Integrator1" ) , TARGET_STRING (
"LowerSaturationLimit" ) , 0 , 0 , 0 } , { 307 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 308 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 309 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/km//h -> m//s " ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 310 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/1-D Lookup Table" ) ,
TARGET_STRING ( "maxIndex" ) , 3 , 0 , 0 } , { 311 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/1-D Lookup Table" ) ,
TARGET_STRING ( "dimSizes" ) , 3 , 0 , 0 } , { 312 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Road Slope Data/1-D Lookup Table" ) ,
TARGET_STRING ( "numYWorkElts" ) , 3 , 4 , 0 } , { 313 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/Chassi/Rolling resistance/const" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 314 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Engine Dynamics/Integrator1"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 315 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Engine Dynamics/Integrator1"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 316 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Engine Dynamics/Integrator1"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 317 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay1"
) , TARGET_STRING ( "OnSwitchValue" ) , 0 , 0 , 0 } , { 318 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay1"
) , TARGET_STRING ( "OffSwitchValue" ) , 0 , 0 , 0 } , { 319 , TARGET_STRING
(
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay1"
) , TARGET_STRING ( "OnOutputValue" ) , 0 , 0 , 0 } , { 320 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay1"
) , TARGET_STRING ( "OffOutputValue" ) , 0 , 0 , 0 } , { 321 , TARGET_STRING
(
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay2"
) , TARGET_STRING ( "OnSwitchValue" ) , 0 , 0 , 0 } , { 322 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay2"
) , TARGET_STRING ( "OffSwitchValue" ) , 0 , 0 , 0 } , { 323 , TARGET_STRING
(
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay2"
) , TARGET_STRING ( "OnOutputValue" ) , 0 , 0 , 0 } , { 324 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Relay2"
) , TARGET_STRING ( "OffOutputValue" ) , 0 , 0 , 0 } , { 325 , TARGET_STRING
(
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/Integrator"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 326 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/Integrator"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 327 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Vehicle Dynamics/Integrator"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 328 ,
TARGET_STRING ( "TruckBenchmark/Vehicle Model/ICE/Cylinder/Integrator" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 329 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 330 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 331 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Saturation1" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 332 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Saturation1" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 333 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/Saturation" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 334 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/Saturation" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 335 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/Switch" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 336 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 337 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/rad//s -> RPM" ) , TARGET_STRING (
"Gain" ) , 0 , 0 , 0 } , { 338 , TARGET_STRING (
 "TruckBenchmark/Controller/CAN TX//RX/J1939 CAN Transport Layer1/J1939 Transport Layer Receive Subsystem/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 339 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/Clutch and Transmission/Speed Difference Clutch Limits/Compare To Zero/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 340 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Constant"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 341 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Saturation"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 342 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Saturation"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 343 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Saturation1"
) , TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 344 , TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder temp (one iter with delay)/Saturation1"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 345 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 346 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 347 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/Gain M_e" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 348 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/Cylinder torque/n_eratio" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 349 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda/Constant2" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 350 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Cylinder/lambda/Fuel Limit" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 351 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/PSI_egr/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 352 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/f_egr/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 353 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/EGR-system/f_egr/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 354 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Subsystem/Integrator X_Oem"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 355 ,
TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Subsystem/Integrator X_Oem"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 356 ,
TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Exhaust Manifold/Subsystem/Integrator X_Oem"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 357 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Subsystem X_Oim/Integrator X_Oim"
) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 358 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Subsystem X_Oim/Integrator X_Oim"
) , TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 359 ,
TARGET_STRING (
 "TruckBenchmark/Vehicle Model/ICE/Intake Manifold/Subsystem X_Oim/Integrator X_Oim"
) , TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 360 ,
TARGET_STRING ( "TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Saturation" )
, TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 361 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Saturation" ) , TARGET_STRING
( "LowerLimit" ) , 0 , 0 , 0 } , { 362 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Switch" ) , TARGET_STRING (
"Threshold" ) , 0 , 0 , 0 } , { 363 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Gain2" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 364 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Integrator omega_t" ) ,
TARGET_STRING ( "UpperSaturationLimit" ) , 0 , 0 , 0 } , { 365 ,
TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbo inertia/Integrator omega_t" ) ,
TARGET_STRING ( "LowerSaturationLimit" ) , 0 , 0 , 0 } , { 366 ,
TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub PI_c/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 367 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/Saturation" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 368 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/Saturation" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 369 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/PI_t/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 370 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/Saturation" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 371 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/Saturation1" ) ,
TARGET_STRING ( "UpperLimit" ) , 0 , 0 , 0 } , { 372 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/Saturation1" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 373 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/DeltaT_c/eta_c/Constant2"
) , TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 374 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/Constant" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 375 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/Constant1" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 376 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/Constant2" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 377 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Compressor/Sub W_c/PHI_c/Constant3" )
, TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 378 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/f_vgt/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 379 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/Sub W_t/f_vgt/Constant1" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 380 , TARGET_STRING (
"TruckBenchmark/Vehicle Model/ICE/Turbo/Turbine/eta_tm/c_m/Constant" ) ,
TARGET_STRING ( "Value" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 } } ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 ,
( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 381 , TARGET_STRING (
"scenario" ) , 8 , 0 , 0 } , { 382 , TARGET_STRING ( "road" ) , 7 , 0 , 0 } ,
{ 383 , TARGET_STRING ( "model" ) , 13 , 0 , 0 } , { 384 , TARGET_STRING (
"control" ) , 14 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . n22fqqxpxo , & rtB . d3yr0hfu1a ,
& rtB . j2q40ay2j1 , & rtB . kc4ngec1x5 , & rtB . b0oj4tfbt4 , & rtB .
eq0q3y5jp5 , & rtDW . pe5pl50ynw , & rtB . nmprwynq2w , & rtB . n0gg0eojnl ,
& rtDW . pu1q4zlmwb , & rtB . ha4qtjrmin , & rtB . hc01pdzof3 , & rtB .
gze5jcom5s , & rtB . l0kuu0ds13 , & rtB . a33eudfoqk , & rtB . dn5b4tnvem , &
rtB . bmptpxj5fu , & rtB . p5dhuulwqq , & rtB . dlya0nsoeh , & rtB .
jro4altozu , & rtB . lq3cbmwulo , & rtB . d4bourvq1r , & rtB . eskiwmqp4i , &
rtB . hzphm3vuhc , & rtB . bajmf2pksh , & rtB . bk2poabk1f , & rtB .
awfdpaljkk , & rtB . klnxngbb1k , & rtB . deirtazmpx , & rtB . efkmx5vf54 , &
rtB . kvxbfpgjze , & rtB . d4fubsaq1v , & rtB . ooofdxrsnp , & rtB .
nnky4aaqaz , & rtB . d33i42nznw , & rtB . k4n1klhres , & rtB . hrozmhet10 , &
rtB . kpnuhs4yan , & rtB . ai3npgqmd0 , & rtB . kp3tvzs4pj , & rtB .
paczzqkqdw , & rtB . fgbfua1b4j , & rtB . gs1ggdpy4b , & rtB . diwh55j5zr , &
rtB . pdpozm2pyi , & rtB . ddfsxk3pjm , & rtB . nxqvmomv1r , & rtB .
l2hnvs30zp , & rtB . cgnmu1btuu , & rtB . klpxz3py2k , & rtB . dvczlbyjax , &
rtB . bkoec5z0bm , & rtB . bfe1jqp3ql , & rtB . icjifd4a3j , & rtB .
aur1x2p4r3 , & rtB . lsjheazm1j , & rtB . efe3nojiks , & rtB . kifydbwdix , &
rtB . lcaei1u3tp , & rtB . mkgmrqsz4m , & rtB . h3rgiaase1 , & rtB .
cumj2jjpd3 , & rtB . omvi4tphx3 , & rtB . gmmxsb1ncz , & rtB . anky1mhun4 , &
rtB . mko4spaqlt , & rtB . caa50ajekj , & rtB . ejfqwmdcba , & rtB .
cjmcjehzib , & rtB . lxhopxto0a , & rtB . iwgroxai2r , & rtB . mlhy3nfifs , &
rtB . hplgmt4cua , & rtB . nvztpo42zx , & rtB . paqrt3aosc , & rtB .
k13vzx0oza , & rtB . bwddlbipky , & rtB . j1c35nbnvo , & rtB . bt0yraf3qh , &
rtB . lrkl1f4nyq , & rtB . fpsp5e4daw , & rtB . ooztqypzjf , & rtB .
faymzhlev0 , & rtB . gy11xlunmk , & rtB . o44mkznquh , & rtB . hjdh45uyy1 , &
rtB . cb4di0dti4 , & rtB . kminp3y1kp [ 0 ] , & rtB . fvm1pndj51 [ 0 ] , &
rtB . n22fqqxpxo , & rtDW . e4lgtlqce2 , & rtDW . mnycq5gn5i , & rtB .
e10ply524g , & rtDW . eda54vucfl , & rtB . m1vu5h1j0f , & rtB . kc4ngec1x5 ,
& rtB . dwqarhpyfj , & rtB . bmo2rqwngx , & rtB . pd4h1x0zka , & rtB .
k2q4u3lafs , & rtB . mms3wxyzqm , & rtB . abyfl0makg , & rtB . fegajgngwz , &
rtB . mvg3ssqh31 , & rtB . kny5u5cuyg , & rtB . p0pelhou1r , & rtB .
mtgpjerup5 , & rtB . ouddd1bq5c , & rtB . lcmzvp5mvt , & rtB . ksirzoklu3 , &
rtB . ldefe4o41v , & rtB . ayyewbsw5d , & rtB . hic4phvehd , & rtB .
cua1wzatht [ 0 ] , & rtB . ffstplvowd , & rtB . bbjwnzbysv , & rtB .
bk4hs1x304 , & rtB . okv40fdgvu , & rtB . oeo3ys3ci4 , & rtB . omwgk4e1kl , &
rtB . ay21w05qrx , & rtB . hwekqshicu , & rtB . jzm0xgagji , & rtB .
iwb3403aih , & rtB . iinqiuxn3i , & rtB . dtbeclhhb3 , & rtB . kny5u5cuyg , &
rtB . pgdssncn1o , & rtB . n0czoqzhzp , & rtB . pyprhl40ct , & rtB .
jzkj5ctoqn , & rtB . pobigfdmnk , & rtB . ewquelfwcj , & rtB . mtgpjerup5 , &
rtB . p0pelhou1r , & rtB . aiuwtukjl2 , & rtB . fefmeddlto , & rtB .
dcjlzvgjdk , & rtB . onmzapip3s , & rtB . fwampsknte , & rtB . otng3qjdpw , &
rtB . j1zi0jrhi4 , & rtB . et2uhmlji2 , & rtB . ds5nytnni5 , & rtB .
hr10hckzct , & rtB . fagi55uakt , & rtB . h1jzkaxeay , & rtB . forqmcoyzl , &
rtB . eixkduik4f , & rtB . lx4vqnwa25 , & rtB . mtn4j2z4x0 , & rtB .
kaqpmomne3 , & rtB . obqy5rqktf , & rtB . nvtq3ka1ru , & rtB . kwjng0hwid , &
rtB . blszti35p5 , & rtB . kiwuycktce , & rtB . ja1ga1numg , & rtB .
bvz3zvgshe , & rtB . kyljpuifbw , & rtB . drzrfcyncc , & rtB . pcmk2laltd , &
rtB . fqxly0svox , & rtB . kzvckvcpof , & rtB . did2wrnqd3 , & rtB .
njcgrc3zvm , & rtB . fitzivdg3v , & rtB . pgniezqsr0 , & rtB . aw3ze00r1f , &
rtB . l2ijibgtxt , & rtB . j51psxbbsa , & rtB . ibko4nml5o , & rtB .
evvikftrhr , & rtB . opyybpyray , & rtB . b4k3rvzg1m , & rtB . fp2bci2nfq , &
rtB . ktvccmzbfr , & rtB . f04oqjsfjx , & rtB . hotpdqr22m , & rtB .
ky5hu1sl5r , & rtB . ly5zsvwobo , & rtB . linntx1wlj , & rtB . k5zbpv0nhl , &
rtB . jyisic03f3 , & rtB . eqthr4105d , & rtB . otng3qjdpw , & rtB .
elz2or5t0r , & rtB . mbcrayrbd0 , & rtB . mb3bxfx2lb , & rtB . ahq1w0grid , &
rtB . hniruipvai , & rtB . beztzub33z , & rtB . px4ho0kp5r , & rtB .
fnlh0owg0m , & rtB . j2u4yltrpp , & rtB . dq2gexc5is , & rtB . jx23xarepd , &
rtB . ogasawbx31 , & rtB . m0hw1e23zq , & rtB . llwhjyi5kh , & rtB .
fn1q2rgqt1 , & rtB . ko0hu3j2c1 , & rtB . niafhsfiuh , & rtB . izbygssgku , &
rtB . oahz3ap5xd , & rtB . egpw0yftwz , & rtB . c0cwgduetq , & rtB .
ks5oubt5ho , & rtB . nawvezg5up , & rtB . k5apsyzoda , & rtB . k2xcyxwsbw , &
rtB . ojsnbdpor2 , & rtB . ihfhxuyjzv , & rtB . orgilm5inb , & rtB .
kntt0fbjnf , & rtB . cofo4dglob , & rtB . nlmicoqsbz , & rtB . ig3aydedki , &
rtB . bdsfootlbo , & rtB . fzqijlk23t , & rtB . hmqeokdrxe , & rtB .
n5mu2ryb4f , & rtB . kbxdatlwxl , & rtB . kadspyijan , & rtB . jfjgbdkox2 , &
rtB . os3kqcyax0 , & rtB . ivokndy15y , & rtB . cyuyr3knsa , & rtB .
b1uoph40ee , & rtB . ig43bemqvs , & rtB . p1pmwhnw1j , & rtB . hrhovrq2gk , &
rtB . hmrufe3ypk [ 0 ] , & rtB . oat5nwyvfb [ 0 ] , & rtB . mqo4dyjf2d , &
rtB . dnrdowihpt , & rtB . mocnuvcpgp , & rtB . lsrw5owmej , & rtB .
laxl1bi23g , & rtB . bahf0ftnyg , & rtB . jdemdb52qn , & rtB . ebhzjlfncx , &
rtB . nyt5uikcfo , & rtB . egg3t2uoo3 , & rtB . fgov33fphh , & rtB .
denq2sx3ui , & rtB . iuxkrw4e5c , & rtB . pzxkphoemf , & rtB . gpuw4gaeyd , &
rtB . dxjp03lei3 , & rtB . npvqij5mhv , & rtB . flepa2gomd , & rtP .
radsRPM_Gain , & rtP . Memory1_InitialCondition , & rtP .
Memory2_InitialCondition , & rtP . Memory3_InitialCondition , & rtP .
Constant21_Value , & rtP . Constant22_Value , & rtP . Constant23_Value , &
rtP . Constant24_Value , & rtP . Constant25_Value , & rtP . Constant26_Value
, & rtP . Constant27_Value , & rtP . Constant28_Value , & rtP .
Constant29_Value , & rtP . Constant30_Value , & rtP . Constant32_Value , &
rtP . Constant33_Value , & rtP . Constant34_Value , & rtP . Constant35_Value
, & rtP . Constant36_Value , & rtP . Constant37_Value , & rtP .
Constant38_Value , & rtP . Constant39_Value , & rtP . dummy1_Value , & rtP .
dummy2_Value , & rtP . dummy3_Value , & rtP . PulseGenerator_Amp , & rtP .
PulseGenerator_Period , & rtP . PulseGenerator_Duty , & rtP .
PulseGenerator_PhaseDelay , & rtP . Gain1_Gain , & rtP . Gain10_Gain , & rtP
. Gain11_Gain , & rtP . Gain2_Gain , & rtP . Gain3_Gain , & rtP . Gain4_Gain
, & rtP . Gain5_Gain , & rtP . Gain6_Gain , & rtP . Gain7_Gain , & rtP .
Gain8_Gain , & rtP . Gain9_Gain , & rtP . StringConstant_String , & rtP .
StringConstant1_String , & rtP . gear_Y0 , & rtP . u_vgt_Y0 , & rtP .
u_egr_Y0 , & rtP . u_delta_Y0 , & rtP . F_brake_Y0 , & rtP . brake_Value , &
rtP . Saturation_UpperSat , & rtP . Saturation_LowerSat , & rtP .
BrakeGain_Gain , & rtP . mskmh_Gain , & rtP . Integrator1_IC , & rtP .
Integrator1_UpperSat , & rtP . Integrator1_LowerSat , & rtP .
Saturation_UpperSat_fgktzvfm2k , & rtP . Saturation_LowerSat_eegm4iokxr , &
rtP . kmhms_Gain , & rtP . uDLookupTable_maxIndex , & rtP .
uDLookupTable_dimSizes , & rtP . uDLookupTable_numYWorkElts [ 0 ] , & rtP .
const_Value , & rtP . Integrator1_IC_mck3mtbbq3 , & rtP .
Integrator1_UpperSat_pktoycczal , & rtP . Integrator1_LowerSat_ofks0duo33 , &
rtP . Relay1_OnVal , & rtP . Relay1_OffVal , & rtP . Relay1_YOn , & rtP .
Relay1_YOff , & rtP . Relay2_OnVal , & rtP . Relay2_OffVal , & rtP .
Relay2_YOn , & rtP . Relay2_YOff , & rtP . Integrator_IC , & rtP .
Integrator_UpperSat , & rtP . Integrator_LowerSat , & rtP .
Integrator_IC_ikgusueg51 , & rtP . Saturation_UpperSat_atvgvohnm4 , & rtP .
Saturation_LowerSat_bnot2t5v4i , & rtP . Saturation1_UpperSat , & rtP .
Saturation1_LowerSat , & rtP . Saturation_UpperSat_enesi2iumz , & rtP .
Saturation_LowerSat_bn3le4gtty , & rtP . Switch_Threshold , & rtP .
Constant1_Value_fe1czv4ovb , & rtP . radsRPM_Gain_edopox2oep , & rtP .
Constant_Value , & rtP . Constant_Value_eler4bv4qe , & rtP .
Constant_Value_b5ccgfu4yk , & rtP . Saturation_UpperSat_ehbc0hou2u , & rtP .
Saturation_LowerSat_e2gfsq1ep3 , & rtP . Saturation1_UpperSat_haikx2purp , &
rtP . Saturation1_LowerSat_ja3qpjhkdu , & rtP . Constant_Value_nm5d5hyfni , &
rtP . Constant2_Value , & rtP . GainM_e_Gain , & rtP . n_eratio_Gain , & rtP
. Constant2_Value_c3vhbw33ec , & rtP . FuelLimit_Value , & rtP .
Saturation_UpperSat_hto0bhsqhd , & rtP . Constant_Value_gcvl5az0p5 , & rtP .
Constant1_Value , & rtP . IntegratorX_Oem_IC , & rtP .
IntegratorX_Oem_UpperSat , & rtP . IntegratorX_Oem_LowerSat , & rtP .
IntegratorX_Oim_IC , & rtP . IntegratorX_Oim_UpperSat , & rtP .
IntegratorX_Oim_LowerSat , & rtP . Saturation_UpperSat_imjkncmbbp , & rtP .
Saturation_LowerSat_jenqmbtgcj , & rtP . Switch_Threshold_oyf5ishr1i , & rtP
. Gain2_Gain_jj2oxunwb2 , & rtP . Integratoromega_t_UpperSat , & rtP .
Integratoromega_t_LowerSat , & rtP . Constant1_Value_foo0ytc1ur , & rtP .
Saturation_UpperSat_i32xa2dnvv , & rtP . Saturation_LowerSat_f5etl5uivq , &
rtP . Constant_Value_dwh2dts0z5 , & rtP . Saturation_LowerSat_kzgxh2ssqh , &
rtP . Saturation1_UpperSat_pjh2z4fnof , & rtP .
Saturation1_LowerSat_o3inkji2se , & rtP . Constant2_Value_imre1apqn2 , & rtP
. Constant_Value_cfl4aorgnt , & rtP . Constant1_Value_kvscu5x5rd , & rtP .
Constant2_Value_dfqgdtofyy , & rtP . Constant3_Value , & rtP .
Constant_Value_pi0lofejm1 , & rtP . Constant1_Value_cjbf34ugrc , & rtP .
Constant_Value_ajsql1lpqg , & rtP . scenario , & rtP . road , & rtP . model ,
& rtP . control , } ; static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } ,
{ "unsigned char" , "uint8_T" , 0 , 0 , sizeof ( uint8_T ) , ( uint8_T )
SS_UINT8 , 0 , 0 , 0 } , { "unsigned char" , "boolean_T" , 0 , 0 , sizeof (
boolean_T ) , ( uint8_T ) SS_BOOLEAN , 0 , 0 , 0 } , { "unsigned int" ,
"uint32_T" , 0 , 0 , sizeof ( uint32_T ) , ( uint8_T ) SS_UINT32 , 0 , 0 , 0
} , { "struct" , "CAN_MESSAGE_BUS" , 7 , 1 , sizeof ( CAN_MESSAGE_BUS ) , (
uint8_T ) SS_STRUCT , 0 , 0 , 0 } , { "numeric" , "CAN_DATATYPE" , 0 , 0 ,
sizeof ( CAN_DATATYPE ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , { "numeric" ,
"pointer_T" , 0 , 0 , sizeof ( pointer_T ) , ( uint8_T ) SS_POINTER , 0 , 0 ,
0 } , { "struct" , "struct_AgOSJRrmuL6uVtDSBEmT8F" , 2 , 8 , sizeof (
struct_AgOSJRrmuL6uVtDSBEmT8F ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_gwPC03F18UUnIJczODLOeC" , 6 , 10 , sizeof (
struct_gwPC03F18UUnIJczODLOeC ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_viKi95lWyopdIho8t2U8eB" , 3 , 16 , sizeof (
struct_viKi95lWyopdIho8t2U8eB ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_WiP9horN26ElKVOW4YTxdC" , 8 , 19 , sizeof (
struct_WiP9horN26ElKVOW4YTxdC ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_Jff5mszvfldlVC6RiPMV3C" , 1 , 27 , sizeof (
struct_Jff5mszvfldlVC6RiPMV3C ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_O5m41ToDtdmOFFdeNwuUzD" , 74 , 28 , sizeof (
struct_O5m41ToDtdmOFFdeNwuUzD ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_EUK64LV9KqFNVcz2dp6tHB" , 4 , 102 , sizeof (
struct_EUK64LV9KqFNVcz2dp6tHB ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } , {
"struct" , "struct_8L4f4gB0y0ox512d7wKmvG" , 7 , 106 , sizeof (
struct_8L4f4gB0y0ox512d7wKmvG ) , ( uint8_T ) SS_STRUCT , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , { "Extended" , rt_offsetof ( CAN_MESSAGE_BUS , Extended ) , 1 ,
0 , 0 } , { "Length" , rt_offsetof ( CAN_MESSAGE_BUS , Length ) , 1 , 0 , 0 }
, { "Remote" , rt_offsetof ( CAN_MESSAGE_BUS , Remote ) , 1 , 0 , 0 } , {
"Error" , rt_offsetof ( CAN_MESSAGE_BUS , Error ) , 1 , 0 , 0 } , { "ID" ,
rt_offsetof ( CAN_MESSAGE_BUS , ID ) , 3 , 0 , 0 } , { "Timestamp" ,
rt_offsetof ( CAN_MESSAGE_BUS , Timestamp ) , 0 , 0 , 0 } , { "Data" ,
rt_offsetof ( CAN_MESSAGE_BUS , Data ) , 1 , 1 , 0 } , { "k_slopeVector" ,
rt_offsetof ( struct_AgOSJRrmuL6uVtDSBEmT8F , k_slopeVector ) , 0 , 7 , 0 } ,
{ "x_distanceVector" , rt_offsetof ( struct_AgOSJRrmuL6uVtDSBEmT8F ,
x_distanceVector ) , 0 , 7 , 0 } , { "v_init" , rt_offsetof (
struct_gwPC03F18UUnIJczODLOeC , v_init ) , 0 , 6 , 0 } , { "gear_init" ,
rt_offsetof ( struct_gwPC03F18UUnIJczODLOeC , gear_init ) , 0 , 6 , 0 } , {
"vehicleMass" , rt_offsetof ( struct_gwPC03F18UUnIJczODLOeC , vehicleMass ) ,
0 , 6 , 0 } , { "v_set" , rt_offsetof ( struct_gwPC03F18UUnIJczODLOeC , v_set
) , 0 , 6 , 0 } , { "road" , rt_offsetof ( struct_gwPC03F18UUnIJczODLOeC ,
road ) , 7 , 6 , 0 } , { "h_0" , rt_offsetof ( struct_gwPC03F18UUnIJczODLOeC
, h_0 ) , 0 , 6 , 0 } , { "r_gearNumbers" , rt_offsetof (
struct_viKi95lWyopdIho8t2U8eB , r_gearNumbers ) , 0 , 8 , 0 } , {
"r_gearRatios" , rt_offsetof ( struct_viKi95lWyopdIho8t2U8eB , r_gearRatios )
, 0 , 8 , 0 } , { "i_f" , rt_offsetof ( struct_viKi95lWyopdIho8t2U8eB , i_f )
, 0 , 6 , 0 } , { "r_w" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , r_w )
, 0 , 6 , 0 } , { "C_d" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , C_d )
, 0 , 6 , 0 } , { "g" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , g ) , 0
, 6 , 0 } , { "m" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , m ) , 0 , 6
, 0 } , { "A" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , A ) , 0 , 6 , 0
} , { "c_r0" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , c_r0 ) , 0 , 6 ,
0 } , { "c_r1" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , c_r1 ) , 0 , 6
, 0 } , { "rho" , rt_offsetof ( struct_WiP9horN26ElKVOW4YTxdC , rho ) , 0 , 6
, 0 } , { "M_max" , rt_offsetof ( struct_Jff5mszvfldlVC6RiPMV3C , M_max ) , 0
, 6 , 0 } , { "c_pa" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_pa ) ,
0 , 6 , 0 } , { "c_pe" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_pe )
, 0 , 6 , 0 } , { "R_a" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , R_a )
, 0 , 6 , 0 } , { "R_e" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , R_e )
, 0 , 6 , 0 } , { "c_va" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_va
) , 0 , 6 , 0 } , { "c_ve" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
c_ve ) , 0 , 6 , 0 } , { "gamma_a" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , gamma_a ) , 0 , 6 , 0 } , { "gamma_e" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , gamma_e ) , 0 , 6 , 0 } , {
"gamma_c" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , gamma_c ) , 0 , 6 ,
0 } , { "T_amb" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , T_amb ) , 0 ,
6 , 0 } , { "p_amb" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , p_amb ) ,
0 , 6 , 0 } , { "V_im" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , V_im )
, 0 , 6 , 0 } , { "p_im_Init" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
p_im_Init ) , 0 , 6 , 0 } , { "T_im" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , T_im ) , 0 , 6 , 0 } , { "V_em" , rt_offsetof
( struct_O5m41ToDtdmOFFdeNwuUzD , V_em ) , 0 , 6 , 0 } , { "p_em_Init" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , p_em_Init ) , 0 , 6 , 0 } , {
"r_c" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , r_c ) , 0 , 6 , 0 } , {
"V_d" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , V_d ) , 0 , 6 , 0 } , {
"q_HV" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , q_HV ) , 0 , 6 , 0 } ,
{ "AFs" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , AFs ) , 0 , 6 , 0 } ,
{ "n_cyl" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , n_cyl ) , 0 , 6 , 0
} , { "T_w" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , T_w ) , 0 , 6 , 0
} , { "d_pipe" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , d_pipe ) , 0 ,
6 , 0 } , { "l_pipe" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , l_pipe )
, 0 , 6 , 0 } , { "n_pipe" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
n_pipe ) , 0 , 6 , 0 } , { "R_c" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , R_c ) , 0 , 6 , 0 } , { "c_psi2" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_psi2 ) , 0 , 6 , 0 } , {
"c_phi2" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_phi2 ) , 0 , 6 , 0
} , { "c_wpsiVec" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_wpsiVec )
, 0 , 9 , 0 } , { "c_wphiVec" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
c_wphiVec ) , 0 , 9 , 0 } , { "Q_c" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , Q_c ) , 0 , 10 , 0 } , { "eta_cmax" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , eta_cmax ) , 0 , 6 , 0 } , {
"w_copt" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , w_copt ) , 0 , 6 , 0
} , { "pi_copt" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , pi_copt ) , 0
, 6 , 0 } , { "c_volVec" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
c_volVec ) , 0 , 11 , 0 } , { "T_1_Init" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , T_1_Init ) , 0 , 6 , 0 } , { "x_r_Init" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , x_r_Init ) , 0 , 6 , 0 } , {
"eta_sc" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , eta_sc ) , 0 , 6 , 0
} , { "x_cv" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , x_cv ) , 0 , 6 ,
0 } , { "h_tot" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , h_tot ) , 0 ,
6 , 0 } , { "eta_igch" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
eta_igch ) , 0 , 6 , 0 } , { "A_egrmax" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , A_egrmax ) , 0 , 6 , 0 } , { "tau_degr" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , tau_degr ) , 0 , 6 , 0 } , {
"uInit_egr" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , uInit_egr ) , 0 ,
6 , 0 } , { "PI_egropt" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
PI_egropt ) , 0 , 6 , 0 } , { "A_vgtmax" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , A_vgtmax ) , 0 , 6 , 0 } , { "R_t" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , R_t ) , 0 , 6 , 0 } , {
"BSR_opt" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , BSR_opt ) , 0 , 6 ,
0 } , { "c_mVec" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_mVec ) , 0
, 9 , 0 } , { "w_tlin" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , w_tlin
) , 0 , 6 , 0 } , { "c_mlin" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
c_mlin ) , 0 , 6 , 0 } , { "tau_vgt" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , tau_vgt ) , 0 , 6 , 0 } , { "uInit_vgt" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , uInit_vgt ) , 0 , 6 , 0 } , {
"K_t" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , K_t ) , 0 , 6 , 0 } , {
"c_f1" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_f1 ) , 0 , 6 , 0 } ,
{ "c_f2" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_f2 ) , 0 , 6 , 0 }
, { "c_vgt1" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_vgt1 ) , 0 , 6
, 0 } , { "c_vgt2" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_vgt2 ) ,
0 , 6 , 0 } , { "J_t" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , J_t ) ,
0 , 6 , 0 } , { "omega_t_Init" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD
, omega_t_Init ) , 0 , 6 , 0 } , { "c_egr" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , c_egr ) , 0 , 11 , 0 } , { "eta_tmmax" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , eta_tmmax ) , 0 , 6 , 0 } , {
"tau_egr1" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , tau_egr1 ) , 0 , 6
, 0 } , { "tau_egr2" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , tau_egr2
) , 0 , 6 , 0 } , { "K_egr" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
K_egr ) , 0 , 6 , 0 } , { "tau_dvgt" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , tau_dvgt ) , 0 , 6 , 0 } , { "X_Oc" ,
rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , X_Oc ) , 0 , 6 , 0 } , { "c_pi"
, rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_pi ) , 0 , 6 , 0 } , {
"c_fricVec" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , c_fricVec ) , 0 ,
11 , 0 } , { "J_e" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD , J_e ) , 0
, 6 , 0 } , { "limit_n_e" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
limit_n_e ) , 0 , 12 , 0 } , { "limit_m_f" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , limit_m_f ) , 0 , 12 , 0 } , {
"with_egr_act_model" , rt_offsetof ( struct_O5m41ToDtdmOFFdeNwuUzD ,
with_egr_act_model ) , 0 , 6 , 0 } , { "with_vgt_act_model" , rt_offsetof (
struct_O5m41ToDtdmOFFdeNwuUzD , with_vgt_act_model ) , 0 , 6 , 0 } , {
"transmission" , rt_offsetof ( struct_EUK64LV9KqFNVcz2dp6tHB , transmission )
, 9 , 6 , 0 } , { "vehicle" , rt_offsetof ( struct_EUK64LV9KqFNVcz2dp6tHB ,
vehicle ) , 10 , 6 , 0 } , { "clutch" , rt_offsetof (
struct_EUK64LV9KqFNVcz2dp6tHB , clutch ) , 11 , 6 , 0 } , { "engine" ,
rt_offsetof ( struct_EUK64LV9KqFNVcz2dp6tHB , engine ) , 12 , 6 , 0 } , {
"u_egract" , rt_offsetof ( struct_8L4f4gB0y0ox512d7wKmvG , u_egract ) , 0 , 6
, 0 } , { "u_vgtact" , rt_offsetof ( struct_8L4f4gB0y0ox512d7wKmvG , u_vgtact
) , 0 , 6 , 0 } , { "u_egr" , rt_offsetof ( struct_8L4f4gB0y0ox512d7wKmvG ,
u_egr ) , 0 , 6 , 0 } , { "u_vgt" , rt_offsetof (
struct_8L4f4gB0y0ox512d7wKmvG , u_vgt ) , 0 , 6 , 0 } , { "Ts" , rt_offsetof
( struct_8L4f4gB0y0ox512d7wKmvG , Ts ) , 0 , 6 , 0 } , { "k_smoke" ,
rt_offsetof ( struct_8L4f4gB0y0ox512d7wKmvG , k_smoke ) , 0 , 6 , 0 } , {
"v_set" , rt_offsetof ( struct_8L4f4gB0y0ox512d7wKmvG , v_set ) , 0 , 6 , 0 }
} ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { { rtwCAPI_SCALAR
, 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR ,
4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } , { rtwCAPI_VECTOR , 8 , 2 , 0 }
, { rtwCAPI_MATRIX_COL_MAJOR , 10 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 0
, 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 12 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 14 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 16 , 2
, 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 18 , 2 , 0 } , {
rtwCAPI_MATRIX_COL_MAJOR , 20 , 2 , 0 } , { rtwCAPI_MATRIX_COL_MAJOR , 22 , 2
, 0 } } ; static const uint_T rtDimensionArray [ ] = { 1 , 1 , 8 , 1 , 1 , 31
, 20 , 1 , 2 , 1 , 1 , 2 , 1 , 9905 , 1 , 15 , 1 , 3 , 2 , 2 , 3 , 1 , 1 , 33
} ; static const real_T rtcapiStoredFloats [ ] = { 0.0 , 2.0E-5 , 1.0 , - 2.0
, 0.00054 } ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , (
NULL ) , rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( NULL ) , ( NULL ) , - 1 , 0
} , { ( const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( int8_T ) 0 , ( uint8_T ) 0 } , { ( const void *
) & rtcapiStoredFloats [ 1 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] ,
( int8_T ) 2 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 0
] , ( const void * ) & rtcapiStoredFloats [ 2 ] , ( int8_T ) 1 , ( uint8_T )
0 } , { ( NULL ) , ( NULL ) , 6 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 3 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , (
int8_T ) 5 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 4 ]
, ( const void * ) & rtcapiStoredFloats [ 0 ] , ( int8_T ) 3 , ( uint8_T ) 0
} , { ( const void * ) & rtcapiStoredFloats [ 2 ] , ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( int8_T ) 4 , ( uint8_T ) 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 252 ,
rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 129 ,
rtModelParameters , 4 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 2564456923U , 14143646U , 2799630258U , 17045496U } , ( NULL ) , 0 , (
boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * TruckBenchmark_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void TruckBenchmark_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void TruckBenchmark_host_InitializeDataMapInfo (
TruckBenchmark_host_DataMapInfo_T * dataMap , const char * path ) {
rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ; rtwCAPI_SetStaticMap ( dataMap ->
mmi , & mmiStatic ) ; rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetPath ( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap ->
mmi , ( NULL ) ) ; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
