class HRZ_TestMdfr : ModifierBase
{
	int LIFETIME = 180;  //currently the same as the config
	float m_Time;
	
	static const int CHANCE_OF_VOMIT = 1;
	
	ref HumanMovementState		m_MovementState	= new HumanMovementState();

	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_IsPersistent 		= false;
		m_ID 				= 105;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 10;
	}
	
	override string GetDebugText()
	{
		return (LIFETIME - GetAttachedTime()).ToString();
	}

	override protected void OnActivate(PlayerBase player)
	{
	player.GetSymptomManager().QueueUpSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_SHAKEHRZ);
	}
	
	override protected void OnDeactivate(PlayerBase player)
	{
	player.GetSymptomManager().RemoveSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_SHAKEHRZ);
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
		int roll = Math.RandomInt(0, 100);	
		m_Time += deltaT;
		//Print (m_Time);
 	   	float power = Math.Sin(m_Time);
		//Print (power);
		
		//PPEffects.SetBlurFlashbang(power);
		
	}
};
