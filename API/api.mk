NAME := apps_ww101key_07b_03_httpbin_get

$(NAME)_SOURCES    := api.c

$(NAME)_COMPONENTS := protocols/HTTP_client

WIFI_CONFIG_DCT_H := wifi_config_dct.h