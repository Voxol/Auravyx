#include "stdafx.h"
#include "FontLoader.h"
#include "Assets.h"
#include "FileIO.h"

FontLoader::FontLoader()
{
}


FontLoader::~FontLoader()
{
}
FontChar loadCharacter(char character, float x, float y, float width, float height, float xOff, float yOff, float xAdv, float resolution)
{
	float fontSize = -1;
	float texCoords[] = {x, y, x, y + height, x + width, y, x + width, y + height, x, y + height, x + width, y};
	float verts[] = { 0, 0, 0, height / fontSize, width / 1, 0, width / 1, height / fontSize, 0, height / fontSize, width / 1, 0 };
	//texCoords = new float[]{x, y + height, x, y, x + width, y + height, x + width, y, x, y, x + width, y + height};
	for (int i = 0; i < 12; i++)
	{
		texCoords[i] = texCoords[i] / resolution;
	}
	//Util::log(std::vector<float>(texCoords, texCoords + sizeof texCoords / sizeof texCoords[0]).at(1));
	Model model = Model::load2DModel(std::vector<float>(verts, verts + sizeof verts / sizeof verts[0]), std::vector<float>(texCoords, texCoords + sizeof texCoords / sizeof texCoords[0]));
			
	FontChar fontCharacter((int) xAdv, (int) xOff, (int) yOff, (int) width, (int) height, model.vao);
	return fontCharacter;
}

void FontLoader::loadFont(std::string file)
{
	std::vector<std::string> lines = Util::splitString(Util::readTextFile(file), "\n");
	std::vector<FontChar> characters(500);
	
	std::string fontName = FileIO::getFileName(file);
	fontName = fontName.substr(0, fontName.length() - 4);
	std::shared_ptr<Texture> texture = Assets::getTexture(fontName);
	int largestValue = -10;
	std::vector<std::string> lineOne = Util::splitString(lines.at(0), " ");
	std::vector<std::string> sizeString = Util::splitString(lineOne.at(2), "=");
	float size = std::stof(sizeString[1]);
	for (int i = 0; i < lines.size(); i++)
	{
		std::string line = lines.at(i);
		if (Util::startsWith(line, "char "))
		{
			std::string ASCIIID = Util::removeAll(line.substr(8, 8), ' ');
			std::string xString = Util::removeAll(line.substr(18, 5), ' ');
			std::string yString = Util::removeAll(line.substr(25, 5), ' ');
			std::string widthString = Util::removeAll(line.substr(36, 5), ' ');
			std::string heightString = Util::removeAll(line.substr(48, 5), ' ');
			std::string xOffString = Util::removeAll(line.substr(61, 5), ' ');
			std::string yOffString = Util::removeAll(line.substr(74, 5), ' ');
			std::string xAdvString = Util::removeAll(line.substr(88, 5), ' ');
			int asciiCharacter = std::stoi(ASCIIID);
			int height = std::stoi(heightString);
			FontChar character = loadCharacter(asciiCharacter,
				(float) std::stoi(xString),
				(float) std::stoi(yString),
				(float) std::stoi(widthString),
				(float) height,
				(float) std::stoi(xOffString), (float) std::stoi(yOffString), 
				(float) std::stoi(xAdvString), (float) texture->getHeight());
			characters.at(asciiCharacter) = character;
			if (height > largestValue)
			{
				largestValue = height;
			}
		}
	}
	Font bitmapFont(*texture.get(), texture->getHeight(), (float) largestValue, (float)	size, characters, 0.0f, 0.0f, 1.0f, 1.0f);
	Assets::addFont(fontName, bitmapFont);
}

