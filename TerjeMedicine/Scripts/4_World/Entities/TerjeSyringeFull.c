class TerjeSyringeFull extends Inventory_Base
{
	private string m_medSolution;
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		m_medSolution = "";
	}
	
	override void OnTerjeStoreSave(TerjeStorageWritingContext ctx)
	{
		super.OnTerjeStoreSave(ctx);
		ctx.WriteString("medSolution", m_medSolution);
	}
	
	override void OnTerjeStoreLoad(TerjeStorageReadingContext ctx)
	{
		super.OnTerjeStoreLoad(ctx);
		ctx.ReadString("medSolution", m_medSolution);
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionEmptySyringe);
		AddAction(ActionInjectSyringeSelf);
		AddAction(ActionInjectSyringeTarget);
	}
	
	override bool CanBeDisinfected()
	{
		return false;
	}
	
	string GetMedSolutionClassname()
	{
		return m_medSolution;
	}
	
	void UpdateSyringeData(string solutionClassname)
	{
		m_medSolution = solutionClassname;
	}
	
	string GetTerjeSyringeClassnameEmpty()
	{
		return "TerjeSyringeEmpty";
	}
	
	float GetTerjeDamageOnUse()
	{
		return 5;
	}
	
	override void OnApply(PlayerBase player)
	{
		if (g_Game.IsDedicatedServer())
		{
			float operatorPerkSterilityMod = 1.0;
			PlayerBase operator = PlayerBase.Cast( this.GetHierarchyRootPlayer() ); 
			if (operator && operator.GetTerjeSkills())
			{
				float perkValue;
				if (operator.GetTerjeSkills().GetPerkValue("med", "cleanstr", perkValue))
				{
					operatorPerkSterilityMod += perkValue;
					operatorPerkSterilityMod = Math.Clamp(operatorPerkSterilityMod, 0, 1);
				}
			}
			
			float perkSepsisresMod = 1.0;
			if (player.GetTerjeSkills())
			{
				float perkSepsisres;
				if (player.GetTerjeSkills().GetPerkValue("immunity", "sepsisres", perkSepsisres))
				{
					perkSepsisresMod -= Math.Clamp(perkSepsisres, 0, 1);
				}
			}
			
			if (!IsDisinfected() && TerjeEvent(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_DIRTY_SYRINGE_SEPSIS_CHANCE) * operatorPerkSterilityMod * perkSepsisresMod))
			{
				if (player.GetTerjeStats()) player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + 0.1);
			}
			
			TerjeConsumableEffects medEffects = new TerjeConsumableEffects();
			if (medEffects && GetMedSolutionClassname() != "")
			{
				medEffects.Apply(this, "CfgVehicles " + GetMedSolutionClassname(), player, 1.0);
			}
			
			MiscGameplayFunctions.DealAbsoluteDmg(this, GetTerjeDamageOnUse());
		}
	}
}

class TerjeImprovisedSyringeFull : TerjeSyringeFull
{
	override string GetTerjeSyringeClassnameEmpty()
	{
		return "TerjeImprovisedSyringeEmpty";
	}
}