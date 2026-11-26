modded class TerjeConsumableEffects
{
	override void TerjeApplyPositiveEffects(string classname, PlayerBase player, float amount, float perkPharmacMod)
	{
		super.TerjeApplyPositiveEffects(classname, player, amount, perkPharmacMod);
		
		if (player.GetTerjeStats())
		{
			int medLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntiradLevel" );
			if (medLevel > 0)
			{
				int medActiveLevel = 0;
				float medActiveTimeSec = 0;
				player.GetTerjeStats().GetAntirad(medActiveLevel, medActiveTimeSec);
				
				float medTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntiradTimeSec" );
				if (medLevel >= medActiveLevel && medTimeSec > 0)
				{
					int MaxTimeSec = TerjeGetMaxTimeSec(classname, "Antirad");
					float ActiveTimeSec = TerjeGetActiveTimeSec(medActiveTimeSec, medTimeSec, amount, perkPharmacMod);
					player.GetTerjeStats().SetAntirad(medLevel, Math.Min(MaxTimeSec, ActiveTimeSec));
				}
			}
		}
	}
	
	override void TerjeApplyNegativeEffects(string classname, PlayerBase player, float amount)
	{
		super.TerjeApplyNegativeEffects(classname, player, amount);
		
		if (player.GetTerjeStats())
		{
			float medDmgValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medRadiationIncrement" );
			if (medDmgValue != 0)
			{
				player.GetTerjeStats().SetRadiationValue(player.GetTerjeStats().GetRadiationValue() + (medDmgValue * amount));
			}
		}
	}
	
	override private string DescribePositiveEffects(string classname)
	{
		string result = super.DescribePositiveEffects(classname);
		
		result += TerjeGetEffectString_Level("Antirad", "#STR_TERJERAD_EFFECT_RADPROTECT", classname);
		
		float medDmgValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medRadiationIncrement" );
		if (medDmgValue < 0)
		{
			result += "   " + PercentValue(medDmgValue, 0) + "#STR_TERJERAD_EFFECT_RADIATION " + NEXT_LINE;
		}
		
		return result;
	}
	
	override private string DescribeNegativeEffects(string classname)
	{
		string result = super.DescribeNegativeEffects(classname);
		
		float medDmgValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medRadiationIncrement" );
		if (medDmgValue > 0)
		{
			result += "   " + PercentValue(medDmgValue, 1) + "#STR_TERJERAD_EFFECT_RADIATION " + NEXT_LINE;
		}
		
		return result;
	}
}
