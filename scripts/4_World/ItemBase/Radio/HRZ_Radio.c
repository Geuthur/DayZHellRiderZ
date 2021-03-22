class HRZ_Radio_Base extends ItemBase
{
    protected ItemBase m_Cassette;
    protected Object m_VisualCassette;
    protected bool m_Playing;
    protected EffectSound m_ActiveSound;
    
    //Network synced data
    protected bool m_SyncStatus;
    
    void HRZ_Radio_Base()
    {
        RegisterNetSyncVariableBool( "m_SyncStatus" );
    }
    
    override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
        
        if( m_SyncStatus && !IsPlaying() ) TurnOn();
        if( !m_SyncStatus && IsPlaying() ) TurnOff();
	}	
   
    override void SetActions()
	{
        super.SetActions();

		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
		AddAction(ActionTurnOnWhileOnGround);
		AddAction(ActionTurnOffWhileOnGround);
//		AddAction(ActionAttach);
//		AddAction(ActionAttachOnSelection);
//		AddAction(ActionDetach);
//		AddAction(ActionTurnOnTransmitter);
//		AddAction(ActionTurnOnSpotlight);
	}
    
	override void EEItemAttached( EntityAI item, string slot_name )
	{
        super.EEItemAttached( item, slot_name );
        
        if( slot_name == "Cassette" )
        {
            m_Cassette = ItemBase.Cast( item );
            
            EntityAI EAI = this;
			
            if ( !EAI.GetInventory().IsInCargo()) {            
                ShowCassette();
            }    
        }
	}
    
	override void EEItemDetached( EntityAI item, string slot_name )
	{
        super.EEItemDetached( item, slot_name );
        
        if( slot_name == "Cassette" )
        {
            TurnOff();
            
            HideCassette();
            
            m_Cassette = NULL;
        }
        else if ( slot_name == "BatteryD" )
        {
            TurnOff();            
        }
    }
    
	override void OnMovedInsideCargo( EntityAI container )
	{
		HideCassette();
        TurnOff();
	}
	
	override void OnRemovedFromCargo( EntityAI container )
	{
		ShowCassette();
	}
	
	// Dont Work ATM Fix is on the Todo
    protected void ShowCassette()
    {
        return;
        if( !m_Cassette || m_VisualCassette ) return;
        //Print("Cassette Show");
        m_VisualCassette = GetGame().CreateObject( m_Cassette.GetType(), GetPosition(), true, false, false );
        m_VisualCassette.SetPosition( "0.05466 0.0784 0.018" );
        m_VisualCassette.SetYawPitchRoll( "0 0 180" );
        AddChild( m_VisualCassette, -1, false );
    };    
	
    protected void HideCassette()
    {
        if( m_VisualCassette )
        {
            if( m_VisualCassette.GetParent() ) RemoveChild( m_VisualCassette );
            
            GetGame().ObjectDelete( m_VisualCassette );
            
            m_VisualCassette = NULL;
        }
    };
	
    void TurnOn()
    {
        if ( GetCompEM().CanWork() ) GetCompEM().SwitchOn();
    } 
    
    void TurnOff()
    {
        GetCompEM().SwitchOff();
    }

    override void OnWorkStart()
    {
        if (!Play())
        {
            TurnOff();
        }
    }

    override void OnWorkStop()
    {
        Stop();
    }

    
    bool Play()
    {
        if( !m_Cassette ) return false;
        
        string cfgPath = "CfgVehicles " + m_Cassette.GetType() + " CfgCassette" ;
        
        if( !GetGame().ConfigIsExisting( cfgPath ) ) return false;
        
        if ( m_ActiveSound ) m_ActiveSound.SoundStop();

		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
            m_ActiveSound = SEffectManager.PlaySoundOnObject( GetGame().ConfigGetTextOut( cfgPath + " soundSet" ), this );
            m_ActiveSound.SetSoundAutodestroy( true );
            SetTapeVolume();
        }
        
        m_Playing = true;
        m_SyncStatus = true;
        return true;
    }
    
    void SetTapeVolume()
    {
    }
    
    void Stop()
    {
        m_Playing = false;
        m_SyncStatus = false;

        if ( m_ActiveSound ) m_ActiveSound.SoundStop();

        if ( !m_Cassette ) return;       
    }
    
    bool IsPlaying()
    {
        return m_Playing;
    }
};