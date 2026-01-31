enum TerjeSkillsStealthMask
{
	// DO NOT CHANGE THIS ENUM
	// ITS REPRESENT BITMASK FROM 0..31
	// THIS BITMASK IS ALREADY FULL
	TERJE_SKILLS_STEALTH_SHOES = 0,
	TERJE_SKILLS_STEALTH_WEAPON = 7,
	TERJE_SKILLS_STEALTH_CLOTHES = 14,
	TERJE_SKILLS_STEALTH_VOICE = 21,
	TERJE_SKILLS_STEALTH_FEETS = 30,
	TERJE_SKILLS_STEALTH_NINJA = 31
}

modded class PlayerBase
{
	ref array<ItemBase> m_terjeSkillsSpawnEntityOnGroundCache = null;
	private int m_terjeSkillsStealthMask = 0;
	
	override void Init()
	{
		super.Init();
		RegisterNetSyncVariableInt("m_terjeSkillsStealthMask");
	}
	
	override void OnTerjePlayerRespawned()
	{
		super.OnTerjePlayerRespawned();
		
		if (GetGame().IsDedicatedServer() && GetTerjeSettingBool(TerjeSettingsCollection.SKILLS_RESET_ALL_ON_DEATH))
		{
			if (GetTerjeSkills() != null && TerjeSettingsCollection.SKILLS_INITIAL_EXP != null)
			{
				GetTerjeSkills().ResetAll();
				foreach (string skillId, int settingId : TerjeSettingsCollection.SKILLS_INITIAL_EXP)
				{
					int initialExp = GetTerjeSettingInt(settingId);
					if (initialExp > 0)
					{
						GetTerjeSkills().AddSkillExperience(skillId, initialExp, false, false);
					}
				}
			}
		}
	}
	
	override void OnTerjeProfileFirstCreation()
	{
		super.OnTerjeProfileFirstCreation();
		
		if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null && TerjeSettingsCollection.SKILLS_INITIAL_EXP != null)
		{
			foreach (string skillId, int settingId : TerjeSettingsCollection.SKILLS_INITIAL_EXP)
			{
				int initialExp = GetTerjeSettingInt(settingId);
				if (initialExp > 0)
				{
					GetTerjeSkills().AddSkillExperience(skillId, initialExp, false, false);
				}
			}
		}
	}
	
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionTerjeMaskStash, InputActionMap);
	}
	
	override void OnTerjeRegisterModifiers(array<ref TerjePlayerModifierBase> modifiers)
	{
		super.OnTerjeRegisterModifiers(modifiers);
		modifiers.Insert(new TerjePlayerModifierSkillAthletic());
		modifiers.Insert(new TerjePlayerModifierSkillStealth());
		modifiers.Insert(new TerjePlayerModifierPerkStrongHands());
	}
	
	override EntityAI SpawnEntityOnGroundPos(string object_name, vector pos)
	{
		EntityAI result = super.SpawnEntityOnGroundPos(object_name, pos);
		if (m_terjeSkillsSpawnEntityOnGroundCache != null)
		{
			ItemBase resultItem = ItemBase.Cast(result);
			if (resultItem)
			{
				m_terjeSkillsSpawnEntityOnGroundCache.Insert(resultItem);
			}
		}
		return result;
	}
	
	override void OnTerjeRPC(PlayerIdentity sender, string id, ParamsReadContext ctx)
	{
		super.OnTerjeRPC(sender, id, ctx);
		
		if (id == TerjeSkillsConstants.TRPC_PLAYER_PERK_APPLY)
		{
			if (GetGame().IsDedicatedServer())
			{
				Param2<string, string> perkUpgradeParams;
				if (!ctx.Read(perkUpgradeParams))
				{
					return;
				}
				
				GetTerjeSkills().AddPerkLevel(perkUpgradeParams.param1, perkUpgradeParams.param2);
			}
		}
		else if (id == TerjeSkillsConstants.TRPC_PLAYER_PERKS_RESET)
		{
			if (GetGame().IsDedicatedServer())
			{
				Param1<string> perkResetParams;
				if (!ctx.Read(perkResetParams))
				{
					return;
				}
				
				GetTerjeSkills().ResetSkill(perkResetParams.param1);
			}
		}
		// New RPCs for adding and decreasing perk levels
		else if (id == TerjeSkillsConstants.TRPC_PLAYER_PERK_DEC)
		{
			if (GetGame().IsDedicatedServer())
			{
				Param2<string, string> perkDecParams;
				if (!ctx.Read(perkDecParams))
				{
					return;
				}
				
				ref TerjeSkillCfg skillCfg;

				if (!GetTerjeSkillsRegistry().FindSkill(perkDecParams.param1, skillCfg))
				{
					return;
				}

				ref TerjePerkCfg perkCfg;
				if (!skillCfg.FindPerk(perkDecParams.param2, perkCfg))
				{
					return;
				}
				int level = GetTerjeProfile().GetSkillPerk(perkDecParams.param1, perkDecParams.param2);
				if (level <= 0)
				{
					return;
				}
				else if (level > perkCfg.GetStagesCount())
				{
					return;
				}
				
				int stage = level - 1;
				int requiredPerkPoints = perkCfg.GetRequiredPerkPoints(stage);
				int newlevel = level - 1;
				int myPerkPoints = GetTerjeProfile().GetSkillPerkPoints(perkDecParams.param1);
				myPerkPoints = myPerkPoints + requiredPerkPoints;
				GetTerjeProfile().SetSkillPerkPoints(perkDecParams.param1, myPerkPoints);
				GetTerjeSkills().SetPerkLevel(perkDecParams.param1, perkDecParams.param2, newlevel);
			}
		}
	}
	
	override void OnTerjePlayerKilledEvent()
	{
		super.OnTerjePlayerKilledEvent();
		
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSkills() != null)
		{
			float experienceLosePercentage;
			ref array<ref TerjeSkillCfg> skills = new array<ref TerjeSkillCfg>;
			GetTerjeSkillsRegistry().GetSkills(skills);
			if (GetTerjeSettingBool(TerjeSettingsCollection.SKILLS_RESET_ALL_ON_DEATH))
			{
				GetTerjeSkills().ResetAll();
			}
			else if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_EXPERIENCE_LOSE_PERCENTAGE, experienceLosePercentage) && experienceLosePercentage > 0)
			{
				foreach (ref TerjeSkillCfg skill_1 : skills)
				{
					float calculatedExpLosePercentage = GetTerjeSkills().GetSkillExperience(skill_1.GetId()) * Math.Clamp(experienceLosePercentage, 0, 1);
					GetTerjeSkills().AddSkillExperience(skill_1.GetId(), -calculatedExpLosePercentage, false);
				}
			}
			else
			{
				foreach (ref TerjeSkillCfg skill_2 : skills)
				{
					GetTerjeSkills().AddSkillExperience(skill_2.GetId(), skill_2.GetExpLoseOnDeath());
				}
			}
		}
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		TerjeStrongBonesPerkEEHitByHandler(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		TerjeSurvDmgModEEHitByHandler(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		TerjeDamageHandler.GetInstance().EEHitBy(damageResult, damageType, source, this, component, dmgZone, ammo, modelPos, speedCoef);
	}
	
	override bool CanBeTargetedByAI(EntityAI ai)
	{
		bool result = super.CanBeTargetedByAI(ai);
		
		if (!result && GetGame() && GetGame().IsDedicatedServer() && IsAlive() && IsUnconscious() && !IsInVehicle() && GetTerjeSkills() != null && ai != null)
		{
			if (ai.IsZombie() || ai.IsAnimal())
			{
				if (GetTerjeSkills().IsPerkRegistered("surv", "survinst") && GetTerjeSkills().GetPerkLevel("surv", "survinst") == 0)
				{
					result = true;
				}
			}
		}
		
		return result;
	}
	
	override protected float GetWeightSpecialized(bool forceRecalc = false)
	{
		float result = super.GetWeightSpecialized(forceRecalc);	
		if (GetTerjeSkills() != null)
		{
			float weightModifier = 1.0;
			float strengthSkillModifier = 0;
			if (GetTerjeSkills().GetSkillModifierValue("strng", "maxweightmod", strengthSkillModifier))
			{
				weightModifier = weightModifier + strengthSkillModifier;
			}
			
			float strengthPerkModifier = 0;	
			if (GetTerjeSkills().GetPerkValue("strng", "hvweight", strengthPerkModifier))
			{
				weightModifier = weightModifier + strengthPerkModifier;
			}
			
			if (weightModifier > 1.0)
			{
				result = result / weightModifier;
			}
			
			float ltarmorPerkValue = 0;
			if (GetTerjeSkills().GetPerkValue("strng", "ltarmor", ltarmorPerkValue))
			{
				result = result + (TerjeCalculateVestAndHelmetWeight() * ltarmorPerkValue);
			}
		}
		
		return Math.Max(0.0, result);
	}
	
	override void OnTerjeCharacterLifetimeUpdated(int secondsSinceRespawn)
	{
		if (GetTerjeSkills() != null)
		{
			int offsetValue;
			if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_LIFETIME_OFFSET, offsetValue) && (secondsSinceRespawn % offsetValue) == 0)
			{
				float expGain;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_LIFETIME_GAIN_EXP, expGain))
				{
					GetTerjeSkills().AddSkillExperience("surv", expGain);
				}
			}
		}
	}
	
	override void TerjeSendSoundEvent(string soundSet, string soundType, float volume)
	{
		if (GetGame() && GetGame().IsDedicatedServer() && GetTerjeSkills() != null)
		{
			float perkValue;
			if (soundType == TERJE_SOUND_EVENT_TYPE_VOICE)
			{
				if (GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_VOICE, "coldbldd", perkValue))
				{
					volume *= Math.Clamp(1.0 + perkValue, 0, 1);
				}
			}
			else if (soundType == TERJE_SOUND_EVENT_TYPE_EQUIPMENT)
			{
				if (GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_CLOTHES, "fitequip", perkValue))
				{
					volume *= Math.Clamp(1.0 + perkValue, 0, 1);
				}
			}
			else if (soundType == TERJE_SOUND_EVENT_TYPE_WEAPON)
			{
				if (GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter", perkValue))
				{
					volume *= Math.Clamp(1.0 + perkValue, 0, 1);
				}
			}
			
			if (GetTerjeSkillsStealthPerkValueFromBitmask( TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_NINJA, "ninja", perkValue))
			{
				volume *= 0.5;
			}
		}
		
		super.TerjeSendSoundEvent(soundSet, soundType, volume);
	}
	
	private float TerjeCalculateVestAndHelmetWeight()
	{
		float totalWeight = 0;
		ItemBase vest = GetItemOnSlot("Vest");
		if (vest)
		{
			totalWeight += vest.GetConfigWeightModified();
		}
		
		ItemBase helmet = GetItemOnSlot("Headgear");
		if (helmet)
		{
			totalWeight += helmet.GetConfigWeightModified();
		}
		
		return totalWeight;	
	}
	
	private void TerjeStrongBonesPerkEEHitByHandler(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetGame().IsDedicatedServer() && GetAllowDamage() && GetTerjeSkills() != null && !GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
		{
			if (GetHealth("RightLeg", "Health") <= 1 || GetHealth("LeftLeg", "Health") <= 1 || GetHealth("RightFoot", "Health") <= 1 || GetHealth("LeftFoot", "Health") <= 1)
			{
				float strbonesPerkModifier;
				if (GetTerjeSkills().GetPerkValue("athlc", "strbones", strbonesPerkModifier) && Math.RandomFloat01() > Math.Clamp(1.0 + strbonesPerkModifier, 0.0, 1.0))
				{
					// Prevent bones broke
					if (GetHealth("RightLeg", "Health") <= 1)
					{
						SetHealth("RightLeg", "Health", 2);
					}
					
					if (GetHealth("LeftLeg", "Health") <= 1)
					{
						SetHealth("LeftLeg", "Health", 2);
					}
					
					if (GetHealth("RightFoot", "Health") <= 1)
					{
						SetHealth("RightFoot", "Health", 2);
					}
					
					if (GetHealth("LeftFoot", "Health") <= 1)
					{
						SetHealth("LeftFoot", "Health", 2);
					}
				}
			}
		}
	}
	
	private void TerjeSurvDmgModEEHitByHandler(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (GetGame().IsDedicatedServer() && GetAllowDamage() && damageResult != null && source != null && source.IsZombie())
		{
			float survSkillMod;
			if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null && GetTerjeSkills().GetSkillModifierValue("surv", "survzmbmod", survSkillMod))
			{
				float actualDmg = damageResult.GetDamage(dmgZone, "Health") * Math.Clamp(Math.AbsFloat(survSkillMod), 0, 1);
				if (actualDmg > 0)
				{
					AddHealth(dmgZone, "Health", actualDmg);
				}
			}
		}
	}
	
	void UpdateTerjeSkillsStealthBitmask()
	{
		if (GetGame().IsDedicatedServer() && GetTerjeSkills() != null)
		{
			int bitmask = m_terjeSkillsStealthMask;
			bool setShadowtrc = GetTerjeSkills().GetPerkLevel("stlth", "shadowtrc") > 0;
			bool setNinja = GetGame().GetWorld().IsNight() && (GetTerjeSkills().GetPerkLevel("stlth", "ninja") > 0);

			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_SHOES, "qtstep");
			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_WEAPON, "qshooter");
			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_VOICE, "coldbldd");
			bitmask = UpdateTerjeSkillsStealthBitmask_Perk(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_CLOTHES, "fitequip");
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_FEETS, setShadowtrc);
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_NINJA, setNinja);

			if (m_terjeSkillsStealthMask != bitmask)
			{
				m_terjeSkillsStealthMask = bitmask;
				SetSynchDirty();
			}
		}
	}
	
	bool GetTerjeSkillsStealthPerkValueFromBitmask(int bitIndex, string perkId, out float result)
	{
		ref TerjeSkillCfg skill;
		if (!GetTerjeSkillsRegistry().FindSkill("stlth", skill))
		{
			result = 0.0;
			return false;
		}
		
		ref TerjePerkCfg perk;
		if (!skill.FindPerk(perkId, perk))
		{
			result = 0.0;
			return false;
		}
		
		if (bitIndex == TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_FEETS || bitIndex == TerjeSkillsStealthMask.TERJE_SKILLS_STEALTH_NINJA)
		{
			result = perk.GetValue(0);
			return TerjeBitmaskHelper.GetBit(m_terjeSkillsStealthMask, bitIndex);
		}
		else
		{
			for (int index = 0; index < 7; index++)
			{
				bool bitValue = TerjeBitmaskHelper.GetBit(m_terjeSkillsStealthMask, bitIndex + index);
				if (bitValue && index < perk.GetStagesCount())
				{
					result = perk.GetValue(index);
					return true;
				}
			}
		}
		
		result = 0.0;
		return false;
	}
	
	private int UpdateTerjeSkillsStealthBitmask_Perk(int bitmask, int offset, string perkId)
	{
		int perkLevel = 0;
		if (GetTerjeSkills() != null)
		{
			perkLevel = GetTerjeSkills().GetPerkLevel("stlth", perkId);
		}
		
		for (int index = 0; index < 7; index++)
		{
			bool bitValue = (perkLevel == (index + 1));
			bitmask = TerjeBitmaskHelper.SetBit(bitmask, offset + index, bitValue);
		}
		
		return bitmask;
	}
}
