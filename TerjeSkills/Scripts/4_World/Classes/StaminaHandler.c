modded class StaminaConsumers
{
	private float m_terjeMaxStaminaModifier = 1.0;
	
	void SetTerjeMaxStaminaModifier(float value)
	{
		m_terjeMaxStaminaModifier = value;
	}
	
	bool TerjeOverrideConsumerThreshold(EStaminaConsumers consumer, float newValue)
	{
		ref StaminaConsumer sc;
		if ( m_StaminaConsumers.Find(consumer, sc) && sc != null )
		{
			sc.SetActivationThreshold(newValue);
			sc.SetDrainThreshold(newValue);
			return true;
		}
		
		return false;
	}
	
	override bool HasEnoughStaminaFor(EStaminaConsumers consumer, float curStamina, bool isDepleted, float cap)
	{
		return super.HasEnoughStaminaFor(consumer, curStamina * m_terjeMaxStaminaModifier, isDepleted, cap * m_terjeMaxStaminaModifier);
	}
	
	override bool HasEnoughStaminaToStart(EStaminaConsumers consumer, float curStamina, bool isDepleted, float cap)
	{
		return super.HasEnoughStaminaToStart(consumer, curStamina * m_terjeMaxStaminaModifier, isDepleted, cap * m_terjeMaxStaminaModifier);
	}
}

modded class StaminaModifiers
{
	bool TerjeOverrideModifierMinMax(EStaminaModifiers modifier, float minValue, float maxValue)
	{
		ref StaminaModifier sm;
		if ( m_StaminaModifiers.Find(modifier, sm) && sm != null )
		{
			sm.SetMinValue(minValue);
			sm.SetMaxValue(maxValue);
			return true;
		}
		
		return false;
	}
}

modded class StaminaModifier
{
	private float m_terjeModifier = 1.0;
	
	void SetTerjeModifier(float value)
	{
		m_terjeModifier = Math.Clamp(1.0 + value, 0.001, 1.0); //min value of 0 can cause Division by zero
	}
	
	override float GetMinValue()
	{
		return super.GetMinValue() * m_terjeModifier;
	}
	
	override float GetMaxValue()
	{
		return super.GetMaxValue() * m_terjeModifier;
	}
}

