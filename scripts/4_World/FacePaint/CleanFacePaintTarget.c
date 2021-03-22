class HRZ_ActionCleanFaceTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(4);
	}
};

class HRZ_ActionCleanFaceTarget: ActionContinuousBase
{
	void HRZ_ActionCleanFaceTarget()
	{
		m_CallbackClass = HRZ_ActionCleanFaceTargetCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTMan(UAMaxDistances.DEFAULT);
	}

	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{
            return true;
        }

		PlayerBase man;
		Class.CastTo(man,  target.GetObject() );
		        
        if (man.HRZ_GetFacePaint() == "None")
        {
            return false;
        }
        return true;
	}	
	
	override string GetText()
	{
		return "Wasche Farbe von Person";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		PlayerBase man;
		if ( action_data.m_Target && Class.CastTo(man, action_data.m_Target.GetObject()) )
		{        
		    man.HRZ_SetFacePaint(0);
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
            action_data.m_MainItem.AddQuantity(-30);
            if (action_data.m_MainItem.GetQuantity() <= 0 ) {
                action_data.m_MainItem.Delete();
            }             
        }
	}
};