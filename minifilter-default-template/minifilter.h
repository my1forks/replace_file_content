#pragma once
#include<ntifs.h>
#include<ntddk.h>
#include<wdm.h>

#include<fltKernel.h>
#include<string.h>

#define MINI_INCLUDE
#include "ctx.h"

namespace dbg {
    template<typename... types>
    void print(types... args)
    {
        DbgPrintEx(DPFLTR_DEFAULT_ID, DPFLTR_ERROR_LEVEL, args...);
    }

    __inline void dbgbreak() {
        if(*KdDebuggerNotPresent)
            print("breakpoint trigger\n");
        else
            DbgBreakPoint();
        

    }

#define CALL_ONCE_START {\
    static int i = 0;\
    if(i==0){
#define CALL_ONCE_END i++;\
    }}
}
extern PFLT_FILTER gFilterHandle;

namespace minifilter {
    NTSTATUS InstanceQueryTeardown(
        _In_ PCFLT_RELATED_OBJECTS FltObjects,
        _In_ FLT_INSTANCE_QUERY_TEARDOWN_FLAGS Flags
    );

    NTSTATUS InstanceSetup(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
            _In_ DEVICE_TYPE VolumeDeviceType,
            _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
        );

    NTSTATUS Unload(
            _In_ FLT_FILTER_UNLOAD_FLAGS Flags
        );

    VOID InstanceTeardownStart(
        _In_ PCFLT_RELATED_OBJECTS FltObjects,
        _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
    );

    VOID InstanceTeardownComplete(
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _In_ FLT_INSTANCE_TEARDOWN_FLAGS Flags
        );

    VOID CtxContextCleanup(
            _In_ PFLT_CONTEXT Context,
            _In_ FLT_CONTEXT_TYPE ContextType
        );

