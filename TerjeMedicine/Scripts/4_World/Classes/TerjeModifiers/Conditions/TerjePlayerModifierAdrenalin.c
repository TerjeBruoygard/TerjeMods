class TerjePlayerModifierAdrenalin : TerjePlayerModifierBase
{
	override float GetTimeout()
	{
		return 1;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ADRENALIN_ENABLED) == false)
		{
			player.GetTerjeStats().SetAdrenalinValue(0);
			return;
		}
		
		float adrenalineTimer = player.GetTerjeStats().GetAdrenalinValue();
		if (adrenalineTimer > 0)
		{
			bool reviveFromKnockout = false;
			if (player.GetTerjeStats().IsInKnockout())
			{
				if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_KNOCKOUT_REVIVE_BY_ADR))
				{
					reviveFromKnockout = true;
				}
				else
				{
					return;
				}
			}
			
			player.GetTerjeStats().SetAdrenalinValue(adrenalineTimer - deltaTime);
			
			if (!player.GetModifiersManager().IsModifierActive(eModifiers.MDF_EPINEPHRINE))
			{
				player.GetModifiersManager().ActivateModifier( eModifiers.MDF_EPINEPHRINE );
			}
			
			if (!player.GetStaminaHandler().ContainsDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE))
			{
				if (reviveFromKnockout)
				{
					if (player.GetTerjeHealth().GetHealth() < PlayerConstants.SL_HEALTH_LOW)
					{
						player.GetTerjeHealth().SetHealth(PlayerConstants.SL_HEALTH_LOW, TerjeDamageSource.COMA);
					}
					
					if (player.GetTerjeHealth().GetBlood() < PlayerConstants.SL_BLOOD_LOW)
					{
						player.GetTerjeHealth().SetBlood(PlayerConstants.SL_BLOOD_LOW, TerjeDamageSource.COMA);
					}
				}
				
				player.GiveShock(100);
				player.GetStaminaHandler().SetStamina(100);
				player.GetStaminaHandler().ActivateDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE);
			}
		}
		else
		{
			if (player.GetStaminaHandler().ContainsDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE))
			{
				player.GetStaminaHandler().DeactivateDepletionModifier(EStaminaMultiplierTypes.EPINEPHRINE);
			}
			
			if (player.GetModifiersManager().IsModifierActive(eModifiers.MDF_EPINEPHRINE))
			{
				player.GetModifiersManager().DeactivateModifier( eModifiers.MDF_EPINEPHRINE );
			}
		}
	}
}

modded class StaminaHandler
{
	bool ContainsDepletionModifier(EStaminaMultiplierTypes type)
	{
		return m_ActiveDepletionModifiers.Find(type) != -1;
	}
	
	bool ContainsRecoveryModifier(EStaminaMultiplierTypes type)
	{
		return m_ActiveRecoveryModifiers.Find(type) != -1;
	}
}
