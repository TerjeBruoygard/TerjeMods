modded class ActionLightItemOnFireCB
{
	override void CreateActionComponent()
	{
		super.CreateActionComponent();
		
		float overrideStartingTime = -1;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_SURV_OVERRIDE_START_FIRE_TIME, overrideStartingTime) && overrideStartingTime > 0)
		{
			if (m_ActionData.m_Player && m_ActionData.m_Player.IsAlive() && m_ActionData.m_Player.GetTerjeSkills())
			{
				float modifierValue;
				if (m_ActionData.m_Player.GetTerjeSkills().GetSkillModifierValue("surv", "survfiremod", modifierValue))
				{
					modifierValue = Math.Clamp(1.0 + modifierValue, 0, 1);
				}
				else
				{
					modifierValue = 1.0;
				}
				
				m_ActionData.m_ActionComponent = new CAContinuousTime(Math.Max(1, modifierValue * overrideStartingTime));
			}
		}
	}
}

modded class ActionLightItemOnFire
{
	bool Streatman_CanIgnite(ItemBase item, ItemBase target_item)
	{
		// this makes sure, that the player only gets success XP if the fire actually starts
		if (item && target_item)
		{
			if (item.CanIgniteItem(target_item) && target_item.IsThisIgnitionSuccessful(item))
				return true;
			if (item.CanBeIgnitedBy(target_item) && target_item.IsTargetIgnitionSuccessful(item))
				return true;
		}
		return  false;
	}
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		bool ignitionResult = true;
		ItemBase item = action_data.m_MainItem;
		ItemBase target_item = ItemBase.Cast( action_data.m_Target.GetObject() );
		if (target_item && action_data.m_Player && action_data.m_Player.GetTerjeSkills())
		{
			int expGain;
			float perkValue;
			float absoluteChance = GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_SURV_IGNITE_FIRE_BASE_CHANCE);
			if (action_data.m_Player.GetTerjeSkills().GetPerkValue("surv", "startfire", perkValue))
			{
				absoluteChance += (Math.Clamp(1.0 - absoluteChance, 0, 1) * Math.Clamp(perkValue, 0, 1));
			}
			
			if (TerjeEvent(absoluteChance) && Streatman_CanIgnite(item, target_item))
			{
				ignitionResult = true;
				GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_MAKE_FIRE_SUCCESS_GAIN_EXP, expGain);
			}
			else
			{
				ignitionResult = false;
				GetTerjeSettingInt(TerjeSettingsCollection.SKILLS_SURV_MAKE_FIRE_FAIL_GAIN_EXP, expGain);
			}
			
			if (expGain > 0)
			{
				action_data.m_Player.GetTerjeSkills().AddSkillExperience("surv", expGain);
			}
			
			if (ignitionResult && target_item.IsInherited(FireplaceBase) && action_data.m_Player.GetTerjeSkills().GetPerkValue("surv", "maintngfire", perkValue))
			{
				FireplaceBase.Cast(target_item).SetTerjeSkillSurvFuelModifier( 1.0 + perkValue );
			}
		}
		
		if (ignitionResult)
		{
			super.OnFinishProgressServer(action_data);
		}
		else
		{
			ItemBase ignited_item;
			ItemBase fire_source_item;
			if ( item.CanIgniteItem( target_item ) )
			{
				ignited_item = target_item;
				fire_source_item = item;
			}
			else if ( item.CanBeIgnitedBy( target_item ) )
			{
				ignited_item = item;
				fire_source_item = target_item;			
			}
			
			fire_source_item.OnIgnitedTargetFailed( ignited_item );
			ignited_item.OnIgnitedThisFailed( fire_source_item );	
		}
	}
}
