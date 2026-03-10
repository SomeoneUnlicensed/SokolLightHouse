#!/bin/sh

# SokolLightHouse ISO Generation Script
# This script integrates the service into the Alpine for SAR build.

# 1. Compile the service
make -C SokolLightHouse clean
make -C SokolLightHouse ARCH=armv8-a OPTIMIZE=-O3

# 2. Check build result
if [ ! -f SokolLightHouse/sokol-lighthouse ]; then
    echo "Compilation failed!"
    exit 1
fi

# 3. Create service init script
cat <<EOF > SokolLightHouse/scripts/sokol-lighthouse.init
#!/sbin/openrc-run

name="SokolLightHouse Service"
command="/usr/bin/sokol-lighthouse"
command_background=true
pidfile="/run/sokol-lighthouse.pid"

depend() {
    need localmount
    after bootmisc
}
EOF

chmod +x SokolLightHouse/scripts/sokol-lighthouse.init

# 4. Instructions for alpine-for-sar integration
echo "Integration Instructions:"
echo "1. Copy SokolLightHouse/sokol-lighthouse to your Alpine overlay /usr/bin/"
echo "2. Copy SokolLightHouse/scripts/sokol-lighthouse.init to /etc/init.d/sokol-lighthouse"
echo "3. Run 'rc-update add sokol-lighthouse default' in your local.sh"
echo "4. Re-run 'make iso' in alpine-for-sar directory"
