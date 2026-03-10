#!/bin/sh
# SAR OS Resource Optimization
# Author: Vladimir Letunovsky

# Remove sound modules
modprobe -r snd_bcm2835 2>/dev/null
modprobe -r snd 2>/dev/null

# Disable wireless for power saving
ifconfig wlan0 down 2>/dev/null
modprobe -r brcmfmac 2>/dev/null
modprobe -r bluetooth 2>/dev/null

# Stop GUI services
rc-service lxdm stop 2>/dev/null
rc-update del lxdm default 2>/dev/null
