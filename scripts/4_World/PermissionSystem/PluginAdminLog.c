class HRZ_PluginAdminLog extends PluginAdminLog {

	protected FileHandle m_LogFile;

    protected const string m_LogDirectory = "$profile:HellRiderZ/";
	protected string m_Log;
	
	void HRZ_PluginAdminLog()
    {
        if (!FileExist(m_LogDirectory) && GetGame().IsMultiplayer())
        {
            PrintFormat("[HRZ]::MakeDirectory - %1", m_LogDirectory);
			MakeDirectory(m_LogDirectory);
		}
    }
	
    void PrintLog(string message)
    {
        m_LogFile = OpenFile(CurrentLogFile(), FileMode.APPEND);
        message = string.Format("[%1-%2] %3\n", GetDate(), GetTime(), message);
        FPrintln(m_LogFile, message);
        CloseFile(m_LogFile);
    }
	
    protected string GetTime()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return string.Format("%1:%2:%3", hour.ToStringLen(2), minute.ToStringLen(2), second.ToStringLen(2));
    }

    protected string GetDate()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return string.Format("%1.%2.%3", year.ToStringLen(2), month.ToStringLen(2), day.ToStringLen(2));
    }
	
    protected string CurrentLogFile()
    {
        return string.Format("%1AdminLog_%2.log", m_LogDirectory, GetDate());
    }
	
	override string GetPlayerPrefix( PlayerBase player, PlayerIdentity identity )  // player name + id + position prefix for log prints
	{	
		
		m_Position = player.GetPosition();
		m_PosArray[3] = { m_Position[0].ToString(), m_Position[2].ToString(), m_Position[1].ToString() };
		
		for ( int i = 0; i < 3; i++ )	// trim position precision
		{
			m_DotIndex = m_PosArray[i].IndexOf(".");
			if ( m_DotIndex != -1 )
			{
			m_PosArray[i] = m_PosArray[i].Substring( 0, m_DotIndex + 2 );
			}
		}
		
		if ( !identity ) 	// return partial message even if it fails to fetch identity 
		{
			return "Player \"" + "Unknown/Dead Entity" + "\" (SteamID=" + "Unknown" + " pos=<X:" +  m_PosArray[0] + ", Z:" + m_PosArray[1] + ", Y:" + m_PosArray[2] + ">)";
		}
		
		m_PlayerName = "\"" + identity.GetName() + "\"";
		m_Pid = identity.GetPlainId();
		
		if ( !player.IsAlive() )
		{
		 	m_PlayerName = m_PlayerName + " (DEAD)"; 
		}
		
		return "Player " + m_PlayerName + " (SteamID=" + m_Pid + " pos=<X:" +  m_PosArray[0] + ", Z:" + m_PosArray[1] + ", Y:" + m_PosArray[2] + ">)";
	}

	string HRZ_GetPositionString( vector pos )
	{
		m_PosArray[3] = { pos[0].ToString(), pos[2].ToString(), pos[1].ToString() };
		
		for ( int i = 0; i < 3; i++ )
		{
			m_DotIndex = m_PosArray[i].IndexOf(".");
			if ( m_DotIndex != -1 )
			{
			m_PosArray[i] = m_PosArray[i].Substring( 0, m_DotIndex + 2 );
			}
		}

		return "pos=<X:" +  m_PosArray[0] + ", Z:" + m_PosArray[1] + ", Y:" + m_PosArray[2] + ">";		
	}

	void HRZ_ActionGetInTransport(PlayerBase player, Transport transport)	
	{
		if (player && transport)
		{
			m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );
			m_Log = string.Format("\[HRZ] Vehicle " + m_PlayerPrefix +  " Steigt in " + transport.GetType()  + " (" + HRZ_GetPositionString(transport.GetPosition()) + ")");
        	PrintLog(m_Log);
		}		
	}

	void HRZ_ActionGetOutTransport(PlayerBase player, Transport transport)	
	{
		if (player && transport)
		{		
			m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );
			m_Log = string.Format("\[HRZ] Vehicle " + m_PlayerPrefix +  " Verlässt den " + transport.GetType() + " (" + HRZ_GetPositionString(transport.GetPosition()) + ")");
			PrintLog(m_Log);
		}		
	}

	void HRZ_OnPartDestroyedServer(PlayerBase player, Object construction, string part_name)
	{
        if (construction)
        {
		    if (player)
		    {
    			m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );	    
            	m_Log = string.Format("\[HRZ] PlayerDestroyedBasePart " + m_PlayerPrefix +  " " + construction.GetType() + " ["+ part_name + "] (" + HRZ_GetPositionString(construction.GetPosition()) + ")");
				PrintLog(m_Log);
			} else {
            	m_Log = string.Format("\[HRZ] DestroyedBasePart " + construction.GetType() + " [" + part_name + "] (" + HRZ_GetPositionString(construction.GetPosition()) + ")");
				PrintLog(m_Log);
			}
        }        
	}
	
    void HRZ_DigOutStash(PlayerBase player,ItemBase chest)
    {
       		if (player) {
           	m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );
			m_Log = string.Format("\[HRZ] DigOutStash " + m_PlayerPrefix +  " Gräbt " + chest.GetType() + " (" + HRZ_GetPositionString(chest.GetPosition()) + ") aus.");
			PrintLog(m_Log);
        	}
    }
	
    void HRZ_DigInStash(PlayerBase player,ItemBase stashed_item)
    {
       		if (player) {
           	m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );
			m_Log = string.Format("\[HRZ] DigInStash " + m_PlayerPrefix +  " Gräbt " + stashed_item.GetType() + " (" + HRZ_GetPositionString(stashed_item.GetPosition()) + ") ein.");
			PrintLog(m_Log);
        	}
    }
	
    void HRZ_DecraftWoodenCrate(PlayerBase player)
    {
       		if (player) {
           	m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );
			m_Log = string.Format("\[HRZ] DecaftWoodenCrate " + m_PlayerPrefix);
			PrintLog(m_Log);
        	}
    }
	
	void HRZ_EditNote(PlayerBase player, string old_text, string new_text)
	{
		if (player && old_text && new_text)
		{
			//Print("Call");
			m_PlayerPrefix = this.GetPlayerPrefix( player , player.GetIdentity() );
			//if (!old_text.Empty) {
			m_Log = string.Format("\[HRZ] Note Old Text " + m_PlayerPrefix + old_text);
			PrintLog(m_Log);
			//} 
			m_Log = string.Format("\[HRZ] Note New Text " + m_PlayerPrefix + new_text);
			PrintLog(m_Log);
		}
	}
	
    void HRZ_PlayerKill(PlayerBase player, Object source)
    {
       		if ( player && source )
			{
			
				if ( source.IsWeapon() || source.IsMeleeWeapon() )  // player
				{				
					m_Source = PlayerBase.Cast( EntityAI.Cast( source ).GetHierarchyParent() );
					m_PlayerPrefix2 = "";
					if (m_Source)
					{
						m_PlayerPrefix2 = this.GetPlayerPrefix( m_Source ,  m_Source.GetIdentity() );
					}
					
					if ( source.IsMeleeWeapon() )
					{	
						m_Log = string.Format("\[HRZ] Killfeed " + m_PlayerPrefix + " killed by " + m_PlayerPrefix2 + " with " + source.GetDisplayName() );
						PrintLog(m_Log);
					}
					else
					{
						m_Distance = vector.Distance( player.GetPosition(), m_Source.GetPosition() );
						m_Log = string.Format("\[HRZ] Killfeed " + m_PlayerPrefix + " killed by " + m_PlayerPrefix2 + " with " + source.GetDisplayName() + " from " + m_Distance + " meters " );
						PrintLog(m_Log);
					}
				}
				else // others
				{
					//m_Log = string.Format("\[HRZ] Killfeed " + m_PlayerPrefix + " killed by " + source.GetType() );
					//PrintLog(m_Log);
				}
	        		} else {
				//LogPrint("DEBUG: PlayerKilled() player/source does not exist");
			}	
    }

}