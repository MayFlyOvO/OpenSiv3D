﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# define  NOMINMAX
# define  STRICT
# define  WIN32_LEAN_AND_MEAN
# define  _WIN32_WINNT _WIN32_WINNT_WIN7
# define  NTDDI_VERSION NTDDI_WIN7
# include <Windows.h>
# include <wrl.h>
using namespace Microsoft::WRL;
# include <d3d11.h>
# include <Siv3D/Array.hpp>

namespace s3d
{
	class D3D11SwapChain
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		IDXGIAdapter* m_adapter = nullptr;

		DXGI_SWAP_CHAIN_DESC m_desc{};

		ComPtr<IDXGISwapChain> m_swapChain;

		Array<ComPtr<IDXGIOutput>> enumOutputs();

	public:

		D3D11SwapChain(ID3D11Device* device, ID3D11DeviceContext* context, IDXGIAdapter* adapter);

		~D3D11SwapChain();

		bool init();

	};
}

# endif
