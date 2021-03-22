enum HRZ_SherlockPipeBurningState
{
	NOT_BURNING,
	BURNING
};

class HRZ_Sherlockpipe : Clothing
{	
	private int	m_BurningState = HRZ_SherlockPipeBurningState.NOT_BURNING;
	static vector m_OnMaskLocalPos = Vector(-0.03,0.20,0.05); // x z y

	HRZ_CigaretteLight m_Light;
	ref protected EffectSound 	m_SmokingSound;

	void HRZ_Sherlockpipe()
	{
		RegisterNetSyncVariableInt("m_BurningState");
	}

	override void SetActions()
	{
		super.SetActions();		
		AddAction(ActionLightItemOnFire);
		AddAction(HRZ_ActionSmokeSelf);
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext  ctx) 
	{
		super.OnRPC(sender, rpc_type, ctx);
			
		switch(rpc_type)
		{
			case HRZ_SoundTypeSmoking.INHALE:
				PlaySmokingSound();
			break;
			case HRZ_SoundTypeSmoking.EXHALE:
				PlayExhaleSound();
			break;
		}
	}

	void PlaySmokingSound()
	{
		m_SmokingSound = SEffectManager.PlaySoundOnObject( "Smoking_SoundSet", this );
		m_SmokingSound.SetSoundAutodestroy( true );
	}

	void PlayExhaleSound()
	{
		m_SmokingSound = SEffectManager.PlaySoundOnObject( "HRZ_Exhale_SoundSet", this );
		m_SmokingSound.SetSoundAutodestroy( true );
	}
	
	override bool IsClothing()
	{
		return false;
	}
	
	override void OnWasAttached( EntityAI parent, int slot_id )
	{
		if ( m_Light  &&  parent.IsInherited(PlayerBase) )
		{
			AttachLightOnMask( PlayerBase.Cast(parent) );
		}
	}
	
	override void OnWasDetached( EntityAI parent, int slot_id )
	{
		if ( m_Light  &&  parent.IsInherited(PlayerBase) )
		{
			m_Light.DetachFromParent();
			m_Light.AttachOnMemoryPoint(this, "light");
		}
	}
	
	void MakeHusten(PlayerBase player)
	{
		if( player.GetModifiersManager().IsModifierActive(101) ) { //effectively resets the timer
			return;  //let previous modifier finish
		}
		player.GetModifiersManager().ActivateModifier(101);
	}

	override bool CanPutInCargo( EntityAI parent )
	{
		if( !super.CanPutInCargo(parent) ) {return false;}
		return CanBeTakenAsCargo();
	}
	
	override bool CanRemoveFromCargo(EntityAI parent)
	{
		return CanBeTakenAsCargo();
	}
	
	bool CanBeTakenAsCargo()
	{
		return !GetCompEM().IsWorking();
	}
	
	override bool IsIgnited()
	{
		return GetCompEM().IsWorking();
	}
	
	override bool CanIgniteItem(EntityAI ignite_target = NULL)
	{
		return GetCompEM().IsWorking();
	}
	
	override bool HasFlammableMaterial()
	{
			return true;
	}
	
	void SetBurningState(int state_number)
	{
		m_BurningState = state_number;
	}

	void SetBurningStateSynchronized(int state_number)
	{
		if ( GetGame().IsServer() )
		{
			m_BurningState = state_number;
			SetSynchDirty();
		}
	}

	override bool CanBeIgnitedBy(EntityAI igniter = NULL)
	{
		if ( GetCompEM().GetEnergy() >= 3 )
			return true;
		return false;
	}
	
	override bool CanReleaseAttachment (EntityAI attachment)
	{
		if( !super.CanReleaseAttachment( attachment ) )
			return false;
		return !GetCompEM().IsWorking();
	}
	
	override void OnIgnitedThis(EntityAI fire_source)
	{
		GetCompEM().SwitchOn();
	}
	
	override void OnSwitchOn()
	{
		if ( !GetCompEM().HasEnoughStoredEnergy() )
			GetCompEM().SwitchOff();
	}
	
	override void OnWorkStart()
	{
		SetBurningState(HRZ_SherlockPipeBurningState.BURNING);
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // Client side
		{
			CreateCigaretteLight();
		}		
	}
	
	override void OnWorkStop()
	{
		if ( GetGame().IsServer() )
		{
			SetBurningStateSynchronized(HRZ_SherlockPipeBurningState.NOT_BURNING);
		} else {
			SetBurningState(HRZ_SherlockPipeBurningState.NOT_BURNING);
		}
		
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // Client side
		{
			if (m_Light)
				m_Light.FadeOut();
			
			m_Light = NULL;
		}
	}
	
	void CreateCigaretteLight()
	{
		if (!m_Light)
			m_Light = HRZ_CigaretteLight.Cast(  ScriptedLightBase.CreateLight( HRZ_CigaretteLight, "0 0 0")  );

		bool is_on_mask = false;
		PlayerBase player = PlayerBase.Cast( GetHierarchyParent() );
		
		if (player)
		{
			ItemBase att_item = player.GetItemOnSlot("Mask");
			
			if (att_item == this)
			{
				is_on_mask = true;
			}
		}
		
		
		if (is_on_mask)
		{
			AttachLightOnMask(player);
		}
		else
		{
			m_Light.AttachOnMemoryPoint(this, "light");
		}
	}	

	void AttachLightOnMask(PlayerBase player)
	{
		int boneIdx = player.GetBoneIndexByName("Head");
		
		if( boneIdx != -1 )
		{
			if ( m_Light.GetParent() )
				m_Light.DetachFromParent();
			
			m_Light.SetPosition( m_OnMaskLocalPos );
			
			player.AddChild(m_Light, boneIdx);
		}
	}
};