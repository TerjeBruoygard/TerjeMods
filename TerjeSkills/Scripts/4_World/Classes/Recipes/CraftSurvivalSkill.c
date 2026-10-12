modded class CraftHandDrillKit
{
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo()) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "anctech", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "anctech");
	}
	
	bool TerjeDo()
	{
		return true;
	}
}

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

modded class CraftBaseBallBatBarbed
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

modded class CraftBaseBallBatNailed
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

modded class CraftBoneKnife
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

modded class CraftStoneKnife
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

modded class CraftSpearStone
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

modded class CraftGhillieAttachment
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

modded class CraftGhillieBushrag
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

modded class CraftGhillieHood
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

modded class CraftGhillieSuit
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

modded class CraftGhillieTop
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

modded class CraftImprovisedLeatherBag
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

modded class CraftLeatherCourierBag
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

modded class CraftLeatherSack
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

modded class CraftSpearBone
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