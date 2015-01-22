#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "3rdParty\Bitmap.h"
#include "3rdParty\Texture.h"

class TextureLoader
{
private:
	Bitmap flip;
	Texture* gTexture;
	std::string m_name;
public:
	TextureLoader();
	~TextureLoader();
	void LoadTexture(std::string filename);
	Texture* getTexture();
	const std::string& getName(){return m_name;};
	void TextureLoader::FlipImage();
};
#endif

