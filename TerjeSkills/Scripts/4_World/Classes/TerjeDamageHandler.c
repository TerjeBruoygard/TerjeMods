class TerjeDamageHandler
{
	private static ref TerjeDamageHandler m_Instance = null;
	static ref TerjeDamageHandler GetInstance()
	{
		if (m_Instance == null)
		{
			m_Instance = new TerjeDamageHandler;
		}
		
		return m_Instance;
	}
	
	bool IsStrengthExperienceRequired(string ammo, string ammoType)
	{
		if (ammo.IndexOf("FlashLight") == 0)
		{
			return false; // Compatibility
		}
		
		if (GetTerjeGameConfig().ConfigGetBool( "CfgAmmo " + ammo + " terjeIgnoreExpStrength" ))
		{
			return false;
		}
		
		return true;
	}
	
	void TerjeCommitAdditionalPerkDamage(EntityAI source, EntityAI target, string dmgZone, string ammoName, vector modelPos, float damageCoef, int delay)
	{
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(target.ProcessDirectDamage, delay, false, 0, source, dmgZone, ammoName, modelPos, damageCoef, 0);
	}
	
	void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, EntityAI target, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if (ammo.IndexOf("Dummy_") == 0)
		{
			return;
		}
		
		if (g_Game.IsDedicatedServer() && target.IsAlive() && target.GetAllowDamage() && source != null && damageResult != null)
		{
			PlayerBase sourcePlayer = PlayerBase.Cast(source.GetHierarchyRootPlayer());
			if (sourcePlayer && sourcePlayer.GetTerjeSkills())
			{
				string ammoType = GetTerjeGameConfig().ConfigGetTextOut( "CfgAmmo " + ammo + " DamageApplied " + "type" );
				if (ammoType == "Melee")
				{
					float additionalDmg = damageResult.GetDamage(dmgZone, "Health");
					if ( ammo.Contains("Heavy") )
					{
						float hattkforcePerkValue;
						if (sourcePlayer.GetTerjeSkills().GetPerkValue("strng", "hattkforce", hattkforcePerkValue))
						{
							TerjeCommitAdditionalPerkDamage(source, target, dmgZone, "Dummy_TerjeStrengthHeavy", modelPos, additionalDmg * hattkforcePerkValue, 100);
						}
						
						EEHitBy_MasterStrikePerk(damageResult, damageType, sourcePlayer, target, component, dmgZone, ammo, modelPos, speedCoef);
						
						if (IsStrengthExperienceRequired(ammo, ammoType))
						{
							if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STRENGTH_MELEE_HEAVY_GAIN_CHANCE)))
							{
								int strengthMeleeHeavyGainExp;
								if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STRENGTH_MELEE_HEAVY_GAIN_EXP, strengthMeleeHeavyGainExp))
								{
									sourcePlayer.GetTerjeSkills().AddSkillExperience("strng", strengthMeleeHeavyGainExp);
								}
							}
						}
					}
					else
					{
						float lattkforcePerkValue;
						if (sourcePlayer.GetTerjeSkills().GetPerkValue("strng", "lattkforce", lattkforcePerkValue))
						{
							TerjeCommitAdditionalPerkDamage(source, target, dmgZone, "Dummy_TerjeStrengthLight", modelPos, additionalDmg * lattkforcePerkValue, 100);
						}
						
						if (IsStrengthExperienceRequired(ammo, ammoType))
						{
							if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_STRENGTH_MELEE_LIGHT_GAIN_CHANCE)))
							{
								int strengthMeleeLightGainExp;
								if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_STRENGTH_MELEE_LIGHT_GAIN_EXP, strengthMeleeLightGainExp))
								{
									sourcePlayer.GetTerjeSkills().AddSkillExperience("strng", strengthMeleeLightGainExp);
								}
							}
						}
					}
				}
			}
		}
	}
	
	void EEHitBy_MasterStrikePerk(TotalDamageResult damageResult, int damageType, PlayerBase sourcePlayer, EntityAI target, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		if ((dmgZone == "Head") && (sourcePlayer.GetTerjeSkills() != null) && (sourcePlayer.GetTerjeSkills().GetPerkLevel("strng", "mrstroke") > 0))
		{
			if (target.IsMan())
			{
				TerjeCommitAdditionalPerkDamage(sourcePlayer, target, dmgZone, "Dummy_TerjeStrengthMStroke", modelPos, 1.0, 200);
			}
			else if (target.IsAnimal() || target.IsZombie())
			{
				TerjeCommitAdditionalPerkDamage(sourcePlayer, target, dmgZone, "Dummy_TerjeStrengthMStrokeAlt", modelPos, 1.0, 200);
			}
		}
	}
}
