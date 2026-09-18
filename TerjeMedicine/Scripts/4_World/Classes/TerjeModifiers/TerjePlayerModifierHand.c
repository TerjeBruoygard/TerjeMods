class TerjePlayerModifierHand : TerjePlayerModifierBase
{
	private float m_handLastValue = -1;
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_DETAILED_SANITARY_DISPLAY))
		{
			return;
		}
		
		// Hand visual states
		float handCurrentValue = player.GetTerjeStats().GetHandValue(); 
		if (m_handLastValue < 0)
		{
			m_handLastValue = handCurrentValue;
		}
		
		int handTendency = 0;
		int handLevel = 0;

		if      (handCurrentValue < TerjeMedicineConstants.HAND_LEVEL4) handLevel = 4;
		else if (handCurrentValue < TerjeMedicineConstants.HAND_LEVEL3) handLevel = 3;
		else if (handCurrentValue < TerjeMedicineConstants.HAND_LEVEL2) handLevel = 2;
		else                                                            handLevel = 1;
		
		player.GetTerjeStats().SetHandLevelAndTendency(handLevel, handTendency);
		m_handLastValue = handCurrentValue;
		
		// Hand action states
		ItemBase gloves;
		if (ItemBase.CastTo(gloves, player.GetItemOnSlot("Gloves")))
		{
			if (gloves.IsDisinfected())
			{
				handCurrentValue = 3;
			}
			else handCurrentValue = 1;
		}
		else if (player.GetTerjeStats().GetDisinfected() >= 1)
		{
			handCurrentValue = 3;
		}
		else if (player.HasBloodyHands())
		{
			handCurrentValue = 0;
		}
		else handCurrentValue = 2;
		
		player.GetTerjeStats().SetHandValue(handCurrentValue);
	}
}
