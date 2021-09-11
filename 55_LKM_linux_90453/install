#!/bin/bash

sudo mkdir -p "/lib/modules/"`uname -r`"/kernel/drivers/occlum"
sudo cp simple.ko "/lib/modules/"`uname -r`"/kernel/drivers/occlum"

if [ -e "/etc/modules" ]; then
    # Ubuntu
    sudo sh -c "cat /etc/modules | grep -Fxq simple || echo simple >> /etc/modules"
elif [ -d "/etc/modules-load.d" ]; then
    # CentOS
    sudo sh -c "echo \"simple\" > /etc/modules-load.d/simple.conf"
fi
sudo /sbin/depmod
sudo /sbin/modprobe simple
