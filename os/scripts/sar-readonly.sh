#!/bin/sh
# SAR OS Read-Only enabler
# Author: Vladimir Letunovsky

mount -o remount,ro /
mount -t tmpfs -o size=32M tmpfs /tmp
mount -t tmpfs -o size=16M tmpfs /var/log