modded class StaminaHandler
{
	private float m_terjeMaxStaminaModifier = 1.0;
	private float m_terjeUpdateTimer = 10.0;
	
	override void RegisterStaminaConsumers()
	{
		super.RegisterStaminaConsumers();
		
		float consumeStaminaEvade;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_MELEE_EVOID_STAMINA_MIN, consumeStaminaEvade) && consumeStaminaEvade >= 0)
		{
			m_StaminaConsumers.TerjeOverrideConsumerThreshold(EStaminaConsumers.MELEE_EVADE, consumeStaminaEvade);
		}
	}
	
	override void RegisterStaminaModifiers()
	{
		super.RegisterStaminaModifiers();
		
		float consumeStaminaModMin;
		float consumeStaminaModMax;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_MELEE_EVOID_STAMINA_MIN, consumeStaminaModMin) && consumeStaminaModMin >= 0)
		{
			if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_MELEE_EVOID_STAMINA_MAX, consumeStaminaModMax) && consumeStaminaModMax >= 0)
			{
				m_StaminaModifiers.TerjeOverrideModifierMinMax(EStaminaModifiers.MELEE_EVADE, consumeStaminaModMin, consumeStaminaModMax);
			}
		}
	}
	
	override void Update(float deltaT, int pCurrentCommandID)
	{
		if (m_Player && m_Player.GetTerjeSkills())
		{
			m_terjeUpdateTimer = m_terjeUpdateTimer + deltaT;
			if (m_terjeUpdateTimer >= 10.0)
			{
				m_terjeUpdateTimer = 0;
				
				float athleticSkillModifier;
				if (!m_Player.GetTerjeSkills().GetSkillModifierValue("athlc", "maxstaminamod", athleticSkillModifier))
				{
					athleticSkillModifier = 0;
				}
				
				float athleticPerkModifier;
				if (!m_Player.GetTerjeSkills().GetPerkValue("athlc", "enduring", athleticPerkModifier))
				{
					athleticPerkModifier = 0;
				}
				
				float athleticGlobalStaminaModifier = athleticSkillModifier + athleticPerkModifier; 
				float newMaxStaminaModifier = Math.Max(1.0, athleticGlobalStaminaModifier + 1.0);
				if (m_terjeMaxStaminaModifier != newMaxStaminaModifier)
				{
					m_terjeMaxStaminaModifier = newMaxStaminaModifier;
					
					// Force modifiers recalculation
					m_StaminaDepletionMultiplier = 0;
					m_StaminaRecoveryMultiplier = 0;
					RecalculateDepletionMultiplier();
					RecalculateRecoveryMultiplier();
				}
				
				float jumperPerkModifier;
				if (m_Player.GetTerjeSkills().GetPerkValue("strng", "jumper", jumperPerkModifier))
				{
					m_StaminaModifiers.GetModifierData(EStaminaModifiers.JUMP).SetTerjeModifier(jumperPerkModifier);
					m_StaminaModifiers.GetModifierData(EStaminaModifiers.CLIMB).SetTerjeModifier(jumperPerkModifier);
					m_StaminaModifiers.GetModifierData(EStaminaModifiers.VAULT).SetTerjeModifier(jumperPerkModifier);
				}
				
				float defencePerkModifier;
				if (m_Player.GetTerjeSkills().GetPerkValue("strng", "mrdefence", defencePerkModifier))
				{
					m_StaminaModifiers.GetModifierData(EStaminaModifiers.MELEE_EVADE).SetTerjeModifier(defencePerkModifier);
				}
				
				float lattkspeedPerkModifier;
				if (m_Player.GetTerjeSkills().GetPerkValue("strng", "lattkspeed", lattkspeedPerkModifier))
				{
					m_StaminaModifiers.GetModifierData(EStaminaModifiers.MELEE_LIGHT).SetTerjeModifier(lattkspeedPerkModifier);
				}
				
				float hattkspeedPerkModifier;
				if (m_Player.GetTerjeSkills().GetPerkValue("strng", "hattkspeed", hattkspeedPerkModifier))
				{
					m_StaminaModifiers.GetModifierData(EStaminaModifiers.MELEE_HEAVY).SetTerjeModifier(hattkspeedPerkModifier);
				}
			}
		}

		if (m_StaminaConsumers != null)
		{
			m_StaminaConsumers.SetTerjeMaxStaminaModifier(m_terjeMaxStaminaModifier);
		}
		
		m_StaminaDepletion /= m_terjeMaxStaminaModifier;
		super.Update(deltaT, pCurrentCommandID);
	}
	
	override void SetDepletionMultiplier(float val)
	{
		super.SetDepletionMultiplier(val / m_terjeMaxStaminaModifier);
	}

	override void SetRecoveryMultiplier(float val)
	{
		super.SetRecoveryMultiplier(val / m_terjeMaxStaminaModifier);
	}
	
	override void StaminaProcessor_Move(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Move(pHumanMovementState);
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_SPRINT)
			{
				if (m_StaminaDelta < 0 && m_Player.GetTerjeSkills().GetPerkValue("athlc", "quickf", perkValue))
				{
					m_StaminaDelta *= Math.Clamp(1.0 + perkValue, 0.0, 1.0);
				}
			}
			else if (pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_RUN || pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_WALK)
			{
				if (m_StaminaDelta > 0 && m_Player.GetTerjeSkills().GetPerkValue("athlc", "marathon", perkValue))
				{
					m_StaminaDelta *= Math.Max(1.0 + perkValue, 1.0);
				}
			}
			else if (pHumanMovementState.m_iMovement == DayZPlayerConstants.MOVEMENTIDX_IDLE)
			{
				if (m_StaminaDelta > 0 && m_Player.GetTerjeSkills().GetPerkValue("athlc", "pbreath", perkValue))
				{
					m_StaminaDelta *= Math.Max(1.0 + perkValue, 1.0);
				}
			}		
		}
	}
	
	override void StaminaProcessor_Ladder(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Ladder(pHumanMovementState);
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("athlc", "ladder", perkValue))
			{
				if (m_StaminaDelta < 0)
				{
					m_StaminaDelta *= Math.Clamp(1.0 - perkValue, 0.0, 1.0);
				}
				else if (m_StaminaDelta > 0)
				{
					m_StaminaDelta *= Math.Max(1.0 + perkValue, 1.0);
				}
			}
		}
	}
	
	override void StaminaProcessor_Swimming(HumanMovementState pHumanMovementState)
	{
		super.StaminaProcessor_Swimming(pHumanMovementState);
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("athlc", "swimmer", perkValue))
			{
				if (m_StaminaDelta < 0)
				{
					m_StaminaDelta *= Math.Clamp(1.0 - perkValue, 0.0, 1.0);
				}
				else if (m_StaminaDelta > 0)
				{
					m_StaminaDelta *= Math.Max(1.0 + perkValue, 1.0);
				}
			}
		}
	}
	
	override void SetCooldown(float time, int modifier = -1)
	{
		float terjeCooldownModifier;
		if (GetTerjeSettingFloat(TerjeSettingsCollection.SKILLS_ATHLETIC_COOLDOWN_MODIFIER, terjeCooldownModifier))
		{
			time *= terjeCooldownModifier;
		}
		
		if (m_Player && m_Player.GetTerjeSkills())
		{
			float perkValue;
			if (m_Player.GetTerjeSkills().GetPerkValue("athlc", "npant", perkValue))
			{
				time *= Math.Clamp(1.0 + perkValue, 0.0, 1.0);
			}
		}
		
		// Record old stamina settings
		bool actualStaminaDepleted = m_StaminaDepleted;
		float actualStamina = m_Stamina;
		float synchedStamina = m_StaminaSynced;
		
		// Enable cooldown for depleted stamina
		m_StaminaDepleted = false;
		if (m_Stamina <= 0)
		{
			m_Stamina = 1;
		}
		
		if (m_StaminaSynced <= 0)
		{
			m_StaminaSynced = 1;
		}
		
		// Call base logic
		super.SetCooldown(time, modifier);
		
		// Restore variables
		m_StaminaDepleted = actualStaminaDepleted;
		m_Stamina = actualStamina;
		m_StaminaSynced = synchedStamina;
	}
}