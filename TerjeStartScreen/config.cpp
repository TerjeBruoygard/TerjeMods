class CfgPatches
{
	class TerjeStartScreen
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
	class TerjeStartScreen
	{
		dir="TerjeStartScreen";
		hideName=0;
		hidePicture=0;
		version="1.0.0";
		extra=0;
		
		defines[]={"TERJE_START_SCREEN_MOD"};
		type="mod";
		dependencies[]={"gui","Game","World","Mission"};
		
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"TerjeStartScreen/Textures/startscreen_icons.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]={"TerjeStartScreen/Scripts/3_Game"};
			};
			class worldScriptModule
			{
				value="";
				files[]={"TerjeStartScreen/Scripts/4_World", "TerjeStartScreen/Scripts/4_Compatibility"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"TerjeStartScreen/Scripts/5_Mission", "TerjeStartScreen/Scripts/5_Compatibility"};
			};
		};
	};
};
