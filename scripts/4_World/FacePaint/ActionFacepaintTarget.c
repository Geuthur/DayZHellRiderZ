class HRZ_ActionPaintFaceTargetCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(4);
	}
};

class HRZ_ActionPaintFaceTarget: ActionContinuousBase
{
	void HRZ_ActionPaintFaceTarget()
	{
		m_CallbackClass = HRZ_ActionPaintFaceTargetCB;
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
	
	override string GetText()
	{
		return "Färbe andere Person";
	}
	
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{
            return true;
        }

		PlayerBase face;
		Class.CastTo(face, target.GetObject() );
		        
        if (face.HRZ_GetFacePaint() == "None")
        {
            return true;
        }
        return false;
	}	

	override void OnFinishProgressServer( ActionData action_data )
	{			
        HRZ_FacePaint_Base ps = HRZ_FacePaint_Base.Cast(action_data.m_MainItem);
        if ( ps )
        {
            PlayerBase face;
		    if ( action_data.m_Target && Class.CastTo(face, action_data.m_Target.GetObject()) )
		    {        
    		    face.HRZ_SetFacePaint(ps.GetGlobalFacePaintIndex());
		        action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
                ps.AddQuantity(-15);
                if (ps.GetQuantity() <= 0 ) {
                    ps.Delete();
                }                
            }
        }
	}
};