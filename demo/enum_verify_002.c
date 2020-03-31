/* Intentionally without headers (for now) */

int main()
{
    VmOpCode code;

    core_indicate_use(VmOpCode, CoreEnumUse::Selected);
    switch (code)
    {
        case VmOpCode::Assign:
        default:
            break;
    }
    end_core_indicate_use(VmOpCode);
    return 0;
}