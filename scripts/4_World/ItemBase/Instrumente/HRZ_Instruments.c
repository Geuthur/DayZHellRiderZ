class HRZ_Instruments_Base extends Clothing
{
	ref HumanMovementState state = new HumanMovementState();
	protected ItemBase m_Instruments;
    	protected bool m_InstrumentPlaying;
    	protected EffectSound m_InstrumentActiveSound;
	protected bool m_IsActive = false;
	static bool HRZ_InstrumentMenu = false;
	
    //Network synced data
    protected bool m_InstrumentSyncStatus;		
	
    void HRZ_Instruments_Base()
    {
		m_Instruments = this;
        RegisterNetSyncVariableBool( "m_InstrumentSyncStatus" );
    }
	override bool CanRemoveFromHands ( EntityAI player ) 
	{
		return !m_IsActive;
	}
	
	/*
	override void EEItemIntoHands (EntityAI item)
	{
		HRZ_InstrumentMenu = true;
	}
	*/
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(HRZ_ActionSwitchSong);
	}
	
    override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
        
        if( m_InstrumentSyncStatus && !IsPlaying() ) SoundTurnOn();
        if( !m_InstrumentSyncStatus && IsPlaying() ) SoundTurnOff();
	}	
	
	override void OnMovedInsideCargo( EntityAI container )
	{
        SoundTurnOff();
	}
	
	override void EEInventoryOut (Man oldParentMan, EntityAI diz, EntityAI newParent)
	{
        SoundTurnOff();
		HRZ_InstrumentMenu = false;
	}  
	

	void SoundTurnOn()
	{
		if ( GetCompEM().CanWork() ) GetCompEM().SwitchOn();
	}

	void SoundTurnOff()
	{
        GetCompEM().SwitchOff();
	}
	
    override void OnWorkStart()
    {
		m_IsActive = true;
		HRZ_InstrumentMenu = true;
        if (!PlaySong())
        {
            SoundTurnOff();
        }
    }
	
	override bool IsClothing()
	{
		return false;
	}
	
    override void OnWorkStop()
    {
		m_IsActive = false;
		HRZ_InstrumentMenu = false;
        StopSong();
    }

	bool PlaySong()
	{
        string cfgPath = "CfgVehicles " + m_Instruments.GetType() + " CfgInstruments" ;
		
		if( !GetGame().ConfigIsExisting( cfgPath ) ) return false;
		
		if ( m_InstrumentActiveSound ) m_InstrumentActiveSound.SoundStop();
		
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
            m_InstrumentActiveSound = SEffectManager.PlaySoundOnObject( GetGame().ConfigGetTextOut( cfgPath + " soundSet" ), this );
			Print(m_InstrumentActiveSound);
            m_InstrumentActiveSound.SetSoundAutodestroy( true );
            SetTapeVolume();
        }
        
        m_InstrumentPlaying = true;
        m_InstrumentSyncStatus = true;
        return true;
	}
	
    void SetTapeVolume()
    {
    }
	
	void StopSong()
	{
        m_InstrumentPlaying = false;
        m_InstrumentSyncStatus = false;

        if ( m_InstrumentActiveSound ) m_InstrumentActiveSound.SoundStop();
	}
	
    bool IsPlaying()
    {
        return m_InstrumentPlaying;
    }
};