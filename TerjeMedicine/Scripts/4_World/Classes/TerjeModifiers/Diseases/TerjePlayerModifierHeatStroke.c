class TerjePlayerModifierHeatStroke : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_HEATSTROKE_ENABLED) == false)
		{
			player.GetTerjeStats().SetHeatStrokeValue(0);
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
		
		float heatstrokeIncPerSec = 0;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_INC_PER_SEC, heatstrokeIncPerSec);
		
		float heatstrokeTemperatureDropModifier = 0;
		float heatstrokeValue = player.GetTerjeStats().GetHeatStrokeValue();
		int heatstrokeIntOrig = (int)heatstrokeValue;
		
		float perkHeatresMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkHeatres;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "heatres", perkHeatres))
			{
				perkHeatresMod -= Math.Clamp(perkHeatres, 0, 1);
			}
		}
		
		float immunityMod = Math.Clamp(1.0 - GetPlayerImmunity(player), 0, 1);
		if (heatstrokeValue > 1)
		{
			float currHeatComf = player.GetStatHeatComfort().Get();
			if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_EMPTY)
			{
				if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_TEMPERATURE_EMPTY_MODIFIER, heatstrokeTemperatureDropModifier) && heatstrokeTemperatureDropModifier > 0)
				{
					heatstrokeValue += (heatstrokeIncPerSec * immunityMod * perkHeatresMod * deltaTime * heatstrokeTemperatureDropModifier);
				}
			}
			else if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_CRITICAL)
			{
				if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_TEMPERATURE_CRIT_MODIFIER, heatstrokeTemperatureDropModifier) && heatstrokeTemperatureDropModifier > 0)
				{
					heatstrokeValue += (heatstrokeIncPerSec * immunityMod * perkHeatresMod * deltaTime * heatstrokeTemperatureDropModifier);
				}
			}
			else if (currHeatComf < PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
			{
				if (GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_TEMPERATURE_WARN_MODIFIER, heatstrokeTemperatureDropModifier) && heatstrokeTemperatureDropModifier > 0)
				{
					heatstrokeValue += (heatstrokeIncPerSec * immunityMod * perkHeatresMod * deltaTime * heatstrokeTemperatureDropModifier);
				}
			}
		}
		
		int heatstrokeVanillaAgents = player.GetSingleAgentCount(eAgents.HEATSTROKE);
		if (heatstrokeVanillaAgents > 0)
		{
			if (heatstrokeValue > 1)
			{
				float heatstrokeTransferAgentsModifier = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_TRANSFER_AGENTS_MODIFIER, heatstrokeTransferAgentsModifier);
				heatstrokeValue += (heatstrokeTransferAgentsModifier * immunityMod * perkHeatresMod * (float)heatstrokeVanillaAgents);
			}
			
			player.RemoveAgent(eAgents.HEATSTROKE);
		}
		
		if (heatstrokeValue > 0)
		{
			float heatstrokeDecPerSec = 1;
			float heatstrokeImmunityHealThreshold = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_DEC_PER_SEC, heatstrokeDecPerSec);
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_IMMUNITY_HEAL_THRESHOLD, heatstrokeImmunityHealThreshold);

			if (player.GetTerjeSkills())
			{
				float perkFtwarmMod;
				if (player.GetTerjeSkills().GetPerkValue("immunity", "ftwarm", perkFtwarmMod))
				{
					heatstrokeImmunityHealThreshold *= 1.0 + perkFtwarmMod;
					heatstrokeDecPerSec *= 1.0 + perkFtwarmMod;
				}
			}
			
			if (player.GetHeatBufferStage() > 0 && heatstrokeValue < heatstrokeImmunityHealThreshold)
			{
				float heatstrokeDefaultImmunityStrength = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_DEFAULT_IMMUNITY_STRENGTH, heatstrokeDefaultImmunityStrength);
				heatstrokeValue -= (heatstrokeDefaultImmunityStrength * heatstrokeDecPerSec * deltaTime);
			}
			else if (heatstrokeValue > GetHeatStrokeVirusAutoReproductionThreshold(player))
			{
				if (heatstrokeValue > 1)
				{
					heatstrokeValue += (heatstrokeIncPerSec * immunityMod * perkHeatresMod * deltaTime);
				}
			}
			
			int heatstrokeLevel = (int)heatstrokeValue;
			if (antibioticLevel > 0 && antibioticLevel >= heatstrokeLevel)
			{
				float antibioticStrength = (antibioticLevel - heatstrokeLevel) + 1;
				heatstrokeValue -= (antibioticStrength * heatstrokeDecPerSec * deltaTime);	
			}
			
			player.GetTerjeStats().SetHeatStrokeValue(heatstrokeValue);
			
			if (heatstrokeLevel == 1)
			{
				float heatstrokeLightSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_LIGHT_SYMPTOM_CHANCE, heatstrokeLightSymptomChance);
				if (Math.RandomFloat01() < heatstrokeLightSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_FEVERBLUR);
				}
			}
			else if (heatstrokeLevel == 2)
			{
				float heatstrokeHeavySymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_HEAVY_SYMPTOM_CHANCE, heatstrokeHeavySymptomChance);
				if (Math.RandomFloat01() < heatstrokeHeavySymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_VOMIT);
				}
			}
			else if (heatstrokeLevel >= 3)
			{
				float heatstrokeCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_CRITICAL_DMG_MULTIPLIER, heatstrokeCriticalDmgMultiplier);
				float dmgForce = (heatstrokeValue - 3.0) * heatstrokeCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.HEATSTROKE, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				float heatstrokeCriticalSymptomChance = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEATSTROKE_CRITICAL_SYMPTOM_CHANCE, heatstrokeCriticalSymptomChance);
				if (Math.RandomFloat01() < heatstrokeCriticalSymptomChance * deltaTime)
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_FAINT);
				}
			}
			
			if (heatstrokeIntOrig > 0 && heatstrokeValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_HEATSTROKE_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
	}
	
	float GetHeatStrokeVirusAutoReproductionThreshold(PlayerBase player)
	{
		return 0.5;
	}
}
