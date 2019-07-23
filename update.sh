#!/bin/bash
cd Team-Wiki && mkdocs gh-deploy
cd /home/badcw/PycharmProjects/Team-Wiki && git pull
cd /home/badcw/PycharmProjects/Team-Wiki && git add *
timenow=$(date)" badcw"
cd /home/badcw/PycharmProjects/Team-Wiki && git commit -m "${timenow}"
cd /home/badcw/PycharmProjects/Team-Wiki && git push