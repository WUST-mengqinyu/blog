#!/bin/bash
cd /home/badcw/PycharmProjects/Team-Wiki && git pull
cd Team-Wiki && mkdocs gh-deploy
cd /home/badcw/PycharmProjects/Team-Wiki && git add *
timenow=$(date)
cd /home/badcw/PycharmProjects/Team-Wiki && git commit -m "${timenow}"
cd /home/badcw/PycharmProjects/Team-Wiki && git push
