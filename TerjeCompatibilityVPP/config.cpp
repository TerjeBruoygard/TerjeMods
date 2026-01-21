class CfgPatches
{
	class TerjeCompatibilityVPP
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeCore",
			"DZM_VPPAdminTools"
		};
	};
};

class CfgMods
{
	class TerjeCompatibilityVPP
	{
		dir="TerjeCompatibilityVPP";
		hideName=1;
		hidePicture=1;
		version="1.0.0";
		extra=0;
		
		defines[]={"TERJE_COMPATIBILITY_VPP_MOD"};
		type="mod";
		dependencies[]={"World","Mission"};
		
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]={"TerjeCompatibilityVPP/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value="";
				files[]={"TerjeCompatibilityVPP/Scripts/5_Mission"};
			};
		};
	};
};
