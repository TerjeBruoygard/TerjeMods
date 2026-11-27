class TerjePlayerModifierHealthGain : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float healthGainTimer = player.GetTerjeStats().GetHealthExtraRegenTimer();
		if (healthGainTimer > 0)
		{
			float gainPower = Math.Clamp(1.0 - GetPlayerHealth01(player), 0, 1);
			float gainPerSec = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_HEALTH_REGEN_MEDS_PER_SEC);
			if (gainPower > 0 && gainPerSec > 0)
			{
				AddPlayerHealth(player, gainPerSec * gainPower * deltaTime);
			}
			
			player.GetTerjeStats().SetHealthExtraRegenTimer(healthGainTimer - deltaTime);
		}
	}
}
