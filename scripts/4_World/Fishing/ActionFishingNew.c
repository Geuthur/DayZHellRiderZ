modded class FishingActionData : ActionData
{
	//Einstellungen für Fischen
	const float FISHING_SUCCESS 		= 0.05; //0.2
	const float FISHING_BAIT_LOSS 		= 0.02;
	const float FISHING_HOOK_LOSS 		= 0.015;
	const float FISHING_DAMAGE 			= 5.0;
	const float FISHING_GARBAGE_CHANCE 	= 0.2; //0.2
}

modded class ActionFishingNewCB : ActionContinuousBaseCB
{
	const ref TStringArray JUNK = {
		"Special",
		"Wellies",		
		"Netting",
        "Pot"
		};
		
	const ref TStringArray  SPECIAL = {
		"Compass",
		"BurlapSack",
		"Netting",
	};	
	
	const ref TStringArray  WELLIES = {
		"Wellies_Black",
		"Wellies_Brown",
		"Wellies_Green",
		"Wellies_Grey"
	};	
		
	const ref TStringArray  PONDFISH = {
		"Carp"
		};

	const ref TStringArray  SEAFISH = {
		"Mackerel"
	};
		
	override void HandleFishingResultSuccess()
	{
		if (!GetGame().IsMultiplayer() || GetGame().IsServer())
		{
			ItemBase fish;
			
			if (!m_ActionDataFishing.m_Bait)
				m_ActionDataFishing.InitBait(ItemBase.Cast(m_ActionDataFishing.m_MainItem.FindAttachmentBySlotName("Hook")));
			
			if (!m_ActionDataFishing.IsBaitEmptyHook())
			{
				m_ActionDataFishing.m_Bait.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
				MiscGameplayFunctions.TurnItemIntoItem(m_ActionDataFishing.m_Bait,m_ActionDataFishing.m_Bait.ConfigGetString("hookType"),m_ActionDataFishing.m_Player);
			}
			else
			{
				m_ActionDataFishing.m_Bait.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
			}
			
			float rnd = Math.RandomFloatInclusive(0.0,1.0);
			if (rnd > m_ActionDataFishing.FISHING_GARBAGE_CHANCE)
			{
				if (m_ActionDataFishing.m_IsSurfaceSea)
					fish = ItemBase.Cast(GetGame().CreateObjectEx(SEAFISH.GetRandomElement(),m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
				else
					fish = ItemBase.Cast(GetGame().CreateObjectEx(PONDFISH.GetRandomElement(),m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
			}
			else
			{
				string junk_types = JUNK.GetRandomElement();
				if (junk_types == "Special")
					junk_types = SPECIAL.GetRandomElement();
				if (junk_types == "Wellies")
					junk_types = WELLIES.GetRandomElement();	
				fish = ItemBase.Cast(GetGame().CreateObjectEx(junk_types,m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
				fish.SetHealth("","Health",fish.GetMaxHealth("","Health") * 0.1);
			}
			
			if (fish)
			{
				fish.SetWet(0.3);
				if (fish.HasQuantity())
				{
					float coef = Math.RandomFloatInclusive(0.5, 1.0);
					float item_quantity = fish.GetQuantityMax() * coef;
					item_quantity = Math.Round(item_quantity);
					fish.SetQuantity( item_quantity );
				}				
			}
			
			m_ActionDataFishing.m_MainItem.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
		}
	}
};