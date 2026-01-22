class CfgPatches
{
	class TerjeMedicine_Pills
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeMedicine"
		};
	};
};

class CfgVehicles
{
	class Edible_Base;
	
	// BASE PILLS
	class TerjePillsBase: Edible_Base
	{
		descriptionShort="#STR_TERJEMED_TABLETS_DESC";
		debug_ItemCategory=7;
		rotationFlags=17;
		canBeSplit=1;
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		varQuantityDestroyOnMin=1;
		varTemperatureMin=0;
		varTemperatureMax=0;
		itemSize[]={1,2};
		weight=20;
		weightPerQuantityUnit=2;
		stackedUnit="pills";
		quantityBar=0;
		absorbency=0;
		medicalItem=1;
		medicalPillsCategory=1;
		hiddenSelections[]={"zbytek"};
		medSkillExpAddToSelf=10;
		medPainkillerMaxTimeSec=1800;
		medAntipoisonMaxTimeSec=1800;
		medAntibiohazardMaxTimeSec=1800;
		medAntibioticsMaxTimeSec=1800;
		medRabiesAntibioticMaxTimeSec=1800;
		medZAntidotMaxTimeSec=1800;
		medAntisepsisMaxTimeSec=1800;
		medConcussionHealMaxTimeSec=1800;
		medBloodHemostaticMaxTimeSec=1800;
		medBloodRegenMaxTimeSec=1800;
		medHematomaHealMaxTimeSec=1800;
		medAdrenalinMaxTimeSec=1800;
		medAntidepresantMaxTimer=1800;
		medImmunityGainMaxTimer=1800;
		class AnimEvents
		{
			class SoundWeapon
			{
				class Tablets_open
				{
					soundSet="Tablets_open_SoundSet";
					id=201;
				};
				class Tablets_catch
				{
					soundSet="Tablets_catch_SoundSet";
					id=202;
				};
				class Tablets_close
				{
					soundSet="Tablets_close_SoundSet";
					id=203;
				};
				class pickup
				{
					soundSet="purificationtablets_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="purificationtablets_drop_SoundSet";
					id=898;
				};
			};
		};
	};

	class CharcoalTablets: Edible_Base
	{
		descriptionShort="#STR_TERJEMED_TABLETS_DESC";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		medAntipoisonLevel=1;
		medAntipoisonTimeSec=300;
		overdosedIncrement=0.01;
		medicalItem=1;
		medSkillExpAddToSelf=5;
		medicalPillsCategory=1;
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_11_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class ChelatingTablets: Edible_Base
	{
		descriptionShort="#STR_TERJEMED_TABLETS_DESC";
		medAntipoisonLevel=2;
		medAntipoisonTimeSec=600;
		overdosedIncrement=0.6;
		medicalItem=1;
		medSkillExpAddToSelf=15;
		medicalPillsCategory=1;
	};
	
