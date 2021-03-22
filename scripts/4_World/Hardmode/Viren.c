	//float	m_Type = 0;
	//float	m_Invasibility;					//how fast the agent grows when potent enough to grow
	//float 	m_TransferabilityIn;			//to the player
	//float	m_TransferabilityOut;			//from the player
	//float	m_Digestibility = 0.1;			//multiplier for agents digested in the player stomach from an infected item(agents_transfered = digested_amount(in grams or mls) * m_Digestibility)
	//int		m_MaxCount = 1;
	//float 	m_AutoinfectProbability = CalculateAutoinfectProbability(0);	// [0..1], 0 = zero chance, 1 = 100% chance of getting this agent once per hour
	//float 	m_TransferabilityAirOut; 		// transferibility airborne out
	//float 	m_AntibioticsResistance = 1;	//[0..1], 0 means antibiotics have full effect, 1 means no effect
modded class BrainAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= eAgents.BRAIN;
		m_Invasibility 			= 1;
		m_TransferabilityIn		= 1;
		m_TransferabilityOut	= 0;
		m_AntibioticsResistance = 1;
		m_MaxCount 				= 5000;
		m_Potency 				= EStatLevels.GREAT;
		m_DieOffSpeed 			= 1;
	}
}

// Infektion Chance Einstellungen

modded class CommonColdMdfr
{
	const int AGENT_THRESHOLD_ACTIVATE = 50; // 200
	const int AGENT_THRESHOLD_DEACTIVATE = 21; //100
}

modded class InfluenzaMdfr
{
	const int AGENT_THRESHOLD_ACTIVATE = 600; //300
	const int AGENT_THRESHOLD_DEACTIVATE = 100; //200
}

modded class WoundInfectionMdfr
{
	static const int AGENT_THRESHOLD_ACTIVATE = 900; // 100
	static const int AGENT_THRESHOLD_DEACTIVATE = 20; // 20
}

modded class SalmonellaMdfr: ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE = 60; //60
	static const int AGENT_THRESHOLD_DEACTIVATE = 20; //20
}
modded class CholeraMdfr: ModifierBase
{
	static const int AGENT_THRESHOLD_ACTIVATE = 250;
	static const int AGENT_THRESHOLD_DEACTIVATE = 50;
}

// Spezifische Einstellungen der Krankheiten

modded class InfluenzaAgent extends AgentBase
{
	const float INFLUENZA_AGENT_AUTOINFECT_THRESHOLD_HC = PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING;

	override void Init()
	{
		m_Type 					= eAgents.INFLUENZA;
		m_Invasibility 			= 0.33; //0.33 | how fast the agent grows when potent enough to grow
		m_TransferabilityIn		= 1; //1 
		m_TransferabilityOut	= 1; //1
		m_MaxCount 				= 1000; //1000
		m_Digestibility			= 0.1; //0.1
		m_AntibioticsResistance = 0.35; //0.25
		m_AutoinfectProbability = CalculateAutoinfectProbability( 0.75 ); // 0.65 
		m_TransferabilityAirOut = 1; // transferibility airborne out
		m_Potency 				= EStatLevels.HIGH; // MEDIUM - grow when player's immune system is at this level or lower
		m_DieOffSpeed 			= 0.66; //how fast the agent dies off when not potent enough to grow(per sec)
	}
}

modded class SalmonellaAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= eAgents.SALMONELLA;
		m_Invasibility 			= 0.75;
		m_TransferabilityIn		= 0.1;
		m_TransferabilityOut	= 0.1;
		m_AntibioticsResistance = 1;
		m_MaxCount 				= 300;
		m_Potency 				= EStatLevels.HIGH;
		m_DieOffSpeed 			= 1;
	}
}

modded class FoodPoisonAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= eAgents.FOOD_POISON;
		m_Invasibility 			= 1;
		m_TransferabilityIn		= 1;
		m_TransferabilityOut	= 0;
		m_AntibioticsResistance = 0.5;
		m_MaxCount 				= 400;
		m_Potency 				= EStatLevels.CRITICAL;
		m_DieOffSpeed 			= 1;
		m_Digestibility 		= 1;
	}
}

modded class ChemicalAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= eAgents.CHEMICAL_POISON;
		m_Invasibility 			= 1;
		m_TransferabilityIn		= 1;
		m_TransferabilityOut	= 0;
		m_AntibioticsResistance = 1;
		m_MaxCount 				= 1000;
		m_Potency 				= EStatLevels.HIGH;
		m_DieOffSpeed 			= 1;
	}
}

modded class WoundAgent extends AgentBase
{
	override void Init()
	{
		m_Type 					= eAgents.WOUND_AGENT;
		m_Invasibility 			= 0.5;
		m_TransferabilityIn		= 1;
		m_TransferabilityOut	= 0.1;
		m_AntibioticsResistance = 0.5;
		m_MaxCount 				= 1000;
		m_Potency 				= EStatLevels.HIGH;
		m_DieOffSpeed 			= 1;
	}
}