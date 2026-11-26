class ActionSurgeryBulletBaseCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = m_ActionData.m_MainItem.GetTerjeSurgeryBulletTime(m_ActionData.m_Player);
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(time, 1));
	}
}

class ActionSurgeryBulletSelf : ActionBandageSelf
{	
	void ActionSurgeryBulletSelf()
	{
		m_CallbackClass 	= ActionSurgeryBulletBaseCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_STITCHUPSELF;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_SURBULLET_SELF";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return player.HasTerjeBulletWoundsSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			ApplySurgeryBullet(action_data.m_MainItem, target, target);
		}
	}
	
	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		super.OnStartAnimationLoopServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (target && target.GetTerjeStats())
		{
			float pain = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FORCE_SURGERY_PAIN);
			if (target.GetTerjeStats().GetPainValue() < pain)
			{
				target.GetTerjeStats().SetPainValue(pain);
			}
		}
	}
}

class ActionSurgeryBulletTarget : ActionBandageTarget
{
	void ActionSurgeryBulletTarget()
	{
		m_CallbackClass 	= ActionSurgeryBulletBaseCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_SURBULLET_TARGET";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (otherPlayer)
		{
			return otherPlayer.HasTerjeBulletWounds() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase operator = PlayerBase.Cast(action_data.m_Player);
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		
		if (action_data.m_MainItem && target && operator)
		{
			if (CanReceiveAction(action_data.m_Target))
			{
				ApplySurgeryBullet(action_data.m_MainItem, target, operator);
			}
		}
	}
	
	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		super.OnStartAnimationLoopServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (target && target.GetTerjeStats())
		{
			float pain = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_BULLETS_FORCE_SURGERY_PAIN);
			if (target.GetTerjeStats().GetPainValue() < pain)
			{
				target.GetTerjeStats().SetPainValue(pain);
			}
		}
	}
}