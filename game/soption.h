﻿#pragma once
#include <cstdint>

struct sOption {
	sOption();
	~sOption();
	void vSetOverallByVidOptions();

	static bool IsSupportShadow();
	static bool IsSupportReflection();
	static bool IsSupportLod();
	const char* vGetTnlText(int tnl) const;
	int vGetTnlLvl(const char* tnl) const;
	const char* aGetSpeakerText(int speaker) const;
	int aGetSpeakerLvl(const char* speaker) const;
	const char* GetThreeLvlText(int level) const;
	const char* GetTwoLvlText(int level) const;
	const char* vGetOverallText(int level) const;
	const char* vGetTexResText(int level) const;
	const char* vGetParticleText(int level) const;
	int vGetLvl3FromText(const char* level) const;
	void vResetByOverall(const char* overall);
	int vGetOverallLvl(const char* level) const;
	int vGetTexResLvl(const char* level) const;
	int vGetParticleLvl(const char* level) const;
	int aGetOverallLvl(const char* level) const;

	static bool sbHwTnlSupport;
	static bool sbRtSupport;
	static bool sbVsSupport;
	static bool sbPsSupport;
	static bool sbMrtSupport;
	static bool sbClipPlaneSupport;

	uint32_t m_wWindowedMode;
	uint32_t m_vFillMode;
	uint32_t m_vWideMode;
	uint32_t m_vScreenWidth;
	uint32_t m_vScreenHeight;
	uint32_t m_vGameScreen;
	uint32_t m_vScreenWidth2;
	uint32_t m_vScreenHeight2;
	uint32_t m_vScreenColor;
	uint32_t m_vOverall;
	uint32_t m_vTnLMode;
	uint32_t m_vMipDDSRes;
	uint32_t m_vUseMipmap;
	uint32_t m_vMaxMipLevel;
	uint32_t m_vMipMapCreateFilter;
	uint32_t m_vParticleLevel;
	uint32_t m_vShadowEnabled;
	uint32_t m_vShadowmapEnabled;
	uint32_t m_vReflectionEnabled;
	uint32_t m_vLodEnabled;
	uint32_t m_gNpcEnabled;
	uint32_t m_vCoordX;
	uint32_t m_vCoordY;
	float m_vScreenRatio;
	uint32_t m_aMssEnabled;
	uint32_t m_aOverall;
	uint32_t m_aMssFrequency;
	uint32_t m_aMssBits;
	uint32_t m_aMssChannels;
	uint32_t m_aMssHwSoundEnabled;
	uint32_t m_aMssBalance;
	uint32_t m_aMssSpeaker;
	float m_aSfxVolume;
	float m_aBgmVolume;
	float m_gMouseSensitivity;
	uint32_t m_gWhisper;
	uint32_t m_gInvitation;
	uint32_t m_gFriendConfirm;
	uint32_t m_gTransChatWin;
	uint32_t m_gUiEffect;
	char m_gLastLoginId[24];
	uint32_t m_gIdentity;
	uint32_t m_gExtendChatLine;
	uint32_t m_gUserSort;
	uint32_t m_bPPLEnabled;
	uint32_t m_gPPLSize;
	uint32_t m_gPowerGauge;
	uint32_t m_gCaptureLogo;
	uint32_t m_gRestore;
	uint32_t m_mChatWndUp;
	uint32_t m_gUnderExtBtn;
	uint32_t m_gAvatarNewBie;
	uint32_t m_mCaptureHideGUI;
	uint32_t m_mCaptureHidePII;
	uint32_t m_gTerrainTooltip;
	uint32_t m_gCutinFlag;
	char m_mMacroText[8][64];
	uint32_t m_mSaveMacros;
	char m_localName[32];
};
