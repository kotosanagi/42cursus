#!/bin/sh

pgrep /telegraf-1.16.2/usr/bin/telegraf
RET_TELEGRAF=$?

pgrep vsftpd
RET_VSFTPD=$?

if [ $RET_TELEGRAF == 1 -o $RET_VSFTPD == 1 ]; then
    exit 1
else
    exit 0
fi