#include"minifilter.h"

namespace minifilter {
    NTSTATUS Unload(
        _In_ FLT_FILTER_UNLOAD_FLAGS Flags
    ) {
        PAGED_CODE();
        FltUnregisterFilter(gFilterHandle);

        dbg::print("replace unloaded\n");
        return STATUS_SUCCESS;
    }
}