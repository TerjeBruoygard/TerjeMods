enum TerjeMedicineWoundsMask
{
	TERJE_MED_WOUNDS_MASK_STUB = 0,
	TERJE_MED_WOUNDS_MASK_BULLET,
	TERJE_MED_WOUNDS_MASK_VISCERA,
	TERJE_MED_WOUNDS_MASK_SUTURE,
	TERJE_MED_WOUNDS_MASK_SUTURE_DIRTY,
	TERJE_MED_WOUNDS_MASK_DIRTYBANDAGE,
	TERJE_MED_WOUNDS_MASK_STUB_SURGERY
}

modded class PlayerBase
{
	private int m_terjeMedWoundsMask = 0;
	private static const int TERJE_KILLFIX_RECENT_PVP_WINDOW_DEFAULT_MS = 180000;
	private string m_terjeKillFixLastAggressorId = "";
	private string m_terjeKillFixLastAggressorName = "";
	private string m_terjeKillFixLastAmmo = "";
	private string m_terjeKillFixLastZone = "";
	private vector m_terjeKillFixLastHitPosition = vector.Zero;
	private int m_terjeKillFixLastHitTime = -1;

	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("m_terjeMedWoundsMask");
	}
	
	override void OnTerjeRegisterModifiers(array<ref TerjePlayerModifierBase> modifiers)
	{
		super.OnTerjeRegisterModifiers(modifiers);
		
		modifiers.Insert(new TerjePlayerModifierPsionicScriptableAreas());
		modifiers.Insert(new TerjePlayerModifierSleeping());
		modifiers.Insert(new TerjePlayerModifierMind());
		modifiers.Insert(new TerjePlayerModifierPain());
		modifiers.Insert(new TerjePlayerModifierSepsis());
		modifiers.Insert(new TerjePlayerModifierZVirus());
		modifiers.Insert(new TerjePlayerModifierPoison());
		modifiers.Insert(new TerjePlayerModifierInfluenza());
		modifiers.Insert(new TerjePlayerModifierOverdose());
		modifiers.Insert(new TerjePlayerModifierContusion());
		modifiers.Insert(new TerjePlayerModifierHemostatic());
		modifiers.Insert(new TerjePlayerModifierBloodRegen());
		modifiers.Insert(new TerjePlayerModifierHematomas());
		modifiers.Insert(new TerjePlayerModifierAdrenalin());
		modifiers.Insert(new TerjePlayerModifierDisinfected());
		modifiers.Insert(new TerjePlayerModifierComa());
		modifiers.Insert(new TerjePlayerModifierWounds());
		modifiers.Insert(new TerjePlayerModifierBiohazard());
		modifiers.Insert(new TerjePlayerModifierRabies());
		modifiers.Insert(new TerjePlayerModifierImmunity());
		modifiers.Insert(new TerjePlayerModifierHealthGain());
	}
	
	override bool HasTerjeHealings()
	{
		if (super.HasTerjeHealings())
		{
			return true;
		}
		else if (GetTerjeStats().GetAntipoisonLevel() || GetTerjeStats().GetSalve() || GetTerjeStats().GetHealthExtraRegen())
		{
			return true;
		}
		else if (GetTerjeStats().GetPainkillerLevel() || GetTerjeStats().GetHemostatic() || GetTerjeStats().GetBloodRegen())
		{
			return true;
		}
		else if (GetTerjeStats().GetAntidepresantLevel() || GetTerjeStats().GetAntibioticLevel() || GetTerjeStats().GetAntisepsis())
		{
			return true;
		}
		else if (GetTerjeStats().GetZAntidot() || GetTerjeStats().GetAdrenalin() || GetTerjeStats().GetContusionHeal())
		{
			return true;
		}
		else if (GetTerjeStats().GetAntibiohazardLevel() || GetTerjeStats().GetInfluenzaVacine() || GetTerjeStats().GetZVirusVacine())
		{
			return true;
		}
		else if (GetTerjeStats().GetRabiesVacine() || GetTerjeStats().GetRabiesCureLevel() || GetTerjeStats().GetImmunityGain())
		{
			return true;
		}
		
		return false;
	}
	
	override bool HasTerjeDisease()
	{
		if (super.HasTerjeDisease())
		{
			return true;
		}
		else if (GetTerjeStats().GetZVirusLevel() || GetTerjeStats().GetSepsisLevel() || GetTerjeStats().GetRabiesLevel())
		{
			return true;
		}
		else if (GetTerjeStats().GetInfluenzaLevel() || GetTerjeStats().GetPoisonLevel() || GetTerjeStats().GetBiohazardLevel())
		{
			return true;
		}
		
		return false;
	}
	
	override bool IsBleeding()
	{
		return super.IsBleeding() || HasTerjeStubWounds() || HasTerjeSutures();
	}
	
	override float GetHealthRegenSpeed()
	{
		float healthRegenCommonModifier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEALTH_REGEN_COMMON_MODIFIER);
		if (HasTerjeSicknesOrInjures())
		{
			healthRegenCommonModifier = 0; // Do not heal when heavy injured
		}
		else
		{
			float perkQhealingMod;
			if (GetTerjeSkills() && GetTerjeSkills().GetPerkValue("immunity", "qhealing", perkQhealingMod))
			{
				healthRegenCommonModifier *= (1.0 + perkQhealingMod);
			}
		}
		
		return super.GetHealthRegenSpeed() * healthRegenCommonModifier;
	}
	
	bool HasTerjeBleedingSelf()
	{
		return super.IsBleeding() || HasTerjeStubWoundsSelf() || HasTerjeSuturesSelf();
	}
	
	bool HasTerjeDirtyBandages()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_DIRTYBANDAGE);
	}
	
	bool HasTerjeDirtyBandagesSelf()
	{
		return (GetTerjeStats().GetBandagesDirty() > 0) || (GetTerjeStats().GetSuturesBandagedDirty() > 0);
	}
	
	bool HasTerjeSutures()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE);
	}
	
	bool HasTerjeSuturesSelf()
	{
		return GetTerjeStats().GetSuturesTotal() > 0;
	}
	
	bool HasTerjeSuturesDirty()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE_DIRTY);
	}
	
	bool HasTerjeSuturesDirtySelf()
	{
		return GetTerjeStats().GetSuturesDirty() > 0;
	}
	
	bool HasTerjeStubWounds()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB);
	}
	
	bool HasTerjeStubWoundsSelf()
	{
		return GetTerjeStats().GetStubWounds() > 0;
	}
	
	bool HasTerjeBulletWounds()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_BULLET);
	}
	
	bool HasTerjeBulletWoundsSelf()
	{
		return GetTerjeStats().GetBulletWounds() > 0;
	}
	
	bool HasTerjeViscera()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_VISCERA);
	}
	
	bool HasTerjeVisceraSelf()
	{
		return GetTerjeStats().GetViscera();
	}
	
	bool HasTerjeStubReadyToSurgery()
	{
		return TerjeBitmaskHelper.GetBit(m_terjeMedWoundsMask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB_SURGERY);
	}
	
	bool HasTerjeStubReadyToSurgerySelf()
	{
		return (GetTerjeStats().GetBandagesTotal() > 0) || (GetTerjeStats().GetStubWounds() > 0);
	}
	
	override bool HasTerjeSicknesOrInjures()
	{
		if (super.HasTerjeSicknesOrInjures())
		{
			return true;
		}
		
		if (GetTerjeStats() != null)
		{
			if (GetTerjeStats().GetHematomasCount() >= TerjeMedicineConstants.HEMATOMAS_BAD_COUNT) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetBulletWounds() > 3) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetStubWounds() > 3) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetViscera()) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetPainLevel() > 1) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetSepsisLevel() > 1) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetZVirusLevel() > 1) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetInfluenzaLevel() > 2) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetOverdoseLevel() > 2) 
			{
				return true;
			}
			
			if (GetTerjeStats().GetMindLevel() > 3) 
			{
				return true;
			}
		}
		
		return false;
	}
	
	bool IsStayingInBlock()
	{
		if (m_MeleeFightLogic)
		{
			return m_MeleeFightLogic.IsInBlock();
		}
		
		return false;
	}
	
	bool IsFaceBlocked(bool mouthOnly)
	{
		ref ItemBase itemCheck = GetItemOnSlot("Mask");
		if (itemCheck)
		{
			if (mouthOnly)
			{
				bool skipMaskCondition = false;
				string itemMaskType = itemCheck.GetType();
				if (itemMaskType.IndexOf("Balaclava3Holes_") == 0)
				{
					skipMaskCondition = true;
				}
				
				if (!skipMaskCondition)
				{
					return true;
				}
			}
			else
			{
				return true;
			}
		}
		
		itemCheck = GetItemOnSlot("Headgear");
		if (itemCheck)
		{
			string configPathNoMask = "CfgVehicles " + itemCheck.GetType() +  " noMask";
			if (GetTerjeGameConfig().ConfigIsExisting(configPathNoMask))
			{
				if (GetTerjeGameConfig().ConfigGetInt(configPathNoMask) == 1)
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	void UpdateTerjeWoundsBitmask()
	{
		if (g_Game.IsDedicatedServer())
		{
			int bitmask = m_terjeMedWoundsMask;
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB, HasTerjeStubWoundsSelf());
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_BULLET, HasTerjeBulletWoundsSelf());
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_VISCERA, HasTerjeVisceraSelf());
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE, HasTerjeSuturesSelf());
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_SUTURE_DIRTY, HasTerjeSuturesDirtySelf());
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_DIRTYBANDAGE, HasTerjeDirtyBandagesSelf());
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeMedicineWoundsMask.TERJE_MED_WOUNDS_MASK_STUB_SURGERY, HasTerjeStubReadyToSurgerySelf());
			
			if (m_terjeMedWoundsMask != bitmask)
			{
				m_terjeMedWoundsMask = bitmask;
				SetSynchDirty();
			}
		}
	}
	
	override void OnCallTerjeVomitSymptom(SymptomBase symptom, float duration, float drainForce)
	{
		super.OnCallTerjeVomitSymptom(symptom, duration, drainForce);
		
		if (g_Game && g_Game.IsDedicatedServer() && GetTerjeStats())
		{
			float poisonValue = GetTerjeStats().GetPoisonValue();
			if (poisonValue > 2)
			{
				float poisonDecrement = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_VOMIT_AGENTS_LOSE);
				GetTerjeStats().SetPoisonValue(GetTerjeStats().GetPoisonValue() - (poisonDecrement * drainForce));
			}
		}
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (g_Game && g_Game.IsServer())
		{
			TerjeKillFixRememberAggressor(source, dmgZone, ammo, modelPos);
		}

		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
	}

	override void EEKilled(Object killer)
	{
		TerjeKillFixLogDeferredPvPDeath(killer);
		super.EEKilled(killer);
		
		EntityAI entityKiller = EntityAI.Cast(killer);
		if (entityKiller)
		{
			PlayerBase killerPlayer = PlayerBase.Cast(entityKiller.GetHierarchyRootPlayer());
			if (killerPlayer && killerPlayer.GetTerjeStats() != null)
			{
				float safeDist;
				float mindDegValue;
				float mindDegTime;
				if (this.GetIdentity())
				{
					safeDist = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PLAYER_KILLING_MIND_DEG_SAFEDIST);
					mindDegValue = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PLAYER_KILLING_MIND_DEG_VALUE);
					mindDegTime = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PLAYER_KILLING_MIND_DEG_TIME);
				}
				else
				{
					safeDist = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_AI_KILLING_MIND_DEG_SAFEDIST);
					mindDegValue = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_AI_KILLING_MIND_DEG_VALUE);
					mindDegTime = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_AI_KILLING_MIND_DEG_TIME);
				}
				
				if (vector.Distance(killerPlayer.GetWorldPosition(), this.GetWorldPosition()) < safeDist)
				{
					killerPlayer.GetTerjeStats().AddMindDegradation(mindDegValue, mindDegTime);
				}
			}
		}

		TerjeKillFixClearAggressor();
	}

	private bool TerjeKillFixIsEnabled()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_LOG_EXTEND_ENABLED);
	}

	private int TerjeKillFixGetRecentPvpWindowMs()
	{
		int value = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_LOG_EXTEND_RECENT_PVP_WINDOW_MS);
		if (value <= 0)
		{
			return TERJE_KILLFIX_RECENT_PVP_WINDOW_DEFAULT_MS;
		}

		return value;
	}
	
	private bool TerjeKillFixIsEnabled()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_LOG_EXTEND_ENABLED);
	}

	private int TerjeKillFixGetRecentPvpWindowMs()
	{
		int value = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_LOG_EXTEND_RECENT_PVP_WINDOW_MS);
		if (value <= 0)
		{
			return TERJE_KILLFIX_RECENT_PVP_WINDOW_DEFAULT_MS;
		}

		return value;
	}

	private bool TerjeKillFixShouldLogPositions()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_LOG_EXTEND_LOG_POSITIONS);
	}

	private bool TerjeKillFixRequireDeferredState()
	{
		return GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_LOG_EXTEND_REQUIRE_DEFERRED_STATE);
	}

	private vector TerjeKillFixResolveHitPosition(vector modelPos)
	{
		if ((modelPos[0] != 0) || (modelPos[1] != 0) || (modelPos[2] != 0))
		{
			return ModelToWorld(modelPos);
		}

		return GetWorldPosition();
	}

	private string TerjeKillFixVectorToString(vector value)
	{
		return value[0].ToString() + " " + value[1].ToString() + " " + value[2].ToString();
	}

	private void TerjeKillFixRememberAggressor(EntityAI source, string dmgZone, string ammo, vector modelPos)
	{
		if (!TerjeKillFixIsEnabled())
		{
			return;
		}

		if (!source)
		{
			TerjeKillFixClearAggressor();
			return;
		}

		PlayerBase aggressorPlayer = PlayerBase.Cast(source.GetHierarchyRootPlayer());
		if (!aggressorPlayer || aggressorPlayer == this)
		{
			TerjeKillFixClearAggressor();
			return;
		}

		PlayerIdentity aggressorIdentity = aggressorPlayer.GetIdentity();
		if (!aggressorIdentity)
		{
			TerjeKillFixClearAggressor();
			return;
		}

		m_terjeKillFixLastAggressorId = aggressorIdentity.GetId();
		m_terjeKillFixLastAggressorName = aggressorIdentity.GetName();
		m_terjeKillFixLastAmmo = ammo;
		m_terjeKillFixLastZone = dmgZone;
		m_terjeKillFixLastHitPosition = TerjeKillFixResolveHitPosition(modelPos);
		m_terjeKillFixLastHitTime = g_Game.GetTime();
	}

	private void TerjeKillFixClearAggressor()
	{
		m_terjeKillFixLastAggressorId = "";
		m_terjeKillFixLastAggressorName = "";
		m_terjeKillFixLastAmmo = "";
		m_terjeKillFixLastZone = "";
		m_terjeKillFixLastHitPosition = vector.Zero;
		m_terjeKillFixLastHitTime = -1;
	}

	private bool TerjeKillFixHasDamageOverTime(int healthSettingId, int bloodSettingId)
	{
		float healthLose = 0;
		float bloodLose = 0;
		GetTerjeSettingFloat(healthSettingId, healthLose);
		GetTerjeSettingFloat(bloodSettingId, bloodLose);
		return (healthLose > 0) || (bloodLose > 0);
	}

	private bool TerjeKillFixHasEnabledDamageOverTime(int enabledSettingId, int healthSettingId, int bloodSettingId)
	{
		return GetTerjeSettingBool(enabledSettingId) && TerjeKillFixHasDamageOverTime(healthSettingId, bloodSettingId);
	}

	private bool TerjeKillFixHasDeferredDamageState()
	{
		if (!GetTerjeStats())
		{
			return false;
		}

		if (GetTerjeStats().IsInKnockout() && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_MEDICAL_COMA) && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_KNOCKOUT_TO_COMA))
		{
			return true;
		}

		if ((GetTerjeStats().GetBulletWounds() > 0) && TerjeKillFixHasEnabledDamageOverTime(TerjeSettingsCollection.MEDICINE_BULLETS_ENABLED, TerjeSettingsCollection.MEDICINE_BULLETS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_BULLETS_BLOOD_LOSE))
		{
			return true;
		}

		if ((GetTerjeStats().GetStubWounds() > 0) && TerjeKillFixHasEnabledDamageOverTime(TerjeSettingsCollection.MEDICINE_STUBS_ENABLED, TerjeSettingsCollection.MEDICINE_STUBS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_STUBS_BLOOD_LOSE))
		{
			return true;
		}

		if (GetTerjeStats().GetViscera() && TerjeKillFixHasEnabledDamageOverTime(TerjeSettingsCollection.MEDICINE_VISCERA_ENABLED, TerjeSettingsCollection.MEDICINE_VISCERA_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_VISCERA_BLOOD_LOSE))
		{
			return true;
		}

		if ((GetTerjeStats().GetBandagesClean() > 0) && TerjeKillFixHasDamageOverTime(TerjeSettingsCollection.MEDICINE_CLEAN_BANDAGED_WOUNDS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_CLEAN_BANDAGED_WOUNDS_BLOOD_LOSE))
		{
			return true;
		}

		if ((GetTerjeStats().GetBandagesDirty() > 0) && TerjeKillFixHasDamageOverTime(TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGED_WOUNDS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_DIRTY_BANDAGED_WOUNDS_BLOOD_LOSE))
		{
			return true;
		}

		if ((GetTerjeStats().GetSuturesClean() > 0) && TerjeKillFixHasDamageOverTime(TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_WOUNDS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_WOUNDS_BLOOD_LOSE))
		{
			return true;
		}

		if (HasTerjeSuturesDirtySelf() && TerjeKillFixHasDamageOverTime(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_WOUNDS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_WOUNDS_BLOOD_LOSE))
		{
			return true;
		}

		if ((GetTerjeStats().GetSuturesBandagedClean() > 0) && TerjeKillFixHasDamageOverTime(TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_BANDAGED_WOUNDS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_CLEAN_SUTURE_BANDAGED_WOUNDS_BLOOD_LOSE))
		{
			return true;
		}

		if ((GetTerjeStats().GetSuturesBandagedDirty() > 0) && TerjeKillFixHasDamageOverTime(TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_WOUNDS_HEALTH_LOSE, TerjeSettingsCollection.MEDICINE_DIRTY_SUTURE_BANDAGED_WOUNDS_BLOOD_LOSE))
		{
			return true;
		}

		return false;
	}

	private void TerjeKillFixLogDeferredPvPDeath(Object killer)
	{
		if (!g_Game || !g_Game.IsServer())
		{
			return;
		}

		if (!TerjeKillFixIsEnabled())
		{
			return;
		}

		if (m_terjeKillFixLastHitTime < 0 || m_terjeKillFixLastAggressorId == "")
		{
			return;
		}

		if (TerjeKillFixRequireDeferredState() && !TerjeKillFixHasDeferredDamageState())
		{
			return;
		}

		PlayerBase resolvedKiller;
		EntityAI entityKiller = EntityAI.Cast(killer);
		if (entityKiller)
		{
			resolvedKiller = PlayerBase.Cast(entityKiller.GetHierarchyRootPlayer());
		}

		if (resolvedKiller && resolvedKiller != this)
		{
			return;
		}

		if (killer && !resolvedKiller && killer != this)
		{
			return;
		}

		int delayMs = g_Game.GetTime() - m_terjeKillFixLastHitTime;
		if (delayMs < 0 || delayMs > TerjeKillFixGetRecentPvpWindowMs())
		{
			return;
		}

		string victimName = GetType();
		string victimId = "offline";
		if (GetIdentity())
		{
			victimName = GetIdentity().GetName();
			victimId = GetIdentity().GetId();
		}

		string originalKillerType = "null";
		if (killer)
		{
			originalKillerType = killer.GetType();
		}

		string hitPositionStr = "disabled";
		string deathPositionStr = "disabled";
		if (TerjeKillFixShouldLogPositions())
		{
			vector deathPosition = GetWorldPosition();
			hitPositionStr = TerjeKillFixVectorToString(m_terjeKillFixLastHitPosition);
			deathPositionStr = TerjeKillFixVectorToString(deathPosition);
		}

		PrintFormat("[TerjeKillFix] deferred_pvp_death victim=%1 victim_id=%2 killer=%3 killer_id=%4 ammo=%5 zone=%6 delay_ms=%7 last_hit_pos=%8 death_pos=%9 original_killer=%10",
			victimName,
			victimId,
			m_terjeKillFixLastAggressorName,
			m_terjeKillFixLastAggressorId,
			m_terjeKillFixLastAmmo,
			m_terjeKillFixLastZone,
			delayMs,
			hitPositionStr,
			deathPositionStr,
			originalKillerType);
	}

	override void SetActionsRemoteTarget(out TInputActionMap InputActionMap)
	{
		AddAction(ActionStethoscopeInspect, InputActionMap);
		AddAction(ActionTerjeBodyDrag, InputActionMap);
		super.SetActionsRemoteTarget(InputActionMap);
	}
	
	override bool Consume(ItemBase source, float amount, EConsumeType consume_type)
	{
		if (super.Consume(source, amount, consume_type))
		{
			if (g_Game && g_Game.IsDedicatedServer() && HasBloodyHands() && !GetItemOnSlot("Gloves"))
			{
				if (Math.RandomFloat01() < GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_DIRTY_HANDS_CONSUME_CHANCE))
				{
					InsertAgent(eAgents.FOOD_POISON, amount * GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_DIRTY_HANDS_CONSUME_AMOUNT));
				}
			}
			
			return true;
		}
		
		return false;
	}
	
	override void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		super.OnTerjeRPC(sender, id, ctx);

		if (id == "tm.mind.weaponfire")
		{
			if (g_Game.IsDedicatedServer())
			{
				Weapon_Base weapon;
				if (Weapon_Base.CastTo(weapon, GetItemInHands()))
				{
					if (!weapon.IsJammed() && !weapon.IsDamageDestroyed() && weapon.CanFire())
					{
						weapon.ProcessWeaponEvent(new WeaponEventTrigger);
					}
				}
			}
			return;
		}
		else if (id == "tm.body.drag")
		{
			Param2<vector, vector> dragPayload;
			if (!ctx.Read(dragPayload))
				return;
			
			g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.OnTerjeBodyDragProgress);
			OnTerjeBodyDragProgress(dragPayload.param1, dragPayload.param2, g_Game.GetTime());
		}
	}
	
	void OnTerjeBodyDragProgress(vector from, vector to, int startTime)
	{
		if (GetTerjeMaintenanceMode())
		{
			return;
		}
		
		if (!IsAlive())
		{
			ResetDeathCooldown();
			DisableSimulation(false);
		}
		
		if (g_Game)
		{
			if (g_Game.IsDedicatedServer())
			{
				SetPosition(to);
			}
			else
			{
				float progress = ((float)(g_Game.GetTime() - startTime)) * 0.002;
				SetPosition(vector.Lerp(from, to, Math.Clamp(progress, 0, 1)));
				if (progress < 1.0)
				{
					g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.OnTerjeBodyDragProgress, 15, false, from, to, startTime);
				}
			}
		}
	}
}
