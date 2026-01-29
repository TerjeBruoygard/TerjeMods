class TerjePillsCharcoalTablets: CharcoalTablets
{
	override bool SetQuantity(float value, bool destroy_config = true, bool destroy_forced = false, bool allow_client = false, bool clamp_to_stack_max = true)
	{
		bool superQuantity = super.SetQuantity(value);
		UpdateVisualState();
		return superQuantity;
	}
	
	protected void UpdateVisualState()
	{
		int pillcount = GetQuantity();
		
		if ( pillcount >= 1 ) ShowSelection("Tablet_01");
		else HideSelection("Tablet_01");
		if ( pillcount >= 2 ) ShowSelection("Tablet_02");
		else HideSelection("Tablet_02");
		if ( pillcount >= 3 ) ShowSelection("Tablet_03");
		else HideSelection("Tablet_03");
		if ( pillcount >= 4 ) ShowSelection("Tablet_04");
		else HideSelection("Tablet_04");
		if ( pillcount >= 5 ) ShowSelection("Tablet_05");
		else HideSelection("Tablet_05");
		if ( pillcount >= 6 ) ShowSelection("Tablet_06");
		else HideSelection("Tablet_06");
		if ( pillcount >= 7 ) ShowSelection("Tablet_07");
		else HideSelection("Tablet_07");
		if ( pillcount >= 8 ) ShowSelection("Tablet_08");
		else HideSelection("Tablet_08");
		if ( pillcount >= 9 ) ShowSelection("Tablet_09");
		else HideSelection("Tablet_09");
		if ( pillcount == 10 ) ShowSelection("Tablet_10");
		else HideSelection("Tablet_10");
	}
}

class TerjePillsPainkillerTablets: PainkillerTablets
{
	override bool SetQuantity(float value, bool destroy_config = true, bool destroy_forced = false, bool allow_client = false, bool clamp_to_stack_max = true)
	{
		bool superQuantity = super.SetQuantity(value);
		UpdateVisualState();
		return superQuantity;
	}
	
	protected void UpdateVisualState()
	{
		int pillcount = GetQuantity();
		
		if ( pillcount >= 1 ) ShowSelection("Tablet_01");
		else HideSelection("Tablet_01");
		if ( pillcount >= 2 ) ShowSelection("Tablet_02");
		else HideSelection("Tablet_02");
		if ( pillcount >= 3 ) ShowSelection("Tablet_03");
		else HideSelection("Tablet_03");
		if ( pillcount >= 4 ) ShowSelection("Tablet_04");
		else HideSelection("Tablet_04");
		if ( pillcount >= 5 ) ShowSelection("Tablet_05");
		else HideSelection("Tablet_05");
		if ( pillcount >= 6 ) ShowSelection("Tablet_06");
		else HideSelection("Tablet_06");
		if ( pillcount >= 7 ) ShowSelection("Tablet_07");
		else HideSelection("Tablet_07");
		if ( pillcount >= 8 ) ShowSelection("Tablet_08");
		else HideSelection("Tablet_08");
		if ( pillcount >= 9 ) ShowSelection("Tablet_09");
		else HideSelection("Tablet_09");
		if ( pillcount == 10 ) ShowSelection("Tablet_10");
		else HideSelection("Tablet_10");
	}
}

class TerjePillsTetracyclineAntibiotics: TetracyclineAntibiotics
{
	override bool SetQuantity(float value, bool destroy_config = true, bool destroy_forced = false, bool allow_client = false, bool clamp_to_stack_max = true)
	{
		bool superQuantity = super.SetQuantity(value);
		UpdateVisualState();
		return superQuantity;
	}
	
	protected void UpdateVisualState()
	{
		int pillcount = GetQuantity();
		
		if ( pillcount >= 1 ) ShowSelection("Tablet_01");
		else HideSelection("Tablet_01");
		if ( pillcount >= 2 ) ShowSelection("Tablet_02");
		else HideSelection("Tablet_02");
		if ( pillcount >= 3 ) ShowSelection("Tablet_03");
		else HideSelection("Tablet_03");
		if ( pillcount >= 4 ) ShowSelection("Tablet_04");
		else HideSelection("Tablet_04");
		if ( pillcount >= 5 ) ShowSelection("Tablet_05");
		else HideSelection("Tablet_05");
		if ( pillcount >= 6 ) ShowSelection("Tablet_06");
		else HideSelection("Tablet_06");
		if ( pillcount >= 7 ) ShowSelection("Tablet_07");
		else HideSelection("Tablet_07");
		if ( pillcount >= 8 ) ShowSelection("Tablet_08");
		else HideSelection("Tablet_08");
		if ( pillcount >= 9 ) ShowSelection("Tablet_09");
		else HideSelection("Tablet_09");
		if ( pillcount == 10 ) ShowSelection("Tablet_10");
		else HideSelection("Tablet_10");
	}
}
