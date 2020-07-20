﻿#include "wresourcemanager.h"

#include "bitmap.h"
#include "cfile.h"
#include "w3dspr.h"
#include "woverlay.h"
#include "wresource.h"
#include "wtitlefont.h"
#include "wvideo.h"

WResourceManager* g_resourceManager = nullptr;

WVideoDev* WResourceManager::VideoReference() const {
	return this->video;
}

void WResourceManager::SetVideoReference(WVideoDev* video) {
	this->video = video;
}

const WList<w_texlist*>& WResourceManager::GetTextureList() const {
	return this->texList;
}

void WResourceManager::Lock(rmlType_t type) {
	this->m_lock[type].Lock();
}

void WResourceManager::Unlock(rmlType_t type) {
	this->m_lock[type].Unlock();
}

void WResourceManager::UnlockAllByThread(unsigned int threadID) {
	for (auto& lock : this->m_lock) {
		lock.UnlockInThread(threadID);
	}
}

void WResourceManager::SetUseLessVideoRam(int level) {
	this->m_savemem[0] = false;
	this->m_savemem[1] = level > 0;
	this->m_savemem[2] = level > 1;
}

void WResourceManager::Release(WResource* resrc) {
	delete resrc;
}

void WResourceManager::Release(int texhandle) {
	w_texlist* tex = this->FindTexture(texhandle);
	if (!tex) {
		return;
	}
	tex->count--;
	if (tex->count <= 0) {
		this->m_nByteUsedTexture -= tex->size;
		this->video->DestroyTexture(texhandle);
		this->texList.DelItem(tex);
		delete[] tex;
	}
}

w_texlist* WResourceManager::FindTexture(int texHandle) {
	for (auto* it = this->texList.Start(); it != nullptr; it = this->texList.Next()) {
		if (it->texhandle == texHandle) {
			return it;
		}
	}
	return nullptr;
}

WOverlay* WResourceManager::GetOverlay(const char* filename, unsigned int flag) {
	auto* overlay = new WOverlay();
	overlay->m_resrcMng = this;
	if (!filename || !overlay->Load(filename, flag)) {
		return overlay;
	}
	delete overlay;
	return nullptr;
}

WOverlay* WResourceManager::GetOverlay(const char* name, Bitmap* bitmap, unsigned int flag) {
	auto* overlay = new WOverlay();
	overlay->m_resrcMng = this;
	if (!name || !overlay->Load(name, bitmap, flag)) {
		return overlay;
	}
	delete overlay;
	return nullptr;
}

WTitleFont* WResourceManager::GetTitleFont() {
	auto* font = new WTitleFont();
	font->m_resrcMng = this;
	return font;
}

void WResourceManager::Release(WTitleFont* font) {
	delete font;
}

W3dSpr* WResourceManager::Get3DSpr(const char* filename, int type) {
	W3dSpr* spr = new W3dSpr();
	spr->m_resrcMng = this;
	if (!spr->LoadSprite(filename, type)) {
		return spr;
	}
	delete spr;
	return nullptr;
}

W3dAniSpr* WResourceManager::Get3DAniSpr(const char* filename, int type, float fSprSizeX, float fSprSizeY) {
	W3dAniSpr* spr = new W3dAniSpr();
	spr->m_resrcMng = this;
	if (!spr->LoadSpritesInOneTexture(filename, type, fSprSizeX, fSprSizeY)) {
		return spr;
	}
	delete spr;
	return nullptr;
}

void WResourceManager::StrcpyLower(char* out, const char* src) {
	for (; *src; src++) {
		*out++ = (*src >= 'A' && *src <= 'Z') ? (*src - 0x20) : *src;
	}
	*out = 0;
}

const char* WResourceManager::FindMatchFile(const char* filename) {
	char lowername[64] = {0};

	if (!this->m_matchDirectory) {
		return filename;
	}

	const char* basename = strrchr(filename, '/');
	if (!basename) {
		basename = strrchr(filename, '\\');
		if (!basename) {
			return filename;
		}
	}

	// Increment past the directory separator.
	basename++;

	StrcpyLower(lowername, basename);

	auto* match = this->m_matchList.Find(lowername);
	if (!match) {
		return filename;
	}

	return match->fullname;
}

