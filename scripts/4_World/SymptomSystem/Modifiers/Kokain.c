class HRZ_KokainMdfr: ModifierBase
{
	int LIFETIME = 180;  //currently the same as the config
	
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
		m_ID 				= HRZ_eModifiers.MDF_Kokain;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 10;
	}
	
	override string GetDebugText()
	{
		return (LIFETIME - GetAttachedTime()).ToString();
	}

	override protected void OnActivate(PlayerBase player)
	{
	player.GetSymptomManager().QueueUpSecondarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
	player.GetSymptomManager().QueueUpSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_KOKAIN);
	}
	
	override protected void OnDeactivate(PlayerBase player)
	{
	player.GetSymptomManager().RemoveSecondarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
	player.GetSymptomManager().RemoveSecondarySymptom(HRZ_SymptomIDs.SYMPTOM_KOKAIN);
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
		int roll3 = Math.RandomInt(0, 100);
		
		if ( roll < CHANCE_OF_FREEZE )
		{
			SymptomBase freeze_symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_FREEZE);
			if (freeze_symptom)
				freeze_symptom.SetDuration(5);
		} 

		if ( roll2 < CHANCE_OF_SHAKE )
		{
			//Print("Shock");
			if ( player.GetHealth("GlobalHealth","Shock") <= SHOCK_LIMIT )
			{
				float currenthealth = player.GetHealth("GlobalHealth", "Health");
				player.AddHealth("GlobalHealth", "Health" , HEALTH_DECREMENT_PER_SEC * deltaT );
			}
			else
			{
				float currentshock =  player.GetHealth("GlobalHealth", "Shock");
				player.AddHealth("GlobalHealth", "Shock", SHOCK_DECREMENT_PER_SEC * deltaT);
			}
		}
		if ( roll3 < CHANCE_OF_VOMIT )
		{
			SymptomBase symptom_vomit = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
			if (symptom_vomit)
				symptom_vomit.SetDuration(4);
		}
	}
};