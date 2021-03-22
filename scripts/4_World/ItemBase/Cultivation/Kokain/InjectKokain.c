class HRZ_ActionInjectCrackCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class HRZ_ActionInjectKokain: ActionContinuousBase
{
	protected ref Timer m_TimerSmokeStart;
	
	void HRZ_ActionInjectKokain()
	{
		m_CallbackClass = HRZ_ActionInjectCrackCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_COLLECTBLOODSELF;
		m_FullBody = true;
		
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_MEDIUM;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}
		
	override bool HasTarget()
	{
		return false;
	}
	
	override string GetText()
	{
		return "Kokain Spritzen";
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
        HRZ_Kokain_Syringe ps = HRZ_Kokain_Syringe.Cast(action_data.m_MainItem);

        if ( ps )
        {
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
           	ps.AddQuantity(-100);
            if (ps.GetQuantity() <= 0 ) {
               ps.Delete();
            }
        }
		EntityAI item = action_data.m_MainItem;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		{
			if(action_data.m_MainItem && player)
			{
				if( player.GetModifiersManager().IsModifierActive(HRZ_eModifiers.MDF_Kokain) ) { //effectively resets the timer
					return;  //let previous modifier finish
				}
				// Kokain Trigger Symptom
				player.GetModifiersManager().ActivateModifier(HRZ_eModifiers.MDF_Kokain);
			}
		}
	}
	
	override void OnFinishProgressClient(ActionData action_data)
	{
		if( GetGame().IsClient() || !GetGame().IsMultiplayer())
		{
		}
	}

	/*
	void onAnimate(float deltaTime){
		m_TimerSmokeLoop = new Timer;
		print(m_TimerSmokeLoop);
 	   float power = Math.Sin(getTime());

	   // setRadialBlur(power, power);
	   // setChromAber(power * 2, power * 2);
	    //setOverlay(...);
	    //setVignette(...);
	    //setFilmGrain(...);
	    //setCameraEffects(...);
	    // etc...
	}
     //   int TimeMiliSeconds = 50;
     //   bool Loop = true;
     //   GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Function, TimeMiliSeconds , Loop );
     //if its a qui operations best to do use the CALL_CATEGORY_GUI instead of system

	void test (ActionData action_data, PlayerBase player)
	{
	while
		m_Time += deltatime;
			if( m_EffectStartTime <= 0 )
			{
				m_EffectStartTime = Math.RandomFloatInclusive(MIN_TIME_BETWEEN_EFFECTS, MAX_TIME_BETWEEN_EFFECTS);
				m_BlurDuration = Math.RandomFloatInclusive(BLUR_DURATION_TIME_MIN, BLUR_DURATION_TIME_MAX);
				m_BlurStrength = Math.RandomFloat(BLUR_STRENGTH_MIN, BLUR_STRENGTH_MAX);
				//PrintString("m_BlurDuration=" +m_BlurDuration.ToString());
			}
		
			if( m_EffectStartTime > 0 && m_Time > m_EffectStartTime )
			{
				m_EffectTime += deltatime / m_BlurDuration;
				float cos_value = Math.Sin(m_EffectTime  * Math.PI);
				float val = cos_value * m_BlurStrength;
				Print(val);
				PPEffects.SetBlurDrunk(val);
					//PrintString("cos=" +cos_value.ToString());
			
				if( m_EffectTime >= 1 )
				{
					m_EffectTime = 0;
					m_EffectStartTime = -1;
					m_Time = 0;
				}
			}
	}*/

};
