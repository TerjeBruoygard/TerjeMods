class TerjePlayerModifierHemostatic : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 3;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float hemostaticValue = 0;
		float hemostaticTimer = 0;
		if (player.GetTerjeStats().GetHemostatic(hemostaticValue, hemostaticTimer))
		{			
			if (hemostaticTimer > 0)
			{
				player.GetTerjeStats().SetHemostatic(hemostaticValue, hemostaticTimer - deltaTime);
			}
			else if (hemostaticValue > 0)
			{
				player.GetTerjeStats().SetHemostatic(0, 0);
			}
		}
	}
}