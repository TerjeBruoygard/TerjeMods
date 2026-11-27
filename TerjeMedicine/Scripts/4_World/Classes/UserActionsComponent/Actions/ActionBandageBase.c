modded class ActionBandageSelfCB
{
	override void CreateActionComponent()
	{
		super.CreateActionComponent();
		
		float perkSpeedMod = 1.0;
		if (m_ActionData.m_Player && m_ActionData.m_Player.GetTerjeSkills())
		{
			float perkModifier;
			if (m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("med", "mastdress", perkModifier))
			{
				perkSpeedMod += perkModifier;
			}
		}
		
		float effectivity = m_ActionData.m_MainItem.GetBandagingEffectivity();
		float adjustedTimeSpent = UATimeSpent.BANDAGE;

		if (effectivity > 0)
		{
			adjustedTimeSpent = adjustedTimeSpent / effectivity;
		}

		float settingSpeedMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGE_TIME_MOD, settingSpeedMod))
		{
			settingSpeedMod = 1.0;
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(1, adjustedTimeSpent * perkSpeedMod * settingSpeedMod));
	}
}

modded class ActionBandageTargetCB
{
	override void CreateActionComponent()
	{
		super.CreateActionComponent();
		
		float perkSpeedMod = 1.0;
		if (m_ActionData.m_Player && m_ActionData.m_Player.GetTerjeSkills())
		{
			float perkModifier;
			if (m_ActionData.m_Player.GetTerjeSkills().GetPerkValue("med", "mastdress", perkModifier))
			{
				perkSpeedMod += perkModifier;
			}
		}
		
		float effectivity = m_ActionData.m_MainItem.GetBandagingEffectivity();
		float adjustedTimeSpent = UATimeSpent.BANDAGE;

		if (effectivity > 0)
		{
			adjustedTimeSpent = adjustedTimeSpent / effectivity;
		}

		float settingSpeedMod;
		if (!GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGE_TIME_MOD, settingSpeedMod))
		{
			settingSpeedMod = 1.0;
		}
		
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(1, adjustedTimeSpent * perkSpeedMod * settingSpeedMod));
	}
}

