class TerjePlayerModifierOverdose : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 0.5;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_OVERDOSE_ENABLED) == false)
		{
			return;
		}
		
		float overdoseValue = player.GetTerjeStats().GetOverdoseValue();
		if (overdoseValue > 0)
		{
			float perkIntoxicresMod = 1.0;
			if (player.GetTerjeSkills())
			{
				float perkIntoxicres;
				if (player.GetTerjeSkills().GetPerkValue("immunity", "intoxicres", perkIntoxicres))
				{
					perkIntoxicresMod += perkIntoxicres;
				}
			}
			
			float overdoseDecPerSec = 0;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_OVERDOSE_DEC_PER_SEC, overdoseDecPerSec);
			overdoseValue -= (overdoseDecPerSec * perkIntoxicresMod * deltaTime);
			player.GetTerjeStats().SetOverdoseValue(overdoseValue);
			
			if (!player.GetAllowDamage())
			{
				return;
			}
			
			if (overdoseValue > 2)
			{
				if (GetPlayerShock(player) > 50)
				{
					if (TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_OVERDOSE_UNCONSCIOUS_CHANCE) * deltaTime))
					{
						SetPlayerShock(player, TerjeDamageSource.OVERDOSE, 0);
					}
				}
			}
			
			if (overdoseValue > 3)
			{
				float overdoseCriticalDmgMultiplier = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_OVERDOSE_CRITICAL_DMG_MULTIPLIER);
				float dmgForce = overdoseCriticalDmgMultiplier * (overdoseValue - 3);
				DecreasePlayerHealth(player, TerjeDamageSource.OVERDOSE, dmgForce * deltaTime);
			}
		}
	}
}
