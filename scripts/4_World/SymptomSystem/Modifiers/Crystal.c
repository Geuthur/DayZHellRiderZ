class HRZ_ShakeMdfr: ModifierBase
{
	int LIFETIME = 180;  //currently the same as the config
	
	static const int CHANCE_OF_SHAKE = 15;
	static const int CHANCE_OF_LAUGHTER = 30;
	static const int CHANCE_OF_SHOCK = 1;

	ref HumanMovementState		m_MovementState	= new HumanMovementState();

	override void Init()
	{
		m_TrackActivatedTime	= true;
		m_IsPersistent 		= false;
		m_ID 				= HRZ_eModifiers.MDF_Crystal;
		m_TickIntervalInactive 	= DEFAULT_TICK_TIME_INACTIVE;
		m_TickIntervalActive 	= 10;
	}
	
	override string GetDebugText()
	{
		return (LIFETIME - GetAttachedTime()).ToString();
	}

	override protected void OnActivate(PlayerBase player)
	{
	if( player.GetNotifiersManager() ) 
	player.GetNotifiersManager().ActivateByType(eNotifiers.NTF_PILLS);
	}
	
	override protected void OnDeactivate(PlayerBase player)
	{
	if( player.GetNotifiersManager() ) 
	player.GetNotifiersManager().DeactivateByType(eNotifiers.NTF_PILLS);
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
		if ( roll < CHANCE_OF_SHAKE )
		{
			SymptomBase shake_symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_FREEZE);
			if (shake_symptom)
				shake_symptom.SetDuration(5);
			
		} 
		if ( roll2 < CHANCE_OF_LAUGHTER )
		{
			SymptomBase laugh_symptom = player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_LAUGHTER);
			if (laugh_symptom)
				laugh_symptom.SetDuration(5);
		}
		if ( roll3 < CHANCE_OF_SHOCK )
		{
			player.AddHealth("", "Shock", -1);
		} 
	}
};