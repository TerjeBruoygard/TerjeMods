modded class JMObjectSpawnerProperties
{
	override void CollectLiquids( string classname, ItemBase item, out array<string> labels )
	{
		super.CollectLiquids(classname, item, labels);
		
		if (!item || item.IsBloodContainer())
			return;
		
		int initTerje = item.GetTerjeCustomLiquidTypeInit();
		if (initTerje > 0 && labels.Count() > 0)
		{
			string initName = TerjeCustomLiquids.GetInstance().GetDisplayName(initTerje);
			if (initName.IndexOf("#") == 0)
				initName = Widget.TranslateString(initName);
			
			labels.Set(0, DefaultLabel(initName));
		}
		
		foreach (int liquidType, ref LiquidInfo liquidInfo : TerjeCustomLiquids.GetInstance().m_LiquidInfosByType)
		{
			if (liquidType == initTerje)
				continue;
			
			string displayName = liquidInfo.m_LiquidDisplayName;
			if (displayName.IndexOf("#") == 0)
				displayName = Widget.TranslateString(displayName);
			
			m_LiquidValues.Insert(-liquidType);
			labels.Insert(displayName);
		}
	}
	
	override void Click_SetLiquid( UIEvent eid, UIActionBase action )
	{
		super.Click_SetLiquid(eid, action);
		
		if (eid != UIEvent.CHANGE || m_LiquidValue >= 0)
			return;
		
		ItemBase preview = ItemBase.Cast(m_Form.GetPreviewItem());
		if (preview)
			preview.SetTerjeLiquidType(-m_LiquidValue, true);
	}
}
