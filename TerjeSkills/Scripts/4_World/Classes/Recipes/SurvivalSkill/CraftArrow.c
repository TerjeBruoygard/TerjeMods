modded class CraftArrow
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo()) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	bool TerjeDo()
	{
		return true;
	}
}

modded class CraftArrowBone
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo()) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
	
	bool TerjeDo()
	{
		return true;
	}
}
