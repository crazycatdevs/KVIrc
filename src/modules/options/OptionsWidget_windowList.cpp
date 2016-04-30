//=============================================================================
//
//   File : OptionsWidget_windowList.cpp
//   Creation date : Wed Jan 16 04:30:39 2002 GMT by Szymon Stefanek
//
//   This file is part of the KVIrc IRC client distribution
//   Copyright (C) 2002-2010 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your option) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
//=============================================================================

#include "OptionsWidget_windowList.h"

#include "kvi_settings.h"
#include "KviLocale.h"
#include "KviOptions.h"

OptionsWidget_windowList::OptionsWidget_windowList(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("windowlist_options_widget");
	createLayout();

	addBoolSelector(0, 0, 0, 0, __tr2qs_ctx("Use tree window list", "options"), KviOption_boolUseTreeWindowListWindowList);
	addBoolSelector(0, 1, 0, 1, __tr2qs_ctx("Sort windows by name", "options"), KviOption_boolSortWindowListItemsByName);
	addBoolSelector(0, 2, 0, 2, __tr2qs_ctx("Show window icons in window list", "options"), KviOption_boolUseWindowListIcons);
	KviBoolSelector * b = addBoolSelector(0, 3, 0, 3, __tr2qs_ctx("Show activity meter in window list", "options"), KviOption_boolUseWindowListActivityMeter);
	mergeTip(b, __tr2qs_ctx("This option enables the usage of the window list activity meter. "
	                        "Each window entry will have a small indicator of the activity that is going on in that window. "
	                        "The indicator is a small square that changes colors, dark colors mean low activity, "
	                        "while bright colors signal high activity. KVIrc also uses some heuristics to determine "
	                        "whether the activity is somewhat \"human\" or it is generated by automated entities (such as bots "
	                        "or IRC servers). \"Human\" activity causes the indicator to be shaded red while automated "
	                        "activity causes the indicator to be shaded blue.",
	                "options"));

	addBoolSelector(0, 4, 0, 4, __tr2qs_ctx("Show IRC context indicator in window list", "options"), KviOption_boolUseWindowListIrcContextIndicator);
	addBoolSelector(0, 5, 0, 5, __tr2qs_ctx("Enable window tooltips", "options"), KviOption_boolShowWindowListToolTips);
	addBoolSelector(0, 6, 0, 6, __tr2qs_ctx("Allow the window list to be moved", "options"), KviOption_boolShowTreeWindowListHandle);
	addBoolSelector(0, 7, 0, 7, __tr2qs_ctx("Show user flag for channels", "options"), KviOption_boolShowUserFlagForChannelsInWindowList);

	addRowSpacer(0, 8, 0, 8);
}

OptionsWidget_windowList::~OptionsWidget_windowList()
    = default;

OptionsWidget_windowListTree::OptionsWidget_windowListTree(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("treewindowlist_options_widget");
}

OptionsWidget_windowListTree::~OptionsWidget_windowListTree()
    = default;

OptionsWidget_windowListTreeForeground::OptionsWidget_windowListTreeForeground(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("treewindowlist_options_widget");
	createLayout();

	addFontSelector(0, 0, 0, 0, __tr2qs_ctx("Font:", "options"), KviOption_fontTreeWindowList);

	KviTalGroupBox * g = addGroupBox(0, 1, 0, 1, Qt::Horizontal, __tr2qs_ctx("Text/Alert Colors", "options"));

	addColorSelector(g, __tr2qs_ctx("Normal:", "options"), KviOption_colorTreeWindowListForeground);
	addColorSelector(g, __tr2qs_ctx("Selected:", "options"), KviOption_colorTreeWindowListActiveForeground);
	addColorSelector(g, __tr2qs_ctx("Alert level 1:", "options"), KviOption_colorTreeWindowListHighlight1Foreground);
	addColorSelector(g, __tr2qs_ctx("Alert level 2:", "options"), KviOption_colorTreeWindowListHighlight2Foreground);
	addColorSelector(g, __tr2qs_ctx("Alert level 3:", "options"), KviOption_colorTreeWindowListHighlight3Foreground);
	addColorSelector(g, __tr2qs_ctx("Alert level 4:", "options"), KviOption_colorTreeWindowListHighlight4Foreground);
	addColorSelector(g, __tr2qs_ctx("Alert level 5:", "options"), KviOption_colorTreeWindowListHighlight5Foreground);

	addColorSelector(0, 2, 0, 2, __tr2qs_ctx("Progress bar color:", "options"), KviOption_colorTreeWindowListProgress);

	addRowSpacer(0, 3, 0, 3);
}

