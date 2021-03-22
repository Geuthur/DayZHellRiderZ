class HRZ_HustenMdfr: ModifierBase
{
	int LIFETIME = 30;  //currently the same as the config
	
	static const int CHANCE_OF_COUGH = 90;
	
	ref HumanMovementState		m_MovementState	= new HumanMovementState();

	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_IsPersistent 		= false;
		m_ID 				= HRZ_eModifiers.MDF_Husten;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 10;
	}
	
	override string GetDebugText()
	{
		return (LIFETIME - GetAttachedTime()).ToString();
	}
	
	override protected void OnActivate(PlayerBase player)
	{
	}
	
	override protected void OnDeactivate(PlayerBase player)
	{
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
		if ( roll < CHANCE_OF_COUGH )
		{
			SymptomBase cough_symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
			if (cough_symptom)
				cough_symptom.SetDuration(5);
			
		} 
	}
};