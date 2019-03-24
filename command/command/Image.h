#pragma once
#include "History.h"
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(CHistory& history, const boost::filesystem::path& path, int width, int height);

	boost::filesystem::path GetPath() const override;

	// Ширина изображения в пикселях
	int GetWidth() const override;

	// Высота изображения в пикселях
	int GetHeight() const override;

	// Изменяет размер изображения
	void Resize(int width, int height) override;

private:
	boost::filesystem::path m_path;
	int m_width;
	int m_height;
	CHistory& m_history;
	void InitializationPath(const boost::filesystem::path& path);
};
