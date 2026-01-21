class CfgPatches
{
	class TerjeMedicine
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore",
			"DZ_Gear_Medical"
		};
	};
};

class CfgMods
{
	class TerjeMedicine
	{
		dir="TerjeMedicine";
		hideName=0;
		hidePicture=0;
		version="1.0.0";
		extra=0;
		
		defines[]={"TERJE_MEDICINE_MOD"};
		type="mod";
		dependencies[]={"gui","Game","World","Mission"};
		
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"TerjeMedicine/Textures/icon_medicine.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]={"TerjeMedicine/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value="";
				files[]={"TerjeMedicine/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"TerjeMedicine/Scripts/5_Mission"};
			};
		};
	};
};

class CfgTerjeSkills
{
	#include "immunity.hpp"
	#include "medicine.hpp"
};
