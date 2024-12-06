#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } , { "physical_connection" , 14 , 8 } , {
"int64_T" , 15 , 8 } , { "uint64_T" , 16 , 8 } , { "CAN_DATATYPE" , 17 , 24 }
, { "CAN_MESSAGE_BUS" , 18 , 24 } , { "struct_8L4f4gB0y0ox512d7wKmvG" , 19 ,
56 } , { "struct_viKi95lWyopdIho8t2U8eB" , 20 , 248 } , {
"struct_WiP9horN26ElKVOW4YTxdC" , 21 , 64 } , {
"struct_Jff5mszvfldlVC6RiPMV3C" , 22 , 8 } , {
"struct_O5m41ToDtdmOFFdeNwuUzD" , 23 , 1224 } , {
"struct_EUK64LV9KqFNVcz2dp6tHB" , 24 , 1544 } , { "string" , 25 , 8 } , {
"string" , 26 , 8 } , { "struct_AgOSJRrmuL6uVtDSBEmT8F" , 27 , 158480 } , {
"struct_gwPC03F18UUnIJczODLOeC" , 28 , 158520 } , { "uint64_T" , 29 , 8 } , {
"int64_T" , 30 , 8 } , { "uint_T" , 31 , 32 } , { "char_T" , 32 , 8 } , {
"uchar_T" , 33 , 8 } , { "time_T" , 34 , 8 } } ; static uint_T
rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T ) , sizeof (
int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof ( uint16_T ) ,
sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T ) , sizeof (
fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof ( action_T )
, 2 * sizeof ( uint32_T ) , sizeof ( int32_T ) , sizeof ( int64_T ) , sizeof
( uint64_T ) , sizeof ( CAN_DATATYPE ) , sizeof ( CAN_MESSAGE_BUS ) , sizeof
( struct_8L4f4gB0y0ox512d7wKmvG ) , sizeof ( struct_viKi95lWyopdIho8t2U8eB )
, sizeof ( struct_WiP9horN26ElKVOW4YTxdC ) , sizeof (
struct_Jff5mszvfldlVC6RiPMV3C ) , sizeof ( struct_O5m41ToDtdmOFFdeNwuUzD ) ,
sizeof ( struct_EUK64LV9KqFNVcz2dp6tHB ) , 8 , sizeof ( char_T ) , sizeof (
struct_AgOSJRrmuL6uVtDSBEmT8F ) , sizeof ( struct_gwPC03F18UUnIJczODLOeC ) ,
sizeof ( uint64_T ) , sizeof ( int64_T ) , sizeof ( uint_T ) , sizeof (
char_T ) , sizeof ( uchar_T ) , sizeof ( time_T ) } ; static const char_T *
rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" , "uint8_T" ,
"int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" , "fcn_call_T"
, "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" ,
"physical_connection" , "int64_T" , "uint64_T" , "CAN_DATATYPE" ,
"CAN_MESSAGE_BUS" , "struct_8L4f4gB0y0ox512d7wKmvG" ,
"struct_viKi95lWyopdIho8t2U8eB" , "struct_WiP9horN26ElKVOW4YTxdC" ,
"struct_Jff5mszvfldlVC6RiPMV3C" , "struct_O5m41ToDtdmOFFdeNwuUzD" ,
"struct_EUK64LV9KqFNVcz2dp6tHB" , "string" , "string" ,
"struct_AgOSJRrmuL6uVtDSBEmT8F" , "struct_gwPC03F18UUnIJczODLOeC" ,
"uint64_T" , "int64_T" , "uint_T" , "char_T" , "uchar_T" , "time_T" } ;
static DataTypeTransition rtBTransitions [ ] = { { ( char_T * ) ( & rtB .
pdpozm2pyi ) , 18 , 0 , 1 } , { ( char_T * ) ( & rtB . hic4phvehd ) , 17 , 0
, 22 } , { ( char_T * ) ( & rtB . fefmeddlto ) , 0 , 0 , 220 } , { ( char_T *
) ( & rtB . kminp3y1kp [ 0 ] ) , 3 , 0 , 62 } , { ( char_T * ) ( & rtB .
dtbeclhhb3 ) , 8 , 0 , 19 } , { ( char_T * ) ( & rtDW . kpmtixcj35 ) , 0 , 0
, 20104 } , { ( char_T * ) ( & rtDW . ki10t4re5z ) , 15 , 0 , 1 } , { (
char_T * ) ( & rtDW . kgxadfuhgr . modelTStart ) , 0 , 0 , 2 } , { ( char_T *
) ( & rtDW . ckmhctwgle . LoggedData ) , 11 , 0 , 143 } , { ( char_T * ) ( &
rtDW . imduqxhj3y ) , 6 , 0 , 7 } , { ( char_T * ) ( & rtDW . g1tih4iurb ) ,
7 , 0 , 1 } , { ( char_T * ) ( & rtDW . gk4tvjl5km . NODEADDR ) , 10 , 0 , 55
} , { ( char_T * ) ( & rtDW . dbfmnhxbxj ) , 2 , 0 , 3 } , { ( char_T * ) ( &
rtDW . nhh3pckv2z ) , 3 , 0 , 6 } , { ( char_T * ) ( & rtDW . hpyvhbyyfk ) ,
8 , 0 , 20 } } ; static DataTypeTransitionTable rtBTransTable = { 15U ,
rtBTransitions } ; static DataTypeTransition rtPTransitions [ ] = { { (
char_T * ) ( & rtP . scenario ) , 28 , 0 , 1 } , { ( char_T * ) ( & rtP .
road ) , 27 , 0 , 1 } , { ( char_T * ) ( & rtP . model ) , 24 , 0 , 1 } , { (
char_T * ) ( & rtP . control ) , 19 , 0 , 1 } , { ( char_T * ) ( & rtP .
Constant_Value ) , 0 , 0 , 124 } , { ( char_T * ) ( & rtP .
StringConstant_String ) , 11 , 0 , 2 } , { ( char_T * ) ( & rtP .
uDLookupTable_maxIndex ) , 7 , 0 , 4 } } ; static DataTypeTransitionTable
rtPTransTable = { 7U , rtPTransitions } ;
