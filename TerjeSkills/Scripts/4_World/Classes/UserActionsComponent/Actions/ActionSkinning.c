modded class ActionSkinningCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		super.CreateActionComponent();
		
		float overrideSkinningTime = -1;
		float terjeSkinningTime = -1;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_SKINNING_TIME, overrideSkinningTime) && overrideSkinningTime > 0)
		{
			terjeSkinningTime = overrideSkinningTime;
			
			if (m_ActionData.m_Player && m_ActionData.m_Player.IsAlive() && m_ActionData.m_Player.GetTerjeSkills() != null)
			{
				if (m_ActionData.m_Player.GetTerjeSkills().IsPerkRegistered("hunt", "quickcut"))
				{
					float quickcutPerk;
					if (m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("hunt", "quickcut", quickcutPerk))
					{
						terjeSkinningTime *= Math.Clamp(1.0 + quickcutPerk, 0, 1);
					}
				}
			}
			
			if (m_ActionData.m_MainItem)
			{
				if (GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningTimeModifier"))
				{
					terjeSkinningTime *= GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningTimeModifier");
				}
				else if (GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningModifier"))
				{
					// For backward compatibility only, please use terjeSkinningTimeModifier instead
					terjeSkinningTime *= GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningModifier");
				}
				
				if (GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningTimeModifierOverride"))
				{
					terjeSkinningTime = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningTimeModifierOverride");
				}
				else if (GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningModifierOverride"))
				{
					// For backward compatibility only, please use terjeSkinningTimeModifierOverride instead
					terjeSkinningTime = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + m_ActionData.m_MainItem.GetType() + " terjeSkinningModifierOverride");
				}
			}
			
			if (m_ActionData.m_Target != null)
			{
				AnimalBase animalBody = AnimalBase.Cast(m_ActionData.m_Target.GetObject());
				if (animalBody && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + animalBody.GetType() + " terjeSkinningTimeModifier"))
				{
					terjeSkinningTime *= GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + animalBody.GetType() + " terjeSkinningTimeModifier");
				}
			}
		}
		
		if (terjeSkinningTime >= 0)
		{
			m_ActionData.m_ActionComponent = new CAContinuousTime(terjeSkinningTime);
		}
	}
}

modded class ActionSkinning
{
	private ref array<ItemBase> m_terjeSpawnedItemsCache = new array<ItemBase>;
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		m_terjeSpawnedItemsCache.Clear();
		AnimalBase animalBody = AnimalBase.Cast(action_data.m_Target.GetObject());
		if (animalBody && action_data.m_Player && action_data.m_Player.IsAlive() && action_data.m_Player.GetTerjeSkills())
		{
			float huntingButchAnimalExpGainModifier;
			if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_BUTCH_ANIMAL_EXP_GAIN_MODIFIER, huntingButchAnimalExpGainModifier))
			{
				int huntExp = (int)(GetTerjeGameConfig().ConfigGetInt("CfgVehicles " + animalBody.GetType() + " terjeOnButchHuntingExp") * huntingButchAnimalExpGainModifier);
				if (action_data.m_MainItem && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + action_data.m_MainItem.GetType() + " terjeSkinningExpModifier"))
				{
					huntExp = (int)(huntExp * GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + action_data.m_MainItem.GetType() + " terjeSkinningExpModifier"));
				}
				
				if (huntExp > 0)
				{
					action_data.m_Player.GetTerjeSkills().AddSkillExperience("hunt", huntExp);
				}
			}
		}
		
		super.OnFinishProgressServer(action_data);
		
		if (action_data.m_Player && action_data.m_Player.IsAlive() && action_data.m_Player.GetTerjeSkills())
		{
			TerjeProcessServerSpawnedItems(action_data.m_Player);
			
			if (action_data.m_MainItem && action_data.m_Player.GetTerjeSkills().IsPerkRegistered("hunt", "mknife"))
			{
				float huntingOverrideKnifeDamage;
				if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_KNIFE_DAMAGE, huntingOverrideKnifeDamage))
				{
					float mknifeSkill;
					if (action_data.m_Player.GetTerjeSkills().GetPerkValue("hunt", "mknife", mknifeSkill))
					{
						mknifeSkill = Math.Clamp(1.0 + mknifeSkill, 0.1, 1) - 0.1;
					}
					else
					{
						mknifeSkill = 1.0;
					}
					
					float animalBodyMod = 1.0;
					if (animalBody && GetTerjeGameConfig().ConfigIsExisting("CfgVehicles " + animalBody.GetType() + " terjeSkinningKnifeDamageModifier"))
					{
						animalBodyMod = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + animalBody.GetType() + " terjeSkinningKnifeDamageModifier");
					}
					
					action_data.m_MainItem.DecreaseHealth(huntingOverrideKnifeDamage * mknifeSkill * animalBodyMod, false);
				}
			}
		}
		
		m_terjeSpawnedItemsCache.Clear();
	}
	
	override ItemBase CreateOrgan(PlayerBase player, vector body_pos, string item_to_spawn, string cfg_skinning_organ_class, ItemBase tool)
	{
		ItemBase resultItem = super.CreateOrgan(player, body_pos, item_to_spawn, cfg_skinning_organ_class, tool);
		if (resultItem)
		{
			m_terjeSpawnedItemsCache.Insert(resultItem);
		}
		
		return resultItem;
	}
	
	void TerjeProcessServerSpawnedItems(PlayerBase player)
	{
		float skillModifier = 0;
		if (player.GetTerjeSkills().GetSkillModifierValue("hunt", "meatcountmod", skillModifier))
		{
			set<string> uniqItemsCache();
			foreach (ItemBase item : m_terjeSpawnedItemsCache)
			{
				if (item)
				{
					string itemType = item.GetType();
					if (uniqItemsCache.Find(itemType) != -1)
					{
						if (TerjeEventInverse(skillModifier))
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
		
		float meathunterInitSetting = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_MEAT_INIT_QUANTITY);
		float meathunterMinSetting = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_HUNTING_OVERRIDE_MEAT_MIN_QUANTITY);
		foreach (ItemBase item2 : m_terjeSpawnedItemsCache)
		{
			if (item2)
			{
				if (item2.IsMeat() && item2.HasQuantity())
				{
					float newQuantityMin = item2.GetQuantityMax() * meathunterMinSetting;
					float newQuantityInit = item2.GetQuantityMax() * Math.RandomFloat01() * meathunterInitSetting;
					float newQuantityAdd = (item2.GetQuantityMax() - newQuantityMin) * meathuntSkill;
					float newQuantityTotal = Math.Max(newQuantityMin, newQuantityInit + newQuantityAdd);
					item2.SetQuantity(Math.Round(newQuantityTotal));
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
	}
	
	void TerjeProcessServerSpawnedCustomItem(PlayerBase player, ItemBase item)
	{
		// Override for custom logic handling
	}
}
