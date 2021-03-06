#pragma once

#include "Extract/paz/HaruotoFD.h"

class Cef_first final : public CHaruotoFD
{
public:
	bool Mount(CArcFile* archive) override;
	bool Decode(CArcFile* archive) override;

private:
	bool IsSupported(const CArcFile* archive);

	void InitMountKey(CArcFile* archive) override;
	void InitDecodeKey(CArcFile* archive) override;

	size_t InitMovieTable(const u8* table) override;

	void DecodeTable1() override;

	void Decrypt(u8* target, size_t size) override;

	void DecodeMovieData(u8* target, size_t size) override;

	size_t GetMovieBufSize(const CArcFile* archive) override;

	u8  m_key = 0;
	u8  m_movie_table[256][256];
	u32 m_movie_table_id = 0;
};
