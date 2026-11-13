modded class Slot
{
	float m_TerjeGrowthTimeBonus;
	float m_TerjeWitherResistBonus;
	float m_TerjeWeatherproofChance;
	float m_TerjeHothouseBonus;
	
	void TerjeStampFarmingPerks(PlayerBase player)
	{
		if (!player || !player.GetTerjeSkills())
		{
			return;
		}
		
		TerjePlayerSkillsAccessor skills = player.GetTerjeSkills();
		float baseYieldMult = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_BASE_YIELD_MULT);
		float harvestingEfficiency = baseYieldMult;
		
		float skillModifier;
		if (skills.GetSkillModifierValue("farm", "cropyieldmod", skillModifier))
		{
			harvestingEfficiency = harvestingEfficiency + skillModifier;
		}
		
		m_HarvestingEfficiency = harvestingEfficiency;
		m_TerjeGrowthTimeBonus = 0;
		m_TerjeWitherResistBonus = 0;
		m_TerjeWeatherproofChance = 0;
		m_TerjeHothouseBonus = 0;
		
		float fastGrowthValue;
		if (skills.GetPerkValue("farm", "fastgrow", fastGrowthValue))
		{
			m_TerjeGrowthTimeBonus = fastGrowthValue;
		}
		
		float toughCropsValue;
		if (skills.GetPerkValue("farm", "toughcrp", toughCropsValue))
		{
			m_TerjeWitherResistBonus = toughCropsValue;
		}
		
		float weatherproofValue;
		if (skills.GetPerkValue("farm", "weathprf", weatherproofValue))
		{
			m_TerjeWeatherproofChance = weatherproofValue;
		}
		
		float hothouseValue;
		if (skills.GetPerkValue("farm", "hothouse", hothouseValue))
		{
			m_TerjeHothouseBonus = hothouseValue;
		}
	}
}

modded class GardenBase
{
	protected PlayerBase m_TerjeLastPlantingPlayer;
	
	void TerjeSetLastPlantingPlayer(PlayerBase player)
	{
		m_TerjeLastPlantingPlayer = player;
	}
	
	override void PlantSeed(ItemBase seed, string selection_component)
	{
		if ((g_Game.IsServer() || !g_Game.IsMultiplayer()) && m_TerjeLastPlantingPlayer)
		{
			Slot slot = GetSlotBySelection(selection_component);
			if (slot)
			{
				slot.TerjeStampFarmingPerks(m_TerjeLastPlantingPlayer);
			}
		}
		
		m_TerjeLastPlantingPlayer = null;
		super.PlantSeed(seed, selection_component);
	}
	
	override void CreatePlant(Slot slot)
	{
		bool canCreate = GetGame().IsServer() || !GetGame().IsMultiplayer();
		bool isGreenhouse = (GardenPlotGreenhouse.Cast(this) != null) || (GardenPlotPolytunnel.Cast(this) != null);
		
		if (canCreate && isGreenhouse && slot && slot.m_TerjeHothouseBonus != 0)
		{
			slot.m_HarvestingEfficiency = slot.m_HarvestingEfficiency + slot.m_TerjeHothouseBonus;
		}
		
		super.CreatePlant(slot);
		
		if (!canCreate || !slot)
		{
			return;
		}
		
		PlantBase plant = slot.GetPlant();
		if (!plant)
		{
			return;
		}
		
		float growthBonus = slot.m_TerjeGrowthTimeBonus;
		if (isGreenhouse)
		{
			growthBonus = growthBonus - slot.m_TerjeHothouseBonus;
		}
		
		plant.TerjeBakeFarmingPerks(growthBonus, slot.m_TerjeWitherResistBonus, slot.m_TerjeWeatherproofChance);
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		
		if (!m_Slots)
		{
			return;
		}
		
		int slotsCount = GetGardenSlotsCount();
		for (int i = 0; i < slotsCount; i++)
		{
			Slot slot = m_Slots.Get(i);
			if (!slot)
			{
				continue;
			}
			
			ctx.WriteFloat("farmGrowth_" + i, slot.m_TerjeGrowthTimeBonus);
			ctx.WriteFloat("farmWither_" + i, slot.m_TerjeWitherResistBonus);
			ctx.WriteFloat("farmWeather_" + i, slot.m_TerjeWeatherproofChance);
			ctx.WriteFloat("farmHothouse_" + i, slot.m_TerjeHothouseBonus);
		}
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		
		if (!m_Slots)
		{
			return;
		}
		
		int slotsCount = GetGardenSlotsCount();
		for (int i = 0; i < slotsCount; i++)
		{
			Slot slot = m_Slots.Get(i);
			if (!slot)
			{
				continue;
			}
			
			ctx.ReadFloat("farmGrowth_" + i, slot.m_TerjeGrowthTimeBonus);
			ctx.ReadFloat("farmWither_" + i, slot.m_TerjeWitherResistBonus);
			ctx.ReadFloat("farmWeather_" + i, slot.m_TerjeWeatherproofChance);
			ctx.ReadFloat("farmHothouse_" + i, slot.m_TerjeHothouseBonus);
		}
	}
}
