class TerjePlayerModifierPoison : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	private float m_firstSymptomTime = 0;
	private int m_lastPoisonLevel = -1;
	
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		int antipoisonLevel = 0;
		float antipoisonTime = 0;
		if (player.GetTerjeStats().GetAntipoison(antipoisonLevel, antipoisonTime))
		{
			if (antipoisonTime > 0)
			{
				player.GetTerjeStats().SetAntipoison(antipoisonLevel, antipoisonTime - deltaTime);
			}
			else if (antipoisonLevel > 0)
			{
				player.GetTerjeStats().SetAntipoison(0, 0);
			}
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_POSION_ENABLED) == false)
		{
			player.GetTerjeStats().SetPoisonValue(0);
			return;
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval -= deltaTime;
		}
		
		if (m_firstSymptomTime > 0)
		{
			m_firstSymptomTime += deltaTime;
		}
		
		float perkPoisonresMod = 1.0;
		float perkSvdinnerMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkPoisonres;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "poisonres", perkPoisonres))
			{
				perkPoisonresMod += perkPoisonres;
			}
			float perkSvdinner;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "svdinner", perkSvdinner))
			{
				perkSvdinnerMod += perkSvdinner;
				perkSvdinnerMod = Math.Clamp(perkSvdinnerMod, 0, 1);
			}
		}
		
		float poisonValue = player.GetTerjeStats().GetPoisonValue();
		int poisonIntOrig = (int)poisonValue;
		
		float immunityMod = Math.Clamp(1.0 - GetPlayerImmunity(player), 0.2, 1.0);
		if (poisonValue < 2.5)
		{
			poisonValue += (immunityMod * perkSvdinnerMod * this.TransferVanillaAgents(player, eAgents.FOOD_POISON, TerjeSettingsCollection.MEDICINE_POISON_TRANSFER_FOOD_POISON_AGENTS_MODIFIER));
		}
		
		if (poisonValue < 3.5)
		{
			poisonValue += (immunityMod * this.TransferVanillaAgents(player, eAgents.SALMONELLA, TerjeSettingsCollection.MEDICINE_POISON_TRANSFER_SALMONELLA_MODIFIER));
			poisonValue += (immunityMod * this.TransferVanillaAgents(player, eAgents.CHOLERA, TerjeSettingsCollection.MEDICINE_POISON_TRANSFER_CHOLERA_MODIFIER));
			poisonValue += (immunityMod * this.TransferVanillaAgents(player, eAgents.HEAVYMETAL, TerjeSettingsCollection.MEDICINE_POISON_TRANSFER_HEAVYMETAL_MODIFIER));
		}
		
		int poisonLevel = (int)poisonValue;
		if (m_lastPoisonLevel == 0 && poisonLevel > 0)
		{
			m_firstSymptomTime = deltaTime;
		}
		
		m_lastPoisonLevel = poisonLevel;
		
		if (poisonValue > 0)
		{
			float poisonDecPerSec = 0;
			float poisonVomitForceModifier = 1.0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_DEC_PER_SEC, poisonDecPerSec);	
			poisonValue -= (poisonDecPerSec * perkPoisonresMod * deltaTime);

			if (antipoisonLevel >= poisonLevel)
			{
				float poisonAntidoteHealMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_ANTIDOTE_HEAL_MULTIPLIER, poisonAntidoteHealMultiplier);
				
				float antipoisonStrength = (antipoisonLevel - poisonLevel) + 1;
				poisonValue -= (antipoisonStrength * poisonDecPerSec * perkPoisonresMod * poisonAntidoteHealMultiplier * deltaTime);	
			}
			
			player.GetTerjeStats().SetPoisonValue(poisonValue);
			
			if (poisonLevel == 1)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_LIGHT_SYMPTOM_CHANCE) * deltaTime) || m_firstSymptomTime > 5)
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_VOMIT_FORCE_MODIFIER, poisonVomitForceModifier);
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(3, 5), poisonVomitForceModifier * 0.5);
					m_firstSymptomTime = 0;
				}
			}
			else if (poisonLevel == 2)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_HEAVY_SYMPTOM_CHANCE) * deltaTime) || m_firstSymptomTime > 3)
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_VOMIT_FORCE_MODIFIER, poisonVomitForceModifier);
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(4, 8), poisonVomitForceModifier * 1.0);
					m_firstSymptomTime = 0;
				}
			}
			else if (poisonLevel >= 3)
			{
				float poisonCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_CRITICAL_DMG_MULTIPLIER, poisonCriticalDmgMultiplier);
				float dmgForce = (poisonValue - 3.0) * poisonCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.POISON, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_CRITICAL_SYMPTOM_CHANCE) * deltaTime) || m_firstSymptomTime > 1)
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_POISON_VOMIT_FORCE_MODIFIER, poisonVomitForceModifier);
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(5, 10), poisonVomitForceModifier * 2.5);
					m_firstSymptomTime = 0;
				}
			}
			
			if (poisonIntOrig > 0 && poisonValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_POISON_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
	}
	
	float TransferVanillaAgents(PlayerBase player, eAgents agent, int terjeSetting)
	{
		int poisonVanillaAgents = player.GetSingleAgentCount(agent);
		if (poisonVanillaAgents > 0)
		{
			player.RemoveAgent(agent);
			
			float poisonTransferAgentsModifier = 0;
			if (GetTerjeSettingFloat(terjeSetting, poisonTransferAgentsModifier))
			{
				return Math.Clamp(poisonTransferAgentsModifier * (float)poisonVanillaAgents, 0.0, poisonTransferAgentsModifier * 3);
			}
		}
		return 0;
	}
}
