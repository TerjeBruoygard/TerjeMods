enum TerjePlayerStatesMask
{
	TERJE_GOD_MODE,
	TERJE_INVISIBLE_LOCAL,
	TERJE_INVISIBLE_REMOTE,
	TERJE_NOCLIP,
	TERJE_NOTARGET,
	TERJE_FREEZE,
	TERJE_NOSIMULATE,
	TERJE_IGNORE_DAMAGE,
	TERJE_NOHEATCOMFORT,
	TERJE_INDESTRUCTIBLE,
	TERJE_MAINTENANCE_MODE
}

modded class PlayerBase
{
	private const int TERJE_CORE_STORE_BEGIN_MARKER_V1 = 133986254;
	private const int TERJE_CORE_STORE_END_MARKER_V1 = 1860587056;
	private int m_terjePlayerSpawnState = 0;
	private int m_terjePlayerStatesMask = 0;
	private int m_terjePlayerStatesMaskClient = 0;
	private int m_terjeModifierId = 0;
	private ref array<ref TerjePlayerModifierBase> m_terjeModifiers;
	private ref TerjePlayerProfile m_terjeProfile = null;
	private float m_terjeProfileSynchTimer = 0;
	private ref TerjePlayerStats m_terjeStats = null;
	private float m_terjeStatsSynchTimer = 0;
	private ref TerjePlayerSkillsAccessor m_terjePlayerSkillsAccessor = null;
	private ref TerjePlayerSoulsAccessor m_terjePlayerSoulsAccessor = null;
	private ref TerjePlayerHealthAccessor m_terjePlayerHealthAccessor = null;
	
	// void OnTerjeAttachmentChangedEvent(string slotName, EntityAI entity, bool state)
	ref ScriptInvoker OnTerjeAttachmentChangedEvent = new ScriptInvoker;
	
	void SetTerjePlayerSpawnState(int state)
	{
		m_terjePlayerSpawnState = state;
	}
	
	void OnTerjePlayerLoaded() 
	{
		//Calling the function to load blood type on player load
		TerjePlayerLoadBloodType()
	}
	
	void OnTerjePlayerRespawned() 
	{
		//Calling the function to load blood type on respawn
		TerjePlayerLoadBloodType()
	}
	
	void OnTerjeProfileFirstCreation() {}
	
	void OnTerjeProfileChanged() {}
	
	void OnTerjeStatsChanged() {}
	
	void OnTerjeUpdateServerTick(float deltaTime) {}
	
	void OnTerjeRegisterModifiers(array<ref TerjePlayerModifierBase> modifiers)
	{
		modifiers.Insert(new TerjePlayerModifierLifetime());
	}
	
	// Load persisted blood type from terje profile
	void TerjePlayerLoadBloodType()
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_PERSIST_BLOOD_TYPE) && GetTerjeProfile() != null)
			{
				int bloodType = GetTerjeProfile().GetBloodType();
				if (bloodType != -1)
				{
					GetStatBloodType().Set(bloodType);
				}
			}
		}
	}

	ref TerjePlayerProfile CreateTerjeProfile()
	{
		if (GetGame() && IsAlive() && GetIdentity() && (GetGame().IsDedicatedServer() || IsTerjeLocalControlledPlayer()))
		{
			m_terjeProfile = new TerjePlayerProfile;
			m_terjeProfile.OnInit();
		}
		
		return m_terjeProfile;
	}
	
	TerjePlayerProfile GetTerjeProfile()
	{
		return m_terjeProfile;
	}
	
	TerjePlayerStats GetTerjeStats()
	{
		if (m_terjeStats == null && IsAlive() && GetIdentity())
		{
			if (GetGame().IsDedicatedServer() || IsTerjeLocalControlledPlayer())
			{
				m_terjeStats = new TerjePlayerStats;
				m_terjeStats.OnInit();
			}
		}
		
		return m_terjeStats;
	}
	
	TerjePlayerSkillsAccessor GetTerjeSkills()
	{
		if (m_terjePlayerSkillsAccessor == null && IsAlive() && GetIdentity())
		{
			if (GetGame().IsDedicatedServer() || IsTerjeLocalControlledPlayer())
			{
				m_terjePlayerSkillsAccessor = new TerjePlayerSkillsAccessor(this);
			}
		}
		
		return m_terjePlayerSkillsAccessor;
	}
	
	TerjePlayerSoulsAccessor GetTerjeSouls()
	{
		if (m_terjePlayerSoulsAccessor == null && IsAlive() && GetIdentity())
		{
			if (GetGame().IsDedicatedServer() || IsTerjeLocalControlledPlayer())
			{
				m_terjePlayerSoulsAccessor = new TerjePlayerSoulsAccessor(this);
			}
		}
		
		return m_terjePlayerSoulsAccessor;
	}
	
	TerjePlayerHealthAccessor GetTerjeHealth()
	{
		if (m_terjePlayerHealthAccessor == null)
		{
			m_terjePlayerHealthAccessor = new TerjePlayerHealthAccessor(this);
		}
		
		return m_terjePlayerHealthAccessor;
	}
	
	bool HasActiveTerjeStartScreen()
	{
		return false;
	}
	
	string GetTerjeCharacterName()
	{
		if (GetIdentity() != null)
		{
			return GetIdentity().GetName();
		}
		
		if (GetCachedName() != string.Empty)
		{
			return GetCachedName();
		}
		
		return string.Empty;
	}
	
	bool AddTerjeRadiation(float rAmount)
	{
		// Universal interface to insert radiation agents into the player body.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	bool AddTerjeRadiationAdvanced(float rAmount, float environmentRadiation, bool ignoreProtection)
	{
		// Universal interface to insert radiation agents into the player body with extra parameters.
		// Implemented in TerjeRadiation mod.
		return false;
	}
	
	float GetTerjeRadiation()
	{
		// Universal interface to get radiation agents from the player body.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	float GetTerjeRadiationAdvanced(bool body, bool itemInHands, bool equipment)
	{
		// Universal interface to get radiation agents from the player with extended options.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	float GetTerjeRadiationProtection(float environmentRadiation)
	{
		// Universal interface to get radiation agents from the player body.
		// Implemented in TerjeRadiation mod.
		return 0;
	}
	
	bool IsTerjeLocalControlledPlayer()
	{
		return GetGame().IsClient() && (GetGame().GetPlayer() == this);
	}
	
	bool HasTerjeSicknesOrInjures()
	{
		if (GetStatWater() != null && GetStatWater().Get() < PlayerConstants.SL_WATER_LOW)
		{
			return true;
		}
		
		if (GetStatEnergy() != null && GetStatEnergy().Get() < PlayerConstants.SL_ENERGY_LOW)
		{
			return true;
		}
		
		return false;
	}
	
	override void Init()
	{
		super.Init();

		RegisterNetSyncVariableInt("m_terjePlayerStatesMask");
		if (GetGame().IsDedicatedServer())
		{
			ref array<ref TerjePlayerModifierBase> terjeModifiers = new array<ref TerjePlayerModifierBase>;
			OnTerjeRegisterModifiers(terjeModifiers);
			m_terjeModifiers = terjeModifiers;
			m_terjeModifierId = 0;
			m_terjeProfileSynchTimer = GetTerjeSettingFloat(TerjeSettingsCollection.CORE_PROFILE_SYNCH_INTERVAL);
			m_terjeStatsSynchTimer = GetTerjeSettingFloat(TerjeSettingsCollection.CORE_STATS_SYNCH_INTERVAL);
		}
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}
		
		if (!TerjeStorageHelpers.VerifyMarker(ctx, TERJE_CORE_STORE_BEGIN_MARKER_V1))
		{
			return false;
		}
		
		if (GetGame().IsDedicatedServer() && GetTerjeStats() != null)
		{
			if (!GetTerjeStats().OnStoreLoad(ctx))
			{
				TerjeLog_Error("Failed to read player stats.");
				return false;
			}
		}
		
		if (!TerjeStorageHelpers.VerifyMarker(ctx, TERJE_CORE_STORE_END_MARKER_V1))
		{
			return false;
		}
		
		return true;
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		TerjeStorageHelpers.WriteMarker(ctx, TERJE_CORE_STORE_BEGIN_MARKER_V1);
		if (GetGame().IsDedicatedServer() && GetTerjeStats() != null)
		{
			GetTerjeStats().OnStoreSave(ctx);
		}
		
		TerjeStorageHelpers.WriteMarker(ctx, TERJE_CORE_STORE_END_MARKER_V1);
	}
	
	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item, slot_name);
		
		if (OnTerjeAttachmentChangedEvent != null)
		{
			OnTerjeAttachmentChangedEvent.Invoke(slot_name, item, true);
		}
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		
		if (OnTerjeAttachmentChangedEvent != null)
		{
			OnTerjeAttachmentChangedEvent.Invoke(slot_name, item, false);
		}
	}
	
	void OnTerjePlayerKilledEvent()
	{
		// Save persisted blood type to terje profile
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_PERSIST_BLOOD_TYPE) && GetTerjeProfile() != null)
			{
				GetTerjeProfile().SetBloodType(GetStatBloodType().Get());
			}
		}
	}
	
	override void OnDisconnect()
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjeGodMode(false);
			SetTerjeIndestructible(false);
			SetTerjeIgnoreDamage(false);
			
			if (GetTerjeSettingBool(TerjeSettingsCollection.CORE_FIX_KILL_ON_DISCONNECT) && (IsUnconscious() || IsRestrained()))
			{
				// Kill player in unconscious or restrained before disconnect to fix EEKilled call and process terje stats and profile
				SetHealth("", "", 0.0);
			}
		}
		
		super.OnDisconnect();
	}
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
		if (!GetTerjeMaintenanceMode())
		{
			OnTerjePlayerKilledEvent();
		}
		
		m_terjeModifiers = null;
		m_terjeProfile = null;
		m_terjeStats = null;
		m_terjePlayerSkillsAccessor = null;
		m_terjePlayerSoulsAccessor = null;
	}
	
	override bool HasHealings()
	{
		bool result = super.HasHealings();
		bool detailedHealingHudBadges = false;
		if (!result && GetTerjeStats() && GetTerjeSettingBool(TerjeSettingsCollection.CORE_DETAILED_HEALING_HUD_BADGES, detailedHealingHudBadges) && !detailedHealingHudBadges)
		{
			return HasTerjeHealings();
		}
		
		return result;
	}
	
	bool HasTerjeHealings()
	{
		return false;
	}
	
	override bool HasDisease()
	{
		bool result = super.HasDisease();
		bool detailedDiseaseHudBadges = false;
		if (!result && GetTerjeStats() && GetTerjeSettingBool(TerjeSettingsCollection.CORE_DETAILED_DISEASE_HUD_BADGES, detailedDiseaseHudBadges) && !detailedDiseaseHudBadges)
		{
			return HasTerjeDisease();
		}
		
		return result;
	}
	
	bool HasTerjeDisease()
	{
		return false;
	}
	
	override void OnScheduledTick(float deltaTime)
	{
		super.OnScheduledTick(deltaTime);
		
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			if (GetIdentity() && IsAlive() && GetTerjeProfile() != null && GetTerjeStats() != null)
			{
				if (m_terjePlayerSpawnState != 0)
				{
					int spawnState = m_terjePlayerSpawnState;
					m_terjePlayerSpawnState = 0;
					
					if (spawnState == 1)
					{
						OnTerjePlayerRespawned();
					}
					else if (spawnState == 2)
					{
						OnTerjePlayerLoaded();
					}
				}
				
				OnTerjeUpdateServerTick(deltaTime);
			}

			if (GetIdentity() && IsAlive() && (GetTerjeProfile() != null) && (GetTerjeStats() != null) && (m_terjeModifiers != null) && (m_terjeModifiers.Count() > 0) && (!HasActiveTerjeStartScreen()))
			{
				foreach (ref TerjePlayerModifierBase terjeIterModifier : m_terjeModifiers)
				{
					if (terjeIterModifier != null)
					{
						terjeIterModifier.CallServerTimerIncrement(deltaTime);
					}
				}
				
				if (m_terjeModifierId >= m_terjeModifiers.Count())
				{
					m_terjeModifierId = 0;
				}
				
				ref TerjePlayerModifierBase terjeCurModifier = m_terjeModifiers.Get(m_terjeModifierId);
				if (terjeCurModifier != null)
				{
					terjeCurModifier.CallServerTick(this);
				}
				
				m_terjeModifierId = m_terjeModifierId + 1;
			}
			
			if (GetIdentity() && IsAlive() && GetTerjeProfile() != null && GetTerjeStats() != null)
			{
				float synchInterval;
				m_terjeProfileSynchTimer = m_terjeProfileSynchTimer + deltaTime;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.CORE_PROFILE_SYNCH_INTERVAL, synchInterval) && (m_terjeProfileSynchTimer > synchInterval) && GetTerjeProfile().IsDirtySynch())
				{
					GetTerjeProfile().SynchWithClient(this, false, TerjeERPC.TerjeRPC_SYNCH_PLAYER_PROFILE);
					m_terjeProfileSynchTimer = 0;
					OnTerjeProfileChanged();
				}
				
				m_terjeStatsSynchTimer = m_terjeStatsSynchTimer + deltaTime;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.CORE_STATS_SYNCH_INTERVAL, synchInterval) && (m_terjeStatsSynchTimer > synchInterval) && GetTerjeStats().IsDirtySynch())
				{
					GetTerjeStats().SynchWithClient(this, false, TerjeERPC.TerjeRPC_SYNCH_PLAYER_STATS);
					m_terjeStatsSynchTimer = 0;
					OnTerjeStatsChanged();
				}
			}
			
			bool terjeStateMode = !GetAllowDamage();
			if (terjeStateMode != GetTerjeGodMode())
			{
				SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_GOD_MODE, terjeStateMode);
			}
			
			terjeStateMode = !PhysicsIsSolid();
			if (terjeStateMode != GetTerjeNoClipMode())
			{
				SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOCLIP, terjeStateMode);
			}
			
			terjeStateMode = GetIsSimulationDisabled();
			if (terjeStateMode != GetTerjeNoSimulateMode())
			{
				SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOSIMULATE, terjeStateMode);
			}
			
			terjeStateMode = !GetCanBeDestroyed();
			if (terjeStateMode != GetTerjeIndestructible())
			{
				SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INDESTRUCTIBLE, terjeStateMode);
			}
		}
	}
	
	override void EOnPostFrame( IEntity other, int extra )
	{
		if (GetGame() && GetGame().IsClient())
		{
			if (IsTerjeLocalControlledPlayer())
			{
				if (GetTerjeInvisibleModeLocal())
				{
					SetInvisible(true);
				}
			}
			else
			{
				if (GetTerjeInvisibleModeRemote())
				{
					SetInvisible(true);
				}
			}
		}
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);
		if (rpc_type == TerjeERPC.TerjeRPC_SYNCH_PLAYER_STATS)
		{
			if (!GetGame().IsDedicatedServer())
			{
				if (GetTerjeStats() != null && GetTerjeStats().OnStoreLoad(ctx))
				{
					OnTerjeStatsChanged();
				}
			}
		}
		else if (rpc_type == TerjeERPC.TerjeRPC_SYNCH_PLAYER_PROFILE)
		{
			if (!GetGame().IsDedicatedServer())
			{
				ref TerjePlayerProfile profile = GetTerjeProfile();
				if (profile == null)
				{
					profile = CreateTerjeProfile();
				}
				
				if (profile.OnStoreLoad(ctx))
				{
					OnTerjeProfileChanged();
				}
			}
		}
		else if (rpc_type == TerjeERPC.TerjeRPC_CUSTOM_CALL)
		{
			Param1<string> metaData;
			if (!ctx.Read(metaData))
			{
				return;
			}
			
			OnTerjeRPC(sender, metaData.param1, ctx);
		}
	}
	
	void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		if (id == "~pse")
		{
			if (!GetGame() || !GetGame().IsClient())
			{
				return;
			}
			
			Param2<string, float> soundEventParams;
			if (!ctx.Read(soundEventParams))
			{
				return;		
			}
			
			EffectSound effectTerjeSound = SEffectManager.PlaySoundOnObject(soundEventParams.param1, this);
			if (effectTerjeSound)
			{
				effectTerjeSound.SetSoundVolume(soundEventParams.param2);
				effectTerjeSound.SetSoundMaxVolume(soundEventParams.param2);
				effectTerjeSound.SetAutodestroy(true);
			}
		}
	}
	
	void TerjeRPCSingleParam(string id, Param params, bool guaranteed, PlayerIdentity recipient = NULL)
	{
		array<ref Param> sendData();
		sendData.Insert(new Param1<string>(id));
		if (params != null)
		{
			sendData.Insert(params);
		}
		
		this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, guaranteed, recipient);
	}
	
	void TerjeSendToClient(string id, PlayerIdentity recipient, Param params)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, true, recipient);
		}
	}
	
	void TerjeStreamToClient(string id, PlayerIdentity recipient, out TerjeStreamRpc stream)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			stream = new TerjeStreamRpc();
			stream.InitTerjeRpcEx(id, recipient, TerjeStreamRpc_Target.TO_CLIENT, this, (int)TerjeERPC.TerjeRPC_CUSTOM_CALL);
		}
	}
		
	void TerjeSendToServer(string id, Param params)
	{
		if (GetGame() && GetGame().IsClient())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, true, null);
		}
	}
		
	void TerjeStreamToServer(string id, out TerjeStreamRpc stream)
	{
		if (GetGame() && GetGame().IsClient())
		{
			stream = new TerjeStreamRpc();
			stream.InitTerjeRpcEx(id, null, TerjeStreamRpc_Target.TO_SERVER, this, (int)TerjeERPC.TerjeRPC_CUSTOM_CALL);
		}
	}
	
	void TerjeSendToAll(string id, Param params)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			array<ref Param> sendData();
			sendData.Insert(new Param1<string>(id));
			if (params != null)
			{
				sendData.Insert(params);
			}
			
			this.RPC(TerjeERPC.TerjeRPC_CUSTOM_CALL, sendData, true, null);
		}
	}
	
	void TerjeStreamToAll(string id, out TerjeStreamRpc stream)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			stream = new TerjeStreamRpc();
			stream.InitTerjeRpcEx(id, null, TerjeStreamRpc_Target.TO_ALL, this, (int)TerjeERPC.TerjeRPC_CUSTOM_CALL);
		}
	}
	
	void TerjeSendSoundEvent(string soundSet, string soundType, float volume)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && soundSet != "" && volume > 0)
		{
			Param2<string, float> params = new Param2<string, float>(soundSet, volume);
			TerjeRPCSingleParam("~pse", params, false);
		}
	}
	
	override void OnCommandVehicleStart()
	{
		// Hide weapon when player is inside the car (only visual change)
		super.OnCommandVehicleStart();
		TryHideEquipmentInsideCar(true);
	}
	
	override void OnCommandVehicleFinish()
	{
		// Show weapon when player get out from the car (only visual change)
		super.OnCommandVehicleFinish();
		TryHideEquipmentInsideCar(false);
	}
	
	void TryHideEquipmentInsideCar(bool state)
	{
		EntityAI weaponMelee = GetItemOnSlot("Melee");
		EntityAI weaponShoulder = GetItemOnSlot("Shoulder");
		
		if (weaponMelee)
		{
			if (state)
			{
				SetSimpleHiddenSelectionState(DayZPlayer.SIMPLE_SELECTION_MELEE_RIFLE,false);
				SetSimpleHiddenSelectionState(DayZPlayer.SIMPLE_SELECTION_MELEE_MELEE,false);
			}
			else
			{
				UpdateShoulderProxyVisibility(weaponMelee, "Melee");
			}
		}
		
		if (weaponShoulder)
		{
			if (state)
			{
				SetSimpleHiddenSelectionState(SIMPLE_SELECTION_SHOULDER_RIFLE,false);
				SetSimpleHiddenSelectionState(SIMPLE_SELECTION_SHOULDER_MELEE,false);
			}
			else
			{
				UpdateShoulderProxyVisibility(weaponShoulder, "Shoulder");
			}
		}
	}
	
	void OnTerjeCharacterLifetimeUpdated(int secondsSinceRespawn)
	{

	}
	
	void CallTerjeVomitSymptom(float duration, float drainForce)
	{
		SymptomBase symptom = GetSymptomManager().QueueUpPrimarySymptom( SymptomIDs.SYMPTOM_VOMIT );
		if( symptom )
		{
			symptom.SetDuration( duration );

			float waterDrainFromVomit = 70;
			GetTerjeSettingFloat(TerjeSettingsCollection.CORE_WATER_DRAIN_FROM_VOMIT, waterDrainFromVomit);
			
			float energyDrainFromVomit = 55;
			GetTerjeSettingFloat(TerjeSettingsCollection.CORE_ENERGY_DRAIN_FROM_VOMIT, energyDrainFromVomit);
			
			if ( GetStatWater().Get() > drainForce * waterDrainFromVomit )
			{
				GetStatWater().Add( -1.0 * drainForce * waterDrainFromVomit );
			}
			
			if ( GetStatEnergy().Get() > drainForce * energyDrainFromVomit )
			{
				GetStatEnergy().Add( -1.0 * drainForce * energyDrainFromVomit );
			}
			
			OnCallTerjeVomitSymptom(symptom, duration, drainForce);
		}
	}
	
	void OnCallTerjeVomitSymptom(SymptomBase symptom, float duration, float drainForce)
	{
	
	}
	
	override bool Consume(PlayerConsumeData data)
	{
		bool result = super.Consume(data);
		if (result)
		{
			if (data.m_Type == EConsumeType.ENVIRO_POND || data.m_Type == EConsumeType.ENVIRO_WELL || data.m_Type == EConsumeType.ENVIRO_SNOW)
			{
				TerjeConsumableEffects medEffects = new TerjeConsumableEffects();
				medEffects.Apply(null, "CfgLiquidDefinitions " + Liquid.GetLiquidClassname(LIQUID_WATER), this, data.m_Amount);
			}
			else if (data.m_Type == EConsumeType.ITEM_SINGLE_TIME || data.m_Type == EConsumeType.ITEM_CONTINUOUS)
			{
				Edible_Base edible_item = Edible_Base.Cast(data.m_Source);
				if (edible_item && edible_item.IsLiquidContainer() && edible_item.GetLiquidType() == LIQUID_TERJE_CUSTOM)
				{
					int customLiquidId = edible_item.GetTerjeLiquidType();
					if (customLiquidId > 0)
					{
						ref NutritionalProfile nutProfile = TerjeCustomLiquids.GetInstance().GetNutritionalProfileByType(customLiquidId);
						
						if (nutProfile != null)
						{
							GetStatEnergy().Add((nutProfile.GetEnergy() / 100) * data.m_Amount);
							GetStatWater().Add((nutProfile.GetWaterContent() / 100) * data.m_Amount);
							m_PlayerStomach.DigestAgents(nutProfile.GetAgents(), data.m_Amount);
						}
					}
				}
			}
		}
		
		return result;
	}
	
	override bool CanBeTargetedByAI( EntityAI ai )
	{
		if (!super.CanBeTargetedByAI( ai ))
			return false;

		if (GetTerjeNoTargetMode())
			return false;

		return true;
	}
	
	override bool EEOnDamageCalculated(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetTerjeIgnoreDamage())
		{
			return false;
		}
		
		return super.EEOnDamageCalculated(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (m_terjePlayerStatesMaskClient != m_terjePlayerStatesMask)
		{
			m_terjePlayerStatesMaskClient = m_terjePlayerStatesMask;
			OnTerjePlayerStateChanged();
		}
	}
	
	protected void SetTerjePlayerStateBit(TerjePlayerStatesMask id, bool value)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			int bitmask = m_terjePlayerStatesMask;
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, id, value);
			if (bitmask != m_terjePlayerStatesMask)
			{
				m_terjePlayerStatesMask = bitmask;
				OnTerjePlayerStateChanged();
				SetSynchDirty();
			}
		}
		else
		{
			TerjeLog_Error("PlayerBase::SetTerjePlayerStateBit function call on client is not allowed.");
		}
	}
	
	protected bool GetTerjePlayerStateBit(TerjePlayerStatesMask id)
	{
		return TerjeBitmaskHelper.GetBit(m_terjePlayerStatesMask, id);
	}
	
	protected void OnTerjePlayerStateChanged()
	{
		if (GetGame() && GetGame().IsClient())
		{
			if (IsTerjeLocalControlledPlayer())
			{
				SetInvisible(GetTerjeInvisibleModeLocal());
			}
			else
			{
				SetInvisible(GetTerjeInvisibleModeRemote());
			}
		}
	}
	
	bool GetTerjeFaceVisible()
	{
		ref ItemBase itemCheck = GetItemOnSlot("Mask");
		if (itemCheck)
		{
			return false;
		}
		
		itemCheck = GetItemOnSlot("Headgear");
		if (itemCheck)
		{
			string configPathNoMask = "CfgVehicles " + itemCheck.GetType() +  " noMask";
			if (GetTerjeGameConfig().ConfigIsExisting(configPathNoMask) && (GetTerjeGameConfig().ConfigGetInt(configPathNoMask) == 1))
			{
				return false;
			}
		}
		
		return true;
	}
	
	void SetTerjeGodMode(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_GOD_MODE, state);
			SetAllowDamage(!state);
		}
	}
	
	bool GetTerjeGodMode()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_GOD_MODE);
	}
	
	void SetTerjeInvisibleMode(bool localState, bool remoteState)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INVISIBLE_LOCAL, localState);
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INVISIBLE_REMOTE, remoteState);
		}
	}
	
	bool GetTerjeInvisibleModeLocal()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INVISIBLE_LOCAL);
	}
	
	bool GetTerjeInvisibleModeRemote()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INVISIBLE_REMOTE);
	}
	
	void SetTerjeNoClipMode(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOCLIP, state);
			PhysicsSetSolid(!state);
		}
	}
	
	bool GetTerjeNoClipMode()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOCLIP);
	}
	
	void SetTerjeNoTargetMode(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOTARGET, state);
		}
	}
	
	bool GetTerjeNoTargetMode()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOTARGET);
	}
	
	void SetTerjeFreezeMode(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_FREEZE, state);
			
			HumanInputController controller = GetInputController();
			if (controller != null)
			{
				controller.SetDisabled(state);
			}
		}
	}
	
	bool GetTerjeFreezeMode()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_FREEZE);
	}
	
	void SetTerjeNoSimulateMode(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOSIMULATE, state);
			DisableSimulation(state);
		}
	}
	
	bool GetTerjeNoSimulateMode()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOSIMULATE);
	}
	
	void SetTerjeIgnoreDamage(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_IGNORE_DAMAGE, state);
		}
	}
	
	bool GetTerjeIgnoreDamage()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_IGNORE_DAMAGE);
	}
	
	void SetTerjeDisableHeatComfort(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOHEATCOMFORT, state);
		}
	}
	
	bool GetTerjeDisableHeatComfort()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_NOHEATCOMFORT);
	}
	
	void SetTerjeIndestructible(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INDESTRUCTIBLE, state);
			SetCanBeDestroyed(!state);
		}
	}
	
	bool GetTerjeIndestructible()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_INDESTRUCTIBLE);
	}
	
	void SetTerjeMaintenanceMode(bool state)
	{
		if (GetGame() && GetGame().IsDedicatedServer())
		{
			SetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_MAINTENANCE_MODE, state);
		}
	}
	
	bool GetTerjeMaintenanceMode()
	{
		return GetTerjePlayerStateBit(TerjePlayerStatesMask.TERJE_MAINTENANCE_MODE);
	}
}
