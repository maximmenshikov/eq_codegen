/*
 * Intentionally without headers (for now).
 * Will cause a failure due to nested indications.
 */

int main()
{
    VmOpCode code;

    core_indicate_use(VmOpCode, CoreEnumUse::AllVariants);
    core_indicate_use(VmOpCode, CoreEnumUse::Selected);
    switch (code)
    {
        case VmOpCode::Assign:
        case VmOpCode::Declare:
        default:
            break;
    }
    end_core_indicate_use(VmOpCode);
    return 0;
}