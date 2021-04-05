#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "textureObject.h"
#include <map>

class TextureManager
{
public:
	static TextureManager* instance()
	{
		if (!tetMgr)
			tetMgr = new TextureManager();
		return tetMgr;
	}
	~TextureManager();
	void operator=(const TextureManager &) = delete;

	unsigned int createTexture(std::string source, bool vertically_on_load = true);
	std::shared_ptr<TextureObject> getTexture(std::string source);
	std::shared_ptr<TextureObject> getTexture(unsigned int texId);
	void removeTexture(std::string source);
	void removeTexture(unsigned int texId);
private:
	TextureManager();

public:

private:
	std::map<std::string, std::shared_ptr<TextureObject>> texs;
	static TextureManager* tetMgr;
};

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	texs.clear();
}

unsigned int TextureManager::createTexture(std::string source, bool vertically_on_load)
{
	std::shared_ptr<TextureObject> to = std::make_shared< TextureObject>(source, vertically_on_load);
	texs[source] = to;
	return to->getTextureId();
}

std::shared_ptr<TextureObject> TextureManager::getTexture(std::string source)
{
	auto ret = texs.find(source);
	return ret == texs.end() ? nullptr : ret->second;
}

std::shared_ptr<TextureObject> TextureManager::getTexture(unsigned int texId)
{
	for (auto temp : texs)
		if (temp.second->getTextureId() == texId)
			return temp.second;
	return nullptr;
}

void TextureManager::removeTexture(std::string source)
{
	texs.erase(source);
}

void TextureManager::removeTexture(unsigned int texId)
{
	for (auto temp : texs)
	{
		if (temp.second->getTextureId() == texId)
		{
			texs.erase(temp.first);
			break;
		}
	}
}

TextureManager* TextureManager::tetMgr = nullptr;
#endif