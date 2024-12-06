#include "TruckBenchmark_capi_host.h"
static TruckBenchmark_host_DataMapInfo_T root;
static int initialized = 0;
__declspec( dllexport ) rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        TruckBenchmark_host_InitializeDataMapInfo(&(root), "TruckBenchmark");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction(){return(getRootMappingInfo());}
