class HRZ_ActionBlowWhistleWolfCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(3.5);
	}
};

class HRZ_ActionBlowWhistleWolf: ActionContinuousBase
{
	ref NoiseParams noise;

	void HRZ_ActionBlowWhistleWolf()
	{
		m_CallbackClass = HRZ_ActionBlowWhistleWolfCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_TAKETEMPSELF;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONMOD_TAKETEMPSELF;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		noise = new NoiseParams();
		noise.LoadFromPath("CfgVehicles HRZ_Whistle_Wolf cfgWhistle");		
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
		return "Pfeifen";
	}

	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		GetGame().RPCSingleParam( action_data.m_MainItem, HRZ_SoundTypeWhistleWolf.DEFAULT, NULL, true );
		GetGame().GetNoiseSystem().AddNoisePos(action_data.m_MainItem, action_data.m_MainItem.GetPosition(), noise, 1.0);
	}

	override void OnEndServer( ActionData action_data )
	{
        GetGame().RPCSingleParam( action_data.m_MainItem, HRZ_SoundTypeWhistleWolf.STOP, NULL, true );
        super.OnEndServer( action_data );
	}     

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		return true;
	}
};