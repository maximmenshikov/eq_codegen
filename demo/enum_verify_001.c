/* Intentionally without headers (for now) */

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
    return 0;
}