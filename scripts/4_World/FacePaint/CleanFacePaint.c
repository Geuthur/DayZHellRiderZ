class HRZ_ActionCleanFaceCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(4);
	}
};

class HRZ_ActionCleanFace: ActionContinuousBase
{
	void HRZ_ActionCleanFace()
	{
		m_CallbackClass = HRZ_ActionCleanFaceCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_SHAVE;
		m_FullBody = false;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTSelf;
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{
            return true;
        }             
        if (player.HRZ_GetFacePaint() == "None")
        {
            return false;
        }
        return true;
	}
	
	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "Wasche Farbe von Gesicht";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		action_data.m_Player.HRZ_SetFacePaint(0);
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
        action_data.m_MainItem.AddQuantity(-25);
        if (action_data.m_MainItem.GetQuantity() <= 0 ) {
            action_data.m_MainItem.Delete();
        }        
	}
};