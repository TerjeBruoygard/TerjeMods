modded class JMESPMeta
{
	UIActionEditableText m_terjeRadiation;
	
	override void CreateActions( Widget parent )
	{
		super.CreateActions(parent);
		
		m_terjeRadiation = UIActionManager.CreateEditableText( parent, "Radiation:" );
		m_terjeRadiation.SetOnlyNumbers( true );
		m_terjeRadiation.Disable();
	}
	
	override void Update()
	{
		super.Update();
		
		if ( m_terjeRadiation && !m_terjeRadiation.IsFocused() && !m_terjeRadiation.IsEdited() )
		{
			float radValue = 0;
			EntityAI targetEntity = EntityAI.Cast(target);
			if (targetEntity)
			{
				radValue = GetTerjeScriptableAreas().GetTerjeRadiationFromEntity(targetEntity);
			}
			
			m_terjeRadiation.SetText( FloatToString( radValue ) );
		}
	}
	
	override void UpdateActions()
	{
		super.UpdateActions();
		
		if ( m_terjeRadiation && !m_terjeRadiation.IsFocused() && !m_terjeRadiation.IsEdited() )
		{
			float radValue = 0;
			EntityAI targetEntity = EntityAI.Cast(target);
			if (targetEntity)
			{
				radValue = GetTerjeScriptableAreas().GetTerjeRadiationFromEntity(targetEntity);
			}
			
			m_terjeRadiation.SetText( FloatToString( radValue ) );
		}
	}
}