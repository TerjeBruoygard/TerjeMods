class CfgPatches
{
	class TerjeCompatibilityCOT
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore",
			"JM_COT_Scripts"
		};
	};
};

class CfgMods
{
	class TerjeCompatibilityCOT
	{
		dir="TerjeCompatibilityCOT";
		hideName=1;
		hidePicture=1;
		version="1.0.0";
		extra=0;
		
		defines[]={"TERJE_COMPATIBILITY_COT_MOD"};
		type="mod";
		dependencies[]={"World","Mission"};
		
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]={"TerjeCompatibilityCOT/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"TerjeCompatibilityCOT/Scripts/5_Mission"};
			};
		};
	};
};
