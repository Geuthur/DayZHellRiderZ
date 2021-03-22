modded class VomitStuffedMdfr: ModifierBase
{
	
	override bool ActivateCondition(PlayerBase player)
	{
		float stomach = m_Player.m_PlayerStomach.GetStomachVolume();
		if ( stomach >= PlayerConstants.VOMIT_THRESHOLD )
		{
		static const int wasser_verlust = 350;
		m_Player.GetStatWater().Add( -1 * wasser_verlust );
		//m_Player.GetStatWater().Add(-wasser_verlust);
		static const int essen_verlust = 310;
		m_Player.GetStatEnergy().Add( -1 * essen_verlust );
		//m_Player.GetStatEnergy().Add(-essen_verlust);
			return true;
		}
		else
		{
			return false;
		}
	}

	override void OnActivate(PlayerBase player)
	{
		player.GetSymptomManager().QueueUpPrimarySymptom( SymptomIDs.SYMPTOM_VOMIT );
	}


	override bool DeactivateCondition(PlayerBase player)
	{
		return !ActivateCondition(player);
	}
};