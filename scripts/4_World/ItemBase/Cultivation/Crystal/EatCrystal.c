class HRZ_ActionEatCrackCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(5);
	}
};

class HRZ_ActionEatCrack: ActionContinuousBase
{
	void HRZ_ActionEatCrack()
	{
		m_CallbackClass = HRZ_ActionEatCrackCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_EAT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = false;
	}

	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTSelf;
	}
	
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{
            return true;
        }
		return true;
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
		return "Iss Crystal Meth";
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
        HRZ_Crystal_Base ps = HRZ_Crystal_Base.Cast(action_data.m_MainItem);

        if ( ps )
        {
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
            ps.AddQuantity(-25);
            if (ps.GetQuantity() <= 0 ) {
               ps.Delete();
            }
        }
		EntityAI item = action_data.m_MainItem;
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		{
			if(action_data.m_MainItem && player)
			{
				if( player.GetModifiersManager().IsModifierActive(HRZ_eModifiers.MDF_Crystal) ) { //effectively resets the timer
					return;  //let previous modifier finish
				}
				// Crystal Trigger Symptom
				player.GetModifiersManager().ActivateModifier(HRZ_eModifiers.MDF_Crystal);
			}
		}
	}
};
