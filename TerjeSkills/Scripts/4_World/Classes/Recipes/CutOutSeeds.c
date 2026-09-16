modded class CutOutSeeds
{
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);
		
		if (results.Count() == 0)
		{
			return;
		}
		
		ItemBase result = results[0];
		if (!result || !result.HasQuantity())
		{
			return;
		}
		
		float vanillaQuantity = result.GetQuantity();
		float quantityMult = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_FARMING_OVERRIDE_SEED_CUT_MULT);
		
		if (player && player.GetTerjeSkills())
		{
			float seedGainValue;
			if (player.GetTerjeSkills().GetPerkValue("farm", "seedgain", seedGainValue))
			{
				quantityMult = quantityMult + seedGainValue;
			}
		}
		
		if (quantityMult < 0)
		{
			quantityMult = 0;
		}
		
		float terjeQuantity = Math.Ceil(vanillaQuantity * quantityMult);
		terjeQuantity = Math.Min(terjeQuantity, result.GetQuantityMax());
		result.SetQuantity(terjeQuantity);
	}
}
