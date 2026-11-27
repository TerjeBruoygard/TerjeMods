class TerjePlayerModifierBloodRegen : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float bloodRegenValue = 0;
		float bloodRegenTimer = 0;
		if (player.GetTerjeStats().GetBloodRegen(bloodRegenValue, bloodRegenTimer))
		{
			if (bloodRegenTimer > 0)
			{
				player.GetTerjeStats().SetBloodRegen(bloodRegenValue, bloodRegenTimer - deltaTime);
			}
			else if (bloodRegenValue > 0)
			{
				player.GetTerjeStats().SetBloodRegen(0, 0);
			}
		}
		
		if (bloodRegenValue > 0)
		{
			float bloodRegenMedsModifier = 1;
			GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BLOOD_REGEN_MEDS_MODIFIER, bloodRegenMedsModifier);
			player.GetTerjeHealth().AddBlood(bloodRegenValue * bloodRegenMedsModifier * deltaTime);
		}
	}
}
