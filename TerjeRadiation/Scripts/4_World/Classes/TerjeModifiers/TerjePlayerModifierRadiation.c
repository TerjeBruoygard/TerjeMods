class TerjePlayerModifierRadiation : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		int antiradLevel = 0;
		float antiradTime = 0;
		if (player.GetTerjeStats().GetAntirad(antiradLevel, antiradTime))
		{
			if (antiradTime > 0)
			{
				player.GetTerjeStats().SetAntirad(antiradLevel, antiradTime - deltaTime);
			}
			else if (antiradLevel > 0)
			{
				player.GetTerjeStats().SetAntirad(0, 0);
			}
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval -= deltaTime;
		}
		
		float radiationValue = player.GetTerjeStats().GetRadiationValue();
		float radiationAccumulator = player.GetTerjeStats().GetRadiationAccumulated();
		if (radiationAccumulator > 0)
		{
			if (antiradLevel > 0)
			{
				float bufferMedDecPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_MEDS_DEC_PER_SEC) * antiradLevel * deltaTime;
				if (bufferMedDecPerSec > 0)
				{
					radiationAccumulator -= bufferMedDecPerSec;
				}
			}
			else
			{
				float bufferCommonDecPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_COMMON_DEC_PER_SEC) * deltaTime;
				if (bufferCommonDecPerSec > 0)
				{
					radiationAccumulator -= bufferCommonDecPerSec;
				}
			}
			
			if (radiationAccumulator > GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_CRITICAL_DISEASE_THRESHOLD))
			{
				radiationValue += GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_CRITICAL_DISEASE_INCREMENT) * deltaTime;
			}
			else if (radiationAccumulator > GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_HEAVY_DISEASE_THRESHOLD))
			{
				if (radiationValue < 2.5)
				{
					radiationValue += GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_HEAVY_DISEASE_INCREMENT) * deltaTime;
				}
			}
			else if (radiationAccumulator > GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_LIGHT_DISEASE_THRESHOLD))
			{
				if (radiationValue < 1.5)
				{
					radiationValue += GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_BUFFER_LIGHT_DISEASE_INCREMENT) * deltaTime;
				}
			}

			player.GetTerjeStats().SetRadiationAccumulated(radiationAccumulator);
		}
		
		if (radiationValue > 0)
		{
			float immunityMod = 1.0;
			float perkRadgenMod = 1.0;
			if (player.GetTerjeSkills())
			{
				float resdiseasesmod;
				if (player.GetTerjeSkills().GetSkillModifierValue("immunity", "resdiseasesmod", resdiseasesmod))
				{
					immunityMod += resdiseasesmod;
				}
				float radregen;
				if (player.GetTerjeSkills().GetPerkValue("immunity", "radregen", radregen))
				{
					perkRadgenMod += radregen;
				}
			}
			
			int radiationLevel = (int)radiationValue;
			float radiationDecPerSec = 0;
			if (antiradLevel > 0)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_MEDS_DEC_PER_SEC, radiationDecPerSec);
				radiationDecPerSec *= antiradLevel - radiationLevel + 1;
			}
			else
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_COMMON_DEC_PER_SEC, radiationDecPerSec);	
			}
			
			radiationValue -= (radiationDecPerSec * immunityMod * perkRadgenMod * deltaTime);
			player.GetTerjeStats().SetRadiationValue(radiationValue);
			
			if (radiationValue > 1)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_LIGHT_SYMPTOM_CHANCE) * deltaTime))
				{
					float radiationVomitForceModifier = 1;
					GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_VOMIT_FORCE_MODIFIER, radiationVomitForceModifier);					
					player.CallTerjeVomitSymptom(Math.RandomIntInclusive(3, 5), radiationVomitForceModifier);
				}
			}
			
			if (radiationValue > 2)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_HEAVY_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
					player.GetBleedingManagerServer().AttemptAddBleedingSource( Math.RandomIntInclusive(0, 5) );
				}
				
				float radiationCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.RADIATION_CRITICAL_DMG_MULTIPLIER, radiationCriticalDmgMultiplier);
				float dmgForce = (radiationValue - 2.0) * radiationCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.RADIATION, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
			}
			
			if (radiationLevel > 0 && radiationValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.RADIATION_IMMUNITY_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
		
		player.UpdateTerjeRadiationAccumulated();
	}
}
