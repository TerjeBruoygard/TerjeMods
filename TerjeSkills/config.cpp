class CfgPatches
{
	class TerjeSkills
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore"
		};
	};
};

class CfgMods
{
	class TerjeSkills
	{
		dir="TerjeSkills";
		hideName=0;
		hidePicture=0;
		version="1.0.0";
		extra=0;
		
		defines[]={"TERJE_SKILLS_MOD"};
		type="mod";
		dependencies[]={"gui","Game","World","Mission"};
		
		class defs
		{
			class imageSets
			{
				files[] =
				{
					"TerjeSkills/Textures/Icons/TerjeSkills.imageset", 
					"TerjeSkills/Textures/Icons/PerkBorders.imageset", 
					"TerjeSkills/Textures/Icons/PerkLevels.imageset", 
					"TerjeSkills/Textures/Icons/TerjePerk.imageset",
					"TerjeSkills/Textures/Icons/TerjePerkBlack.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]={"TerjeSkills/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value="";
				files[]={"TerjeSkills/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"TerjeSkills/Scripts/5_Mission"};
			};
		};
	};
};

class CfgTerjeSkills
{
	class SkillsBase
	{
		enabled=0; //do not change this, its a base class
		perkPointsPerLevel=1;
		expLoseOnDeath=-100;
		levels[]=
		{
			  100,   200,   300,   400,   500,   700,   900,  1100,  1300,  1500, //  1-10
			 1750,  2000,  2250,  2500,  2750,  3250,  3750,  4250,  4750,  5250, // 11-20
			 6000,  6750,  7500,  8250,  9000, 10000, 11000, 12000, 13000, 14000, // 20-30
			16000, 18000, 20000, 22000, 24000, 26000, 28000, 30000, 32000, 34000, // 31-40
			37000, 40000, 43000, 46000, 50000, 55000, 60000, 70000, 80000, 100000 // 41-50
		};
	};
	#include "athletic.hpp"
	#include "strength.hpp"
	#include "metabolism.hpp"
	#include "stealth.hpp"
	#include "survival.hpp"
	#include "hunting.hpp"
	#include "fishing.hpp"
	#include "farming.hpp"
};
