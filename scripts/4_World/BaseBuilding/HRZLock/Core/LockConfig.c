/*
class HRZCodeLock extends PluginBase
{
    protected const string m_LogDirectory = "$profile:HellRiderZ/";
    const static string cfgPath = "$profile:HellRiderZ/HRZCodeLock.json";
    //private bool m_CanHackLock;

    void HRZCodeLock()
    {
		if (!FileExist(m_LogDirectory) && GetGame().IsMultiplayer())
        {
            PrintFormat("[HRZ]::MakeDirectory - %1", m_LogDirectory);
			MakeDirectory(m_LogDirectory);
		}
        //m_CanHackLock         = true;
        LoadConfig();
    }
    
// Local configuration functions

    private void LoadConfig()
    {
        if (FileExist( cfgPath ) )
        {
            JsonFileLoader<HRZCodeLock>.JsonLoadFile( cfgPath, this );
        }
        else
        {
            CreateConfig();
        }
    }

    private void SaveConfig()
    {
        JsonFileLoader<HRZCodeLock>.JsonSaveFile( cfgPath, this );
    }

    private void CreateConfig()
    {
        //m_CanHackLock        = true;
        SaveConfig();
        LoadConfig();
    }
	
	// Deactivated for the Moment

    bool CanHackLock()
    {
        LoadConfig();
        return m_CanHackLock;
    }

}
*/
/*
static ref HRZCodeLock g_HRZCodeLock;
static ref HRZCodeLock GetHRZCodeLock()
{
    if ( !g_HRZCodeLock )
    {
        g_HRZCodeLock = new ref HRZCodeLock();
    }
    
    return g_HRZCodeLock;
}
*/