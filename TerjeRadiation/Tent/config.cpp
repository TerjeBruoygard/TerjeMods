class CfgPatches
{
	class TerjeRadiation_Tent
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"TerjeRadiation",
			"DZ_Gear_Camping",
			"DZ_Data"
		};
	};
};

class CfgSlots
{
	class Slot_CanisterGasoline
	{
		name="CanisterGasoline";
		displayName="#STR_TERJERAD_CANISTRE";
		selection="CanisterGasoline";
		ghostIcon="set:TerjeRadiation_icon image:tr_canistre";
	};
	class Slot_TerjeShower
	{
		name="TerjeShower";
		displayName="#STR_TERJERAD_SHOWER";
		selection="Shower";
		ghostIcon="set:TerjeRadiation_icon image:tr_shower";
	};
	class Slot_TerjePump 
	{
		name="TerjePump";
		displayName="#STR_TERJERAD_PUMP";
		selection="Pump";
		ghostIcon="set:TerjeRadiation_icon image:tr_pump";
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyJerryCan: ProxyAttachment
	{
		model="dz\vehicles\parts\jerrycan.p3d";
		inventoryslot[] += {"CanisterGasoline"};
	};
	class ProxyPump: ProxyAttachment
	{
		model="TerjeRadiation\Tent\Pump.p3d";
		inventoryslot[] += {"TerjePump"};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class TentBase;
	class Bottle_Base;
	class CanisterGasoline: Bottle_Base
	{
		inventorySlot[] += {"CanisterGasoline"};
	};

