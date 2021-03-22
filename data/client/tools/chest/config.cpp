class CfgPatches
{
	class DZ_Gear_Camping
	{
		units[]=
		{
			"SeaChest",
			"WoodenCrate"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class Container_Base;
	class WorldContainer_Base;
	class HouseNoDestruct;
	class Static;
	class BaseBuildingBase: Inventory_Base
	{
	};
		class SeaChest: Container_Base
	{
		scope=2;
		displayName="$STR_CfgVehicles_SeaChest0";
		descriptionShort="$STR_CfgVehicles_SeaChest1";
		model="\DZ\gear\camping\sea_chest.p3d";
		hologramMaterial="sea_chest";
		hologramMaterialPath="dz\gear\camping\data";
		slopeTolerance=0.40000001;
		yawPitchRollLimit[]={45,45,45};
		weight=10000;
		itemBehaviour=0;
		itemSize[]={10,10};
		carveNavmesh=1;
		canBeDigged=0;
		rotationFlags=2;
		hiddenSelections[]=
		{
			"camoGround"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\gear\camping\data\sea_chest_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=600;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\camping\data\sea_chest.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\camping\data\sea_chest.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\camping\data\sea_chest_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\camping\data\sea_chest_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\camping\data\sea_chest_destruct.rvmat"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=8;
					};
					class Blood
					{
						damage=8;
					};
					class Shock
					{
						damage=8;
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,10};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="seachest_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="seachest_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class WoodenCrate: Container_Base
	{
		scope=2;
		displayName="$STR_CfgVehicles_Wooden_Case0";
		descriptionShort="$STR_CfgVehicles_Wooden_Case1";
		model="\DZ\gear\camping\wooden_case.p3d";
		hologramMaterial="wooden_case";
		hologramMaterialPath="dz\gear\camping\data";
		slopeTolerance=0.40000001;
		yawPitchRollLimit[]={45,45,45};
		inventorySlot[]=
		{
			"Truck_01_WoodenCrate1",
			"Truck_01_WoodenCrate2",
			"Truck_01_WoodenCrate3",
			"Truck_01_WoodenCrate4"
		};
		weight=10000;
		itemSize[]={10,5};
		itemBehaviour=0;
		carveNavmesh=1;
		canBeDigged=0;
		rotationFlags=2;
		hiddenSelections[]=
		{
			"camoGround"
		};
		hiddenSelectionsTextures[]=
		{
			"\dz\gear\camping\data\wooden_case_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\camping\data\wooden_case.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\camping\data\wooden_case.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\camping\data\wooden_case_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\camping\data\wooden_case_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\camping\data\wooden_case_destruct.rvmat"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=8;
					};
					class Blood
					{
						damage=8;
					};
					class Shock
					{
						damage=8;
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,5};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="seachest_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="seachest_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};
