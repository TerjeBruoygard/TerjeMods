class ActionSurgeryVisceraBaseCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		float time = m_ActionData.m_MainItem.GetTerjeSurgeryVisceraTime(m_ActionData.m_Player);
		m_ActionData.m_ActionComponent = new CAContinuousRepeat(Math.Max(time, 1));
	}
}

class ActionSurgeryVisceraSelf : ActionBandageSelf
{	
	void ActionSurgeryVisceraSelf()
	{
		m_CallbackClass 	= ActionSurgeryVisceraBaseCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_STITCHUPSELF;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_SURGERY_SELF";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		return player.HasTerjeVisceraSelf() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (action_data.m_MainItem && target)
		{
			ApplySurgeryViscera(action_data.m_MainItem, target, target);
		}
	}
	
	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		super.OnStartAnimationLoopServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Player);
		if (target && target.GetTerjeStats())
		{
			float pain = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FORCE_SURGERY_PAIN);
			if (target.GetTerjeStats().GetPainValue() < pain)
			{
				target.GetTerjeStats().SetPainValue(pain);
			}
		}
	}
}

class ActionSurgeryVisceraTarget : ActionBandageTarget
{
	void ActionSurgeryVisceraTarget()
	{
		m_CallbackClass 	= ActionSurgeryVisceraBaseCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody 			= true;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;

		m_Text = "#STR_TERJEMED_SURGERY_TARGET";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		PlayerBase otherPlayer = PlayerBase.Cast(target.GetObject());
		if (otherPlayer)
		{
			return otherPlayer.HasTerjeViscera() && (!item.HasQuantity() || !item.IsTerjeEmptyQuantity());
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
				ApplySurgeryViscera(action_data.m_MainItem, target, operator);
			}
		}
	}
	
	override void OnStartAnimationLoopServer( ActionData action_data )
	{
		super.OnStartAnimationLoopServer(action_data);
		
		PlayerBase target = PlayerBase.Cast(action_data.m_Target.GetObject());
		if (target && target.GetTerjeStats())
		{
			float pain = GetTerjeSettingFloat(TerjeSettingsCollection.MEDICINE_VISCERA_FORCE_SURGERY_PAIN);
			if (target.GetTerjeStats().GetPainValue() < pain)
			{
				target.GetTerjeStats().SetPainValue(pain);
			}
		}
	}
}