	class PainkillerTablets: Edible_Base
	{
		descriptionShort="#STR_TERJEMED_TABLETS_DESC";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		medPainkillerLevel=1;
		medPainkillerTimeSec=300;
		medSkillExpAddToSelf=10;
		overdosedIncrement=0.2;
		medicalItem=1;
		medicalPillsCategory=1;
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_2_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TetracyclineAntibiotics: Edible_Base
	{
		descriptionShort="#STR_TERJEMED_TABLETS_DESC";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		varQuantityInit=10;
		varQuantityMin=0;
		varQuantityMax=10;
		medAntibioticLevel=1;
		medAntibioticsTimeSec=300;
		medSkillExpAddToSelf=10;
		overdosedIncrement=0.45;
		medicalItem=1;
		medicalPillsCategory=1;
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_3_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsMagnesiumSulfate : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_MAGNESIUMSULFATE";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		medBloodRegenValue=2.5;
		medBloodRegenTimeSec=120;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_4_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsAdepress : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ADEPRESS";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		medAntidepresantLevel=1;
		medAntidepresantTimer=150;
		overdosedIncrement=0.2;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_5_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsB190 : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_B190";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		medAntiradLevel=1;
		medAntiradTimer=140;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_6_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	// ADVANCED PILLS
	class TerjePillsAnalgin : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ANALGIN";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medPainkillerLevel=1;
		medPainkillerTimeSec=500;
		overdosedIncrement=0.15;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_7_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsNimesulid : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NIMESULID";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medPainkillerLevel=1;
		medPainkillerTimeSec=600;
		overdosedIncrement=0.25;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_8_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsParacetamol : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_PARACETAMOL";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medPainkillerLevel=1;
		medPainkillerTimeSec=200;
		overdosedIncrement=0.45;
		medAntibioticLevel=1;
		medAntibioticsTimeSec=120;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_10_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsIbuprofen : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_IBUPROFEN";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		medPainkillerLevel=1;
		medPainkillerTimeSec=600;
		medAntibioticLevel=2;
		medAntibioticsTimeSec=300;
		overdosedIncrement=0.35;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_11_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsNurofen : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NUROFEN";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medPainkillerLevel=1;
		medPainkillerTimeSec=350;
		medAntibioticLevel=2;
		medAntibioticsTimeSec=300;
		overdosedIncrement=0.52;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_6_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsAmoxiclav : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AMOXICLAV";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medAntibioticLevel=2;
		medAntibioticsTimeSec=1200;
		overdosedIncrement=0.75;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_5_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsPiperacylin : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_PIPERACYLIN";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medAntibioticLevel=2;
		medAntibioticsTimeSec=1100;
		overdosedIncrement=0.45;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_4_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsAmibaktam : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AMIBAKTAM";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medAntibioticLevel=1;
		medAntibioticsTimeSec=60;
		overdosedIncrement=0.05;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_3_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsPolisorb : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_POLISORB";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medAntipoisonLevel=1;
		medAntipoisonTimeSec=300;
		overdosedIncrement=0.05;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_2_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsMesalazin : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_MESALAZIN";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntipoisonLevel=2;
		medAntipoisonTimeSec=600;
		overdosedIncrement=0.35;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_1_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsFtalazol : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_FTALAZOL";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntipoisonLevel=1;
		medAntipoisonTimeSec=1200;
		overdosedIncrement=0.25;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_2_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsNoopept : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_NOOPEPT";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medPainkillerLevel=1;
		medPainkillerTimeSec=380;
		medConcussionHealTimeSec=380;
		overdosedIncrement=0.35;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_3_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsVikasol : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_VIKASOL";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medBloodHemostaticValue=1;
		medBloodHemostaticTimeSec=300;
		overdosedIncrement=0.15;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_4_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsIrovit : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_IROVIT";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medBloodRegenValue=1;
		medBloodRegenTimeSec=120;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_5_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsPotassiumIodide : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_POTASIUM_IODIDE";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntiradLevel=1;
		medAntiradTimer=60;
		overdosedIncrement=0.2;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_6_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsHexacyanoferrate : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_HEXACYANOFERRATE";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntiradLevel=1;
		medAntiradTimer=120;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_7_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsMexamine : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_MEXAMINE";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntiradLevel=2;
		medAntiradTimer=25;
		overdosedIncrement=0.75;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_8_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsAgteminol : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_AGTEMINOL";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntidepresantLevel=1;
		medAntidepresantTimer=120;
		overdosedIncrement=0.2;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_9_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsVenlafaxine : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_VANLAFAXINE";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medAntidepresantLevel=1;
		medAntidepresantTimer=250;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_10_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsRombiopental : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ROMBIOPENTAL";
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		medAntibiohazardLevel=1;
		medAntibiohazardTimeSec=30;
		overdosedIncrement=0.15;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_7_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\capsule\data\capsule_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\capsule\data\capsule_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\capsule\data\capsule_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsPotassiumCyanide : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_CYANIDE";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medFoodPoisonIncrement=5;
		overdosedIncrement=1.5;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_1_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsArsenic : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_ARSENIC";
		model="TerjeMedicine\Pills\circle\circle.p3d";
		medFoodPoisonIncrement=3.5;
		overdosedIncrement=2.5;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_3_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\circle\data\circle_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\circle\data\circle_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\circle\data\circle_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};
	
	class TerjePillsIversan : TerjePillsBase
	{
		scope=2;
		displayName="#STR_TERJEMED_IVERSAN";
		model="TerjeMedicine\Pills\oval\oval.p3d";
		medFoodPoisonIncrement=2.2;
		overdosedIncrement=0.5;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_4_co.paa"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.7,{"TerjeMedicine\Pills\oval\data\oval_mat.rvmat"}},
						{0.5,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.3,{"TerjeMedicine\Pills\oval\data\oval_mat_damage.rvmat"}},
						{0.0,{"TerjeMedicine\Pills\oval\data\oval_mat_destruct.rvmat"}}
					};
				};
			};
		};
	};

	class HouseNoDestruct;

	class StaticObj_TerjePillsMagnesiumSulfate : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_4_co.paa"};
	};
	
	class StaticObj_TerjePillsAdepress : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_5_co.paa"};
	};
	
	class StaticObj_TerjePillsB190 : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_6_co.paa"};
	};
	
	class StaticObj_TerjePillsAnalgin : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_7_co.paa"};
	};
	
	class StaticObj_TerjePillsNimesulid : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_8_co.paa"};
	};
	
	class StaticObj_TerjePillsParacetamol : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_10_co.paa"};
	};
	
	class StaticObj_TerjePillsIbuprofen : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_11_co.paa"};
	};
	
	class StaticObj_TerjePillsNurofen : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_6_co.paa"};
	};
	
	class StaticObj_TerjePillsAmoxiclav : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_5_co.paa"};

	};
	
	class StaticObj_TerjePillsPiperacylin : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_4_co.paa"};
	};
	
	class StaticObj_TerjePillsAmibaktam : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_3_co.paa"};
	};
	
	class StaticObj_TerjePillsPolisorb : HouseNoDestruct
	{
		scope=1;
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_2_co.paa"};
	};
};