modded class TerjeConsumableEffects
{
	const string COLOR_RED = "<color rgba='198,59,64,255'>";
	const string COLOR_YELLOW = "<color rgba='255,215,0,255'>";
	const string COLOR_GREEN = "<color rgba='97,215,124,255'>";
	const string COLOR_END = "</color>";
	const string NEXT_LINE = "<br/>";
	
	private string TimeValue(float value)
	{
		return COLOR_END + "(" + (int)(value) + "sec)" + NEXT_LINE;
	}
	private string LevelValue(float value)
	{
		return COLOR_END + "(" + (int)(value) + "lvl)" + NEXT_LINE;
	}
	private string NoValue()
	{
		return COLOR_END + NEXT_LINE;
	}
	private string TimeIncreaseValue(float value)
	{
		return COLOR_END + "(+" + (int)(value) + "sec)" + NEXT_LINE;
	}
	private string PercentIncreaseValue(float value)
	{
		return "+" + (int)(value * 100) + "%" + COLOR_END + NEXT_LINE;
	}
	
	
	override void Apply(EntityAI entity, string classname, PlayerBase player, float amount)
	{
		super.Apply(entity, classname, player, amount);
		
		float timeModifier;
		if (player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkValue("med", "pharmac", timeModifier))
		{
			timeModifier = 1.0 + timeModifier;
		}
		else
		{
			timeModifier = 1.0;
		}
		
		if (player && player.GetTerjeStats())
			{
				float overdosedIncrement = GetTerjeGameConfig().ConfigGetFloat( classname + " overdosedIncrement" );
				if (overdosedIncrement > 0)
				{
					player.GetTerjeStats().SetOverdoseValue(player.GetTerjeStats().GetOverdoseValue() + (overdosedIncrement * amount));
				}
				
				float biohazardIncrement = GetTerjeGameConfig().ConfigGetFloat( classname + " biohazardIncrement" );
				if (biohazardIncrement > 0)
				{
					player.GetTerjeStats().SetBiohazardValue(player.GetTerjeStats().GetBiohazardValue() + (biohazardIncrement * amount));
				}
				
				int medPainkillerLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medPainkillerLevel" );
				if (medPainkillerLevel > 0)
				{
					if (medPainkillerLevel < 3 && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("med", "anestlog") > 0)
					{
						medPainkillerLevel = medPainkillerLevel + 1;
					}
					
					int activePainkillerLevel = 0;
					float activePainkillerTime = 0;
					player.GetTerjeStats().GetPainkiller(activePainkillerLevel, activePainkillerTime);
					
					float medPainkillerTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medPainkillerTimeSec" );
					if (medPainkillerLevel >= activePainkillerLevel && medPainkillerTimeSec > 0)
					{
						int medPainkillerMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medPainkillerMaxTimeSec" );
						if (medPainkillerMaxTimeSec <= 0)
						{
							medPainkillerMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetPainkiller(medPainkillerLevel, Math.Min(medPainkillerMaxTimeSec, activePainkillerTime + (medPainkillerTimeSec * amount * timeModifier)));
					}
				}
				
				float medHealthgenTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medHealthgainTimeSec" );
				if (medHealthgenTimeSec > 0)
				{
					int medHealthgenMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medHealthgainMaxTimeSec" );
					if (medHealthgenMaxTimeSec <= 0)
					{
						medHealthgenMaxTimeSec = 1800;
					}
					
					float medHealthgenActualTime = player.GetTerjeStats().GetHealthExtraRegenTimer();
					player.GetTerjeStats().SetHealthExtraRegenTimer(Math.Min(medHealthgenMaxTimeSec, medHealthgenActualTime + (medHealthgenTimeSec * amount * timeModifier)));
				}
				
				int medAntipoisonLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntipoisonLevel" );
				if (medAntipoisonLevel > 0)
				{
					int activeAntipoisonLevel = 0;
					float activeAntipoisonTime = 0;
					player.GetTerjeStats().GetAntipoison(activeAntipoisonLevel, activeAntipoisonTime);
					
					float medAntipoisonTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntipoisonTimeSec" );
					if (medAntipoisonLevel >= activeAntipoisonLevel && medAntipoisonTimeSec > 0)
					{
						int medAntipoisonMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medAntipoisonMaxTimeSec" );
						if (medAntipoisonMaxTimeSec <= 0)
						{
							medAntipoisonMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetAntipoison(medAntipoisonLevel, Math.Min(medAntipoisonMaxTimeSec, activeAntipoisonTime + (medAntipoisonTimeSec * amount * timeModifier)));
					}
				}
				
				int medAntibiohazardLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibiohazardLevel" );
				if (medAntibiohazardLevel > 0)
				{
					int activeAntibiohazardLevel = 0;
					float activeAntibiohazardTime = 0;
					player.GetTerjeStats().GetAntibiohazard(activeAntibiohazardLevel, activeAntibiohazardTime);
					
					float medAntibiohazardTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntibiohazardTimeSec" );
					if (medAntibiohazardLevel >= activeAntibiohazardLevel && medAntibiohazardTimeSec > 0)
					{
						int medAntibiohazardMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibiohazardMaxTimeSec" );
						if (medAntibiohazardMaxTimeSec <= 0)
						{
							medAntibiohazardMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetAntibiohazard(medAntibiohazardLevel, Math.Min(medAntibiohazardMaxTimeSec, activeAntibiohazardTime + (medAntibiohazardTimeSec * amount * timeModifier)));
					}
				}
				
				int medAntibioticLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibioticLevel" );
				if (medAntibioticLevel > 0)
				{
					if (medAntibioticLevel < 3 && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("med", "expantib") > 0)
					{
						medAntibioticLevel = medAntibioticLevel + 1;
					}
					
					int activeAntibioticLevel = 0;
					float activeAntibioticTime = 0;
					player.GetTerjeStats().GetAntibiotic(activeAntibioticLevel, activeAntibioticTime);
					
					float medAntibioticsTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntibioticsTimeSec" );
					if (medAntibioticLevel >= activeAntibioticLevel && medAntibioticsTimeSec > 0)
					{
						int medAntibioticsMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibioticsMaxTimeSec" );
						if (medAntibioticsMaxTimeSec <= 0)
						{
							medAntibioticsMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetAntibiotic(medAntibioticLevel, Math.Min(medAntibioticsMaxTimeSec, activeAntibioticTime + (medAntibioticsTimeSec * amount * timeModifier)));
					}
				}
				
				int medRabiesAntibioticLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medRabiesAntibioticLevel" );
				if (medRabiesAntibioticLevel > 0)
				{
					if (medRabiesAntibioticLevel < 3 && player && player.GetTerjeSkills() && player.GetTerjeSkills().GetPerkLevel("med", "expantib") > 0)
					{
						medRabiesAntibioticLevel = medRabiesAntibioticLevel + 1;
					}
					
					int activeRabiesAntibioticLevel = 0;
					float activeRabiesAntibioticTime = 0;
					player.GetTerjeStats().GetRabiesCure(activeRabiesAntibioticLevel, activeRabiesAntibioticTime);
					
					float medRabiesAntibioticsTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medRabiesAntibioticTimeSec" );
					if (medRabiesAntibioticLevel >= activeRabiesAntibioticLevel && medRabiesAntibioticsTimeSec > 0)
					{
						int medRabiesAntibioticsMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medRabiesAntibioticMaxTimeSec" );
						if (medRabiesAntibioticsMaxTimeSec <= 0)
						{
							medRabiesAntibioticsMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetRabiesCure(medRabiesAntibioticLevel, Math.Min(medRabiesAntibioticsMaxTimeSec, activeRabiesAntibioticTime + (medRabiesAntibioticsTimeSec * amount * timeModifier)));
					}
				}
				
				float medZAntidotTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medZAntidotTimeSec" );
				if (medZAntidotTimeSec > 0)
				{
					int medZAntidotMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medZAntidotMaxTimeSec" );
					if (medZAntidotMaxTimeSec <= 0)
					{
						medZAntidotMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetZAntidotValue(Math.Min(medZAntidotMaxTimeSec, player.GetTerjeStats().GetZAntidotValue() + (medZAntidotTimeSec * amount * timeModifier)));
				}
				
				float medAntisepsis = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntisepsisTimeSec" );
				if (medAntisepsis > 0)
				{
					int medAntisepsisMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medAntisepsisMaxTimeSec" );
					if (medAntisepsisMaxTimeSec <= 0)
					{
						medAntisepsisMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAntisepsisValue(Math.Min(medAntisepsisMaxTimeSec, player.GetTerjeStats().GetAntisepsisValue() + (medAntisepsis * amount * timeModifier)));
				}
				
				float medConcussionHealTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medConcussionHealTimeSec" );
				if (medConcussionHealTime > 0)
				{
					int medConcussionHealMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medConcussionHealMaxTimeSec" );
					if (medConcussionHealMaxTimeSec <= 0)
					{
						medConcussionHealMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetContusionHealValue(Math.Min(medConcussionHealMaxTimeSec, player.GetTerjeStats().GetContusionHealValue() + (medConcussionHealTime * amount * timeModifier)));
				}
				
				float medBloodHemostaticValue = GetTerjeGameConfig().ConfigGetInt( classname + " medBloodHemostaticValue" );
				if (medBloodHemostaticValue > 0)
				{
					int activeHemostaticValue = 0;
					float activeHemostaticTime = 0;
					player.GetTerjeStats().GetHemostatic(activeHemostaticValue, activeHemostaticTime);
					
					float medHemostaticTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodHemostaticTimeSec" );
					if (medBloodHemostaticValue >= activeHemostaticValue && medHemostaticTimeSec > 0)
					{
						int medHemostaticMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medBloodHemostaticMaxTimeSec" );
						if (medHemostaticMaxTimeSec <= 0)
						{
							medHemostaticMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetHemostatic(medBloodHemostaticValue, Math.Min(medHemostaticMaxTimeSec, activeHemostaticTime + (medHemostaticTimeSec * amount * timeModifier)));
					}	
				}
				
				float medBloodRegenValue = GetTerjeGameConfig().ConfigGetInt( classname + " medBloodRegenValue" );
				if (medBloodRegenValue > 0)
				{
					int activeRegenValue = 0;
					float activeRegenTime = 0;
					player.GetTerjeStats().GetBloodRegen(activeRegenValue, activeRegenTime);
					
					float medRegenTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodRegenTimeSec" );
					if (medBloodRegenValue >= activeRegenValue && medRegenTimeSec > 0)
					{
						int medRegenMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medBloodRegenMaxTimeSec" );
						if (medRegenMaxTimeSec <= 0)
						{
							medRegenMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetBloodRegen(medBloodRegenValue, Math.Min(medRegenMaxTimeSec, activeRegenTime + (medRegenTimeSec * amount * timeModifier)));
					}	
				}
				
				float medHematomaHealTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medHematomaHealTimeSec" );
				if (medHematomaHealTimeSec > 0)
				{
					int medHematomaHealMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medHematomaHealMaxTimeSec" );
					if (medHematomaHealMaxTimeSec <= 0)
					{
						medHematomaHealMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetSalveValue(Math.Min(medHematomaHealMaxTimeSec, player.GetTerjeStats().GetSalveValue() + (medHematomaHealTimeSec * amount * timeModifier)));
				}
				
				float medAdrenalinTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAdrenalinTimeSec" );
				if (medAdrenalinTimeSec > 0)
				{
					int medAdrenalinMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medAdrenalinMaxTimeSec" );
					if (medAdrenalinMaxTimeSec <= 0)
					{
						medAdrenalinMaxTimeSec = 1800;
					}
					
					player.GetTerjeStats().SetAdrenalinValue(Math.Min(medAdrenalinMaxTimeSec, player.GetTerjeStats().GetAdrenalinValue() + (medAdrenalinTimeSec * amount * timeModifier)));
					player.GetStaminaHandler().SetStamina( player.GetStaminaHandler().GetStaminaMax() );
				}
				
				int medAntidepLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntidepresantLevel" );
				if (medAntidepLevel > 0)
				{
					int activeAntidepValue = 0;
					float activeAntidepTime = 0;
					player.GetTerjeStats().GetAntidepresant(activeAntidepValue, activeAntidepTime);
					
					float medAntidepTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntidepresantTimer" );
					if (medAntidepLevel >= activeAntidepValue && medAntidepTimeSec > 0)
					{
						int medAntidepMaxTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medAntidepresantMaxTimer" );
						if (medAntidepMaxTimeSec <= 0)
						{
							medAntidepMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetAntidepresant(medAntidepLevel, Math.Min(medAntidepMaxTimeSec, activeAntidepTime + (medAntidepTimeSec * amount * timeModifier)));
					}
				}
				
				float medMindDegradationForce = GetTerjeGameConfig().ConfigGetFloat( classname + " medMindDegradationForce" );
				if (medMindDegradationForce > 0)
				{
					float medMindDegradationTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medMindDegradationTime" );
					if (medMindDegradationTime > 0)
					{
						player.GetTerjeStats().AddMindDegradation(medMindDegradationForce, medMindDegradationTime * amount);
					}
				}
				
				float medSleepingIncTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medSleepingIncrementTimeSec" );
				if (medSleepingIncTime > 0)
				{
					float medSleepingIncValue = GetTerjeGameConfig().ConfigGetFloat( classname + " medSleepingIncrementValue" );
					if (medSleepingIncValue > 0)
					{
						player.GetTerjeStats().AddSleepingIncrement(medSleepingIncValue, medSleepingIncTime * amount);
					}
					else if (medSleepingIncValue < 0)
					{
						player.GetTerjeStats().AddSleepingDecrement(Math.AbsFloat(medSleepingIncValue), medSleepingIncTime * amount);
					}
				}
				
				float medInfluenzaVacineTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medInfluenzaVacineTime" );
				if (medInfluenzaVacineTime > 0)
				{
					player.GetTerjeStats().SetInfluenzaVacineValue(medInfluenzaVacineTime * amount * timeModifier);
				}
				
				float medZVirusVacineTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medZVirusVacineTime" );
				if (medZVirusVacineTime > 0)
				{
					player.GetTerjeStats().SetZVirusVacineValue(medZVirusVacineTime * amount * timeModifier);
				}
				
				float medRabiesVacineTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medRabiesVacineTime" );
				if (medRabiesVacineTime > 0)
				{
					player.GetTerjeStats().SetRabiesVacineValue(medRabiesVacineTime * amount * timeModifier);
				}
				
				float medImmunityGainForce = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainForce" );
				if (medImmunityGainForce > 0)
				{
					float activeImmmunityGainForce = 0;
					float activeImmunityGainTime = 0;
					player.GetTerjeStats().GetImmunityGainValue(activeImmmunityGainForce, activeImmunityGainTime);
					
					float medImmunityGainTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainTimeSec" );
					if (medImmunityGainForce >= activeImmmunityGainForce && medImmunityGainTimeSec > 0)
					{
						float medImmunityGainMaxTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainMaxTimer" );
						if (medImmunityGainMaxTimeSec <= 0)
						{
							medImmunityGainMaxTimeSec = 1800;
						}
						
						player.GetTerjeStats().SetImmunityGainValue(medImmunityGainForce, Math.Min(medImmunityGainMaxTimeSec, activeImmunityGainTime + (medImmunityGainTimeSec * amount * timeModifier)));
					}
				}
				
				// Negative effects
				float medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medHematomasIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetHematomas(player.GetTerjeStats().GetHematomas() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medContussionLight");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_LIGHT);
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medContussionHeavy");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetContusionValue(TerjeMedicineConstants.CONTUSION_HEAVY);
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medFoodPoisonIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetPoisonValue(player.GetTerjeStats().GetPoisonValue() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medChemicalPoisonIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetBiohazardValue(player.GetTerjeStats().GetBiohazardValue() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medInfuenzaInfectionIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetInfluenzaValue(player.GetTerjeStats().GetInfluenzaValue() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medZombieVirusIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetZVirusValue(player.GetTerjeStats().GetZVirusValue() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medSepsisInfectionIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetSepsisValue(player.GetTerjeStats().GetSepsisValue() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medRabiesVirusIncrement");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetRabiesValue(player.GetTerjeStats().GetRabiesValue() + (medDmgValue * amount));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medPsiDamageValue");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().AddMindDegradation(medDmgValue, GetTerjeGameConfig().ConfigGetFloat(classname + " medPsiDamageTime"));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medSleepDamageValue");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().AddSleepingDecrement(medDmgValue, GetTerjeGameConfig().ConfigGetFloat(classname + " medSleepDamageTime"));
				}
				
				medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medPainSet");
				if (medDmgValue > 0)
				{
					player.GetTerjeStats().SetPainValue(medDmgValue);
				}
		}
	}
	
	override string Describe(EntityAI entity, string classname)
	{
		string result = super.Describe(entity, classname);
		float overdosedIncrement = GetTerjeGameConfig().ConfigGetFloat( classname + " overdosedIncrement" );
		if (overdosedIncrement > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_OVERDOSE " + COLOR_RED + PercentIncreaseValue(overdosedIncrement);
		}
		
		float biohazardIncrement = GetTerjeGameConfig().ConfigGetFloat( classname + " biohazardIncrement" );
		if (biohazardIncrement > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_BIOHAZARD " + COLOR_RED + PercentIncreaseValue(biohazardIncrement);
		}
		
		int medPainkillerLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medPainkillerLevel" );
		float medPainkillerTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medPainkillerTimeSec" );
		if (medPainkillerLevel > 0 && medPainkillerTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_PAINKILLER " + COLOR_GREEN + medPainkillerLevel + TimeValue(medPainkillerTimeSec);
		}
		
		int medAntipoisonLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntipoisonLevel" );
		float medAntipoisonTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntipoisonTimeSec" );
		if (medAntipoisonLevel > 0 && medAntipoisonTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIPOISON " + COLOR_GREEN + medAntipoisonLevel + TimeValue(medAntipoisonTimeSec);
		}
		
		int medAntibiohazardLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibiohazardLevel" );
		float medAntibiohazardTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntibiohazardTimeSec" );
		if (medAntibiohazardLevel > 0 && medAntibiohazardTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIBIOHAZARD " + COLOR_GREEN + medAntibiohazardLevel + TimeValue(medAntibiohazardTimeSec);
		}
		
		int medAntibioticLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntibioticLevel" );
		float medAntibioticsTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntibioticsTimeSec" );
		if (medAntibioticLevel > 0 && medAntibioticsTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIBIOTIC " + COLOR_GREEN + medAntibioticLevel + TimeValue(medAntibioticsTimeSec);			
		}
		
		int medRabiesAntibioticLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medRabiesAntibioticLevel" );
		float medRabiesAntibioticsTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medRabiesAntibioticTimeSec" );
		if (medRabiesAntibioticLevel > 0 && medRabiesAntibioticsTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_RABIESCURE " + COLOR_GREEN + medRabiesAntibioticLevel + TimeValue(medRabiesAntibioticsTimeSec);			
		}
		
		float medZAntidotTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medZAntidotTimeSec" );
		if (medZAntidotTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_ZANTIDOT " + TimeValue(medZAntidotTimeSec);
		}
		
		float medAntisepsis = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntisepsisTimeSec" );
		if (medAntisepsis > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_ANTISEPSIS " + TimeValue(medAntisepsis);
		}
		
		float medConcussionHealTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medConcussionHealTimeSec" );
		if (medConcussionHealTime > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_CONTUSIONCURE " + TimeValue(medConcussionHealTime);
		}
		
		float medBloodHemostaticValue = GetTerjeGameConfig().ConfigGetInt( classname + " medBloodHemostaticValue" );
		float medHemostaticTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodHemostaticTimeSec" );
		if (medBloodHemostaticValue > 0 && medHemostaticTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_HEMOSTATIC " + TimeValue(medHemostaticTimeSec);
		}
		
		float medBloodRegenValue = GetTerjeGameConfig().ConfigGetInt( classname + " medBloodRegenValue" );
		float medRegenTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medBloodRegenTimeSec" );
		if (medBloodRegenValue > 0 && medRegenTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_BLOODREGEN " + TimeValue(medRegenTimeSec);
		}
		
		float medHematomaHealTimeSec = GetTerjeGameConfig().ConfigGetInt( classname + " medHematomaHealTimeSec" );
		if (medHematomaHealTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_HEMATOMA " + TimeIncreaseValue(medHematomaHealTimeSec);
		}
		
		float medAdrenalinTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAdrenalinTimeSec" );
		if (medAdrenalinTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_ADRENALIN " + TimeValue(medAdrenalinTimeSec);
		}
		
		int medAntidepLevel = GetTerjeGameConfig().ConfigGetInt( classname + " medAntidepresantLevel" );
		float medAntidepTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medAntidepresantTimer" );
		if (medAntidepLevel > 0 && medAntidepTimeSec > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_ANTIDEPRESANT " + COLOR_GREEN + medAntidepLevel + TimeValue(medAntidepTimeSec);			
		}
		
		float medInfluenzaVacineTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medInfluenzaVacineTime" );
		if (medInfluenzaVacineTime > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_INFVACINE " + TimeValue(medInfluenzaVacineTime);
		}
		
		float medZVirusVacineTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medZVirusVacineTime" );
		if (medZVirusVacineTime > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_ZEDVACINE " + TimeValue(medZVirusVacineTime);
		}
		
		float rabiesVacineTime = GetTerjeGameConfig().ConfigGetFloat( classname + " medRabiesVacineTime" );
		if (rabiesVacineTime > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_RABIESVACCINE " + TimeValue(rabiesVacineTime);
		}
		
		float medImmunityGainForce = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainForce" );
		float medImmunityGainTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medImmunityGainTimeSec" );
		TerjeLog_Info("medImmunityGainForce=" + medImmunityGainForce + "; medImmunityGainTimeSec=" + medImmunityGainTimeSec);
		if (medImmunityGainForce > 0 && medImmunityGainTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_IMMUNGAIN " + TimeValue(medImmunityGainTimeSec);
		}
		
		float medHealthgenTimeSec = GetTerjeGameConfig().ConfigGetFloat( classname + " medHealthgainTimeSec" );
		if (medHealthgenTimeSec > 0)
		{
			result = result + COLOR_YELLOW + "#STR_TERJEMED_EFFECT_HEALTHREGEN " + TimeValue(medHealthgenTimeSec);
		}
		
		// Negative effects
		float medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medHematomasIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_HEMATOMA " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medContussionLight");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_CONTLIGHT " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medContussionHeavy");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_CONTHEAVY " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medFoodPoisonIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_FOODPOISON " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medChemicalPoisonIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_CHEMPOISON " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medInfuenzaInfectionIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_INFLUENZA " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medZombieVirusIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_ZOMBIE " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medSepsisInfectionIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_SEPSIS " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medRabiesVirusIncrement");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_RABIES " + NoValue();
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medPsiDamageTime");
		if (medDmgValue > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_DMG_PSI " + COLOR_RED + TimeValue(medDmgValue);	
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medSleepDamageTime");
		if (medDmgValue > 0)
		{
			result = result + "#STR_TERJEMED_EFFECT_DMG_SLEEP " + COLOR_RED + TimeValue(medDmgValue);	
		}
		
		medDmgValue = GetTerjeGameConfig().ConfigGetFloat(classname + " medPainSet");
		if (medDmgValue > 0)
		{
			result = result + COLOR_RED + "#STR_TERJEMED_EFFECT_DMG_PAIN " + LevelValue(medDmgValue);
		}
		
		return result;
	}
}