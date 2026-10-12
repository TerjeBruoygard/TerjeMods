class Farming: SkillsBase
{
	id="farm";
	enabled=1;
	displayName="#STR_TERJESKILL_FARMING_NAME";
	description="#STR_TERJESKILL_FARMING_DESC";
	icon="set:TerjeSkills_icon image:ts_farming";
	
	class Modifiers
	{
		class HarvestYieldModifier
		{
			id="cropyieldmod";
			enabled=1;
			text="#STR_TERJESKILL_FARMING_MOD0";
			value=0.02;
		};
	};
	
	class Perks
	{
		class RichHarvest
		{
			id="richhrv";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_RICHHRV";
			description="#STR_TERJEPERK_FARM_RICHHRV_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_richhrv";
			enabledIcon="set:TerjePerk_icon image:tp_richhrv";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.1,0.2,0.3,0.4,0.5,0.7};
		};
		
		class FreshHarvest
		{
			id="freshhrv";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_FRESHHRV";
			description="#STR_TERJEPERK_FARM_FRESHHRV_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_freshhrv";
			enabledIcon="set:TerjePerk_icon image:tp_freshhrv";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.25,0.5,1.0,1.5,2.0,3.0};
		};
		
		class FastGrowth
		{
			id="fastgrow";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_FASTGROW";
			description="#STR_TERJEPERK_FARM_FASTGROW_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_fastgrow";
			enabledIcon="set:TerjePerk_icon image:tp_fastgrow";
			requiredSkillLevels[]={1,5,10,20,30,40};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={-0.1,-0.15,-0.25,-0.4,-0.55,-0.7};
		};
		
		class QuickDigger
		{
			id="quickdig";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_QUICKDIG";
			description="#STR_TERJEPERK_FARM_QUICKDIG_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_quickdig";
			enabledIcon="set:TerjePerk_icon image:tp_quickdig";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={-0.1,-0.2,-0.3,-0.5,-0.7,-0.85};
		};
		
		class ToughCrops
		{
			id="toughcrp";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_TOUGHCRP";
			description="#STR_TERJEPERK_FARM_TOUGHCRP_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_toughcrp";
			enabledIcon="set:TerjePerk_icon image:tp_toughcrp";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.2,0.4,0.6,0.9,1.2,1.5};
		};
		
		class WaterBalance
		{
			id="wtrbal";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_WATERBALANCE";
			description="#STR_TERJEPERK_FARM_WATERBALANCE_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_wtrbal";
			enabledIcon="set:TerjePerk_icon image:tp_wtrbal";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={-0.1,-0.2,-0.3,-0.4,-0.55,-0.7};
		};
		
		class Weatherproof
		{
			id="weathprf";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_WEATHPRF";
			description="#STR_TERJEPERK_FARM_WEATHPRF_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_weathprf";
			enabledIcon="set:TerjePerk_icon image:tp_weathprf";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.15,0.3,0.45,0.6,0.8,1.0};
		};
		
		class HothouseGrower
		{
			id="hothouse";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_HOTHOUSE";
			description="#STR_TERJEPERK_FARM_HOTHOUSE_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_hothouse";
			enabledIcon="set:TerjePerk_icon image:tp_hothouse";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.1,0.2,0.3,0.4,0.5,0.6};
		};
		
		class SeedGain
		{
			id="seedgain";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_SEEDGAIN";
			description="#STR_TERJEPERK_FARM_SEEDGAIN_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_seedgain";
			enabledIcon="set:TerjePerk_icon image:tp_seedgain";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.15,0.3,0.5,0.7,0.9,1.2};
		};
		
		class RichSoil
		{
			id="richsoil";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_RICHSOIL";
			description="#STR_TERJEPERK_FARM_RICHSOIL_DES";
			stagesCount=6;
			disabledIcon="set:TerjePerkBlack_icon image:tp_richsoil";
			enabledIcon="set:TerjePerk_icon image:tp_richsoil";
			requiredSkillLevels[]={1,5,10,15,20,25};
			requiredPerkPoints[]={1,1,1,1,1,2};
			values[]={0.15,0.25,0.45,0.65,0.85,1.0};
		};
		
		class RemoveRottenCrop
		{
			id="remrotv";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_REMROTV";
			description="#STR_TERJEPERK_FARM_REMROTV_DES";
			stagesCount=1;
			disabledIcon="set:TerjePerkBlack_icon image:tp_remrotv";
			enabledIcon="set:TerjePerk_icon image:tp_remrotv";
			requiredSkillLevels[]={5};
			requiredPerkPoints[]={1};
			values[]={0.0};
		};
		
		class ColdGround
		{
			id="coldgrnd";
			enabled=1;
			displayName="#STR_TERJEPERK_FARM_COLDGRND";
			description="#STR_TERJEPERK_FARM_COLDGRND_DES";
			stagesCount=1;
			disabledIcon="set:TerjePerkBlack_icon image:tp_coldgrnd";
			enabledIcon="set:TerjePerk_icon image:tp_coldgrnd";
			requiredSkillLevels[]={1};
			requiredPerkPoints[]={1};
			values[]={0.0};
		};
	};
};
