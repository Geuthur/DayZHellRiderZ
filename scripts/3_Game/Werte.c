modded class PlayerConstants 
{	
	//--------------------------------------------------------
	static const int BLOOD_THRESHOLD_FATAL 					= 2500;	//fatal blood level
	
	static const float BLOOD_REGEN_RATE_PER_SEC				= 0.2; 	//base amount of blood regenerated per second
	static const float DAMAGE_ZONE_BLOOD_REGEN_MODIFIER 	= 0.6;
	
	static const float BLOOD_REGEN_MODIFIER_ENERGY_LOW		= 0; 	//multiplier for blood regen rate 
	static const float BLOOD_REGEN_MODIFIER_ENERGY_MID		= 0.4;
	static const float BLOOD_REGEN_MODIFIER_ENERGY_HIGH		= 0.8;
	
	static const float BLOOD_REGEN_MODIFIER_WATER_LOW		= 0; 	//multiplier for blood regen rate (BLOOD_REGEN_MULTIPLIER_WATER_LOW ?)
	static const float BLOOD_REGEN_MODIFIER_WATER_MID		= 0.4;
	static const float BLOOD_REGEN_MODIFIER_WATER_HIGH		= 0.8;
	
	static const float SALINE_BLOOD_REGEN_PER_SEC			= 2.5;	//boost for blood regen per second, independent on BLOOD_REGEN_SPEED
	static const float SALINE_LIQUID_AMOUNT					= 500;
	static const float SALINE_WATER_REGEN_PER_SEC 			= 1.6;

	// Immunsystem Einstellungen
	static const float IMMUNITY_THRESHOLD_LEVEL_HIGH = 0.95; // 0.95
	static const float IMMUNITY_THRESHOLD_LEVEL_NORMAL = 0.65; // 0.65
	static const float IMMUNITY_THRESHOLD_LEVEL_LOW = 0.35; // 0.35
	static const float IMMUNITY_THRESHOLD_LEVEL_CRITICAL = 0.15; //
	
	// Magen Erweiterungs Einstellungen
	static const int BT_STOMACH_VOLUME_LVL3 = 1500;
	static const int BT_STOMACH_VOLUME_LVL2 = 750;
	static const int BT_STOMACH_VOLUME_LVL1 = 1;
	// Maximal Essen Einstellungen
	const int VOMIT_THRESHOLD = 200; // 2000
	
	//Spielerwerte
	static const float SHOES_MOVEMENT_DAMAGE_PER_STEP = 0.005; // 0.035
}