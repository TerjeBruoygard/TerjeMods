class TerjeCutRottenMeat extends RecipeBase
{
	override void Init()
	{
		m_Name = "#STR_TERJESKILLS_CRAFT_CUT_ROTTEN";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 3;//animation length in relative time units
		
		m_AnywhereInInventory = false;//is this recipe valid even when neither of the items is in hands
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredient(0, "Edible_Base");
		
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1, "Inventory_Base");
		
		m_IngredientAddHealth[1] = -0.05;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player) //final check for recipe's validity
	{
		Edible_Base edible = Edible_Base.Cast(ingredients[0]);
		if (edible && edible.HasQuantity() && edible.GetFoodStage() && edible.GetFoodStageType() == FoodStageType.ROTTEN)
		{
			string skillName = "";
			string perkName = "";
			if (edible.IsMeat())
			{
				skillName = "hunt";
				perkName = "remvrot";
			}
			else if (edible.IsTerjeWholeFish() || edible.IsTerjeFishFillet())
			{
				skillName = "fish";
				perkName = "remrotf";
			}
			else if (edible.IsFruit() || edible.IsMushroom())
			{
				skillName = "farm";
				perkName = "remrotv";
			}
			
			if (skillName != "" && perkName != "")
			{
				ItemBase item_tool = ingredients[1];
				if (item_tool && item_tool.ConfigIsExisting("OpenItemSpillRange"))
				{
					if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel(skillName, perkName) > 0)
					{
						return true;
					}
				}
			}
		}
		
		return false;
	}

	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		Edible_Base edible = Edible_Base.Cast(ingredients[0]);
		ItemBase item_tool = ingredients[1];
		if (edible && item_tool)
		{
			array<int> spill_range = new array<int>;
			item_tool.ConfigGetIntArray("OpenItemSpillRange", spill_range );
			float spill_modificator = Math.RandomIntInclusive( spill_range.Get(0),spill_range.Get(1) ) / 100;
			float quantity_old = edible.GetQuantity();
			float spill_amount = quantity_old * spill_modificator * 5;
			float quantity_new = quantity_old - spill_amount;
			FoodStageType lastState = edible.GetLastDecayStage();
			if (lastState == FoodStageType.NONE)
			{
				lastState = FoodStageType.RAW;
			}
			
			edible.ChangeFoodStage(lastState);
			edible.SetTerjeDecayTimer(3600);
			edible.RemoveAgent(eAgents.FOOD_POISON);
			edible.SetQuantity(quantity_new);
		}
	}
}