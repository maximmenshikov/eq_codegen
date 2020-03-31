/*
 * Intentionally without headers (for now).
 * Will cause a failure due to double-closed indication.
 */

int main()
{
    VmOpCode code;

    core_indicate_use(VmOpCode, CoreEnumUse::AllVariants);
    switch (code)
    {
        case VmOpCode::Assign:
        case VmOpCode::Declare:
        default:
            break;
    }
    end_core_indicate_use(VmOpCode);
    end_core_indicate_use(VmOpCode);
    return 0;
}