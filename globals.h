#pragma once
inline DWORD process_id;
inline HANDLE handle;
inline HWND target_hwnd;
inline uintptr_t ReplayInterfacePointer;
inline uintptr_t CPedFactoryPointer;
inline uintptr_t CViewportGamePointer;
inline uintptr_t WindowWidth;
inline uintptr_t camGameplayDirectorPointer;
inline uintptr_t CNetworkPlayerMgrPointer;
inline uintptr_t AimCPedPointer;
inline uintptr_t isCollimationAddress;
inline uintptr_t collimationPedAddress;

// CAutomobile : CVehicle : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// fragInstGta : rage::phfwFragInst : rage::fragInst : rage::phInstBreakable : rage::phInst : rage::pgBase
// CPed : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// phInstGta : rage::phfwInst : rage::phInst : rage::pgBase
// CPickup : CObject : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// phInstGta : rage::phfwInst : rage::phInst : rage::pgBase
// CObject : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// phInstGta : rage::phfwInst : rage::phInst : rage::pgBase
// CPedFactory
// CPed : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CViewportGame : CViewport
// CViewportPrimaryOrtho : CViewport
// CViewportFrontend3DScene : CViewport
// camGameplayDirector : camBaseDirector : camBaseObject : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// camFollowPedCamera : camFollowCamera : camThirdPersonCamera : camBaseCamera : camBaseObject : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CNetworkPlayerMgr : rage::netPlayerMgrBase
// CNetGamePlayer : rage::netPlayer
// CPlayerInfo : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CPed : CPhysical : CDynamicEntity : CEntity : rage::fwEntity : rage::fwExtensibleBase : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CPedWeaponManager : CInventoryListener : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CWeaponInfo : CItemInfo : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// CPedInventory : CWeaponObserver : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// camFollowPedCamera : camFollowCamera : camThirdPersonCamera : camBaseCamera : camBaseObject : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// camFollowPedCameraMetadata : camFollowCameraMetadata : camThirdPersonCameraMetadata : camBaseCameraMetadata : camBaseObjectMetadata : rage::datBase
// camFirstPersonShooterCamera : camFirstPersonAimCamera : camAimCamera : camBaseCamera : camBaseObject : rage::fwRefAwareBase : rage::fwRefAwareBaseImpl<rage::datBase> : rage::datBase
// camFirstPersonShooterCameraMetadata : camFirstPersonAimCameraMetadata : camAimCameraMetadata : camBaseCameraMetadata : camBaseObjectMetadata : rage::datBase

// Model Coordinates
// World Coordinates
// Camera (View) Coordinates
// Clip Coordinates
// Image Coordinates

// Model Matrix (Model Coordinates -> World Coordinates)
// View Matrix (World Coordinates -> Camera (View) Coordinates)
// Projection Matrix (Camera (View) Coordinates -> Clip Coordinates)

// Local Space (Object Space)
// World Space
// View Space (Eye Space)
// Clip Space
// Screen Space

