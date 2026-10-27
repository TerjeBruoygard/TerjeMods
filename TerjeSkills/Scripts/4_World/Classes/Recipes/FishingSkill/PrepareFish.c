modded class PrepareFish
{
	override float GetLengthInSecs()
	{
		float overrideSkinningTime;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_SKINNING_TIME, overrideSkinningTime) && overrideSkinningTime > 0)
		{
 			return overrideSkinningTime;
		}
		else
		{
			return super.GetLengthInSecs();
		}
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		int incExp = 0;
		ItemBase fishBody = ingredients[0];
		ItemBase knifeItem = ingredients[1];
		
		if (g_Game.IsDedicatedServer() && player && player.IsAlive() && player.GetTerjeSkills())
		{
			if (knifeItem && player.GetTerjeSkills().IsPerkRegistered("fish", "strgarms"))
			{
				float fishingOverrideKnifeDamage;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_KNIFE_DAMAGE, fishingOverrideKnifeDamage))
				{
					float mknifeSkill = 1.0;
					float perkStrgarms;
					if (player.GetTerjeSkills().GetPerkValue("fish", "strgarms", perkStrgarms))
					{
						mknifeSkill += perkStrgarms;
						mknifeSkill = Math.Clamp(mknifeSkill, 0, 1);
					}
					
					float fishBodyMod = 1.0;
					if (fishBody && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + fishBody.GetType() + " terjeSkinningKnifeDamageModifier"))
					{
						fishBodyMod = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + fishBody.GetType() + " terjeSkinningKnifeDamageModifier");
					}
					
					knifeItem.DecreaseHealth(fishingOverrideKnifeDamage * mknifeSkill * fishBodyMod, false);
				}
			}
			
			if (fishBody)
			{
				float huntingButchFishExpGainModifier;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_BUTCH_EXP_GAIN_MODIFIER, huntingButchFishExpGainModifier))
				{
					int expCfg = GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + fishBody.GetType() + " terjeOnButchFishingExp");
					incExp = (int)(expCfg * huntingButchFishExpGainModifier);
					if (knifeItem && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + knifeItem.GetType() + " terjeSkinningExpModifier"))
					{
						incExp = (int)(incExp * GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + knifeItem.GetType() + " terjeSkinningExpModifier"));
					}
				}
			}
		}
		
		super.Do(ingredients, player, results, specialty_weight);
		
		if (g_Game.IsDedicatedServer() && player && player.IsAlive() && player.GetTerjeSkills())
		{
			if (player.GetTerjeSkills().IsPerkRegistered("fish", "masterf"))
			{
				float initQuantity = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FISHING_OVERRIDE_FILLET_MIN_QUANTITY);	
				float perkQuantity = 0.0;
				player.GetTerjeSkills().GetPerkValue("fish", "masterf", perkQuantity);
				
				float totalQuantity = initQuantity + ((1.0 - initQuantity) * Math.Clamp(perkQuantity, 0, 1));
				for (int i=0; i < results.Count(); i++)
				{
					ItemBase item_result = ItemBase.Cast(results.Get(i));
					if (item_result)
					{
						item_result.SetQuantityNormalized(item_result.GetQuantityNormalized() * totalQuantity);
					}
				}
			}
			
			if (incExp > 0)
			{
				player.GetTerjeSkills().AddSkillExperience("fish", incExp);
			}
		}
	}
	
	override float GetTerjeCraftingTimeModifier(PlayerBase player)
	{
		float result = 1.0;
		if (player && player.IsAlive() && player.GetTerjeSkills() != null)
		{
			if (player.GetTerjeSkills().IsPerkRegistered("fish", "quickclean"))
			{
				float quickcutPerk;
				if (player.GetTerjeSkills().GetPerkValue("fish", "quickclean", quickcutPerk))
				{
					result *= Math.Clamp(1.0 + quickcutPerk, 0, 1);
				}
			}
		}
		
		return Math.Max(0, result);
	}
}