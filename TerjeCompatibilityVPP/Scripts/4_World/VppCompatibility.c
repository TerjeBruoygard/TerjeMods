modded class PermissionManager
{
	override void OnInit()
	{
		AddPermissionType({"TerjePlayerManager"});
		super.OnInit();
	}
}

modded class PlayerBase
{
	override void VPPHealPlayer(bool set_max = true, bool repair_items = true)
	{
		super.VPPHealPlayer(set_max, repair_items);
		
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			GetTerjeAdmintoolSupport().OnHeal(this);
		}
	}
}
