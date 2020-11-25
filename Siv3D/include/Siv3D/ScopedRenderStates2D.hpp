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

# pragma once
# include "Common.hpp"
# include "Uncopyable.hpp"
# include "Graphics2D.hpp"

namespace s3d
{
	class ScopedRenderStates2D : Uncopyable
	{
	public:

		struct SamplerStateInfo
		{
			ShaderStage shaderStage;

			uint32 slot;

			SamplerState state;
		};

		ScopedRenderStates2D() = default;

		explicit ScopedRenderStates2D(const BlendState& blendState);

		explicit ScopedRenderStates2D(const RasterizerState& rasterizerState);

		explicit ScopedRenderStates2D(const SamplerState& samplerState);

		explicit ScopedRenderStates2D(const Array<SamplerStateInfo>& samplerStateInfos);

		/*
		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState);

		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState);

		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const BlendState& blendState, const RasterizerState& rasterizerState, const SamplerState& samplerState);

		ScopedRenderStates2D(const BlendState& blendState, const SamplerState& samplerState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const BlendState& blendState, const SamplerState& samplerState);

		ScopedRenderStates2D(const RasterizerState& rasterizerState, const SamplerState& samplerState, const BlendState& blendState);

		ScopedRenderStates2D(const SamplerState& samplerState, const BlendState& blendState, const RasterizerState& rasterizerState);

		ScopedRenderStates2D(const SamplerState& samplerState, const RasterizerState& rasterizerState, const BlendState& blendState);
		*/

		ScopedRenderStates2D(ScopedRenderStates2D&& other) noexcept;

		~ScopedRenderStates2D();

		//ScopedRenderStates2D& operator =(ScopedRenderStates2D&& other) noexcept;

	private:

		Optional<BlendState> m_oldBlendState;
		
		Optional<RasterizerState> m_oldRasterizerState;
		
		Array<SamplerStateInfo> m_oldSamplerStateInfos;

		void clear() noexcept;
	};
}

# include "detail/ScopedRenderStates2D.ipp"
