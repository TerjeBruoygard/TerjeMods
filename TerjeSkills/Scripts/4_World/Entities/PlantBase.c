modded class PlantBase
{
	float m_TerjeWeatherproofChance;
	
	void TerjeBakeFarmingPerks(float growthBonus, float witherResistBonus, float weatherproofChance)
	{
		if (growthBonus != 0)
		{
			m_FullMaturityTime = (int)(m_FullMaturityTime * Math.Clamp(1.0 + growthBonus, 0.2, 1.0));
			TerjeRecalcStateChangeTime();
		}
		
		if (witherResistBonus != 0)
		{
			m_DeleteDryPlantTime = (int)(m_DeleteDryPlantTime * (1.0 + witherResistBonus));
			m_SpoilAfterFullMaturityTime = (int)(m_SpoilAfterFullMaturityTime * (1.0 + witherResistBonus));
		}
		
		m_TerjeWeatherproofChance = weatherproofChance;
	}
	
	protected void TerjeRecalcStateChangeTime()
	{
		int divisor = m_GrowthStagesCount - 2;
		if (divisor <= 0)
		{
			return;
		}
		
		m_StateChangeTime = m_FullMaturityTime / divisor;
	}
	
	override void Tick()
	{
		if (m_PlantState == EPlantState.PAUSED && m_TerjeWeatherproofChance > 0 && Math.RandomFloat01() < m_TerjeWeatherproofChance)
		{
			m_TimeTracker = m_TimeTracker + m_TimeTicker.GetDuration() * m_DebugTickSpeedMultiplier;
			if (m_TimeTracker >= m_StateChangeTime)
			{
				GrowthTimerTick();
			}
			
			return;
		}
		
		super.Tick();
	}
	
	override bool OnStoreLoadCustom(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoadCustom(ctx, version))
		{
			return false;
		}
		
		float loadedWeatherproofChance = 0.0;
		if (ctx.Read(loadedWeatherproofChance))
		{
			m_TerjeWeatherproofChance = loadedWeatherproofChance;
		}
		
		return true;
	}
	
	override void OnStoreSaveCustom(ParamsWriteContext ctx)
	{
		super.OnStoreSaveCustom(ctx);
		ctx.Write(m_TerjeWeatherproofChance);
	}
	
	override void Harvest(PlayerBase player)
	{
		bool wasHarvestable = IsHarvestable();
		int baseYield = m_CropsCount;
		string cropType = m_CropsType;
		
		if (wasHarvestable && player)
		{
			for (int i = 0; i < baseYield; i++)
			{
				ItemBase spawnedItem = ItemBase.Cast(GetGame().CreateObjectEx(cropType, player.GetPosition(), ECE_PLACE_ON_SURFACE));
				if (!spawnedItem)
				{
					continue;
				}
				
				TerjeApplyCropQuantity(player, spawnedItem);
				TerjeApplyFreshHarvestPerk(player, spawnedItem);
			}
		}
		
		m_HasCrops = false;
		SetSynchDirty();
		UpdatePlant();
		m_GardenBase.SyncSlots();
	}
	
	protected void TerjeApplyCropQuantity(PlayerBase player, ItemBase item)
	{
		if (!item || !item.HasQuantity())
		{
			return;
		}
		
		float quantityMult = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_CROP_BASE_QUANTITY);
		
		if (player && player.GetTerjeSkills())
		{
			float richHarvestValue;
			if (player.GetTerjeSkills().GetPerkValue("farm", "richhrv", richHarvestValue))
			{
				quantityMult = quantityMult + richHarvestValue;
			}
		}
		
		quantityMult = Math.Clamp(quantityMult, 0, 1.0);
		item.SetQuantity(item.GetQuantityMax() * quantityMult);
	}
	
	protected void TerjeApplyFreshHarvestPerk(PlayerBase player, ItemBase item)
	{
		if (!player || !player.GetTerjeSkills())
		{
			return;
		}
		
		Edible_Base edible = Edible_Base.Cast(item);
		if (!edible)
		{
			return;
		}
		
		float perkValue;
		if (!player.GetTerjeSkills().GetPerkValue("farm", "freshhrv", perkValue))
		{
			return;
		}
		
		float baseDecayTime = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_CROP_DECAY_TIME);
		float finalDecayTime = baseDecayTime * (1.0 + perkValue);
		edible.SetTerjeDecayTimer(finalDecayTime);
	}
}
