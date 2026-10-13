class CfgPatches
{
	class TerjeUnderground_Stash
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeMedicine",
			"DZ_Gear_Camping"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class UndergroundStash: Inventory_Base
	{
		scope = 2;
		model = "\TerjeSkills\UndergroundStash\terje_stash.p3d";
		hiddenSelections[] = {"zbytek"};
		simpleHiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"dz\gear\cultivation\data\soil_cultivated_co.paa"};
		hiddenSelectionsMaterials[] = {"dz\gear\cultivation\data\soil_cultivated.rvmat"};
	};
	class UndergroundStashSnow: UndergroundStash
	{
		model = "\TerjeSkills\UndergroundStash\terje_stash.p3d";
		hiddenSelections[] = {"zbytek"};
		simpleHiddenSelections[] = {"zbytek"};
		hiddenSelectionsTextures[] = {"dz\gear\camping\data\underground_stash_snow_ca.paa"};
		hiddenSelectionsMaterials[] = {"dz\gear\camping\data\underground_stash_snow.rvmat"};
	};
};
