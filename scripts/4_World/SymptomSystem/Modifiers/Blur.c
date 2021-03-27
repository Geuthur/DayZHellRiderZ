class HRZ_BlurMdfr: ModifierBase
{
	int LIFETIME = 30;  //currently the same as the config
	
	static const int CHANCE_OF_FREEZE = 70;
	static const int CHANCE_OF_SHAKE = 50;
	static const int CHANCE_OF_VOMIT = 1;
	
	private const float 	HEALTH_DECREMENT_PER_SEC = -0.2;
	private const float 	SHOCK_DECREMENT_PER_SEC = -2;
	private const float 	SHOCK_LIMIT = 0;
	
	ref HumanMovementState		m_MovementState	= new HumanMovementState();

	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_IsPersistent 		= false;
		m_ID 				= HRZ_eModifiers.MDF_Blur;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 10;
	}
	
	override string GetDebugText()
	{
		return (LIFETIME - GetAttachedTime()).ToString();
	}

	override protected void OnActivate(PlayerBase player)
	{
	player.GetSymptomManager().QueueUpSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_BLUR);
	}
	
	override protected void OnDeactivate(PlayerBase player)
	{
	player.GetSymptomManager().RemoveSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_BLUR);
	}
	
	override bool ActivateCondition(PlayerBase player)
	{
		return false;
	}

	override bool DeactivateCondition(PlayerBase player)
	{
		float attached_time = GetAttachedTime();
		
		if ( attached_time >= LIFETIME )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	override protected void OnTick(PlayerBase player, float deltaT)
	{
	}
};