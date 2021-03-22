class InstSong1 extends EmoteBase
{
	
	void InstSong1()
	{
		m_ID = EmoteConstants.ID_INST_SONG1;
    	m_StanceMaskAdditive = 0;
		m_StanceMaskFullbody = DayZPlayerConstants.STANCEMASK_CROUCH;
		m_AdditiveCallbackUID = 0;
		m_FullbodyCallbackUID = DayZPlayerConstants.CMD_GESTUREFB_SITA;
		m_HideItemInHands = false;
  	}
  	override void OnBeforeStandardCallbackCreated(int callback_ID, int stancemask, bool is_fullbody)
	{
		//protected EffectSound	m_Song1;
		//ActionData action_data;
		//Print("Song1");
		//Playerbase player;
		//player = GetCurrentPosition();
		//m_Song1 = SEffectManager.PlaySound( "HRZ_Guitar1_SoundSet", GetCurrentPosition() );
		//m_Song1.SetSoundAutodestroy( true );
		//test.SetTapeVolume(); 
		//m_Player.test(SetTapeVolume());
    	//m_Player.HRZ_Instruments_Base().SetTapeVolume();
    	//m_Player.RequestSoundEvent(EPlayerSoundEventID.SYMPTOM_LAUGHTER);
	}	
}

class InstSong2 : InstSong1
{
	void InstSong2()
	{
		m_ID = EmoteConstants.ID_INST_SONG2;
	}
  	override void OnBeforeStandardCallbackCreated(int callback_ID, int stancemask, bool is_fullbody)
	{
		//Print("Song2");
		//protected EffectSound	m_Song2;
		//m_Song2 = SEffectManager.PlaySound( "HRZ_Guitar2_SoundSet", GetCurrentPosition() );
		//m_Song2.SetSoundAutodestroy( true );
	}

//m_Song2.SoundStop();
}

class InstSong3 : InstSong1
{
	void InstSong3()
	{
		m_ID = EmoteConstants.ID_INST_SONG3;
	}
  	override void OnBeforeStandardCallbackCreated(int callback_ID, int stancemask, bool is_fullbody)
	{
		//Print("Song3");
		//protected EffectSound	m_Song3;
		//m_Song3 = SEffectManager.PlaySound( "HRZ_Guitar3_SoundSet", GetCurrentPosition() );
		//m_Song3.SetSoundAutodestroy( true );
	}
//m_Song3.SoundStop();
}