#! /bin/bash/

echo raz dwa | awk '{print $1}'
# raz

echo raz dwa | awk '{print $2}'
# dwa

echo raz dwa | awk '{print $0}'
# raz dwa
