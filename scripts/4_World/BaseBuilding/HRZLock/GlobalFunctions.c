class HRZGlobalFunctions
{
	static string ConvertToStars( string input )
	{
        string passString = "";

        for (int i = 0; i < input.Length(); i++)
        {
            passString += "*";
        }

        return passString;
	}

    static void HRZ_HideUI( int menuID )
    {
        g_Game.GetUIManager().ShowCursor(false);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().CloseMenu( menuID );
        GetGame().GetMission().GetHud().Show( true );
    }

    static void HRZ_ShowUI()
    {
        g_Game.GetUIManager().ShowUICursor( true );
        g_Game.GetUIManager().ShowCursor( true );
        GetGame().GetInput().ChangeGameFocus( 1 );
        GetGame().GetMission().GetHud().Show( false );
    }
}