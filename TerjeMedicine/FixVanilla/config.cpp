class CfgPatches
{
	class TerjeMedicine_FixVanilla
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeMedicine", "DZ_Characters_Vests", "DZ_Characters_Headgear"
		};
	};
};

class CfgVehicles
{
	class Clothing;
	class Edible_Base;
	class Inventory_Base;

	class PlateCarrierVest: Clothing 
	{
		class Protection
		{
			melee=0.8;
			firearm=0.45;
		};
	};

	class PressVest_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.6;
			firearm=0.35;
		};
	};

	class PoliceVest: Clothing
	{
		class Protection
		{
			melee=0.6;
			firearm=0.15;
		};
	};
	
	class BallisticHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.5;
			firearm=0.35;
		};
	};

	class ZSh3PilotHelmet: Clothing
	{
		class Protection
		{
			melee=0.5;
		};
	};

	class ConstructionHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.5;
		};
	};

	class MotoHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.8;
		};
	};

	class DarkMotoHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.8;
		};
	};

	class TankerHelmet: Clothing
	{
		class Protection
		{
			melee=0.5;
		};
	};

	class GorkaHelmet: Clothing
	{
		class Protection
		{
			melee=0.6;
		};
	};

	class FirefightersHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.5;
		};
	};

	class SkateHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.5;
		};
	};

	class Ssh68Helmet: Clothing
	{
		class Protection
		{
			melee=0.5;
			firearm=0.15;
		};
	};

	class DirtBikeHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.8;
		};
	};

	class HockeyHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.8;
		};
	};

	class Mich2001Helmet: Clothing
	{
		class Protection
		{
			melee=0.7;
			firearm=0.35;
		};
	};

	class T56TankerHelmet_ColorBase: Clothing
	{
		class Protection
		{
			melee=0.7;
			firearm=0.35;
		};
	};
	
	class Chestplate: Clothing
	{
		class Protection
		{
			melee = 0.65;
			firearm = 0.25;
		};
	};
	
	class Chainmail: Clothing
	{
		class Protection
		{
			melee = 0.6;
			firearm = 0.1;
		};
	};
	
	class Chainmail_Leggings: Clothing
	{
		class Protection
		{
			melee = 0.5;
			firearm = 0.1;
		};
	};
	
	class Chainmail_Coif: Clothing
	{
		class Protection
		{
			melee = 0.5;
			firearm = 0.1;
		};
	};
	
	class GreatHelm: Clothing
	{
		class Protection
		{
			melee = 0.5;
			firearm = 0.1;
		};
	};
	
	class NorseHelm: Clothing
	{
		class Protection
		{
			melee = 0.5;
			firearm = 0.1;
		};
	};
	
	class BandageDressing: Inventory_Base
	{
		medBloodStop=2;
		medicalItem=1;
	};

	class Thermometer: Inventory_Base
	{
		medicalItem=1;
	};

	class Bandana_ColorBase: Clothing
	{
		medBloodStop=2;
	};

	class Rag: Inventory_Base
	{
		medBloodStop=2;
		canBeSplit = 1;
		varQuantityInit = 1.0;
		varQuantityMin = 0.0;
		varQuantityMax = 10.0;
		varQuantityDestroyOnMin = 1;
	};

	class SurgicalGloves_ColorBase: Clothing
	{
		medGloves=1;
		varCleannessInit=1;
		canBeDisinfected=1;
		medicalItem=1;
	};
	
	class VitaminBottle: Edible_Base
	{
		medicalItem=1;
		overdosedIncrement = 0.01;
		medImmunityGainValue=1;
		medImmunityGainTimeSec=120;
		medImmunityGainMaxTimeSec=1800;
	};

	class PurificationTablets: Edible_Base
	{
		medicalItem=1;
	};

	class IodineTincture: Edible_Base
	{
		medicalItem=1;
	};

	class DisinfectantAlcohol: Edible_Base
	{
		medicalItem=1;
	};

	class DisinfectantSpray: Edible_Base
	{
		medicalItem=1;
	};

	class SalineBag: Inventory_Base
	{
		medicalItem=1;
	};

	class StartKitIV: Inventory_Base
	{
		medicalItem=1;
	};

	class SalineBagIV: Inventory_Base
	{
		medicalItem=1;
	};

	class BloodBagEmpty: Inventory_Base
	{
		medicalItem=1;
	};

	class BloodBagFull: Inventory_Base
	{
		medicalItem=1;
	};

	class BloodBagIV: Inventory_Base
	{
		medicalItem=1;
	};

	class BloodTestKit: Inventory_Base
	{
		medicalItem=1;
	};
	
	class SewingKit: Inventory_Base
	{
		terjeOverrideSurgeryConsumeQuantity=50;
		terjeSurgeryVisceraEffectivity=0.01;
		terjeSurgeryVisceraTime=300;
		terjeSurgeryBulletEffectivity=0.1;
		terjeSurgeryBulletTime=120;
		terjeSurgeryStubEffectivity=0.3;
		terjeSurgeryStubTime=60;
	};
};
