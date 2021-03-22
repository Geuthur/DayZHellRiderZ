modded class PluginManager
{
    override void Init()
    {
        super.Init();
        RegisterPlugin("HRZ_PluginAdminLog", false, true);
	RegisterPlugin("HRZ_PermissionManager", true, true);
        RegisterPlugin("HRZ_PermissionClient", true, false);
    }
}