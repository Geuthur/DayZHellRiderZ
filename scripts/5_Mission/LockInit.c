// Handle the esacpe key with menus
modded class MissionGameplay extends MissionBase
{
    void MissionGameplay()
    {
		g_HRZLockRPCManager = null;
        GetHRZLockRPCManager();
    }

	override void OnKeyPress(int key)
	{
		super.OnKeyPress(key);
		m_Hud.KeyPress(key);
		

		switch ( key )
		{
			case KeyCode.KC_ESCAPE:
				HRZ_CloseCodeLockMenu();
				break;

			case KeyCode.KC_RETURN:
				HRZ_HandleEnterKey();
				break;

			case KeyCode.KC_NUMPADENTER:
				HRZ_HandleEnterKey();
				break;
		}
	}

	void HRZ_CloseCodeLockMenu()
	{
		if( GetUIManager().IsMenuOpen( HRZ_SET_CODE_MENU ) )
		{
			HRZGlobalFunctions.HRZ_HideUI( HRZ_SET_CODE_MENU );
		}
		else if( GetUIManager().IsMenuOpen( HRZ_ENTER_CODE_MENU ) )
		{
			HRZGlobalFunctions.HRZ_HideUI( HRZ_ENTER_CODE_MENU );
		}
	}

	void HRZ_HandleEnterKey()
	{
		HRZ_EnterCodeMenu menu_Enter;
		HRZ_SetCodeMenu menu_Set;
		
		if ( Class.CastTo( menu_Enter, GetUIManager().FindMenu( HRZ_ENTER_CODE_MENU ) ) )
		{
			menu_Enter.HRZ_SendEnterCodeRPC();
		}
		
		else if ( Class.CastTo( menu_Set, GetUIManager().FindMenu( HRZ_SET_CODE_MENU ) ) )
		{
			menu_Set.HRZ_CheckState();
		}
	}
}

modded class MissionServer
{
    void MissionServer()
    {
		g_HRZLockRPCManager = null;
        GetHRZLockRPCManager();
		//g_HRZCodeLock = null;
        //GetHRZCodeLock();
    }
}