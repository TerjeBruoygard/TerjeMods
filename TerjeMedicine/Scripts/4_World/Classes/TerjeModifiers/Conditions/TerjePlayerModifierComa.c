class TerjePlayerModifierComa : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (!player.GetAllowDamage())
		{
			return;
		}
		
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_MEDICAL_COMA))
		{
			return;
		}
		
		if (player.HasActiveTerjeStartScreen())
		{
			return;
		}
		
		if (player.GetTerjeStats() == null)
		{
			return;
		}
		
		bool criticalState = IsPlayerStateCritical(player);
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_KNOCKOUT_TO_COMA))
		{
			float knockoutDelay = player.GetTerjeStats().GetKnockoutDelay();
			if (knockoutDelay >= 0)
			{
				player.GetTerjeStats().SetKnockoutDelay(knockoutDelay - deltaTime);
			}
			
			float knockoutTimerMax = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_KNOCKOUT_TIME_MAX);
			float knockoutTimer = player.GetTerjeStats().GetKnockoutTimer();
			if (knockoutTimer < 0)
			{
				if (knockoutDelay < 0)
				{
					if (!player.GetTerjeIndestructible())
					{
						player.SetTerjeIndestructible(true);
					}
					
					if (criticalState)
					{
						player.GetTerjeStats().SetKnockoutTimer(deltaTime);
						player.GetTerjeStats().SetAdrenalinValue(0);
						player.GetTerjeStats().SetHealthExtraRegenTimer(0);
						player.GetTerjeStats().ResetKnockoutFinisher();
					}
				}
				
				if (criticalState)
				{
					SetPlayerShock(player, TerjeDamageSource.COMA, 0);
				}
			}
			else if ((knockoutTimerMax > 0) && (knockoutTimer > knockoutTimerMax))
			{
				if (player.GetTerjeIndestructible())
				{
					player.SetTerjeIndestructible(false);
				}
				
				player.GetTerjeStats().SetKnockoutTimer(-1);
				SetPlayerHealth(player, TerjeDamageSource.COMA, 0);
				return;
			}
			else if (criticalState)
			{
				SetPlayerShock(player, TerjeDamageSource.COMA, 0);
				player.GetTerjeStats().SetKnockoutTimer(knockoutTimer + deltaTime);
				
				if (knockoutTimer >= GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_KNOCKOUT_TIME_SAFE))
				{
					if (player.GetTerjeStats().GetKnockoutFinisher() >= GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_KNOCKOUT_FINISHER_COUNT))
					{
						if (player.GetTerjeIndestructible())
						{
							player.SetTerjeIndestructible(false);
						}
						
						player.GetTerjeStats().SetKnockoutTimer(-1);
						SetPlayerHealth(player, TerjeDamageSource.COMA, 0);
						return;
					}
				}
				else
				{
					player.GetTerjeStats().ResetKnockoutFinisher();
				}
			}
			else
			{
				if (player.GetTerjeIndestructible())
				{
					SetPlayerHealthMaxFatalZones(player);
					player.SetTerjeIndestructible(false);
				}
				
				player.GetTerjeStats().SetKnockoutTimer(-1);
				player.GetTerjeStats().SetKnockoutDelay(GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_KNOCKOUT_TIME_COOLDOWN));
				player.GetTerjeStats().ResetKnockoutFinisher();
			}
		}
		else if (criticalState && (player.GetTerjeStats().GetAdrenalinValue() <= 0))
		{
			SetPlayerShock(player, TerjeDamageSource.COMA, 0);
		}
	}
	
	void SetPlayerHealthMaxFatalZones(PlayerBase player)
	{
		float health = player.GetTerjeHealth().GetHealth();
		float blood = player.GetTerjeHealth().GetBlood();
		float shock = player.GetTerjeHealth().GetShock();
		
		player.SetFullHealth();
		player.GetTerjeHealth().SetHealth(health, TerjeDamageSource.COMA);
		player.GetTerjeHealth().SetBlood(blood, TerjeDamageSource.COMA);
		player.GetTerjeHealth().SetShock(shock, TerjeDamageSource.COMA);
	}
	
	bool IsPlayerStateCritical(PlayerBase player)
	{
		bool criticalBlood = (GetPlayerBlood(player) < PlayerConstants.SL_BLOOD_CRITICAL);
		bool criticalHealth = (GetPlayerHealth(player) < PlayerConstants.SL_HEALTH_CRITICAL);
		return criticalBlood || criticalHealth;
	}
}
