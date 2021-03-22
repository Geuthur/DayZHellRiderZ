class HRZ_ActionPaintFaceCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(4);
	}
};

class HRZ_ActionPaintFace: ActionContinuousBase
{
	void HRZ_ActionPaintFace()
	{
		m_CallbackClass = HRZ_ActionPaintFaceCB;
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
            return true;
        }
        return false;
	}
	
	override bool HasTarget()
	{
		return false;
	}
		
	override string GetText()
	{
		return "Farbe Auftragen";
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
        HRZ_FacePaint_Base ps = HRZ_FacePaint_Base.Cast(action_data.m_MainItem);

        if ( ps )
        {
		    action_data.m_Player.HRZ_SetFacePaint(ps.GetGlobalFacePaintIndex());
		    action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
            ps.AddQuantity(-50);
            if (ps.GetQuantity() <= 0 ) {
               ps.Delete();
            }
        }
	}
};