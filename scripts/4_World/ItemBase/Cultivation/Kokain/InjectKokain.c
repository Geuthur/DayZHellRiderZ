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
};
