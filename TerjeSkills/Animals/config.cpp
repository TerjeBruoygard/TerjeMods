class CfgPatches
{
	class TerjeSkills_Animals
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeSkills",
			"DZ_Animals_ursus_arctos",
			"DZ_Animals_vulpes_vulpes",
			"DZ_Animals_varanus_griseus",
			"DZ_Animals_sus_scrofa",
			"DZ_Animals_sus_domesticus",
			"DZ_Animals_rangifer_tarandus_feminam",
			"DZ_Animals_rangifer_tarandus",
			"DZ_Animals_ovis_aries_fem",
			"DZ_Animals_ovis_aries",
            "DZ_Animals_ovis_gmelini",
			"DZ_Animals_lepus_europaeus",
			"DZ_Animals_gallus_gallus_domesticus_feminam",
			"DZ_Animals_gallus_gallus_domesticus",
			"DZ_Animals_cervus_elaphus_feminam",
			"DZ_Animals_cervus_elaphus",
			"DZ_Animals_capreolus_capreolus_fem",
			"DZ_Animals_capreolus_capreolus",
			"DZ_Animals_capra_hircus_fem",
			"DZ_Animals_capra_hircus",
			"DZ_Animals_canis_lupus",
			"Animal_Canis_Familiaris_Dobermann_ColorBase",
			"Animal_Canis_Familiaris_German_Shepherd_ColorBase",
			"DZ_Animals_bos_taurus_fem",
			"DZ_Animals_bos_taurus",
			"DZ_Gear_Food",
			"DZ_Gear_Nasdara_Food"
		};
	};
};

class CfgVehicles
{
	class AnimalBase;
	
	class Animal_UrsusArctos: AnimalBase
	{
		terjeOnKillHuntingExp=500;
		terjeOnHeadshotHuntingExp=250;
		terjeOnButchHuntingExp=250;
		terjeHighlightWithPathfinder=0;
		terjeSkinningTimeModifier=2.0;
		terjeSkinningKnifeDamageModifier=2.0;
	};

	class Animal_VulpesVulpes: AnimalBase
	{
		terjeOnKillHuntingExp=50;
		terjeOnHeadshotHuntingExp=50;
		terjeOnButchHuntingExp=50;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=0.5;
		terjeSkinningKnifeDamageModifier=0.75;
	};
	
	class Animal_SusScrofa: AnimalBase
	{
		terjeOnKillHuntingExp=200;
		terjeOnHeadshotHuntingExp=100;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_SusDomesticus: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=10;
		terjeOnButchHuntingExp=100;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_RangiferTarandusF: AnimalBase
	{
		terjeOnKillHuntingExp=150;
		terjeOnHeadshotHuntingExp=150;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.5;
		terjeSkinningKnifeDamageModifier=1.5;
	};
	
	class Animal_RangiferTarandus: AnimalBase
	{
		terjeOnKillHuntingExp=200;
		terjeOnHeadshotHuntingExp=200;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.5;
		terjeSkinningKnifeDamageModifier=1.5;
	};
	
