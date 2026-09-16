modded class CAContinuousWaterSlot
{
	override void CalcAndSetQuantity(ActionData action_data)
	{
		if (!g_Game.IsServer())
		{
			return;
		}
		
		float bottleCost = m_SpentQuantity * TerjeGetWaterBottleCostMultiplier(action_data.m_Player);
		
		if (m_SpentUnits)
		{
			m_SpentUnits.param1 = bottleCost;
			SetACData(m_SpentUnits);
		}
		
		if (action_data.m_MainItem)
		{
			action_data.m_MainItem.AddQuantity(-bottleCost, false, false);
		}
	}
	
	protected float TerjeGetWaterBottleCostMultiplier(PlayerBase player)
	{
		float waterUsageMult = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_WATER_USAGE_MULT);
		float waterBalanceMult = 1.0;
		
		if (player && player.GetTerjeSkills())
		{
			float waterBalanceValue;
			if (player.GetTerjeSkills().GetPerkValue("farm", "wtrbal", waterBalanceValue))
			{
				waterBalanceMult = Math.Clamp(1.0 + waterBalanceValue, 0.15, 1.0);
			}
		}
		
		return waterUsageMult * waterBalanceMult;
	}
}

modded class CAContinuousWaterPlant
{
	override void CalcAndSetQuantity(ActionData action_data)
	{
		if (!g_Game.IsServer())
		{
			return;
		}
		
		float bottleCost = m_SpentQuantity * TerjeGetWaterBottleCostMultiplier(action_data.m_Player);
		
		if (m_SpentUnits)
		{
			m_SpentUnits.param1 = bottleCost;
			SetACData(m_SpentUnits);
		}
		
		if (action_data.m_MainItem)
		{
			action_data.m_MainItem.AddQuantity(-bottleCost, false, false);
		}
	}
	
	protected float TerjeGetWaterBottleCostMultiplier(PlayerBase player)
	{
		float waterUsageMult = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_WATER_USAGE_MULT);
		float waterBalanceMult = 1.0;
		
		if (player && player.GetTerjeSkills())
		{
			float waterBalanceValue;
			if (player.GetTerjeSkills().GetPerkValue("farm", "wtrbal", waterBalanceValue))
			{
				waterBalanceMult = Math.Clamp(1.0 + waterBalanceValue, 0.15, 1.0);
			}
		}
		
		return waterUsageMult * waterBalanceMult;
	}
}
