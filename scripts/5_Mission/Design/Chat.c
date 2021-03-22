modded class ChatLine
{
	private const int      OUTLINE_COLOUR = ARGB(255, 0, 0, 0);

	// Consts
	const float FADE_TIMEOUT = 30;
	const float FADE_OUT_DURATION = 3;
	const float FADE_IN_DURATION = 0.5;

	override void Set(ChatMessageEventParams params)	// Param 1 --> Channel, Param 2 --> sender name, Param 3 --> message, Param 4 ?? 
	{
		int channel; 
		
		m_NameWidget.SetText("");
		m_TextWidget.SetText("");
		
		SetColour(DEFAULT_COLOUR);
		m_RootWidget.Show(true);
		
		channel = params.param1; // 0 = Survior   1 = Game/System   2 = Admin 
		
		Print(channel);
		
		if ( channel & CCSystem )
		{
			// Game
			if(params.param2 != "")
			{
				m_NameWidget.SetText(GAME_PREFIX + ": " );
			} 
			SetColour(GAME_TEXT_COLOUR);
		}
		else if ( channel & CCAdmin )
		{
			// Admin
			m_NameWidget.SetText(ADMIN_PREFIX + ": ");
			SetColour(ADMIN_TEXT_COLOUR);			
		}
		else if ( channel & CCTransmitter )
		{
			// Radio - Trasnmitter
			m_NameWidget.SetText(RADIO_PREFIX + params.param2 + " : ");
		}
		else if ( channel == 0 || channel & CCDirect )
		{
			// Player
			if(params.param2 != "")
			{
				return;
				//m_NameWidget.SetText(params.param2 + " : ");
			}
		}
		
		
		m_TextWidget.SetText(params.param3);
		
		m_FadeTimer.FadeIn(m_RootWidget, FADE_IN_DURATION);
		m_TimeoutTimer.Run(FADE_TIMEOUT, m_FadeTimer, "FadeOut", new Param2<Widget, float>(m_RootWidget, FADE_OUT_DURATION));
	}

	override void SetColour(int colour)
	{
        m_NameWidget.SetOutline(2,OUTLINE_COLOUR);
        m_TextWidget.SetOutline(2,OUTLINE_COLOUR);
		m_NameWidget.SetColor(colour);
		m_TextWidget.SetColor(colour);
	}

}