class TerjePlayerModifierSepsis : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 0.5;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float antisepsisTime = player.GetTerjeStats().GetAntisepsisValue();
		if (antisepsisTime > 0)
		{	
			player.GetTerjeStats().SetAntisepsisValue(antisepsisTime - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SEPSIS_ENABLED) == false)
		{
			player.GetTerjeStats().SetSepsisValue(0);
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

		float sepsisValue = player.GetTerjeStats().GetSepsisValue();
		if (sepsisValue > 0)
		{
			int sepsisIntOrig = (int)sepsisValue;
			float immunityMod = Math.Clamp(1.0 - GetPlayerImmunity(player), 0.2, 1.0);
			float sepsisIncPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_INC_PER_SEC);	
			sepsisValue += (sepsisIncPerSec * immunityMod * deltaTime);
			
			if (antisepsisTime > 0)
			{
				float sepsisDecPerSec = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_DEC_PER_SEC, sepsisDecPerSec);
				sepsisValue -= (sepsisDecPerSec * deltaTime);	
			}
			
			player.GetTerjeStats().SetSepsisValue(sepsisValue);
			
			if (sepsisValue > 1)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_LIGHT_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
				}
			}
			
			if (sepsisValue > 2)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_HEAVY_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HOT);
				}
			}
			
			if (sepsisValue > 3)
			{
				float sepsisCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_CRITICAL_DMG_MULTIPLIER, sepsisCriticalDmgMultiplier);
				float dmgForce = (sepsisValue - 3.0) * sepsisCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.SEPSIS, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SEPSIS_CRITICAL_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
				}
			}
			
			if (sepsisIntOrig > 0 && sepsisValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_SEPSIS_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 900;
				}
			}
		}
	}
}
