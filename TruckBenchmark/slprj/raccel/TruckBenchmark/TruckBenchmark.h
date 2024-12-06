#ifndef RTW_HEADER_TruckBenchmark_h_
#define RTW_HEADER_TruckBenchmark_h_
#ifndef TruckBenchmark_COMMON_INCLUDES_
#define TruckBenchmark_COMMON_INCLUDES_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#include "j1939/cantransportlib.hpp"
#include "j1939/j1939lib.hpp"
#include "can_message.h"
#include "hostlib_vntcan.h"
#include "mexfcns.h"
#endif
#include "TruckBenchmark_types.h"
#include <stddef.h>
#include "rtsplntypes.h"
#include <float.h>
#include "mwmathutil.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#include "rtGetInf.h"
#define MODEL_NAME TruckBenchmark
#define NSAMPLE_TIMES (7) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (243) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (13)   
#elif NCSTATES != 13
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { CAN_MESSAGE_BUS pdpozm2pyi ; CAN_DATATYPE hic4phvehd ;
CAN_DATATYPE cua1wzatht [ 20 ] ; CAN_DATATYPE fqxly0svox ; real_T fefmeddlto
; real_T fegajgngwz ; real_T bmo2rqwngx ; real_T ejfqwmdcba ; real_T
cjmcjehzib ; real_T lxhopxto0a ; real_T iwgroxai2r ; real_T mlhy3nfifs ;
real_T hplgmt4cua ; real_T nvztpo42zx ; real_T paqrt3aosc ; real_T k13vzx0oza
; real_T bwddlbipky ; real_T j1c35nbnvo ; real_T bt0yraf3qh ; real_T
lrkl1f4nyq ; real_T fpsp5e4daw ; real_T ooztqypzjf ; real_T faymzhlev0 ;
real_T gy11xlunmk ; real_T o44mkznquh ; real_T hjdh45uyy1 ; real_T cb4di0dti4
; real_T klpxz3py2k ; real_T dvczlbyjax ; real_T bkoec5z0bm ; real_T
bfe1jqp3ql ; real_T l2hnvs30zp ; real_T cgnmu1btuu ; real_T icjifd4a3j ;
real_T aur1x2p4r3 ; real_T lsjheazm1j ; real_T efe3nojiks ; real_T kifydbwdix
; real_T lcaei1u3tp ; real_T mkgmrqsz4m ; real_T h3rgiaase1 ; real_T
cumj2jjpd3 ; real_T omvi4tphx3 ; real_T gmmxsb1ncz ; real_T anky1mhun4 ;
real_T mko4spaqlt ; real_T caa50ajekj ; real_T pd4h1x0zka ; real_T d33i42nznw
; real_T hrozmhet10 ; real_T nnky4aaqaz ; real_T kpnuhs4yan ; real_T
ai3npgqmd0 ; real_T c0cwgduetq ; real_T kiwuycktce ; real_T bdsfootlbo ;
real_T ig3aydedki ; real_T egg3t2uoo3 ; real_T bahf0ftnyg ; real_T mocnuvcpgp
; real_T laxl1bi23g ; real_T nyt5uikcfo ; real_T ebhzjlfncx ; real_T
lsrw5owmej ; real_T jdemdb52qn ; real_T fzqijlk23t ; real_T hmqeokdrxe ;
real_T paczzqkqdw ; real_T kp3tvzs4pj ; real_T pgdssncn1o ; real_T hc01pdzof3
; real_T gs1ggdpy4b ; real_T gze5jcom5s ; real_T ha4qtjrmin ; real_T
diwh55j5zr ; real_T deirtazmpx ; real_T hzphm3vuhc ; real_T ddfsxk3pjm ;
real_T nxqvmomv1r ; real_T pcmk2laltd ; real_T ihfhxuyjzv ; real_T cofo4dglob
; real_T mtn4j2z4x0 ; real_T kaqpmomne3 ; real_T px4ho0kp5r ; real_T
fnlh0owg0m ; real_T beztzub33z ; real_T nvtq3ka1ru ; real_T lx4vqnwa25 ;
real_T hniruipvai ; real_T aw3ze00r1f ; real_T h1jzkaxeay ; real_T et2uhmlji2
; real_T fagi55uakt ; real_T ds5nytnni5 ; real_T hr10hckzct ; real_T
kzvckvcpof ; real_T fitzivdg3v ; real_T njcgrc3zvm ; real_T k5apsyzoda ;
real_T pgniezqsr0 ; real_T forqmcoyzl ; real_T linntx1wlj ; real_T eixkduik4f
; real_T drzrfcyncc ; real_T bvz3zvgshe ; real_T jyisic03f3 ; real_T
ogasawbx31 ; real_T otng3qjdpw ; real_T ldefe4o41v ; real_T ksirzoklu3 ;
real_T j1zi0jrhi4 ; real_T ktvccmzbfr ; real_T b4k3rvzg1m ; real_T hotpdqr22m
; real_T ky5hu1sl5r ; real_T opyybpyray ; real_T fp2bci2nfq ; real_T
f04oqjsfjx ; real_T evvikftrhr ; real_T ly5zsvwobo ; real_T ibko4nml5o ;
real_T bbjwnzbysv ; real_T k2q4u3lafs ; real_T ay21w05qrx ; real_T okv40fdgvu
; real_T hwekqshicu ; real_T omwgk4e1kl ; real_T oeo3ys3ci4 ; real_T
bk4hs1x304 ; real_T mvg3ssqh31 ; real_T dwqarhpyfj ; real_T ouddd1bq5c ;
real_T iinqiuxn3i ; real_T aiuwtukjl2 ; real_T jzkj5ctoqn ; real_T p0pelhou1r
; real_T jzm0xgagji ; real_T ewquelfwcj ; real_T pobigfdmnk ; real_T
mtgpjerup5 ; real_T iwb3403aih ; real_T kny5u5cuyg ; real_T pyprhl40ct ;
real_T n0czoqzhzp ; real_T dcjlzvgjdk ; real_T fwampsknte ; real_T onmzapip3s
; real_T k2xcyxwsbw ; real_T l2ijibgtxt ; real_T did2wrnqd3 ; real_T
j51psxbbsa ; real_T k5zbpv0nhl ; real_T eqthr4105d ; real_T ahq1w0grid ;
real_T orgilm5inb ; real_T ojsnbdpor2 ; real_T nlmicoqsbz ; real_T kntt0fbjnf
; real_T os3kqcyax0 ; real_T jfjgbdkox2 ; real_T kbxdatlwxl ; real_T
ko0hu3j2c1 ; real_T niafhsfiuh ; real_T denq2sx3ui ; real_T iuxkrw4e5c ;
real_T fgov33fphh ; real_T pzxkphoemf ; real_T ivokndy15y ; real_T kwjng0hwid
; real_T obqy5rqktf ; real_T dq2gexc5is ; real_T j2u4yltrpp ; real_T
kyljpuifbw ; real_T blszti35p5 ; real_T ja1ga1numg ; real_T jx23xarepd ;
real_T gqm1fborqv [ 2 ] ; real_T oat5nwyvfb [ 2 ] ; real_T hmrufe3ypk [ 2 ] ;
real_T dnrdowihpt ; real_T hrhovrq2gk ; real_T mqo4dyjf2d ; real_T m0hw1e23zq
; real_T llwhjyi5kh ; real_T izbygssgku ; real_T kadspyijan ; real_T
n5mu2ryb4f ; real_T npvqij5mhv ; real_T flepa2gomd ; real_T cyuyr3knsa ;
real_T ig43bemqvs ; real_T b1uoph40ee ; real_T p1pmwhnw1j ; real_T fn1q2rgqt1
; real_T nawvezg5up ; real_T ks5oubt5ho ; real_T oahz3ap5xd ; real_T
egpw0yftwz ; real_T lcmzvp5mvt ; real_T ayyewbsw5d ; real_T k4n1klhres ;
real_T fgbfua1b4j ; real_T mms3wxyzqm ; real_T abyfl0makg ; real_T nmprwynq2w
; real_T n0gg0eojnl ; real_T gpuw4gaeyd ; real_T dxjp03lei3 ; real_T
mbcrayrbd0 ; real_T elz2or5t0r ; real_T mb3bxfx2lb ; real_T eq0q3y5jp5 ;
real_T kc4ngec1x5 ; real_T d3yr0hfu1a ; real_T j2q40ay2j1 ; real_T b0oj4tfbt4
; real_T m1vu5h1j0f ; real_T e10ply524g ; real_T n22fqqxpxo ; real_T
ffstplvowd ; uint8_T kminp3y1kp [ 31 ] ; uint8_T fvm1pndj51 [ 31 ] ;
boolean_T dtbeclhhb3 ; boolean_T l0kuu0ds13 ; boolean_T a33eudfoqk ;
boolean_T dn5b4tnvem ; boolean_T bmptpxj5fu ; boolean_T p5dhuulwqq ;
boolean_T dlya0nsoeh ; boolean_T jro4altozu ; boolean_T lq3cbmwulo ;
boolean_T d4bourvq1r ; boolean_T eskiwmqp4i ; boolean_T bajmf2pksh ;
boolean_T bk2poabk1f ; boolean_T awfdpaljkk ; boolean_T klnxngbb1k ;
boolean_T efkmx5vf54 ; boolean_T kvxbfpgjze ; boolean_T d4fubsaq1v ;
boolean_T ooofdxrsnp ; } B ; typedef struct { real_T kpmtixcj35 ; real_T
mluvktfvfy ; real_T jtxmye3nth ; real_T mp0kaoewzv ; real_T l2wwwtxl4l ;
real_T ox1qbuvuuc ; real_T bffjy4cqw3 ; real_T omie0z5rtl ; real_T ltzscgd5af
; real_T iazakfnige ; real_T b1sjehltlg [ 9905 ] ; real_T hmg2uwdzcg [ 9905 ]
; real_T jahel4guj4 ; real_T c1a2ddum24 ; real_T h1t2m1slzp ; real_T
jescywanqo ; real_T n3jvfqlh1d ; real_T jie24f0s0n ; real_T od5y3smrxh ;
real_T bzxfv0jxlh ; real_T ozxovagibo ; real_T o0eadiapoc ; real_T lgjsvdiy5a
[ 137 ] ; real_T ozecqffs1t [ 137 ] ; int64_T ki10t4re5z ; struct { real_T
modelTStart ; } kgxadfuhgr ; struct { real_T modelTStart ; } ldxvb4zcz0 ;
struct { void * LoggedData ; } ckmhctwgle ; struct { void * CONFIGHANDLE ; }
jpjfz2svcl ; struct { void * CONFIGHANDLE ; } kbixsgmskc ; struct { void *
NODEPTR ; void * CONFIGHANDLE ; } maxcur2n31 ; struct { void * NODEPTR ; void
* CONFIGHANDLE ; } alvst5aflb ; struct { void * PGPTR ; void * CONFIGHANDLE ;
} iuixpdicwr ; struct { void * LoggedData ; } dlhpralghu ; struct { void *
LoggedData [ 4 ] ; } m4n4tlm3qw ; struct { void * PGPTR ; void * CONFIGHANDLE
; } kzspl1dppk ; struct { void * PGPTR ; void * CONFIGHANDLE ; } k2kbed5e0t ;
struct { void * PGPTR ; void * CONFIGHANDLE ; } osuhy0wf15 ; struct { void *
PGPTR ; void * CONFIGHANDLE ; } clkxcrhgir ; struct { void * LoggedData ; }
omjkcskvmm ; struct { void * PGPTR ; void * CONFIGHANDLE ; } e3hhsxef2w ;
struct { void * PGPTR ; void * CONFIGHANDLE ; } of3rn5nxd4 ; struct { void *
PGPTR ; void * CONFIGHANDLE ; } bvdrbi2l1c ; struct { void * PGPTR ; void *
CONFIGHANDLE ; } e3ktwiowkd ; struct { void * PGPTR ; void * CONFIGHANDLE ; }
d4x2b0bhgu ; struct { void * PGPTR ; void * CONFIGHANDLE ; } krc0v3lfqy ;
struct { void * PGPTR ; void * CONFIGHANDLE ; } kr1tkdktl0 ; struct { void *
PGPTR ; void * CONFIGHANDLE ; } imsyrbpl23 ; struct { void * LoggedData ; }
pwm5n5vpra ; struct { void * LoggedData [ 4 ] ; } dwf1cmy2ra ; struct { void
* AQHandles ; } gtasy1jsdx ; struct { void * PGPTR ; void * CONFIGHANDLE ; }
ekxqe2lb2z ; void * j2t1smeuiz ; void * bd2sguzpuq [ 6 ] ; void * lqs2eqamfb
[ 9 ] ; struct { void * LoggedData ; } dp3k1dexua ; struct { void *
LoggedData ; } btbog5aing ; struct { void * LoggedData ; } dsrqsv4lmb ;
struct { void * LoggedData ; } acp0df3iba ; struct { void * AQHandles ; }
p33krp3hyb ; struct { void * AQHandles ; } dzibnwkozv ; struct { void *
AQHandles ; } m2ysthz4lp ; struct { void * AQHandles ; } ltc2bikvjk ; struct
{ void * AQHandles ; } fwhtblllbe ; struct { void * AQHandles ; } kyvzs2v1y5
; struct { void * AQHandles ; } a5wlo524la ; struct { void * AQHandles ; }
osoqnotoxt ; struct { void * AQHandles ; } afai5j1n5f ; struct { void *
AQHandles ; } gtasy1jsdxk ; struct { void * AQHandles ; } jtwmyt455q ; struct
{ void * TUbufferPtrs [ 2 ] ; } k4tau4hadb ; struct { void * TUbufferPtrs [ 2
] ; } hku5cqszwy ; struct { void * LoggedData ; } fmunnl32cm ; struct { void
* LoggedData ; } ikortawjg0 ; struct { void * AQHandles ; } o0cbjrpiwk ;
struct { void * AQHandles ; } dakk2fhtjk ; struct { void * LoggedData ; }
nbxezyhs1i ; struct { void * AQHandles ; } bzrmj3zxqu ; struct { void *
AQHandles ; } pudhr5q1sv ; struct { void * LoggedData ; } bp4u12rzh4 ; struct
{ void * AQHandles ; } ahb0xajdg5 ; struct { void * LoggedData ; } kfghz55atc
; struct { void * AQHandles ; } jj02cyrtix ; struct { void * LoggedData ; }
dbvexqyya2 ; struct { void * AQHandles ; } mduldnxlmb ; struct { void *
LoggedData ; } oz0i0yjqqd ; struct { void * AQHandles ; } o2domeg4ik ; struct
{ void * LoggedData ; } jx0u12jtqd ; struct { void * AQHandles ; }
gtasy1jsdxk2 ; struct { void * LoggedData ; } pgtrfza33s ; struct { void *
AQHandles ; } mhg3ukoydp ; struct { void * LoggedData ; } ov4way2tof ; struct
{ void * AQHandles ; } kqufha1qme ; struct { void * LoggedData ; } fidvncdjop
; struct { void * AQHandles ; } ck00fvktvl ; struct { void * LoggedData ; }
d2de4uag14 ; struct { void * AQHandles ; } fsc12ul0nq ; struct { void *
LoggedData ; } n3hthjpxsy ; struct { void * AQHandles ; } jk5klgbkjx ; struct
{ void * LoggedData ; } n34n5fqe0k ; struct { void * AQHandles ; } bgmhbb2ggj
; struct { void * LoggedData ; } klqnmdizzb ; struct { void * AQHandles ; }
jfed40pyro ; struct { void * LoggedData ; } a0fgq0yh1e ; struct { void *
AQHandles ; } mgmkqdnd4h ; struct { void * LoggedData ; } lnn0v5njmk ; struct
{ void * AQHandles ; } cqmz0ka510 ; struct { void * LoggedData ; } cotf1zhzxt
; struct { void * AQHandles ; } awm3x1p030 ; struct { void * AQHandles ; }
pz3v3lsswe ; struct { void * LoggedData ; } dnck3gwe1l ; struct { void *
AQHandles ; } nji534mx2v ; struct { void * LoggedData ; } hk1cc0h0mo ; struct
{ void * AQHandles ; } kn50mamzgm ; struct { void * LoggedData ; } kptuczirt5
; struct { void * AQHandles ; } lz2njt4sro ; struct { void * LoggedData ; }
eiuytjixgn ; struct { void * AQHandles ; } hw0crwwhgx ; struct { void *
LoggedData ; } lg0y0ft0jg ; struct { void * AQHandles ; } odefyqi2dd ; struct
{ void * LoggedData ; } i2r5nvclht ; struct { void * AQHandles ; } jwv41mpadj
; struct { void * LoggedData ; } n0ff0fnxnz ; struct { void * AQHandles ; }
mtia2gm3mn ; struct { void * LoggedData ; } k4x0ksvebo ; struct { void *
AQHandles ; } acteg3xdu0 ; struct { void * LoggedData ; } jkhls1x1xd ; struct
{ void * AQHandles ; } dd50e1xu1m ; struct { void * LoggedData ; } owv4g3fh0s
; struct { void * AQHandles ; } phol22yedf ; struct { void * LoggedData ; }
mbaya5ksxj ; struct { void * AQHandles ; } pieup45y1d ; struct { void *
LoggedData ; } o0pg4xxi5b ; struct { void * AQHandles ; } n4ipdfmwpg ; struct
{ void * LoggedData ; } h03ppf21vf ; struct { void * AQHandles ; } pp33uvzuj4
; struct { void * LoggedData ; } fdojmr2ecl ; struct { void * LoggedData ; }
ap5xh2jdk5 ; struct { void * LoggedData ; } kaiai5muqe ; struct { void *
LoggedData ; } ii2sh4h1st ; struct { void * LoggedData ; } m51eciw0jw ;
struct { void * LoggedData ; } awaialiapj ; struct { void * LoggedData ; }
l41y0q41uv ; struct { void * LoggedData ; } f4etw2hcvw ; struct { void *
LoggedData ; } bkhbnfm5sg ; struct { void * AQHandles ; } p4sflk0g2w ; struct
{ void * AQHandles ; } ofz4kqfoe0 ; struct { void * CTLHandle ; } pegf1lgc5k
; struct { void * CTLHandle ; } ft5nitf1xd ; int32_T imduqxhj3y ; int32_T
h0ytymzc2i ; int32_T ndy1r3lteo ; int32_T ono0qix5io ; int32_T bih1twzowf ;
int32_T evb2jcnsmb ; int32_T jcb0vgamw2 ; uint32_T g1tih4iurb ; struct {
int_T NODEADDR ; } gk4tvjl5km ; struct { int_T NODEADDR ; } jqdnga4d0r ;
int_T khs2ujrsdq ; int_T hoc4ujevyd ; int_T pqjv5ubgvq ; int_T dzwszeq5uo ;
int_T lru3e1mvrz ; int_T luuegejdc0 ; int_T nva3c2aiue ; int_T p1lgfwsxn3 ;
int_T ozura1lel3 ; int_T cn5pwf5utq ; int_T c1d5q3vumy ; int_T flfjax3w0e ;
int_T gluwhgdkil ; int_T onwpqbmdms ; int_T n0wxb1xzlc ; struct { int_T Tail
; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
mf4tzazbhp ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } pszwtqz0gn ; int_T dhwxr34two ;
int_T bcl2uuqmhl ; int_T nxjlr5banb ; int_T ja1c4asgaz ; int_T btigisbrqf ;
int_T ckyfoeqie5 ; int_T ixaqaxatlt ; int_T fshou35ift ; int_T cflc32uwnd ;
int_T oqko4zquza ; int_T h3mr0riybw ; int_T pfmhktgqz5 ; int_T mquiy4fzeb ;
int_T omeqzycfh2 ; int_T imt2dcvft2 ; int_T cwyukvwtwb ; int_T ipcifxvj5x ;
int_T c2dyuklr3i ; int_T p40fsqbchl ; int_T l4mfodlgua ; int_T kf0zhsqe1e ;
int_T ie2rbfy2dj ; int_T bi3ryeji3q ; int_T gexhlxucmx ; int_T bzymrve3xd ;
int_T cjg2lxwx3p ; int_T jbxbvwznkw ; int_T ofeqpav0z1 ; int_T f2rh3pjcf4 ;
int_T czpni4mnff ; int_T edzwglzc12 ; int_T kcrt4gkpma ; int_T gdkaitdhn2 ;
int_T j4aiaaqlli ; int_T jw31kvp3ln ; int_T aetkdo2sks ; int8_T dbfmnhxbxj ;
int8_T p1nnlsrxke ; int8_T bfmr5zictt ; uint8_T nhh3pckv2z ; uint8_T
pu1q4zlmwb ; uint8_T pe5pl50ynw ; uint8_T eda54vucfl ; uint8_T mnycq5gn5i ;
uint8_T e4lgtlqce2 ; boolean_T hpyvhbyyfk ; boolean_T mv3mphax4f ; boolean_T
dyrzzohb5s ; boolean_T apmlxbmuwh ; boolean_T ogaaumd32e ; boolean_T
gvkgxqsg5w ; boolean_T ksp31oyn4z ; boolean_T gwi2bo5yvs ; boolean_T
dedzusgrw0 ; boolean_T dqrx4b5l1l ; boolean_T ei55bolyl0 ; boolean_T
frdq0ezqxz ; boolean_T hc5kmkcx43 ; boolean_T bp0lxwi25f ; boolean_T
nd3tkuvjly ; boolean_T adrllpi2ax ; boolean_T cqvouu2ka3 ; boolean_T
j4h3zrlxtn ; boolean_T asj3qcjbaz ; boolean_T ok1wan2u4e ; } DW ; typedef
struct { real_T cwf2tewh2v ; real_T lpegok4bfi ; real_T akhhz2ar2w ; real_T
ekar034xyr ; real_T aufcyghqde ; real_T gdrfqkaj00 ; real_T dl0s2litjt ;
real_T a3o55becan ; real_T olhqyyiiqq ; real_T faiarhiizk ; real_T f10gbcy5as
; real_T d0etugyxyo ; real_T fteoprdfjw ; } X ; typedef struct { real_T
cwf2tewh2v ; real_T lpegok4bfi ; real_T akhhz2ar2w ; real_T ekar034xyr ;
real_T aufcyghqde ; real_T gdrfqkaj00 ; real_T dl0s2litjt ; real_T a3o55becan
; real_T olhqyyiiqq ; real_T faiarhiizk ; real_T f10gbcy5as ; real_T
d0etugyxyo ; real_T fteoprdfjw ; } XDot ; typedef struct { boolean_T
cwf2tewh2v ; boolean_T lpegok4bfi ; boolean_T akhhz2ar2w ; boolean_T
ekar034xyr ; boolean_T aufcyghqde ; boolean_T gdrfqkaj00 ; boolean_T
dl0s2litjt ; boolean_T a3o55becan ; boolean_T olhqyyiiqq ; boolean_T
faiarhiizk ; boolean_T f10gbcy5as ; boolean_T d0etugyxyo ; boolean_T
fteoprdfjw ; } XDis ; typedef struct { real_T cwf2tewh2v ; real_T lpegok4bfi
; real_T akhhz2ar2w ; real_T ekar034xyr ; real_T aufcyghqde ; real_T
gdrfqkaj00 ; real_T dl0s2litjt ; real_T a3o55becan ; real_T olhqyyiiqq ;
real_T faiarhiizk ; real_T f10gbcy5as ; real_T d0etugyxyo ; real_T fteoprdfjw
; } CStateAbsTol ; typedef struct { real_T cwf2tewh2v ; real_T lpegok4bfi ;
real_T akhhz2ar2w ; real_T ekar034xyr ; real_T aufcyghqde ; real_T gdrfqkaj00
; real_T dl0s2litjt ; real_T a3o55becan ; real_T olhqyyiiqq ; real_T
faiarhiizk ; real_T f10gbcy5as ; real_T d0etugyxyo ; real_T fteoprdfjw ; }
CXPtMin ; typedef struct { real_T cwf2tewh2v ; real_T lpegok4bfi ; real_T
akhhz2ar2w ; real_T ekar034xyr ; real_T aufcyghqde ; real_T gdrfqkaj00 ;
real_T dl0s2litjt ; real_T a3o55becan ; real_T olhqyyiiqq ; real_T faiarhiizk
; real_T f10gbcy5as ; real_T d0etugyxyo ; real_T fteoprdfjw ; } CXPtMax ;
typedef struct { real_T lr3ji2rgwk ; real_T eommou5amd ; real_T b32en0czi5 ;
real_T mlu3auj0vq ; real_T cacjlcr1nt ; real_T cw2v4azdro ; real_T cflsczbppg
; real_T b5pki20a5d ; real_T dj0cbnt1la ; real_T m0i4snnkas ; real_T
owwq5xupbf ; real_T jdg1ombjey ; real_T cnqckg51m5 ; real_T ahmiwlbhvm ;
real_T ow1efrp4un ; real_T a3zb3vrb30 ; real_T fzprjsbtph ; real_T gmq4134fkn
; real_T bgmfgfnqlx ; real_T kyjae5h2lu ; real_T berjub23jg ; real_T
mr4zgvyklq ; real_T fnrxk55avd ; real_T g5znlndipk ; real_T mp4zunr0sq ;
real_T itbeoarcd1 ; real_T k35urubxm5 ; real_T bf2qk2fhkd ; real_T erjapnyqdp
; real_T cbu2blq4ae ; real_T j5yhl3xbkg ; real_T bfmk1h5e3o ; real_T
fajvkrccpi ; real_T h4kzxcctcg ; real_T lpahibq2y5 ; real_T grarlpksb3 ;
real_T m30aod4wy4 ; real_T aokmth3ymy ; real_T dbecdvs4zo ; real_T mag3ujlaw0
; real_T eowuh1hss2 ; real_T jolmx4ixju ; real_T ox5rpwyxco ; real_T
l0g3le5jog ; real_T frmdrgx4zt ; real_T lsktlgrwa4 ; real_T bkushmsqu4 ;
real_T azbolayp2y ; real_T lrm3laizhh ; real_T h1ma3waard ; real_T hp0dszoqof
; real_T oqm0wqx0fh ; real_T daocbbswlk ; real_T oh2odqlmhf ; real_T
pn0xl2qz2l ; real_T ieehakhyry ; real_T f3wc1505sm ; real_T ebzwzq5ona ;
real_T inijbjlsfi ; real_T e5dtngaiji ; real_T cpjm0zpnk1 ; real_T ld5xmcvr3e
; real_T dlmfqjncno ; } ZCV ; typedef struct { rtwCAPI_ModelMappingInfo mmi ;
} DataMapInfo ; struct P_ { struct_gwPC03F18UUnIJczODLOeC scenario ;
struct_AgOSJRrmuL6uVtDSBEmT8F road ; struct_EUK64LV9KqFNVcz2dp6tHB model ;
struct_8L4f4gB0y0ox512d7wKmvG control ; real_T Constant_Value ; real_T
gear_Y0 ; real_T u_vgt_Y0 ; real_T u_egr_Y0 ; real_T u_delta_Y0 ; real_T
F_brake_Y0 ; real_T Saturation_UpperSat ; real_T Saturation_LowerSat ; real_T
brake_Value ; real_T Constant_Value_eler4bv4qe ; real_T Integrator_IC ;
real_T Integrator_UpperSat ; real_T Integrator_LowerSat ; real_T mskmh_Gain ;
real_T Integrator1_IC ; real_T Integrator1_UpperSat ; real_T
Integrator1_LowerSat ; real_T Gain1_Gain ; real_T Gain2_Gain ; real_T
PulseGenerator_Amp ; real_T PulseGenerator_Period ; real_T
PulseGenerator_Duty ; real_T PulseGenerator_PhaseDelay ; real_T Gain3_Gain ;
real_T Gain4_Gain ; real_T Integratoromega_t_UpperSat ; real_T
Integratoromega_t_LowerSat ; real_T Saturation_UpperSat_i32xa2dnvv ; real_T
Saturation_LowerSat_f5etl5uivq ; real_T Gain6_Gain ; real_T Gain5_Gain ;
real_T Integrator1_IC_mck3mtbbq3 ; real_T Integrator1_UpperSat_pktoycczal ;
real_T Integrator1_LowerSat_ofks0duo33 ; real_T radsRPM_Gain ; real_T
Gain8_Gain ; real_T Gain9_Gain ; real_T radsRPM_Gain_edopox2oep ; real_T
Memory3_InitialCondition ; real_T Saturation_UpperSat_enesi2iumz ; real_T
Saturation_LowerSat_bn3le4gtty ; real_T Switch_Threshold ; real_T
Saturation_UpperSat_hto0bhsqhd ; real_T Saturation1_UpperSat ; real_T
Saturation1_LowerSat ; real_T Memory2_InitialCondition ; real_T
Saturation_UpperSat_atvgvohnm4 ; real_T Saturation_LowerSat_bnot2t5v4i ;
real_T IntegratorX_Oim_IC ; real_T IntegratorX_Oim_UpperSat ; real_T
IntegratorX_Oim_LowerSat ; real_T Integrator_IC_ikgusueg51 ; real_T
n_eratio_Gain ; real_T GainM_e_Gain ; real_T Saturation_UpperSat_fgktzvfm2k ;
real_T Saturation_LowerSat_eegm4iokxr ; real_T BrakeGain_Gain ; real_T
Relay1_OnVal ; real_T Relay1_OffVal ; real_T Relay1_YOn ; real_T Relay1_YOff
; real_T Relay2_OnVal ; real_T Relay2_OffVal ; real_T Relay2_YOn ; real_T
Relay2_YOff ; real_T Saturation_UpperSat_ehbc0hou2u ; real_T
Saturation_LowerSat_e2gfsq1ep3 ; real_T Saturation1_UpperSat_haikx2purp ;
real_T Saturation1_LowerSat_ja3qpjhkdu ; real_T Memory1_InitialCondition ;
real_T Saturation_UpperSat_imjkncmbbp ; real_T Saturation_LowerSat_jenqmbtgcj
; real_T Switch_Threshold_oyf5ishr1i ; real_T IntegratorX_Oem_IC ; real_T
IntegratorX_Oem_UpperSat ; real_T IntegratorX_Oem_LowerSat ; real_T
Saturation_LowerSat_kzgxh2ssqh ; real_T Saturation1_UpperSat_pjh2z4fnof ;
real_T Saturation1_LowerSat_o3inkji2se ; real_T Gain2_Gain_jj2oxunwb2 ;
real_T kmhms_Gain ; real_T Constant21_Value ; real_T Constant22_Value ;
real_T Constant23_Value ; real_T Constant24_Value ; real_T Constant25_Value ;
real_T Constant26_Value ; real_T Constant27_Value ; real_T Constant28_Value ;
real_T Constant29_Value ; real_T Constant30_Value ; real_T Constant32_Value ;
real_T Constant33_Value ; real_T Constant34_Value ; real_T Constant35_Value ;
real_T Constant36_Value ; real_T Constant37_Value ; real_T Constant38_Value ;
real_T Constant39_Value ; real_T Gain11_Gain ; real_T dummy3_Value ; real_T
Gain10_Gain ; real_T dummy1_Value ; real_T Gain7_Gain ; real_T dummy2_Value ;
real_T const_Value ; real_T Constant_Value_b5ccgfu4yk ; real_T
Constant_Value_nm5d5hyfni ; real_T Constant2_Value ; real_T
Constant2_Value_c3vhbw33ec ; real_T FuelLimit_Value ; real_T
Constant_Value_gcvl5az0p5 ; real_T Constant1_Value ; real_T
Constant1_Value_fe1czv4ovb ; real_T Constant2_Value_imre1apqn2 ; real_T
Constant1_Value_foo0ytc1ur ; real_T Constant_Value_cfl4aorgnt ; real_T
Constant1_Value_kvscu5x5rd ; real_T Constant2_Value_dfqgdtofyy ; real_T
Constant3_Value ; real_T Constant_Value_dwh2dts0z5 ; real_T
Constant_Value_pi0lofejm1 ; real_T Constant1_Value_cjbf34ugrc ; real_T
Constant_Value_ajsql1lpqg ; void * StringConstant_String ; void *
StringConstant1_String ; uint32_T uDLookupTable_maxIndex ; uint32_T
uDLookupTable_dimSizes ; uint32_T uDLookupTable_numYWorkElts [ 2 ] ; } ;
extern CAN_DATATYPE CAN_DATATYPE_GROUND ; extern const char_T *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern P rtP ; extern mxArray * mr_TruckBenchmark_GetDWork ( ) ; extern void
mr_TruckBenchmark_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_TruckBenchmark_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * TruckBenchmark_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern
const int_T gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern
rtInportTUtable * gblInportTUtables ; extern const char * gblInportFileName ;
extern const int_T gblNumRootInportBlks ; extern const int_T
gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ; extern
const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [ ] ;
extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model (
ssExecutionInfo * executionInfo ) ;
#endif