	class TerjeShower : Inventory_Base 
	{
		scope=2;
		displayName="#STR_TERJERAD_SHOWER";
		descriptionShort="#STR_TERJERAD_SHOWER_DESC";
		model="TerjeRadiation\Tent\Hose.p3d";
		weight=1000;
		absorbency=0;
		itemSize[]={3, 3};
		rotationFlags=17;
		inventorySlot[]={"TerjeShower"};
		repairableWithKits[]={6};
		repairCosts[]={25.0};
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeRadiation\Tent\data\hose_co.paa"};

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeRadiation\Tent\data\hose_mat.rvmat"}},
						{0.7,{"TerjeRadiation\Tent\data\hose_mat.rvmat"}},
						{0.5,{"TerjeRadiation\Tent\data\hose_mat.rvmat"}},
						{0.3,{"TerjeRadiation\Tent\data\hose_mat.rvmat"}},
						{0.0,{"TerjeRadiation\Tent\data\hose_mat.rvmat"}}
					};
				};
			};
		};
		
		class AnimEvents
		{
			class SoundWeapon
			{
				class Stitch
				{
					soundSet="StitchUpSelf_SoundSet";
					id=201;
				};
				class pickup
				{
					soundSet="sewingkit_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="sewingkit_drop_SoundSet";
					id=898;
				};
			};
		};
	};

	class TerjePump : Inventory_Base 
	{
		scope=2;
		displayName="#STR_TERJERAD_PUMP";
		descriptionShort="#STR_TERJERAD_PUMP_DESC";
		model="TerjeRadiation\Tent\Pump.p3d";
		weight=1000;
		absorbency=0;
		itemSize[]={4, 3};
		rotationFlags=0;
		repairableWithKits[]={7};
		repairCosts[]={25.0};
		inventorySlot[]={"TerjePump"};
		hiddenSelections[]={"zbytek"};
		hiddenSelectionsTextures[]={"TerjeRadiation\Tent\data\pump_co.paa"};

		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						{1.0,{"TerjeRadiation\Tent\data\pump_mat.rvmat"}},
						{0.7,{"TerjeRadiation\Tent\data\pump_mat.rvmat"}},
						{0.5,{"TerjeRadiation\Tent\data\pump_mat.rvmat"}},
						{0.3,{"TerjeRadiation\Tent\data\pump_mat.rvmat"}},
						{0.0,{"TerjeRadiation\Tent\data\pump_mat.rvmat"}}
					};
				};
			};
		};
		
		class AnimEvents
		{
			class SoundWeapon
			{
				class Stitch
				{
					soundSet="StitchUpSelf_SoundSet";
					id=201;
				};
				class pickup
				{
					soundSet="sewingkit_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="sewingkit_drop_SoundSet";
					id=898;
				};
			};
		};
	};

	class TerjeRadTent: TentBase
	{
		scope=2;
		displayName="#STR_TERJERAD_RADTENT";
		descriptionShort="#STR_TERJERAD_RADTENT_DESC";
		model="TerjeRadiation\Tent\RadTent.p3d";
		bounding="BSphere";
		overrideDrawArea="3.0";
		forceFarBubble="true";
		slopeTolerance=0.3;
		yawPitchRollLimit[]={15,15,15};
		hiddenSelections[]=
		{
			"bags",
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeRadiation\Tent\data\radtent_co.paa",
			"TerjeRadiation\Tent\data\radtentplace_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"TerjeRadiation\Tent\data\radtent_mat.rvmat",
			"TerjeRadiation\Tent\data\radtentplace_mat.rvmat"
		};
		openable=0;
		absorbency=0;
		carveNavmesh=1;
		weight=60000;
		itemSize[]={10,5};
		itemsCargoSize[]={0,0};
		itemBehaviour=0;
		lootCategory="Tents";
		placement="ForceSlopeOnTerrain";
		physLayer="item_large";
		repairableWithKits[]={5,2};
		repairCosts[]={30,25};
		attachments[]=
		{
			"CanisterGasoline",
			"TerjeShower",
			"TerjePump",
			"CarBattery"
		};
		class EnergyManager
		{
			hasIcon=1;
			autoSwitchOff=1;
			autoSwitchOffWhenInCargo=1;
			energyUsagePerSecond=0.05;
			plugType=5;
			attachmentAction=1;
			updateInterval=1.0;
		};
		minPlacingDist=10;
		rotationFlags=2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1700;
					healthLevels[]=
					{
						{1.0,{""}},
						{0.7,{""}},
						{0.5,{""}},
						{0.3,{""}},
						{0.0,{""}}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0.05;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0.3;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=8;
					};
				};
			};
			class DamageZones
			{
				class Body
				{
					class Health
					{
						hitpoints=1700;
						transferToGlobalCoef=0.5;
						healthLevels[]=
						{
							{1.0,{"TerjeRadiation\Tent\data\radtent_mat.rvmat","DZ\gear\camping\data\tent_pristine_co.paa"}},
							{0.7,{"TerjeRadiation\Tent\data\radtent_mat.rvmat","DZ\gear\camping\data\tent_worn_co.paa"}},
							{0.5,{"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat","DZ\gear\camping\data\tent_damage_co.paa"}},
							{0.3,{"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat","DZ\gear\camping\data\tent_destruct_co.paa"}},
							{0.0,{"TerjeRadiation\Tent\data\radtent_mat_destruct.rvmat","DZ\gear\camping\data\tent_destruct_co.paa"}}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.05;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.3;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=8;
							};
						};
					};
					componentNames[]=
					{
						"body"
					};
					transferToZonesNames[]=
					{
						"Inventory"
					};
					transferToZonesCoefs[]={1};
					fatalInjuryCoef=-1;
				};
				class Inventory
				{
					class Health
					{
						hitpoints=1700;
						transferToGlobalCoef=0.5;
						healthLevels[]=
						{
							{1.0,{"TerjeRadiation\Tent\data\radtent_mat.rvmat"}},
							{0.7,{"TerjeRadiation\Tent\data\radtent_mat.rvmat"}},
							{0.5,{"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat"}},
							{0.3,{"TerjeRadiation\Tent\data\radtent_mat_damage.rvmat"}},
							{0.0,{"TerjeRadiation\Tent\data\radtent_mat_destruct.rvmat"}}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.05;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.3;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=8;
							};
						};
					};
					componentNames[]=
					{
						"inventory"
					};
					transferToZonesNames[]=
					{
						"Body"
					};
					transferToZonesCoefs[]={1,1};
					fatalInjuryCoef=-1;
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Attachments
			{
				name="$STR_attachment_accessories";
				description="";
				attachmentSlots[]=
				{
					"CanisterGasoline",
					"TerjeShower",
					"TerjePump",
					"CarBattery"
				};
				icon="set:dayz_inventory image:cat_fp_tents";
				view_index=1;
			};
		};
		class AnimationSources
		{
			class Body
			{
				source="user";
				animPeriod=0.01;
				initPhase=1;
			};
			class Shower
			{
				source="user";
				animPeriod=0.01;
				initPhase=1;
			};
			class Inventory
			{
				source="user";
				animPeriod=0.01;
				initPhase=1;
			};
			class Canistre_plug
			{
				source="user";
				initPhase=1;
				animPeriod=0.01;
			};
			class Cord_folded
			{
				source="user";
				initPhase=1;
				animPeriod=0.01;
			};
			class Cord_plugged
			{
				source="user";
				initPhase=1;
				animPeriod=0.01;
			};
			class Pack
			{
				source="user";
				initPhase=1;
				animPeriod=0.01;
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="cartent_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpTentLight_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpTent_SoundSet";
					id=797;
				};
				class mediumtent_drop
				{
					soundset="mediumtent_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class TerjeRadTentPlacing: TerjeRadTent
	{
		scope=1;
		displayName="#STR_TERJERAD_RADTENT";
		descriptionShort="#STR_TERJERAD_RADTENT_DESC";
		model="TerjeRadiation\Tent\RadTentPlacing.p3d";
		storageCategory=10;
		hiddenSelections[]=
		{
			"placing"
		};
		hiddenSelectionsTextures[]=
		{
			"TerjeRadiation\Tent\data\radtentplace_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"TerjeRadiation\Tent\data\radtentplace_mat.rvmat"
		};
		hologramMaterial="radtentplace_mat";
		hologramMaterialPath="TerjeRadiation\Tent\data";
		class AnimationSources
		{
			class Placing
			{
				source="user";
				animPeriod=0.01;
				initPhase=1;
			};
		};
	};
	
	class HouseNoDestruct;
	class TerjeRadTentStatic: HouseNoDestruct
	{
		scope=1;
		model="TerjeRadiation\Tent\RadTentStatic.p3d";
		displayName="#STR_TERJERAD_RADTENT";
		descriptionShort="#STR_TERJERAD_RADTENT_DESC";
	};
};

class CfgSoundShaders
{
	class TerjeRadTentShowerSoundShader
	{
		samples[]={{"TerjeRadiation\Tent\sound\shower",0.9}};
		volume=1;
		range=50;
	};
	class TerjeRadTentPumpSoundShader
	{
		samples[]={{"TerjeRadiation\Tent\sound\pump",0.9}};
		volume=2;
		range=25;
	};
};

class CfgSoundSets
{
	class TerjeRadTentShower_SoundSet
	{
		sound3DProcessingType="infected3DProcessingType";
		volumeCurve="infectedAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
		soundShaders[]={"TerjeRadTentShowerSoundShader"};
	};
	class TerjeRadTentPump_SoundSet
	{
		sound3DProcessingType="infected3DProcessingType";
		volumeCurve="infectedAttenuationCurve";
		spatial=1;
		doppler=0;
		loop=0;
		soundShaders[]={"TerjeRadTentPumpSoundShader"};
	};
};
