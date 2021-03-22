modded class InGameMenu extends UIScriptedMenu
{
	protected Widget			m_WebSite;
	protected Widget			m_Report;
	protected Widget			m_Discord;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("Client/gui/day_z_ingamemenu.layout");

		m_ContinueButton			= layoutRoot.FindAnyWidget( "continuebtn" );
		m_ExitButton				= layoutRoot.FindAnyWidget( "exitbtn" );
		m_RestartButton				= layoutRoot.FindAnyWidget( "restartbtn" );
		m_RespawnButton 			= layoutRoot.FindAnyWidget( "respawn_button" );
		m_RestartDeadRandomButton	= layoutRoot.FindAnyWidget( "respawn_button_random" );
		m_RestartDeadCustomButton	= layoutRoot.FindAnyWidget( "respawn_button_custom" );
		m_OptionsButton				= layoutRoot.FindAnyWidget( "optionsbtn" );
		m_ModdedWarning				= TextWidget.Cast( layoutRoot.FindAnyWidget( "ModdedWarning" ) );
		m_HintPanel					= new UiHintPanel(layoutRoot.FindAnyWidget( "hint_frame" ));
		m_ServerInfoPanel 			= layoutRoot.FindAnyWidget( "server_info" );
		m_ServerIP 					= TextWidget.Cast( layoutRoot.FindAnyWidget( "server_ip" ) );
		m_ServerPort 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "server_port" ) );
		m_ServerName 				= TextWidget.Cast( layoutRoot.FindAnyWidget( "server_name" ) );
		//m_FavoriteButton 			= layoutRoot.FindAnyWidget( "favorite_button" );
		m_FavoriteImage 			= layoutRoot.FindAnyWidget( "favorite_image" );
		m_UnfavoriteImage 			= layoutRoot.FindAnyWidget( "unfavorite_image" );
		m_CopyInfoButton 			= layoutRoot.FindAnyWidget( "copy_button" );
						
		m_WebSite	 				= layoutRoot.FindAnyWidget( "webSitebtn" );
		m_Report 					= layoutRoot.FindAnyWidget( "reportbtn" );
		m_Discord	 				= layoutRoot.FindAnyWidget( "discordbtn" );

		if (GetGame().IsMultiplayer())
		{
			ButtonSetText(m_RestartButton, "#main_menu_respawn");
		}
		else
		{
			ButtonSetText(m_RestartButton, "#main_menu_restart");
		}		
		
	#ifdef BULDOZER		
		delete m_RestartButton;
	#endif
		
		HudShow( false );
		SetGameVersion();
		SetServerInfoVisibility(SetServerInfo() && g_Game.GetProfileOption( EDayZProfilesOptions.SERVERINFO_DISPLAY ));
		m_ModdedWarning.Show( g_Game.ReportModded() );
		
		return layoutRoot;
	}
	
		override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		
		if ( w == m_WebSite )
		{
			OnClick_Website();
			return true;
		}
		else if ( w == m_Report )
		{
			OnClick_Report();
			return true;
		}
		else if ( w == m_Discord )
		{
			OnClick_Discord();
			return true;
		}
		return false;
	}


	protected void OnClick_Website()
	{
			GetGame().OpenURL("https://hell-rider.de/DayZ"); //Replace my links to yours. Opens any URL Page in browser
	}
	protected void OnClick_Report()
	{
			GetGame().OpenURL("https://hell-rider.de/DayZHelp/"); //Replace my links to yours. Opens any URL Page in browser
	}
	protected void OnClick_Discord()
	{
			GetGame().OpenURL("https://discord.hell-rider.de"); //Replace my links to yours. Opens any URL Page in browser
	}
	
}
