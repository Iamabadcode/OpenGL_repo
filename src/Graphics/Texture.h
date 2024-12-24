#pragma once

class Texture
{
public:
	Texture(const char* path);
	~Texture();



	void Use() const { glBindTexture(GL_TEXTURE_2D, m_texture_id); }
	void Unuse() const { glBindTexture(GL_TEXTURE_2D, 0); }

	unsigned int id() const { return m_texture_id; }
private:
	int m_width;
	int m_height;
	int m_nr_channels;

	unsigned int m_texture_id;
};