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
	class CarpFilletMeat: Edible_Base
	{
		scope=2;
		displayName="$STR_CarpFilletMeat0";
		descriptionShort="$STR_CarpFilletMeat1";
		model="\dz\gear\food\carp_fillet.p3d";
		rotationFlags=34;
		weight=0;
		interactionWeight=1;
		quantityBar=1;
		varQuantityInit=300;
		varQuantityMin=0;
		varQuantityMax=300;
		itemSize[]={2,3};
		absorbency=0.30000001;
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
		class MeleeModes
		{
			class Default
			{
				ammo="MeleeFist";
				range=1;
			};
			class Heavy
			{
				ammo="MeleeFist_Heavy";
				range=1;
			};
			class Sprint
			{
				ammo="MeleeFist_Heavy";
				range=2.8;
			};
		};
		hiddenSelections[]=
		{
			"cs_raw"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\gear\food\data\carp_fillet_raw_CO.paa",
			"dz\gear\food\data\carp_fillet_baked_CO.paa",
			"dz\gear\food\data\carp_fillet_boiled_CO.paa",
			"dz\gear\food\data\carp_fillet_dried_CO.paa",
			"dz\gear\food\data\carp_fillet_burnt_CO.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\gear\food\data\carp_fillet_raw.rvmat",
			"dz\gear\food\data\carp_fillet_baked.rvmat",
			"dz\gear\food\data\carp_fillet_boiled.rvmat",
			"dz\gear\food\data\carp_fillet_dried.rvmat",
			"dz\gear\food\data\carp_fillet_burnt.rvmat",
			"dz\gear\food\data\carp_fillet_rotten.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=50;
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
					nutrition_properties[]={4.5,266,120,184,1,4};
					cooking_properties[]={0,0};
				};
				class Rotten
				{
					visual_properties[]={-1,-1,5};
					nutrition_properties[]=
					{
						4,
						67,
						120,
						30,
						1,
						"4 + 		  16"
					};
					cooking_properties[]={0,0};
				};
				class Baked
				{
					visual_properties[]={0,1,1};
					nutrition_properties[]={3.5,200,74,129,1};
					cooking_properties[]={70,45};
				};
				class Boiled
				{
					visual_properties[]={0,2,2};
					nutrition_properties[]={3,187,53,150,1};
					cooking_properties[]={70,55};
				};
				class Dried
				{
					visual_properties[]={0,3,3};
					nutrition_properties[]={1.5,130,43,180,1};
					cooking_properties[]={70,120,80};
				};
				class Burned
				{
					visual_properties[]={0,4,4};
					nutrition_properties[]={4,60,13,50,1,16};
					cooking_properties[]={100,30};
				};
			};
			class FoodStageTransitions: MeatStageTransitions
			{
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
	class MackerelFilletMeat: Edible_Base
	{
		scope=2;
		displayName="$STR_MackerelFilletMeat0";
		descriptionShort="$STR_MackerelFilletMeat1";
		model="\dz\gear\food\mackerel_fillet.p3d";
		rotationFlags=34;
		weight=0;
		interactionWeight=1;
		quantityBar=1;
		itemSize[]={3,1};
		absorbency=0.30000001;
		varQuantityInit=200;
		varQuantityMin=0;
		varQuantityMax=200;
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
		class MeleeModes
		{
			class Default
			{
				ammo="MeleeFist";
				range=1;
			};
			class Heavy
			{
				ammo="MeleeFist_Heavy";
				range=1;
			};
			class Sprint
			{
				ammo="MeleeFist_Heavy";
				range=2.8;
			};
		};
		hiddenSelections[]=
		{
			"cs_raw"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\gear\food\data\mackerel_fillet_raw_CO.paa",
			"dz\gear\food\data\mackerel_fillet_baked_CO.paa",
			"dz\gear\food\data\mackerel_fillet_boiled_CO.paa",
			"dz\gear\food\data\mackerel_fillet_dried_CO.paa",
			"dz\gear\food\data\mackerel_fillet_burnt_CO.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\gear\food\data\mackerel_fillet_raw.rvmat",
			"dz\gear\food\data\mackerel_fillet_baked.rvmat",
			"dz\gear\food\data\mackerel_fillet_boiled.rvmat",
			"dz\gear\food\data\mackerel_fillet_dried.rvmat",
			"dz\gear\food\data\mackerel_fillet_burnt.rvmat",
			"dz\gear\food\data\mackerel_fillet_rotten.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=50;
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
					nutrition_properties[]={4.5,200,100,184,1,4}; // 4.5,800,360,184,1,4
					cooking_properties[]={0,0};
				};
				class Rotten
				{
					visual_properties[]={-1,-1,5};
					nutrition_properties[]={4,100,100,30,1,"4 + 16"}; // nutrition_properties[]={4,200,360,30,1,"4 + 16"};
					cooking_properties[]={0,0};
				};
				class Baked
				{
					visual_properties[]={0,1,1};
					nutrition_properties[]={3.5,200,100,129,1}; // nutrition_properties[]={3.5,600,222,129,1};
					cooking_properties[]={70,45};
				};
				class Boiled
				{
					visual_properties[]={0,2,2};
					nutrition_properties[]={3,180,80,150,1}; // nutrition_properties[]={3,560,160,150,1};
					cooking_properties[]={70,55};
				};
				class Dried
				{
					visual_properties[]={0,3,3};
					nutrition_properties[]={1.5,120,40,180,1}; // nutrition_properties[]={1.5,390,130,180,1};
					cooking_properties[]={70,120,80};
				};
				class Burned
				{
					visual_properties[]={0,4,4};
					nutrition_properties[]={4,80,20,50,1,16}; // nutrition_properties[]={4,180,40,50,1,16};
					cooking_properties[]={100,30};
				};
			};
			class FoodStageTransitions: MeatStageTransitions
			{
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