modded class ActionBandageBase
{
	override void ApplyBandage(ItemBase item, PlayerBase player)
	{
		if (item && !player.TerjeIsNPC())
		{
			item.ApplyTerjeConsumableEffects(player, 1);
			CheckInfectionBandaging(item, player);
			
			PlayerBase operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
			if (operator && operator.GetTerjeSkills())
			{
				int bandageExpGain = 0;
				if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_BANDAGE_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
				{
					operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
				}
			}
		}
		
		super.ApplyBandage(item, player);
	}
	
	void CheckInfectionBandaging(ItemBase item, PlayerBase player, PlayerBase operator = null)
	{
		if (!operator)
		{
			operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
		}
		
		float perkSepsisresMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkSepsisres;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "sepsisres", perkSepsisres))
			{
				perkSepsisresMod -= Math.Clamp(perkSepsisres, 0, 1);
			}
		}
		
		float operatorPerkSterilityMod = 1.0;
		if (operator)
		{
			float bandagingSepsisChance = 0;
			ItemBase gloves = operator.GetItemOnSlot("Gloves");
			if (gloves)
			{
				if (!gloves.IsDisinfected())
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGING_SEPSIS_CHANCE_D_G, bandagingSepsisChance);
				}
			}
			else if (operator.HasBloodyHands())
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGING_SEPSIS_CHANCE_D_H, bandagingSepsisChance);
			}
			
			if (operator.GetTerjeSkills())
			{
				float perkValue;
				if (operator.GetTerjeSkills().GetPerkValue("med", "cleanstr", perkValue))
				{
					operatorPerkSterilityMod += perkValue;
					operatorPerkSterilityMod = Math.Clamp(operatorPerkSterilityMod, 0, 1);
				}
			}
			
			if (player && player.GetTerjeStats())
			{
				if (TerjeEvent(bandagingSepsisChance * operatorPerkSterilityMod * perkSepsisresMod))
				{
					player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
				}
			}
		}
		
		float bandagingSepsisModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BANDAGING_SEPSIS_MODIFIER, bandagingSepsisModifier);
		if (player && player.GetTerjeStats())
		{
			if (TerjeEvent(item.GetInfectionChance() * operatorPerkSterilityMod * bandagingSepsisModifier * perkSepsisresMod))
			{
				player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
			}
		}
	}
	
	void CheckInfectionSurgery(ItemBase item, PlayerBase player, PlayerBase operator = null)
	{
		if (!operator && item)
		{
			operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
		}
		
		float perkSepsisresMod = 1.0;
		if (player.GetTerjeSkills())
		{
			float perkSepsisres;
			if (player.GetTerjeSkills().GetPerkValue("immunity", "sepsisres", perkSepsisres))
			{
				perkSepsisresMod -= Math.Clamp(perkSepsisres, 0, 1);
			}
		}
		
		float operatorPerkSterilityMod = 1.0;
		if (operator && operator.GetTerjeStats() && player.GetTerjeStats())
		{
			float bandagingSepsisChance = 0;
			ItemBase gloves = operator.GetItemOnSlot("Gloves");
			if (gloves)
			{
				if (!gloves.IsDisinfected())
				{
					GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SURGERY_SEPSIS_CHANCE_D_G, bandagingSepsisChance);
				}
			}
			else if (operator.HasBloodyHands())
			{
				bandagingSepsisChance = 1;
			}
			else if (!operator.GetTerjeStats().GetDisinfected())
			{
				GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SURGERY_SEPSIS_CHANCE_D_H, bandagingSepsisChance);
			}
			
			if (operator.GetTerjeSkills())
			{
				float perkValue;
				if (operator.GetTerjeSkills().GetPerkValue("med", "cleanstr", perkValue))
				{
					operatorPerkSterilityMod += perkValue;
					operatorPerkSterilityMod = Math.Clamp(operatorPerkSterilityMod, 0, 1);
				}
			}
			
			if (TerjeEvent(bandagingSepsisChance * operatorPerkSterilityMod * perkSepsisresMod))
			{
				player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.25);
			}
		}
		
		float bandagingSepsisModifier = 1;
		GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_SURGERY_SEPSIS_MODIFIER, bandagingSepsisModifier);
		if (player && player.GetTerjeStats())
		{
			if (TerjeEvent(item.GetInfectionChance() * bandagingSepsisModifier * operatorPerkSterilityMod * perkSepsisresMod))
			{
				player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.25);
			}
		}
	}
	
	void ChangeBandage(ItemBase item, PlayerBase player)
	{
		if (item)
		{
			if (player.GetTerjeStats() != null)
			{
				if (player.GetTerjeStats().GetBandagesDirty() > 0)
				{
					player.GetTerjeStats().SetBandagesDirty(player.GetTerjeStats().GetBandagesDirty() - 1);
					player.GetTerjeStats().SetBandagesClean(player.GetTerjeStats().GetBandagesClean() + 1);
				}
				else if (player.GetTerjeStats().GetSuturesBandagedDirty() > 0)
				{
					player.GetTerjeStats().SetSuturesBandagedDirty(player.GetTerjeStats().GetSuturesBandagedDirty() - 1);
					player.GetTerjeStats().SetSuturesBandagedClean(player.GetTerjeStats().GetSuturesBandagedClean() + 1);
				}
				
				PlayerBase operator = PlayerBase.Cast( item.GetHierarchyRootPlayer() ); 
				if (operator && operator.GetTerjeSkills())
				{
					int bandageExpGain = 0;
					if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_BANDAGE_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
					{
						operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
					}
				}
			}
			
			CheckInfectionBandaging(item, player);
			
			if (item.HasQuantity())
			{
				float consumeQuantity = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + item.GetType() + " terjeOverrideSurgeryConsumeQuantity");
				if (consumeQuantity > 0)
				{
					item.AddQuantity(-consumeQuantity, true);
				}
				else
				{
					item.AddQuantity(-1, true);
				}
			}
			else
			{
				item.Delete();
			}
		}
	}
	
	void ApplySurgeryViscera(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (TerjeEvent(item.GetTerjeSurgeryVisceraEffectivity(operator)))
		{
			if (target.GetTerjeStats() != null)
			{
				target.GetTerjeStats().SetViscera(false);
				
				int suturesMin = 1;
				int suturesMax = 1;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_VISCERA_SUTURES_MIN, suturesMin);
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_VISCERA_SUTURES_MAX, suturesMax);
				
				if (suturesMin > 0 && suturesMax > 0 && suturesMin < suturesMax)
				{
					target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + Math.RandomIntInclusive(suturesMin, suturesMax));
				}
				else if (suturesMin > 0)
				{
					target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + suturesMin);
				}
				
				if (operator.GetTerjeSkills())
				{
					int bandageExpGain = 0;
					if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_VISCERA_SURGERY_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
					{
						operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
					}
				}
			}
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_VISCERA_SUCCESS", "set:TerjePerk_icon image:tp_surgeryinternal");
			}
		}
		else
		{
			target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			target.GetTerjeHealth().DecreaseHealth(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FAILED_HEALTH_LOSE), TerjeDamageSource.SURGERY_VISCERA);
			target.GetTerjeHealth().DecreaseBlood(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FAILED_BLOOD_LOSE), TerjeDamageSource.SURGERY_VISCERA);
			target.GetTerjeHealth().DecreaseShock(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FAILED_SHOCK_LOSE), TerjeDamageSource.SURGERY_VISCERA);
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_VISCERA_FAILED", "set:TerjePerkBlack_icon image:tp_surgeryinternal");
			}
		}
		
		CheckInfectionSurgery(item, target, operator);
		
		if (item.HasQuantity())
		{
			float consumeQuantity = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + item.GetType() + " terjeOverrideSurgeryConsumeQuantity");
			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}
	
	void ApplySurgeryBullet(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (TerjeEvent(item.GetTerjeSurgeryBulletEffectivity(operator)))
		{
			if (target.GetTerjeStats() != null)
			{
				int bulletWounds = target.GetTerjeStats().GetBulletWounds();
				if (bulletWounds > (target.GetTerjeStats().GetStubWounds() + target.GetTerjeStats().GetBandagesClean() + target.GetTerjeStats().GetBandagesDirty()))
				{
					int suturesMin = 1;
					int suturesMax = 1;
					GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_BULLETS_SUTURES_MIN, suturesMin);
					GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_BULLETS_SUTURES_MAX, suturesMax);
					
					if (suturesMin > 0 && suturesMax > 0 && suturesMin < suturesMax)
					{
						target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + Math.RandomIntInclusive(suturesMin, suturesMax));
					}
					else if (suturesMin > 0)
					{
						target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + suturesMin);
					}
				}
				
				target.GetTerjeStats().SetBulletWounds(bulletWounds - 1);
				
				if (operator.GetTerjeSkills())
				{
					int bandageExpGain = 0;
					if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_BULLET_SURGERY_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
					{
						operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
					}
				}
			}
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_BULLET_SUCCESS", "set:TerjePerk_icon image:tp_surgerybullet");
			}
			
		}
		else
		{
			target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			target.GetTerjeHealth().DecreaseHealth(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_HEALTH_LOSE), TerjeDamageSource.SURGERY_BULLETS);
			target.GetTerjeHealth().DecreaseBlood(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_BLOOD_LOSE), TerjeDamageSource.SURGERY_BULLETS);
			target.GetTerjeHealth().DecreaseShock(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FAILED_SHOCK_LOSE), TerjeDamageSource.SURGERY_BULLETS);
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_BULLET_FAILED", "set:TerjePerkBlack_icon image:tp_surgerybullet");
			}
		}
		
		CheckInfectionSurgery(item, target, operator);
		
		if (item.HasQuantity())
		{
			float consumeQuantity = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + item.GetType() + " terjeOverrideSurgeryConsumeQuantity");
			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}
	
	void ApplySurgeryStub(ItemBase item, PlayerBase target, PlayerBase operator)
	{
		if (TerjeEvent(item.GetTerjeSurgeryStubEffectivity(operator)))
		{
			if (target.GetTerjeStats() != null)
			{
				if (target.GetTerjeStats().GetStubWounds() > 0)
				{
					target.GetTerjeStats().SetStubWounds(target.GetTerjeStats().GetStubWounds() - 1);
				}
				else if (target.GetTerjeStats().GetBandagesClean() > 0)
				{
					target.GetTerjeStats().SetBandagesClean(target.GetTerjeStats().GetBandagesClean() - 1);
				}
				else if (target.GetTerjeStats().GetBandagesDirty() > 0)
				{
					target.GetTerjeStats().SetBandagesDirty(target.GetTerjeStats().GetBandagesDirty() - 1);
				}
				
				int suturesMin = 1;
				int suturesMax = 1;
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_STUBS_SUTURES_MIN, suturesMin);
				GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_STUBS_SUTURES_MAX, suturesMax);
				
				if (suturesMin > 0 && suturesMax > 0 && suturesMin < suturesMax)
				{
					target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + Math.RandomIntInclusive(suturesMin, suturesMax));
				}
				else if (suturesMin > 0)
				{
					target.GetTerjeStats().SetSuturesClean(target.GetTerjeStats().GetSuturesClean() + suturesMin);
				}
			
				if (operator.GetTerjeSkills())
				{
					int bandageExpGain = 0;
					if (GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_MEDICINE_STUB_SURGERY_EXP_GAIN, bandageExpGain) && bandageExpGain > 0)
					{
						operator.GetTerjeSkills().AddSkillExperience("med", bandageExpGain);
					}
				}
			}
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 8, "#STR_TERJEMED_SURGERY_SUCCESS", "#STR_TERJEMED_SURGERY_WOUND_SUCCESS", "set:TerjePerk_icon image:tp_surgerystab");
			}
		}
		else
		{
			target.GetSymptomManager().QueueUpPrimarySymptom(SymptomIDs.SYMPTOM_PAIN_HEAVY);
			target.GetTerjeHealth().DecreaseHealth(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_HEALTH_LOSE), TerjeDamageSource.SURGERY_STUBS);
			target.GetTerjeHealth().DecreaseBlood(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_BLOOD_LOSE), TerjeDamageSource.SURGERY_STUBS);
			target.GetTerjeHealth().DecreaseShock(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_STUBS_FAILED_SHOCK_LOSE), TerjeDamageSource.SURGERY_STUBS);
			
			if (operator.GetIdentity())
			{
				NotificationSystem.SendNotificationToPlayerIdentityExtended(operator.GetIdentity(), 10, "#STR_TERJEMED_SURGERY_FAILED", "#STR_TERJEMED_SURGERY_WOUND_FAILED", "set:TerjePerkBlack_icon image:tp_surgerystab");
			}
		}
		
		CheckInfectionSurgery(item, target, operator);
		
		if (item.HasQuantity())
		{
			float consumeQuantity = GetTerjeGameConfig().ConfigGetFloat("CfgVehicles " + item.GetType() + " terjeOverrideSurgeryConsumeQuantity");
			if (consumeQuantity > 0)
			{
				item.AddQuantity(-consumeQuantity, true);
			}
			else
			{
				item.AddQuantity(-1, true);
			}
		}
		else
		{
			item.Delete();
		}
	}
}

modded class ActionBandageSelf
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return super.ActionCondition(player, target, item) && player.HasTerjeBleedingSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
}

modded class ActionBandageTarget
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return super.ActionCondition(player, target, item) && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
}