WFixedFont* WResourceManager::GetFixedFont(const char* filename) {
	// TODO: Implement.
	abort();
}

int WResourceManager::UploadTexture(const char* texName, const Bitmap* bitmap, unsigned int type, RECT* rect) {
	// TODO: Implement.
	abort();
}

void WResourceManager::FixTexture(int texHandle, const Bitmap* bitmap, unsigned int type, RECT* rect) const {
	if (rect) {
		this->video->FixTexturePart(texHandle, *rect, bitmap->m_bi, bitmap->m_vram, type);
	} else {
		this->video->UpdateTexture(texHandle, bitmap->m_bi, bitmap->m_vram, type);
	}
}

int WResourceManager::LoadTexture(const char* filename, unsigned int type, int level, const char* texname) {
	// TODO: Implement.
	abort();
}

int WResourceManager::GetTextureWidth(int texHandle) {
	for (auto* it = this->texList.Start(); it != nullptr; it = this->texList.Next()) {
		if (it->texhandle == texHandle) {
			return it->width;
		}
	}
	return 0;
}

int WResourceManager::GetTextureHeight(int texHandle) {
	for (auto* it = this->texList.Start(); it != nullptr; it = this->texList.Next()) {
		if (it->texhandle == texHandle) {
			return it->height;
		}
	}
	return 0;
}

Bitmap* WResourceManager::MakeQuarterBitmap(Bitmap* bitmap) {
	// TODO: should downsample image.
	return new Bitmap(*bitmap);
}

void WResourceManager::AddMissingTexture(const char* filename) {
	if (!this->m_missingTextureList.Find(filename)) {
		char* filenameCopied = new char[strlen(filename) + 1];
		strcpy(filenameCopied, filename);
		this->m_missingTextureList.AddItem(filenameCopied, filenameCopied, false);
	}
}

Bitmap* WResourceManager::LoadBRES(const char* zipname, const char* filename) {
	// TODO: Load zipped bitmap.
	return nullptr;
}

Bitmap* WResourceManager::LoadBMP(const char* filename) {
	// TODO: Load bitmap.
	return nullptr;
}

Bitmap* WResourceManager::LoadJPG(const char* filename) {
	// TODO: Load JPEG image.
	return nullptr;
}

Bitmap* WResourceManager::LoadPNG(const char* filename, bool bFromMem, bool bNet) {
	// TODO: Load PNG image.
	return nullptr;
}

Bitmap* WResourceManager::LoadTGA(const char* filename) {
	// TODO: Load TGA image.
	return nullptr;
}

Bitmap* WResourceManager::LoadBitmapA(const char* filename, int level, bool bNet) {
	char temp[256];
	Bitmap* result = nullptr;
	this->m_lock[1].Lock();
	const char* extension = strrchr(filename, '.');
	const char* zipName = strrchr(filename, '?');
	if (zipName) {
		memset(temp, 0, 0x100);
		memcpy(temp, filename, zipName - filename);
		result = this->LoadBRES(zipName + 1, temp);
	} else if (extension) {
		if (!_strcmpi(extension, ".bmp")) {
			result = this->LoadBMP(filename);
		} else if (!_strcmpi(extension, ".jpg")) {
			result = this->LoadJPG(filename);
		} else if (!_strcmpi(extension, ".png")) {
			result = this->LoadPNG(filename, false, bNet);
		} else if (!_strcmpi(extension, ".tga")) {
			result = this->LoadTGA(filename);
		}
		if (!result && (!_strcmpi(extension, ".jpg") || !_strcmpi(extension, ".bmp"))) {
			strcpy(&temp[4], filename);
			strcpy(strrchr(temp + 4, '.'), ".png");
			result = this->LoadPNG(temp + 4, false, false);
		}
	}
	if (result && result->m_bi->bmiHeader.biWidth > 8 && result->m_bi->bmiHeader.biHeight > 8 && this->m_savemem[level]) {
		Bitmap* downsampled = this->MakeQuarterBitmap(result);
		delete result;
		result = downsampled;
	}
	if (!level && result) {
		result->Update();
	}
	this->m_lock[1].Unlock();
	return result;
}

cFile* WResourceManager::GetCFile(const char* filename, int len) {
	return ::GetCFile(this->FindMatchFile(filename), len, 0);
}
