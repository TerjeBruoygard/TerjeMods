class TerjePlayerModifierHand : TerjePlayerModifierBase
{
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_DETAILED_SANITARY_DISPLAY))
		{
			return;
		}
		
		int handLevel;
		if (player.HasBloodyHands())
		{
			handLevel = 4;
		}
		else
		{
			ItemBase gloves;
			if (ItemBase.CastTo(gloves, player.GetItemOnSlot("Gloves")))
			{
				if (gloves.IsDisinfected())
				{
					handLevel = 1;
				}
				else
				{
					handLevel = 3;
				}
			}
			else if (player.GetTerjeStats().GetDisinfected())
			{
				handLevel = 1;
			}
			else
			{
				handLevel = 2;
			}
		}
		
		player.GetTerjeStats().SetHandLevel(handLevel);
	}
}
