modded class GameConstants
{
	/**
	 * \defgroup Food decay constants
	 * \desc Constants for decay of various types of food.
	 * \ Boiled = Gekocht Baked = Gebacken Dried = Getrocknet
	 * \ Zeitrechnung: DECAY_FOOD_RAW_MEAT / DECAY_RATE_ON_PLAYER / 60 = Ungefähre Zeit der Rottung
	 */
	const float DECAY_FOOD_RAW_MEAT = 10800; //1 Stunde 21600
	const float DECAY_FOOD_RAW_FRVG = 21600; //2,5 Stunde 43200
	const float DECAY_FOOD_BOILED_MEAT = 21600; //2,5 Stunden 259200
	const float DECAY_FOOD_BOILED_FRVG = 17280; //2 Stunden 172800
	const float DECAY_FOOD_BAKED_MEAT = 21600; //2,5 Stunden 345600
	const float DECAY_FOOD_BAKED_FRVG = 21600; //2,5 Stunden 259200
	const float DECAY_FOOD_DRIED_MEAT = 54000; //6 Stunden 691200
	const float DECAY_FOOD_CAN_OPEN = 81000; //9 Stunden 172800
	const int DECAY_FOOD_FRVG_DRIED_CHANCE = 43;
	const int DECAY_TIMER_RANDOM_PERCENTAGE = 25;
	const float DECAY_RATE_ON_PLAYER = 2.5;
	}