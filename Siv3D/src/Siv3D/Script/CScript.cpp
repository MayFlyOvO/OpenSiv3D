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

# include "CScript.hpp"
# include <Siv3D/Error.hpp>
# include <Siv3D/EngineLog.hpp>
# include <Siv3D/Unicode.hpp>
# include <Siv3D/FileSystem.hpp>
# include <Siv3D/Logger.hpp>
# include "angelscript/scriptarray.h"
# include "angelscript/scriptgrid.h"
# include "angelscript/scriptstdstring.h"
# include "Bind/ScriptBind.hpp"

namespace s3d
{
	namespace detail
	{
		[[nodiscard]]
		inline constexpr StringView GetMessageType(const AngelScript::asEMsgType msgType) noexcept
		{
			constexpr std::array<StringView, 3> types =
			{
				U"error"_sv, U"warning"_sv, U"info"_sv
			};

			return types[msgType];
		}

		static void MessageCallback(const AngelScript::asSMessageInfo* msg, void* pMessageArray)
		{
			const StringView type = GetMessageType(msg->type);
			const String section = Unicode::Widen(msg->section);
			const String message = Unicode::Widen(msg->message);

			const String fullMessage = (U"[{}] {}({}): "_fmt(type, FileSystem::FileName(section), msg->row) + message);
			const String logMessage = (U"{}({}): {}: "_fmt(section, msg->row, type) + message);
			Logger(logMessage);

			Array<String>* messageArray = static_cast<Array<String>*>(pMessageArray);
			messageArray->push_back(fullMessage);
		}
	}

	CScript::CScript() {}

	CScript::~CScript()
	{
		LOG_SCOPED_TRACE(U"CScript::~CScript()");

		shutdown();
	}

	void CScript::init()
	{
		LOG_SCOPED_TRACE(U"CScript::init()");

		if (m_engine = AngelScript::asCreateScriptEngine(ANGELSCRIPT_VERSION); 
			(not m_engine))
		{
			throw EngineError{ U"asCreateScriptEngine() failed" };
		}

		if (m_engine->SetMessageCallback(asFUNCTION(detail::MessageCallback), &m_messages, AngelScript::asCALL_CDECL) < 0)
		{
			throw EngineError{ U"SetMessageCallback() failed" };
		}
		m_engine->SetEngineProperty(AngelScript::asEP_REQUIRE_ENUM_SCOPE, 1);
		m_engine->SetEngineProperty(AngelScript::asEP_USE_CHARACTER_LITERALS, 1);
		m_engine->SetEngineProperty(AngelScript::asEP_DISALLOW_EMPTY_LIST_ELEMENTS, 1);
		m_engine->SetEngineProperty(AngelScript::asEP_ALLOW_UNSAFE_REFERENCES, 1);

		{
			AngelScript::RegisterScriptArray(m_engine);
			AngelScript::RegisterScriptGrid(m_engine);
			RegisterTypes(m_engine);
			RegisterYesNo(m_engine);
			RegisterNamedParameter(m_engine);
			RegisterUtility(m_engine);
			RegisterChar(m_engine);
			AngelScript::RegisterStdString(m_engine);
			RegisterNone_t(m_engine);
			RegisterOptional(m_engine);
			RegisterNumber(m_engine);
			RegisterFloatingPoint(m_engine);

			RegisterDuration(m_engine);
			RegisterDate(m_engine);
			RegisterDateTime(m_engine);
			RegisterTime(m_engine);
			RegisterStopwatch(m_engine);
			RegisterVariableSpeedStopwatch(m_engine);
			RegisterTimer(m_engine);
			RegisterProfiler(m_engine);
			RegisterMillisecClock(m_engine);
			RegisterMicrosecClock(m_engine);
			RegisterRDTSCClock(m_engine);

			RegisterSpecialFolder(m_engine);
			RegisterCopyOption(m_engine);
			RegisterFileSystem(m_engine);
			RegisterResource(m_engine);
			RegisterMathConstants(m_engine);
			RegisterMath(m_engine);
			RegisterEasing(m_engine);
			RegisterPeriodic(m_engine);
			RegisterPrimeNumber(m_engine);

			RegisterColor(m_engine);
			RegisterColorF(m_engine);
			RegisterHSV(m_engine);
			RegisterPalette(m_engine);
			RegisterPoint(m_engine);
			RegisterVec2(m_engine);
			RegisterFloat2(m_engine);
			RegisterVec3(m_engine);
			RegisterFloat3(m_engine);
			RegisterVec4(m_engine);
			RegisterFloat4(m_engine);
			RegisterCircular(m_engine);
			RegisterOffsetCircular(m_engine);
			RegisterMat3x2(m_engine);
			RegisterBezier2(m_engine);
			RegisterBezier3(m_engine);
			RegisterLine(m_engine);
			RegisterRect(m_engine);
			RegisterRectF(m_engine);
			RegisterCircle(m_engine);
			RegisterEllipse(m_engine);

			//void RegisterTriangle(AngelScript::asIScriptEngine * engine);
			//void RegisterQuad(AngelScript::asIScriptEngine * engine);
			//void RegisterRoundRect(AngelScript::asIScriptEngine * engine);
			RegisterPolygon(m_engine);
			RegisterLineString(m_engine);
			RegisterLineStyleParameters(m_engine);
			RegisterLineStyle(m_engine);
			//void RegisterShape2D(AngelScript::asIScriptEngine * engine);
			RegisterFloatRect(m_engine);

			RegisterInput(m_engine);
			RegisterKeyboard(m_engine);
			RegisterMouse(m_engine);

			//void RegisterImage(AngelScript::asIScriptEngine * engine);
			//void RegisterSoundFont(AngelScript::asIScriptEngine * engine);
			//void RegisterWave(AngelScript::asIScriptEngine * engine);
			//void RegisterAudio(AngelScript::asIScriptEngine * engine);

			//void RegisterTextureFormat(AngelScript::asIScriptEngine * engine);
			RegisterTexture(m_engine);
			RegisterTextureRegion(m_engine);
			RegisterTexturedQuad(m_engine);
			RegisterTexturedCircle(m_engine);
			//void RegisterTexturedRoundRect(AngelScript::asIScriptEngine * engine);
			//void RegisterDynamicTexture(AngelScript::asIScriptEngine * engine);
			//void RegisterVideoTexture(AngelScript::asIScriptEngine * engine);
			//void RegisterFont(AngelScript::asIScriptEngine * engine);
			//void RegisterDrawableText(AngelScript::asIScriptEngine * engine);
			//void RegisterTransformer2D(AngelScript::asIScriptEngine * engine);
			//void RegisterScopedViewport2D(AngelScript::asIScriptEngine * engine);

			//void RegisterEmoji(AngelScript::asIScriptEngine * engine);
			//void RegisterIcon(AngelScript::asIScriptEngine * engine);

			RegisterRandom(m_engine);
			RegisterPrint(m_engine);
			RegisterPutText(m_engine);
			RegisterThreading(m_engine);
			RegisterUserAction(m_engine);
			RegisterSystem(m_engine);
			RegisterWindowStyle(m_engine);
			RegisterWindow(m_engine);
			RegisterMonitor(m_engine);
			RegisterCursorStyle(m_engine);
			RegisterCursor(m_engine);
			RegisterGraphics(m_engine);
			RegisterResizeMode(m_engine);
			RegisterScene(m_engine);
			RegisterTextInputMode(m_engine);
			RegisterTextInput(m_engine);
			RegisterSimpleGUI(m_engine);
			RegisterLanguageCode(m_engine);
			RegisterTextToSpeech(m_engine);
			RegisterSay(m_engine);
			//void RegisterDialog(AngelScript::asIScriptEngine* engine);
		}

		{
			auto nullScript = std::make_unique<ScriptData>(ScriptData::Null{}, m_engine);

			if (not nullScript->isInitialized())
			{
				throw EngineError{ U"Failed to create nullScript" };
			}

			m_scripts.setNullData(std::move(nullScript));
		}

		m_shutDown = false;
	}

