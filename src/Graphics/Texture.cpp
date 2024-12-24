#include "GL_util.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture(const char* path)
	: m_width(-1), m_height(-1), m_nr_channels(-1), m_texture_id(0)
{
	unsigned char* data; 
 	glGenTextures(1, &m_texture_id);
	glBindTexture(GL_TEXTURE_2D, m_texture_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::string filepath = std::string("res/") + path;
	data = stbi_load(filepath.c_str(), &m_width, &m_height, &m_nr_channels, 0);
	Debug::Log("Loaded texture " + filepath, Debug::INFO);

	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

	}
	else 
	{
		Debug::Log(std::string("Texture ") + path + " failed to load", Debug::ERROR);
		ASSERT(false);
	}
	
	stbi_image_free(data);

	Debug::Log("Created Texture", Debug::INFO);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture_id);
}
