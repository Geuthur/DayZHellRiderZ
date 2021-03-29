modded class MainMenu extends UIScriptedMenu
{
	protected Widget				discord_button;
	protected Widget				homepage_button;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets( "Client/gui/MainMenu.layout" );
		
		homepage_button				= layoutRoot.FindAnyWidget( "homepage_button" );
		discord_button				= layoutRoot.FindAnyWidget( "discord_button" );
		
		m_Play						= layoutRoot.FindAnyWidget( "play" );
		m_ChooseServer				= layoutRoot.FindAnyWidget( "choose_server" );
		m_CustomizeCharacter		= layoutRoot.FindAnyWidget( "customize_character" );
		m_PlayVideo					= layoutRoot.FindAnyWidget( "play_video" );
		m_Tutorials					= layoutRoot.FindAnyWidget( "tutorials" );
		m_TutorialButton			= layoutRoot.FindAnyWidget( "tutorial_button" );
		m_MessageButton				= layoutRoot.FindAnyWidget( "message_button" );
		m_SettingsButton			= layoutRoot.FindAnyWidget( "settings_button" );
		m_Exit						= layoutRoot.FindAnyWidget( "exit_button" );
		m_PrevCharacter				= layoutRoot.FindAnyWidget( "prev_character" );
		m_NextCharacter				= layoutRoot.FindAnyWidget( "next_character" );

		m_Version					= TextWidget.Cast( layoutRoot.FindAnyWidget( "version" ) );
		m_ModdedWarning				= TextWidget.Cast( layoutRoot.FindAnyWidget( "ModdedWarning" ) );
		m_CharacterRotationFrame	= layoutRoot.FindAnyWidget( "character_rotation_frame" );
		
		m_LastPlayedTooltip			= layoutRoot.FindAnyWidget( "last_server_info" );
		m_LastPlayedTooltip.Show(false);
		m_LastPlayedTooltipLabel	= m_LastPlayedTooltip.FindAnyWidget( "last_server_info_label" );
		m_LastPlayedTooltipName 	= TextWidget.Cast( m_LastPlayedTooltip.FindAnyWidget( "last_server_info_name" ) );
		m_LastPlayedTooltipIP		= TextWidget.Cast( m_LastPlayedTooltip.FindAnyWidget( "last_server_info_ip" ) );
		m_LastPlayedTooltipPort		= TextWidget.Cast( m_LastPlayedTooltip.FindAnyWidget( "last_server_info_port" ) );
		
		m_LastPlayedTooltipTimer	= new WidgetFadeTimer();
		
		m_Stats						= new MainMenuStats( layoutRoot.FindAnyWidget( "character_stats_root" ) );
		
		m_Mission					= MissionMainMenu.Cast( GetGame().GetMission() );
		
		m_LastFocusedButton = 		m_Play;

		m_ScenePC					= m_Mission.GetIntroScenePC();
		
		if( m_ScenePC )
		{
			m_ScenePC.ResetIntroCamera();
		}
		
		m_PlayVideo.Show( false );
		
		m_PlayerName				= TextWidget.Cast( layoutRoot.FindAnyWidget("character_name_text") );
		
		// Set Version
		string version;
		GetGame().GetVersion( version );
		m_Version.SetText( "#main_menu_version" + " " + version );
		
		GetGame().GetUIManager().ScreenFadeOut(0);

		SetFocus( null );
		
		Refresh();
		
		LoadMods();
		
		GetDayZGame().GetBacklit().MainMenu_OnShow();
	
		g_Game.SetLoadState( DayZLoadState.MAIN_MENU_CONTROLLER_SELECT );
		
		return layoutRoot;
	}

	override bool OnClick( Widget w, int x, int y, int button )
	{
		if( button == MouseState.LEFT )
		{
			if( w == m_Play )
			{
				m_LastFocusedButton = m_Play;
				Play();
				return true;
			}
			else if ( w == m_ChooseServer )
			{
				m_LastFocusedButton = m_ChooseServer;
				OpenMenuServerBrowser();
				return true;
			}
			else if ( w == m_CustomizeCharacter )
			{
				OpenMenuCustomizeCharacter();
				return true;
			}
			else if ( w == m_TutorialButton )
			{
				OpenTutorials();
				return true;
			}
			else if ( w == m_MessageButton )
			{
				OpenCredits();
				return true;
			}
			else if ( w == m_SettingsButton )
			{
				OpenSettings();
				return true;
			}
			else if ( w == m_Exit )
			{
				Exit();
				return true;
			}
			else if ( w == m_PrevCharacter )
			{
				PreviousCharacter();
				return true;
			}
			else if ( w == m_NextCharacter )
			{
				NextCharacter();
				return true;
			}
			else if ( w == m_PlayVideo )
			{
				m_LastFocusedButton = m_PlayVideo;
				PlayVideo();
				return true;
			}
			else if ( w == m_Tutorials )
			{
				m_LastFocusedButton = m_Tutorials;
				OpenTutorials();
				return true;
			}
			else if ( w == discord_button )
			{
				GetGame().OpenURL("https://discord.hell-rider.de"); //Replace my links to yours. Opens any URL Page in browser
				return true;
			}
			else if ( w == homepage_button )
			{
				GetGame().OpenURL("https://hell-rider.de/DayZ"); //Replace my links to yours. Opens any URL Page in browser
				return true;
			}	
		}
		return false;
	}
	
	override void OnChangeCharacter(bool create_character = true)
	{
		if ( m_ScenePC && m_ScenePC.GetIntroCharacter() )
		{
			int charID = m_ScenePC.GetIntroCharacter().GetCharacterID();
			if (create_character)
			{
				m_ScenePC.GetIntroCharacter().CreateNewCharacterById( charID );
			}
			m_PlayerName.SetText( m_ScenePC.GetIntroCharacter().GetCharacterNameById( charID ) );
			
			Widget w = m_CustomizeCharacter.FindAnyWidget(m_CustomizeCharacter.GetName() + "_label");
			
			if ( w )
			{
				TextWidget text = TextWidget.Cast( w );
				
				if( m_ScenePC.GetIntroCharacter().IsDefaultCharacter() )
				{
					text.SetText("CHARACTER");
				}
				else
				{
					text.SetText("CHARACTER");
				}
			}
			if (m_ScenePC.GetIntroCharacter().GetCharacterObj() )
			{
				if ( m_ScenePC.GetIntroCharacter().GetCharacterObj().IsMale() )
					m_ScenePC.GetIntroCharacter().SetCharacterGender(ECharGender.Male);
				else
					m_ScenePC.GetIntroCharacter().SetCharacterGender(ECharGender.Female);
			}
			
			//update character stats
			m_Stats.UpdateStats();
		}
	}
}