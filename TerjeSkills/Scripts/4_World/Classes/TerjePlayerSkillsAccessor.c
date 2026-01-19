modded class TerjePlayerSkillsAccessor
{
	override int GetSkillLevel(string skillId)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return 0;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return 0;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return 0;
		}
		
		int exp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		return skillCfg.GetLevelFromExp(exp);
	}
	
	override int GetSkillExperience(string skillId)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return 0;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return 0;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return 0;
		}
		
		return m_Player.GetTerjeProfile().GetSkillExperience(skillId);
	}
	
	override void SetSkillLevel(string skillId, int level, bool showNotification = true)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		if (level < 0)
		{
			level = 0;
		}
		else if (level > skillCfg.GetMaxLevel())
		{
			level = skillCfg.GetMaxLevel();
		}
		
		int newExp = skillCfg.GetExpForLevel(level);
		int curExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		if (newExp > curExp)
		{
			AddSkillExperience(skillId, newExp - curExp, false, showNotification);
		}
		else
		{
			m_Player.GetTerjeProfile().SetSkillExperience(skillId, 0);
			m_Player.GetTerjeProfile().SetSkillHighRangeLevel(skillId, 0);
			m_Player.GetTerjeProfile().SetSkillPerkPoints(skillId, 0);
			ResetAllSkillPerks(skillId);
			AddSkillExperience(skillId, newExp, false, showNotification);
		}
	}
	
	override void AddSkillExperience(string skillId, int value, bool affectModifiers = true, bool showNotification = true)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		int curExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		if (affectModifiers)
		{
			if (value > 0)
			{
				float gainModifier;
				PluginTerjeScriptableAreas plugin = GetTerjeScriptableAreas();
				if (plugin && plugin.TryCalculateTerjeEffectValue(m_Player, "exp", skillId, gainModifier))
				{
					value = (int)(value * gainModifier);
				}
				else if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_EXPERIENCE_GAIN_MODIFIER, gainModifier))
				{
					value = (int)(value * gainModifier);
				}
			}
			else if (value < 0)
			{
				float loseModifier;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_EXPERIENCE_LOSE_MODIFIER, loseModifier))
				{
					value = (int)(value * loseModifier);
				}
			}
		}
		
		int	newExp = curExp + value;
		
		if ((value > 0) && TerjeWorldHelper.IsOutOfMap(m_Player))
		{
			return;
		}
		
		if (value > 0)
		{
			// Add perk points on level-up
			int curLevel = skillCfg.GetLevelFromExp(curExp);
			int newLevel = skillCfg.GetLevelFromExp(newExp);
			if (newLevel > curLevel)
			{
				if (m_Player.GetTerjeProfile().GetSkillHighRangeLevel(skillId) < newLevel)
				{
					int perkPoints = m_Player.GetTerjeProfile().GetSkillPerkPoints(skillId);
					int perkPointsPerLevel = skillCfg.GetPerkPointsPerLevel();
					int perkPointsNew = perkPoints + ((newLevel - curLevel) * perkPointsPerLevel);
					m_Player.GetTerjeProfile().SetSkillPerkPoints(skillId, perkPointsNew);
					m_Player.GetTerjeProfile().SetSkillHighRangeLevel(skillId, newLevel);
					
					if (showNotification && m_Player.GetIdentity())
					{
						string notificationMessage = "#STR_TERJESKILL_NEWLEVEL_MSG1 " + skillCfg.GetDisplayName() + " #STR_TERJESKILL_NEWLEVEL_MSG2 " + newLevel + "<br/>#STR_TERJESKILL_NEWLEVEL_MSG3";
						NotificationSystem.SendNotificationToPlayerIdentityExtended(m_Player.GetIdentity(), 8, skillCfg.GetDisplayName(), notificationMessage, skillCfg.GetIcon());
					}
				}
			}
		}
		
		m_Player.GetTerjeProfile().SetSkillExperience(skillId, newExp);
	}
	
	override int GetSkillPerkPoints(string skillId)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return 0;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return 0;
		}
			
		return m_Player.GetTerjeProfile().GetSkillPerkPoints(skillId);
	}
	
	override void ResetAll()
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		array<ref TerjeSkillCfg> skillsCfg();
		GetTerjeSkillsRegistry().GetSkills(skillsCfg);
		foreach (ref TerjeSkillCfg skillCfg : skillsCfg)
		{
			if (skillCfg != null)
			{
				string skillId = skillCfg.GetId();
				m_Player.GetTerjeProfile().SetSkillExperience(skillId, 0);
				m_Player.GetTerjeProfile().SetSkillHighRangeLevel(skillId, 0);
				m_Player.GetTerjeProfile().SetSkillPerkPoints(skillId, 0);
				m_Player.GetTerjeProfile().ResetKnownSkillBooks(skillId);
				ResetAllSkillPerks(skillId);
			}
		}
	}
	
	override void ResetAllSkillPerks(string skillId)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		ref array<ref TerjePerkCfg> perksCfg = new array<ref TerjePerkCfg>;
		skillCfg.GetPerks(perksCfg);
		foreach (ref TerjePerkCfg perkCfg : perksCfg)
		{
			m_Player.GetTerjeProfile().SetSkillPerk(skillId, perkCfg.GetId(), 0);
		}
	}
	
	override void ResetSkill(string skillId)
	{
		float experienceLoseOnResetPerks;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_EXPERIENCE_LOSE_ON_RESET_PERKS, experienceLoseOnResetPerks))
		{
			return;
		}
		
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		int curExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		if (curExp <= 0)
		{
			return;
		}
		
		int newExp = (int)(curExp * experienceLoseOnResetPerks);
		if (newExp < 0)
		{
			newExp = 0;
		}
		
		if (newExp > curExp)
		{
			newExp = curExp;
		}
		
		m_Player.GetTerjeProfile().SetSkillExperience(skillId, 0);
		m_Player.GetTerjeProfile().SetSkillHighRangeLevel(skillId, 0);
		m_Player.GetTerjeProfile().SetSkillPerkPoints(skillId, 0);
		ResetAllSkillPerks(skillId);
		AddSkillExperience(skillId, newExp, false);
	}
	
	override void SetPerkLevel(string skillId, string perkId, int level)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		ref TerjePerkCfg perkCfg;
		if (!skillCfg.FindPerk(perkId, perkCfg))
		{
			return;
		}
		
		if (level < 0)
		{
			level = 0;
		}
		else if (level > perkCfg.GetStagesCount())
		{
			level = perkCfg.GetStagesCount();
		}
		
		m_Player.GetTerjeProfile().SetSkillPerk(skillId, perkId, level);
	}
	
	override void AddPerkLevel(string skillId, string perkId)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		ref TerjePerkCfg perkCfg;
		if (!skillCfg.FindPerk(perkId, perkCfg))
		{
			return;
		}
		
		int level = m_Player.GetTerjeProfile().GetSkillPerk(skillId, perkId) + 1;
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
		if (requiredPerkPoints < 0)
		{
			return;
		}
		
		int skillPerkPoints = m_Player.GetTerjeProfile().GetSkillPerkPoints(skillId);
		if (requiredPerkPoints > skillPerkPoints)
		{
			return;
		}
		
		skillPerkPoints = skillPerkPoints - requiredPerkPoints;
		m_Player.GetTerjeProfile().SetSkillPerkPoints(skillId, skillPerkPoints);
		m_Player.GetTerjeProfile().SetSkillPerk(skillId, perkId, level);
	}
	
	override int GetPerkLevel(string skillId, string perkId)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return 0;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return 0;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return 0;
		}
		
		ref TerjePerkCfg perkCfg;
		if (!skillCfg.FindPerk(perkId, perkCfg))
		{
			return 0;
		}
		
		int perkLevel = m_Player.GetTerjeProfile().GetSkillPerk(skillId, perkId);
		if (perkLevel < 0)
		{
			perkLevel = 0;
		}
		else if (perkLevel > perkCfg.GetStagesCount())
		{
			perkLevel = perkCfg.GetStagesCount();
		}
		
		int currentSkillExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		int currentSkillLevel = skillCfg.GetLevelFromExp(currentSkillExp);
		for (int i = perkLevel; i > 0; i--)
		{
			int requiredSkillLevel = perkCfg.GetRequiredSkillLevel(i - 1);
			if (currentSkillLevel >= requiredSkillLevel)
			{
				return i;
			}
		}
		
		return 0;
	}
	
	override bool GetPerkValue(string skillId, string perkId, out float result)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			result = 0;
			return false;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return false;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			result = 0;
			return false;
		}
		
		ref TerjePerkCfg perkCfg;
		if (!skillCfg.FindPerk(perkId, perkCfg))
		{
			result = 0;
			return false;
		}
		
		int perkLevel = m_Player.GetTerjeProfile().GetSkillPerk(skillId, perkId);
		if (perkLevel < 0)
		{
			perkLevel = 0;
		}
		else if (perkLevel > perkCfg.GetStagesCount())
		{
			perkLevel = perkCfg.GetStagesCount();
		}
		
		if (perkLevel == 0)
		{
			result = 0;
			return false;
		}
		
		int currentSkillExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		int currentSkillLevel = skillCfg.GetLevelFromExp(currentSkillExp);
		for (int i = perkLevel; i > 0; i--)
		{
			int requiredSkillLevel = perkCfg.GetRequiredSkillLevel(i - 1);
			if (currentSkillLevel >= requiredSkillLevel)
			{
				result = perkCfg.GetValue(i - 1);
				return true;
			}
		}
		
		result = 0;
		return false;
	}
	
	override void GetPerkStatus(string skillId, string perkId, out int perkLevel, out int activePerkLevel, out bool canBeUpgraded)
	{
		perkLevel = 0;
		activePerkLevel = 0;
		canBeUpgraded = false;
		
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			return;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return;
		}
		
		ref TerjePerkCfg perkCfg;
		if (!skillCfg.FindPerk(perkId, perkCfg))
		{
			return;
		}
		
		int currentSkillExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		int currentSkillLevel = skillCfg.GetLevelFromExp(currentSkillExp);
		perkLevel = m_Player.GetTerjeProfile().GetSkillPerk(skillId, perkId);
		
		for (int i = perkLevel; i > 0; i--)
		{
			int requiredSkillLevel = perkCfg.GetRequiredSkillLevel(i - 1);
			if (currentSkillLevel >= requiredSkillLevel)
			{
				activePerkLevel = i;
				break;
			}
		}
		
		if (perkLevel >= 0 && perkLevel < perkCfg.GetStagesCount())
		{
			int requiredPerkPoints = perkCfg.GetRequiredPerkPoints(perkLevel);
			int requiredSkillLevel2 = perkCfg.GetRequiredSkillLevel(perkLevel);
			int skillPerkPoints = m_Player.GetTerjeProfile().GetSkillPerkPoints(skillId);
			if (requiredPerkPoints >= 0 && requiredPerkPoints <= skillPerkPoints && currentSkillLevel >= requiredSkillLevel2)
			{
				canBeUpgraded = true;
			}
		}
	}
	
	override bool GetSkillModifierValue(string skillId, string modifierId, out float result)
	{
		if (!m_Player || !m_Player.GetTerjeProfile())
		{
			result = 0;
			return false;
		}
		
		if (!GetGame().IsDedicatedServer() && !m_Player.IsTerjeLocalControlledPlayer())
		{
			return false;
		}
		
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			result = 0;
			return false;
		}
		
		ref TerjeSkillModifierCfg modifierCfg;
		if (!skillCfg.FindModifier(modifierId, modifierCfg))
		{
			result = 0;
			return false;
		}
		
		int skillExp = m_Player.GetTerjeProfile().GetSkillExperience(skillId);
		int skillLevel = skillCfg.GetLevelFromExp(skillExp);	
		result = modifierCfg.GetValue() * (float)skillLevel;
		return true;
	}
	
	override bool IsPerkRegistered(string skillId, string perkId)
	{
		ref TerjeSkillCfg skillCfg;
		if (!GetTerjeSkillsRegistry().FindSkill(skillId, skillCfg))
		{
			return false;
		}
		
		ref TerjePerkCfg perkCfg;
		if (!skillCfg.FindPerk(perkId, perkCfg))
		{
			return false;
		}
		
		return true;
	}
}
