class HRZ_CodeLock extends ItemBase
{
	// Variable Definitions \\
	protected EffectSound 		m_Sound;

	// Timer related variables
    ref Timer           		m_LockOut;
    ref Timer           		m_Tick;
    protected int 				m_RemainingTimer;
    protected int 				m_NoSynchRemainingTimer;
	protected bool				m_ClientTicking				= false;
    protected bool 				m_TimerActive				= false;
    protected int 				m_BadAttempts				= 0;
	const int					m_MaxAttempts				= 3;
    const int 					m_LockOutTimer    			= 30;
    const int 					m_TickInterval    			= 1;

	// Persistence related variables
	string 						m_PassCodeLock;
	bool 						m_CodeLockIsLocked;
	protected LockAction 		m_LockActionPerformed 		= LockAction.NONE;
	const string 				SOUND_LOCK_OPEN 			= "combinationlock_open_SoundSet";
	const string 				SOUND_LOCK_CLOSE 			= "combinationlock_close_SoundSet";
	
	//================================================================
	// Lockout Functions
	//================================================================

    // Create and run the timer.
    void HRZ_StartLockout()
    {
		// Set variables
		m_TimerActive 		= true;

		SetSynchDirty();

		m_RemainingTimer 	= m_LockOutTimer + 1;

        // Create a timer and run it for x seconds
        m_LockOut = new Timer;
        m_LockOut.Run( m_LockOutTimer, this, "HRZ_RemoveTimer", null, false );
    }

    void HRZ_Tick()  // So this is function declaration
    {
        // Check if the timer is active, don't run this for no reason.
        if ( m_TimerActive ) 											// This checks to make sure the timer is active, so it doesn't do shit for no reason
        {
            m_Tick = new Timer; 										// This creates a new timer to be ran
            m_Tick.Run( m_TickInterval, this, "HRZ_Tick", null, false ); 	// This runs the newly created timer
        }

		m_RemainingTimer --; 											// This decrements ( reduces by 1 ) m_RemainingTimer
		SetSynchDirty();
    }

    // Reset varibles so user can attempt to "login"
    void HRZ_RemoveTimer()
    {
        m_BadAttempts = 0;
        m_TimerActive = false;

		SetSynchDirty();
    }

	void HRZ_IncrementBadAttempts()
	{
		m_BadAttempts++;
	}

	void HRZ_ClearBadAttempts()
	{
		m_BadAttempts = 0;
	}

	bool HRZ_IsTimerActive()
	{
		return m_TimerActive;
	}

	int HRZ_GetBadAttempts()
	{
		return m_BadAttempts;
	}

	int HRZ_GetMaxAttempts()
	{
		return m_MaxAttempts;
	}

	int HRZ_GetRemainingTimer()
	{
		return m_RemainingTimer;
	}

	bool HRZ_IsClientTicking()
	{
		return m_ClientTicking;
	}
	// ---	
	
	//================================================================
	// Lock Core
	//================================================================
	void HRZ_CodeLock()
	{
		SetBaseLockValues();

		RegisterNetSyncVariableBool( "m_CodeLockIsLocked" );
		RegisterNetSyncVariableBool( "m_TimerActive" );
		RegisterNetSyncVariableInt( "m_LockActionPerformed", 0, LockAction.COUNT );
		RegisterNetSyncVariableInt( "m_RemainingTimer", 0, m_LockOutTimer + 1 );
	}
	
	protected void SetBaseLockValues()
	{
		//set lock init values
		m_PassCodeLock = "reset";
		m_CodeLockIsLocked = false;
	}

	override void EEInit()
	{
		super.EEInit();
		//set visual on init
		UpdateVisuals();
	}	
	
