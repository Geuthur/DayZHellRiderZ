class HRZ_StonedMdfr: ModifierBase
{
	int LIFETIME = 360;  //currently the same as the config
	
	static const int CHANCE_OF_LAUGHTER = 50;
	static const int CHANCE_OF_COUGH = 15;
	static const int WATER_DRAIN_WHILE_STONED = 2;
	
	float 			m_LastWaterLevel;
	ref HumanMovementState		m_MovementState	= new HumanMovementState();

	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_IsPersistent 		= false;
		m_ID 				= HRZ_eModifiers.MDF_Stoned;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 10;
	}
	
	override string GetDebugText()
	{
		return (LIFETIME - GetAttachedTime()).ToString();
	}
	
	override protected void OnActivate(PlayerBase player)
	{
	player.GetSymptomManager().QueueUpSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_CANNABIS);
	}
	
	override protected void OnDeactivate(PlayerBase player)
	{
	player.GetSymptomManager().RemoveSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_CANNABIS);
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
		int roll2 = Math.RandomInt(0, 100);	
		if ( roll < CHANCE_OF_COUGH )
		{
			SymptomBase cough_symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_COUGH);
			if (cough_symptom)
				cough_symptom.SetDuration(5);
			
		} else if ( roll2 < CHANCE_OF_LAUGHTER )
		{
			SymptomBase laugh_symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
			if (laugh_symptom)
				laugh_symptom.SetDuration(5);
		}
		if (player.GetStatWater().Get() > (WATER_DRAIN_WHILE_STONED))
	 		player.GetStatWater().Add(-1 * WATER_DRAIN_WHILE_STONED);
			float currentshock =  player.GetHealth("GlobalHealth", "Shock");
			player.AddHealth("GlobalHealth", "Shock", WATER_DRAIN_WHILE_STONED * deltaT);
	}
};