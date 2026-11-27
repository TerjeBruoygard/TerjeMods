class TerjePlayerModifierPain : TerjePlayerModifierBase
{
	private float m_immunityInterval = 0;
	
	override float GetTimeout()
	{
		return 0.3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_PAIN_ENABLED) == false)
		{
			player.GetTerjeStats().SetPainValue(0);
			player.GetTerjeStats().SetPainLevel(0);
			player.GetTerjeStats().SetPainkiller(0, 0);
			return;
		}
		
		eBrokenLegs currentBrokenLegs = player.GetBrokenLegs();
		float painValue = player.GetTerjeStats().GetPainValue();
		if (painValue < 3.1 && player.GetTerjeStats().GetViscera())
		{
			painValue = 3.2;
		}
		else if (painValue < 2.1 && ((currentBrokenLegs == eBrokenLegs.BROKEN_LEGS) || (player.GetTerjeStats().GetStubWounds() > 0) || (player.GetTerjeStats().GetBulletWounds() > 0) || (player.GetTerjeStats().GetBandagesClean() > 0) || (player.GetTerjeStats().GetBandagesDirty() > 0)))
		{
			painValue = 2.2;
		}
		else if (painValue < 1.1 && ((currentBrokenLegs == eBrokenLegs.BROKEN_LEGS_SPLINT) || (player.GetTerjeStats().GetHematomasCount() >= TerjeMedicineConstants.HEMATOMAS_PAIN_COUNT) || (player.GetTerjeStats().GetSuturesClean() > 0) || (player.GetTerjeStats().GetSuturesDirty() > 0)))
		{
			painValue = 1.2;
		}
		
		int painkillerLevel = 0;
		float painkillerTime = 0;
		if (player.GetTerjeStats().GetPainkiller(painkillerLevel, painkillerTime))
		{
			if (painkillerTime > 0)
			{
				player.GetTerjeStats().SetPainkiller(painkillerLevel, painkillerTime - deltaTime);
			}
			else if (painkillerLevel > 0)
			{
				player.GetTerjeStats().SetPainkiller(0, 0);
			}
			
			if (painkillerLevel > 0)
			{
				if (!player.GetModifiersManager().IsModifierActive(eModifiers.MDF_PAINKILLERS))
				{
					player.GetModifiersManager().ActivateModifier( eModifiers.MDF_PAINKILLERS );
				}
				
				if (painkillerLevel >= 3 && !player.GetModifiersManager().IsModifierActive(eModifiers.MDF_MORPHINE))
				{
					player.GetModifiersManager().ActivateModifier( eModifiers.MDF_MORPHINE );
				}
			}
			else
			{
				if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_PAINKILLERS))
				{
					player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_PAINKILLERS );
				}
				
				if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_MORPHINE))
				{
					player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_MORPHINE );
				}
			}
		}
		
		if (m_immunityInterval > 0)
		{
			m_immunityInterval -= deltaTime;
		}
		
		float painSymtomChance = 0;
		int painLevel = (int)Math.Clamp(painValue, 0, 3);
		if (player.GetTerjeSkills())
		{
			if (painLevel > 0 && player.GetTerjeSkills().GetPerkLevel("immunity", "lowpain") > 0)
			{
				painLevel -= 1;
			}
		}
		
		float painDecLevelValue = 0;
		if (painLevel == 0)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL0, painDecLevelValue);
		}
		else if (painLevel == 1)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL1, painDecLevelValue);
		}
		else if (painLevel == 2)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL2, painDecLevelValue);
		}
		else if (painLevel == 3)
		{
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_DEC_LEVEL3, painDecLevelValue);
		}
		
		float immunityMod = 1.0 + GetPlayerImmunity(player);
		float newPainValue = painValue - (painDecLevelValue * immunityMod * deltaTime);
		player.GetTerjeStats().SetPainValue(newPainValue);
		player.GetTerjeStats().SetPainLevel(painLevel);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (painkillerLevel >= painLevel)
		{
			painLevel = 0;
		}
		
		if (painLevel == 2)
		{
			if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_LIGHT_SYMPTOM_CHANCE) * deltaTime))
			{
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_LIGHT);
			}
		}
		else if (painLevel == 3)
		{
			if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_HEAVY_SYMPTOM_CHANCE) * deltaTime))
			{
				player.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			}
		}
		
		if (!player.IsUnconscious())
		{
			int currentShock = player.GetHealth("","Shock");
			if (painLevel == 3 && currentShock > PlayerConstants.UNCONSCIOUS_THRESHOLD + GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_LEVEL3_MAX_SHOCK))
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_LEVEL3_UNCOUNCION_CHANCE) * deltaTime))
				{
					SetPlayerShock(player, TerjeDamageSource.PAIN, 10);
				}
				else
				{
					DecreasePlayerShock(player, TerjeDamageSource.PAIN, 5);
				}
			}
			else if ((player.GetTerjeStats().GetContusion() || painLevel == 2) && currentShock > PlayerConstants.UNCONSCIOUS_THRESHOLD + GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_PAIN_LEVEL2_MAX_SHOCK))
			{
				DecreasePlayerShock(player, TerjeDamageSource.PAIN, 5);
			}
		}
		
		if (newPainValue < 1 && painValue >= 1 && m_immunityInterval <= 0)
		{
			float immunityExpGain = 0;
			GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_PAIN_EXP_GAIN, immunityExpGain);
			if (immunityExpGain > 0 && player.GetTerjeSkills())
			{
				player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
				m_immunityInterval = 300;
			}
		}
	}
}
