#include"minifilter.h"

#include"utils.h"
namespace minifilter
{
    namespace irp_read {
        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        )
        {
            PFILE_OBJECT FileObject = Data->Iopb->TargetFileObject;

            if(FlagOn(Data->Iopb->IrpFlags, IRP_PAGING_IO))
                return FLT_PREOP_SUCCESS_NO_CALLBACK;

            if(FLT_IS_FASTIO_OPERATION(Data))
                return FLT_PREOP_DISALLOW_FASTIO;

            ULONG_PTR stackLow;
            ULONG_PTR stackHigh;

            IoGetStackLimits(&stackLow, &stackHigh);

            if (((ULONG_PTR)FileObject > stackLow) &&
                ((ULONG_PTR)FileObject < stackHigh)) {

                dbg::dbgbreak();
            }
            
            
            return FLT_PREOP_SUCCESS_WITH_CALLBACK;
        }
        FLT_POSTOP_CALLBACK_STATUS
            PostOperation( 
                _Inout_ PFLT_CALLBACK_DATA Data,
                _In_ PCFLT_RELATED_OBJECTS FltObjects,
                _In_opt_ PVOID CompletionContext,
                _In_ FLT_POST_OPERATION_FLAGS Flags
            )
        {
            return FLT_POSTOP_FINISHED_PROCESSING;
        }

    }
}