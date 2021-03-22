modded class BaseBuildingBase extends ItemBase
{
    HRZ_PluginAdminLog m_BaseBuildingLog;

	override void OnPartDestroyedServer( Man player, string part_name, int action_id, bool destroyed_by_connected_part = false )
	{
        m_BaseBuildingLog = HRZ_PluginAdminLog.Cast( GetPlugin(HRZ_PluginAdminLog) );
        if (player != null) {
            PlayerBase pbplayer = PlayerBase.Cast(player);
            m_BaseBuildingLog.HRZ_OnPartDestroyedServer(pbplayer, this, part_name);
        } else {
            m_BaseBuildingLog.HRZ_OnPartDestroyedServer(null, this, part_name);
        }
		super.OnPartDestroyedServer( player, part_name, action_id );
    }    
}