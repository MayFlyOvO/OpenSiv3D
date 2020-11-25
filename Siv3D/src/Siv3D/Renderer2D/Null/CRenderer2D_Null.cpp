﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include "CRenderer2D_Null.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>

namespace s3d
{
	CRenderer2D_Null::CRenderer2D_Null()
	{
		// do nothing
	}

	CRenderer2D_Null::~CRenderer2D_Null()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Null::~CRenderer2D_Null()");
	}

	void CRenderer2D_Null::init()
	{
		LOG_SCOPED_TRACE(U"CRenderer2D_Null::init()");
	}

	void CRenderer2D_Null::addLine(const Float2&, const Float2&, float, const Float4(&)[2])
	{
		// do nothing
	}

	void CRenderer2D_Null::addTriangle(const Float2(&)[3], const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addTriangle(const Float2(&)[3], const Float4(&)[3])
	{
		// do nothing
	}

	void CRenderer2D_Null::addRect(const FloatRect&, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addRect(const FloatRect&, const Float4(&)[4])
	{
		// do nothing
	}

	void CRenderer2D_Null::addRectFrame(const FloatRect&, const float, const Float4&, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addCircle(const Float2&, const float, const Float4&, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addCircleFrame(const Float2&, const float, const float, const Float4&, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addQuad(const FloatQuad&, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addQuad(const FloatQuad&, const Float4(&)[4])
	{
		// do nothing
	}

	void CRenderer2D_Null::addLineString(const Vec2*, const size_t, const Optional<Float2>&, const float, const bool, const Float4&, const IsClosed)
	{
		// do nothing
	}

	void CRenderer2D_Null::addLineString(const Vec2*, const ColorF*, const size_t, const Optional<Float2>&, const float, const bool, const IsClosed)
	{
		// do nothing
	}

	void CRenderer2D_Null::addPolygon(const Array<Float2>&, const Array<TriangleIndex>&, const Optional<Float2>&, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addPolygon(const Vertex2D*, const size_t, const TriangleIndex*, const size_t)
	{
		// do nothing
	}

	void CRenderer2D_Null::addPolygonFrame(const Float2*, const size_t, const float, const Float4&)
	{
		// do nothing
	}

	void CRenderer2D_Null::addNullVertices(const uint32)
	{
		// do nothing
	}

	Optional<VertexShader> CRenderer2D_Null::getCustomVS() const
	{
		return none;
	}

	BlendState CRenderer2D_Null::getBlendState() const
	{
		return BlendState::Default;
	}

	RasterizerState CRenderer2D_Null::getRasterizerState() const
	{
		return RasterizerState::Default2D;
	}

	SamplerState CRenderer2D_Null::getSamplerState(const ShaderStage, const uint32) const
	{
		return SamplerState::Default2D;
	}

	void CRenderer2D_Null::setBlendState(const BlendState&)
	{
		// do nothing
	}

	void CRenderer2D_Null::setRasterizerState(const RasterizerState&)
	{
		// do nothing
	}

	void CRenderer2D_Null::setSamplerState(const ShaderStage, const uint32, const SamplerState&)
	{
		// do nothing
	}

	Optional<PixelShader> CRenderer2D_Null::getCustomPS() const
	{
		return none;
	}

	void CRenderer2D_Null::setCustomVS(const Optional<VertexShader>&)
	{
		// do nothing
	}

	void CRenderer2D_Null::setCustomPS(const Optional<PixelShader>&)
	{
		// do nothing
	}

	float CRenderer2D_Null::getMaxScaling() const noexcept
	{
		return 1.0f;
	}
}
