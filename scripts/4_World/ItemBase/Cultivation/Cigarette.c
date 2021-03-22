class HRZ_CigaretteLight extends PointLightBase
{
	void HRZ_CigaretteLight()
	{
		SetVisibleDuringDaylight(true);
		SetRadiusTo( 0.05 );
		SetBrightnessTo(15);
		SetCastShadow(false);
		FadeIn(1);
		SetFadeOutTime(1);
		SetDiffuseColor(0.8, 0.2, 0.1);
		SetAmbientColor(0.8, 0.2, 0.1);

		SetFlareVisible(false);
	}
}

enum HRZ_CigaretteBurningState
{
	NOT_BURNING,
	BURNING
};

enum HRZ_SoundTypeSmoking
{
	INHALE,
	EXHALE
}

class HRZ_Cigarette_Base : ItemBase
{	
	private int	m_BurningState = HRZ_CigaretteBurningState.NOT_BURNING;

	HRZ_CigaretteLight m_Light;
	ref protected EffectSound 	m_SmokingSound;

	void HRZ_Cigarette_Base()
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
	
	void MakeHusten(PlayerBase player)
	{
		if( player.GetModifiersManager().IsModifierActive(HRZ_eModifiers.MDF_Husten) ) { //effectively resets the timer
			return;  //let previous modifier finish
		}
		player.GetModifiersManager().ActivateModifier(HRZ_eModifiers.MDF_Husten);
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
		if ( GetCompEM().GetEnergy() >= 3 )
		{
			return true;
		}
		return false;
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
		return true;

		if ( !GetCompEM().CheckWetness() )
			return false;
		
		if ( !GetCompEM().CanWork() )
			return false;

		if ( GetCompEM().GetEnergy() >= 3 )
			return true;
		
		return false;
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
		SetBurningState(HRZ_CigaretteBurningState.BURNING);
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // Client side
		{
			CreateCigaretteLight();
		}		
	}
	
	override void OnWorkStop()
	{
		if ( GetGame().IsServer() )
		{
			SetBurningStateSynchronized(HRZ_CigaretteBurningState.NOT_BURNING);
		} else {
			SetBurningState(HRZ_CigaretteBurningState.NOT_BURNING);
		}
		DecreaseHealth(100);		
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
		
			m_Light.AttachOnMemoryPoint(this, "light");
			
		SetLit();
	}	

	void SetLit()
	{
	}
		
};

class HRZ_Cigarette: HRZ_Cigarette_Base {
	override void SetLit()
	{
		SetObjectTexture(0, "Client\\Smoking\\cigarettes\\data\\cigarette_lit_co.paa");
		SetObjectMaterial(0, "Client\\Smoking\\cigarettes\\data\\cigarette_lit.rvmat");
		SetObjectTexture(1, "Client\\Smoking\\cigarettes\\data\\cigarette_lit_co.paa");
		SetObjectMaterial(1, "Client\\Smoking\\cigarettes\\data\\cigarette_lit.rvmat");
	}	
};