	class Animal_OvisAriesF: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=25;
		terjeOnButchHuntingExp=100;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_OvisAries: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=25;
		terjeOnButchHuntingExp=100;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_OvisGmelini: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=25;
		terjeOnButchHuntingExp=100;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_LepusEuropaeus: AnimalBase
	{
		terjeOnKillHuntingExp=50;
		terjeOnHeadshotHuntingExp=150;
		terjeOnButchHuntingExp=50;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=0.25;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	
	class Animal_GallusGallusDomesticusF: AnimalBase
	{
		terjeOnKillHuntingExp=10;
		terjeOnHeadshotHuntingExp=10;
		terjeOnButchHuntingExp=10;
		terjeSkinningTimeModifier=0.25;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	
	class Animal_GallusGallusDomesticus: AnimalBase
	{
		terjeOnKillHuntingExp=10;
		terjeOnHeadshotHuntingExp=10;
		terjeOnButchHuntingExp=10;
		terjeSkinningTimeModifier=0.25;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	
	class Animal_VaranusGriseus: AnimalBase
	{
		terjeOnKillHuntingExp=10;
		terjeOnHeadshotHuntingExp=10;
		terjeOnButchHuntingExp=10;
		terjeSkinningTimeModifier=0.25;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	
	class Animal_CervusElaphusF: AnimalBase
	{
		terjeOnKillHuntingExp=150;
		terjeOnHeadshotHuntingExp=150;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.25;
		terjeSkinningKnifeDamageModifier=1.25;
	};
	
	class Animal_CervusElaphus: AnimalBase
	{
		terjeOnKillHuntingExp=200;
		terjeOnHeadshotHuntingExp=200;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.25;
		terjeSkinningKnifeDamageModifier=1.25;
	};
	
	class Animal_CapreolusCapreolusF: AnimalBase
	{
		terjeOnKillHuntingExp=150;
		terjeOnHeadshotHuntingExp=150;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.25;
		terjeSkinningKnifeDamageModifier=1.25;
	};
	
	class Animal_CapreolusCapreolus: AnimalBase
	{
		terjeOnKillHuntingExp=150;
		terjeOnHeadshotHuntingExp=150;
		terjeOnButchHuntingExp=100;
		terjeHighlightWithPathfinder=1;
		terjeSkinningTimeModifier=1.25;
		terjeSkinningKnifeDamageModifier=1.25;
	};
	
	class Animal_CapraHircusF: AnimalBase
	{
		terjeOnKillHuntingExp=50;
		terjeOnHeadshotHuntingExp=50;
		terjeOnButchHuntingExp=50;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_CapraHircus: AnimalBase
	{
		terjeOnKillHuntingExp=50;
		terjeOnHeadshotHuntingExp=50;
		terjeOnButchHuntingExp=50;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_CanisLupus: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=25;
		terjeOnButchHuntingExp=50;
		terjeHighlightWithPathfinder=0;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_CanisFamiliaris_Dobermann_ColorBase: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=25;
		terjeOnButchHuntingExp=50;
		terjeHighlightWithPathfinder=0;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_CanisFamiliaris_GermanShepherd_ColorBase: AnimalBase
	{
		terjeOnKillHuntingExp=25;
		terjeOnHeadshotHuntingExp=25;
		terjeOnButchHuntingExp=50;
		terjeHighlightWithPathfinder=0;
		terjeSkinningTimeModifier=1.0;
		terjeSkinningKnifeDamageModifier=1.0;
	};
	
	class Animal_BosTaurusF: AnimalBase
	{
		terjeOnKillHuntingExp=10;
		terjeOnHeadshotHuntingExp=10;
		terjeOnButchHuntingExp=50;
		terjeSkinningTimeModifier=2.0;
		terjeSkinningKnifeDamageModifier=2.0;
	};
	
	class Animal_BosTaurus: AnimalBase
	{
		terjeOnKillHuntingExp=10;
		terjeOnHeadshotHuntingExp=10;
		terjeOnButchHuntingExp=50;
		terjeSkinningTimeModifier=2.0;
		terjeSkinningKnifeDamageModifier=2.0;
	};
	
	class Edible_Base;
	class DeadChicken_ColorBase: Edible_Base
	{
		terjeOnButchHuntingExp=10;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	class DeadRabbit: Edible_Base
	{
		terjeOnButchHuntingExp=50;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	class DeadFox: Edible_Base
	{
		terjeOnButchHuntingExp=50;
		terjeSkinningKnifeDamageModifier=0.6;
	};
	class DeadLizard: Edible_Base
	{
		terjeOnButchHuntingExp=10;
		terjeSkinningKnifeDamageModifier=0.3;
	};
	class Carp: Edible_Base
	{
		terjeOnButchFishingExp=25;
		terjeSkinningKnifeDamageModifier=0.6;
	};
	class Mackerel: Edible_Base
	{
		terjeOnButchFishingExp=25;
		terjeSkinningKnifeDamageModifier=0.6;
	};
	class WalleyePollock: Edible_Base
	{
		terjeOnButchFishingExp=25;
		terjeSkinningKnifeDamageModifier=0.6;
	};
	class SteelheadTrout: Edible_Base
	{
		terjeOnButchFishingExp=25;
		terjeSkinningKnifeDamageModifier=0.6;
	};
	class Sardines: Edible_Base
	{
		terjeOnButchFishingExp=25;
		terjeSkinningKnifeDamageModifier=0.6;
	};
	class Bitterlings: Edible_Base
	{
		terjeOnButchFishingExp=25;
		terjeSkinningKnifeDamageModifier=0.6;
	};
};
