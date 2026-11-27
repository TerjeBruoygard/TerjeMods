class TerjePlayerModifierContusion : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float healValue = player.GetTerjeStats().GetContusionHealValue();
		if (healValue > 0)
		{
			player.GetTerjeStats().SetContusionHealValue(healValue - deltaTime);
		}
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_CONTUSION_ENABLED) == false)
		{
			player.GetTerjeStats().SetContusionValue(0);
			return;
		}
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		float contusionValue = player.GetTerjeStats().GetContusionValue();
		if (contusionValue > 0)
		{
			int contusionIntOrig = (int)contusionValue;
			float contusionHealModifier = 1;
			float contusionDecPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CONTUSION_DEC_PER_SEC, contusionDecPerSec);	

			if (healValue > 0)
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CONTUSION_HEAL_MODIFIER, contusionHealModifier);
			}
			
			contusionValue -= (contusionDecPerSec * contusionHealModifier * deltaTime);
			player.GetTerjeStats().SetContusionValue(contusionValue);
			
			if (contusionValue > 1)
			{
				if (GetPlayerShock(player) > PlayerConstants.UNCONSCIOUS_THRESHOLD + 25)
				{
					DecreasePlayerShock(player, TerjeDamageSource.CONTUSION, 20);
				}
			}
			
			if (contusionValue > 2)
			{
				if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_CONTUSION_UNCONSCIOUS_CHANCE)))
				{
					SetPlayerShock(player, TerjeDamageSource.CONTUSION, 0);
				}
			}
			
			if (contusionIntOrig > 0 && contusionValue < 1)
			{
				float immunityExpGain = 0;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_CONTUSION_EXP_GAIN, immunityExpGain);
				if (immunityExpGain > 0 && player.GetTerjeSkills())
				{
					player.GetTerjeSkills().AddSkillExperience("immunity", immunityExpGain);
				}
			}
		}
	}
}
