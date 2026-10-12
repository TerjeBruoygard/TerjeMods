class TerjeStartScreenPageFace : TerjeStartScreenPageBase
{
	protected Widget m_nextButtonPanel;
	protected Widget m_facesGrid;
	protected Widget m_beardPanel;
	protected Widget m_beardButtonsPanel;
	protected TextWidget m_beardTitleText;
	protected ref TerjeXmlObject m_currentFace;
	protected TerjeWidgetButton m_nextButton;
	protected ref array<ref TerjeWidgetButtonHold> m_beardButtons;
	protected int m_beardSelectedLevel;
	protected int m_beardMaxLevel;
	protected int m_beardMask;
	protected bool m_beardSelectionEnabled;
	
	override void OnInit()
	{
		super.OnInit();
		m_nextButtonPanel = GetNativeWidget().FindAnyWidget("PanelNextButton");
		m_facesGrid = GetNativeWidget().FindAnyWidget("FacesGrid");
		m_beardPanel = GetNativeWidget().FindAnyWidget("PanelBeardLevel");
		m_beardButtonsPanel = GetNativeWidget().FindAnyWidget("PanelBeardButtons");
		m_beardTitleText = TextWidget.Cast(GetNativeWidget().FindAnyWidget("TerjeBeardLevelTitle"));
		m_beardButtons = new array<ref TerjeWidgetButtonHold>;
		m_beardSelectedLevel = 0;
		m_beardMaxLevel = 3;
		m_beardMask = 15;
		m_beardSelectionEnabled = false;
	}

	override string GetNativeLayout()
	{
		return "TerjeStartScreen/Layouts/PageFace.layout";
	}
	
	override void InitInputContext(TerjeStartScreenContextBase context)
	{
		super.InitInputContext(context);
		
		TerjeStartScreenContextFace faceContext = TerjeStartScreenContextFace.Cast(context);
		if (faceContext != null)
		{
			m_currentFace = null;
			m_beardSelectedLevel = 0;
			m_beardMaxLevel = 3;
			m_beardMask = 15;
			m_beardSelectionEnabled = false;
			UpdateBeardButtonsState();
			PushCommand(new TerjeWidgetCommand_TerjeStartScreenFacesRefresh(faceContext.m_inputFacesXml));
		}
	}
	
	override void InitOutputContext(TerjeStartScreenContextBase context)
	{
		super.InitOutputContext(context);
		
		TerjeStartScreenContextFace faceContext = TerjeStartScreenContextFace.Cast(context);
		if ((faceContext != null) && (m_currentFace != null))
		{
			m_currentFace.SetAttribute("beardSelected", m_beardSelectedLevel.ToString());
			faceContext.m_inputFacesXml.Clear();
			faceContext.m_selectedFaceXml = m_currentFace;
		}
	}
	
	override void OnCommand(TerjeWidgetCommand command, float timeslice)
	{
		super.OnCommand(command, timeslice);
		
		if (command.IsInherited(TerjeWidgetCommand_TerjeStartScreenFacesRefresh))
		{
			DestroyAllChildren();
			m_beardButtons.Clear();
			
			TerjeWidgetCommand_TerjeStartScreenFacesRefresh refreshCommand = TerjeWidgetCommand_TerjeStartScreenFacesRefresh.Cast(command);
			for (int i = 0; i < refreshCommand.m_facesXml.GetChildrenCount(); i++)
			{
				CreateFaceItemWidget(refreshCommand.m_facesXml.GetChild(i));
			}
			
			m_nextButton = TerjeWidgetButton.Cast(CreateTerjeWidgetEx(TerjeWidgetButton, m_nextButtonPanel));
			m_nextButton.SetText("#STR_USRACT_NEXT_ACTION");
			m_nextButton.SetEnabled(false);
			m_nextButton.OnClickEvent.Insert(OnClickNextButton);
			BuildBeardButtons();
			UpdateBeardButtonsState();
		}
	}
	
	protected void OnClickNextButton(TerjeWidgetButton widget)
	{
		if (m_currentFace != null)
		{
			ExecuteNextPage();
		}
	}
	
	protected void CreateFaceItemWidget(TerjeXmlObject faceXml)
	{
		if (!faceXml)
			return;
		
		string icon;
		if (!faceXml.FindAttribute("icon", icon))
		{
			return;
		}
		
		string background;
		TerjeStartScreenItemFace itemWidget = TerjeStartScreenItemFace.Cast(CreateTerjeWidgetEx(TerjeStartScreenItemFace, m_facesGrid));
		if (faceXml.FindAttribute("background", background))
		{
			itemWidget.SetBackground(background);
		}
		
		itemWidget.SetValid(faceXml.EqualAttribute("$valid", "1"));
		itemWidget.SetIcon(icon);
		itemWidget.SetSelected(false);
		itemWidget.SetUserParam("face", new Param1<ref TerjeXmlObject>(faceXml));
		itemWidget.OnClickEvent.Insert(OnFaceItemClick);
	}
	
	protected void OnFaceItemClick(TerjeStartScreenItemFace w)
	{
		w.SetSelected(true);
		for (int i = 0; i < GetChildrenCount(); i++)
		{
			TerjeStartScreenItemFace childItem = TerjeStartScreenItemFace.Cast(GetChild(i));
			if (childItem != null && childItem != w)
			{
				childItem.SetSelected(false);
			}
		}
		
		Param1<ref TerjeXmlObject> faceParam = Param1<ref TerjeXmlObject>.Cast(w.GetUserParam("face"));
		if (faceParam != null)
		{
			m_currentFace = faceParam.param1;
			ApplyFaceBeardSelectionData(m_currentFace);
			if ((m_nextButton != null) && (m_currentFace != null))
			{
				m_nextButton.SetEnabled(true);
			}
		}
	}

	protected void BuildBeardButtons()
	{
		if (m_beardButtonsPanel == null) return;
		if (m_beardButtons.Count() > 0) return;

		for (int i = 0; i <= 3; i++)
		{
			TerjeWidgetButtonHold btn = TerjeWidgetButtonHold.Cast(CreateTerjeWidgetEx(TerjeWidgetButtonHold, m_beardButtonsPanel));
			if (btn == null) continue;
			
			btn.SetSizeImmediately(112, 30, false);
			btn.SetHoldTime(0.1);

			btn.SetUserParam("beardLevel", new Param1<int>(i));
			btn.SetText(i.ToString());
			btn.OnClickEvent.Insert(OnClickBeardButton);
			m_beardButtons.Insert(btn);
		}
	}

	protected void ApplyFaceBeardSelectionData(TerjeXmlObject faceXml)
	{
		if (faceXml == null)
		{
			m_beardSelectionEnabled = false;
			UpdateBeardButtonsState();
			return;
		}

		string rawEnabled = "0";
		string rawSelectable = "0";
		string rawMask = "15";
		string rawMax = "3";
		string rawDefault = "0";
		string rawSelected = string.Empty;

		faceXml.FindAttribute("$beardEnabled", rawEnabled);
		faceXml.FindAttribute("$beardSelectable", rawSelectable);
		faceXml.FindAttribute("$beardMask", rawMask);
		faceXml.FindAttribute("$beardMax", rawMax);
		faceXml.FindAttribute("$beardDefault", rawDefault);
		faceXml.FindAttribute("beardSelected", rawSelected);

		m_beardSelectionEnabled = (rawEnabled.ToInt() == 1) && (rawSelectable.ToInt() == 1);
		m_beardMask = rawMask.ToInt();
		m_beardMaxLevel = FindLastAllowedBeardLevel(m_beardMask);
		if (m_beardMaxLevel < 0) m_beardMaxLevel = 0;
		if (m_beardMaxLevel > 3) m_beardMaxLevel = 3;

		int cfgMaxLevel = TerjeMathHelper.ClampInt(rawMax.ToInt(), 0, 3);
		if (cfgMaxLevel > m_beardMaxLevel) m_beardMaxLevel = cfgMaxLevel;

		m_beardSelectedLevel = TerjeMathHelper.ClampInt(rawDefault.ToInt(), 0, m_beardMaxLevel);
		if (rawSelected != string.Empty) m_beardSelectedLevel = TerjeMathHelper.ClampInt(rawSelected.ToInt(), 0, m_beardMaxLevel);
		if ((m_beardMask & (1 << m_beardSelectedLevel)) == 0) m_beardSelectedLevel = FindFirstAllowedBeardLevel();

		UpdateBeardButtonsState();
	}

	protected int FindFirstAllowedBeardLevel()
	{
		for (int i = 0; i <= m_beardMaxLevel; i++)
		{
			if ((m_beardMask & (1 << i)) != 0) return i;
		}

		return 0;
	}

	protected int FindLastAllowedBeardLevel(int mask)
	{
		for (int i = 3; i >= 0; i--)
		{
			if ((mask & (1 << i)) != 0) return i;
		}

		return 0;
	}

	protected void OnClickBeardButton(TerjeWidgetButtonHold btn)
	{
		if (!m_beardSelectionEnabled) return;
		if (btn == null) return;

		Param1<int> levelParam = Param1<int>.Cast(btn.GetUserParam("beardLevel"));
		if (levelParam == null) return;

		int level = TerjeMathHelper.ClampInt(levelParam.param1, 0, 3);
		if ((m_beardMask & (1 << level)) == 0) return;

		m_beardSelectedLevel = TerjeMathHelper.ClampInt(level, 0, m_beardMaxLevel);
		UpdateBeardButtonsState();
	}

	protected void UpdateBeardButtonsState()
	{
		if (m_beardPanel != null) m_beardPanel.Show(m_beardSelectionEnabled);
		if (m_beardButtonsPanel != null) m_beardButtonsPanel.Show(m_beardSelectionEnabled);
		if (m_beardTitleText != null) m_beardTitleText.SetText("Beard level");

		for (int i = 0; i < m_beardButtons.Count(); i++)
		{
			TerjeWidgetButtonHold btn = m_beardButtons.Get(i);
			if (btn == null) continue;

			Param1<int> levelParam = Param1<int>.Cast(btn.GetUserParam("beardLevel"));
			if (levelParam == null) continue;

			int level = TerjeMathHelper.ClampInt(levelParam.param1, 0, 3);
			bool enabled = m_beardSelectionEnabled && (level <= m_beardMaxLevel) && ((m_beardMask & (1 << level)) != 0);
			if (enabled)
			{
				btn.SetEnabled(true);
				btn.SetText(level.ToString());
				if (level == m_beardSelectedLevel) btn.SetColor(ARGB(90, 60, 113, 84));
				else btn.SetColor(ARGB(60, 255, 0, 0));
			}
			else
			{
				btn.SetEnabled(false);
				btn.SetText(level.ToString());
				btn.SetColor(ARGB(60, 80, 80, 80));
			}
		}
	}
}

class TerjeWidgetCommand_TerjeStartScreenFacesRefresh : TerjeWidgetCommand
{
	ref TerjeXmlObject m_facesXml;
	
	void TerjeWidgetCommand_TerjeStartScreenFacesRefresh(TerjeXmlObject facesXml)
	{
		m_facesXml = facesXml;
	}
}