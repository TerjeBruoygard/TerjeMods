modded class JMObjectSpawnerForm
{
	override void OnInit()
	{
		super.OnInit();
		
		foreach (int liquidType, ref LiquidInfo liquidInfo: TerjeCustomLiquids.GetInstance().m_LiquidInfosByType)
		{
			string liquidClsName = liquidInfo.m_LiquidClassName;
			string displayName = liquidInfo.m_LiquidDisplayName;

			if (displayName.IndexOf("#") == 0)
			{
				displayName = Widget.TranslateString(displayName);
			}

			m_ObjItemStateLiquid.Insert(-liquidType);
			m_ObjItemStateLiquidText.Insert(displayName);
		}
	}
	
	override void UpdateItemStateType(int mode, int liquidType = 0)
	{
		if (mode == 0 && liquidType == LIQUID_TERJE_CUSTOM && m_PreviewItem && m_PreviewItem.IsInherited(ItemBase))
		{
			int terjeLiquidType = ItemBase.Cast(m_PreviewItem).GetTerjeCustomLiquidTypeInit();
			if (terjeLiquidType > 0)
			{
				liquidType = -terjeLiquidType;
			}
		}
		
		super.UpdateItemStateType(mode, liquidType);
	}
}