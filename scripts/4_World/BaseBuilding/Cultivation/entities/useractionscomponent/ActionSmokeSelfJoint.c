class HRZ_ActionJointSmokeSelfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(2.00);
	}
};

class HRZ_ActionJointSmokeSelf: ActionContinuousBase
{
	//const string SMOKE_SOUND                  = "Smoking_SoundSet";
	bool m_ApplyModifier;
	int CurrentCycles;
	
	void HRZ_ActionJointSmokeSelf()
	{
		m_CallbackClass = HRZ_ActionJointSmokeSelfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_TAKETEMPSELF;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_TAKETEMPSELF;	
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}
	
	override bool HasProneException()
	{
		return true;
	}
	
	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "Rauchen";
	}

	void BlowSmoke( ActionData action_data )
	{
		if ( GetGame().IsMultiplayer() && GetGame().IsClient() || !GetGame().IsMultiplayer() ) {
			PlayerBase player = action_data.m_Player;

			int boneIdx = player.GetBoneIndexByName("Head");
			if( boneIdx != -1 )
			{
				EffectParticle eff = new EffBreathVapourHeavy();		
				if( eff )
				{
					vector player_pos = player.GetPosition();
					eff.SetDecalOwner( player );
					SEffectManager.PlayInWorld( eff, "-0.03 0.15 0" );
					Particle p = eff.GetParticle();
					player.AddChild(p, boneIdx);
				}
			}
		}
	}

	override void ApplyModifiers( ActionData action_data )
	{
		HRZ_Joint_Base joint = HRZ_Joint_Base.Cast(action_data.m_MainItem);
				
		if (joint) {
			joint.MakeStoned(action_data.m_Player);
			if (CurrentCycles >= 50)
			    joint.MakePuke(action_data.m_Player);	
		}	
	}

	override void OnFinishProgressClient( ActionData action_data )
	{
		PlayerBase player = action_data.m_Player;
		HRZ_Joint_Base joint = HRZ_Joint_Base.Cast(action_data.m_MainItem);
		string joint_type = joint.GetType();
		
		BlowSmoke( action_data );  
		
		if (joint) {
			player.AddValueToJointValue(1);
			CurrentCycles = player.GetJointCycles();
		}
			
		super.OnFinishProgressClient(action_data);
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		ItemBase ib = ItemBase.Cast(action_data.m_MainItem);
		
		ib.GetCompEM().ConsumeEnergy(20);

		BlowSmoke( action_data );
		
		if (!m_ApplyModifier)
		{
		ApplyModifiers(action_data);
		m_ApplyModifier = true;
		}
		
		GetGame().RPCSingleParam( action_data.m_MainItem, HRZ_SoundTypeSmoking.EXHALE, NULL, true );
	}

	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		
		GetGame().RPCSingleParam( action_data.m_MainItem, HRZ_SoundTypeSmoking.INHALE, NULL, true );
	}	

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		HRZ_Joint_Base cig = HRZ_Joint_Base.Cast(item);
		if (cig) {
			return cig.IsIgnited();
		}
		return false;
	}
};