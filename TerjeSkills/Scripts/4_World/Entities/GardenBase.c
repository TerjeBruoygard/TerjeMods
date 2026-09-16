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
	static const int TERJE_SLOT_PERK_SAVE_VERSION = 1;
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
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		ctx.Write(TERJE_SLOT_PERK_SAVE_VERSION);
		
		int slotsCount = GetGardenSlotsCount();
		for (int i = 0; i < slotsCount; i++)
		{
			Slot slot = m_Slots.Get(i);
			ctx.Write(slot.m_TerjeGrowthTimeBonus);
			ctx.Write(slot.m_TerjeWitherResistBonus);
			ctx.Write(slot.m_TerjeWeatherproofChance);
			ctx.Write(slot.m_TerjeHothouseBonus);
		}
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
		{
			return false;
		}
		
		int terjeVersion;
		if (!ctx.Read(terjeVersion))
		{
			return true;
		}
		
		if (terjeVersion < TERJE_SLOT_PERK_SAVE_VERSION)
		{
			return true;
		}
		
		int slotsCount = GetGardenSlotsCount();
		for (int i = 0; i < slotsCount; i++)
		{
			Slot slot = m_Slots.Get(i);
			if (!ctx.Read(slot.m_TerjeGrowthTimeBonus))
			{
				return true;
			}
			
			if (!ctx.Read(slot.m_TerjeWitherResistBonus))
			{
				return true;
			}
			
			if (!ctx.Read(slot.m_TerjeWeatherproofChance))
			{
				return true;
			}
			
			if (!ctx.Read(slot.m_TerjeHothouseBonus))
			{
				return true;
			}
		}
		
		return true;
	}
}