OptionsWidget_windowListTreeForeground::~OptionsWidget_windowListTreeForeground()
    = default;

OptionsWidget_windowListTreeBackground::OptionsWidget_windowListTreeBackground(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("treewindowlist_options_widget");

	createLayout();

	KviTalGroupBox * g = addGroupBox(0, 0, 1, 0, Qt::Horizontal, __tr2qs_ctx("Background Colors", "options"));
	addColorSelector(g, __tr2qs_ctx("Normal:", "options"), KviOption_colorTreeWindowListBackground);
	addColorSelector(g, __tr2qs_ctx("Selected:", "options"), KviOption_colorTreeWindowListActiveBackground);

	addPixmapSelector(0, 1, 1, 1, __tr2qs_ctx("Background image:", "options"), KviOption_pixmapTreeWindowListBackground);

	addLabel(0, 2, 0, 2, __tr2qs_ctx("Horizontal align:", "options"));
	m_pHorizontalAlign = new QComboBox(this);
	addWidgetToLayout(m_pHorizontalAlign, 1, 2, 1, 2);

	addLabel(0, 3, 0, 3, __tr2qs_ctx("Vertical align:", "options"));
	m_pVerticalAlign = new QComboBox(this);
	addWidgetToLayout(m_pVerticalAlign, 1, 3, 1, 3);

	m_pHorizontalAlign->addItem(__tr2qs_ctx("Tile", "options"));
	m_pHorizontalAlign->addItem(__tr2qs_ctx("Left", "options"));
	m_pHorizontalAlign->addItem(__tr2qs_ctx("Right", "options"));
	m_pHorizontalAlign->addItem(__tr2qs_ctx("Center", "options"));

	m_pVerticalAlign->addItem(__tr2qs_ctx("Tile", "options"));
	m_pVerticalAlign->addItem(__tr2qs_ctx("Top", "options"));
	m_pVerticalAlign->addItem(__tr2qs_ctx("Bottom", "options"));
	m_pVerticalAlign->addItem(__tr2qs_ctx("Center", "options"));

	switch(KVI_OPTION_UINT(KviOption_uintTreeWindowListPixmapAlign) & Qt::AlignHorizontal_Mask)
	{
		case Qt::AlignLeft:
			m_pHorizontalAlign->setCurrentIndex(1);
			break;
		case Qt::AlignRight:
			m_pHorizontalAlign->setCurrentIndex(2);
			break;
		case Qt::AlignHCenter:
			m_pHorizontalAlign->setCurrentIndex(3);
			break;
		default:
			m_pHorizontalAlign->setCurrentIndex(0);
	}

	switch(KVI_OPTION_UINT(KviOption_uintTreeWindowListPixmapAlign) & Qt::AlignVertical_Mask)
	{
		case Qt::AlignTop:
			m_pVerticalAlign->setCurrentIndex(1);
			break;
		case Qt::AlignBottom:
			m_pVerticalAlign->setCurrentIndex(2);
			break;
		case Qt::AlignVCenter:
			m_pVerticalAlign->setCurrentIndex(3);
			break;
		default:
			m_pVerticalAlign->setCurrentIndex(0);
	}

	layout()->setRowStretch(1, 1);
}

OptionsWidget_windowListTreeBackground::~OptionsWidget_windowListTreeBackground()
    = default;

