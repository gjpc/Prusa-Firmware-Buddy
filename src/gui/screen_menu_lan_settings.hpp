/**
 * @file screen_menu_lan_settings.hpp
 */

#pragma once

#include <netdev.h>

#include "screen_menu.hpp"
#include "WindowMenuItems.hpp"
#include "MItem_tools.hpp"
#include "MItem_lan.hpp"

// ------------------- ETHERNET -----------------------
using ScreenMenuEthernetSettings_ = ScreenMenu<EFooter::Off, MI_RETURN, MI_NET_IP_VER_t, WMI_NET<MI_NET_IP, NETDEV_ETH_ID>, MI_IP4_ADDR, MI_IP4_NMSK, MI_IP4_GWAY, MI_HOSTNAME, MI_MAC_ADDR>;

class ScreenMenuEthernetSettings final : public ScreenMenuEthernetSettings_ {
    constexpr static const char *label = N_("ETHERNET SETTINGS");

public:
    ScreenMenuEthernetSettings();

protected:
    virtual void windowEvent(EventLock /*has private ctor*/, window_t *sender, GUI_event_t event, void *param) override;
};

// ------------------------ WIFI -----------------------------------
using ScreenMenuWifiSettings_ = ScreenMenu<EFooter::Off, MI_RETURN, MI_WIFI_STATUS_t, MI_WIFI_INIT_t, MI_WIFI_CREDENTIALS_INI_FILE_t, MI_WIFI_CREDENTIALS_t, MI_NET_IP_VER_t, WMI_NET<MI_NET_IP, NETDEV_ESP_ID>, MI_IP4_ADDR, MI_IP4_NMSK, MI_IP4_GWAY, MI_HOSTNAME, MI_MAC_ADDR>;

class ScreenMenuWifiSettings final : public ScreenMenuWifiSettings_ {
    constexpr static const char *label = N_("WI-FI SETTINGS");

public:
    ScreenMenuWifiSettings();

protected:
    virtual void windowEvent(EventLock /*has private ctor*/, window_t *sender, GUI_event_t event, void *param) override;
};
