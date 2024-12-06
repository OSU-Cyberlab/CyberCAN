#ifndef RTW_HEADER_TruckBenchmark_acc_types_h_
#define RTW_HEADER_TruckBenchmark_acc_types_h_
#include "rtwtypes.h"
#ifndef DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
#define DEFINED_TYPEDEF_FOR_CAN_MESSAGE_BUS_
typedef struct { uint8_T Extended ; uint8_T Length ; uint8_T Remote ; uint8_T
Error ; uint32_T ID ; real_T Timestamp ; uint8_T Data [ 8 ] ; }
CAN_MESSAGE_BUS ;
#endif
typedef struct P_TruckBenchmark_T_ P_TruckBenchmark_T ;
#endif