	void CScript::shutdown()
	{
		if (m_shutDown)
		{
			return;
		}

		LOG_SCOPED_TRACE(U"CScript::shutdown()");

		m_scripts.destroy();

		m_engine->ShutDownAndRelease();

		m_shutDown = true;
	}

	Script::IDType CScript::createFromCode(const StringView code, const ScriptCompileOption compileOption)
	{
		if (not code)
		{
			return Script::IDType::NullAsset();
		}

		{
			auto script = std::make_unique<ScriptData>(ScriptData::Code{}, code, m_engine, compileOption);

			if (not script->isInitialized())
			{
				return Script::IDType::NullAsset();
			}

			const auto id = m_scripts.add(std::move(script));

			m_scripts[id]->setScriptID(id.value());

			return id;
		}
	}

	Script::IDType CScript::createFromFile(const FilePathView path, const ScriptCompileOption compileOption)
	{
		if (not path)
		{
			return Script::IDType::NullAsset();
		}

		{
			auto script = std::make_unique<ScriptData>(ScriptData::File{}, path, m_engine, compileOption);

			if (not script->isInitialized())
			{
				return Script::IDType::NullAsset();
			}

			const auto id = m_scripts.add(std::move(script));

			m_scripts[id]->setScriptID(id.value());

			return id;
		}
	}

	void CScript::release(const Script::IDType handleID)
	{
		m_scripts.erase(handleID);
	}

	bool CScript::compiled(const Script::IDType handleID)
	{
		return m_scripts[handleID]->compileSucceeded();
	}

	bool CScript::reload(const Script::IDType handleID, const ScriptCompileOption compileOption)
	{
		return m_scripts[handleID]->reload(compileOption, handleID.value());
	}
	
	const std::shared_ptr<ScriptModule>& CScript::getModule(const Script::IDType handleID)
	{
		return m_scripts[handleID]->getModule();
	}
	
	AngelScript::asIScriptFunction* CScript::getFunction(const Script::IDType handleID, const StringView decl)
	{
		return m_scripts[handleID]->getFunction(decl);
	}

	Array<String> CScript::getFunctionDeclarations(const Script::IDType handleID, const IncludeParamNames includeParamNames)
	{
		return m_scripts[handleID]->getFunctionDeclarations(includeParamNames);
	}

	const FilePath& CScript::path(const Script::IDType handleID)
	{
		return m_scripts[handleID]->path();
	}

	Array<String> CScript::retrieveMessages_internal()
	{
		Array<String> messages = std::move(m_messages);

		m_messages.clear();

		return messages;
	}

	const Array<String>& CScript::getMessages(const Script::IDType handleID)
	{
		return m_scripts[handleID]->getMessages();
	}

	void CScript::setSystemUpdateCallback(const Script::IDType handleID, const std::function<bool(void)>& callback)
	{
		return m_scripts[handleID]->setSystemUpdateCallback(callback);
	}

	const std::function<bool(void)>& CScript::getSystemUpdateCallback(const uint64 scriptID)
	{
		return m_scripts[Script::IDType(static_cast<Script::IDType>(scriptID))]->getSystemUpdateCallback();
	}

	AngelScript::asIScriptEngine* CScript::getEngine()
	{
		return m_engine;
	}
}