    namespace irp_create
    {
        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        );
        FLT_POSTOP_CALLBACK_STATUS
            PostOperation(
                _Inout_ PFLT_CALLBACK_DATA Data,
                _In_ PCFLT_RELATED_OBJECTS FltObjects,
                _In_opt_ PVOID CompletionContext,
                _In_ FLT_POST_OPERATION_FLAGS Flags
            );
    }
    namespace irp_read {

        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        );
        FLT_POSTOP_CALLBACK_STATUS
            PostOperation(
                _Inout_ PFLT_CALLBACK_DATA Data,
                _In_ PCFLT_RELATED_OBJECTS FltObjects,
                _In_opt_ PVOID CompletionContext,
                _In_ FLT_POST_OPERATION_FLAGS Flags
            );

    }

    namespace irp_write {

        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        );
        FLT_POSTOP_CALLBACK_STATUS
            PostOperation(
                _Inout_ PFLT_CALLBACK_DATA Data,
                _In_ PCFLT_RELATED_OBJECTS FltObjects,
                _In_opt_ PVOID CompletionContext,
                _In_ FLT_POST_OPERATION_FLAGS Flags
            );

    }

    namespace irp_mj_acquire_for_section_synchronization {

        FLT_PREOP_CALLBACK_STATUS PreOperation(
            _Inout_ PFLT_CALLBACK_DATA Data,
            _In_ PCFLT_RELATED_OBJECTS FltObjects,
            _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
        );
        FLT_POSTOP_CALLBACK_STATUS
            PostOperation(
                _Inout_ PFLT_CALLBACK_DATA Data,
                _In_ PCFLT_RELATED_OBJECTS FltObjects,
                _In_opt_ PVOID CompletionContext,
                _In_ FLT_POST_OPERATION_FLAGS Flags
            );

    }

    CONST FLT_OPERATION_REGISTRATION Callbacks[] = {

    { IRP_MJ_CREATE,
      0,
      irp_create::PreOperation,
      irp_create::PostOperation },

    { IRP_MJ_CREATE_NAMED_PIPE,
      0,
      NULL,
      NULL },

    { IRP_MJ_CLOSE,
      0,
      NULL,
      NULL },

    { IRP_MJ_READ,
      0,
      irp_read::PreOperation,
      irp_read::PostOperation },

    { IRP_MJ_WRITE,
      0,
      irp_write::PreOperation,
      irp_write::PostOperation },

    { IRP_MJ_QUERY_INFORMATION,
      0,
      NULL,
      NULL },

    { IRP_MJ_SET_INFORMATION,
      0,
      NULL,
      NULL },

    { IRP_MJ_QUERY_EA,
      0,
      NULL,
      NULL },

    { IRP_MJ_SET_EA,
      0,
      NULL,
      NULL },

    { IRP_MJ_FLUSH_BUFFERS,
      0,
      NULL,
      NULL },

    { IRP_MJ_QUERY_VOLUME_INFORMATION,
      0,
      NULL,
      NULL },

    { IRP_MJ_SET_VOLUME_INFORMATION,
      0,
      NULL,
      NULL },

    { IRP_MJ_DIRECTORY_CONTROL,
      0,
      NULL,
      NULL },

    { IRP_MJ_FILE_SYSTEM_CONTROL,
      0,
      NULL,
      NULL },

    { IRP_MJ_DEVICE_CONTROL,
      0,
      NULL,
      NULL },

    { IRP_MJ_INTERNAL_DEVICE_CONTROL,
      0,
      NULL,
      NULL },

    { IRP_MJ_SHUTDOWN,
      0,
      NULL,
      NULL },                               //post operations not supported

    { IRP_MJ_LOCK_CONTROL,
      0,
      NULL,
      NULL },

    { IRP_MJ_CLEANUP,
      0,
      NULL,
      NULL },

    { IRP_MJ_CREATE_MAILSLOT,
      0,
      NULL,
      NULL },

    { IRP_MJ_QUERY_SECURITY,
      0,
      NULL,
      NULL },

    { IRP_MJ_SET_SECURITY,
      0,
      NULL,
      NULL },

    { IRP_MJ_QUERY_QUOTA,
      0,
      NULL,
      NULL },

    { IRP_MJ_SET_QUOTA,
      0,
      NULL,
      NULL },

    { IRP_MJ_PNP,
      0,
      NULL,
      NULL },

    { IRP_MJ_ACQUIRE_FOR_SECTION_SYNCHRONIZATION,
      0,
      irp_mj_acquire_for_section_synchronization::PreOperation,
      irp_mj_acquire_for_section_synchronization::PostOperation },

    { IRP_MJ_RELEASE_FOR_SECTION_SYNCHRONIZATION,
      0,
      NULL,
      NULL },

    { IRP_MJ_ACQUIRE_FOR_MOD_WRITE,
      0,
      NULL,
      NULL },

    { IRP_MJ_RELEASE_FOR_MOD_WRITE,
      0,
      NULL,
      NULL },

    { IRP_MJ_ACQUIRE_FOR_CC_FLUSH,
      0,
      NULL,
      NULL },

    { IRP_MJ_RELEASE_FOR_CC_FLUSH,
      0,
      NULL,
      NULL },

    { IRP_MJ_FAST_IO_CHECK_IF_POSSIBLE,
      0,
      NULL,
      NULL },

    { IRP_MJ_NETWORK_QUERY_OPEN,
      0,
      NULL,
      NULL },

    { IRP_MJ_MDL_READ,
      0,
      NULL,
      NULL },

    { IRP_MJ_MDL_READ_COMPLETE,
      0,
      NULL,
      NULL },

    { IRP_MJ_PREPARE_MDL_WRITE,
      0,
      NULL,
      NULL },

    { IRP_MJ_MDL_WRITE_COMPLETE,
      0,
      NULL,
      NULL },

    { IRP_MJ_VOLUME_MOUNT,
      0,
      NULL,
      NULL },

    { IRP_MJ_VOLUME_DISMOUNT,
      0,
      NULL,
      NULL },

    { IRP_MJ_OPERATION_END }
    };

    const FLT_CONTEXT_REGISTRATION ContextRegistration[] = {

      { FLT_INSTANCE_CONTEXT,
      0,
      CtxContextCleanup,
      CTX_INSTANCE_CONTEXT_SIZE,
      CTX_INSTANCE_CONTEXT_TAG },

    { FLT_FILE_CONTEXT,
      0,
      CtxContextCleanup,
      CTX_FILE_CONTEXT_SIZE,
      CTX_FILE_CONTEXT_TAG },

    { FLT_STREAM_CONTEXT,
      0,
      CtxContextCleanup,
      CTX_STREAM_CONTEXT_SIZE,
      CTX_STREAM_CONTEXT_TAG },

    { FLT_STREAMHANDLE_CONTEXT,
      0,
      CtxContextCleanup,
      CTX_STREAMHANDLE_CONTEXT_SIZE,
      CTX_STREAMHANDLE_CONTEXT_TAG },

    { FLT_CONTEXT_END }
    };


    CONST FLT_REGISTRATION FilterRegistration = {

        sizeof(FLT_REGISTRATION),         //  Size
        FLT_REGISTRATION_VERSION,         //  Version
        0,                                //  Flags

        ContextRegistration,              //  Context
        Callbacks,                        //  Operation callbacks

        Unload,                           //  MiniFilterUnload

        InstanceSetup,                    //  InstanceSetup
        InstanceQueryTeardown,            //  InstanceQueryTeardown
        InstanceTeardownStart,            //  InstanceTeardownStart
        InstanceTeardownComplete,         //  InstanceTeardownComplete

        NULL,                             //  GenerateFileName
        NULL,                             //  GenerateDestinationFileName
        NULL                              //  NormalizeNameComponent

    };
}