void OptionsWidget_windowListTreeBackground::commit()
{
	KviOptionsWidget::commit();

	int iFlags = 0;
	switch(m_pHorizontalAlign->currentIndex())
	{
		case 1:
			iFlags |= Qt::AlignLeft;
			break;
		case 2:
			iFlags |= Qt::AlignRight;
			break;
		case 3:
			iFlags |= Qt::AlignHCenter;
			break;
	}
	switch(m_pVerticalAlign->currentIndex())
	{
		case 1:
			iFlags |= Qt::AlignTop;
			break;
		case 2:
			iFlags |= Qt::AlignBottom;
			break;
		case 3:
			iFlags |= Qt::AlignVCenter;
			break;
	}

	KVI_OPTION_UINT(KviOption_uintTreeWindowListPixmapAlign) = iFlags;
}

OptionsWidget_windowListTreeFeatures::OptionsWidget_windowListTreeFeatures(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("treewindowlist_options_widget");
	createLayout();

	KviUIntSelector * u;

	u = addUIntSelector(0, 1, 0, 1, __tr2qs_ctx("Minimum width:", "options"), KviOption_uintTreeWindowListMinimumWidth, 24, 1024, 125);
	u->setSuffix(__tr2qs_ctx(" pixels", "options"));
	addBoolSelector(0, 3, 0, 3, __tr2qs_ctx("Mouse wheel changes the active window instead of scrolling the scrollbar", "options"), KviOption_boolWheelScrollsWindowsList);

	addRowSpacer(0, 4, 0, 4);
}

OptionsWidget_windowListTreeFeatures::~OptionsWidget_windowListTreeFeatures()
    = default;

OptionsWidget_windowListClassic::OptionsWidget_windowListClassic(QWidget * parent)
    : KviOptionsWidget(parent)
{
	setObjectName("classicwindowlist_options_widget");
	createLayout();

	KviUIntSelector * u;

	addFontSelector(0, 0, 0, 0, __tr2qs_ctx("Font:", "options"), KviOption_fontWindowList);
	KviTalGroupBox * g = addGroupBox(0, 1, 0, 1, Qt::Horizontal, __tr2qs_ctx("Text/Alert Colors", "options"));
	addColorSelector(g, __tr2qs_ctx("Normal:", "options"), KviOption_colorWindowListNormalText);
	addColorSelector(g, __tr2qs_ctx("Minimized:", "options"), KviOption_colorWindowListMinimizedText);
	addColorSelector(g, __tr2qs_ctx("Alert level 1:", "options"), KviOption_colorWindowListHighlight1Text);
	addColorSelector(g, __tr2qs_ctx("Alert level 2:", "options"), KviOption_colorWindowListHighlight2Text);
	addColorSelector(g, __tr2qs_ctx("Alert level 3:", "options"), KviOption_colorWindowListHighlight3Text);
	addColorSelector(g, __tr2qs_ctx("Alert level 4:", "options"), KviOption_colorWindowListHighlight4Text);
	addColorSelector(g, __tr2qs_ctx("Alert level 5:", "options"), KviOption_colorWindowListHighlight5Text);

	addColorSelector(0, 2, 0, 2, __tr2qs_ctx("Progress bar color:", "options"), KviOption_colorWindowListProgressBar);
	u = addUIntSelector(0, 3, 0, 3, __tr2qs_ctx("Minimum width of buttons:", "options"), KviOption_uintWindowListButtonMinWidth, 24, 9999, 100);
	u->setSuffix(__tr2qs_ctx(" pixels", "options"));
	addBoolSelector(0, 4, 0, 4, __tr2qs_ctx("Set maximum button width", "options"), KviOption_boolClassicWindowListSetMaximumButtonWidth);
	u = addUIntSelector(0, 5, 0, 5, __tr2qs_ctx("Maximum width of buttons:", "options"), KviOption_uintClassicWindowListMaximumButtonWidth, 24, 9999, 100);
	u->setSuffix(__tr2qs_ctx(" pixels", "options"));
	addBoolSelector(0, 6, 0, 6, __tr2qs_ctx("Use flat buttons", "options"), KviOption_boolUseFlatClassicWindowListButtons);

	addRowSpacer(0, 7, 0, 7);
}

OptionsWidget_windowListClassic::~OptionsWidget_windowListClassic()
    = default;
