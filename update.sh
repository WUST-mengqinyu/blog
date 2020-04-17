#!/bin/bash
git pull
mkdocs gh-deploy
git add *
timenow=$(date)
git commit -m "${timenow}"
git push