class globals
{
public:
	globals()
	{
        std::ifstream i("file.json");
        json j;
        if (i.is_open()) i >> j;
		//{
		//	if (!j["render_thread"]["enable_esp"].is_null()) j["render_thread"]["enable_esp"];
		//}
		try
		{
			from_json(j["render_thread"]["enable_esp"], render_thread.enable_esp);
			from_json(j["render_thread"]["render_only_in_game"], render_thread.render_only_in_game);
			from_json(j["render_thread"]["text_info"], render_thread.text_info);
			from_json(j["render_thread"]["text_info_color"], render_thread.text_info_color);

			from_json(j["render_thread"]["automobile_esp"], render_thread.automobile_esp);
			from_json(j["render_thread"]["automobile_box"], render_thread.automobile_box);
			from_json(j["render_thread"]["automobile_box_color"], render_thread.automobile_box_color);
			from_json(j["render_thread"]["automobile_text_info"], render_thread.automobile_text_info);
			from_json(j["render_thread"]["automobile_text_info_color"], render_thread.automobile_text_info_color);

			from_json(j["render_thread"]["ped_esp"], render_thread.ped_esp);
			from_json(j["render_thread"]["ped_esp_exclude_self"], render_thread.ped_esp_exclude_self);
			from_json(j["render_thread"]["ped_box"], render_thread.ped_box);
			from_json(j["render_thread"]["ped_box_color"], render_thread.ped_box_color);
			from_json(j["render_thread"]["ped_text_info"], render_thread.ped_text_info);
			from_json(j["render_thread"]["ped_text_info_color"], render_thread.ped_text_info_color);
			from_json(j["render_thread"]["ped_bone"], render_thread.ped_bone);
			from_json(j["render_thread"]["ped_bone_color"], render_thread.ped_bone_color);

			from_json(j["render_thread"]["pickup_esp"], render_thread.pickup_esp);
			from_json(j["render_thread"]["pickup_box"], render_thread.pickup_box);
			from_json(j["render_thread"]["pickup_box_color"], render_thread.pickup_box_color);
			from_json(j["render_thread"]["pickup_text_info"], render_thread.pickup_text_info);
			from_json(j["render_thread"]["pickup_text_info_color"], render_thread.pickup_text_info_color);

			from_json(j["render_thread"]["object_esp"], render_thread.object_esp);
			from_json(j["render_thread"]["object_box"], render_thread.object_box);
			from_json(j["render_thread"]["object_box_color"], render_thread.object_box_color);
			from_json(j["render_thread"]["object_text_info"], render_thread.object_text_info);
			from_json(j["render_thread"]["object_text_info_color"], render_thread.object_text_info_color);

			from_json(j["render_thread"]["player_esp"], render_thread.player_esp);
			from_json(j["render_thread"]["player_esp_exclude_self"], render_thread.player_esp_exclude_self);
			from_json(j["render_thread"]["player_box"], render_thread.player_box);
			from_json(j["render_thread"]["player_box_color"], render_thread.player_box_color);
			from_json(j["render_thread"]["player_text_info"], render_thread.player_text_info);
			from_json(j["render_thread"]["player_text_info_color"], render_thread.player_text_info_color);

			from_json(j["aimbot_thread_globals"]["enable_aimbot"], aimbot_thread.enable_aimbot);
			from_json(j["aimbot_thread_globals"]["exclude_player"], aimbot_thread.exclude_player);

			from_json(j["main_script_thread"]["no_recoil"], main_script_thread.no_recoil);
			from_json(j["main_script_thread"]["no_spread"], main_script_thread.no_spread);
			from_json(j["main_script_thread"]["one_shoot_kill"], main_script_thread.one_shoot_kill);

			from_json(j["trigger_bot_thread_globals"]["enable_trigger_bot"], trigger_bot_thread.enable_trigger_bot);
		}
		catch (...)
		{
			spdlog::critical("Error json file");
		}
	}
	~globals()
	{
		std::ofstream o("file.json");
		json j = 
			{ 
				{"aimbot_thread", {
					{"enable_aimbot", aimbot_thread.enable_aimbot},
					{"exclude_player", aimbot_thread.exclude_player}
				}},
				{"main_script_thread", {
					{"one_shoot_kill", main_script_thread.one_shoot_kill},
					{"no_recoil", main_script_thread.no_recoil},
					{"no_spread", main_script_thread.no_spread}
				}},
				{"trigger_bot_thread", {
					{"enable_trigger_bot", trigger_bot_thread.enable_trigger_bot}
				}},
				{"render_thread", {
					{"enable_esp", render_thread.enable_esp},
					{"render_only_in_game", render_thread.render_only_in_game},
					{"text_info", render_thread.text_info},
					{"text_info_color", render_thread.text_info_color},

					{"automobile_esp", render_thread.automobile_esp},
					{"automobile_box", render_thread.automobile_box},
					{"automobile_box_color", render_thread.automobile_box_color},
					{"automobile_text_info", render_thread.automobile_text_info},
					{"automobile_text_info_color", render_thread.automobile_text_info_color},

					{"ped_esp", render_thread.ped_esp},
					{"ped_esp_exclude_self", render_thread.ped_esp_exclude_self},
					{"ped_box", render_thread.ped_box},
					{"ped_box_color", render_thread.ped_box_color},
					{"ped_text_info", render_thread.ped_text_info},
					{"ped_text_info_color", render_thread.ped_text_info_color},
					{"ped_bone", render_thread.ped_bone},
					{"ped_bone_color", render_thread.ped_bone_color},

					{"pickup_esp", render_thread.pickup_esp},
					{"pickup_box", render_thread.pickup_box},
					{"pickup_box_color", render_thread.pickup_box_color},
					{"pickup_text_info", render_thread.pickup_text_info},
					{"pickup_text_info_color", render_thread.pickup_text_info_color},

					{"object_esp", render_thread.object_esp},
					{"object_box", render_thread.object_box},
					{"object_box_color", render_thread.object_box_color},
					{"object_text_info", render_thread.object_text_info},
					{"object_text_info_color", render_thread.object_text_info_color},

					{"player_esp", render_thread.player_esp},
					{"player_esp_exclude_self", render_thread.player_esp_exclude_self},
					{"player_box", render_thread.player_box},
					{"player_box_color", render_thread.player_box_color},
					{"player_text_info", render_thread.player_text_info},
					{"player_text_info_color", render_thread.player_text_info_color}
				}}
			};
		o << std::setw(4) << j << std::endl;
	}
	template <typename T>
	void from_json(json& j, T& value)
	{
		if (j.is_null()) return;
		value = j.get<T>();
	}
public:
	struct
	{
		bool enable_aimbot = false;
		bool exclude_player = true;
	}aimbot_thread;

	struct
	{
		bool one_shoot_kill = false;
		bool no_recoil = false;
		bool no_spread = false;
	}main_script_thread;

	struct
	{
		bool enable_trigger_bot = false;
	}trigger_bot_thread;

	struct
	{
		bool enable_esp = true;
		bool render_only_in_game = false;
		bool text_info = true;
		D3DCOLOR text_info_color = D3DCOLOR_RGBA(255, 255, 0, 255);

		bool automobile_esp = false;
		bool automobile_box = true;
		D3DCOLOR automobile_box_color = WHITE(255);
		bool automobile_text_info = true;
		D3DCOLOR automobile_text_info_color = WHITE(255);

		bool ped_esp = true;
		bool ped_esp_exclude_self = true;
		bool ped_box = true;
		D3DCOLOR ped_box_color = WHITE(255);
		bool ped_text_info = true;
		D3DCOLOR ped_text_info_color = WHITE(255);
		bool ped_bone = true;
		D3DCOLOR ped_bone_color = WHITE(255);

		bool pickup_esp = false;
		bool pickup_box = true;
		D3DCOLOR pickup_box_color = WHITE(255);
		bool pickup_text_info = true;
		D3DCOLOR pickup_text_info_color = WHITE(255);

		bool object_esp = false;
		bool object_box = true;
		D3DCOLOR object_box_color = WHITE(255);
		bool object_text_info = true;
		D3DCOLOR object_text_info_color = WHITE(255);

		bool player_esp = false;
		bool player_esp_exclude_self = true;
		bool player_box = true;
		D3DCOLOR player_box_color = WHITE(255);
		bool player_text_info = true;
		D3DCOLOR player_text_info_color = WHITE(255);
	}render_thread;
};

inline std::unique_ptr<globals> g;