	// --- EVENTS
	override void OnStoreSave( ParamsWriteContext ctx )
	{   
		super.OnStoreSave( ctx );
		
		//write data
		ctx.Write( m_PassCodeLock );
		ctx.Write( m_CodeLockIsLocked );
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		
		//--- Combination Lock data ---
		if ( !ctx.Read( m_PassCodeLock ) )
		{
			m_PassCodeLock = "reset";
			return false;
		}
		
		//combination locked
		if ( !ctx.Read( m_CodeLockIsLocked ) )
		{
			m_CodeLockIsLocked = false;
			return false;
		}

		return true;
	}
	
	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		//synchronize
		Synchronize();
	}
	
	// --- SYNCHRONIZATION
	void Synchronize()
	{
		bsbDebugPrint("[bsb] HRZ_CodeLock.Synchronize " + " m_PassCodeLock=" + m_PassCodeLock + " m_CodeLockIsLocked=" + m_CodeLockIsLocked);
		if ( GetGame().IsServer() )
		{
			SetSynchDirty();
			
			UpdateVisuals();
		}
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if ( m_RemainingTimer != m_NoSynchRemainingTimer ) 						// Check to see if this variable was synced. If not, don't run this.
		{
			m_NoSynchRemainingTimer = m_RemainingTimer;							// Set the local value to the synced value.

			if ( GetGame().GetUIManager().IsMenuOpen( HRZ_ENTER_CODE_MENU ) )		// If the menu is open
			{
				if ( m_RemainingTimer > 0 )
				{
					g_HRZLockRPCManager.m_HRZEnterCodeMenu.HRZ_LockedOut();
				}
				else if ( m_RemainingTimer <= 0 )
				{
					g_HRZLockRPCManager.m_HRZEnterCodeMenu.txt_EditPin.SetText("Password Eingabe");
				}
			}
		}

		//update visuals (client)
		UpdateVisuals();
		
		//update sound (client)
		UpdateSound();
		
		bsbDebugPrint("[bsb] HRZ_CodeLock.OnVariablesSynchronized " + " m_PassCodeLock=" + m_PassCodeLock + " m_CodeLockIsLocked=" + m_CodeLockIsLocked);
	}
	
	void SetPasscode( string passcode )
	{
		m_PassCodeLock = passcode;
	}
	
	void SetLockedState( bool state )
	{
		m_CodeLockIsLocked = state;
	}
	
	//Lock lock
	void LockServer( EntityAI parent, string passcode )
	{
		bsbDebugPrint("[bsb] HRZ_CodeLock.LockServer " + " m_PassCodeLock=" + m_PassCodeLock + " m_CodeLockIsLocked=" + m_CodeLockIsLocked);
		
		// Lock attachment slot
		InventoryLocation inventory_location = new InventoryLocation;
		GetInventory().GetCurrentInventoryLocation( inventory_location );		
		parent.GetInventory().SetSlotLock( inventory_location.GetSlot(), true );

		SetPasscode( passcode );
		SetLockedState( true );

		m_LockActionPerformed = LockAction.LOCKED;

		Synchronize();
	}
	
	void UnlockServer( EntityAI player, EntityAI parent )
	{
		bsbDebugPrint("[bsb] HRZ_CodeLock.UnlockServer " + " m_PassCodeLock=" + m_PassCodeLock + " m_CodeLockIsLocked=" + m_CodeLockIsLocked);
		
		Fence fence = Fence.Cast( parent );
		
		//set slot unlock
		InventoryLocation inventory_location = new InventoryLocation;
		GetInventory().GetCurrentInventoryLocation( inventory_location );			
		fence.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );	
		
		//drop entity from attachment slot
		if (player)
			player.ServerDropEntity( this );
		else
			parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
		SetPosition( fence.GetKitSpawnPosition() );
		PlaceOnSurface();
	
		SetPasscode( "reset" );
		SetLockedState( false );

		m_LockActionPerformed = LockAction.UNLOCKED;
		SetTakeable(true);
		
		Synchronize();
	}
	
	bool IsLocked( string ui_Passcode)
	{
		if ( m_PassCodeLock != ui_Passcode )
		{
			return true;
		}
		
		return false;
	}
	
	bool GetLockState()
	{
		return m_CodeLockIsLocked;
	}

	// --- VISUALS
	void UpdateVisuals()
	{
		//Client/Server
		if ( GetLockState() )
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( HideItem, 		0, false );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( ShowAttached, 	0, false );
		}
		else
		{
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( ShowItem, 		0, false );
			GetGame().GetCallQueue( CALL_CATEGORY_GAMEPLAY ).CallLater( HideAttached, 	0, false );
		}
	}
	
	void UpdateSound()
	{
		//was locked
		if ( m_LockActionPerformed == LockAction.LOCKED )
		{
			SoundLockClose();
		}
		
		//was unlocked
		if ( m_LockActionPerformed == LockAction.UNLOCKED )
		{
			SoundLockOpen();
		}
	}
	
	//Show/Hide anims
	protected void ShowItem()
	{
		SetAnimationPhase( "Combination_Lock_Item", 0 );
		SetAnimationPhase( "Lock_Item_1", 			0 );
		SetAnimationPhase( "Lock_Item_2", 			0 );
	}
	
	protected void HideItem()
	{
		SetAnimationPhase( "Combination_Lock_Item", 1 );
		SetAnimationPhase( "Lock_Item_1", 			1 );
		SetAnimationPhase( "Lock_Item_2", 			1 );
	}
	
	protected void ShowAttached()
	{
		SetAnimationPhase( "Combination_Lock_Attached", 0 );
		SetAnimationPhase( "Lock_Attached_1", 			0 );
		SetAnimationPhase( "Lock_Attached_2", 			0 );
	}
	
	protected void HideAttached()
	{
		SetAnimationPhase( "Combination_Lock_Attached", 1 );
		SetAnimationPhase( "Lock_Attached_1", 			1 );
		SetAnimationPhase( "Lock_Attached_2", 			1 );
	}	
	// ---	
	
	//================================================================
	// SOUNDS
	//================================================================
	protected void SoundLockOpen()
	{
		PlaySoundSet( m_Sound, SOUND_LOCK_OPEN, 0, 0 );
	}

	protected void SoundLockClose()
	{
		PlaySoundSet( m_Sound, SOUND_LOCK_CLOSE, 0, 0 );
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction( HRZ_ActionAttachCodeLock );
	}
}
