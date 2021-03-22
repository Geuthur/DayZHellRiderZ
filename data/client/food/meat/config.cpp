

class CfgPatches
{
	class DZ_Gear_Food
	{
		units[]=
		{
			"Food_CanBakedBeans",
			"Food_CanFrankBeans",
			"Food_CanPasta",
			"Food_CanSardines",
			"Food_BoxCerealCrunchin"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class BaseFoodStageTransitions
{
	class Raw
	{
		class ToBaked
		{
			transition_to=2;
			cooking_method=1;
		};
		class ToBoiled
		{
			transition_to=3;
			cooking_method=2;
		};
		class ToBurned
		{
			transition_to=5;
			cooking_method=3;
		};
	};
	class Rotten
	{
		class ToBurned
		{
			transition_to=5;
			cooking_method=1;
		};
	};
	class Baked
	{
		class ToBurned
		{
			transition_to=5;
			cooking_method=1;
		};
	};
	class Boiled
	{
		class ToBaked
		{
			transition_to=2;
			cooking_method=1;
		};
	};
	class Dried
	{
		class ToBaked
		{
			transition_to=5;
			cooking_method=1;
		};
		class ToBoiled
		{
			transition_to=5;
			cooking_method=2;
		};
	};
	class Burned
	{
	};
};
class NotCookable
{
	class Raw
	{
		class ToRotten
		{
			transition_to=6;
			cooking_method=4;
		};
	};
};
class MeatStageTransitions: BaseFoodStageTransitions
{
};
class FruitStageTransitions: BaseFoodStageTransitions
{
};
class AnimalCorpsesStageTransitions: BaseFoodStageTransitions
{
};
class MushroomsStageTransitions: BaseFoodStageTransitions
{
};
class FoodAnimationSources
{
	class CS_Raw
	{
		source="user";
		animPeriod=0.0099999998;
		initPhase=1;
	};
	class CS_Rotten
	{
		source="user";
		animPeriod=0.0099999998;
		initPhase=1;
	};
	class CS_Baked
	{
		source="user";
		animPeriod=0.0099999998;
		initPhase=1;
	};
	class CS_Boiled
	{
		source="user";
		animPeriod=0.0099999998;
		initPhase=1;
	};
	class CS_Dried
	{
		source="user";
		animPeriod=0.0099999998;
		initPhase=1;
	};
	class CS_Burned
	{
		source="user";
		animPeriod=0.0099999998;
		initPhase=1;
	};
};
class NutritionModifiers
{
	class General
	{
		base_stage="Raw";
		class Raw
		{
			nutrition_properties[]={1,1,1,1,1};
		};
		class Rotten
		{
			nutrition_properties[]={0.5,0.75,1,0.25,1};
		};
		class Baked
		{
			nutrition_properties[]={2,0.5,0.75,0.75,1};
		};
		class Boiled
		{
			nutrition_properties[]={1,1,0.80000001,0.80000001,1};
		};
		class Dried
		{
			nutrition_properties[]={4,0.1,0.5,0.80000001,1};
		};
		class Burned
		{
			nutrition_properties[]={1,0.25,0.75,0.1,1};
		};
	};
};
class CfgVehicles
{	
	class Inventory_Base;
	class Edible_Base: Inventory_Base
	{
		varTemperatureMax=100;
	};
	class Lard: Edible_Base
	{
		scope=2;
		displayName="$STR_Lard0";
		descriptionShort="$STR_Lard1";
		model="\dz\gear\food\lard.p3d";
		rotationFlags=34;
		weight=0;
		interactionWeight=1;
		itemSize[]={2,2};
		absorbency=0.30000001;
		varQuantityInit=200;
		varQuantityMin=0;
		varQuantityMax=200;
		quantityBar=1;
		inventorySlot[]=
		{
			"Ingredient",
			"DirectCookingA",
			"DirectCookingB",
			"DirectCookingC",
			"SmokingA",
			"SmokingB",
			"SmokingC",
			"SmokingD"
		};
		isMeleeWeapon=1;
		hiddenSelections[]=
		{
			"cs_raw",
			"cs_dried"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\gear\food\data\lard_raw_CO.paa",
			"dz\gear\food\data\lard_baked_CO.paa",
			"dz\gear\food\data\lard_boiled_CO.paa",
			"dz\gear\food\data\lard_dried_CO.paa",
			"dz\gear\food\data\lard_burnt_CO.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\gear\food\data\lard_raw.rvmat",
			"dz\gear\food\data\lard_baked.rvmat",
			"dz\gear\food\data\lard_boiled.rvmat",
			"dz\gear\food\data\lard_dried.rvmat",
			"dz\gear\food\data\lard_burnt.rvmat",
			"dz\gear\food\data\meat_steak_rotten.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
		};
		class AnimationSources: FoodAnimationSources
		{
		};
		class Food
		{
			class FoodStages
			{
				class Raw
				{
					visual_properties[]={0,0,0};
					nutrition_properties[]={20,200,0,1,0,4};
					cooking_properties[]={0,0};
				};
				class Rotten
				{
					visual_properties[]={-1,-1,5};
					nutrition_properties[]={30,150,0,1,0,"4 + 16"};
					cooking_properties[]={0,0};
				};
				class Baked
				{
					visual_properties[]={0,1,1};
					nutrition_properties[]={15,300,0,1,0};
					cooking_properties[]={70,45};
				};
				class Boiled
				{
					visual_properties[]={0,2,2};
					nutrition_properties[]={20,300,0,1,0};
					cooking_properties[]={70,55};
				};
				class Dried
				{
					visual_properties[]={0,3,3};
					nutrition_properties[]={15,150,0,1,0};
					cooking_properties[]={70,120,80};
				};
				class Burned
				{
					visual_properties[]={0,4,4};
					nutrition_properties[]={20,100,0,1,0,16};
					cooking_properties[]={100,30};
				};
			};
			class FoodStageTransitions: MeatStageTransitions
			{
				class Baked
				{
					class ToRotten
					{
						transition_to=6;
						cooking_method=4;
					};
				};
				class Dried
				{
					class ToBaked
					{
						transition_to=2;
						cooking_method=1;
					};
					class ToBoiled
					{
						transition_to=3;
						cooking_method=2;
					};
				};
			};
		};
		class NoiseImpact
		{
			strength=600;
			type="sound";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class openTunaCan
				{
					soundSet="openTunaCan_SoundSet";
					id=204;
				};
				class Eating_TakeFood
				{
					soundSet="Eating_TakeFood_Soundset";
					id=889;
				};
				class Eating_BoxOpen
				{
					soundSet="Eating_BoxOpen_Soundset";
					id=893;
				};
				class Eating_BoxShake
				{
					soundSet="Eating_BoxShake_Soundset";
					id=894;
				};
				class Eating_BoxEnd
				{
					soundSet="Eating_BoxEnd_Soundset";
					id=895;
				};
			};
		};
	};
};
