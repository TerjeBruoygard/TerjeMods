modded class Edible_Base
{
	override int TerjeOverrideDescriptionByConsumableEffects()
	{
		if (g_Game.IsClient())
		{
			PlayerBase player = PlayerBase.Cast( g_Game.GetPlayer() );
			if (player && player.GetTerjeSkills())
			{
				if ((!GetTerjeGameConfig().ConfigGetBool("CfgVehicles " + GetType() + " medicalPillsCategory")) && player.GetTerjeSkills().GetPerkLevel("surv", "expert") > 0)
				{
					return 2;
				}
			}
		}
		
		return super.TerjeOverrideDescriptionByConsumableEffects();
	}
}