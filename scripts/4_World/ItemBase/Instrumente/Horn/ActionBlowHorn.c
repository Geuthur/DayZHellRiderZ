class HRZ_ActionBlowHornCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
        HRZ_Horn horn;
        Class.CastTo(horn, m_ActionData.m_MainItem);
        int l = horn.GetHornSoundLength();
        m_ActionData.m_ActionComponent = new CAContinuousTime(l);
	}
};

class HRZ_ActionBlowHorn: ActionContinuousBase
{
	ref NoiseParams noise;

	void HRZ_ActionBlowHorn()
	{
		m_CallbackClass = HRZ_ActionBlowHornCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_TAKETEMPSELF;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_TAKETEMPSELF;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		noise = new NoiseParams();
		noise.LoadFromPath("CfgVehicles HRZ_Horn cfgHorn");		
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
		return "Benutze Horn";
	}

	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		GetGame().RPCSingleParam( action_data.m_MainItem, 0, NULL, true );
		GetGame().GetNoiseSystem().AddNoisePos(action_data.m_MainItem, action_data.m_MainItem.GetPosition(), noise, 1.0);
	}

	override void OnEndServer( ActionData action_data )
	{
        GetGame().RPCSingleParam( action_data.m_MainItem, 1, NULL, true );
        super.OnEndServer( action_data );
	}        

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
};