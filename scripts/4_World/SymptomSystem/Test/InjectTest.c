class HRZ_ActionInjectTestCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(0.5);
	}
};

class HRZ_ActionInjectTest: ActionContinuousBase
{	
	void HRZ_ActionInjectTest()
	{
		m_CallbackClass = HRZ_ActionInjectTestCB;
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
		return "Test Spritzen";
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
        HRZ_Test_Syringe ps = HRZ_Test_Syringe.Cast(action_data.m_MainItem);

        if ( ps )
        {
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
           	//ps.AddQuantity(-100);
            //if (ps.GetQuantity() <= 0 ) {
            //   ps.Delete();
            //}
        }
		EntityAI item = action_data.m_MainItem;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		{
			if(action_data.m_MainItem && player)
			{
				if( player.GetModifiersManager().IsModifierActive(HRZ_eModifiers.MDF_Blur) ) { //effectively resets the timer
					return;  //let previous modifier finish
				}
				// Kokain Trigger Symptom
				player.GetModifiersManager().ActivateModifier(HRZ_eModifiers.MDF_Blur);
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

class HRZ_ActionInjectTest2: ActionContinuousBase
{
	void HRZ_ActionInjectTest2()
	{
		m_CallbackClass = HRZ_ActionInjectTestCB;
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
		return "Test2 Spritzen";
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
        HRZ_Test_Syringe2 ps = HRZ_Test_Syringe2.Cast(action_data.m_MainItem);

        if ( ps )
        {
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
           	//ps.AddQuantity(-100);
            //if (ps.GetQuantity() <= 0 ) {
            //   ps.Delete();
            //}
        }
		EntityAI item = action_data.m_MainItem;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		{
			if(action_data.m_MainItem && player)
			{
				if( player.GetModifiersManager().IsModifierActive(HRZ_eModifiers.MDF_Test) ) { //effectively resets the timer
					return;  //let previous modifier finish
				}
				// Kokain Trigger Symptom
				player.GetModifiersManager().ActivateModifier(HRZ_eModifiers.MDF_Test);
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