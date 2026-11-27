class TerjePlayerModifierImmunity : TerjePlayerModifierBase
{
	protected float m_skillExpGainTimer = 0;
	
	override float GetTimeout()
	{
		return 10.0;
	}
	
	override void OnServerFixedTick(PlayerBase player, float deltaTime)
	{
		super.OnServerFixedTick(player, deltaTime);
		
		float gainForce;
		float gainTime;
		float immunity = player.GetTerjeStats().GetInternalImmunity();
		player.GetTerjeStats().GetImmunityGainValue(gainForce, gainTime);
		
		if (gainForce > 0)
		{
			immunity += GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INTIMM_GAIN_MOD) * gainForce * deltaTime * 0.001;
			
			m_skillExpGainTimer += deltaTime;
			if (m_skillExpGainTimer >= 60)
			{
				m_skillExpGainTimer = 0;
				
				if (player.GetTerjeSkills())
				{
					int expGain = GetTerjeSettingInt(TerjeSettingsCollection.MEDICINE_IMMUNITY_VITAMINS_EXP_GAIN);
					if (expGain > 0)
					{
						player.GetTerjeSkills().AddSkillExperience("immunity", expGain);
					}
				}
			}
			
			gainTime = Math.Max(0, gainTime - deltaTime);
			if (gainTime <= 0)
			{
				gainForce = 0;
			}
			
			player.GetTerjeStats().SetImmunityGainValue(gainForce, gainTime);
		}
		else
		{
			immunity -= GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_INTIMM_LOSE_MOD) * 0.001;
		}
		
		player.GetTerjeStats().SetInternalImmunity(immunity);
	}
}
