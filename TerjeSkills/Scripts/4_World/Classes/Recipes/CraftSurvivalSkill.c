modded class CraftHandDrillKit
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "anctech", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "anctech");
	}
}

modded class CraftArrow
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftArrowBone
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftBaseBallBatBarbed
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftBaseBallBatNailed
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftBoneKnife
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftStoneKnife
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftSpearStone
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftGhillieAttachment
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftGhillieBushrag
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftGhillieHood
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftGhillieSuit
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftGhillieTop
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftImprovisedLeatherBag
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftLeatherCourierBag
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftLeatherSack
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}

modded class CraftSpearBone
{
	bool TerjeDo = true;
	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return super.CanDo(ingredients, player) && TerjeCanDo(player);
	}
	
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		super.Do(ingredients, player, results, specialty_weight);
		if (TerjeDo) TerjeSkillsCraftingHelper.GetInstance().DoCraftPerkRequired(this, player, results, "surv", "bushcraft", true);
	}
	
	bool TerjeCanDo(PlayerBase player)
	{
		return TerjeSkillsCraftingHelper.GetInstance().CanDoCraftPerkRequired(this, player, "surv", "bushcraft");
	}
}