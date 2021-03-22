class CfgPatches
{
	class DayZHellRiderZ
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"JM_CF_Scripts",
			"JM_COT_GUI",
			"DZ_Gear_Consumables",
			"DZ_Vehicles_Wheeled",
			"DZ_Structures_Residential",
			"DZ_Sounds_Effects",
			"DZ_Sounds_Weapons"
		};
	};
};
class CfgMods
{
	class DayZHellRiderZ
	{
	    name = "DayZ Hell-RiderZ";
	    author = "Geuthur";
	    inputs = "DayZHellRiderZ\data\inputs.xml";
	    type = "mod";
	    dependencies[] = {"Game", "World", "Mission"};
	    class defs
	    {
			class imageSets
			{
				files[] = {"DayZHellRiderZ/scripts/layouts/hrz_icons.imageset"};
			};
			class gameScriptModule
			{
				value = "";
				files[] = {"DayZHellRiderZ/scripts/3_Game"};
			};
			
			class worldScriptModule
			{
				value="";
				files[] = {"DayZHellRiderZ/scripts/4_World"};
			};
			
			class missionScriptModule
			{
				value="";
				files[] = {"DayZHellRiderZ/scripts/5_Mission"};
			};
		};
    };
};
