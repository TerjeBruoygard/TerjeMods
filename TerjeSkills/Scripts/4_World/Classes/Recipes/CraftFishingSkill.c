modded class CraftFishingRod
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
}

modded class CraftFishNetTrap
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
}

modded class CraftBoneHook
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
}

modded class CraftWoodenHook
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "fish", "craftsman", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "fish", "craftsman");
	}
}