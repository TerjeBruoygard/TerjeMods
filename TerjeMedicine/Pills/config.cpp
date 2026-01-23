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
	class TerjePills_Capsule: TerjePillsBase
	{
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
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
	class TerjePills_Oval: TerjePillsBase
	{
		model="TerjeMedicine\Pills\oval\oval.p3d";
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
	class TerjePills_Circle: TerjePillsBase
	{
		model="TerjeMedicine\Pills\circle\circle.p3d";
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
	
	class TerjePillsMagnesiumSulfate: TerjePills_Capsule
	{
		scope=2;
		displayName="#STR_TERJEMED_MAGNESIUMSULFATE";
		medBloodRegenValue=2.5;
		medBloodRegenTimeSec=120;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_4_co.paa"};
	};
	class TerjePillsAdepress: TerjePills_Capsule
	{
		scope=2;
		displayName="#STR_TERJEMED_ADEPRESS";
		medAntidepresantLevel=1;
		medAntidepresantTimer=150;
		overdosedIncrement=0.2;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_5_co.paa"};
	};
	class TerjePillsB190: TerjePills_Capsule
	{
		scope=2;
		displayName="#STR_TERJEMED_B190";
		medAntiradLevel=1;
		medAntiradTimer=140;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_6_co.paa"};
	};
	
	// ADVANCED PILLS
	class TerjePillsAnalgin: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_ANALGIN";
		medPainkillerLevel=1;
		medPainkillerTimeSec=500;
		overdosedIncrement=0.15;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_7_co.paa"};
	};
	class TerjePillsNimesulid: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_NIMESULID";
		medPainkillerLevel=1;
		medPainkillerTimeSec=600;
		overdosedIncrement=0.25;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_8_co.paa"};
	};
	class TerjePillsParacetamol: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_PARACETAMOL";
		medPainkillerLevel=1;
		medPainkillerTimeSec=200;
		overdosedIncrement=0.45;
		medAntibioticLevel=1;
		medAntibioticsTimeSec=120;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_10_co.paa"};
	};
	class TerjePillsIbuprofen: TerjePills_Capsule
	{
		scope=2;
		displayName="#STR_TERJEMED_IBUPROFEN";
		medPainkillerLevel=1;
		medPainkillerTimeSec=600;
		medAntibioticLevel=2;
		medAntibioticsTimeSec=300;
		overdosedIncrement=0.35;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_11_co.paa"};
	};
	class TerjePillsNurofen: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_NUROFEN";
		medPainkillerLevel=1;
		medPainkillerTimeSec=350;
		medAntibioticLevel=2;
		medAntibioticsTimeSec=300;
		overdosedIncrement=0.52;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_6_co.paa"};
	};
	class TerjePillsAmoxiclav: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_AMOXICLAV";
		medAntibioticLevel=2;
		medAntibioticsTimeSec=1200;
		overdosedIncrement=0.75;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_5_co.paa"};
	};
	class TerjePillsPiperacylin: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_PIPERACYLIN";
		medAntibioticLevel=2;
		medAntibioticsTimeSec=1100;
		overdosedIncrement=0.45;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_4_co.paa"};
	};
	class TerjePillsAmibaktam: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_AMIBAKTAM";
		medAntibioticLevel=1;
		medAntibioticsTimeSec=60;
		overdosedIncrement=0.05;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_3_co.paa"};
	};
	class TerjePillsPolisorb: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_POLISORB";
		medAntipoisonLevel=1;
		medAntipoisonTimeSec=300;
		overdosedIncrement=0.05;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_2_co.paa"};
	};
	class TerjePillsMesalazin: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_MESALAZIN";
		medAntipoisonLevel=2;
		medAntipoisonTimeSec=600;
		overdosedIncrement=0.35;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_1_co.paa"};
	};
	class TerjePillsFtalazol: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_FTALAZOL";
		medAntipoisonLevel=1;
		medAntipoisonTimeSec=1200;
		overdosedIncrement=0.25;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_2_co.paa"};
	};
	class TerjePillsNoopept: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_NOOPEPT";
		medPainkillerLevel=1;
		medPainkillerTimeSec=380;
		medConcussionHealTimeSec=380;
		overdosedIncrement=0.35;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_3_co.paa"};
	};
	class TerjePillsVikasol: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_VIKASOL";
		medBloodHemostaticValue=1;
		medBloodHemostaticTimeSec=300;
		overdosedIncrement=0.15;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_4_co.paa"};
	};
	class TerjePillsIrovit: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_IROVIT";
		medBloodRegenValue=1;
		medBloodRegenTimeSec=120;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_5_co.paa"};
	};
	class TerjePillsPotassiumIodide: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_POTASIUM_IODIDE";
		medAntiradLevel=1;
		medAntiradTimer=60;
		overdosedIncrement=0.2;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_6_co.paa"};
	};
	class TerjePillsHexacyanoferrate: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_HEXACYANOFERRATE";
		medAntiradLevel=1;
		medAntiradTimer=120;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_7_co.paa"};
	};
	class TerjePillsMexamine: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_MEXAMINE";
		medAntiradLevel=2;
		medAntiradTimer=25;
		overdosedIncrement=0.75;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_8_co.paa"};
	};
	class TerjePillsAgteminol: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_AGTEMINOL";
		medAntidepresantLevel=1;
		medAntidepresantTimer=120;
		overdosedIncrement=0.2;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_9_co.paa"};
	};
	class TerjePillsVenlafaxine: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_VANLAFAXINE";
		medAntidepresantLevel=1;
		medAntidepresantTimer=250;
		overdosedIncrement=0.3;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_10_co.paa"};
	};
	class TerjePillsRombiopental: TerjePills_Capsule
	{
		scope=2;
		displayName="#STR_TERJEMED_ROMBIOPENTAL";
		medAntibiohazardLevel=1;
		medAntibiohazardTimeSec=30;
		overdosedIncrement=0.15;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_7_co.paa"};
	};
	class TerjePillsPotassiumCyanide: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_CYANIDE";
		medFoodPoisonIncrement=5;
		overdosedIncrement=1.5;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_1_co.paa"};
	};
	class TerjePillsArsenic: TerjePills_Circle
	{
		scope=2;
		displayName="#STR_TERJEMED_ARSENIC";
		medFoodPoisonIncrement=3.5;
		overdosedIncrement=2.5;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\circle\data\circle_3_co.paa"};
	};
	class TerjePillsIversan: TerjePills_Oval
	{
		scope=2;
		displayName="#STR_TERJEMED_IVERSAN";
		medFoodPoisonIncrement=2.2;
		overdosedIncrement=0.5;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_4_co.paa"};
	};

	class HouseNoDestruct;
	class StaticObj_TerjePills_capsule: HouseNoDestruct
	{
		model="TerjeMedicine\Pills\capsule\capsule.p3d";
		hiddenSelections[]={"zbytek"};
	};
	class StaticObj_TerjePills_oval: HouseNoDestruct
	{
		model="TerjeMedicine\Pills\oval\oval.p3d";
		hiddenSelections[]={"zbytek"};
	};
	class StaticObj_TerjePills_circle: HouseNoDestruct
	{
		model="TerjeMedicine\Pills\circle\circle.p3d";
		hiddenSelections[]={"zbytek"};
	};
	class StaticObj_TerjePillsMagnesiumSulfate: StaticObj_TerjePills_capsule
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_4_co.paa"};
	};
	class StaticObj_TerjePillsAdepress: StaticObj_TerjePills_capsule
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_5_co.paa"};
	};
	class StaticObj_TerjePillsB190: StaticObj_TerjePills_capsule
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_6_co.paa"};
	};
	class StaticObj_TerjePillsAnalgin: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_7_co.paa"};
	};
	class StaticObj_TerjePillsNimesulid: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_8_co.paa"};
	};
	class StaticObj_TerjePillsParacetamol: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_10_co.paa"};
	};
	class StaticObj_TerjePillsIbuprofen: StaticObj_TerjePills_capsule
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\capsule\data\capsule_11_co.paa"};
	};
	class StaticObj_TerjePillsNurofen: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_6_co.paa"};
	};
	class StaticObj_TerjePillsAmoxiclav: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_5_co.paa"};
	};
	class StaticObj_TerjePillsPiperacylin: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_4_co.paa"};
	};
	class StaticObj_TerjePillsAmibaktam: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_3_co.paa"};
	};
	class StaticObj_TerjePillsPolisorb: StaticObj_TerjePills_oval
	{
		scope=1;
		hiddenSelectionsTextures[]={"TerjeMedicine\Pills\oval\data\oval_2_co.paa"};
	};
};
