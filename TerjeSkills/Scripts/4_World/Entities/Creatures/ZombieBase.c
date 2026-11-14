modded class ZombieBase
{
	private bool m_terjeHasReceivedDamage = false;
	
	bool HasTerjeReceivedDamage()
	{
		return m_terjeHasReceivedDamage;
	}
	
	override bool FightLogic(int pCurrentCommandID, DayZInfectedInputController pInputController, float pDt)
	{
		if (pCurrentCommandID == DayZInfectedConstants.COMMANDID_ATTACK && m_ActualAttackType != null && m_ActualTarget != null)
		{
			PlayerBase playerTarget = PlayerBase.Cast(m_ActualTarget);
			if (playerTarget && playerTarget.GetMeleeFightLogic())
			{
				int blockResponse = playerTarget.GetMeleeFightLogic().TerjeSkills_BlockAttackExtended();
				if (blockResponse == 2)
				{
					// Change heavy attack to light
					m_ActualAttackType.m_IsHeavy = 0;
				}
				else if (blockResponse == 0)
				{
					// Escalate light attack to heavy
					m_ActualAttackType.m_IsHeavy = 1;
				}
			}
		}
		
		return super.FightLogic(pCurrentCommandID, pInputController, pDt);
	}
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		m_terjeHasReceivedDamage = true;
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		TerjeDamageHandler.GetInstance().EEHitBy(damageResult, damageType, source, this, component, dmgZone, ammo, modelPos, speedCoef);
	}
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
		EntityAI killerEntity = EntityAI.Cast(killer);
		if (killerEntity)
		{
			PlayerBase killerPlayer = PlayerBase.Cast(killerEntity);
			if (!killerPlayer)
			{
				killerPlayer = PlayerBase.Cast(killerEntity.GetHierarchyRootPlayer());
			}
			
			if (killerPlayer && killerPlayer.GetTerjeSkills())
			{
				int expGainSurv = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_KILL_ZOMBIE_GAIN_EXP, expGainSurv))
				{
					killerPlayer.GetTerjeSkills().AddSkillExperience("surv", expGainSurv);
				}
				
				// Used for STALKER mods compatibility only (Some monsters are zombies)
				int expGainHunt = GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + GetType() + " terjeOnKillHuntingExp");
				if (expGainHunt > 0)
				{
					float settingModifier = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_KILL_ANIMAL_EXP_GAIN_MODIFIER);
					if (settingModifier > 0)
					{
						killerPlayer.GetTerjeSkills().AddSkillExperience("hunt", (int)(settingModifier * expGainHunt));
					}
				}
			}
		}
	}
}
