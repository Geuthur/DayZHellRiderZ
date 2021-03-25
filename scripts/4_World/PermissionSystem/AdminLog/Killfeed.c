modded class PlayerBase {

	HRZ_PluginAdminLog m_KillFeedLog;
	
	override void EEKilled( Object killer )
	{
	super.EEKilled(killer);
	
	if ( m_AdminLog )
		{
			m_KillFeedLog.HRZ_PlayerKill( this, killer );
		}
	}

}