﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "FontFace.hpp"

namespace s3d
{
	FontFace::~FontFace()
	{
		release();
	}

	bool FontFace::load(const FT_Library library, const void* data, const size_t size)
	{
		release();

		if (const FT_Error error = ::FT_New_Memory_Face(library, static_cast<const FT_Byte*>(data), static_cast<FT_Long>(size), 0, &m_face))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else if (error)
			{
				// failed to open or load
			}

			return false;
		}
		
		if (not init())
		{
			return false;
		}

		return true;
	}

	bool FontFace::load(const FT_Library library, const FilePathView path)
	{
		release();

		if (const FT_Error error = ::FT_New_Face(library, path.narrow().c_str(), 0, &m_face))
		{
			if (error == FT_Err_Unknown_File_Format)
			{
				// unsupported format
			}
			else if (error)
			{
				// failed to open or load
			}

			return false;
		}

		if (not init())
		{
			return false;
		}

		return true;
	}

	HBGlyphInfo FontFace::getGlyphInfo(const StringView s)
	{
		::hb_buffer_clear_contents(m_hbBuffer);

		::hb_buffer_add_utf32(m_hbBuffer,
			reinterpret_cast<const uint32*>(s.data()),
			static_cast<int32>(s.length()), 0, static_cast<int32>(s.length()));

		::hb_buffer_guess_segment_properties(m_hbBuffer);

		::hb_shape(m_hbFont, m_hbBuffer, nullptr, 0);

		uint32 glyphCount = 0;
		const hb_glyph_info_t* glyphInfo = ::hb_buffer_get_glyph_infos(m_hbBuffer, &glyphCount);

		return{ glyphInfo, glyphCount };
	}

	bool FontFace::init()
	{
		assert(m_face != nullptr);
		assert(m_hbBuffer == nullptr);

		m_hbFont = ::hb_ft_font_create_referenced(m_face);

		m_hbBuffer = ::hb_buffer_create();

		if (not ::hb_buffer_allocation_successful(m_hbBuffer))
		{
			return false;
		}

		//::hb_buffer_set_replacement_codepoint(m_hbBuffer, (hb_codepoint_t)-1);

		return true;
	}

	void FontFace::release()
	{
		if (m_hbBuffer)
		{
			::hb_buffer_destroy(m_hbBuffer);
			m_hbBuffer = nullptr;
		}

		if (m_hbFont)
		{
			::hb_font_destroy(m_hbFont);
			m_hbFont = nullptr;
		}

		if (m_face)
		{
			::FT_Done_Face(m_face);
			m_face = nullptr;
		}
	}
}
