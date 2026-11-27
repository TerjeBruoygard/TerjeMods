class TerjePlayerModifierRabies : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		int antibioticLevel = 0;
		float antibioticTime = 0;
		if (player.GetTerjeStats().GetRabiesCure(antibioticLevel, antibioticTime))
		{
			if (antibioticTime > 0)
			{
				player.GetTerjeStats().SetRabiesCure(antibioticLevel, antibioticTime - deltaTime);
			}
			else if (antibioticLevel > 0)
			{
				player.GetTerjeStats().SetRabiesCure(0, 0);
			}
		}
		
		float vacineTime = player.GetTerjeStats().GetRabiesVacineValue();
		if (vacineTime > 0)
		{
			player.GetTerjeStats().SetRabiesVacineValue(vacineTime - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_RABIES_ENABLED) == false)
		{
			player.GetTerjeStats().SetRabiesValue(0);
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
		
		float rabiesValue = player.GetTerjeStats().GetRabiesValue();
		int rabiesIntOrig = (int)rabiesValue;
		
		float vacineModifier = 1.0;
		if (vacineTime > 1)
		{
			vacineModifier = 0.5;
		}
		
		float perkRabResistMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkRabResist;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "rabres", perkRabResist))
			{
				perkRabResistMod -= Math.Clamp(perkRabResist, 0, 1);
			}
		}
		
		if (rabiesValue > 0)
		{
			if (rabiesValue > 0.1)
			{
				float rabiesIncPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_INC_PER_SEC);
				float immunityMod = Math.Clamp(1.0 - GetPlayerImmunity(player), 0.2, 1.0);
				rabiesValue += (rabiesIncPerSec * vacineModifier * immunityMod * perkRabResistMod * deltaTime);
			}
			
			int rabiesLevel = (int)rabiesValue;
			if (antibioticLevel > 0 && antibioticLevel >= rabiesLevel)
			{
				float rabiesDecPerSec = 0;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_DEC_PER_SEC, rabiesDecPerSec);
				float antibioticStrength = (antibioticLevel - rabiesLevel) + 1;
				rabiesValue -= (antibioticStrength * rabiesDecPerSec * deltaTime);	
			}
			
			if (rabiesValue < 1.0 && vacineTime > 1)
			{
				rabiesValue = 0;
			}
			
			player.GetTerjeStats().SetRabiesValue(rabiesValue);
			
			if (rabiesLevel >= 1)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_LIGHT_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HOT);
				}
			}
			
			if (rabiesLevel >= 2)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_HEAVY_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_HAND_SHIVER);
				}
			}
			
			if (rabiesLevel >= 3)
			{
				float rabiesCriticalDmgMultiplier = 1;
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_CRITICAL_DMG_MULTIPLIER, rabiesCriticalDmgMultiplier);
				float dmgForce = (rabiesValue - 3.0) * rabiesCriticalDmgMultiplier;
				DecreasePlayerHealth(player, TerjeDamageSource.RABIES, dmgForce * deltaTime);
				
				if (!player || !player.IsAlive() || player.GetTerjeStats() == null)
				{
					return;
				}
				
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_RABIES_CRITICAL_SYMPTOM_CHANCE) * deltaTime))
				{
					player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_GASP);
				}
			}
			
			if (rabiesIntOrig > 0 && rabiesValue < 1 && m_immunityInterval <= 0)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_RABIES_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
					m_immunityInterval = 1200;
				}
			}
		}
	}
}
