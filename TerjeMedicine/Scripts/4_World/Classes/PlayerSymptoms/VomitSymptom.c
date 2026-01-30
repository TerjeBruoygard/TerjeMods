modded class VomitSymptom
{
	override void OnGetActivatedServer(PlayerBase player)
	{
		super.OnGetActivatedServer(player);
		
		if (player && player.IsFaceBlocked(true) && GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_MASK_DROP))
		{
			ItemBase itemCheck = player.GetItemOnSlot("Mask");
			if (!itemCheck)
			{
				itemCheck = player.GetItemOnSlot("Headgear");
			}
			
			if (itemCheck)
			{
				player.GetInventory().DropEntity(InventoryMode.SERVER, player, itemCheck);
			}
		}
	}
	
	override bool IsContaminationActive()
	{
		return (m_Player.GetTerjeStats().GetBiohazardLevel() >= 2);
	}
}
