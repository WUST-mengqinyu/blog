#!/bin/bash
git pull
cd Team-Wiki && mkdocs gh-deploy
cd ..
git add *
timenow=$(date)
git commit -m "${timenow}"
git push
