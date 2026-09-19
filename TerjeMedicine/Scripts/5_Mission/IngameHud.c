modded class IngameHud
{
	int TERJE_NOTIFIER_SLEEPING = -1;
	int TERJE_NOTIFIER_MIND = -1;
	int TERJE_NOTIFIER_HAND = -1;
	
	int TERJE_BADGE_BULLETWOUND = -1;
	int TERJE_BADGE_VISCERA = -1;
	int TERJE_BADGE_PAIN = -1;
	int TERJE_BADGE_OVERDOSE = -1;
	int TERJE_BADGE_STUBWOUND = -1;
	int TERJE_BADGE_HEMATOMA = -1;
	int TERJE_BADGE_CONTUSION = -1;
	int TERJE_BADGE_ZVIRUS = -1;
	int TERJE_BADGE_SEPSIS = -1;
	int TERJE_BADGE_INFLUENZA = -1;
	int TERJE_BADGE_POISON = -1;
	int TERJE_BADGE_BIOHAZARD = -1;
	int TERJE_BADGE_RABIES = -1;
	
	int TERJE_BADGE_ANTIPOISON = -1;
	int TERJE_BADGE_SALVE = -1;
	int TERJE_BADGE_PAINKILLER = -1;
	int TERJE_BADGE_HEMOSTATIC = -1;
	int TERJE_BADGE_BLOODREGEN = -1;
	int TERJE_BADGE_DISINFECTED = -1;
	int TERJE_BADGE_BANDAGED_CLEAN = -1;
	int TERJE_BADGE_BANDAGED_DIRTY = -1;
	int TERJE_BADGE_SUTURES_CLEAN = -1;
	int TERJE_BADGE_SUTURES_DIRTY = -1;
	int TERJE_BADGE_ANTIDEPRESANT = -1;
	int TERJE_BADGE_ANTIBIOTIC = -1;
	int TERJE_BADGE_ANTISEPSIS = -1;
	int TERJE_BADGE_Z_ANTIDOT = -1;
	int TERJE_BADGE_ADRENALIN = -1;
	int TERJE_BADGE_CONTUSSIONHEAL = -1;
	int TERJE_BADGE_ANTIBIOHAZARD = -1;
	int TERJE_BADGE_VACINA_A = -1;
	int TERJE_BADGE_VACINA_B = -1;
	int TERJE_BADGE_VACINA_C = -1;
	int TERJE_BADGE_RABIES_CURE = -1;
	int TERJE_BADGE_GAIN_IMMUNITY = -1;
	int TERJE_BADGE_GAIN_HEALTH = -1;
	
	protected bool m_terjeUnconState = false;
	protected TextWidget m_terjeUnconInfoWidget = null;
	
	override void Init( Widget hud_panel_widget )
	{
		super.Init(hud_panel_widget);
		
		if (m_terjeUnconInfoWidget)
		{
			m_terjeUnconInfoWidget.Unlink();
		}
		
		m_terjeUnconInfoWidget = TextWidget.Cast(g_Game.GetWorkspace().CreateWidgets("TerjeCore/Layouts/TerjeWidgetTextCentered.layout", hud_panel_widget));
		m_terjeUnconInfoWidget.Show(false);
	}
	
	override void InitConditionalTerjeBadgesAndNotifiers()
	{
		super.InitConditionalTerjeBadgesAndNotifiers();
		
		// Notifiers
		bool isSleepingEnabled = false;
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_SLEEPING_ENABLED, isSleepingEnabled) && isSleepingEnabled)
		{
			TERJE_NOTIFIER_SLEEPING = RegisterTerjeNotifierWidget("set:TerjeMedicine_icon image:tm_sleeping_{ID}", "TerjeSleeping");
		}
		else
		{
			TERJE_NOTIFIER_SLEEPING = -1;
		}
		
		bool isMindEnabled = false;
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_MIND_ENABLED, isMindEnabled) && isMindEnabled)
		{
			TERJE_NOTIFIER_MIND = RegisterTerjeNotifierWidget("set:TerjeMedicine_icon image:tm_mind_{ID}", "TerjeMind");
		}
		else
		{
			TERJE_NOTIFIER_MIND = -1;
		}
		
		bool isHandEnabled = false;
		if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_DETAILED_SANITARY_DISPLAY, isHandEnabled) && isHandEnabled)
		{
			TERJE_NOTIFIER_HAND = RegisterTerjeNotifierWidget("set:TerjeMedicine_icon image:tm_hand_{ID}", "TerjeHand");
		}
		else
		{
			TERJE_NOTIFIER_HAND = -1;
		}
	}
	
	override void InitBadgesAndNotifiers()
	{
		super.InitBadgesAndNotifiers();
		
		// Change default icons
		ref ImageWidget defaultBleedingIcon = ImageWidget.Cast( m_HudPanelWidget.FindAnyWidget("Bleeding") );
		if (defaultBleedingIcon)
		{
			defaultBleedingIcon.LoadImageFile(0, "set:TerjeMedicine_icon image:tm_scratch");
		}
		
		// Badges
		TERJE_BADGE_BULLETWOUND = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bullethit", "TerjeBullethit", TerjeBadgeType.COUNTER);
		TERJE_BADGE_VISCERA = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_viscera", "TerjeViscera", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_PAIN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_pain", "TerjePain", TerjeBadgeType.LEVELED);
		TERJE_BADGE_OVERDOSE = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_overdosed", "TerjeOverdosed", TerjeBadgeType.LEVELED);
		TERJE_BADGE_STUBWOUND = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_wound", "TerjeKnifeHit", TerjeBadgeType.COUNTER);
		TERJE_BADGE_HEMATOMA = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_hematoma", "TerjeHematoma", TerjeBadgeType.COUNTER);
		TERJE_BADGE_CONTUSION = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_concussion", "TerjeConcussion", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ZVIRUS = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_virusz", "TerjeZVirus", TerjeBadgeType.LEVELED);
		TERJE_BADGE_SEPSIS = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_sepsis", "TerjeSepsis", TerjeBadgeType.LEVELED);
		TERJE_BADGE_INFLUENZA = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_influenza", "TerjeInfluenza", TerjeBadgeType.LEVELED);
		TERJE_BADGE_POISON = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_poison", "TerjePoison", TerjeBadgeType.LEVELED);
		TERJE_BADGE_BIOHAZARD = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_biohazard", "TerjeBiohazard", TerjeBadgeType.LEVELED);
		TERJE_BADGE_RABIES = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_rabies", "TerjeRabies", TerjeBadgeType.LEVELED);
		
		TERJE_BADGE_ANTIPOISON = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antipoison", "TerjeAntipoison", TerjeBadgeType.LEVELED);
		TERJE_BADGE_SALVE = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_salve", "TerjeSalve", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_PAINKILLER = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_painkiller", "TerjePainkiller", TerjeBadgeType.LEVELED);
		TERJE_BADGE_HEMOSTATIC = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_hemostatic", "TerjeHemostatic", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_BLOODREGEN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bloodregen", "TerjeBloodRegen", TerjeBadgeType.DEFAULT);
		if (!GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_ENABLE_DETAILED_SANITARY_DISPLAY))
		{
			TERJE_BADGE_DISINFECTED = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_disinfected_2", "TerjeDisinfected", TerjeBadgeType.DEFAULT);
		}
		TERJE_BADGE_BANDAGED_CLEAN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bandagedclean_2", "TerjeBandagedClean", TerjeBadgeType.COUNTER);
		TERJE_BADGE_BANDAGED_DIRTY = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_bandageddirty_2", "TerjeBandagedDirty", TerjeBadgeType.COUNTER);
		TERJE_BADGE_SUTURES_CLEAN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_protectingwound", "TerjeSuturesClean", TerjeBadgeType.COUNTER);
		TERJE_BADGE_SUTURES_DIRTY = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_protectingwoundseps", "TerjeSuturesDirty", TerjeBadgeType.COUNTER);
		TERJE_BADGE_ANTIDEPRESANT = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antidepresant", "TerjeAntidepresant", TerjeBadgeType.LEVELED);
		TERJE_BADGE_ANTIBIOTIC = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antibiotic", "TerjeAntibiotic", TerjeBadgeType.LEVELED);
		TERJE_BADGE_ANTISEPSIS = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antisepsis", "TerjeAntisepsis", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_Z_ANTIDOT = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_antidotz", "TerjeZAntidot", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ADRENALIN = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_adrenalin", "TerjeAdrenalin", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_CONTUSSIONHEAL = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_concussionheal", "TerjeConcussionHeal", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_ANTIBIOHAZARD = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_biohazardheal", "TerjeBiohazardHeal", TerjeBadgeType.LEVELED);
		TERJE_BADGE_VACINA_A = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_vacina_a", "TerjeVacinaA", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_VACINA_B = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_vacina_b", "TerjeVacinaB", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_VACINA_C = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_vacina_c", "TerjeVacinaC", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_RABIES_CURE = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_rabies_cure", "TerjeRabiesCure", TerjeBadgeType.LEVELED);
		TERJE_BADGE_GAIN_IMMUNITY = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_immunity", "TerjeMedImmunity", TerjeBadgeType.DEFAULT);
		TERJE_BADGE_GAIN_HEALTH = RegisterTerjeBadgetWidget("set:TerjeMedicine_icon image:tm_healthgain", "TerjeMedHealthGain", TerjeBadgeType.DEFAULT);
	}
	
	override bool GetTerjeBadgeColor( int key, int value, out int outputColor )
	{
		if (super.GetTerjeBadgeColor(key, value, outputColor))
		{
			return true;
		}
		else if (key == TERJE_BADGE_CONTUSION || key == TERJE_BADGE_BANDAGED_DIRTY || key == TERJE_BADGE_SUTURES_DIRTY)
		{
			outputColor = GetTerjeBadgeColorWarning();
			return true;
		}
		else if (key == TERJE_BADGE_BULLETWOUND || key == TERJE_BADGE_VISCERA || key == TERJE_BADGE_STUBWOUND || key == TERJE_BADGE_ZVIRUS)
		{
			outputColor = GetTerjeBadgeColorCritical();
			return true;
		}
		else if (key == TERJE_BADGE_BIOHAZARD || key == TERJE_BADGE_PAIN || key == TERJE_BADGE_OVERDOSE || key == TERJE_BADGE_SEPSIS || key == TERJE_BADGE_INFLUENZA || key == TERJE_BADGE_POISON || key == TERJE_BADGE_RABIES)
		{
			if (value <= 2)
			{
				outputColor = GetTerjeBadgeColorWarning();
				return true;
			}
			else
			{
				outputColor = GetTerjeBadgeColorCritical();
				return true;
			}
		}
		else if (key == TERJE_BADGE_HEMATOMA)
		{
			if (value <= 8)
			{
				outputColor = GetTerjeBadgeColorWarning();
				return true;
			}
			else
			{
				outputColor = GetTerjeBadgeColorCritical();
				return true;
			}
		}
		
		outputColor = GetTerjeBadgeColorDefault();
		return false;
	}
	
	void TerjeDisplayTendencyHand( int key, int tendency, int status )
	{
		ImageWidget w;
		Class.CastTo(w, m_Notifiers.FindAnyWidget( String( "Icon" + m_StatesWidgetNames.Get( key ) ) ) );
		
		if( w )
		{
			w.SetImage( Math.Clamp( status - 1, 0, 3 ) );
			float alpha = w.GetAlpha();
			
			switch( status )
			{
				case 4:
					w.SetColor( ARGB( alpha * 255, 220, 220, 0 ) );		//yellow
					m_TendencyStatusCritical.Remove( w );				//remove from blinking group
					break;
				default:
					w.SetColor( ARGB( alpha * 255, 220, 220, 220 ) );	//white
					m_TendencyStatusCritical.Remove( w );				//remove from blinking group
					break;
			}
		}	
	}
	
	override void OnUnconsciousStart()
	{
		super.OnUnconsciousStart();
		m_terjeUnconState = true;
	}
	
	override void OnUnconsciousStop()
	{
		super.OnUnconsciousStop();
		m_terjeUnconState = false;
	}
	
	override void DisplayNotifier( int key, int tendency, int status )
	{
		super.DisplayNotifier(key, tendency, status);
		
		if (key == TERJE_NOTIFIER_HAND)
		{
			TerjeDisplayTendencyHand(key, tendency, status);
		}
	}
	
	override void Update(float timeslice)
	{
		super.Update(timeslice);
		
		if (m_terjeUnconInfoWidget)
		{
			PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
			if (m_terjeUnconState && player && player.IsAlive() && player.GetTerjeStats() && player.GetTerjeStats().IsInKnockout())
			{
				bool showDetailedText;
				if (GetTerjeSettingBool(TerjeSettingsCollection.MEDICINE_KNOCKOUT_SHOW_INFO, showDetailedText) && showDetailedText && !m_terjeUnconInfoWidget.IsVisible())
				{
					m_terjeUnconInfoWidget.SetText("#STR_TERJEMED_KNOCKOUT_INFO");
					m_terjeUnconInfoWidget.Show(true);
				}
			}
			else
			{
				if (m_terjeUnconInfoWidget.IsVisible())
				{
					m_terjeUnconInfoWidget.Show(false);
				}
			}
		}
	}
}
