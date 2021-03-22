modded class PlayerBase {
	
	int activateJointSmokingEffect 		= true; // reduces the fluctuation/sway in aiming when a cigarette is smoked
	int smokingJointEffectDuration 		= 360; // Time in seconds for the effect to stop
	int jointCyclesToActivateEffect 	= 3;	// number of cigarettes consumed to activate the effect
	
	//ref Timer swayTimer;				// timer that resets the values after the effect is over
	ref Timer jointTimer;			// timer that resets the values after the effect is over
	
	bool m_HasConsumedJoint = false;
	int m_jointValue;				// the quantity of the cigarette, what the player consumed
	
	//getters for cig/joint smoke state
	bool HasConsumedJoint () {
		return m_HasConsumedJoint; 
	} 
	
	int GetJointCycles () {
		return m_jointValue;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// set to true if the player consumed a joint
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void AddValueToJointValue(int value) {	
		if(activateJointSmokingEffect) {
			m_jointValue += value;
					
			if((m_jointValue % jointCyclesToActivateEffect) == 0){	
				m_HasConsumedJoint = true;
				CannabisEffectsTriggered(m_jointValue);
				if (!jointTimer) { jointTimer = new Timer()};
				jointTimer.Stop();
				jointTimer.Run(smokingJointEffectDuration, this, "ResetJointValues", null, false);				
			}
		}
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// called by timer if the effect is over, resets all values that the player "consume again"
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void ResetJointValues() {
		m_HasConsumedJoint = false;
		CannabisEffectsTriggeredOff();
		m_jointValue = 0;
		jointTimer.Stop();
	}
	
	// Cannabis Visual Effect On.
    void CannabisEffectsTriggered(int cycles)
    { 
	  float multiplier;
	  int counter;			
		
	  counter = cycles / jointCyclesToActivateEffect;
	  multiplier = 1 + (0.25 * counter);


		if( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
		Material matiColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		Material radiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		Material rotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");

		matiColors.SetParam("Saturation", 2.0 );
		matiColors.SetParam("Vignette", 0.88);
		matiColors.SetParam("VignetteColor", 0.2);

		rotiBlur.SetParam("Power", 0.50 );
		rotiBlur.SetParam("MinDepth", 2.50 );
		rotiBlur.SetParam("MaxDepth", 10.0 );

		radiBlur.SetParam("OffsetX", 0.76 );
		}

    }

    // Cannabis Effects Triggered Off.
    void CannabisEffectsTriggeredOff()
    {

		if( GetGame().IsClient() || !GetGame().IsMultiplayer() )
		{
		//registers
		Material matiColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		Material radiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		Material rotiBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/rotblur");
		//settings
		matiColors.SetParam("Saturation", 1.0 );
		matiColors.SetParam("Vignette", 0.00);
		matiColors.SetParam("VignetteColor", 0.0);

		rotiBlur.SetParam("Power", 0.00 );
		rotiBlur.SetParam("MinDepth", 0.00 );
		rotiBlur.SetParam("MaxDepth", 0.00);

		radiBlur.SetParam("OffsetX", 0.00 );
		}

    }
	
	void randomEffects()
	{
		if( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
		Material gauss = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/gauss");
		gauss.SetParam("Intensity", 0.5);
		}
	}
	
	void randomEffectsOff()
	{
		if( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
		Material gauss = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/gauss");
		gauss.SetParam("Intensity", 0.0);
		}
	}

	override void Init()
      {
        
		super.Init();
		if ( GetGame().IsServer() || GetGame().IsMultiplayer() )
		{
	        DayzPlayerItemBehaviorCfg     heavy = new DayzPlayerItemBehaviorCfg;
			DayzPlayerItemBehaviorCfg 	onehand = new DayzPlayerItemBehaviorCfg;
	
	        heavy.SetHeavyItems();
			onehand.SetToolsOneHanded();
			
			GetDayZPlayerType().AddItemInHandsProfileIK("HRZ_Joint", "dz/anims/workspaces/player/player_main/player_main_1h.asi", onehand, "dz/anims/anm/player/ik/gear/thermometer.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("HRZ_JointTop", "dz/anims/workspaces/player/player_main/player_main_1h.asi", onehand, "dz/anims/anm/player/ik/gear/thermometer.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("HRZ_Cigarette", "dz/anims/workspaces/player/player_main/player_main_1h.asi", onehand, "dz/anims/anm/player/ik/gear/thermometer.anm");
		
	  	}
		
    }
}