#pragma once

class settings
{
public:
	bool menu_opened = true;
	struct {
		bool no_recoil = false;
		bool no_spread = false;
		bool one_shoot_kill = false;
		bool trigger_bot = false;
		bool aimbot = false;
		bool aimbot_player_only = false;
	}weapon;
	struct {
		bool never_wanted = false;
	}self;
	struct {
		bool enable = false;
		ImColor color = ImColor(255, 255, 255);
		struct {
			bool enable = false;
			bool line = true;
			bool text = true;
			ImColor color = ImColor(255, 255, 255);
		}vehicle;
		struct {
			bool enable = false;
			bool line = true;
			bool text = true;
			bool bone = true;
			bool box = true;
			ImColor color = ImColor(255, 255, 255);
			bool exclude_self = true;
		}ped;
		struct {
			bool enable = false;
			bool line = true;
			bool text = true;
			ImColor color = ImColor(255, 255, 255);
		}pickup;
		struct {
			bool enable = false;
			bool line = true;
			bool text = true;
			ImColor color = ImColor(255, 255, 255);
		}object;
	}esp;

	settings()
	{
		std::ifstream f("settings.json");
		nlohmann::json j = nlohmann::json::parse(f);
		menu_opened = j["menu_opened"];
		weapon.no_recoil = j["weapon"]["no_recoil"];
		weapon.no_spread = j["weapon"]["no_spread"];
		weapon.one_shoot_kill = j["weapon"]["one_shoot_kill"];
		weapon.trigger_bot = j["weapon"]["trigger_bot"];
		weapon.aimbot = j["weapon"]["aimbot"];
		weapon.aimbot_player_only = j["weapon"]["aimbot_player_only"];
		self.never_wanted = j["self"]["never_wanted"];
		esp.enable = j["esp"]["enable"];
		esp.color = (ImColor)j["esp"]["color"];
		esp.vehicle.enable = j["esp"]["vehicle"]["enbale"];
		esp.vehicle.line = j["esp"]["vehicle"]["line"];
		esp.vehicle.text = j["esp"]["vehicle"]["text"];
		esp.vehicle.color = (ImColor)j["esp"]["vehicle"]["color"];
		esp.ped.enable = j["esp"]["ped"]["enbale"];
		esp.ped.line = j["esp"]["ped"]["line"];
		esp.ped.text = j["esp"]["ped"]["text"];
		esp.ped.bone = j["esp"]["ped"]["bone"];
		esp.ped.box = j["esp"]["ped"]["box"];
		esp.ped.color = (ImColor)j["esp"]["ped"]["color"];
		esp.ped.exclude_self = j["esp"]["ped"]["exclude_self"];
		esp.pickup.enable = j["esp"]["pickup"]["enbale"];
		esp.pickup.line = j["esp"]["pickup"]["line"];
		esp.pickup.text = j["esp"]["pickup"]["text"];
		esp.pickup.color = (ImColor)j["esp"]["pickup"]["color"];
		esp.object.enable = j["esp"]["object"]["enbale"];
		esp.object.line = j["esp"]["object"]["line"];
		esp.object.text = j["esp"]["object"]["text"];
		esp.object.color = (ImColor)j["esp"]["object"]["color"];
	}
	~settings()
	{
		nlohmann::json j;
		j["menu_opened"] = menu_opened;
		j["weapon"]["no_recoil"] = weapon.no_recoil;
		j["weapon"]["no_spread"] = weapon.no_spread;
		j["weapon"]["one_shoot_kill"] = weapon.one_shoot_kill;
		j["weapon"]["trigger_bot"] = weapon.trigger_bot;
		j["weapon"]["aimbot"] = weapon.aimbot;
		j["weapon"]["aimbot_player_only"] = weapon.aimbot_player_only;
		j["self"]["never_wanted"] = self.never_wanted;
		j["esp"]["enable"] = esp.enable;
		j["esp"]["color"] = (ImU32)esp.color;
		j["esp"]["vehicle"]["enbale"] = esp.vehicle.enable;
		j["esp"]["vehicle"]["line"] = esp.vehicle.line;
		j["esp"]["vehicle"]["text"] = esp.vehicle.text;
		j["esp"]["vehicle"]["color"] = (ImU32)esp.vehicle.color;
		j["esp"]["ped"]["enbale"] = esp.ped.enable;
		j["esp"]["ped"]["line"] = esp.ped.line;
		j["esp"]["ped"]["text"] = esp.ped.text;
		j["esp"]["ped"]["bone"] = esp.ped.bone;
		j["esp"]["ped"]["box"] = esp.ped.box;
		j["esp"]["ped"]["color"] = (ImU32)esp.ped.color;
		j["esp"]["ped"]["exclude_self"] = esp.ped.exclude_self;
		j["esp"]["pickup"]["enbale"] = esp.pickup.enable;
		j["esp"]["pickup"]["line"] = esp.pickup.line;
		j["esp"]["pickup"]["text"] = esp.pickup.text;
		j["esp"]["pickup"]["color"] = (ImU32)esp.pickup.color;
		j["esp"]["object"]["enbale"] = esp.object.enable;
		j["esp"]["object"]["line"] = esp.object.line;
		j["esp"]["object"]["text"] = esp.object.text;
		j["esp"]["object"]["color"] = (ImU32)esp.object.color;

		std::ofstream o("settings.json");
		o << std::setw(4) << j << std::endl;

	}
};

inline std::unique_ptr<settings> g_settings;