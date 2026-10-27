modded class PrepareChicken
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		int huntExp = 0;
		player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		TerjeSkillsSpecificLogicDoSuper(ingredients, player, huntExp);
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsSpecificLogic(player, results, huntExp);
		player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class PrepareRabbit
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		int huntExp = 0;
		player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		TerjeSkillsSpecificLogicDoSuper(ingredients, player, huntExp);
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsSpecificLogic(player, results, huntExp);
		player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class PrepareFox
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		int huntExp = 0;
		player.m_terjeSkillsSpawnEntityOnGroundCache = new array<ItemBase>;
		TerjeSkillsSpecificLogicDoSuper(ingredients, player, huntExp);
		super.Do(ingredients, player, results, specialty_weight);
		TerjeSkillsSpecificLogic(player, results, huntExp);
		player.m_terjeSkillsSpawnEntityOnGroundCache = null;
	}
}

modded class PrepareAnimal
{
	override float GetLengthInSecs()
	{
		float overrideSkinningTime;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_SKINNING_TIME, overrideSkinningTime) && overrideSkinningTime > 0)
		{
 			return overrideSkinningTime;
		}
		else
		{
			return super.GetLengthInSecs();
		}
	}
	
	protected void TerjeSkillsSpecificLogicDoSuper(ItemBase ingredients[], PlayerBase player, out int huntExp)
	{
		huntExp = 0;
		if (!(g_Game.IsDedicatedServer() && player && player.IsAlive() && player.GetTerjeSkills()))
		{
			return;
		}
		
		ItemBase animalBody = ingredients[0];
		ItemBase knifeItem = ingredients[1];
		string animalBodyType = string.Empty;
		string knifeType = string.Empty;
		
		if (animalBody)
		{
			animalBodyType = animalBody.GetType();
		}
		
		if (knifeItem)
		{
			knifeType = knifeItem.GetType();
		}
		
		if (knifeItem && player.GetTerjeSkills().IsPerkRegistered("hunt", "mknife"))
		{
			float huntingOverrideKnifeDamage;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE, huntingOverrideKnifeDamage))
			{
				float mknifeSkill = 1.0;
				float perkMknife;
				if (player.GetTerjeSkills().GetPerkValue("hunt", "mknife", perkMknife))
				{
					mknifeSkill = Math.Clamp(1.0 + perkMknife, 0, 1);
				}
				
				float animalBodyMod = 1.0;
				if (animalBodyType != string.Empty && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + animalBodyType + " terjeSkinningKnifeDamageModifier"))
				{
					animalBodyMod = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + animalBodyType + " terjeSkinningKnifeDamageModifier");
				}
				
				knifeItem.DecreaseHealth(huntingOverrideKnifeDamage * mknifeSkill * animalBodyMod, false);
			}
		}
		
		if (animalBodyType != string.Empty)
		{
			float huntingButchAnimalExpGainModifier;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER, huntingButchAnimalExpGainModifier))
			{
				int expCfg = GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + animalBodyType + " terjeOnButchHuntingExp");
				huntExp = (int)(expCfg * huntingButchAnimalExpGainModifier);
				if (knifeType != string.Empty && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + knifeType + " terjeSkinningExpModifier"))
				{
					huntExp = (int)(huntExp * GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + knifeType + " terjeSkinningExpModifier"));
				}
			}
		}
	}
	
	protected void TerjeSkillsSpecificLogic(PlayerBase player, array<ItemBase> results, int huntExp)
	{
		if (player && player.IsAlive() && player.GetTerjeSkills() && player.m_terjeSkillsSpawnEntityOnGroundCache != null)
		{
			array<ItemBase> resultItems();
			foreach (ItemBase resultItem : results)
			{
				resultItems.Insert(resultItem);
			}
			foreach (ItemBase cacheItem : player.m_terjeSkillsSpawnEntityOnGroundCache)
			{
				resultItems.Insert(cacheItem);
			}
			
			float skillModifier = 0;
			if (player.GetTerjeSkills().GetSkillModifierValue("hunt", "meatcountmod", skillModifier))
			{
				set<string> uniqItemsCache();
				foreach (ItemBase item : resultItems)
				{
					if (item)
					{
						string itemType = item.GetType();
						if (uniqItemsCache.Find(itemType) != -1)
						{
							if (Math.RandomFloat01() > skillModifier)
							{
								item.Delete();
							}
						}
						else
						{
							uniqItemsCache.Insert(itemType);
						}
					}
				}
			}
			
			float meathuntSkill = 1.0;
			if (player.GetTerjeSkills().IsPerkRegistered("hunt", "meathunt"))
			{
				if (!player.GetTerjeSkills().GetPerkValue("hunt", "meathunt", meathuntSkill))
				{
					meathuntSkill = 0;
				}
			}
			
			float plmasterSkill = 1.0;
			if (player.GetTerjeSkills().IsPerkRegistered("hunt", "plmaster"))
			{
				if (!player.GetTerjeSkills().GetPerkValue("hunt", "plmaster", plmasterSkill))
				{
					plmasterSkill = 0;
				}
			}
			
			float meathunterInitSetting;
			if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY, meathunterInitSetting))
			{
				meathunterInitSetting = 0.1;
			}
			
			float meathunterMinSetting;
			if (!GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY, meathunterMinSetting))
			{
				meathunterMinSetting = 0.1;
			}
			
			foreach (ItemBase item2 : resultItems)
			{
				if (item2)
				{
					if (item2.IsMeat() && item2.HasQuantity())
					{
						float newQuantityMin = item2.GetQuantityMax() * meathunterMinSetting;
						float newQuantityInit = item2.GetQuantityMax() * Math.RandomFloat01() * meathunterInitSetting;
						float newQuantityAdd = (item2.GetQuantityMax() - newQuantityMin) * meathuntSkill;
						float newQuantityTotal = Math.Max(newQuantityMin, newQuantityInit + newQuantityAdd);
						item2.SetQuantity(newQuantityTotal);
					}
					else if (item2.IsPeltBase())
					{
						item2.SetHealth01("", "", plmasterSkill);
						if (item2.HasQuantity())
						{
							item2.SetQuantityNormalized(plmasterSkill);
						}
					}
					else if (item2.IsInherited(Bone))
					{
						item2.SetHealth01("", "", Math.Max(GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_BONES_INIT_HP), Math.Clamp(skillModifier, 0, 1)));
					}
					else
					{
						TerjeProcessServerSpawnedCustomItem(player, item2);
					}
				}
			}
			
			if (huntExp > 0)
			{
				player.GetTerjeSkills().AddSkillExperience("hunt", huntExp);
			}
		}
	}
	
	override float GetTerjeCraftingTimeModifier(PlayerBase player)
	{
		float result = super.GetTerjeCraftingTimeModifier(player);
		if (player && player.IsAlive() && player.GetTerjeSkills() != null)
		{
			if (player.GetTerjeSkills().IsPerkRegistered("hunt", "quickcut"))
			{
				float quickcutPerk;
				if (player.GetTerjeSkills().GetPerkValue("hunt", "quickcut", quickcutPerk))
				{
					result *= Math.Clamp(1.0 + quickcutPerk, 0, 1);
				}
			}
			
			float settingMod = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_SMALL_SKINNING_MOD);
			if (settingMod > 0)
			{
				result *= settingMod;
			}
		}
		
		return Math.Max(0, result);
	}
	
	void TerjeProcessServerSpawnedCustomItem(PlayerBase player, ItemBase item)
	{
		// Override for custom logic handling
	}
}